/*
 * File Name : mount_renewal.h
 * Author    : BestStudio
 * Version   : 1.0
 * Date      : 2026-11-13
 *
 * Anka "At" companion tab: mount level / EXP (medal donation), evolution, food, 3 bonus slots,
 * 4 skills and 4 runes. Progress belongs to the character and the mount seal (Anka item text),
 * kept in quest flags "mntdata.<seal id>_<field>". The bonuses work while the seal is worn.
 */
#pragma once

#include "../../common/service.h"

#ifdef ENABLE_MOUNT_RENEWAL
class CHARACTER;

void MountRenewal_SendInfo(LPCHARACTER ch);
void MountRenewal_RefreshAffect(LPCHARACTER ch);
void MountRenewal_OnSealChanged(LPCHARACTER ch, LPITEM pSeal, bool bEquip);
bool MountRenewal_UseItem(LPCHARACTER ch, LPITEM item);	// bonus switchers; true = handled
int MountRenewal_GetLevel(LPCHARACTER ch);
void MountRenewal_RefreshFollower(LPCHARACTER ch);
#endif
