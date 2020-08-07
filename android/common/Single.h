#ifndef _SINGLE_H_
#define _SINGLE_H_
#include <mutex>
#include <memory>

template<typename T>
class Single
{
public:
	static T& instance()
	{
		std::call_once(m_onceFlag, &makeInstance);
		return *Single::m_pInstance;
	}
	static void destroy()
	{
		if (m_pInstance)
		{
			m_pInstance.reset();
		}
	}
private:
	Single() = delete;
	static void makeInstance()
	{
		Single::m_pInstance.reset(new T());
	}
private:
	static std::once_flag m_onceFlag;
	static std::unique_ptr<T> m_pInstance;
};

template<typename T>
std::once_flag Single<T>::m_onceFlag;

template<typename T>
std::unique_ptr<T> Single<T>::m_pInstance;


#endif
