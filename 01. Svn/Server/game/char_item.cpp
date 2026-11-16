// Dosyanin uygun bir yerine ekle:
#ifdef ENABLE_BUFFI_SYSTEM
#include "buffi_system.h"
#endif


// Dosyanin uygun bir yerine ekle:
#ifdef ENABLE_MOUNT_RENEWAL
#include "mount_renewal.h"
#endif


// bool CHARACTER::UseItemEx(LPITEM item, TItemPos DestCell) icinde:
// Ara:
	{
		return false;
	}

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
	if (CBuffiManager::instance().OnUseItem(this, item))
		return true;
#endif


// bool CHARACTER::UseItemEx(LPITEM item, TItemPos DestCell) icinde:
// Ara:
		if (false == item->IsEquipped())
			item->SetSocket(1, item->GetSocket(1) + 1);
	}

// Altina ekle:
#ifdef ENABLE_MOUNT_RENEWAL
	if (MountRenewal_UseItem(this, item))
		return true;
#endif


// bool CHARACTER::UseItemEx(LPITEM item, TItemPos DestCell) icinde:
// Ara:
				{
					case PET_UPBRINGING:
					{

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
						if (item->IsEquipped() && item->GetCell() == INVENTORY_MAX_NUM + WEAR_GROWTH_PET)
						{
							if (m_activeGrowthPet)
							{
								m_activeGrowthPet->Unsummon();
								m_activeGrowthPet = NULL;
							}
							item->Lock(false);
							UnequipItem(item);
							return true;
						}
						return EquipItem(item, WEAR_GROWTH_PET);
#endif


// bool CHARACTER::UseItemEx(LPITEM item, TItemPos DestCell) icinde:
// Ara:
						}
					}
					break;

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
					case PET_SKILL_ALL_DEL_BOOK:
					case PET_EXPFOOD:
						if (item->GetVnum() == PET_SKILL_UNLOCK_ITEM_VNUM || item->GetVnum() == PET_LIFETIME_ITEM_VNUM)
						{
							if (!m_activeGrowthPet)
							{
								ChatPacket(CHAT_TYPE_COMMAND, "PetPotionResult 0 0");
								return false;
							}
							if (item->GetVnum() == PET_SKILL_UNLOCK_ITEM_VNUM)
							{
								if (m_activeGrowthPet->UnlockSkillSlot())
									item->SetCount(item->GetCount() - 1);
							}
							else
								m_activeGrowthPet->ExtendLifetime(item);
							return true;
						}
						break;

					case PET_HP_POTION:
					case PET_ATTACK_POTION:
					case PET_ELEMENTAL_POTION:
					{
						if (!m_activeGrowthPet)
						{
							ChatPacket(CHAT_TYPE_COMMAND, "PetPotionResult 0 0");
							return false;
						}
						m_activeGrowthPet->UseBonusPotion(item);
					}
					break;
#endif


// bool CHARACTER::UseItemEx(LPITEM item, TItemPos DestCell) icinde:
// Ara:
					case PET_FEEDSTUFF:
					{
						LPITEM item2;

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
						if ((!GetItem(DestCell) || GetItem(DestCell) == item) && GetWear(WEAR_GROWTH_PET))
							DestCell = TItemPos(INVENTORY, INVENTORY_MAX_NUM + WEAR_GROWTH_PET);
#endif


// bool CHARACTER::EquipItem(LPITEM item, int iCandidateCell) icinde:
// Ara:
}
bool CHARACTER::EquipItem(LPITEM item, int iCandidateCell)
{

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	if (iCandidateCell == WEAR_GROWTH_PET || (item && item->GetType() == ITEM_GROWTH_PET && item->GetSubType() == PET_UPBRINGING && iCandidateCell == -1))
	{
		if (!item || item->GetType() != ITEM_GROWTH_PET || item->GetSubType() != PET_UPBRINGING || item->IsExchanging() || item->isLocked())
			return false;
		if (!GetGrowthPet(item->GetSocket(2)))
			return false;
		if (LPITEM old = GetWear(WEAR_GROWTH_PET))
		{
			if (m_activeGrowthPet)
			{
				m_activeGrowthPet->Unsummon();
				m_activeGrowthPet = NULL;
			}
			old->Lock(false);
			if (!UnequipItem(old))
				return false;
		}
		return item->EquipTo(this, WEAR_GROWTH_PET);
	}
#endif
#ifdef ENABLE_BUFFI_SYSTEM
	if (CBuffiManager::IsBuffiWearCell(iCandidateCell))
		return CBuffiManager::instance().EquipToBuffi(this, item, iCandidateCell);
#endif

