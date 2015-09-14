#pragma once
#include <string>
#include "EnumSerialize.h"

#ifndef interface
#define interface struct
#endif

interface ISerialize
{
	virtual EnumSerializeType GetSerializeType() = 0;
	virtual bool SetSerializeType(EnumSerializeType SerializeType) = 0;
	virtual const void * GetBuffer() = 0;
	virtual unsigned long GetBufferLength() = 0;
	
	virtual bool Serialize(bool &Value) = 0;
	virtual bool Serialize(char &Value) = 0;
	virtual bool Serialize(unsigned char &Value) = 0;
	virtual bool Serialize(int &Value) = 0;
	virtual bool Serialize(unsigned int &Value) = 0;
	virtual bool Serialize(long &Value) = 0;
	virtual bool Serialize(unsigned long &Value) = 0;
	virtual bool Serialize(long long &Value) = 0;
	virtual bool Serialize(unsigned long long &Value) = 0;
	virtual bool Serialize(float &Value) = 0;
	virtual bool Serialize(double &Value) = 0;
	virtual bool Serialize(char *pstr, unsigned long ulBufferLen) = 0;
};