# GameButtonWindow.CheckGameButton icinde ara:
		buffiButton = self.gameButtonDict["BUFFI"]
		interface = constInfo.GetInterfaceInstance()

# Altina ekle:
		companion = interface.wndCompanion if interface else None
		buffiSummoned = companion is not None and companion.buffiSummoned

