# GameWindow.OptionItemExpired icinde ara:
	def OptionItemExpired(self, category, vnum):
		import advanced_option_notifications

# Altina ekle:
		if category not in ("item_expired", "companion_expired", "alchemy_expired"):
			return


# GameWindow icinde ara:
		return 1
	# Buffi (reference: game.GameWindow.SetSupport* -> interface.SetBuffi*)

# Altina ekle:
	def SetSupportData(self, level, intel, exp, exp_total, evo, duration, runes_1, runes_2, runes_3):
		if self.interface:
			self.interface.SetBuffiInformation(*map(int, (level, intel, exp, exp_total, evo, duration, runes_1, runes_2, runes_3)))

	def SetSupportSkill(self, pts, amt0, pwr0, amt1, pwr1, amt2, pwr2, amt3, pwr3, amt4, pwr4):
		if self.interface:
			self.interface.SetBuffiSkills(*map(int, (pts, amt0, pwr0, amt1, pwr1, amt2, pwr2, amt3, pwr3, amt4, pwr4)))

	def SetSupportSkillBook(self, book0, book1, book2, book3, book4):
		if self.interface:
			self.interface.SetBuffiSkillsBook(*map(int, (book0, book1, book2, book3, book4)))

	def SetSupportSkillCooldown(self, skill0, skill1, skill2, skill3, skill4):
		if self.interface:
			self.interface.SetBuffiSkillsCooldown(*map(int, (skill0, skill1, skill2, skill3, skill4)))

	def SetSupportName(self, name):
		if self.interface:
			self.interface.SetBuffiName(name)

	def SupportLeave(self):
		if self.interface:
			self.interface.Buffi_SetUnsummon()

	def SetSupportSkillColor(self, idx, c0, c1, c2, c3, c4):
		if self.interface and self.interface.wndCompanion:
			self.interface.wndCompanion.SetBuffiSkillColor(int(idx), map(long, (c0, c1, c2, c3, c4)))


# GameWindow icinde ara:
		if self.interface:
			self.interface.SkillUpgradeNegativeGradeConfirm()

# Altina ekle:
	def SupportEvolutionResult(self, success):
		if self.interface and self.interface.wndCompanion:
			self.interface.wndCompanion.OnBuffiEvolutionResult(int(success))

	def SetSupportCastSpeed(self, value):
		if self.interface and self.interface.wndCompanion:
			self.interface.wndCompanion.SetBuffiCastSpeed(int(value))

	if app.ENABLE_GROWTH_PET_RENEWAL:
		def PetPotionResult(self, code, value):
			if self.interface and self.interface.wndCompanion:
				self.interface.wndCompanion.OnPetPotionResult(int(code), int(value))

		def MountInfo(self, data):
			if self.interface and self.interface.wndCompanion:
				self.interface.wndCompanion.OnMountInfo(data.split(","))

		def MountResult(self, code, value):
			if self.interface and self.interface.wndCompanion:
				self.interface.wndCompanion.OnMountResult(int(code), int(value))

		def PetEvolveResult(self, code, value):
			if self.interface and self.interface.wndCompanion:
				self.interface.wndCompanion.OnPetEvolveResult(int(code), int(value))

		def PetSkillSlotResult(self, code, value):
			if self.interface and self.interface.wndCompanion:
				self.interface.wndCompanion.OnPetSkillSlotResult(int(code), int(value))

		def PetMessage(self, code, name = ""):
			messages = {1 : localeInfo.PET_MSG_LIFETIME_OVER, 2 : localeInfo.PET_MSG_LEVEL_TOO_HIGH, 3 : localeInfo.PET_MSG_CANNOT_SUMMON_NOW, 4 : localeInfo.PET_MSG_LIFETIME_MAX, 5 : localeInfo.PET_MSG_LIFETIME_EXTENDED}
			text = messages.get(int(code))
			if text:
				chat.AppendChat(chat.CHAT_TYPE_INFO, text.replace("%s", name))

		def PetTypeUpgradeResult(self, code, pity, pityMax):
			if self.interface and self.interface.wndCompanion:
				self.interface.wndCompanion.OnPetTypeUpgradeResult(int(code), int(pity), int(pityMax))


# GameWindow.__ServerCommand_Build icinde ara:
		serverCommandList={
			"OptionNoticeNext" : self.OptionNoticeNext,

# Altina ekle:
			"SetSupportData"								: self.SetSupportData,
			"SetSupportSkill"								: self.SetSupportSkill,
			"SetSupportSkillBook"							: self.SetSupportSkillBook,
			"SetSupportSkillCooldown"						: self.SetSupportSkillCooldown,
			"SetSupportName"								: self.SetSupportName,
			"SupportLeave"									: self.SupportLeave,
			"SetSupportSkillColor"							: self.SetSupportSkillColor,
			"SetSupportCastSpeed"							: self.SetSupportCastSpeed,
			"SupportEvolutionResult"						: self.SupportEvolutionResult,


# GameWindow.__ServerCommand_Build icinde ara:
		if app.ENABLE_RENEWAL_TELEPORT_SYSTEM:
			serverCommandList["OpenWarpWindow"] = self.__OpenWarpWindow

# Altina ekle:
		if app.ENABLE_GROWTH_PET_RENEWAL:
			serverCommandList["PetPotionResult"] = self.PetPotionResult
			serverCommandList["PetTypeUpgradeResult"] = self.PetTypeUpgradeResult
			serverCommandList["PetMessage"] = self.PetMessage
			serverCommandList["PetEvolveResult"] = self.PetEvolveResult
			serverCommandList["MountInfo"] = self.MountInfo
			serverCommandList["MountResult"] = self.MountResult
			serverCommandList["PetSkillSlotResult"] = self.PetSkillSlotResult

