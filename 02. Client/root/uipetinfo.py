# PetMiniInfomationWindow.Show icinde ara:
	def Show(self):

# Altina ekle:
		if app.ENABLE_GROWTH_PET_RENEWAL:
			return


# PetHatchingWindow.__LoadWindow icinde ara:
		self.isLoaded = 1
		try:

# Altina ekle:
			if app.ENABLE_GROWTH_PET_RENEWAL:
				self.__LoadScript("UIScript/incubatorwindow.py")
			else:
				self.__LoadScript("UIScript/petHatchingWindow.py")


# PetHatchingWindow.__LoadWindow icinde ara:
			self.hatchingSlot.SetOverInItemEvent(ui.__mem_func__(self.OverInItem))
			self.hatchingSlot.SetOverOutItemEvent(ui.__mem_func__(self.OverOutItem))

# Altina ekle:
			if app.ENABLE_GROWTH_PET_RENEWAL:
				self.hatchingSlot.Hide()


# PetHatchingWindow.ClickHatchingButton icinde ara:
			if self.popupDialog.IsShow():
				return

# Altina ekle:
		if app.ENABLE_GROWTH_PET_RENEWAL:
			self.__HatchingQuestionDialogAccept()
			return


# PetHatchingWindow.HatchingWindowOpen icinde ara:
		hatching_money_value = item.GetValue(3)
		if self.hatchingMoneyText:

# Altina ekle:
			if app.ENABLE_GROWTH_PET_RENEWAL:
				self.hatchingMoneyText.SetText(localeInfo.PET_INCUBATOR_PRICE % localeInfo.MoneyFormat(hatching_money_value))
			else:
				self.hatchingMoneyText.SetText(localeInfo.PET_HATCHING_MONEY % localeInfo.NumberToMoneyString(hatching_money_value))


# PetHatchingWindow.HatchingWindowOpen icinde ara:
		item_string = item.GetItemName()
		self.petName = item_string[:item.PET_NAME_MAX_SIZE]

# Altina ekle:
		if app.ENABLE_GROWTH_PET_RENEWAL:
			self.petName = ""


# PetInformationWindow.Show icinde ara:
	def Show(self):

# Altina ekle:
		if app.ENABLE_GROWTH_PET_RENEWAL:
			self.__LoadWindow()
			return

