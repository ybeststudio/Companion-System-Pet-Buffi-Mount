# Ara:
EQUIPMENT_START_INDEX = player.EQUIPMENT_SLOT_START
# companion mount = EQUIPMENT_MOUNT, costume mount / pet = COSTUME_SLOT_MOUNT / COSTUME_SLOT_PET,

# Altina ekle:
COMPANION_MOUNT = item.EQUIPMENT_MOUNT


# Ara:
COSTUME_MOUNT = item.COSTUME_SLOT_MOUNT
COSTUME_PET = item.COSTUME_SLOT_PET

# Altina ekle:
COMPANION_BUFFI = EQUIPMENT_START_INDEX + 33
COMPANION_BUFFI_ARMOR = EQUIPMENT_START_INDEX + 34
COMPANION_BUFFI_WEAPON = EQUIPMENT_START_INDEX + 35
COMPANION_BUFFI_HAIR = EQUIPMENT_START_INDEX + 36
COMPANION_BUFFI_ACCE = EQUIPMENT_START_INDEX + 37
if app.ENABLE_GROWTH_PET_RENEWAL:
	COMPANION_GROWTH_PET = EQUIPMENT_START_INDEX + 38	# WEAR_GROWTH_PET: the growth pet seal, equipped = summoned
else:
	COMPANION_GROWTH_PET = item.EQUIPMENT_PET


# Ara:
				# Companion
				{

# Altina ekle:
					"name" : "Companion_Base",


# Ara:
					(
						{

# Altina ekle:
							"name" : "CompanionSlot",


# Ara:
							"height" : 182,
							"slot" : (	

# Altina ekle:
								{"index":COMPANION_MOUNT, "x":78, "y":133, "width":32, "height":32},


# Ara:
								{"index":COSTUME_MOUNT, "x":113, "y":133, "width":32, "height":32},

# Altina ekle:
								{"index":COMPANION_GROWTH_PET, "x":5, "y":133, "width":32, "height":32},


# Ara:
								{"index":COSTUME_PET, "x":41, "y":133, "width":32, "height":32},

# Altina ekle:
								{"index":COMPANION_BUFFI, "x":113, "y":87, "width":32, "height":32},

								{"index":COMPANION_BUFFI_ACCE, "x":112, "y":13, "width":32, "height":32},
								{"index":COMPANION_BUFFI_WEAPON, "x":10, "y":39, "width":32, "height":32},
								{"index":COMPANION_BUFFI_ARMOR, "x":63, "y":48, "width":32, "height":64},
								{"index":COMPANION_BUFFI_HAIR, "x":63, "y":7, "width":32, "height":32},

