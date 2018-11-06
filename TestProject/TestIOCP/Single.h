#pragma once
#include <mutex>
#include <memory>

template< typename T >
class CSingle
{
public:
	static T& Instance();

private:
	static void MakeInstance();
	static std::unique_ptr<T> m_pInstance;

private:
	CSingle();
	CSingle(const CSingle&);

	static std::once_flag  m_once_flag;
};

template<class T> std::once_flag CSingle<T>::m_once_flag;
template<class T> std::unique_ptr<T> CSingle<T>::m_pInstance;

template <class T> 
T& CSingle<T>::Instance()
{
	std::call_once(m_once_flag, &MakeInstance);
	return *m_pInstance;
}

template <class T>
inline void CSingle<T>::MakeInstance()
{
	m_pInstance.reset(new T);
}

