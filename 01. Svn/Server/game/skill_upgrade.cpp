// Dosyanin uygun bir yerine ekle:
#ifdef ENABLE_BUFFI_SKILL_BOOK
#include "buffi_system.h"
#endif


// Ara:
			return READ_STOP;
		return ch->GetSkillLevel(dwSkill) != iLevel ? READ_SUCCESS : READ_FAIL;
	}

// Altina ekle:
#ifdef ENABLE_BUFFI_SKILL_BOOK
	// ------------------------------------------------------------------ Buffi skills
	int BuffiSkillIndex(DWORD dwSkill)
	{
		for (int i = 0; i < BUFFI_SKILL_COUNT; ++i)
			if (CBuffiActor::GetSkillVnum(i) == dwSkill)
				return i;
		return -1;
	}

	std::string BuffiReadFlag(int idx)
	{
		char szFlag[32];
		snprintf(szFlag, sizeof(szFlag), "buffi.read_time%d", idx);
		return szFlag;
	}

	int BuffiNeedBooks(int iLevel)
	{
		if (iLevel < 30)
			return iLevel - 19;
		return aiGrandMasterSkillBookMaxCount[MINMAX(0, iLevel - 30, 9)];
	}

	EReadResult ReadBuffi(LPCHARACTER ch, DWORD dwSkill, const SUpgradeOption& opt)
	{
		CBuffiActor* pActor = CBuffiManager::instance().Get(ch);
		const int idx = BuffiSkillIndex(dwSkill);
		if (!pActor || idx < 0)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Please summon your Buffi before doing that."));
			return READ_STOP;
		}

		const int iLevel = pActor->GetSkillLevel(idx);
		if (iLevel < 20 || iLevel >= 40)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, iLevel >= 40 ? LC_TEXT("This skill is already at maximum level.") : LC_TEXT("This skill's level is not high enough to be trained with a Book."));
			return READ_STOP;
		}

		if (opt.bMaster)	// Buffi Mastery Book / Stone: one level step without delay or chance
			return pActor->UseMasterBook(idx) ? READ_SUCCESS : READ_STOP;

		const bool bMasterLevel = iLevel < 30;
		const DWORD dwBook = bMasterLevel ? (DWORD) BUFFI_SKILL_BOOK_VNUM : (DWORD) SOUL_STONE_VNUM;
		LPITEM book = ch->FindSpecifyItem(dwBook);
		if (!book)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, bMasterLevel ? LC_TEXT("You don't have the required skill book.") : LC_TEXT("You need a Soul Stone to train this skill further."));
			return READ_STOP;
		}

		const time_t tNextRead = ch->GetQuestFlag(BuffiReadFlag(idx));
		int iCost = 0;
		if (!bMasterLevel && !PaySoulStoneGrade(ch, iLevel, opt, iCost))
			return READ_STOP;
		if (!PrepareRead(ch, tNextRead, opt))
			return READ_STOP;

		ConsumeDelayAffect(ch, tNextRead);
		const bool bBonus = ch->FindAffect(AFFECT_SKILL_BOOK_BONUS) != NULL;
		if (bBonus)
			ch->RemoveAffect(AFFECT_SKILL_BOOK_BONUS);
		if (iCost)
			ch->UpdateAlignment(-iCost);
		book->SetCount(book->GetCount() - 1);

		int iProgress = pActor->GetBookProgress(idx);
		bool bLevelUp = false;
		if (bMasterLevel)
		{
			if (bBonus || number(1, 100) > 65)
				bLevelUp = ++iProgress >= BuffiNeedBooks(iLevel);
			ch->SetQuestFlag(BuffiReadFlag(idx), get_global_time() + number(SKILLBOOK_DELAY_MIN, SKILLBOOK_DELAY_MAX));
		}
		else
		{
			bLevelUp = RollGrandMaster(++iProgress, iLevel, bBonus);
			ch->SetQuestFlag(BuffiReadFlag(idx), get_global_time() + number(28800, 43200));
		}

		if (bLevelUp)
		{
			pActor->OnBookLevelUp(idx);
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Your Buffi's skill has improved."));
			return READ_SUCCESS;
		}

		pActor->SetBookProgress(idx, iProgress);
		if (bMasterLevel)
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You read a Buffi skill book (%d/%d)."), iProgress, BuffiNeedBooks(iLevel));
		else
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Training has failed. Please try again later."));
		return READ_FAIL;
	}
#endif


// Ara:
			iMaxed = dwBook ? 0 : 1;
			iNeed = 1;
		}

// Altina ekle:
#ifdef ENABLE_BUFFI_SKILL_BOOK
		else if (iType == UPGRADE_BUFFI_SKILL)
		{
			CBuffiActor* pActor = CBuffiManager::instance().Get(ch);
			const int idx = BuffiSkillIndex(dwSkill);
			if (pActor && idx >= 0)
			{
				const int iLevel = pActor->GetSkillLevel(idx);
				tNextRead = ch->GetQuestFlag(BuffiReadFlag(idx));
				if (iLevel >= 40)
					iMaxed = 1;
				else if (iLevel >= 20)
				{
					dwBook = iLevel < 30 ? (DWORD) BUFFI_SKILL_BOOK_VNUM : (DWORD) SOUL_STONE_VNUM;
					iCount = ch->CountSpecifyItem(dwBook);
					iNeed = BuffiNeedBooks(iLevel);
					iProgress = MIN(iNeed, pActor->GetBookProgress(idx));
				}
			}
		}
#endif


// ACMD(do_upgrade_skill) icinde:
// Ara:
		{
			case UPGRADE_STANDARD_SKILL:	eResult = ReadStandard(ch, uSkill, opt); break;
			case UPGRADE_PASSIVE_SKILL:		eResult = ReadPassive(ch, uSkill, opt); break;

// Altina ekle:
#ifdef ENABLE_BUFFI_SKILL_BOOK
			case UPGRADE_BUFFI_SKILL:		eResult = ReadBuffi(ch, uSkill, opt); break;
#endif

