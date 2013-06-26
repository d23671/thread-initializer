#include "stdafx.h"
#include "SRWLocker.h"
#include "ThreadInitializer.h"

///////////////////////////////////////////////////////////////////////////////
// Handler Registration Functions (export)

BOOL WINAPI AddThreadInitializer(LPTHREAD_INITIALIZER_ROUTINE InitializerRoutine, LPVOID Context)
{
	return AddThreadInitializerEx(InitializerRoutine, nullptr, Context);
}

BOOL WINAPI AddThreadInitializerEx(LPTHREAD_INITIALIZER_ROUTINE InitializerRoutine, LPTHREAD_INITIALIZER_CLEANUP CleanupRoutine, LPVOID Context)
{
	INITIALIZER_INFO InitializerInfo;

	if (InitializerRoutine == nullptr)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	ZeroMemory(&InitializerInfo, sizeof(InitializerInfo));

	InitializerInfo.Initializer = InitializerRoutine;
	InitializerInfo.Cleaner = CleanupRoutine;
	InitializerInfo.Context = Context;

	SRWLocker<SRWLockExclusive> Locker(InitializersInfoMutex);

	InitializersInfo.push_back(InitializerInfo);

	return TRUE;
}

void WINAPI RemoveAllThreadInitializer(VOID)
{
	SRWLocker<SRWLockExclusive> Locker(InitializersInfoMutex);

	for (std::list<INITIALIZER_INFO>::const_reverse_iterator Iterator = InitializersInfo.rbegin(); Iterator != InitializersInfo.rend(); Iterator++)
	{
		if (Iterator->Cleaner != nullptr)
			Iterator->Cleaner(Iterator->Context);
	}

	InitializersInfo.clear();
}

BOOL WINAPI RemoveThreadInitializer(LPTHREAD_INITIALIZER_ROUTINE InitializerRoutine, BOOL DoCleanup)
{
	if (InitializerRoutine == nullptr)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	{
		SRWLocker<SRWLockExclusive> Locker(InitializersInfoMutex);

		for (std::list<INITIALIZER_INFO>::const_iterator Iterator = InitializersInfo.begin(); Iterator != InitializersInfo.end(); Iterator++)
		{
			if (Iterator->Initializer != InitializerRoutine)
				continue;

			if (DoCleanup && Iterator->Cleaner != nullptr)
				Iterator->Cleaner(Iterator->Context);

			InitializersInfo.erase(Iterator);
			return TRUE;
		}
	}

	SetLastError(ERROR_FILE_NOT_FOUND);
	return FALSE;
}
