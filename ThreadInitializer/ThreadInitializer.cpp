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
	INITIALIZER_INFO handlersInfo;

	if (InitializerRoutine == nullptr)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	ZeroMemory(&handlersInfo, sizeof(handlersInfo));

	handlersInfo.Initializer = InitializerRoutine;
	handlersInfo.Cleaner = CleanupRoutine;
	handlersInfo.Context = Context;

	AcquireSRWLockExclusive(&InitializersInfoMutex);
	InitializersInfo.push_back(handlersInfo);
	ReleaseSRWLockExclusive(&InitializersInfoMutex);

	return TRUE;
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
