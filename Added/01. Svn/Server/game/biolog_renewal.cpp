/*
 * File Name : biolog_renewal.cpp
 * Author    : BestStudio
 * Version   : 1.0
 * Date      : 2026-11-14
 *
 * Anka biologist, see biolog_renewal.h. Mission table = Anka uiBiologist.BiologWindow.bio_data (live probe):
 * level, item, count, success chance, cooldown, soul stone, boost potions and up to 4 rewards. Anka apply names
 * without an Anka2 apply are mapped to the closest one (user decision 2026-11-14), the chest reroll token is dropped.
 * State lives in quest flags "biolog.*" (mission = index of the current mission 1..14, 15 = all done).
 */
#include "stdafx.h"
#include "biolog_renewal.h"
#include <map>
#include <string>

#ifdef ENABLE_BIOLOG_RENEWAL
#include "utils.h"
#include "char.h"
#include "item.h"
#include "affect.h"
#include "constants.h"
#include "desc.h"
#include "cmd.h"
#include "shop.h"
#include "shop_manager.h"
#include "questmanager.h"
#ifdef ENABLE_MOUNT_RENEWAL
#include "mount_renewal.h"
#endif

namespace
{
	enum
	{
		BIOLOG_MISSION_COUNT = 14,
		BIOLOG_PITY_MAX = 3,						// BIOLOGIST_PITTY_DEFAULT_MAX
		BIOLOG_REWARD_COUNT = 4,
		BIOLOG_SHOP_NPC = 20084,
		BIOLOG_SUCCESS_BOOST = 50,
		AFFECT_BIOLOG_RENEWAL = 960,					// 960 + mission index (1..14)
	};

	enum EBiologResult
	{
		BR_NO_MISSION,
		BR_DONE,				// every mission finished
		BR_WAIT,				// cooldown running (value = seconds left)
		BR_NO_ITEM,				// mission item missing
		BR_NO_STONE,			// soul stone missing
		BR_SUCCESS,				// delivery accepted (value = new count)
		BR_FAIL,				// delivery failed (value = pity)
		BR_STONE_PHASE,
		BR_COMPLETE,			// mission finished (value = mission index)
		BR_BUSY,
		BR_TIME_USED,
	};

	struct SBiologReward
	{
		WORD	wApply;
		int		iValue;
	};

	struct SBiologMission
	{
		int				iLevel;
		DWORD			dwItem;
		int				iCount;
		int				iChance;
		int				iTime;
		DWORD			dwStone;
		DWORD			dwBoostTime;
		DWORD			dwBoostSuccess;
		SBiologReward	aReward[BIOLOG_REWARD_COUNT];
	};

	const SBiologMission s_aMission[BIOLOG_MISSION_COUNT + 1] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, { { APPLY_NONE, 0 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 } } },
		{ 30, 61000, 10, 75, 0, 30220, 60050, 60051, { { APPLY_ATT_SPEED, 10 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 } } },
		{ 40, 61001, 15, 60, 300, 30221, 60050, 60051, { { APPLY_MOV_SPEED, 10 }, { APPLY_ATTBONUS_STONE, 5 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 } } },
		// DEF_BONUS 60, POWER_CRITICAL 5
		{ 50, 61002, 15, 60, 600, 30222, 60050, 60051, { { APPLY_DEF_GRADE_BONUS, 60 }, { APPLY_CRITICAL_PCT, 5 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 } } },
		// ATT_VALUE_PVE 50
		{ 60, 61003, 20, 40, 900, 30223, 60052, 60053, { { APPLY_ATT_GRADE_BONUS, 50 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 } } },
		// MALL_DEFBONUS 10, ATTBONUS_SHRINE_METIN 10
		{ 70, 61004, 25, 40, 1200, 30224, 60052, 60053, { { APPLY_MALL_DEFBONUS, 10 }, { APPLY_ATTBONUS_STONE, 10 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 } } },
		{ 80, 61005, 30, 35, 1800, 30225, 60052, 60053, { { APPLY_MALL_ATTBONUS, 10 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 } } },
		// PVP_RESIST_BONUS 10
		{ 85, 61006, 40, 30, 2700, 30226, 60052, 60053, { { APPLY_BLOCK, 10 }, { APPLY_ATTBONUS_STONE, 5 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 } } },
		{ 90, 61007, 50, 25, 3600, 30227, 60054, 60055, { { APPLY_ATTBONUS_HUMAN, 8 }, { APPLY_ATTBONUS_MONSTER, 5 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 } } },
		// ATTBONUS_RAZADOR 20, ATTBONUS_NEMERE 20
		{ 92, 61008, 25, 20, 7200, 30228, 60054, 60055, { { APPLY_ATTBONUS_DRAGON, 20 }, { APPLY_ATTBONUS_DRAGON, 20 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 } } },
		// POWER_CRITICAL 5
		{ 94, 61009, 30, 20, 9000, 30229, 60054, 60055, { { APPLY_ATTBONUS_BOSS, 5 }, { APPLY_CRITICAL_PCT, 5 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 } } },
		// ATT_VALUE_PVE 100, POWER_PENETRATE 5, ATTBONUS_DUNGEON 5
		{ 100, 61010, 40, 15, 10800, 30230, 60054, 60055, { { APPLY_ATT_GRADE_BONUS, 100 }, { APPLY_PENETRATE_PCT, 5 }, { APPLY_ATTBONUS_MONSTER, 5 }, { APPLY_NONE, 0 } } },
		// ATTBONUS_EREBUS 20, SHRINE_SEAL_DROP_BONUS 10
		{ 105, 61011, 40, 25, 14400, 30231, 60056, 60057, { { APPLY_ATTBONUS_BOSS, 20 }, { APPLY_ITEM_DROP_BONUS, 10 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 } } },
		// ATTBONUS_MELEY 20, ATTBONUS_ELEMENTARY 5 (DUNGEON_CHEST_REROLL_TOKEN 10 dropped)
		{ 108, 61012, 45, 15, 16200, 30232, 60056, 60057, { { APPLY_ATTBONUS_DRAGON, 20 }, { APPLY_ATTBONUS_ELEMENTS, 5 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 } } },
		// NORMAL_HIT_DAMAGE_BONUS_PVE 5
		{ 110, 61013, 50, 10, 18000, 30233, 60056, 60057, { { APPLY_NORMAL_HIT_DAMAGE_BONUS, 5 }, { APPLY_ATTBONUS_STONE, 5 }, { APPLY_NONE, 0 }, { APPLY_NONE, 0 } } },
	};

	struct SBiologState
	{
		int iMission;
		int iCount;
		int iNext;		// cooldown end (global time)
		int iStone;
		int iPity;
	};

	void Load(LPCHARACTER ch, SBiologState& s)
	{
		s.iMission = MAX(1, ch->GetQuestFlag("biolog.mission"));
		s.iCount = ch->GetQuestFlag("biolog.count");
		s.iNext = ch->GetQuestFlag("biolog.next");
		s.iStone = ch->GetQuestFlag("biolog.stone");
		s.iPity = ch->GetQuestFlag("biolog.pity");
	}

	void Save(LPCHARACTER ch, const SBiologState& s)
	{
		ch->SetQuestFlag("biolog.mission", s.iMission);
		ch->SetQuestFlag("biolog.count", s.iCount);
		ch->SetQuestFlag("biolog.next", s.iNext);
		ch->SetQuestFlag("biolog.stone", s.iStone);
		ch->SetQuestFlag("biolog.pity", s.iPity);
	}

	void Result(LPCHARACTER ch, int iCode, int iValue = 0)
	{
		ch->ChatPacket(CHAT_TYPE_COMMAND, "BiologResult %d %d", iCode, iValue);
	}

	void GiveRewards(LPCHARACTER ch, int iMission)
	{
		const SBiologMission& m = s_aMission[iMission];
		ch->RemoveAffect(AFFECT_BIOLOG_RENEWAL + iMission);
		for (int i = 0; i < BIOLOG_REWARD_COUNT; ++i)
			if (m.aReward[i].wApply != APPLY_NONE && m.aReward[i].iValue)
				ch->AddAffect(AFFECT_BIOLOG_RENEWAL + iMission, aApplyInfo[m.aReward[i].wApply].bPointType, m.aReward[i].iValue, AFF_NONE, INFINITE_AFFECT_DURATION, 0, false);
	}

	bool UseOne(LPCHARACTER ch, DWORD dwVnum)
	{
		if (!dwVnum || ch->CountSpecifyItem(dwVnum) < 1)
			return false;
		ch->RemoveSpecifyItem(dwVnum, 1);
		return true;
	}
}

void BiologRenewal_SendInfo(LPCHARACTER ch)
{
	if (!ch || !ch->GetDesc())
		return;
	SBiologState s;
	Load(ch, s);
	const int iLeft = MAX(0, s.iNext - get_global_time());
	ch->ChatPacket(CHAT_TYPE_COMMAND, "BiologInfo %d,%d,%d,%d,%d,%d", s.iMission, s.iCount, iLeft, s.iStone, s.iPity, BIOLOG_PITY_MAX);

	std::map<WORD, int> mapSum;
	for (int i = 1; i < s.iMission && i <= BIOLOG_MISSION_COUNT; ++i)
		for (int r = 0; r < BIOLOG_REWARD_COUNT; ++r)
			if (s_aMission[i].aReward[r].wApply != APPLY_NONE && s_aMission[i].aReward[r].iValue)
				mapSum[s_aMission[i].aReward[r].wApply] += s_aMission[i].aReward[r].iValue;
	std::string list;
	for (std::map<WORD, int>::const_iterator it = mapSum.begin(); it != mapSum.end(); ++it)
	{
		char part[32];
		snprintf(part, sizeof(part), "%s%u,%d", list.empty() ? "" : "|", it->first, it->second);
		list += part;
	}
	ch->ChatPacket(CHAT_TYPE_COMMAND, "BiologBonus %s", list.empty() ? "-" : list.c_str());
}

static bool IsLoginDataLoaded(LPCHARACTER ch)
{
	quest::PC* pPC = quest::CQuestManager::instance().GetPC(ch->GetPlayerID());
	return pPC && pPC->IsLoaded() && ch->IsLoadedAffect();
}

void BiologRenewal_OnDataLoaded(LPCHARACTER ch)
{
	if (!ch || !ch->IsPC() || !IsLoginDataLoaded(ch))
		return;
	BiologRenewal_OnLogin(ch);
#ifdef ENABLE_MOUNT_RENEWAL
	MountRenewal_RefreshAffect(ch);
#endif
}

void BiologRenewal_OnLogin(LPCHARACTER ch)
{
	if (!ch)
		return;
	if (!IsLoginDataLoaded(ch))
		return;
	SBiologState s;
	Load(ch, s);
	for (int i = 1; i <= BIOLOG_MISSION_COUNT; ++i)
	{
		if (i < s.iMission)
			GiveRewards(ch, i);
		else
			ch->RemoveAffect(AFFECT_BIOLOG_RENEWAL + i);
	}
	BiologRenewal_SendInfo(ch);
}

// /biolog info | give <useTime 0/1> <useSuccess 0/1> | shop
ACMD(do_biolog_renewal)
{
	char arg1[256], arg2[256], arg3[256];
	three_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2), arg3, sizeof(arg3));
	const std::string sub = arg1;

	if (sub == "info" || sub.empty())
	{
		BiologRenewal_SendInfo(ch);
		return;
	}

	if (ch->IsDead() || ch->GetExchange() || ch->GetMyShop() || ch->GetShopOwner() || ch->IsOpenSafebox() || ch->IsCubeOpen())
	{
		Result(ch, BR_BUSY);
		return;
	}

	if (sub == "shop")
	{
		LPSHOP pkShop = CShopManager::instance().GetByNPCVnum(BIOLOG_SHOP_NPC);
		if (!pkShop)
			return;
		ch->SetShopOwner(ch);
		pkShop->AddGuest(ch, 0, false);
		return;
	}

	if (sub != "give")
		return;

	SBiologState s;
	Load(ch, s);
	if (s.iMission > BIOLOG_MISSION_COUNT)
	{
		Result(ch, BR_DONE);
		return;
	}
	const SBiologMission& m = s_aMission[s.iMission];
	if (ch->GetLevel() < m.iLevel)
	{
		Result(ch, BR_NO_MISSION, m.iLevel);
		return;
	}

	bool bUseTime = false, bUseSuccess = false;
	{
		int iTmp = 0;
		str_to_number(iTmp, arg2);
		bUseTime = iTmp != 0;
		iTmp = 0;
		str_to_number(iTmp, arg3);
		bUseSuccess = iTmp != 0;
	}

	if (s.iStone)
	{
		if (!UseOne(ch, m.dwStone))
		{
			Result(ch, BR_NO_STONE, m.dwStone);
			return;
		}
		GiveRewards(ch, s.iMission);
		const int iDone = s.iMission;
		s.iMission++;
		s.iCount = 0;
		s.iNext = 0;
		s.iStone = 0;
		s.iPity = 0;
		Save(ch, s);
		Result(ch, BR_COMPLETE, iDone);
		BiologRenewal_SendInfo(ch);
		return;
	}

	const int iNow = get_global_time();
	if (s.iNext > iNow)
	{
		if (!bUseTime || !UseOne(ch, m.dwBoostTime))
		{
			Result(ch, BR_WAIT, s.iNext - iNow);
			return;
		}
		s.iNext = 0;
		Result(ch, BR_TIME_USED);
	}

	if (ch->CountSpecifyItem(m.dwItem) < 1)
	{
		Save(ch, s);
		Result(ch, BR_NO_ITEM, m.dwItem);
		BiologRenewal_SendInfo(ch);
		return;
	}

	const bool bSure = s.iPity >= BIOLOG_PITY_MAX;
	int iChance = m.iChance;
	if (!bSure && bUseSuccess && UseOne(ch, m.dwBoostSuccess))
		iChance = MIN(100, iChance + BIOLOG_SUCCESS_BOOST);

	ch->RemoveSpecifyItem(m.dwItem, 1);
	s.iNext = m.iTime ? iNow + m.iTime : 0;
	if (bSure || number(1, 100) <= iChance)
	{
		s.iCount++;
		s.iPity = 0;
		if (s.iCount >= m.iCount)
		{
			s.iCount = m.iCount;
			s.iStone = 1;
			s.iNext = 0;
			Save(ch, s);
			Result(ch, BR_STONE_PHASE, s.iMission);
		}
		else
		{
			Save(ch, s);
			Result(ch, BR_SUCCESS, s.iCount);
		}
	}
	else
	{
		s.iPity = MIN(BIOLOG_PITY_MAX, s.iPity + 1);
		Save(ch, s);
		Result(ch, BR_FAIL, s.iPity);
	}
	BiologRenewal_SendInfo(ch);
}
#endif
