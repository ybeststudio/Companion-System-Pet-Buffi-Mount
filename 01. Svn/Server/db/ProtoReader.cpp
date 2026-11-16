// Ara:
	}
	return retInt;
}

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
int32_t get_Item_SubType_Value(uint32_t type_value, const string &inputString);
void RemapGrowthPetItem(BYTE& bType, BYTE& bSubType, const std::string& subTypeString)
{
	if (bType != ITEM_PET)
		return;

	static const char* growthSubTypes[] =
	{
		"PET_EGG", "PET_UPBRINGING", "PET_BAG", "PET_FEEDSTUFF", "PET_SKILL", "PET_SKILL_DEL_BOOK", "PET_NAME_CHANGE",
		"PET_EXPFOOD", "PET_SKILL_ALL_DEL_BOOK", "PET_EXPFOOD_PER", "PET_ATTR_DETERMINE", "PET_ATTR_CHANGE", "PET_PAY",
		"PET_PRIMIUM_FEEDSTUFF", "PET_HP_POTION", "PET_ATTACK_POTION", "PET_ELEMENTAL_POTION",
	};

	std::string s = subTypeString;
	s.erase(0, s.find_first_not_of(" \t\r\n\""));
	s.erase(s.find_last_not_of(" \t\r\n\"") + 1);
	if (s == "PET_PAY")
	{
		bType = ITEM_COSTUME;
		bSubType = (BYTE) get_Item_SubType_Value(ITEM_COSTUME, "COSTUME_PET");
		return;
	}

	for (size_t i = 0; i < sizeof(growthSubTypes) / sizeof(growthSubTypes[0]); ++i)
	{
		if (s == growthSubTypes[i])
		{
			bType = ITEM_GROWTH_PET;
			bSubType = (BYTE) i;
			return;
		}
	}
}
#endif


// bool Set_Proto_Item_Table(TItemTable *itemTable, const cCsvTable &csvTable,std::map<int32_t, const char*> &nameMap) icinde:
// Ara:
		int32_t col = 2;
		itemTable->bType = get_Item_Type_Value(csvTable.AsStringByIndex(col++));
		itemTable->bSubType = get_Item_SubType_Value(itemTable->bType, csvTable.AsStringByIndex(col++));

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
		RemapGrowthPetItem(itemTable->bType, itemTable->bSubType, csvTable.AsStringByIndex(col - 1));
#endif

