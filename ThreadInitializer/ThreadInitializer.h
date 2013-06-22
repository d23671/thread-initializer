#ifndef _THREADINITIALIZER_
#define _THREADINITIALIZER_

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

#ifdef __cplusplus
}
#endif

#endif /* _THREADINITIALIZER_ */
