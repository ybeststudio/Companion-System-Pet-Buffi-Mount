# Ara:
if app.ENABLE_GROWTH_PET_SYSTEM:
	import uiPetInfo

# Altina ekle:
import uiCompanion


# Interface.__init__ icinde ara:
		self.wndExpandedMoney = None
		self.wndExpandedTaskBar = None

# Altina ekle:
		self.wndCompanion = None


# Interface.__MakeGameButtonWindow icinde ara:
		wndGameButton.SetButtonEvent("GUIDE", ui.__mem_func__(self.__OnClickGuideButton))
		wndGameButton.SetButtonEvent("NOTIFICATION_HISTORY", ui.__mem_func__(self.__OnClickNotificationHistoryButton))

# Altina ekle:
		wndGameButton.SetButtonEvent("BUFFI", ui.__mem_func__(self.ToggleCompanionBuffiWnd))


# Interface.__MakeWindows icinde ara:
			self.wndInventory.SetPetFeedWindow(self.wndPetInfoWindow.GetPetFeedWindow())
			self.wndInventory.SetPetNameChangeWindow(self.wndPetInfoWindow.GetPetNameChangeWindow())

# Altina ekle:
		self.wndCompanion = uiCompanion.CompanionWindow()
		self.wndCompanion.BindInterface(self)
		self.wndCompanion.Hide()


# Interface.Close icinde ara:
			if self.wndPetInfoWindow:
				self.wndPetInfoWindow.Destroy()

# Altina ekle:
		if self.wndCompanion:
			self.wndCompanion.Destroy()
			self.wndCompanion = None


# Interface.TogglePetInformationWindow icinde ara:
		def TogglePetInformationWindow(self):

# Altina ekle:
			if app.ENABLE_GROWTH_PET_RENEWAL and self.wndCompanion:
				if False == player.IsObserverMode():
					if self.wndCompanion.IsShow() and self.wndCompanion.tab == uiCompanion.TAB_PET:
						self.wndCompanion.Close()
					else:
						self.wndCompanion.Open(uiCompanion.TAB_PET)
				return


# Interface icinde ara:
		if self.wndSkillUpgrade:
			self.wndSkillUpgrade.Refresh()

# Altina ekle:
	def ToggleCompanionBuffiWnd(self):
		if self.wndCompanion and False == player.IsObserverMode():
			if self.wndCompanion.IsShow() and self.wndCompanion.tab == uiCompanion.TAB_BUFFI:
				self.wndCompanion.Close()
			else:
				self.wndCompanion.Open(uiCompanion.TAB_BUFFI)

	def SetBuffiInformation(self, *args):
		if self.wndCompanion:
			self.wndCompanion.SetBuffiInformation(*args)

	def SetBuffiSkills(self, *args):
		if self.wndCompanion:
			self.wndCompanion.SetBuffiSkills(*args)

	def SetBuffiSkillsBook(self, *args):
		if self.wndCompanion:
			self.wndCompanion.SetBuffiSkillsBook(*args)

	def SetBuffiSkillsCooldown(self, *args):
		if self.wndCompanion:
			self.wndCompanion.SetBuffiSkillsCooldown(*args)

	def SetBuffiName(self, name):
		if self.wndCompanion:
			self.wndCompanion.SetBuffiName(name)

	def Buffi_SetUnsummon(self):
		if self.wndCompanion:
			self.wndCompanion.UnsummonBuffi()

	def GetBuffiSkillPts(self):
		return self.wndCompanion.GetBuffiSkillPts() if self.wndCompanion else 0

	def GetBuffiSkillsPower(self):
		return self.wndCompanion.GetBuffiSkillsPower() if self.wndCompanion else []

	def GetBuffiSkillsBook(self):
		return self.wndCompanion.GetBuffiSkillsBook() if self.wndCompanion else []

	def GetBuffiSkillsCooldown(self):
		return self.wndCompanion.GetBuffiSkillsCooldown() if self.wndCompanion else []


# Interface.__HideWindows icinde ara:
			if self.wndPetInfoWindow:
				hideWindows += self.wndPetInfoWindow,

# Altina ekle:
		if self.wndCompanion:
			hideWindows += self.wndCompanion,


# Interface.TogglePetInformationWindow icinde ara:
		def TogglePetInformationWindow(self):

# Altina ekle:
			if app.ENABLE_GROWTH_PET_RENEWAL and self.wndCompanion:
				if FALSE == player.IsObserverMode():
					if self.wndCompanion.IsShow() and self.wndCompanion.tab == uiCompanion.TAB_PET:
						self.wndCompanion.Close()
					else:
						self.wndCompanion.Open(uiCompanion.TAB_PET)
				return

