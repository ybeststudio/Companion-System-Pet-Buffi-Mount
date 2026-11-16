// Dosyanin uygun bir yerine ekle:
#ifdef ENABLE_MOUNT_FOLLOWER_LEVEL
#include "locale_service.h"
#include "mount_renewal.h"
#endif


// void CMountActor::SetName() icinde:
// Bul:
		snprintf(buf, sizeof(buf), "%s", m_pkOwner->GetName());

// Degistir:
#ifdef ENABLE_MOUNT_FOLLOWER_LEVEL
#ifdef ENABLE_MULTI_LANGUAGE_SYSTEM
		snprintf(buf, sizeof(buf), LC_LOCALE_TEXT("%s's Mount", m_pkOwner->GetLanguage()), m_pkOwner->GetName());	// tr: "%s Binegi"
#else
		snprintf(buf, sizeof(buf), LC_TEXT("%s's Mount"), m_pkOwner->GetName());
#endif
#else
		snprintf(buf, sizeof(buf), "%s", m_pkOwner->GetName());
#endif


// DWORD CMountActor::Summon(LPITEM pSummonItem, bool bSpawnFar) icinde:
// Ara:
	}
	if (0 != m_pkChar)
	{

// Altina ekle:
#ifdef ENABLE_MOUNT_FOLLOWER_LEVEL
		m_pkChar->SetLevel(MountRenewal_GetLevel(m_pkOwner));
#endif


// DWORD CMountActor::Summon(LPITEM pSummonItem, bool bSpawnFar) icinde:
// Ara:
		return 0;
	}
	m_pkChar->SetMount();

// Altina ekle:
#ifdef ENABLE_MOUNT_FOLLOWER_LEVEL
	m_pkChar->SetCharType(CHAR_TYPE_MOUNT);
	m_pkChar->SetLevel(MountRenewal_GetLevel(m_pkOwner));
#endif


// Ara:
	mountActor->Unmount();
}

// Altina ekle:
#ifdef ENABLE_MOUNT_FOLLOWER_LEVEL
void CMountSystem::RefreshFollower()
{
	const int iLevel = MountRenewal_GetLevel(m_pkOwner);
	for (TMountActorMap::iterator it = m_mountActorMap.begin(); it != m_mountActorMap.end(); ++it)
	{
		CMountActor* actor = it->second;
		if (!actor || !actor->IsSummoned())
			continue;
		actor->SetName();
		actor->GetCharacter()->SetLevel(iLevel);
		actor->GetCharacter()->ViewReencode();
	}
}
#endif

