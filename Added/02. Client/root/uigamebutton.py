if __USE_DYNAMIC_MODULE__:
	import pyapi

app = __import__(pyapi.GetModuleName("app"))
player = __import__(pyapi.GetModuleName("player"))
net = __import__(pyapi.GetModuleName("net"))

import ui
import constInfo
import uiBeginnerEvent


class GameButtonWindow(ui.ScriptWindow):
	BEGINNER_EVENT_BUTTON = False
	def __init__(self):
		self.leftStackBase = None
		ui.ScriptWindow.__init__(self)
		self.beginnerPopup = None
		self.__LoadWindow("UIScript/gamewindow.py")

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def __LoadWindow(self, filename):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, filename)

		except Exception, msg:
			import dbg
			dbg.TraceError("GameButtonWindow.LoadScript - %s" % (msg))
			app.Abort()
			return FALSE

		try:
			self.gameButtonDict = {
				"STATUS" : self.GetChild("StatusPlusButton"),
				"SKILL" : self.GetChild("SkillPlusButton"),
				"QUEST" : self.GetChild("QuestButton"),
				"BUILD" : self.GetChild("BuildGuildBuilding"),
				"EXIT_OBSERVER" : self.GetChild("ExitObserver"),
				"GUIDE" : self.GetChild("GuidelineButton"),
				"BEGINNER" : self.GetChild("BeginnerQuestButton"),
				"NOTIFICATION_HISTORY" : self.GetChild("NotificationHistoryButton"),
				"BUFFI" : self.GetChild("SkillBuffiPlusButton"),
			}


			self.gameButtonDict["EXIT_OBSERVER"].SetEvent(ui.__mem_func__(self.__OnClickExitObserver))

			if app.ENABLE_GAYA_SYSTEM:
				# bottom-left Statu Gelistir stack (gamewindow.py), already spaced
				posx, posy = self.gameButtonDict["BUILD"].GetGlobalPosition()
				self.gameButtonDict["BUILD"].SetPosition(posx, posy - 25 )

				posx, posy = self.gameButtonDict["EXIT_OBSERVER"].GetGlobalPosition()
				self.gameButtonDict["EXIT_OBSERVER"].SetPosition(posx, posy - 25 )

		except Exception, msg:
			import dbg
			dbg.TraceError("GameButtonWindow.LoadScript - %s" % (msg))
			app.Abort()
			return FALSE

		self.__HideAllGameButton()
		import advanced_options_runtime
		if advanced_options_runtime.Get("view_guideline", True):
			self.gameButtonDict["GUIDE"].Show()
		self.gameButtonDict["BEGINNER"].SetEvent(ui.__mem_func__(self.__OnClickBeginner))
		if self.BEGINNER_EVENT_BUTTON:
			self.gameButtonDict["BEGINNER"].Show()
		import advanced_option_notifications
		advanced_option_notifications.BindButton(self.gameButtonDict["NOTIFICATION_HISTORY"])
		self.SetObserverMode(player.IsObserverMode())
		return TRUE


	def Destroy(self):
		if self.beginnerPopup:
			self.beginnerPopup.Destroy()
			self.beginnerPopup = None

		for key in self.gameButtonDict:
			self.gameButtonDict[key].SetEvent(0)

		self.gameButtonDict={}


	def __OnClickBeginner(self):
		if self.beginnerPopup is None:
			self.beginnerPopup = uiBeginnerEvent.BeginnerEventWindow()
		self.beginnerPopup.Open()
	def SetButtonEvent(self, name, event):
		try:
			self.gameButtonDict[name].SetEvent(event)

		except Exception, msg:
			print "GameButtonWindow.LoadScript - %s" % (msg)
			app.Abort()
			return

	def ShowBuildButton(self):
		self.gameButtonDict["BUILD"].Show()

	def HideBuildButton(self):
		self.gameButtonDict["BUILD"].Hide()


	def CheckGameButton(self):

		if not self.IsShow():
			return

		statusPlusButton = self.gameButtonDict["STATUS"]
		skillPlusButton = self.gameButtonDict["SKILL"]

		if player.GetStatus(player.STAT) > 0:
			statusPlusButton.Show()
		else:
			statusPlusButton.Hide()

		if self.__IsSkillStat():
			skillPlusButton.Show()
		else:
			skillPlusButton.Hide()

		# Reference: GameButtonWindow.__OnClickBuffiSkill / SkillBuffiPlusButton ("Buffi'yi Yükselt"),
		buffiButton = self.gameButtonDict["BUFFI"]
		interface = constInfo.GetInterfaceInstance()
		companion = interface.wndCompanion if interface else None
		buffiSummoned = companion is not None and companion.buffiSummoned
		if buffiSummoned:
			buffiButton.Show()
		else:
			buffiButton.Hide()
		self.__ArrangeLeftStack()

	LEFT_STACK = ("STATUS", "SKILL", "BUFFI", "GUIDE", "NOTIFICATION_HISTORY", "BEGINNER")
	LEFT_STACK_STEP = 40

	def __ArrangeLeftStack(self):
		if not self.leftStackBase:
			self.leftStackBase = self.gameButtonDict["STATUS"].GetLocalPosition()
		(x, y) = self.leftStackBase
		for key in self.LEFT_STACK:
			button = self.gameButtonDict.get(key)
			if not button or not button.IsShow():
				continue
			if button.GetLocalPosition() != (x, y):
				button.SetPosition(x, y)
			y -= self.LEFT_STACK_STEP

	def OnUpdate(self):
		self.__ArrangeLeftStack()

	def __IsSkillStat(self):
		if player.GetStatus(player.SKILL_ACTIVE) > 0:
			return TRUE

		return FALSE

	def __OnClickExitObserver(self):
		net.SendChatPacket("/observer_exit")

	def __HideAllGameButton(self):
		for btn in self.gameButtonDict.values():
			btn.Hide()

	def SetObserverMode(self, isEnable):
		if isEnable:
			self.gameButtonDict["EXIT_OBSERVER"].Show()
		else:
			self.gameButtonDict["EXIT_OBSERVER"].Hide()

