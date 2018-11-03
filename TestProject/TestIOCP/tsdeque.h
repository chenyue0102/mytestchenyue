#pragma once
#include <assert.h>
#include <mutex>
#include <deque>

template<typename T>
class tsdeque
{
public:
	tsdeque()
		: m_mutex()
		, m_deque()
	{

	}
	~tsdeque()
	{

	}
public:
	void push_back(const T& t)
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		m_deque.push_back(t);
	}

	void push_back(T&& t)
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		m_deque.push_back(std::forward<T>(t));
	}

	void pop_back(T& t)
	{
		bool bRes = try_pop_back(t);
		assert(bRes);
	}

	bool try_pop_back(T& t)
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		if (!m_deque.empty())
		{
			t = std::move(m_deque.back());
			m_deque.pop_back();
			return true;
		}
		else
		{
			return false;
		}
	}

	void push_front(const T& t)
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		m_deque.push_front(t);
	}

	void push_front(T&& t)
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		m_deque.push_front(std::forward<T>(t));
	}

	void pop_front(T& t)
	{
		bool bRes = try_pop_front(t);
		assert(bRes);
	}

	bool try_pop_front(T& t)
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		if (!m_deque.empty())
		{
			t = std::move(m_deque.front());
			m_deque.pop_front();
			return true;
		}
		else
		{
			return false;
		}
	}

	bool empty()const
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		return m_deque.empty();
	}

	std::size_t size()const
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		return m_deque.size();
	}

private:
	mutable std::mutex m_mutex;
	std::deque<T> m_deque;
};
