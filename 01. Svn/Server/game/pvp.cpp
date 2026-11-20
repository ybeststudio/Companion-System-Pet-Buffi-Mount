// Ara:
bool CPVPManager::CanAttack(LPCHARACTER pkChr, LPCHARACTER pkVictim)
{

// Altina ekle:
#ifdef ENABLE_COMPANION_ATTACK_FIX
	if (pkVictim->IsPet() || pkVictim->IsMount() || pkVictim->GetRider() || pkVictim->GetCharType() == CHAR_TYPE_HORSE)
		return false;
#endif
