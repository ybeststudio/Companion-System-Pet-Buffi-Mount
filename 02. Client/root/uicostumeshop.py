# CostumeShopWindow.BuildWindow icinde ara:
		renderTarget.SetRotation(self.renderIndex, False)
		self.petRenderIndex = renderTarget.GetFreeIndex(50, 85)

# Altina ekle:
		self.companionRenderTarget = CostumeRenderTarget()
		self.companionRenderTarget.SetParent(self)
		self.companionRenderTarget.SetSize(75, 75)
		self.companionRenderTarget.SetPosition(276, 311)
		self.companionRenderTarget.SetIndex(self.petRenderIndex)
		self.companionRenderTarget.Hide()


# CostumeShopWindow.__UpdatePreviewModel icinde ara:
			renderTarget.SelectModel(self.petRenderIndex, pet.value0)
			renderTarget.SetVisibility(self.petRenderIndex, True)

# Altina ekle:
			self.companionRenderTarget.Show()


# CostumeShopWindow.__UpdatePreviewModel icinde ara:
		else:
			renderTarget.SetVisibility(self.petRenderIndex, False)

# Altina ekle:
			self.companionRenderTarget.Hide()

