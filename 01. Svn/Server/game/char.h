// Ara:
		LPGROWTH_PET GetGrowthPet(DWORD dwID);
		void ClearGrowthPet();
		void SetActiveGrowthPet(LPGROWTH_PET pkPet) { m_activeGrowthPet = pkPet;  }

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
		void SummonEquippedGrowthPet();
#endif

