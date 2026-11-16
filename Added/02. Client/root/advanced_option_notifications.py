import os
import ui
import app
import wndMgr
import time
import uiScriptLocale

CATEGORIES = ("system", "dungeon", "guild", "item", "mining", "fishing", "battle_pass", "market_sales", "item_expired", "companion_expired", "alchemy_expired", "auto_cape")
LABELS = {
	"system": uiScriptLocale.NOTIFY_SYSTEM,
	"dungeon": uiScriptLocale.NOTIFY_DUNGEON,
	"guild": uiScriptLocale.NOTIFY_GUILD,
	"item": uiScriptLocale.NOTIFY_ITEM,
	"mining": uiScriptLocale.NOTIFY_MINING,
	"fishing": uiScriptLocale.NOTIFY_FISHING,
	"battle_pass": uiScriptLocale.NOTIFY_BATTLE_PASS,
	"market_sales": uiScriptLocale.NOTIFY_MARKET_SALES,
	"auto_cape": uiScriptLocale.NOTIFY_AUTO_CAPE,
	"item_expired": uiScriptLocale.NOTIFY_ITEM_EXPIRED,
	"companion_expired": uiScriptLocale.NOTIFY_COMPANION_EXPIRED,
	"alchemy_expired": uiScriptLocale.NOTIFY_ALCHEMY_EXPIRED,
}
MAX_RECORDS = 200
_records = []
_history = None
_button = None
_filterDialog = None
_toast = None
import userData
_filename = userData.GetPath("advanced_notifications.json")

try:
	text_type = unicode
except NameError:
	text_type = str

def _Runtime():
	import advanced_options_runtime
	return advanced_options_runtime

def _Text(text):
	if isinstance(text, text_type): return text
	page = app.GetDefaultCodePage()
	return text.decode("cp%d" % page, "replace")

def _Client(text):
	page = app.GetDefaultCodePage()
	return _Text(text).encode("cp%d" % page, "replace")

def _Escape(text):
	return text.replace(u"\\", u"\\\\").replace(u"\t", u"\\t").replace(u"\n", u"\\n")

def _Unescape(text):
	return text.replace(u"\\n", u"\n").replace(u"\\t", u"\t").replace(u"\\\\", u"\\")

def Load(filename=None):
	# own settings file.
	global _filename
	if filename is not None: _filename = filename
	del _records[:]
	try:
		stream = open(_filename, "rb")
	except IOError:
		return
	try:
		lines = stream.readlines()
	finally:
		stream.close()
	for raw in lines[-MAX_RECORDS:]:
		try:
			line = raw.decode("utf-8").rstrip(u"\r\n")
			when, category, text = line.split(u"\t", 2)
			if category not in CATEGORIES: continue
			_records.append((float(when), category, _Unescape(text)[:2048]))
		except (ValueError, TypeError, UnicodeDecodeError):
			continue

def Save():
	stream = open(_filename, "wb")
	try:
		for when, category, text in _records:
			line = u"%r\t%s\t%s\n" % (when, category, _Escape(text))
			stream.write(line.encode("utf-8"))
	finally:
		stream.close()

def Visible(category):
	settings = _Runtime()
	if category == "dungeon" and settings.Get("hide_dungeon_announcement", False): return False
	if category == "guild" and not settings.Get("show_guild_join_notification", True): return False
	return not settings.Get("hidden_notification_"+category, False)

def Record(category, text, when=None, popup=False):
	if category not in CATEGORIES: category = "system"
	text = _Text(text)[:2048]
	if not text: return False
	_records.append((time.time() if when is None else float(when), category, text))
	del _records[:-MAX_RECORDS]
	Save()
	ApplyVisibility()
	if _history and _history.IsShow(): _history.Refresh()
	visible = Visible(category)
	if popup and visible and _toast:
		_toast.message.SetText(_Client(text.replace("\n"," ")[:48]))
		_toast.expires = time.time()+8
		_toast.Show()
	return visible

def Records(): return list(_records)

def Clear():
	del _records[:]
	Save()
	if _history: _history.Refresh()
	ApplyVisibility()

def _MakeButton(ui, parent, text, x, y, callback):
	button = ui.Button()
	if parent is not None: button.SetParent(parent)
	button.SetPosition(x,y)
	path = "d:/ymir work/ui/game/advanced_game_options/"
	button.SetUpVisual(path+"btn_0.png"); button.SetOverVisual(path+"btn_1.png"); button.SetDownVisual(path+"btn_2.png")
	button.SetText(text); button.SetEvent(callback); button.Show()
	return button

def Start():
	global _toast
	if _toast: return
	Load()
	class Toast(ui.Board):
		def __init__(self):
			ui.Board.__init__(self)
			self.SetSize(320,45); self.expires=0
			self.message=ui.TextLine(); self.message.SetParent(self)
			self.message.SetPosition(12,15); self.message.Show(); self.Hide()
		def OnUpdate(self):
			if time.time() >= self.expires: self.Hide()
	_toast=Toast()
	ApplyVisibility()

def BindButton(button):
	global _button
	_button = button
	ApplyVisibility()

def ApplyVisibility():
	wnd = wndMgr
	if _toast and wnd: _toast.SetPosition(max(0,wnd.GetScreenWidth()-330), 190)
	if not _button: return
	if not _Runtime().Get("view_notification_history", True):
		_button.Hide()
		if _history: _history.Hide()
	elif _records: _button.Show()
	else: _button.Hide()

def _RelativeTime(when):
	import localeInfo
	delta = max(0, int(time.time() - when))
	if delta < 60: return localeInfo.NOTIFICATION_AGO_NOW
	if delta < 3600: return localeInfo.NOTIFICATION_AGO_MINUTES % (delta // 60)
	if delta < 86400: return localeInfo.NOTIFICATION_AGO_HOURS % (delta // 3600)
	return localeInfo.NOTIFICATION_AGO_DAYS % (delta // 86400)

ROW_COUNT = 11
HISTORY_SIZE = (457, 359)
HEADER_COLOR = 0xFFF0D08A
ROW_TEXT_COLOR = 0xFFD7D7D7
ROW_TIME_COLOR = 0xFFC3B08A

def OpenHistory():
	global _history
	if _history:
		_history.scroll = 0; _history.Refresh(); _history.Show(); _history.SetTop(); return
	def line(parent, x, y, color, center = False):
		text = ui.TextLine(); text.SetParent(parent); text.SetPosition(x, y)
		text.SetVerticalAlignCenter()
		if center: text.SetHorizontalAlignCenter()
		text.SetPackedFontColor(color); text.Show()
		return text
	class History(ui.BoardWithTitleBar):
		def __init__(self):
			ui.BoardWithTitleBar.__init__(self)
			self.scroll = 0
			self.SetSize(*HISTORY_SIZE); self.SetTitleName(uiScriptLocale.NOTIFY_HISTORY_TITLE)
			self.AddFlag("movable"); self.AddFlag("float"); self.SetCenterPosition(); self.SetCloseEvent(self.Hide)
			self.headerText = line(self, 23, 38, HEADER_COLOR); self.headerText.SetText(uiScriptLocale.NOTIFY_HISTORY_MESSAGE)
			self.headerTime = line(self, 371, 38, HEADER_COLOR, True); self.headerTime.SetText(uiScriptLocale.NOTIFY_HISTORY_TIME)
			self.headerLine = ui.Bar(); self.headerLine.SetParent(self); self.headerLine.SetPosition(10, 47)
			self.headerLine.SetSize(HISTORY_SIZE[0] - 20, 1); self.headerLine.SetColor(0xFF2D2519); self.headerLine.Show()
			self.textLines = []; self.timeLines = []
			for i in range(ROW_COUNT):
				y = 67 + i * 25
				self.textLines.append(line(self, 23, y, ROW_TEXT_COLOR))
				self.timeLines.append(line(self, 366, y, ROW_TIME_COLOR, True))
			button = ui.Button(); button.SetParent(self)
			button.SetUpVisual("d:/ymir work/ui/public/large_button_01.sub")
			button.SetOverVisual("d:/ymir work/ui/public/large_button_02.sub")
			button.SetDownVisual("d:/ymir work/ui/public/large_button_03.sub")
			button.SetText(uiScriptLocale.NOTIFY_HISTORY_CLEAR); button.SetEvent(Clear)
			button.SetPosition((HISTORY_SIZE[0] - button.GetWidth()) // 2, 332); button.Show()
			self.buttons = [button]
			self.lastRefresh = 0
			self.Refresh()
		def Refresh(self):
			rows = list(reversed(_records))
			self.scroll = max(0, min(self.scroll, max(0, len(rows) - ROW_COUNT)))
			rows = rows[self.scroll:self.scroll + ROW_COUNT]
			for index in range(ROW_COUNT):
				if index >= len(rows):
					self.textLines[index].SetText(""); self.timeLines[index].SetText(""); continue
				when, category, text = rows[index]
				text = text.replace("\r"," ").replace("\n"," ")[:60]
				self.textLines[index].SetText(_Client(text))
				self.timeLines[index].SetText(_RelativeTime(when))
			self.lastRefresh = time.time()
		def OnUpdate(self):
			if time.time() - self.lastRefresh > 10: self.Refresh()	# "N dakika once" follows the clock
		def OnRunMouseWheel(self, delta):
			self.scroll += -1 if delta > 0 else 1
			self.Refresh(); return True
		def OnPressEscapeKey(self): self.Hide(); return True
	_history = History(); _history.Show()

def OpenFilters():
	global _filterDialog
	if _filterDialog:
		_filterDialog.Refresh(); _filterDialog.Show(); _filterDialog.SetTop(); return
	class Filters(ui.BoardWithTitleBar):
		def __init__(self):
			ui.BoardWithTitleBar.__init__(self)
			self.SetSize(540, 90 + ((len(CATEGORIES)+1)//2)*35); self.SetTitleName(uiScriptLocale.NOTIFY_FILTER_TITLE)
			self.AddFlag("movable"); self.SetCenterPosition(); self.SetCloseEvent(self.Hide)
			self.buttons = []
			for i,category in enumerate(CATEGORIES):
				self.buttons.append((category,_MakeButton(ui,self,LABELS[category],20+(i%2)*260,45+(i//2)*35,lambda c=category:self.Toggle(c))))
			self.Refresh()
		def Refresh(self):
			for category,button in self.buttons:
				hidden = _Runtime().Get("hidden_notification_"+category,False)
				button.SetText(LABELS[category]+(uiScriptLocale.NOTIFY_HIDDEN if hidden else uiScriptLocale.NOTIFY_VISIBLE))
		def Toggle(self, category):
			key = "hidden_notification_"+category
			_Runtime().Set(key,not _Runtime().Get(key,False)); self.Refresh()
		def OnPressEscapeKey(self): self.Hide(); return True
	_filterDialog = Filters(); _filterDialog.Show()

def Stop(keepButton=False):
	global _history, _button, _filterDialog, _toast
	for window in (_history,_filterDialog,_toast):
		if window:
			window.Hide()
			window.Destroy()
	_history = _filterDialog = _toast = None
	if not keepButton:
		_button = None
