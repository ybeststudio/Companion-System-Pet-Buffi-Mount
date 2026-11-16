// void initItem() icinde:
// Ara:
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_MEDI_PVM", CItemData::APPLY_ATTBONUS_MEDI_PVM);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_PVM_STR", CItemData::APPLY_ATTBONUS_PVM_STR);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_PVM_BERSERKER", CItemData::APPLY_ATTBONUS_PVM_BERSERKER);

// Altina ekle:
#ifdef ENABLE_PET_EXP_BONUS
	PyModule_AddIntConstant(poModule, "APPLY_PET_EXP_BONUS", CItemData::APPLY_PET_EXP_BONUS);
#endif

