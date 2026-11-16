// const D3DXCOLOR& CInstanceBase::GetNameColor() icinde:
// Ara:
}
const D3DXCOLOR& CInstanceBase::GetNameColor()
{

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	static const D3DXCOLOR s_kBuffiNameColor(1.0f, 1.0f, 1.0f, 1.0f);
	static const D3DXCOLOR s_kPetNameColor(122.0f / 255.0f, 231.0f / 255.0f, 93.0f / 255.0f, 1.0f);
	if (GetVirtualNumber() == 34900 || GetVirtualNumber() == 34901)
		return s_kBuffiNameColor;
	if (IsGrowthPet())
		return s_kPetNameColor;
#endif


// UINT CInstanceBase::GetNameColorIndex() icinde:
// Ara:
}
UINT CInstanceBase::GetNameColorIndex()
{

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
	if (GetVirtualNumber() == 34900 || GetVirtualNumber() == 34901)
		return NAMECOLOR_PC + GetEmpireID();
#endif


// void CInstanceBase::UpdateTextTailLevel(DWORD level) icinde:
// Bul:
	static D3DXCOLOR s_kPetColor = D3DXCOLOR(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, 1.0f);

// Degistir:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	static D3DXCOLOR s_kPetColor = D3DXCOLOR(218.0f / 255.0f, 112.0f / 255.0f, 214.0f / 255.0f, 1.0f);
#else
	static D3DXCOLOR s_kPetColor = D3DXCOLOR(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, 1.0f);
#endif


// void CInstanceBase::UpdateTextTailLevel(DWORD level) icinde:
// Ara:
	m_dwLevel = level;
	char szText[256];
	snprintf(szText, sizeof(szText), "Lv %d", level);

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
	if (GetVirtualNumber() == 34900 || GetVirtualNumber() == 34901)
	{
#ifdef ENABLE_GROWTH_PET_RENEWAL
		static D3DXCOLOR s_kBuffiLevelColor = D3DXCOLOR(218.0f/255.0f, 112.0f/255.0f, 214.0f/255.0f, 1.0f);
#else
		static D3DXCOLOR s_kBuffiLevelColor = D3DXCOLOR(204.0f/255.0f, 102.0f/255.0f, 255.0f/255.0f, 1.0f);
#endif
		CPythonTextTail::Instance().AttachLevel(GetVirtualID(), szText, s_kBuffiLevelColor);
		return;
	}
#endif


// void CInstanceBase::UpdateTextTailLevel(DWORD level) icinde:
// Ara:
	else if (IsGrowthPet())
		CPythonTextTail::Instance().AttachLevel(GetVirtualID(), szText, s_kPetColor);

// Altina ekle:
#ifdef ENABLE_MOUNT_FOLLOWER_LEVEL
	else if (IsMount())
		CPythonTextTail::Instance().AttachLevel(GetVirtualID(), szText, s_kPetColor);
#endif

