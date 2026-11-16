# ItemToolTip.__AppendBuffiSealInfo icinde ara:
		self.__AppendBuffiSealLines(localeInfo.TOOLTIP_BUFFI_UNEQUIP, self.FONT_COLOR)
		try:

# Altina ekle:
			import uiCompanion
			state = uiCompanion.g_buffiState


# ItemToolTip.AddItemData icinde ara:
		if self.showEmptyCostumeBonus:
			self.__AppendCostumeTypeLine(itemType, itemSubType)

# Altina ekle:
		if item.ITEM_TYPE_GROWTH_PET == itemType and app.ENABLE_GROWTH_PET_SYSTEM and not app.ENABLE_GROWTH_PET_RENEWAL:
			if item.PET_UPBRINGING == itemSubType:

				pet_id = metinSlot[2]
				if pet_id:
					(pet_level, evol_level, birthday, pet_nick, pet_hp, pet_def, pet_sp) = player.GetPetItem(pet_id)

					self.ClearToolTip()
					self.AppendTextLine(pet_nick, self.TITLE_COLOR)


# ItemToolTip.AddItemData icinde, ilgili if blogunun sonuna ekle:
		elif not (app.ENABLE_GROWTH_PET_RENEWAL and item.ITEM_TYPE_GROWTH_PET == itemType and item.PET_UPBRINGING == itemSubType):
			self.AppendDescription(itemDesc, DESC_DEFAULT_MAX_COLS)
			self.AppendDescription(itemSummary, DESC_DEFAULT_MAX_COLS, self.CONDITION_COLOR)


# ItemToolTip.AddItemData icinde, ilgili if blogunun sonuna ekle:
			elif app.ENABLE_GROWTH_PET_RENEWAL and itemSubType in PET_POTION_SUB_TYPES:
				self.__AppendPetPotionMaxBox(item.GetValue(1))


# ItemToolTip icinde ara:
			self.toolTipHeight += 20
			self.ResizeToolTip()

# Altina ekle:
		def AppendCompanionShortcutTable(self):
			rows = []
			if app.ENABLE_IKASHOP_RENEWAL:
				rows.append((("ctrl", "mouse_right"), localeInfo.TOOLTIP_SHORTCUT_SHOP_SEARCH))
			if app.ENABLE_WIKI_SYSTEM:
				rows.append((("ctrl", "alt", "mouse_left"), localeInfo.TOOLTIP_SHORTCUT_WIKI))
			self.AppendShortcutTable(rows)
			self.ResizeToolTip()


# ItemToolTip.__AppendUpBringingPetItemInfomation icinde ara:
		def __AppendUpBringingPetItemInfomation(self, metinSlot):

# Altina ekle:
			if app.ENABLE_GROWTH_PET_RENEWAL:
				pet_id = metinSlot[2]
				if not pet_id:
					return
				(pet_level, evol_level, birthday, pet_nick, pet_hp, pet_def, pet_sp) = player.GetPetItem(pet_id)
				self.AppendSpace(5)
				self.AppendTextLine("%s %d" % (localeInfo.PET_TOOLTIP_LEVEL, pet_level), self.NORMAL_COLOR)
				self.AppendTextLine("%s +%0.1f%%" % (localeInfo.PET_SEAL_TOOLTIP_HP, pet_hp), self.SPECIAL_POSITIVE_COLOR)
				self.AppendTextLine("%s +%0.1f%%" % (localeInfo.PET_SEAL_TOOLTIP_ATTACK, pet_sp), self.SPECIAL_POSITIVE_COLOR)
				self.AppendTextLine("%s +%0.1f%%" % (localeInfo.PET_SEAL_TOOLTIP_ELEMENT, pet_def), self.SPECIAL_POSITIVE_COLOR)
				self.AppendSpace(9)
				left = metinSlot[0] - app.GetGlobalTimeStamp()
				if left > 0:
					timeText = localeInfo.PET_SEAL_TIME_DHM % (left / 86400, (left % 86400) / 3600, (left % 3600) / 60)
					self.AppendTextLine(localeInfo.PET_SEAL_TOOLTIP_TIME % timeText, self.NORMAL_COLOR)
				else:
					self.AppendTextLine(localeInfo.PET_SEAL_TOOLTIP_TIME % localeInfo.PET_TOOLTIP_LIFETIME_OVER, self.DISABLE_COLOR)
				return

