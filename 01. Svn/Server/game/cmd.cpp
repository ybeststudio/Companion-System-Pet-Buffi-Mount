// Ara:
ACMD(do_priv_guild);
ACMD(do_mount_test);
ACMD(do_unmount);

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
ACMD(do_buffi_summon);
ACMD(do_buffi_unsummon);
ACMD(do_buffi_info);
ACMD(do_buffi_set);
ACMD(do_buffi_option);
#ifdef ENABLE_MOUNT_RENEWAL
ACMD(do_mount_renewal);
#endif
#ifdef ENABLE_BIOLOG_RENEWAL
ACMD(do_biolog_renewal);
#endif
#ifdef ENABLE_BATTLEPASS_RENEWAL
ACMD(do_battlepass_renewal);
#endif
#ifdef ENABLE_GROWTH_PET_RENEWAL
ACMD(do_pet_upgrade_type);
ACMD(do_pet_evolve);
#endif
ACMD(do_support_skill_power);
#ifdef ENABLE_SKILL_UPGRADE
ACMD(do_upgrade_skill);
ACMD(do_upgrade_skill_info);
#endif
ACMD(do_support_add_ore);
ACMD(do_support_remove_ore);
ACMD(do_buffi_skill_color);
#ifdef ENABLE_BUFFI_EVOLUTION
ACMD(do_support_set_evolution);
#endif
ACMD(do_support_full_duration);
#endif


// Ara:
	{ "priv_guild",						do_priv_guild,					0,						POS_DEAD,			GM_HIGH_WIZARD	},
	{ "mount_test",						do_mount_test,					0,						POS_DEAD,			GM_IMPLEMENTOR	},
	{ "unmount",						do_unmount,						0,						POS_DEAD,			GM_PLAYER		},

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
	{ "buffi_summon",					do_buffi_summon,				0,						POS_DEAD,			GM_PLAYER		},
	{ "buffi_unsummon",					do_buffi_unsummon,				0,						POS_DEAD,			GM_PLAYER		},
	{ "buffi_info",						do_buffi_info,					0,						POS_DEAD,			GM_PLAYER		},
	{ "buffi_option",					do_buffi_option,				0,						POS_DEAD,			GM_PLAYER		},
#ifdef ENABLE_GROWTH_PET_RENEWAL
	{ "pet_upgrade_type",				do_pet_upgrade_type,			0,						POS_DEAD,			GM_PLAYER		},
#ifdef ENABLE_MOUNT_RENEWAL
	{ "mountx",							do_mount_renewal,				0,						POS_DEAD,			GM_PLAYER		},
#endif
#ifdef ENABLE_BIOLOG_RENEWAL
	{ "biolog",							do_biolog_renewal,				0,						POS_DEAD,			GM_PLAYER		},
#endif
#ifdef ENABLE_BATTLEPASS_RENEWAL
	{ "bp",								do_battlepass_renewal,			0,						POS_DEAD,			GM_PLAYER		},
#endif
	{ "pet_evolve",						do_pet_evolve,					0,						POS_DEAD,			GM_PLAYER		},
#endif
	{ "buffi_set",						do_buffi_set,					0,						POS_DEAD,			GM_IMPLEMENTOR	},
	{ "support_skill_power",			do_support_skill_power,			0,						POS_DEAD,			GM_PLAYER		},
#ifdef ENABLE_SKILL_UPGRADE
	{ "upgrade_skill",				do_upgrade_skill,				0,						POS_DEAD,			GM_PLAYER		},
	{ "upgrade_skill_info",			do_upgrade_skill_info,			0,						POS_DEAD,			GM_PLAYER		},
#endif
	{ "support_add_ore",				do_support_add_ore,				0,						POS_DEAD,			GM_PLAYER		},
	{ "support_remove_ore",			do_support_remove_ore,			0,						POS_DEAD,			GM_PLAYER		},
	{ "buffi_skill_color",			do_buffi_skill_color,			0,						POS_DEAD,			GM_PLAYER		},
#ifdef ENABLE_BUFFI_EVOLUTION
	{ "support_set_evolution",		do_support_set_evolution,		0,						POS_DEAD,			GM_PLAYER		},
#endif
	{ "support_full_duration",			do_support_full_duration,		0,						POS_DEAD,			GM_PLAYER		},
#endif

