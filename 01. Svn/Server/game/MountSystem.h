// Ara:
		void Unmount(DWORD mobVnum);
		void DeleteMount(DWORD mobVnum);
		void DeleteMount(CMountActor* mountActor);

// Altina ekle:
#ifdef ENABLE_MOUNT_FOLLOWER_LEVEL
		void RefreshFollower();
#endif

