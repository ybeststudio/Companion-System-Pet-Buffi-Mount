// Ara:
		bool RecvRefineInformationPacketNew();
		bool RecvSpecialEffect();
		bool RecvSpecificEffect();

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
		bool RecvBuffiUseSkill();
#endif

