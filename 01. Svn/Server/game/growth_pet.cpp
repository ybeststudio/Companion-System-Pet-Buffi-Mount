// Dosyanin uygun bir yerine ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
static DWORD PetEvolutionLevelCap(DWORD dwEvolution);
#endif


// LPGROWTH_PET CGrowthPet::Summon(LPITEM pSummonItem, bool bIsResummon) icinde:
// Bul:
		m_pOwner->LocaleChatPacket(CHAT_TYPE_INFO, 743, "%s", m_strName.c_str());

// Degistir:
#ifdef ENABLE_GROWTH_PET_RENEWAL
		m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetMessage 1 %s", m_strName.c_str());	// lifetime over
#else
		m_pOwner->LocaleChatPacket(CHAT_TYPE_INFO, 743, "%s", m_strName.c_str());
#endif


// LPGROWTH_PET CGrowthPet::Summon(LPITEM pSummonItem, bool bIsResummon) icinde:
// Bul:
		m_pOwner->LocaleChatPacket(CHAT_TYPE_INFO, 744, "");

// Degistir:
#ifdef ENABLE_GROWTH_PET_RENEWAL
		m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetMessage 2 0");
#else
		m_pOwner->LocaleChatPacket(CHAT_TYPE_INFO, 744, "");
#endif


// LPGROWTH_PET CGrowthPet::Summon(LPITEM pSummonItem, bool bIsResummon) icinde:
// Bul:
		m_pOwner->LocaleChatPacket(CHAT_TYPE_INFO, 745, "");

// Degistir:
#ifdef ENABLE_GROWTH_PET_RENEWAL
		m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetMessage 3 0");	// exchange / shop / safebox open
#else
		m_pOwner->LocaleChatPacket(CHAT_TYPE_INFO, 745, "");
#endif


// LPGROWTH_PET CGrowthPet::Summon(LPITEM pSummonItem, bool bIsResummon) icinde:
// Bul:
	const DWORD dwPetVnum = dwPetEvol < PET_EVOLUTION_4 ? pSummonItem->GetValue(0) : pSummonItem->GetValue(3);

// Degistir:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	DWORD dwPetVnum = dwPetEvol < PET_EVOLUTION_4 ? pSummonItem->GetValue(0) : pSummonItem->GetValue(3);
	LPITEM pCostume = m_pOwner->GetWear(WEAR_COSTUME_PET);
	if (pCostume && pCostume != m_pLookExclude && pCostume->IsCostumePetSkin())
	{
		const DWORD dwCostumeMob = pCostume->GetValue(1) ? pCostume->GetValue(1) : pCostume->GetValue(0);
		if (dwCostumeMob)
			dwPetVnum = dwCostumeMob;
	}
#ifdef ENABLE_WARDROBE_SYSTEM
	dwPetVnum = Wardrobe_VisualPetMob(m_pOwner, dwPetVnum);
#endif
#else
	const DWORD dwPetVnum = dwPetEvol < PET_EVOLUTION_4 ? pSummonItem->GetValue(0) : pSummonItem->GetValue(3);
#endif


// LPGROWTH_PET CGrowthPet::Summon(LPITEM pSummonItem, bool bIsResummon) icinde:
// Ara:
		return NULL;
	}
	m_pGrowthPet->SetEmpire(m_pOwner->GetEmpire());

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	m_pGrowthPet->SetCharType(CHAR_TYPE_GROWTH_PET);
#endif


// LPGROWTH_PET CGrowthPet::Summon(LPITEM pSummonItem, bool bIsResummon) icinde:
// Ara:
	pSummonItem->Lock(true);
	RefreshAffect();
	m_pGrowthPet->Show(m_pOwner->GetMapIndex(), x, y, z);

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	RefreshSkillSlots(true);	// old pets past level 90 get their slots
#endif


// LPGROWTH_PET CGrowthPet::Summon(LPITEM pSummonItem, bool bIsResummon) icinde:
// Ara:
	}
	if (!bIsResummon)
	{

// Altina ekle:
#ifndef ENABLE_GROWTH_PET_RENEWAL
		m_pOwner->LocaleChatPacket(CHAT_TYPE_INFO, 746, "%s", m_strName.c_str());
#endif


// void CGrowthPet::Unsummon() icinde:
// Ara:
			packet.header = HEADER_GC_PET;
			packet.subheader = SUBHEADER_PET_UNSUMMON;
			m_pOwner->GetDesc()->Packet(&packet, sizeof(packet));

// Altina ekle:
#ifndef ENABLE_GROWTH_PET_RENEWAL
			m_pOwner->LocaleChatPacket(CHAT_TYPE_INFO, 747, "%s", m_strName.c_str());
#endif


// void CGrowthPet::SetGrowthPetProto(TGrowthPet* pGrowthPetTable) icinde:
// Ara:
	SetPetPoint(POINT_UPBRINGING_DURATION, pGrowthPetTable->lEndTime);
	SetPetPoint(POINT_UPBRINGING_MAX_DURATION, pGrowthPetTable->lMaxTime);
	SetPetPoint(POINT_UPBRINGING_BIRTHDAY, pGrowthPetTable->lBirthday);

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	SetPetPoint(POINT_UPBRINGING_PET_TYPE, pGrowthPetTable->bType);
#endif


// void CGrowthPet::ChangePetPoint(BYTE bIdx, int iVal, bool bAmount, bool bPacket) icinde:
// Ara:
		case POINT_UPBRINGING_DURATION:
		case POINT_UPBRINGING_MAX_DURATION:
		case POINT_UPBRINGING_BIRTHDAY:

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
		case POINT_UPBRINGING_PET_TYPE:
#endif


// bool CGrowthPet::CanReceiveEXP() icinde:
// Ara:
		return false;
	if (dwLevel > m_pOwner->GetLevel())
		return false;

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	return dwLevel < PetEvolutionLevelCap(bEvolution) || (dwLevel == PetEvolutionLevelCap(bEvolution) && bEvolution >= PET_EVOLUTION_4);
#endif


// BYTE CGrowthPet::CanLevelUp() icinde:
// Ara:
		return LEVELUP_ERROR_MAX_LEVEL;
	if (dwLevel == m_pOwner->GetLevel())
		return LEVELUP_ERROR_OWNER_LEVEL;

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	if (bEvolution < PET_EVOLUTION_4 && dwLevel >= PetEvolutionLevelCap(bEvolution))
		return LEVELUP_ERROR_EVOLUTION;
	return LEVELUP_ERROR_NONE;
#endif


// bool CGrowthPet::LevelUp() icinde:
// Ara:
		ChangePetPoint(POINT_UPBRINGING_PET_ITEM_EXP, 0, true);
		ChangePetPoint(POINT_UPBRINGING_PET_LEVEL, 1);
		IncreaseBattlePoints(dwPetLevel + 1);

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
		RefreshSkillSlots();
#endif


// void CGrowthPet::RefreshAffect() icinde:
// Bul:
	DWORD dwPointType[3] = { POINT_MAX_HP , POINT_MAX_SP, POINT_DEF_GRADE };
	DWORD dwPetPointType[3] = { POINT_UPBRINGING_PET_HP, POINT_UPBRINGING_PET_SP, POINT_UPBRINGING_PET_DEF_GRADE };

	for (int i = 0; i < 3; ++i)
	{
		DWORD dwPlayerPoint = 0;
		switch (dwPointType[i])
		{
			case POINT_MAX_HP:
			case POINT_MAX_SP:
				dwPlayerPoint = m_pOwner->GetRealPoint(dwPointType[i]);
				break;

			default:
				dwPlayerPoint = m_pOwner->GetPoint(dwPointType[i]);
				break;
		}

		float fFactor = float(GetPetPoint(dwPetPointType[i]));
		fFactor /= 10;

		dwPlayerPoint = (dwPlayerPoint / 100.0f) * fFactor;

		m_pOwner->AddAffect(AFFECT_GROWTH_PET, dwPointType[i], dwPlayerPoint, AFF_NONE, INFINITE_AFFECT_DURATION, 0, true, true);
	}

// Degistir:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	// SP slot -> attack against monsters + players %, DEF slot -> elemental power %.
	// Those two are whole percent points, so 0.1 % steps work once they reach 1 %.
	{
		const float fHP = float(GetPetPoint(POINT_UPBRINGING_PET_HP)) / 10.0f;
		const DWORD dwHP = DWORD((m_pOwner->GetRealPoint(POINT_MAX_HP) / 100.0f) * fHP);
		m_pOwner->AddAffect(AFFECT_GROWTH_PET, POINT_MAX_HP, dwHP, AFF_NONE, INFINITE_AFFECT_DURATION, 0, true, true);

		const int iAttack = int(GetPetPoint(POINT_UPBRINGING_PET_SP) / 10);
		m_pOwner->AddAffect(AFFECT_GROWTH_PET, POINT_ATTBONUS_MONSTER, iAttack, AFF_NONE, INFINITE_AFFECT_DURATION, 0, true, true);
		m_pOwner->AddAffect(AFFECT_GROWTH_PET, POINT_ATTBONUS_HUMAN, iAttack, AFF_NONE, INFINITE_AFFECT_DURATION, 0, true, true);

		const int iElement = int(GetPetPoint(POINT_UPBRINGING_PET_DEF_GRADE) / 10);
		m_pOwner->AddAffect(AFFECT_GROWTH_PET, POINT_ATTBONUS_ELEMENTS, iElement, AFF_NONE, INFINITE_AFFECT_DURATION, 0, true, true);
	}
#else
	DWORD dwPointType[3] = { POINT_MAX_HP , POINT_MAX_SP, POINT_DEF_GRADE };
	DWORD dwPetPointType[3] = { POINT_UPBRINGING_PET_HP, POINT_UPBRINGING_PET_SP, POINT_UPBRINGING_PET_DEF_GRADE };

	for (int i = 0; i < 3; ++i)
	{
		DWORD dwPlayerPoint = 0;
		switch (dwPointType[i])
		{
			case POINT_MAX_HP:
			case POINT_MAX_SP:
				dwPlayerPoint = m_pOwner->GetRealPoint(dwPointType[i]);
				break;

			default:
				dwPlayerPoint = m_pOwner->GetPoint(dwPointType[i]);
				break;
		}

		float fFactor = float(GetPetPoint(dwPetPointType[i]));
		fFactor /= 10;

		dwPlayerPoint = (dwPlayerPoint / 100.0f) * fFactor;

		m_pOwner->AddAffect(AFFECT_GROWTH_PET, dwPointType[i], dwPlayerPoint, AFF_NONE, INFINITE_AFFECT_DURATION, 0, true, true);
	}
#endif


// void CGrowthPet::IncreaseBattlePoints(DWORD dwLevel, bool bAttrChange) icinde:
// Ara:
{
	if (!m_pSummonItem || !m_pOwner)
		return;

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	return;
#endif


// Ara:
	if(!bAttrChange)
		RefreshAffect();
}

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
#include "cmd.h"

void CGrowthPet::RefreshLook(LPITEM pExcludeCostume)
{
	if (!m_pOwner || !m_pGrowthPet || !m_pSummonItem)
		return;
	LPITEM pSeal = m_pSummonItem;
	m_pLookExclude = pExcludeCostume;
	Summon(pSeal, true);
	m_pLookExclude = nullptr;
	pSeal->Lock(false);
}

// (uiCompanion.REFINE_TYPE_REQUIREMENTS, wiki systems/pet.txt). Key = current type.
static const struct SPetTypeUpgrade
{
	DWORD dwVnum[3];
	DWORD dwCount[3];
	long long llGold;
} s_aPetTypeUpgrade[PET_TYPE_MAX - 1] =
{
	{ { 40214, 50628, 27987 }, {  5, 10, 25 },  10000000LL },
	{ { 40214, 50632, 40718 }, { 10, 10,  5 },  50000000LL },
	{ { 40214, 50634, 40718 }, { 15, 10, 10 }, 100000000LL },
	{ { 40214, 50635, 40718 }, { 20, 10, 15 }, 250000000LL },
	{ { 40214, 50602, 40718 }, { 25,  5, 20 }, 500000000LL },
};

static const struct SPetEvolveLevel
{
	DWORD dwLevel;
	DWORD dwVnum[5];
	DWORD dwCount[5];
	long long llGold;
} s_aPetEvolveLevels[3] =
{
	{ 55, { 55005, 40214, 40812, 40912, 40914 }, { 10, 10, 10,  5, 10 },  25000000LL },
	{ 75, { 55006, 40214, 40718, 40942, 40820 }, { 10, 15, 10,  5, 10 }, 100000000LL },
	{ 90, { 55007, 40214, 40718, 40919, 40920 }, { 10, 20, 25, 10, 10 }, 500000000LL },
};

static DWORD PetEvolutionLevelCap(DWORD dwEvolution)
{
	if (dwEvolution >= PET_EVOLUTION_4)
		return PET_MAX_LEVEL;
	return s_aPetEvolveLevels[MAX(1, dwEvolution) - 1].dwLevel;
}

enum { PET_EVOLVE_NO_PET, PET_EVOLVE_MAX, PET_EVOLVE_LEVEL, PET_EVOLVE_ITEM, PET_EVOLVE_GOLD, PET_EVOLVE_SUCCESS };
// PetSkillSlotResult codes
enum { PET_SLOT_NO_PET, PET_SLOT_LEVEL, PET_SLOT_FIRST, PET_SLOT_MAX, PET_SLOT_SUCCESS };

void CGrowthPet::EvolveAnka()
{
	if (!m_pOwner || !m_pSummonItem)
		return;

	const DWORD dwEvolution = GetPetPoint(POINT_UPBRINGING_PET_EVOL_LEVEL);
	if (dwEvolution >= PET_EVOLUTION_4)
	{
		m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetEvolveResult %d 0", PET_EVOLVE_MAX);
		return;
	}

	const SPetEvolveLevel& r = s_aPetEvolveLevels[MAX(1, dwEvolution) - 1];
	if (GetPetPoint(POINT_UPBRINGING_PET_LEVEL) < r.dwLevel)
	{
		m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetEvolveResult %d %u", PET_EVOLVE_LEVEL, r.dwLevel);
		return;
	}

	for (int i = 0; i < 5; ++i)
	{
		if (m_pOwner->CountSpecifyItem(r.dwVnum[i]) < (int) r.dwCount[i])
		{
			m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetEvolveResult %d 0", PET_EVOLVE_ITEM);
			return;
		}
	}

	if ((long long) m_pOwner->GetGold() < r.llGold)
	{
		m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetEvolveResult %d 0", PET_EVOLVE_GOLD);
		return;
	}

	for (int i = 0; i < 5; ++i)
		m_pOwner->RemoveSpecifyItem(r.dwVnum[i], r.dwCount[i]);
	m_pOwner->PointChange(POINT_GOLD, -r.llGold);

	ChangePetPoint(POINT_UPBRINGING_PET_EVOL_LEVEL, 1);
	LPITEM pSeal = m_pSummonItem;
	Summon(pSeal, true);
	pSeal->Lock(false);
	RefreshSkillSlots();
	Save();
	m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetEvolveResult %d %u", PET_EVOLVE_SUCCESS, GetPetPoint(POINT_UPBRINGING_PET_EVOL_LEVEL));
}

void CGrowthPet::RefreshSkillSlots(bool bPacket)
{
	if (GetPetPoint(POINT_UPBRINGING_PET_LEVEL) < PET_AUTO_UNLOCK_SKILL_LEVEL)
		return;

	bool bChanged = false;
	for (int i = 0; i < 3 && i < PET_SKILL_COUNT_MAX; ++i)
	{
		if (m_aSkill[i].bLocked)
		{
			m_aSkill[i].bLocked = false;
			bChanged = true;
		}
	}

	if (bChanged)
	{
		Save();
		if (bPacket)
			UpdateSkillPacket();
	}
}

// Pet Kilit Acici: one more slot (4-6) from pet level 105
bool CGrowthPet::UnlockSkillSlot()
{
	if (!m_pOwner)
		return false;

	if (GetPetPoint(POINT_UPBRINGING_PET_LEVEL) < PET_UNLOCK_ITEM_LEVEL)
	{
		m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkillSlotResult %d %d", PET_SLOT_LEVEL, PET_UNLOCK_ITEM_LEVEL);
		return false;
	}

	for (int i = 0; i < 3; ++i)
	{
		if (m_aSkill[i].bLocked)
		{
			m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkillSlotResult %d 0", PET_SLOT_FIRST);
			return false;
		}
	}

	for (int i = 3; i < PET_SKILL_COUNT_MAX; ++i)
	{
		if (m_aSkill[i].bLocked)
		{
			m_aSkill[i].bLocked = false;
			Save();
			UpdateSkillPacket();
			m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkillSlotResult %d %d", PET_SLOT_SUCCESS, i + 1);
			return true;
		}
	}

	m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetSkillSlotResult %d 0", PET_SLOT_MAX);
	return false;
}

bool CGrowthPet::ExtendLifetime(LPITEM pItem)
{
	if (!m_pOwner || !m_pSummonItem || !pItem)
		return false;

	const DWORD dwDay = 3600 * 24;
	const DWORD dwMax = GetPetPoint(POINT_UPBRINGING_MAX_DURATION);
	if (dwMax + dwDay > PET_LIFETIME_MAX_DAYS * dwDay)
	{
		m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetMessage 4 %d", (int) PET_LIFETIME_MAX_DAYS);
		return false;
	}

	const DWORD dwEnd = MAX((DWORD) GetPetPoint(POINT_UPBRINGING_DURATION), (DWORD) time(0)) + dwDay;
	ChangePetPoint(POINT_UPBRINGING_MAX_DURATION, dwMax + dwDay, true);
	ChangePetPoint(POINT_UPBRINGING_DURATION, dwEnd, true);
	m_pSummonItem->SetSocket(0, dwEnd);
	m_pSummonItem->SetSocket(1, dwMax + dwDay);
	pItem->SetCount(pItem->GetCount() - 1);
	Save();
	m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetMessage 5 %u", (dwMax + dwDay) / dwDay);
	return true;
}

// /pet_evolve (Yoldas "Evrim" window)
ACMD(do_pet_evolve)
{
	LPGROWTH_PET pPet = ch->GetActiveGrowthPet();
	if (!pPet)
	{
		ch->ChatPacket(CHAT_TYPE_COMMAND, "PetEvolveResult %d 0", PET_EVOLVE_NO_PET);
		return;
	}
	if (ch->IsDead() || ch->GetExchange() || ch->GetMyShop() || ch->GetShopOwner() || ch->IsOpenSafebox() || ch->IsCubeOpen())
		return;
	pPet->EvolveAnka();
}

enum { PET_POTION_NO_PET, PET_POTION_TYPE, PET_POTION_MAX, PET_POTION_FAIL, PET_POTION_SUCCESS };
// PetTypeUpgradeResult codes
enum { PET_TYPE_UP_INFO, PET_TYPE_UP_NO_PET, PET_TYPE_UP_MAX, PET_TYPE_UP_ITEM, PET_TYPE_UP_GOLD, PET_TYPE_UP_FAIL, PET_TYPE_UP_SUCCESS };

static std::string PetTypePityFlag(DWORD dwPetID)
{
	char szFlag[64];
	snprintf(szFlag, sizeof(szFlag), "pet_type_pity.p%u", dwPetID);
	return szFlag;
}

bool CGrowthPet::UseBonusPotion(LPITEM pPotion)
{
	if (!m_pOwner || !pPotion)
		return false;

	BYTE bPoint;
	switch (pPotion->GetSubType())
	{
		case PET_HP_POTION:			bPoint = POINT_UPBRINGING_PET_HP; break;
		case PET_ATTACK_POTION:		bPoint = POINT_UPBRINGING_PET_SP; break;		// SP slot = Saldiri PvM / PvP
		case PET_ELEMENTAL_POTION:	bPoint = POINT_UPBRINGING_PET_DEF_GRADE; break;	// DEF slot = Elemental Power
		default: return false;
	}

	const long lReqType = pPotion->GetValue(0);
	const long lMax = pPotion->GetValue(1);
	const long lChance = pPotion->GetValue(2);
	const long lAdd = MAX(1, pPotion->GetValue(3));

	if (m_bType < lReqType)
	{
		m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetPotionResult %d %ld", PET_POTION_TYPE, lReqType);
		return false;
	}

	const long lCur = GetPetPoint(bPoint);
	if (lCur >= lMax)
	{
		m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetPotionResult %d %ld", PET_POTION_MAX, lMax);
		return false;
	}

	pPotion->SetCount(pPotion->GetCount() - 1);

	if (number(1, 100) > lChance)
	{
		m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetPotionResult %d %ld", PET_POTION_FAIL, lCur);
		return true;
	}

	ChangePetPoint(bPoint, MIN(lAdd, lMax - lCur));
	RefreshAffect();
	Save();
	m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetPotionResult %d %u", PET_POTION_SUCCESS, GetPetPoint(bPoint));
	return true;
}

void CGrowthPet::UpgradeType(bool bInfoOnly)
{
	if (!m_pOwner)
		return;

	const std::string stFlag = PetTypePityFlag(m_dwID);
	int iPity = m_pOwner->GetQuestFlag(stFlag);

	if (bInfoOnly)
	{
		m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetTypeUpgradeResult %d %d %d", PET_TYPE_UP_INFO, iPity, PET_TYPE_PITY_MAX);
		return;
	}

	if (m_bType >= PET_TYPE_MAX)
	{
		m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetTypeUpgradeResult %d %d %d", PET_TYPE_UP_MAX, iPity, PET_TYPE_PITY_MAX);
		return;
	}

	const SPetTypeUpgrade& r = s_aPetTypeUpgrade[MAX(1, m_bType) - 1];
	for (int i = 0; i < 3; ++i)
	{
		if (m_pOwner->CountSpecifyItem(r.dwVnum[i]) < (int) r.dwCount[i])
		{
			m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetTypeUpgradeResult %d %d %d", PET_TYPE_UP_ITEM, iPity, PET_TYPE_PITY_MAX);
			return;
		}
	}

	if ((long long) m_pOwner->GetGold() < r.llGold)
	{
		m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetTypeUpgradeResult %d %d %d", PET_TYPE_UP_GOLD, iPity, PET_TYPE_PITY_MAX);
		return;
	}

	for (int i = 0; i < 3; ++i)
		m_pOwner->RemoveSpecifyItem(r.dwVnum[i], r.dwCount[i]);
	m_pOwner->PointChange(POINT_GOLD, -r.llGold);

	if (iPity < PET_TYPE_PITY_MAX && number(1, 100) > PET_TYPE_UPGRADE_CHANCE)
	{
		m_pOwner->SetQuestFlag(stFlag, ++iPity);
		m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetTypeUpgradeResult %d %d %d", PET_TYPE_UP_FAIL, iPity, PET_TYPE_PITY_MAX);
		return;
	}

	++m_bType;
	ChangePetPoint(POINT_UPBRINGING_PET_TYPE, m_bType, true);
	Save();
	m_pOwner->SetQuestFlag(stFlag, 0);
	m_pOwner->ChatPacket(CHAT_TYPE_COMMAND, "PetTypeUpgradeResult %d %d %d", PET_TYPE_UP_SUCCESS, 0, PET_TYPE_PITY_MAX);
}

// /pet_upgrade_type [info]  (Yoldas "Gelistirme Turu" window)
ACMD(do_pet_upgrade_type)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	LPGROWTH_PET pPet = ch->GetActiveGrowthPet();
	if (!pPet)
	{
		ch->ChatPacket(CHAT_TYPE_COMMAND, "PetTypeUpgradeResult %d %d %d", PET_TYPE_UP_NO_PET, 0, PET_TYPE_PITY_MAX);
		return;
	}

	if (ch->IsDead() || ch->GetExchange() || ch->GetMyShop() || ch->GetShopOwner() || ch->IsOpenSafebox() || ch->IsCubeOpen())
		return;

	pPet->UpgradeType(!strcmp(arg1, "info"));
}
#endif


// void CGrowthPet::AttrChange(LPITEM pSummonItem, LPITEM pAttrChangeItem) icinde:
// Ara:
		|| (pSummonItem->GetVnum() == PET_SPIDER) 
		|| (pSummonItem->GetVnum() == PET_AZRAEL) ? 6 : 8;
	m_bType = number(1, bMaxType);

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	ChangePetPoint(POINT_UPBRINGING_PET_TYPE, m_bType, true);
#endif


// void CGrowthPet::LearnSkill(BYTE bSlot, LPITEM pSkillBookItem) icinde:
// Ara:
}
void CGrowthPet::LearnSkill(BYTE bSlot, LPITEM pSkillBookItem)
{

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	if (bSlot >= PET_SKILL_COUNT_MAX || m_aSkill[bSlot].bLocked)
		return;
#endif


// void CGrowthPet::LearnSkill(BYTE bSlot, LPITEM pSkillBookItem) icinde:
// Ara:
	if (!m_pOwner)
		return;

// Altina ekle:
#ifndef ENABLE_GROWTH_PET_RENEWAL
	if (GetPetPoint(POINT_UPBRINGING_PET_EVOL_LEVEL) < PET_GROWTH_SKILL_OPEN_EVOL_LEVEL)
		return;
#endif


// void CGrowthPetManager::GenerateGrowthPetProto(LPCHARACTER ch, TGrowthPet* pGrowthPetTable, LPITEM pEggItem, const char* c_szName) icinde:
// Ara:
	BYTE bSkillCount = number(1, hatchTable.bMaxSKillCount);
	if (dwUpBringingVnum == PET_EXEDYAR)
		bSkillCount = 3;

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	bSkillCount = 0;
#endif


// void CGrowthPetManager::GenerateGrowthPetProto(LPCHARACTER ch, TGrowthPet* pGrowthPetTable, LPITEM pEggItem, const char* c_szName) icinde:
// Ara:
	dwHP = number(1, 23);
	dwSP = number(1, 19);
	dwDef = number(1, 21);

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	bPetType = 1;
	dwHP = dwSP = dwDef = 1;
	dwHPApply = dwSPApply = dwDefApply = 0;
	petDuration = PET_HATCH_DURATION_DAYS * (3600 * 24);
#endif

