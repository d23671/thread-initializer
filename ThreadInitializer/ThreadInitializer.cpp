#include "stdafx.h"
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
