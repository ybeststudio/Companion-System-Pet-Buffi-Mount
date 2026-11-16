# InventoryWindow.__LoadWindow icinde ara:
			for i in xrange(player.INVENTORY_PAGE_COUNT):
				self.inventoryTab.append(self.GetChild("Inventory_Tab_%02d" % (i+1)))

# Altina ekle:
			self.equipmentBases = [self.GetChild("Equipment_Base"), self.GetChild("Costume_Base"), self.GetChild("Companion_Base")]


# InventoryWindow.__LoadWindow icinde ara:
		wndItem.SetOverOutItemEvent(ui.__mem_func__(self.OverOutItem))
		slotWindows = []

# Altina ekle:
		for name in ("EquipmentSlot", "CostumeSlot", "CompanionSlot"):
			wnd = self.GetChild(name)
			wnd.SetSelectEmptySlotEvent(ui.__mem_func__(self.SelectEmptySlot))
			wnd.SetSelectItemSlotEvent(ui.__mem_func__(self.SelectItemSlot))
			wnd.SetUnselectItemSlotEvent(ui.__mem_func__(self.UseItemSlot))
			wnd.SetUseSlotEvent(ui.__mem_func__(self.UseItemSlot))
			wnd.SetOverInItemEvent(ui.__mem_func__(self.OverInItem))
			wnd.SetOverOutItemEvent(ui.__mem_func__(self.OverOutItem))
			wnd.SetOverInEmptySlotEvent(ui.__mem_func__(self.OverInEmpty))
			wnd.Show()
			slotWindows.append(wnd)


# InventoryWindow icinde ara:
	MANAGE_OFFSET = 24
	MONEY_SLOT_HEIGHT = 20

# Altina ekle:
	MANAGE_MOVED = ("Equipment_Base", "Costume_Base", "Companion_Base", "Inventory_Tab_01", "Inventory_Tab_02",
		"Inventory_Tab_03", "Inventory_Tab_04", "ItemSlot")


# InventoryWindow.__UseItemPet icinde, ilgili if blogunun sonuna ekle:
			elif app.ENABLE_GROWTH_PET_RENEWAL and (itemSubType == item.PET_FEEDSTUFF or player.GetItemIndex(slotIndex) in (55028, 55029)):
				self.__SendUseItemPacket(slotIndex)
				return

			elif app.ENABLE_GROWTH_PET_RENEWAL and itemSubType in (14, 15, 16):
				self.__SendUseItemPacket(slotIndex)


# InventoryWindow.__UseItemPet icinde ara:
					self.questionDialog.Open()
			if item.PET_SKILL_ALL_DEL_BOOK == itemSubType:

# Altina ekle:
				if app.ENABLE_GROWTH_PET_RENEWAL and player.GetItemIndex(slotIndex) == 55029:
					return

