# Ara:
			{"id": "damage_settings", "name": localeInfo.ADVANCED_OPTIONS_GROUP_DAMAGE_SETTINGS, "windows": ["damage_window"], "hide_titles": ["show_damage_title_img", "damage_title_img"]},
			{"id": "metinstone_settings", "name": localeInfo.ADVANCED_OPTIONS_GROUP_METINSTONE_SETTINGS, "windows": ["stone_scale_window", "queue_metin_window", "event_stone_window", "hide_metin_spawns_window"], "hide_titles": ["stone_scale_title_img", "queue_metin_title_img", "event_stone_title_img", "hide_metin_spawns_img"]},

# Altina ekle:
			{"id": "hide_entities_effects", "name": localeInfo.ADVANCED_OPTIONS_GROUP_HIDE_ENTITIES_EFFECTS, "windows": ["hide_companion_window", "hide_effects_except_damage_window", "auto_hide_companion_map1_window", "shop_range_window"], "hide_titles": ["hide_companion", "hide_effects_except_damage_title_img", "auto_hide_companion_map1_img", "shop_range_title_img"]},


# Ara:
	"pvp_mode_window": 41, "block_mode_window": 61, "names_window": 119, "show_guild_grade_window": 41,
	"stone_scale_window": 47, "event_stone_window": 63, "hide_metin_spawns_window": 62,

# Altina ekle:
	"hide_companion_window": 63, "hide_effects_except_damage_window": 63, "auto_hide_companion_map1_window": 42,


# AdvancedGameOptionsWindow.LoadCategoryOptions icinde ara:
				self.__BindToggle(getOpt("disable_level_up_confirmation_on_off_btn"), "disable_level_up_confirmation", False)
				self.__BindToggle(getOpt("hide_metin_spawns"), "hide_metin_spawns", False)

# Altina ekle:
				self.__BindToggle(getOpt("auto_hide_companion_map1"), "auto_hide_companion_map1", False)


# AdvancedGameOptionsWindow.__SetupGameReferenceDropdowns icinde ara:
			combo.optionArrow = arrow
			return combo

# Altina ekle:
		companionKeys = ("hide_mount", "hide_pet", "hide_buffi")
		companionNames = (localeInfo.GAME_OPTION_HIDE_MOUNT, localeInfo.GAME_OPTION_HIDE_PET, localeInfo.AUTO_BUFFILERI_GIZLE)
		companionCombo = [None]
		def refreshCompanion():
			combo = companionCombo[0]
			if not combo: return
			states = [bool(GetOptSetting(key, False)) for key in companionKeys]
			combo.ClearItem()
			for index, name in enumerate(companionNames):
				combo.InsertItem(index, ("[x] " if states[index] else "[ ] ") + name)
			combo.SetCurrentItem(localeInfo.AUTO_NOTHING_HIDDEN if not any(states) else "%d gizli" % sum(states))
		def selectCompanion(index):
			if index < 0 or index >= len(companionKeys): return
			key = companionKeys[index]
			if advanced_options_runtime.IsAvailable(key):
				SetOptSetting(key, not GetOptSetting(key, False))
			else:
				advanced_options_runtime.ExplainUnavailable(key)
			refreshCompanion()
		companionCombo[0] = makeCombo(getOpt("hide_companion_dropdown_anchor"), companionNames,
			selectCompanion, 0)
		refreshCompanion()


# AdvancedGameOptionsWindow.__SetupGameReferenceDropdowns icinde ara:
			notificationPanel.Children.append(notificationAnchor)
		notificationNames = ("Guideline", localeInfo.AUTO_MISSION_BOOK, localeInfo.GAME_OPTION_NOTIFICATION_BATTLE_PASS, localeInfo.AUTO_ITEM_EXPIRED,

# Altina ekle:
			localeInfo.AUTO_COMPANION_EXPIRED, localeInfo.AUTO_ALCHEMY_EXPIRED, localeInfo.AUTO_BONUS_6_7_FINISHED,


# AdvancedGameOptionsWindow.__SetupGameReferenceDropdowns icinde ara:
			"Fishing", localeInfo.AUTO_MARKET_SALES, localeInfo.BRAVE_CAPE_TITLE)
		notificationKeys = ("guideline", "mission_book", "battle_pass", "item_expired",

# Altina ekle:
			"companion_expired", "alchemy_expired", "bonus_67_finished",


# AdvancedGameOptionsWindow.__SetupGameReferenceDropdowns icinde ara:
		if notificationCombo[0]:
			notificationCombo[0].SetCurrentItem(localeInfo.AUTO_ALL_NOTIFICATIONS)

# Altina ekle:
		scriptWindow.gameCombos = (companionCombo[0], effectCombo[0], notificationCombo[0])

