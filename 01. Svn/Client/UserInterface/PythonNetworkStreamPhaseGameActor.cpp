// bool CPythonNetworkStream::RecvCharacterAdditionalInfo() icinde:
// Ara:
				case CActorInstance::TYPE_PET:

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
					if (kNetActorData.m_dwRace == 34900 || kNetActorData.m_dwRace == 34901)
					{
						kNetActorData.m_stName = chrInfoPacket.name;
						break;
					}
#endif


// bool CPythonNetworkStream::RecvCharacterAdditionalInfo() icinde:
// Bul:
					char szMountName[1024];
					snprintf(szMountName, sizeof(szMountName), "%s - %s", chrInfoPacket.name, c_szName);
					kNetActorData.m_stName = szMountName;
					break;

// Degistir:
#ifdef ENABLE_MOUNT_FOLLOWER_LEVEL
					kNetActorData.m_stName = chrInfoPacket.name;
					break;
#else
					char szMountName[1024];
					snprintf(szMountName, sizeof(szMountName), "%s - %s", chrInfoPacket.name, c_szName);
					kNetActorData.m_stName = szMountName;
					break;
#endif


// Ara:
	}
	return true;
}

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
bool CPythonNetworkStream::RecvBuffiUseSkill()
{
	TPacketGCBuffiUseSkill packet;
	if (!Recv(sizeof(TPacketGCBuffiUseSkill), &packet))
		return false;

	CInstanceBase* pInstance = CPythonCharacterManager::Instance().GetInstancePtr(packet.dwVID);
	if (!pInstance)
		return true;

	CPythonSkill::TSkillData* pSkillData;
	if (!CPythonSkill::Instance().GetSkillData(packet.dwSkillVnum, &pSkillData))
		return true;

	int iGrade = 0;
	if (packet.bSkillLevel >= 40)
		iGrade = 3;
	else if (packet.bSkillLevel >= 30)
		iGrade = 2;
	else if (packet.bSkillLevel >= 20)
		iGrade = 1;

	pInstance->NEW_UseSkill(packet.dwSkillVnum, pSkillData->GetSkillMotionIndex(iGrade), 1, false);
	return true;
}
#endif

