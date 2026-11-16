// Ara:
 * Version   : 1.0.0
 * Date      : 02-11-2026  
 */

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
#include "growth_pet.h"
#endif


// Ara:
		LPITEM pPet = (looks[WARDROBE_LOOK_PET] != d.looks[WARDROBE_LOOK_PET]) ? ch->GetWear(WEAR_PET) : NULL;
		if (pPet)
			ch->PetUnsummon(pPet);

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
		const bool bPetLookChanged = looks[WARDROBE_LOOK_PET] != d.looks[WARDROBE_LOOK_PET];
#endif


// Ara:
		if (pPet)
			ch->PetSummon(pPet);

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
		if (bPetLookChanged && ch->GetActiveGrowthPet())
			ch->GetActiveGrowthPet()->RefreshLook(NULL);
#endif

