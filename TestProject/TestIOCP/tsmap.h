#pragma once
#include <map>
#include <mutex>

template<typename KEY, typename VALUE>
class tsmap
{
public:
	tsmap();
	~tsmap();
public:
	bool insert(const std::pair<KEY, VALUE> &item)
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		return m_map.insert(item).second;
	}
private:
	std::mutex m_mutex;
	std::map<KEY, VALUE> m_map;
};

