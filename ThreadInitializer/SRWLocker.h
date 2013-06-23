#pragma once

class SRWLocker
{
public:
	SRWLocker(SRWLOCK &SRW, BOOL Lock = TRUE, BOOL LockExclusive = FALSE);
	~SRWLocker();
public:
	void LockExclusive();
	void LockShared();
	void Unlock();
private:
	enum class LOCK
	{
		NONE,
		SHARED,
		EXCLUSIVE
	};
private:
	SRWLOCK &SRW;
	LOCK Lock;
private:
	SRWLocker & operator=(const SRWLocker &source);
};
