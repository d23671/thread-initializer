#include "stdafx.h"

SRWLOCK InitializersInfoMutex = SRWLOCK_INIT;
std::list<INITIALIZER_INFO> InitializersInfo;
