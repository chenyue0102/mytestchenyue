#pragma once
#include <mutex>
#include <set>

template<typename T>
class tsset
{
public:
	tsset()
		: m_mutex()
		, m_set()
	{

	}

	~tsset()
	{

	}

	bool insert(const T& t)
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		return m_set.insert(t).second;
	}

	bool insert(T&& t)
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		return m_set.insert(std::forward<T>(t)).second;
	}

	bool erase(const T& t)
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		return (0 != m_set.erase(t));
	}

	bool empty()const
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		return m_set.empty();
	}

	std::size_t size()const
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		return m_set.size();
	}

	void clear()
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		m_set.clear();
	}
private:
	mutable std::mutex m_mutex;
	std::set<T> m_set;
};

