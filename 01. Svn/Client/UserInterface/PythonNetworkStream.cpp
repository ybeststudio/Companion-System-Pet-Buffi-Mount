// Ara:
			Set(HEADER_GC_DIG_MOTION, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDigMotion), STATIC_SIZE_PACKET));
			Set(HEADER_GC_DAMAGE_INFO, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDamageInfo), STATIC_SIZE_PACKET));
			Set(HEADER_GC_SPECIFIC_EFFECT, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCSpecificEffect), STATIC_SIZE_PACKET));

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
			Set(HEADER_GC_BUFFI_USE_SKILL, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCBuffiUseSkill), STATIC_SIZE_PACKET));
#endif

