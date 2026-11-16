// Dosyanin uygun bir yerine ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
#include "growth_pet.h"
#endif


// Dosyanin uygun bir yerine ekle:
#ifdef ENABLE_MOUNT_RENEWAL
#include "mount_renewal.h"
#endif


// void CItem::ModifyPoints(bool bAdd) icinde:
// Ara:
}
void CItem::ModifyPoints(bool bAdd)
{

// Altina ekle:
#ifdef ENABLE_MOUNT_RENEWAL
	if (m_pProto->bType == ITEM_MOUNT)
		return;
#endif
#ifdef ENABLE_BUFFI_SYSTEM
	if (m_bEquipped && GetCell() >= INVENTORY_MAX_NUM && CBuffiManager::IsBuffiWearCell(GetCell() - INVENTORY_MAX_NUM))
		return;
#endif


// bool CItem::EquipTo(LPCHARACTER ch, BYTE bWearCell) icinde:
// Ara:
	if (IsMountItem())
		ch->MountSummon(this);

// Altina ekle:
#ifdef ENABLE_MOUNT_RENEWAL
	if (GetType() == ITEM_MOUNT && bWearCell == WEAR_MOUNT)
		MountRenewal_OnSealChanged(ch, this, true);
#endif


// bool CItem::EquipTo(LPCHARACTER ch, BYTE bWearCell) icinde:
// Ara:
	m_pOwner->ComputeBattlePoints();
	m_pOwner->UpdatePacket();
	Save();

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
	if (CBuffiManager::IsBuffiWearCell(bWearCell))
		CBuffiManager::instance().OnWearChanged(m_pOwner, bWearCell, true);
#endif

#ifdef ENABLE_GROWTH_PET_RENEWAL
	if (bWearCell == WEAR_GROWTH_PET && GetType() == ITEM_GROWTH_PET && GetSubType() == PET_UPBRINGING)
	{
		LPGROWTH_PET pPet = m_pOwner->GetGrowthPet(GetSocket(2));
		if (pPet && (!m_pOwner->GetActiveGrowthPet() || m_pOwner->GetActiveGrowthPet()->GetPetID() != pPet->GetPetID()))
		{
			if (m_pOwner->GetActiveGrowthPet())
				m_pOwner->GetActiveGrowthPet()->Unsummon();
			m_pOwner->SetActiveGrowthPet(pPet->Summon(this));
		}
		Lock(false);
	}
#endif


// bool CItem::Unequip() icinde:
// Ara:
	if (IsMountItem())
		m_pOwner->MountUnsummon(this);

// Altina ekle:
#ifdef ENABLE_MOUNT_RENEWAL
	if (GetType() == ITEM_MOUNT && GetCell() == INVENTORY_MAX_NUM + WEAR_MOUNT)
		MountRenewal_OnSealChanged(m_pOwner, this, false);
#endif


// bool CItem::Unequip() icinde:
// Ara:
	m_pOwner->SetImmuneFlag(dwImmuneFlag);
	m_pOwner->ComputeBattlePoints();
	m_pOwner->UpdatePacket();

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
	LPCHARACTER pkBuffiOwner = m_pOwner;
	const int iBuffiCell = GetCell() - INVENTORY_MAX_NUM;
#endif
#ifdef ENABLE_GROWTH_PET_RENEWAL
	if (m_pOwner && GetCell() == INVENTORY_MAX_NUM + WEAR_GROWTH_PET && m_pOwner->GetActiveGrowthPet()
		&& m_pOwner->GetActiveGrowthPet()->GetPetID() == (DWORD) GetSocket(2))
	{
		m_pOwner->GetActiveGrowthPet()->Unsummon();
		m_pOwner->SetActiveGrowthPet(NULL);
	}
#endif


// bool CItem::Unequip() icinde:
// Ara:
	m_pOwner = NULL;
	m_wCell = 0;
	m_bEquipped	= false;

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
	if (CBuffiManager::IsBuffiWearCell(iBuffiCell))
		CBuffiManager::instance().OnWearChanged(pkBuffiOwner, iBuffiCell, false);
#endif

