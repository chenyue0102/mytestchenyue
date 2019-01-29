#ifndef _SMARTPTR_H_
#define _SMARTPTR_H_

template<typename T>
class SmartPtr
{
public:
	SmartPtr()
		: p(nullptr)
	{
		
	}
	SmartPtr(T *_p)
		: p(_p)
	{
		if (nullptr != p)
		{
			p->AddRef();
		}
	}
	~SmartPtr()
	{
		if (nullptr != p)
		{
			p->Release();
		}
	}
public:
	operator T*()const
	{
		return p;
	}
	T& operator*()const
	{
		return *p;
	}
	T** operator&()
	{
		return &p;
	}
	T* operator->()
	{
		return p;
	}
	bool operator!()
	{
		return (nullptr == p);
	}
	void Swap(SmartPtr &other)
	{
		T *pTemp = p;
		p = other.p;
		other.p = pTemp;
	}
	T* operator=(T *_p)
	{
		if (p != _p)
		{
			SmartPtr(_p).Swap(*this);
		}
		return p;
	}
	T* operator=(SmartPtr<T> &other)
	{
		if (p != other.p)
		{
			SmartPtr(other.p).Swap(*this);
		}
		return p;
	}
private:
	T *p;
};
#endif
