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
	HANDLERSINFO handlersInfo;

	if (InitializerRoutine == nullptr)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	ZeroMemory(&handlersInfo, sizeof(handlersInfo));

	handlersInfo.pfnInitializer = InitializerRoutine;
	handlersInfo.pfnCleanup = CleanupRoutine;
	handlersInfo.lpContext = Context;

	AcquireSRWLockExclusive(&g_srwHandlers);
	g_handlers.push_back(handlersInfo);
	ReleaseSRWLockExclusive(&g_srwHandlers);

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
		SRWLocker<SRWLockExclusive> Locker(g_srwHandlers);

		for (std::list<HANDLERSINFO>::const_iterator Iterator = g_handlers.begin(); Iterator != g_handlers.end(); Iterator++)
		{
			if (Iterator->pfnInitializer != InitializerRoutine)
				continue;

			if (DoCleanup && Iterator->pfnCleanup != nullptr)
				Iterator->pfnCleanup(Iterator->lpContext);

			g_handlers.erase(Iterator);
			return TRUE;
		}
	}

	SetLastError(ERROR_FILE_NOT_FOUND);
	return FALSE;
}
