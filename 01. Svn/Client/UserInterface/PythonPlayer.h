// Ara:
			DWORD GetHP() { return dwPoints[POINT_UPBRINGING_PET_HP]; }
			DWORD GetSP() { return dwPoints[POINT_UPBRINGING_PET_SP]; }
			DWORD GetDef() { return dwPoints[POINT_UPBRINGING_PET_DEF_GRADE]; }

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
			DWORD GetType() { return dwPoints[POINT_UPBRINGING_PET_TYPE]; }
#endif

