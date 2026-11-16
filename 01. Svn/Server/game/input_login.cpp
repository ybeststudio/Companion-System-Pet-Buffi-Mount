// Dosyanin uygun bir yerine ekle:
#ifdef ENABLE_BUFFI_SYSTEM
#include "buffi_system.h"
#endif


// Ara:
extern void SendOfflineWhisperMessages(LPCHARACTER ch);

// Altina ekle:
#ifdef ENABLE_MOUNT_RENEWAL
#include "mount_renewal.h"
#endif


// void CInputLogin::Entergame(LPDESC d, const char * data) icinde:
// Ara:
	if (ch->GetMapIndex() != 113 && CArenaManager::instance().IsArenaMap(ch->GetMapIndex()) == false)
		ch->CheckPet();

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	ch->SummonEquippedGrowthPet();
#endif
#ifdef ENABLE_MOUNT_RENEWAL
	MountRenewal_RefreshAffect(ch);
	MountRenewal_SendInfo(ch);
	MountRenewal_RefreshFollower(ch);
#endif


// void CInputLogin::Entergame(LPDESC d, const char * data) icinde:
// Ara:
	BiologRenewal_OnDataLoaded(ch);	// runs only once the quest flags and the affects are loaded

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
	if (ch->GetMapIndex() != 113 && CArenaManager::instance().IsArenaMap(ch->GetMapIndex()) == false)
		CBuffiManager::instance().OnLogin(ch);
#endif

