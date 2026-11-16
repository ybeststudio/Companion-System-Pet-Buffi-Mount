// Bul:
	//HEADER_GC_EMPTY							= 188,

// Degistir:
#ifdef ENABLE_BUFFI_SYSTEM
	HEADER_GC_BUFFI_USE_SKILL					= 188,
#else
	//HEADER_GC_EMPTY							= 188,
#endif


// Ara:
	BYTE bCaptcha[64*32];
	char szQuiz[256];
} TPacketGCAutoBanQuiz;

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
typedef struct SPacketGCBuffiUseSkill
{
	BYTE	bHeader;
	DWORD	dwVID;
	DWORD	dwSkillVnum;
	BYTE	bSkillLevel;
} TPacketGCBuffiUseSkill;
#endif


// Ara:
	POINT_UPBRINGING_DURATION,
	POINT_UPBRINGING_MAX_DURATION,
	POINT_UPBRINGING_BIRTHDAY,

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
	POINT_UPBRINGING_PET_TYPE,
#endif

