// void initapp() icinde:
// Ara:
	PyModule_AddIntConstant(poModule, "__BUFFI_SUPPORT__", 0);

// Altina ekle:
#ifdef ENABLE_BUFFI_EVOLUTION
	PyModule_AddIntConstant(poModule, "ENABLE_BUFFI_EVOLUTION", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_BUFFI_EVOLUTION", 0);
#endif


// void initapp() icinde:
// Ara:
	PyModule_AddIntConstant(poModule, "ENABLE_BUFFI_EVOLUTION", 0);

// Altina ekle:
#ifdef ENABLE_BUFFI_SKILL_BOOK
	PyModule_AddIntConstant(poModule, "ENABLE_BUFFI_SKILL_BOOK", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_BUFFI_SKILL_BOOK", 0);
#endif


// void initapp() icinde:
// Ara:
	PyModule_AddIntConstant(poModule, "ENABLE_BUFFI_SKILL_BOOK", 0);

// Altina ekle:
#ifdef ENABLE_BUFFI_CHANGE_SEX
	PyModule_AddIntConstant(poModule, "ENABLE_BUFFI_CHANGE_SEX", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_BUFFI_CHANGE_SEX", 0);
#endif


// void initapp() icinde:
// Ara:
	PyModule_AddIntConstant(poModule, "ENABLE_UI_BACKGROUND_BLUR", 0);

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	PyModule_AddIntConstant(poModule, "ENABLE_GROWTH_PET_RENEWAL", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_GROWTH_PET_RENEWAL", 0);
#endif

