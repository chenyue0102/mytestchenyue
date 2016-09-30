#pragma once

struct INotifyTask
{
	virtual void NotifyTaskCompleted(long long llTaskID, bool bInterrupted) = 0;
};
