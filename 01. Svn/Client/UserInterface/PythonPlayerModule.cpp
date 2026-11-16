// Ara:
		pPet->skillData.aSkillInfo[2].bLevel,
		pPet->skillData.aSkillInfo[2].dwCooltime);
}

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
PyObject *playerGetPetType(PyObject *poSelf, PyObject *poArgs)
{
	int iPetID;
	if (!PyTuple_GetInteger(poArgs, 0, &iPetID))
		return Py_BadArgument();

	CPythonPlayer::TPetData* pPet = nullptr;
	CPythonPlayer::Instance().GetPetInfo(iPetID, &pPet);
	return Py_BuildValue("i", pPet ? (int)pPet->GetType() : 0);
}

// (open slot count, ((skill, level, cooltime) x PET_SKILL_COUNT_MAX)); slots >= open count are locked
PyObject *playerGetPetSkillSlots(PyObject *poSelf, PyObject *poArgs)
{
	int iPetID;
	if (!PyTuple_GetInteger(poArgs, 0, &iPetID))
		return Py_BadArgument();

	CPythonPlayer::TPetData* pPet = nullptr;
	CPythonPlayer::Instance().GetPetInfo(iPetID, &pPet);

	PyObject* slots = PyTuple_New(PET_SKILL_COUNT_MAX);
	for (int i = 0; i < PET_SKILL_COUNT_MAX; ++i)
	{
		if (pPet)
			PyTuple_SetItem(slots, i, Py_BuildValue("(iii)", pPet->skillData.aSkillInfo[i].bSkill, pPet->skillData.aSkillInfo[i].bLevel, pPet->skillData.aSkillInfo[i].dwCooltime));
		else
			PyTuple_SetItem(slots, i, Py_BuildValue("(iii)", 0, 0, 0));
	}

	return Py_BuildValue("(iN)", pPet ? pPet->skillData.bSkillCount : 0, slots);
}
#endif


// void initPlayer() icinde:
// Ara:
		{ "GetPetItemVNumInBag", playerGetPetItemVNumInBag, METH_VARARGS },
		{ "GetPetSkill", playerGetPetSkill, METH_VARARGS },
		{ "GetPetSkillByIndex", playerGetPetSkillByIndex, METH_VARARGS },

// Altina ekle:
#ifdef ENABLE_GROWTH_PET_RENEWAL
		{ "GetPetSkillSlots", playerGetPetSkillSlots, METH_VARARGS },
		{ "GetPetType", playerGetPetType, METH_VARARGS },
#endif

