// void CInputDB::GrowthPetLoad(LPDESC d, const char* c_pData) icinde:
// Ara:
		}
	}
	ch->SetGrowthPetLoaded(true);

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	ch->SummonEquippedGrowthPet();
#endif

