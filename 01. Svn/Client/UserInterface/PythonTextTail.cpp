// void CPythonTextTail::RegisterCharacterTextTail(DWORD dwGuildID, DWORD dwVirtualID, const D3DXCOLOR & c_rColor, float fAddHeight) icinde:
// Ara:
	if (pInstance)
	{
		if (pInstance->IsGameMaster() && pInstance != pCharacterInstance && !pCharacterInstance->IsPC()

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
			&& pCharacterInstance->GetVirtualNumber() != 34900 && pCharacterInstance->GetVirtualNumber() != 34901
#endif
#ifdef ENABLE_GROWTH_PET_RENEWAL
			&& !pCharacterInstance->IsGrowthPet()
#endif


// void CPythonTextTail::RegisterCharacterTextTail(DWORD dwGuildID, DWORD dwVirtualID, const D3DXCOLOR & c_rColor, float fAddHeight) icinde:
// Ara:
		prAIFlagInstance->Update();
	}
	pTextTail->bIsPC = pCharacterInstance->IsPC() != FALSE;

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
	if (pCharacterInstance->GetVirtualNumber() == 34900 || pCharacterInstance->GetVirtualNumber() == 34901)
		pTextTail->bIsPC = TRUE;
#endif
#ifdef ENABLE_GROWTH_PET_RENEWAL
	if (pCharacterInstance->IsGrowthPet())
		pTextTail->bIsPC = TRUE;
#endif
#ifdef ENABLE_MOUNT_FOLLOWER_LEVEL
	if (pCharacterInstance->IsMount())
		pTextTail->bIsPC = TRUE;
#endif

