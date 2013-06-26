#ifndef _THREADINITIALIZER_
#define _THREADINITIALIZER_

#if (_WIN32_WINNT >= 0x0600)

typedef void (CALLBACK *LPTHREAD_INITIALIZER_ROUTINE) (LPVOID Context);
typedef void (CALLBACK *LPTHREAD_INITIALIZER_CLEANUP) (LPVOID Context);

#ifdef __cplusplus
extern "C" {
#endif

BOOL
WINAPI
AddThreadInitializer(
	LPTHREAD_INITIALIZER_ROUTINE InitializerRoutine,
	LPVOID Context
	);

BOOL
WINAPI
AddThreadInitializerEx(
	LPTHREAD_INITIALIZER_ROUTINE InitializerRoutine,
	LPTHREAD_INITIALIZER_CLEANUP CleanupRoutine,
	LPVOID Context
	);

void
WINAPI
RemoveAllThreadInitializer(
	VOID
	);

BOOL
WINAPI
RemoveThreadInitializer(
	LPTHREAD_INITIALIZER_ROUTINE InitializerRoutine
	);

#ifdef __cplusplus
}
#endif

#endif // (_WIN32_WINNT >= 0x0600)

#endif /* _THREADINITIALIZER_ */
