#pragma once
#include "TKSerializeExportDefine.h"

/************************************************************************/
/* 字符串类，std::string不能够跨dll边界，使用此类解决此问题                   */
/************************************************************************/
namespace SerializeExport
{

struct SerializeStringData;
class TKSERIALIZE_API CSerializeString
{
public:
	typedef size_t size_type;

	CSerializeString();
	CSerializeString(const CSerializeString &other);
	explicit CSerializeString(const char * copy);
	explicit CSerializeString(const char * str, size_type len);
	~CSerializeString();
public:
	CSerializeString& operator = (const char * copy);
	CSerializeString& operator = (const CSerializeString & copy);
public:
	CSerializeString& operator += (const char * suffix);

	// += operator. Maps to append
	CSerializeString& operator += (char single);

	// += operator. Maps to append
	CSerializeString& operator += (const CSerializeString & suffix);
public:
	const char * c_str() const;

	// Convert a TiXmlString into a char * (need not be null terminated).
	const char * data() const;

	// Return the length of a TiXmlString
	size_type length() const;

	// Alias for length()
	size_type size() const;

	// Checks if a TiXmlString is empty
	bool empty() const;

	// Return capacity of string
	size_type capacity() const;


	// single char extraction
	const char& at(size_type index) const;

	// [] operator
	char& operator [] (size_type index) const;

	// find a char in a string. Return TiXmlString::npos if not found
	size_type find(char lookup) const;

	// find a char in a string from an offset. Return TiXmlString::npos if not found
	size_type find(char tofind, size_type offset) const;

	void clear();

	/*	Function to reserve a big amount of data when we know we'll need it. Be aware that this
	function DOES NOT clear the content of the TiXmlString if any exists.
	*/
	void reserve(size_type cap);

	CSerializeString& assign(const char* str, size_type len);

	CSerializeString& append(const char* str, size_type len);

	void swap(CSerializeString& other);
private:
	SerializeStringData *m_pSerializeStringData;
};
}