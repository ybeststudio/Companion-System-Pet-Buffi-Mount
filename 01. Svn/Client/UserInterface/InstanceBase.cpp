// bool CInstanceBase::Create(const SCreateData& c_rkCreateData) icinde:
// Ara:
		const auto mount = nonPlayer.GetNPCWear(c_rkCreateData.m_dwRace, NPC_WEAR_MOUNT);
		if (mount != 0)
			MountHorse(mount);

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
		const bool isBuffi = c_rkCreateData.m_dwRace == 34900 || c_rkCreateData.m_dwRace == 34901;
		if (isBuffi)
		{
			SetArmor(c_rkCreateData.m_dwArmor ? c_rkCreateData.m_dwArmor : nonPlayer.GetNPCWear(c_rkCreateData.m_dwRace, NPC_WEAR_ARMOR));
			SetWeapon(c_rkCreateData.m_dwWeapon ? c_rkCreateData.m_dwWeapon : nonPlayer.GetNPCWear(c_rkCreateData.m_dwRace, NPC_WEAR_WEAPON));
			SetHair(c_rkCreateData.m_dwHair);
#ifdef ENABLE_ACCE_COSTUME_SYSTEM
			SetAcce(c_rkCreateData.m_dwAcce);
#endif
#ifdef ENABLE_SKILL_COLOR_SYSTEM
			ChangeSkillColor(*c_rkCreateData.m_dwSkillColor);
			memcpy(m_dwSkillColor, *c_rkCreateData.m_dwSkillColor, sizeof(m_dwSkillColor));
#endif
		}
		else
#endif


// void CInstanceBase::ChangeHair(DWORD eHair) icinde:
// Bul:
	if (IsPC() == false)

// Degistir:
#ifdef ENABLE_BUFFI_SYSTEM
	if (IsPC() == false && GetVirtualNumber() != 34900 && GetVirtualNumber() != 34901)
#else
	if (IsPC() == false)
#endif


// void CInstanceBase::ChangeAcce(DWORD dwAcce) icinde:
// Bul:
	if (!IsPC())

// Degistir:
#ifdef ENABLE_BUFFI_SYSTEM
	if (!IsPC() && GetVirtualNumber() != 34900 && GetVirtualNumber() != 34901)
#else
	if (!IsPC())
#endif

