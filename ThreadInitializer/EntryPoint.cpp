#include "stdafx.h"
#include "SRWLocker.h"

///////////////////////////////////////////////////////////////////////////////
// Entry Point

BOOL APIENTRY DllMain(HMODULE /* hModule */, DWORD ul_reason_for_call, LPVOID /* lpReserved */)
{
	switch (ul_reason_for_call)
	{
	case DLL_THREAD_ATTACH:
		{
			SRWLocker<SRWLockShared> Locker(InitializersInfoMutex);

			for (std::list<INITIALIZER_INFO>::const_iterator Iterator = InitializersInfo.begin(); Iterator != InitializersInfo.end(); Iterator++)
				Iterator->Initializer(Iterator->Context);
		}
		break;
	}

	return TRUE;
}
