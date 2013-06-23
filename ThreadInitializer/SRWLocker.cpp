#include "stdafx.h"
#include "SRWLocker.h"

void SRWLockExclusive::Lock(SRWLOCK &SRW)
{
	::AcquireSRWLockExclusive(&SRW);
}

void SRWLockExclusive::Unlock(SRWLOCK &SRW)
{
	::ReleaseSRWLockExclusive(&SRW);
}

void SRWLockShared::Lock(SRWLOCK &SRW)
{
	::AcquireSRWLockShared(&SRW);
}

void SRWLockShared::Unlock(SRWLOCK &SRW)
{
	::ReleaseSRWLockShared(&SRW);
}
