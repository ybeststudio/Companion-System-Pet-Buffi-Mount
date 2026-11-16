// bool CClientManager::CreateGrowthPetTableFromRes(MYSQL_RES* res, std::vector<TGrowthPet>* pVec, DWORD dwPID) icinde:
// Ara:
	{
		MYSQL_ROW row = mysql_fetch_row(res);
		TGrowthPet& pet = pVec->at(i);

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
		unsigned long* lengths = mysql_fetch_lengths(res);
#endif


// bool CClientManager::CreateGrowthPetTableFromRes(MYSQL_RES* res, std::vector<TGrowthPet>* pVec, DWORD dwPID) icinde:
// Bul:
		thecore_memcpy(pet.aSkill, row[cur++], sizeof(pet.aSkill));

// Degistir:
#ifdef ENABLE_GROWTH_PET_RENEWAL
		{
			const unsigned long skillLen = lengths ? lengths[cur] : 0;
			const size_t copyLen = std::min<size_t>(sizeof(pet.aSkill), (size_t)skillLen);
			if (row[cur] && copyLen)
				thecore_memcpy(pet.aSkill, row[cur], copyLen);
			++cur;
		}
#else
		thecore_memcpy(pet.aSkill, row[cur++], sizeof(pet.aSkill));
#endif

