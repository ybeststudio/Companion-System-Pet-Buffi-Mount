// Dosyanin uygun bir yerine ekle:
#ifdef ENABLE_MOUNT_RENEWAL
#include "mount_renewal.h"
#endif


// void BiologRenewal_OnDataLoaded(LPCHARACTER ch) icinde:
// Ara:
	if (!ch || !ch->IsPC() || !IsLoginDataLoaded(ch))
		return;
	BiologRenewal_OnLogin(ch);

// Altina ekle:
#ifdef ENABLE_MOUNT_RENEWAL
	MountRenewal_RefreshAffect(ch);
#endif

