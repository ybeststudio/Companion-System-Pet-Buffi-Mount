// void CPythonNetworkStream::GamePhase() icinde:
// Ara:
			case HEADER_GC_SPECIFIC_EFFECT:
				ret = RecvSpecificEffect();
				break;

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
			case HEADER_GC_BUFFI_USE_SKILL:
				ret = RecvBuffiUseSkill();
				break;
#endif

