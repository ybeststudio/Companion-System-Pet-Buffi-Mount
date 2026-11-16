/*
 * File Name : mount_renewal.cpp
 * Author    : BestStudio
 * Version   : 1.0
 * Date      : 2026-11-13
 *
 * Anka mount ("At") progression, see mount_renewal.h. Rules from the Anka wiki (systems/mount.txt),
 * uiCompanion constants (MOUNT_EVOLVE_REQUIREMENTS, MOUNT_BONUS_SLOT_POOLS, HORSE_SKILL_BONUS, MOUNT_FOOD_*)
 * and locale/common/config_json/mount_runes.json. Anka apply ids are mapped to ours by name.
 */
#include "stdafx.h"
#include "mount_renewal.h"

#ifdef ENABLE_MOUNT_RENEWAL
#include "utils.h"
#include "char.h"
#include "item.h"
#include "affect.h"
#include "constants.h"
#include "desc.h"
#include "cmd.h"
#ifdef ENABLE_MOUNT_FOLLOWER_LEVEL
#include "MountSystem.h"
#endif
#include "desc.h"

namespace
{
	enum
	{
		MOUNT_MAX_LEVEL = 30,
		MOUNT_MAX_EVOLUTION = 3,			// stored 0..3, shown "1 / 4"
		MOUNT_LEVEL_EXP = 10000,			// uiCompanion total_exp
		MOUNT_FOOD_MAX = 518400,			// MOUNT_FOOD_MAX_SECONDS (6 days)
		MOUNT_FOOD_WELL_FED = 259200,
		MOUNT_FOOD_HUNGRY = 172800,
		MOUNT_FOOD_STARVING = 86400,
		MOUNT_BONUS_SLOTS = 3,
		MOUNT_SKILL_COUNT = 4,
		MOUNT_SKILL_MAX_LEVEL = 10,
		MOUNT_SKILL_BOOK_CHANCE = 50,
		MOUNT_RUNE_COUNT = 4,
		MOUNT_RUNE_MAX_RANK = 10,
		AFFECT_MOUNT_RENEWAL = 921,

		VNUM_MEDAL = 50050,					// At Madalyonu: levels 1-20
		VNUM_EMBLEM = 40218,				// At Madalyasi: levels 21-29
		VNUM_FOOD = 58003,					// Dayaniklilik Saman
		VNUM_SKILL_UNLOCKER = 58014,		// At Becerisi Acici
		VNUM_SKILL_BOOK = 40217,			// Binek Beceri Kitabi
		VNUM_FOCUSED_READING = 40216,
		VNUM_YANG = 26002,
	};

	struct SMountBonusDef { WORD bApply; int iMin; int iMax; };
	const SMountBonusDef s_aBonusPool[MOUNT_BONUS_SLOTS][7] =
	{
		{ { APPLY_ATTBONUS_STONE, 1, 10 }, { APPLY_STUN_PCT, 1, 8 }, { APPLY_SP_REGEN, 4, 30 }, { APPLY_HP_REGEN, 4, 30 }, { APPLY_REFLECT_MELEE, 1, 10 }, { APPLY_STEAL_HP, 1, 10 }, { APPLY_STEAL_SP, 1, 10 } },
		{ { APPLY_ATTBONUS_ELEMENTS, 1, 10 }, { APPLY_ENCHANT_FIRE, 1, 10 }, { APPLY_ENCHANT_DARK, 1, 10 }, { APPLY_ENCHANT_ICE, 1, 10 }, { APPLY_ENCHANT_ELECT, 1, 10 }, { APPLY_ENCHANT_WIND, 1, 10 }, { APPLY_ENCHANT_EARTH, 1, 10 } },
		{ { APPLY_PENETRATE_PCT, 1, 10 }, { APPLY_MOV_SPEED, 2, 20 }, { APPLY_POISON_PCT, 1, 8 }, { APPLY_SLOW_PCT, 1, 8 }, { APPLY_DODGE, 2, 15 }, { APPLY_EXP_DOUBLE_BONUS, 2, 20 }, { APPLY_GOLD_DOUBLE_BONUS, 2, 20 } },
	};
	struct SSwitcher { DWORD dwVnum; int iSlot; bool bBetter; };
	const SSwitcher s_aSwitcher[] = { { 58002, 0, false }, { 58004, 1, false }, { 58005, 2, false }, { 65156, 2, true } };

	const WORD s_abSkillApply[MOUNT_SKILL_COUNT] = { APPLY_ATTBONUS_ELEMENTS, APPLY_ATTBONUS_STONE, APPLY_ATTBONUS_MONSTER, APPLY_CRITICAL_PCT };
	const int s_aiSkillValue[MOUNT_SKILL_MAX_LEVEL + 1] = { 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 5 };

	// MOUNT_EVOLVE_REQUIREMENTS, key = current evolution
	struct SEvolve { DWORD dwVnum[3]; int iCount[3]; long long llGold; };
	const SEvolve s_aEvolve[MOUNT_MAX_EVOLUTION] =
	{
		{ { 50050, 40912, 0 }, { 5, 1, 0 }, 5000000LL },
		{ { 50050, 40912, 40914 }, { 10, 3, 1 }, 10000000LL },
		{ { 50050, 40912, 40914 }, { 15, 5, 3 }, 15000000LL },
	};

	struct SMountRuneLevel { WORD bApply; int iValue; long long llCost; int iProb; int iBlessing; DWORD dwVnum[5]; int iCount[5]; };
	static const SMountRuneLevel s_aMountRune[MOUNT_RUNE_COUNT][MOUNT_RUNE_MAX_RANK] =
	{
		{	// rune 1 item 58030
			{ APPLY_NONE, 2, 100000000LL, 70, 3, { 40218, 40822, 40819, 40855, 40922 }, { 1, 200, 2, 2, 1 } },
			{ APPLY_NONE, 4, 125000000LL, 65, 3, { 40218, 40822, 40819, 40855, 40922 }, { 2, 250, 2, 3, 1 } },
			{ APPLY_NONE, 6, 150000000LL, 60, 3, { 40218, 40822, 40819, 40855, 40922 }, { 2, 300, 3, 4, 2 } },
			{ APPLY_NONE, 8, 175000000LL, 55, 3, { 40218, 40822, 40819, 40855, 40922 }, { 3, 350, 3, 5, 2 } },
			{ APPLY_NONE, 10, 200000000LL, 50, 3, { 40218, 40822, 40819, 40923, 40922 }, { 4, 400, 3, 2, 3 } },
			{ APPLY_NONE, 12, 225000000LL, 50, 3, { 40218, 40822, 40819, 40923, 40922 }, { 4, 450, 4, 3, 5 } },
			{ APPLY_NONE, 14, 250000000LL, 50, 3, { 40218, 40822, 40819, 40923, 40926 }, { 5, 500, 5, 3, 3 } },
			{ APPLY_NONE, 16, 275000000LL, 50, 3, { 40218, 40822, 40819, 40923, 40926 }, { 5, 500, 5, 4, 4 } },
			{ APPLY_NONE, 18, 300000000LL, 50, 3, { 40218, 40822, 40819, 40923, 40926 }, { 5, 500, 5, 5, 5 } },
			{ APPLY_NONE, 20, 350000000LL, 50, 3, { 40218, 40822, 40819, 40923, 40926 }, { 5, 500, 5, 5, 5 } },
		},
		{	// rune 2 item 58031
			{ APPLY_NONE, 2, 100000000LL, 70, 3, { 40218, 40841, 0, 0, 0 }, { 1, 25, 0, 0, 0 } },
			{ APPLY_NONE, 4, 125000000LL, 65, 3, { 40218, 40841, 40844, 0, 0 }, { 2, 50, 1, 0, 0 } },
			{ APPLY_NONE, 6, 150000000LL, 60, 3, { 40218, 40841, 40844, 0, 0 }, { 2, 75, 2, 0, 0 } },
			{ APPLY_NONE, 8, 175000000LL, 55, 3, { 40218, 40841, 40844, 0, 0 }, { 3, 100, 2, 0, 0 } },
			{ APPLY_NONE, 10, 200000000LL, 50, 3, { 40218, 40841, 40844, 40840, 40944 }, { 4, 125, 3, 1, 1 } },
			{ APPLY_NONE, 12, 225000000LL, 45, 3, { 40218, 40841, 40844, 40840, 40944 }, { 4, 150, 3, 2, 2 } },
			{ APPLY_NONE, 14, 250000000LL, 40, 3, { 40218, 40841, 40844, 40840, 40944 }, { 5, 175, 4, 3, 3 } },
			{ APPLY_NONE, 16, 300000000LL, 35, 3, { 40218, 40841, 40844, 40840, 40944 }, { 5, 200, 4, 3, 3 } },
			{ APPLY_NONE, 18, 325000000LL, 30, 3, { 40218, 40841, 40844, 40840, 40944 }, { 5, 225, 5, 4, 4 } },
			{ APPLY_NONE, 20, 350000000LL, 25, 3, { 40218, 40841, 40844, 40840, 40944 }, { 5, 250, 5, 5, 5 } },
		},
		{	// rune 3 item 58032
			{ APPLY_NONE, 2, 100000000LL, 70, 3, { 40218, 40841, 40839, 40844, 0 }, { 1, 40, 1, 1, 0 } },
			{ APPLY_NONE, 4, 125000000LL, 65, 3, { 40218, 40841, 40839, 40844, 0 }, { 2, 60, 1, 2, 0 } },
			{ APPLY_NONE, 6, 150000000LL, 60, 3, { 40218, 40841, 40839, 40844, 0 }, { 2, 80, 2, 3, 0 } },
			{ APPLY_NONE, 8, 175000000LL, 55, 3, { 40218, 40841, 40839, 40844, 0 }, { 3, 100, 2, 4, 0 } },
			{ APPLY_NONE, 10, 200000000LL, 50, 3, { 40218, 40841, 40839, 40945, 40944 }, { 4, 120, 3, 1, 1 } },
			{ APPLY_NONE, 12, 225000000LL, 45, 3, { 40218, 40841, 40839, 40945, 40944 }, { 4, 150, 3, 2, 2 } },
			{ APPLY_NONE, 14, 250000000LL, 40, 3, { 40218, 40841, 40839, 40945, 40944 }, { 5, 175, 4, 3, 3 } },
			{ APPLY_NONE, 16, 300000000LL, 35, 3, { 40218, 40841, 40839, 40945, 40944 }, { 5, 200, 4, 3, 3 } },
			{ APPLY_NONE, 18, 325000000LL, 30, 3, { 40218, 40841, 40839, 40945, 40944 }, { 5, 225, 5, 4, 4 } },
			{ APPLY_NONE, 20, 350000000LL, 25, 3, { 40218, 40841, 40839, 40945, 40944 }, { 5, 250, 5, 5, 5 } },
		},
		{	// rune 4 item 58033
			{ APPLY_ATTBONUS_STONE, 1, 100000000LL, 70, 3, { 40218, 40841, 40839, 40842, 0 }, { 1, 80, 2, 1, 0 } },
			{ APPLY_ATTBONUS_STONE, 2, 125000000LL, 65, 3, { 40218, 40841, 40839, 40842, 0 }, { 2, 100, 2, 1, 0 } },
			{ APPLY_ATTBONUS_STONE, 3, 150000000LL, 60, 3, { 40218, 40841, 40839, 40842, 0 }, { 2, 120, 3, 2, 0 } },
			{ APPLY_ATTBONUS_STONE, 4, 175000000LL, 55, 3, { 40218, 40841, 40839, 40842, 0 }, { 3, 100, 3, 2, 0 } },
			{ APPLY_ATTBONUS_STONE, 5, 200000000LL, 50, 3, { 40218, 40841, 40845, 40945, 40944 }, { 4, 150, 1, 1, 1 } },
			{ APPLY_ATTBONUS_STONE, 6, 225000000LL, 45, 3, { 40218, 40846, 40845, 40945, 40944 }, { 4, 2, 2, 2, 2 } },
			{ APPLY_ATTBONUS_STONE, 7, 250000000LL, 40, 3, { 40218, 40846, 40845, 40945, 40944 }, { 5, 3, 3, 3, 3 } },
			{ APPLY_ATTBONUS_STONE, 8, 300000000LL, 35, 3, { 40218, 40846, 40845, 40945, 40944 }, { 5, 3, 3, 3, 3 } },
			{ APPLY_ATTBONUS_STONE, 9, 325000000LL, 30, 3, { 40218, 40846, 40845, 40945, 40944 }, { 5, 4, 4, 4, 4 } },
			{ APPLY_ATTBONUS_STONE, 10, 350000000LL, 25, 3, { 40218, 40846, 40845, 40945, 40944 }, { 5, 5, 5, 5, 5 } },
		},
	};
	static const DWORD s_adwMountRuneItem[MOUNT_RUNE_COUNT] = { 58030, 58031, 58032, 58033 };

	enum { MR_NO_MOUNT, MR_LEVEL_CAP, MR_ITEM, MR_GOLD, MR_EVOLVED, MR_MAX, MR_FED, MR_SKILL_REQ, MR_SKILL_ORDER, MR_SKILL_UNLOCKED,
		MR_SKILL_UP, MR_SKILL_FAIL, MR_SKILL_MAX, MR_RUNE_REQ, MR_RUNE_PREV, MR_RUNE_UP, MR_RUNE_FAIL, MR_BONUS_LOCKED, MR_BONUS_CHANGED, MR_DONATED, MR_LEVEL_UP };

	struct SMountData
	{
		DWORD dwSeal;
		int lv, exp, evo, food, unlocked;
		int bt[MOUNT_BONUS_SLOTS], bv[MOUNT_BONUS_SLOTS];
		int sk[MOUNT_SKILL_COUNT];
		int rune[MOUNT_RUNE_COUNT], bless[MOUNT_RUNE_COUNT];
	};

	std::string Flag(DWORD dwSeal, const char* c_szField)
	{
		char sz[64];
		snprintf(sz, sizeof(sz), "mntdata.%u_%s", dwSeal, c_szField);
		return sz;
	}

	LPITEM GetSeal(LPCHARACTER ch)
	{
		LPITEM item = ch ? ch->GetWear(WEAR_MOUNT) : NULL;
		return (item && item->GetType() == ITEM_MOUNT) ? item : NULL;
	}

	int RollBonus(int iSlot, bool bBetter, int& riApply)
	{
		const SMountBonusDef& d = s_aBonusPool[iSlot][number(0, 6)];
		riApply = d.bApply;
		int v = number(d.iMin, d.iMax);
		if (bBetter)
			v = MAX(v, number(d.iMin, d.iMax));
		return v;
	}

	void Save(LPCHARACTER ch, const SMountData& d)
	{
		static const char* s_aszNames[] = { "lv", "exp", "evo", "food", "un" };
		const int aiValues[] = { d.lv, d.exp, d.evo, d.food, d.unlocked };
		for (int i = 0; i < 5; ++i)
			ch->SetQuestFlag(Flag(d.dwSeal, s_aszNames[i]), aiValues[i]);
		char sz[16];
		for (int i = 0; i < MOUNT_BONUS_SLOTS; ++i)
		{
			snprintf(sz, sizeof(sz), "bt%d", i); ch->SetQuestFlag(Flag(d.dwSeal, sz), d.bt[i]);
			snprintf(sz, sizeof(sz), "bv%d", i); ch->SetQuestFlag(Flag(d.dwSeal, sz), d.bv[i]);
		}
		for (int i = 0; i < MOUNT_SKILL_COUNT; ++i)
		{
			snprintf(sz, sizeof(sz), "sk%d", i); ch->SetQuestFlag(Flag(d.dwSeal, sz), d.sk[i]);
		}
		for (int i = 0; i < MOUNT_RUNE_COUNT; ++i)
		{
			snprintf(sz, sizeof(sz), "ru%d", i); ch->SetQuestFlag(Flag(d.dwSeal, sz), d.rune[i]);
			snprintf(sz, sizeof(sz), "bl%d", i); ch->SetQuestFlag(Flag(d.dwSeal, sz), d.bless[i]);
		}
		ch->SetQuestFlag(Flag(d.dwSeal, "init"), 1);
	}

	bool Load(LPCHARACTER ch, SMountData& d)
	{
		if (!ch || !ch->GetDesc() || !ch->GetDesc()->IsPhase(PHASE_GAME))
			return false;
		LPITEM pSeal = GetSeal(ch);
		if (!pSeal)
			return false;
		memset(&d, 0, sizeof(d));
		d.dwSeal = pSeal->GetID();
		if (!ch->GetQuestFlag(Flag(d.dwSeal, "init")))
		{
			d.lv = 1;
			d.food = get_global_time() + MOUNT_FOOD_MAX;
			const TItemTable* pProto = pSeal->GetProto();
			if (pProto && pProto->aApplies[0].bType != APPLY_NONE)
			{
				d.bt[0] = pProto->aApplies[0].bType;
				d.bv[0] = pProto->aApplies[0].lValue;
			}
			else
				d.bv[0] = RollBonus(0, false, d.bt[0]);
			Save(ch, d);
			return true;
		}
		d.lv = MAX(1, ch->GetQuestFlag(Flag(d.dwSeal, "lv")));
		d.exp = ch->GetQuestFlag(Flag(d.dwSeal, "exp"));
		d.evo = ch->GetQuestFlag(Flag(d.dwSeal, "evo"));
		d.food = ch->GetQuestFlag(Flag(d.dwSeal, "food"));
		d.unlocked = ch->GetQuestFlag(Flag(d.dwSeal, "un"));
		char sz[16];
		for (int i = 0; i < MOUNT_BONUS_SLOTS; ++i)
		{
			snprintf(sz, sizeof(sz), "bt%d", i); d.bt[i] = ch->GetQuestFlag(Flag(d.dwSeal, sz));
			snprintf(sz, sizeof(sz), "bv%d", i); d.bv[i] = ch->GetQuestFlag(Flag(d.dwSeal, sz));
		}
		for (int i = 0; i < MOUNT_SKILL_COUNT; ++i)
		{
			snprintf(sz, sizeof(sz), "sk%d", i); d.sk[i] = ch->GetQuestFlag(Flag(d.dwSeal, sz));
		}
		for (int i = 0; i < MOUNT_RUNE_COUNT; ++i)
		{
			snprintf(sz, sizeof(sz), "ru%d", i); d.rune[i] = ch->GetQuestFlag(Flag(d.dwSeal, sz));
			snprintf(sz, sizeof(sz), "bl%d", i); d.bless[i] = ch->GetQuestFlag(Flag(d.dwSeal, sz));
		}
		return true;
	}

	int LevelCap(int iEvo)
	{
		return MIN((int) MOUNT_MAX_LEVEL, 10 * (iEvo + 1));
	}

	void MedalOfLevel(int iLevel, DWORD& rdwVnum, int& riCount)
	{
		if (iLevel <= 10)		{ rdwVnum = VNUM_MEDAL; riCount = 20; }
		else if (iLevel <= 20)	{ rdwVnum = VNUM_MEDAL; riCount = 25; }
		else					{ rdwVnum = VNUM_EMBLEM; riCount = 30; }
	}

	void Result(LPCHARACTER ch, int iCode, int iValue = 0)
	{
		ch->ChatPacket(CHAT_TYPE_COMMAND, "MountResult %d %d", iCode, iValue);
	}

	bool HasItems(LPCHARACTER ch, const DWORD* pdwVnum, const int* piCount, int iNum)
	{
		for (int i = 0; i < iNum; ++i)
			if (pdwVnum[i] && ch->CountSpecifyItem(pdwVnum[i]) < piCount[i])
				return false;
		return true;
	}

	void TakeItems(LPCHARACTER ch, const DWORD* pdwVnum, const int* piCount, int iNum)
	{
		for (int i = 0; i < iNum; ++i)
			if (pdwVnum[i] && piCount[i] > 0)
				ch->RemoveSpecifyItem(pdwVnum[i], piCount[i]);
	}

	void Changed(LPCHARACTER ch, const SMountData& d)
	{
		Save(ch, d);
		MountRenewal_RefreshAffect(ch);
		MountRenewal_SendInfo(ch);
	}
}

int MountRenewal_GetLevel(LPCHARACTER ch)
{
	LPITEM pSeal = GetSeal(ch);
	if (!pSeal)
		return 1;
	return MAX(1, ch->GetQuestFlag(Flag(pSeal->GetID(), "lv")));
}

void MountRenewal_RefreshFollower(LPCHARACTER ch)
{
#ifdef ENABLE_MOUNT_FOLLOWER_LEVEL
	if (ch && ch->GetMountSystem())
		ch->GetMountSystem()->RefreshFollower();
#endif
}

void MountRenewal_SendInfo(LPCHARACTER ch)
{
	if (!ch || !ch->GetDesc())
		return;
	SMountData d;
	if (!Load(ch, d))
	{
		ch->ChatPacket(CHAT_TYPE_COMMAND, "MountInfo 0");
		return;
	}
	DWORD dwMedal; int iMedals;
	MedalOfLevel(d.lv, dwMedal, iMedals);
	const int iFoodLeft = MAX(0, d.food - get_global_time());
	ch->ChatPacket(CHAT_TYPE_COMMAND, "MountInfo %u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%d",
		d.dwSeal, d.lv, d.exp, d.evo, iFoodLeft,
		d.bt[0], d.bv[0], d.bt[1], d.bv[1], d.bt[2], d.bv[2],
		d.sk[0], d.sk[1], d.sk[2], d.sk[3], d.unlocked,
		d.rune[0], d.rune[1], d.rune[2], d.rune[3], d.bless[0], d.bless[1], d.bless[2], d.bless[3],
		dwMedal, iMedals);
}

void MountRenewal_RefreshAffect(LPCHARACTER ch)
{
	if (!ch)
		return;
	ch->RemoveAffect(AFFECT_MOUNT_RENEWAL);
	SMountData d;
	if (!Load(ch, d))
		return;

	int aiPoint[MAX_APPLY_NUM] = {};
	for (int i = 0; i <= d.evo && i < MOUNT_BONUS_SLOTS; ++i)
		if (d.bt[i] > 0 && d.bt[i] < MAX_APPLY_NUM)
			aiPoint[d.bt[i]] += d.bv[i];
	for (int i = 0; i < MOUNT_SKILL_COUNT && i < d.unlocked; ++i)
		aiPoint[s_abSkillApply[i]] += s_aiSkillValue[MINMAX(0, d.sk[i], (int) MOUNT_SKILL_MAX_LEVEL)];
	for (int i = 0; i < MOUNT_RUNE_COUNT; ++i)
	{
		if (d.rune[i] <= 0)
			continue;
		const SMountRuneLevel& r = s_aMountRune[i][MIN(d.rune[i], (int) MOUNT_RUNE_MAX_RANK) - 1];
		if (r.bApply != APPLY_NONE)
			aiPoint[r.bApply] += r.iValue;
	}

	for (int i = 1; i < MAX_APPLY_NUM; ++i)
		if (aiPoint[i])
			ch->AddAffect(AFFECT_MOUNT_RENEWAL, aApplyInfo[i].bPointType, aiPoint[i], AFF_NONE, INFINITE_AFFECT_DURATION, 0, true, true);
}

void MountRenewal_OnSealChanged(LPCHARACTER ch, LPITEM pSeal, bool bEquip)
{
	if (!ch)
		return;
	if (bEquip)
	{
		MountRenewal_RefreshAffect(ch);
		MountRenewal_SendInfo(ch);
	}
	else
	{
		ch->RemoveAffect(AFFECT_MOUNT_RENEWAL);
		ch->ChatPacket(CHAT_TYPE_COMMAND, "MountInfo 0");
	}
}

bool MountRenewal_UseItem(LPCHARACTER ch, LPITEM item)
{
	if (!ch || !item)
		return false;
	for (size_t s = 0; s < sizeof(s_aSwitcher) / sizeof(s_aSwitcher[0]); ++s)
	{
		if (item->GetVnum() != s_aSwitcher[s].dwVnum)
			continue;
		SMountData d;
		if (!Load(ch, d))
		{
			Result(ch, MR_NO_MOUNT);
			return true;
		}
		const int iSlot = s_aSwitcher[s].iSlot;
		if (iSlot > d.evo)
		{
			Result(ch, MR_BONUS_LOCKED, iSlot + 1);
			return true;
		}
		d.bv[iSlot] = RollBonus(iSlot, s_aSwitcher[s].bBetter, d.bt[iSlot]);
		item->SetCount(item->GetCount() - 1);
		Changed(ch, d);
		Result(ch, MR_BONUS_CHANGED, iSlot + 1);
		return true;
	}
	if (item->GetVnum() == VNUM_FOOD)
	{
		SMountData d;
		if (!Load(ch, d))
		{
			Result(ch, MR_NO_MOUNT);
			return true;
		}
		d.food = get_global_time() + MOUNT_FOOD_MAX;
		item->SetCount(item->GetCount() - 1);
		Changed(ch, d);
		Result(ch, MR_FED);
		return true;
	}
	return false;
}

ACMD(do_mount_renewal)
{
	char arg1[256], arg2[256];
	two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));
	const std::string sub = arg1;

	if (sub == "info" || sub.empty())
	{
		MountRenewal_SendInfo(ch);
		return;
	}

	if (ch->IsDead() || ch->GetExchange() || ch->GetMyShop() || ch->GetShopOwner() || ch->IsOpenSafebox() || ch->IsCubeOpen())
		return;

	SMountData d;
	if (!Load(ch, d))
	{
		Result(ch, MR_NO_MOUNT);
		return;
	}

	if (sub == "donate")
	{
		int iWant = 1;
		str_to_number(iWant, arg2);
		iWant = MINMAX(1, iWant, 10);
		int iDone = 0;
		bool bLevelUp = false;
		for (; iDone < iWant; ++iDone)
		{
			if (d.lv >= LevelCap(d.evo) || d.lv >= MOUNT_MAX_LEVEL)
				break;
			DWORD dwVnum; int iNeed;
			MedalOfLevel(d.lv, dwVnum, iNeed);
			if (ch->CountSpecifyItem(dwVnum) < 1)
				break;
			ch->RemoveSpecifyItem(dwVnum, 1);
			d.exp += (MOUNT_LEVEL_EXP + iNeed - 1) / iNeed;
			if (d.exp >= MOUNT_LEVEL_EXP)
			{
				d.exp = 0;
				++d.lv;
				Result(ch, MR_LEVEL_UP, d.lv);
				bLevelUp = true;
			}
		}
		if (!iDone)
			Result(ch, d.lv >= LevelCap(d.evo) ? MR_LEVEL_CAP : MR_ITEM);
		else
		{
			Changed(ch, d);
			Result(ch, MR_DONATED, iDone);
			if (bLevelUp)
				MountRenewal_RefreshFollower(ch);
		}
		return;
	}

	if (sub == "evolve")
	{
		if (d.evo >= MOUNT_MAX_EVOLUTION)
		{
			Result(ch, MR_MAX);
			return;
		}
		if (d.lv < LevelCap(d.evo))
		{
			Result(ch, MR_LEVEL_CAP, LevelCap(d.evo));
			return;
		}
		const SEvolve& e = s_aEvolve[d.evo];
		if (!HasItems(ch, e.dwVnum, e.iCount, 3))
		{
			Result(ch, MR_ITEM);
			return;
		}
		if ((long long) ch->GetGold() < e.llGold)
		{
			Result(ch, MR_GOLD);
			return;
		}
		TakeItems(ch, e.dwVnum, e.iCount, 3);
		ch->PointChange(POINT_GOLD, -e.llGold);
		++d.evo;
		if (d.evo < MOUNT_BONUS_SLOTS && !d.bt[d.evo])
			d.bv[d.evo] = RollBonus(d.evo, false, d.bt[d.evo]);
		Changed(ch, d);
		Result(ch, MR_EVOLVED, d.evo);
		return;
	}

	if (sub == "feed")
	{
		if (ch->CountSpecifyItem(VNUM_FOOD) < 1)
		{
			Result(ch, MR_ITEM);
			return;
		}
		ch->RemoveSpecifyItem(VNUM_FOOD, 1);
		d.food = get_global_time() + MOUNT_FOOD_MAX;
		Changed(ch, d);
		Result(ch, MR_FED);
		return;
	}

	if (sub == "skill_unlock")
	{
		if (d.lv < MOUNT_MAX_LEVEL || d.evo < MOUNT_MAX_EVOLUTION)
		{
			Result(ch, MR_SKILL_REQ);
			return;
		}
		if (d.unlocked >= MOUNT_SKILL_COUNT)
		{
			Result(ch, MR_SKILL_MAX);
			return;
		}
		if (d.unlocked > 0 && d.sk[d.unlocked - 1] < MOUNT_SKILL_MAX_LEVEL)
		{
			Result(ch, MR_SKILL_ORDER);
			return;
		}
		if (ch->CountSpecifyItem(VNUM_SKILL_UNLOCKER) < 1)
		{
			Result(ch, MR_ITEM);
			return;
		}
		ch->RemoveSpecifyItem(VNUM_SKILL_UNLOCKER, 1);
		d.sk[d.unlocked] = 1;
		++d.unlocked;
		Changed(ch, d);
		Result(ch, MR_SKILL_UNLOCKED, d.unlocked);
		return;
	}

	if (sub == "skill_up")
	{
		int iSlot = -1;
		str_to_number(iSlot, arg2);
		if (iSlot < 0 || iSlot >= d.unlocked)
		{
			Result(ch, MR_SKILL_REQ);
			return;
		}
		if (d.sk[iSlot] >= MOUNT_SKILL_MAX_LEVEL)
		{
			Result(ch, MR_SKILL_MAX);
			return;
		}
		if (ch->CountSpecifyItem(VNUM_SKILL_BOOK) < 1)
		{
			Result(ch, MR_ITEM);
			return;
		}
		ch->RemoveSpecifyItem(VNUM_SKILL_BOOK, 1);
		const bool bFocused = ch->CountSpecifyItem(VNUM_FOCUSED_READING) > 0;
		if (bFocused)
			ch->RemoveSpecifyItem(VNUM_FOCUSED_READING, 1);
		if (!bFocused && number(1, 100) > MOUNT_SKILL_BOOK_CHANCE)
		{
			MountRenewal_SendInfo(ch);
			Result(ch, MR_SKILL_FAIL, iSlot);
			return;
		}
		++d.sk[iSlot];
		Changed(ch, d);
		Result(ch, MR_SKILL_UP, iSlot);
		return;
	}

	if (sub == "rune_up")
	{
		int iRune = -1;
		str_to_number(iRune, arg2);
		if (iRune < 0 || iRune >= MOUNT_RUNE_COUNT)
			return;
		bool bReady = d.lv >= MOUNT_MAX_LEVEL && d.evo >= MOUNT_MAX_EVOLUTION && d.unlocked >= MOUNT_SKILL_COUNT;
		for (int i = 0; bReady && i < MOUNT_SKILL_COUNT; ++i)
			bReady = d.sk[i] >= MOUNT_SKILL_MAX_LEVEL;
		if (!bReady)
		{
			Result(ch, MR_RUNE_REQ);
			return;
		}
		if (iRune > 0 && d.rune[iRune - 1] < MOUNT_RUNE_MAX_RANK)
		{
			Result(ch, MR_RUNE_PREV);
			return;
		}
		if (d.rune[iRune] >= MOUNT_RUNE_MAX_RANK)
		{
			Result(ch, MR_MAX);
			return;
		}
		const SMountRuneLevel& r = s_aMountRune[iRune][d.rune[iRune]];
		if (!HasItems(ch, r.dwVnum, r.iCount, 5))
		{
			Result(ch, MR_ITEM);
			return;
		}
		if ((long long) ch->GetGold() < r.llCost)
		{
			Result(ch, MR_GOLD);
			return;
		}
		TakeItems(ch, r.dwVnum, r.iCount, 5);
		ch->PointChange(POINT_GOLD, -r.llCost);
		if (d.bless[iRune] < r.iBlessing && number(1, 100) > r.iProb)
		{
			++d.bless[iRune];
			Changed(ch, d);
			Result(ch, MR_RUNE_FAIL, iRune);
			return;
		}
		++d.rune[iRune];
		d.bless[iRune] = 0;
		Changed(ch, d);
		Result(ch, MR_RUNE_UP, iRune);
		return;
	}
}
#endif
