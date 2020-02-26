/*
ִ������,���������������id,��ͬ����id,�ᰴ˳��ִ��
*/
#pragma once
#include <mutex>
#include <thread>
#include <list>
#include <vector>
#include <memory>
#include <unordered_map>
#include <condition_variable>
#include <functional>

typedef std::function<void()> TASK_JOB;
typedef std::size_t TASK_GROUPID;
static_assert(sizeof(TASK_GROUPID) == sizeof(void*), "");
class CTaskPool
{
	struct TaskInfo
	{
		TASK_JOB job;
		bool groupIdValid;
		TASK_GROUPID groupId;
	};
	typedef std::list<std::unique_ptr<TaskInfo>> TASK_INFO_ARRAY;
	struct ThreadInfo
	{
		std::thread t;
		std::mutex mtx;
		int index;					//�߳�index,���ڲ���m_curGroupIds
		bool groupIdValid;
		TASK_GROUPID groupId;
		TASK_INFO_ARRAY taskInfos;	//��������̵߳�����
		ThreadInfo()
			: t()
			, mtx()
			, index(0)
			, groupIdValid(false)
			, groupId(0)
			, taskInfos()
		{}
	};
	typedef std::vector<std::unique_ptr<ThreadInfo>> THREAD_INFO_ARRAY;
public:
	CTaskPool();
	~CTaskPool();
public:
	bool Open(unsigned int nPoolSize);
	bool Close();
	bool AddTask(const TASK_JOB &fun);
	bool AddOrderTask(const TASK_JOB &fun, TASK_GROUPID groupId);
private:
	bool InnerAddOrderTask(const TASK_JOB &fun, bool groupIdValid, TASK_GROUPID groupId);
	std::unique_ptr<TaskInfo> InnerGetTaskInfo(ThreadInfo& curThreadInfo);
	static bool innerCheckCurThreadTask(ThreadInfo & curThreadInfo);
	bool innerCheckTask();
	void TaskThread(ThreadInfo &threadInfo);
public:
	std::mutex m_mutex;
	std::condition_variable m_cv;
	THREAD_INFO_ARRAY m_threadInfos;			//�߳���Ϣ
	TASK_INFO_ARRAY m_taskInfos;				//����������Ϣ
	std::unordered_map<TASK_GROUPID, int> m_curGroupIds;//�洢�ĸ�group���ĸ��߳�ִ����,key:groupid value:m_threadInfos index
	volatile bool m_bExit;						//�˳����
};

