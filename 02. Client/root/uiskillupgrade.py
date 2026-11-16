# SkillUpgradeWindow.__CollectSkills icinde ara:
			power = []
			if self.interface:

# Altina ekle:
				power = self.interface.GetBuffiSkillsPower() or []


# SkillUpgradeWindow.OverInSkill icinde ara:
		skillIndex, grade, level, srcSlot = self.skills[index]
		if self.upgradeType == UPGRADE_BUFFI_SKILL:

# Altina ekle:
			wnd = self.interface.wndCompanion if self.interface else None


# SkillUpgradeWindow.OverOut icinde ara:
			if self.interface.tooltipSkill:
				self.interface.tooltipSkill.HideToolTip()

# Altina ekle:
			if self.interface.wndCompanion:
				self.interface.wndCompanion.HideBuffiSkillToolTip()

