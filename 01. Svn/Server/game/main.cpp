// Dosyanin uygun bir yerine ekle:
#ifdef ENABLE_BUFFI_SYSTEM
#include "buffi_system.h"
#endif


// int main(int argc, char **argv) icinde:
// Ara:
	CBotCharacterManager botCharacter;

// Altina ekle:
#ifdef ENABLE_BUFFI_SYSTEM
	CBuffiManager buffi_manager;
#endif

