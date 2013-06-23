#include "stdafx.h"
#include "SRWLocker.h"

SRWLocker::SRWLocker(SRWLOCK &SRW, BOOL Lock, BOOL LockExclusive) :
	SRW(SRW),
	Lock(LOCK::NONE)
{
	if (!Lock)
		return;

	if (LockExclusive)
		this->LockExclusive();
	else
		this->LockShared();
}

SRWLocker::~SRWLocker()
{
	Unlock();
}

void SRWLocker::LockExclusive()
{
	_ASSERTE(this->Lock == LOCK::NONE);
	::AcquireSRWLockExclusive(&this->SRW);
	this->Lock = LOCK::EXCLUSIVE;
}

void SRWLocker::LockShared()
{
	_ASSERTE(this->Lock == LOCK::NONE);
	::AcquireSRWLockShared(&this->SRW);
	this->Lock = LOCK::SHARED;
}

void SRWLocker::Unlock()
{
	switch (this->Lock)
	{
	case LOCK::SHARED:
		::ReleaseSRWLockShared(&this->SRW);
		break;
	case LOCK::EXCLUSIVE:
		::ReleaseSRWLockExclusive(&this->SRW);
		break;
	}

	this->Lock = LOCK::NONE;
}
