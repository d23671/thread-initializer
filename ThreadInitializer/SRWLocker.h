#pragma once

template<class Lock>
class SRWLocker
{
public:
	SRWLocker(SRWLOCK &SRW) :
		SRW(SRW)
	{
		Lock::Lock(this->SRW);
	}

	~SRWLocker()
	{
		Lock::Unlock(this->SRW);
	}
private:
	SRWLOCK &SRW;
private:
	SRWLocker(const SRWLocker<Lock> &source);
	SRWLocker<Lock> & operator=(const SRWLocker<Lock> &source);
};

class SRWLockExclusive
{
public:
	static void Lock(SRWLOCK &SRW);
	static void Unlock(SRWLOCK &SRW);
};

class SRWLockShared
{
public:
	static void Lock(SRWLOCK &SRW);
	static void Unlock(SRWLOCK &SRW);
};
