// Ara:
		void IncreaseBattlePoints(DWORD dwLevel, bool bAttrChange = false);
		void RefreshAffect();
		void ClearAffect();

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
		bool UseBonusPotion(LPITEM pPotion);
		void UpgradeType(bool bInfoOnly);
		void SetPetType(BYTE bType) { m_bType = bType; }
		void RefreshLook(LPITEM pExcludeCostume);
		void EvolveAnka();
		void RefreshSkillSlots(bool bPacket = true);
		bool UnlockSkillSlot();
		bool ExtendLifetime(LPITEM pItem);
	private:
		LPITEM m_pLookExclude = nullptr;
	public:
#endif


// Ara:
		bool m_bMobExpMsg;
		bool m_bItemExpMsg;
};

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
enum
{
	PET_TYPE_MAX = 6,
	PET_TYPE_PITY_MAX = 3,			// "%100 sans oncesi basarisizlik: x / 3"
	PET_TYPE_UPGRADE_CHANCE = 50,
	PET_HATCH_DURATION_DAYS = 7,
	PET_AUTO_UNLOCK_SKILL_LEVEL = 90,	// uiCompanion.PET_AUTO_UNLOCK_SKILL_LEVEL: slots 1-3
	PET_UNLOCK_ITEM_LEVEL = 105,
	PET_SKILL_UNLOCK_ITEM_VNUM = 55029,
	PET_LIFETIME_ITEM_VNUM = 55028,
	PET_LIFETIME_MAX_DAYS = 30,
};
#endif

