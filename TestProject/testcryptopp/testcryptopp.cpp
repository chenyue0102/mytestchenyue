// testcryptopp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include "des.h"
#include "aes.h"
#include "config.h"
#include "modes.h"
#include "filters.h"
#pragma comment(lib, "../lib/cryptlibD.lib")

using namespace CryptoPP;

std::string EncryptDES(const byte *key, const byte *iv, const std::string &data)
{
	std::string result;
	try
	{
		CFB_Mode<DES>::Encryption e;
		e.SetKeyWithIV(key, DES::MAX_KEYLENGTH, iv, DES::BLOCKSIZE);
		StringSource(data, true, new StreamTransformationFilter(e, new StringSink(result)));
	}
	catch (const CryptoPP::Exception& e)
	{
		e.what();
	}
	return result;
}

std::string DecryptDES(const byte *key, const byte *iv, const std::string &data)
{
	std::string result;
	try
	{
		CFB_Mode<DES>::Decryption  d;
		d.SetKeyWithIV(key, DES::MAX_KEYLENGTH, iv, DES::BLOCKSIZE);
		StringSource(data, true, new StreamTransformationFilter(d, new StringSink(result)));
	}
	catch (const CryptoPP::Exception& e)
	{
		e.what();
	}
	return result;
}

std::string EncryptAES(const byte *key, const byte*iv, const std::string &data)
{
	std::string result;
	try
	{
		CFB_Mode<AES>::Encryption e;
		e.SetKeyWithIV(key, AES::MAX_KEYLENGTH, iv, AES::BLOCKSIZE);
		StringSource(data, true, new StreamTransformationFilter(e, new StringSink(result)));
	}
	catch (const CryptoPP::Exception& e)
	{
		e.what();
	}
	return result;
}

std::string DecryptAES(const byte *key, const byte*iv, const std::string &data)
{
	std::string result;
	try
	{
		CFB_Mode<AES>::Decryption d;
		d.SetKeyWithIV(key, AES::MAX_KEYLENGTH, iv, AES::BLOCKSIZE);
		StringSource(data, true, new StreamTransformationFilter(d, new StringSink(result)));
	}
	catch (const CryptoPP::Exception& e)
	{
		e.what();
	}
	return result;
}

int main()
{
	const byte key[DES::MAX_KEYLENGTH] = { 0xb0, 0xef, 0xe2, 0xa0, 0xac, 0x95, 0xea, 0x3a };
	const byte iv[DES::BLOCKSIZE] = { 0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef};
	std::string strData = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
		, 0x00 };
	std::string e = EncryptDES(key, iv, strData);
	std::string d = DecryptDES(key, iv, e);
	assert(d == strData);

	const byte keyAES[AES::MAX_KEYLENGTH] = { 0xb0, 0xef, 0xe2, 0xa0, 0xac, 0x95, 0xea, 
		0x3a, 0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef,
		0xb0, 0xef, 0xe2, 0xa0, 0xac, 0x95, 0xea,
		0x3a, 0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef };
	const byte ivAES[AES::BLOCKSIZE] = { 0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef, 0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef };
	e = EncryptAES(key, iv, strData);
	d = DecryptAES(key, iv, e);
	assert(d == strData);
    return 0;
}

