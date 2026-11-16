// Dosyanin uygun bir yerine ekle:
#ifdef ENABLE_BUFFI_SYSTEM
#include "buffi_system.h"
#endif


// void CHARACTER::Destroy() icinde:
// Ara:
}
void CHARACTER::Destroy()
{

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
	CBuffiManager::instance().OnDestroy(this);
#endif


// void CHARACTER::EncodeInsertPacket(LPENTITY entity) icinde:
// Ara:
			addPacket.dwLevel = GetLevel();
			addPacket.bCharacterSize = GetCharacterSize();
		}

// Altina ekle:
#ifdef ENABLE_MOUNT_FOLLOWER_LEVEL
		if (GetCharType() == CHAR_TYPE_MOUNT)
			addPacket.dwLevel = GetLevel();
#endif
#ifdef ENABLE_BUFFI_SYSTEM
		if (GetRaceNum() == BUFFI_NPC_FEMALE || GetRaceNum() == BUFFI_NPC_MALE)
			addPacket.dwLevel = GetLevel();
#endif


// void CHARACTER::ApplyPoint (WORD bApplyType, int iVal) icinde:
// Ara:
				PointChange (aApplyInfo[bApplyType].bPointType, iVal);
			}
			break;

// Altina ekle:
#ifdef ENABLE_PET_EXP_BONUS
		case APPLY_PET_EXP_BONUS:
			break;
#endif


// void CHARACTER::EquipCostumePetSkin() icinde:
// Ara:
}
void CHARACTER::EquipCostumePetSkin()
{

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	// Anka: a pet costume is only the look of the Yoldas pet; no old pet system, no change cooldown (swap at once)
	if (m_activeGrowthPet)
		m_activeGrowthPet->RefreshLook(NULL);
	return;
#endif


// void CHARACTER::RemoveCostumePetSkin(LPITEM petSkin) icinde:
// Ara:
}
void CHARACTER::RemoveCostumePetSkin(LPITEM petSkin)
{

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	if (m_activeGrowthPet)
		m_activeGrowthPet->RefreshLook(petSkin);
	return;
#endif


// Ara:
	}
	ChatPacket(CHAT_TYPE_COMMAND, "RenewalSkillSelectWindow %s", job);
}

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
void CHARACTER::SummonEquippedGrowthPet()
{
	if (m_activeGrowthPet || !IsGrowthPetLoaded() || !GetDesc() || !GetDesc()->IsPhase(PHASE_GAME))
		return;
	if (GetMapIndex() == 113 || CArenaManager::instance().IsArenaMap(GetMapIndex()))
		return;
	LPITEM pSeal = GetWear(WEAR_GROWTH_PET);
	if (!pSeal || pSeal->GetType() != ITEM_GROWTH_PET || pSeal->GetSubType() != PET_UPBRINGING)
		return;
	LPGROWTH_PET pPet = GetGrowthPet(pSeal->GetSocket(2));
	if (!pPet)
		return;
	m_activeGrowthPet = pPet->Summon(pSeal);
	pSeal->Lock(false);
}
#endif

