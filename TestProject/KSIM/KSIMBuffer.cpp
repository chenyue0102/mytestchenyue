#include "KSIMBuffer.h"
#include <string>


namespace KSIM{
struct KSIMBufferData
{
	std::string buffer;
};
KSIMBuffer::KSIMBuffer()
	: m_pKSIMBufferData(new KSIMBufferData())
{

}

KSIMBuffer::KSIMBuffer(const KSIMBuffer &other)
	: m_pKSIMBufferData(new KSIMBufferData())
{
	m_pKSIMBufferData->buffer = other.m_pKSIMBufferData->buffer;
}

KSIMBuffer::KSIMBuffer(const char *data, unsigned int len)
	: m_pKSIMBufferData(new KSIMBufferData())
{
	assign(data, len);
}

KSIMBuffer::~KSIMBuffer()
{
	delete m_pKSIMBufferData;
	m_pKSIMBufferData = nullptr;
}

const char * KSIMBuffer::data() const
{
	return m_pKSIMBufferData->buffer.data();
}

unsigned int KSIMBuffer::size() const
{
	return m_pKSIMBufferData->buffer.size();
}

bool KSIMBuffer::empty() const
{
	return m_pKSIMBufferData->buffer.empty();
}

unsigned int KSIMBuffer::capacity() const
{
	return m_pKSIMBufferData->buffer.capacity();
}

void KSIMBuffer::clear()
{
	return m_pKSIMBufferData->buffer.clear();
}

void KSIMBuffer::reserve(unsigned int cap)
{
	return m_pKSIMBufferData->buffer.reserve(cap);
}

KSIMBuffer& KSIMBuffer::assign(const char* str, unsigned int len)
{
	if (nullptr != str && len > 0)
	{
		m_pKSIMBufferData->buffer.assign(str, len);
	}
	return *this;
}

KSIMBuffer& KSIMBuffer::append(const char* str, unsigned int len)
{
	if (nullptr != str && len > 0)
	{
		m_pKSIMBufferData->buffer.append(str, len);
	}
	return *this;
}

void KSIMBuffer::swap(KSIMBuffer& other)
{
	return m_pKSIMBufferData->buffer.swap(other.m_pKSIMBufferData->buffer);
}

}