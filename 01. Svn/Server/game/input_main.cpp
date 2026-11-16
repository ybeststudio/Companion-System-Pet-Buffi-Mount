// void CInputMain::PetLearnSkill(LPCHARACTER ch, const char* c_pData) icinde:
// Ara:
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Activate your pet first."));
		return;
	}

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	if (p->slotIndex >= PET_SKILL_COUNT_MAX)
		return;
#endif

