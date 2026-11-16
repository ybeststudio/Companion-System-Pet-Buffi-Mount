// Dosyanin uygun bir yerine ekle:
#ifdef ENABLE_BUFFI_SYSTEM
#include "buffi_system.h"
#endif


// bool CHARACTER::Damage(LPCHARACTER pAttacker, int dam, EDamageType type) icinde:
// Ara:
		float damMul = this->GetDamMul();
		float tempDam = dam;
		dam = tempDam * damMul + 0.5f;

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
		CBuffiManager::instance().OnOwnerAttack(pAttacker, this);
		if (dam > 1 && IsPC() && pAttacker->IsPC() && pAttacker != this && CBuffiManager::instance().IsSummoned(pAttacker))
			dam = 1;
#endif


// static void GiveExp(LPCHARACTER from, LPCHARACTER to, int iExp) icinde:
// Ara:
	iExp = CALCULATE_VALUE_LVDELTA(to->GetLevel(), from->GetLevel(), iExp);

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
	CBuffiManager::instance().OnOwnerGainExp(to, iExp);
#endif


// static void GiveExp(LPCHARACTER from, LPCHARACTER to, int iExp) icinde:
// Ara:
	if (to->GetActiveGrowthPet())
	{

// Altina ekle:
#ifdef ENABLE_PET_EXP_BONUS
		int iPetExpBonus = 0;
		for (int iWear : { (int) WEAR_PET, (int) WEAR_COSTUME_PET })
		{
			LPITEM pPetItem = to->GetWear(iWear);
			if (!pPetItem)
				continue;
			for (int i = 0; i < ITEM_APPLY_MAX_NUM; ++i)
				if (pPetItem->GetProto()->aApplies[i].bType == APPLY_PET_EXP_BONUS)
					iPetExpBonus += pPetItem->GetProto()->aApplies[i].lValue;
		}
		if (iPetExpBonus > 0)
			iBaseExp += iBaseExp * iPetExpBonus / 100;
#endif

