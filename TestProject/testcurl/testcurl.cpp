// testcurl.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define OPENSSL_NO_DEPRECATED_0_9_8
#include <iostream>
#include <vector>
#include <curl/curl.h>
#include <curl/easy.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/asn1.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string>

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	const char *fileName = (const char *)userdata;
	FILE *f = fopen(fileName, "ab+");
	fwrite(ptr, 1, size * nmemb, f);
	fclose(f);
	return size * nmemb;
}

int debug_callback(CURL *curl, curl_infotype type, char *data, size_t size, void *clinetp)
{
	std::string str(data, size);

	std::cout << str << std::endl;
	return 0;
}

void testcurl()
{
	const char *fileName = "d:/1.png";
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, "https://www.baidu.com/img/bd_logo1.png");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fileName);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "json");

	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
	curl_easy_setopt(curl, CURLOPT_CAINFO, "d:\\ca\\test.crt");

	curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, &debug_callback);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

	curl_easy_perform(curl);

	curl_easy_cleanup(curl);
}

void test_rsa_encrypt(const std::vector<uint8_t> &key)
{
	//RSA *rsa = publicKeyToRSA(key.data());
}
std::vector<uint8_t> pri_buf, pub_buf;
#define RSA_BITS 2048
void test_rsa_gen()
{
	//const EVP_CIPHER *cipher = EVP_get_cipherbynid(EVP_PKEY_RSA);
	EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
	int ret = 0;
	if ((ret = EVP_PKEY_keygen_init(ctx)) <= 0)
	{
		return;
	}
	if ((ret = EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, RSA_BITS)) <= 0)
	{
		return;
	}
	BIGNUM *bn = BN_new();
	ret = BN_set_word(bn, RSA_F4);
	if ((ret = EVP_PKEY_CTX_set1_rsa_keygen_pubexp(ctx, bn)) <= 0)
	{
		return;
	}
	EVP_PKEY *pkey = NULL;
	if ((ret = EVP_PKEY_keygen(ctx, &pkey)) != 1)
	{
		return;
	}
	
	{
		BIO *pri = BIO_new(BIO_s_mem());
		BIO *pub = BIO_new(BIO_s_mem());
		ret = PEM_write_bio_PrivateKey(pri, pkey, NULL, NULL, 0, NULL, NULL);
		ret = PEM_write_bio_PUBKEY(pub, pkey);

		int pri_length = BIO_pending(pri);
		int pub_length = BIO_pending(pub);
		pri_buf.resize(pri_length);
		pub_buf.resize(pub_length);
		BIO_read(pri, pri_buf.data(), pri_length);
		BIO_read(pub, pub_buf.data(), pub_length);
		BIO_free_all(pri);
		BIO_free_all(pub);
	}

	{
		BIO *pri_file = BIO_new(BIO_s_file());
		BIO *pub_file = BIO_new(BIO_s_file());
		BIO_write_filename(pri_file, (void*)"./pri.pem");
		BIO_write_filename(pub_file, (void*)"./pub.pem");
		ret = PEM_write_bio_PrivateKey(pri_file, pkey, NULL, NULL, 0, NULL, NULL);
		ret = PEM_write_bio_PUBKEY(pub_file, pkey);
		BIO_free_all(pri_file);
		BIO_free_all(pub_file);
	}

	EVP_PKEY_free(pkey);
	EVP_PKEY_CTX_free(ctx);
	BN_clear_free(bn);
	//CRYPTO_cleanup_all_ex_data();
}
std::string strencrypt;
void test_rsa_encrypt()
{
	EVP_PKEY *pkey = 0;
	{
		BIO *bo = BIO_new(BIO_s_mem());
		BIO_write(bo, pub_buf.data(), pub_buf.size());
		PEM_read_bio_PUBKEY(bo, &pkey, 0, 0);
		BIO_free_all(bo);
	}
	int ret = 0;
	EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, NULL);
	if ((ret = EVP_PKEY_encrypt_init(ctx)) <= 0)
	{
		return;
	}
	//if ((ret = EVP_PKEY_CTX_ctrl_str(ctx, "rsa_padding_mode", "pkcs1")) <= 0) //man pkeyutl
	if ((ret = EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING)) <= 0)
	{
		return;
	}
	if ((ret = EVP_PKEY_CTX_set_rsa_oaep_md(ctx, EVP_sha256())) <= 0)
	{
		return;
	}
	if ((ret = EVP_PKEY_CTX_set_rsa_mgf1_md(ctx, EVP_sha256())) <= 0)
	{
		return;
	}
	std::string in, out;
	in = "abcd1234";
	size_t outlen = 0;
	
	if ((ret = EVP_PKEY_encrypt(ctx, NULL, &outlen, (const unsigned char*)in.data(), in.size())) <= 0) 
	{
		return;
	}
	strencrypt.resize(outlen);
	if ((ret = EVP_PKEY_encrypt(ctx, (unsigned char*)strencrypt.data(), &outlen, (const unsigned char*)in.data(), in.size())) <= 0)
	{
		return;
	}

	EVP_PKEY_free(pkey);
	EVP_PKEY_CTX_free(ctx);
}

void test_rsa_decrypt()
{
	EVP_PKEY *pkey = 0;
	{
		BIO *bo = BIO_new(BIO_s_mem());
		BIO_write(bo, pri_buf.data(), pri_buf.size());
		PEM_read_bio_PrivateKey(bo, &pkey, 0, 0);
		BIO_free_all(bo);
	}
	int ret = 0;
	EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, NULL);
	if ((ret = EVP_PKEY_decrypt_init(ctx)) <= 0)
	{
		return;
	}
	//if ((ret = EVP_PKEY_CTX_ctrl_str(ctx, "rsa_padding_mode", "pkcs1")) <= 0) //man pkeyutl
	if ((ret = EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING)) <= 0)
	{
		return;
	}
	if ((ret = EVP_PKEY_CTX_set_rsa_oaep_md(ctx, EVP_sha256())) <= 0)
	{
		return;
	}
	if ((ret = EVP_PKEY_CTX_set_rsa_mgf1_md(ctx, EVP_sha256())) <= 0)
	{
		return;
	}
	std::string out;
	size_t outlen = 0;

	if ((ret = EVP_PKEY_decrypt(ctx, NULL, &outlen, (const unsigned char*)strencrypt.data(), strencrypt.size())) <= 0)
	{
		return;
	}
	out.resize(outlen);
	if ((ret = EVP_PKEY_decrypt(ctx, (unsigned char*)out.data(), &outlen, (const unsigned char*)strencrypt.data(), strencrypt.size())) <= 0)
	{
		return;
	}

	EVP_PKEY_free(pkey);
	EVP_PKEY_CTX_free(ctx);
}
std::string strSign;
const char *sign_msg = "hello, sign";
void test_sign()
{
	EVP_PKEY *pkey = 0;
	{
		BIO *bo = BIO_new(BIO_s_mem());
		BIO_write(bo, pri_buf.data(), pri_buf.size());
		PEM_read_bio_PrivateKey(bo, &pkey, 0, 0);
		BIO_free_all(bo);
	}
	const EVP_MD *md = EVP_get_digestbyname("SHA256");
	EVP_PKEY_CTX *sign_ctx = NULL;
	EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
	if (EVP_DigestSignInit(md_ctx, &sign_ctx, md, NULL, pkey) <= 0)
	{
		return;
	}
	if (EVP_PKEY_CTX_set_rsa_padding(sign_ctx, RSA_PKCS1_PSS_PADDING) <= 0)
	{
		return;
	}
	size_t signLen = 0;
	if (EVP_DigestSign(md_ctx, NULL, &signLen, NULL, 0) <= 0)
	{
		return;
	}
	strSign.resize(signLen);
	if (EVP_DigestSign(md_ctx, (unsigned char*)strSign.data(), &signLen, (const unsigned char*)sign_msg, strlen(sign_msg)) <= 0)
	{
		return;
	}

	EVP_PKEY_free(pkey);
	//EVP_PKEY_CTX_free(sign_ctx);
	EVP_MD_CTX_free(md_ctx);
}

void test_verify()
{
	const EVP_MD *md = EVP_get_digestbyname("SHA256");
	EVP_PKEY *pkey = 0;
	{
		BIO *bo = BIO_new(BIO_s_mem());
		BIO_write(bo, pub_buf.data(), pub_buf.size());
		PEM_read_bio_PUBKEY(bo, &pkey, 0, 0);
		BIO_free_all(bo);
	}
	EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
	if (EVP_DigestInit(md_ctx, md) <= 0)
	{
		return;
	}
	if (EVP_DigestUpdate(md_ctx, sign_msg, strlen(sign_msg)) <= 0)
	{
		return;
	}
	std::string m;
	unsigned int len;
	m.resize(EVP_MAX_MD_SIZE);
	if (EVP_DigestFinal_ex(md_ctx, (unsigned char*)m.data(), &len) <= 0)
	{
		return;
	}
	EVP_PKEY_CTX *verify_ctx = EVP_PKEY_CTX_new(pkey, NULL);
	if (EVP_PKEY_verify_init(verify_ctx) <= 0)
	{
		return;
	}
	if (EVP_PKEY_CTX_set_rsa_padding(verify_ctx, RSA_PKCS1_PSS_PADDING) <= 0)
	{
		return;
	}
	if (EVP_PKEY_CTX_set_signature_md(verify_ctx, md) <= 0)
	{
		return;
	}
	int verified = EVP_PKEY_verify(verify_ctx, (const unsigned char *)strSign.data(), strSign.size(), (const unsigned char *)m.data(), len);
	assert(1 == verified);
	EVP_PKEY_free(pkey);
	EVP_PKEY_CTX_free(verify_ctx);
	EVP_MD_CTX_free(md_ctx);
}

int openssl_error_print(const char *str, size_t len, void *u) 
{
	for (int i = 0; i < len; i++)
	{
		_fputchar(str[i]);
	}
	return len;
}

std::vector<uint8_t> dumpbio(BIO *bio)
{
	int l = BIO_pending(bio);
	std::vector<uint8_t> v;
	v.resize(l);
	BIO_read(bio, v.data(), l);
	return v;
}
//return find result
bool get_hash_from_asn1(const unsigned char *asn1, int total_length, std::vector<uint8_t> &v)
{
	long len = 0;
	int asn1_tag = 0;
	int asn1_class = 0;
	int j = 0;
	while (total_length > 0) {
		const unsigned char *valueBegin = asn1;
		asn1_tag = 0;
		asn1_class = 0;
		j = ASN1_get_object(&valueBegin, &len, &asn1_tag, &asn1_class, total_length);
		if (j & 0x80) {
			return false;
		}
		if (j & V_ASN1_CONSTRUCTED) {
			const unsigned char *child_asn1 = valueBegin;
			int child_total_length = len;
			long child_value_length;
			if (get_hash_from_asn1(child_asn1, child_total_length, v))
			{
				return true;
			}
		}
		//asn1_class == V_ASN1_UNIVERSAL 
		if (asn1_tag == V_ASN1_OCTET_STRING)
		{
			v.insert(v.begin(), valueBegin, valueBegin + len);
			return true;
		}
		int distance = std::distance(asn1, valueBegin);
		asn1 = valueBegin + len;
		total_length -= len + distance;
	}
	return false;
}

std::vector<uint8_t> get_asn1_body_data(const unsigned char* asn1, int total_length)
{
	std::vector<uint8_t> data;

	long len = 0;
	int asn1_tag = 0;
	int asn1_class = 0;
	const unsigned char *data_begin = asn1;
	int j = ASN1_get_object(&data_begin, &len, &asn1_tag, &asn1_class, total_length);
	if (j & 0x80) {
		return data;
	}
	int distance = std::distance(asn1, data_begin);
	total_length = len;
	asn1 = data_begin;
	j = ASN1_get_object(&data_begin, &len, &asn1_tag, &asn1_class, total_length);
	if (j & 0x80) {
		return data;
	}
	data.insert(data.begin(), asn1, data_begin + len);//header和body
	return data;
}
const unsigned char *g_begin = NULL;
int g_level = 0;
char g_buf[1024];
const unsigned char * get_sign_begin(const unsigned char *asn1, int total_length)
{
	const unsigned char *curBegin = asn1;
	long len = 0;
	int asn1_tag = 0;
	int asn1_class = 0;
	int j = 0;
	while (total_length > 0) {
		const unsigned char *valueBegin = curBegin;
		asn1_tag = 0;
		asn1_class = 0;
		j = ASN1_get_object(&valueBegin, &len, &asn1_tag, &asn1_class, total_length);
		if (j & 0x80) {
			break;
		}
		std::string clazz;
		if (j & V_ASN1_CONSTRUCTED)
		{
			clazz += "cons";
		}
		else if (j&V_ASN1_PRIVATE)
		{
			clazz += "prim";
		}
		std::string type;
		switch (asn1_tag)
		{
		case V_ASN1_NULL:
			type = "NULL";
			break;
		case V_ASN1_OBJECT:
			type = "OBJECT";
			break;
		case V_ASN1_SEQUENCE:
			type = "SEQUENCE";
			break;
		case V_ASN1_BIT_STRING:
			type = "BIT STRING";
			break;
		case V_ASN1_OCTET_STRING:
			type = "OCTET STRING";
			break;
		}
		sprintf(g_buf, "%5d:d=%d hl=%d l=%5d %s:%s\n", std::distance(g_begin, curBegin), g_level, std::distance(curBegin, valueBegin), len,
			clazz.c_str(), type.c_str());
		OutputDebugStringA(g_buf);
		if (j & V_ASN1_CONSTRUCTED) {
			g_level++;
			const unsigned char *p = get_sign_begin(valueBegin, len);
			g_level--;
			if (p != NULL)
			{
				return p;
			}
		}
		int distance = std::distance(curBegin, valueBegin);
		curBegin = valueBegin + len;
		total_length -= len + distance;
	}
	return NULL;
}

void test_read_crt()
{
	//GlobalSign Root CA.crt
	const char crt[] = R"(-----BEGIN CERTIFICATE-----
MIIDdTCCAl2gAwIBAgILBAAAAAABFUtaw5QwDQYJKoZIhvcNAQEFBQAwVzELMAkG
A1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv
b3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw05ODA5MDExMjAw
MDBaFw0yODAxMjgxMjAwMDBaMFcxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i
YWxTaWduIG52LXNhMRAwDgYDVQQLEwdSb290IENBMRswGQYDVQQDExJHbG9iYWxT
aWduIFJvb3QgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDaDuaZ
jc6j40+Kfvvxi4Mla+pIH/EqsLmVEQS98GPR4mdmzxzdzxtIK+6NiY6arymAZavp
xy0Sy6scTHAHoT0KMM0VjU/43dSMUBUc71DuxC73/OlS8pF94G3VNTCOXkNz8kHp
1Wrjsok6Vjk4bwY8iGlbKk3Fp1S4bInMm/k8yuX9ifUSPJJ4ltbcdG6TRGHRjcdG
snUOhugZitVtbNV4FpWi6cgKOOvyJBNPc1STE4U6G7weNLWLBYy5d4ux2x8gkasJ
U26Qzns3dLlwR5EiUWMWea6xrkEmCMgZK9FGqkjWZCrXgzT/LCrBbBlDSgeF59N8
9iFo7+ryUp9/k5DPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8E
BTADAQH/MB0GA1UdDgQWBBRge2YaRQ2XyolQL30EzTSo//z9SzANBgkqhkiG9w0B
AQUFAAOCAQEA1nPnfE920I2/7LqivjTFKDK1fPxsnCwrvQmeU79rXqoRSLblCKOz
yj1hTdNGCbM+w6DjY1Ub8rrvrTnhQ7k4o+YviiY776BQVvnGCv04zcQLcFGUl5gE
38NflNUVyRRBnMRddWQVDf9VMOyGj/8N7yy5Y0b2qvzfvGn9LhJIZJrglfCm7ymP
AbEVtQwdpf5pLGkkeB6zpxxxYu7KyJesF12KwvhHhm4qxFYxldBniYUr+WymXUad
DKqC5JlR3XC321Y9YeRq4VzW9v493kHMB65jUr9TU/Qr6cf9tveCX4XSQRjbgbME
HMUfpIBvFSDJ3gyICh3WZlXi/EjJKSZp4A==
-----END CERTIFICATE-----)";
	//GlobalSign.crt
	const char crt2[] = R"(-----BEGIN CERTIFICATE-----
MIIETjCCAzagAwIBAgINAe5fFp3/lzUrZGXWajANBgkqhkiG9w0BAQsFADBXMQsw
CQYDVQQGEwJCRTEZMBcGA1UEChMQR2xvYmFsU2lnbiBudi1zYTEQMA4GA1UECxMH
Um9vdCBDQTEbMBkGA1UEAxMSR2xvYmFsU2lnbiBSb290IENBMB4XDTE4MDkxOTAw
MDAwMFoXDTI4MDEyODEyMDAwMFowTDEgMB4GA1UECxMXR2xvYmFsU2lnbiBSb290
IENBIC0gUjMxEzARBgNVBAoTCkdsb2JhbFNpZ24xEzARBgNVBAMTCkdsb2JhbFNp
Z24wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDMJXaQeQZ4Ihb1wIO2
hMoonv0FdhHFrYhy/EYCQ8eyip0EXyTLLkvhYIJG4VKrDIFHcGzdZNHr9SyjD4I9
DCuul9e2FIYQebs7E4B3jAjhSdJqYi8fXvqWaN+JJ5U4nwbXPsnLJlkNc96wyOkm
DoMVxu9bi9IEYMpJpij2aTv2y8gokeWdimFXN6x0FNx04Druci8unPvQu7/1PQDh
BjPogiuuU6Y6FnOM3UEOIDrAtKeh6bJPkC4yYOlXy7kEkmho5TgmYHWyn3f/kRTv
riBJ/K1AFUjRAjFhGV64l++td7dkmnq/X8ET75ti+w1s4FRpFqkD2m7pg5NxdsZp
hYIXAgMBAAGjggEiMIIBHjAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB
/zAdBgNVHQ4EFgQUj/BLf6guRSSuTVD6Y5qL3uLdG7wwHwYDVR0jBBgwFoAUYHtm
GkUNl8qJUC99BM00qP/8/UswPQYIKwYBBQUHAQEEMTAvMC0GCCsGAQUFBzABhiFo
dHRwOi8vb2NzcC5nbG9iYWxzaWduLmNvbS9yb290cjEwMwYDVR0fBCwwKjAooCag
JIYiaHR0cDovL2NybC5nbG9iYWxzaWduLmNvbS9yb290LmNybDBHBgNVHSAEQDA+
MDwGBFUdIAAwNDAyBggrBgEFBQcCARYmaHR0cHM6Ly93d3cuZ2xvYmFsc2lnbi5j
b20vcmVwb3NpdG9yeS8wDQYJKoZIhvcNAQELBQADggEBACNw6c/ivvVZrpRCb8RD
M6rNPzq5ZBfyYgZLSPFAiAYXof6r0V88xjPy847dHx0+zBpgmYILrMf8fpqHKqV9
D6ZX7qw7aoXW3r1AY/itpsiIsBL89kHfDwmXHjjqU5++BfQ+6tOfUBJ2vgmLwgtI
fR4uUfaNU9OrH0Abio7tfftPeVZwXwzTjhuzp3ANNyuXlava4BJrHEDOxcd+7cJi
WOx37XMiwor1hkOIreoTbv3Y/kIvuX1erRjvlJDKPSerJpSZdcfL03v3ykzTr1Eh
kluEfSufFT90y1HonoMOFm8b50bOI7355KKL0jlrqnkckSziYSQtjipIcJDEHsXo
4HA=
-----END CERTIFICATE-----)";
	int ret;
	BIO *bio = BIO_new(BIO_s_mem());
	BIO_write(bio, crt, strlen(crt));
	X509 *x509 = PEM_read_bio_X509(bio, NULL, NULL, NULL);
	X509_NAME *name = X509_get_subject_name(x509);
	char *sub = X509_NAME_oneline(name, NULL, 0);
	char *issure = X509_NAME_oneline(X509_get_issuer_name(x509), NULL, 0);
	ASN1_INTEGER *ai = X509_get_serialNumber(x509);
	BIGNUM *bn = ASN1_INTEGER_to_BN(ai, NULL);
	char *tmp = BN_bn2hex(bn);
	EVP_PKEY *pkey = X509_get_pubkey(x509);

	BIO *print_io = BIO_new(BIO_s_mem());
	if (EVP_PKEY_print_public(print_io, pkey, 1, NULL) <= 0) {
		return;
	}
	unsigned char *txt = NULL;
	ret = i2d_PublicKey(pkey, &txt);
	int print_length = BIO_pending(print_io);
	std::string s;
	s.resize(print_length);
	BIO_read(print_io, (char*)s.data(), print_length);
	BIO_free(print_io);
	
	const ASN1_BIT_STRING * psig = NULL;
	const X509_ALGOR *palg = NULL;
	X509_get0_signature(&psig, &palg, x509);
	//const X509_ALGOR *algor = X509_get0_tbs_sigalg(x509);

	BIO *sign_io = BIO_new(BIO_s_mem());
	if (X509_signature_print(sign_io, palg, psig) <= 0) {
		return;
	}
	int sign_length = BIO_pending(sign_io);
	std::string sign;
	sign.resize(sign_length);
	BIO_read(sign_io, (char*)sign.data(), sign_length);
	BIO_free(sign_io);

	
	int l = ASN1_STRING_length(psig);
	auto data = ASN1_STRING_get0_data(psig);//签名
	std::vector<uint8_t> decrypt_sign;		//解码后签名
	std::vector<uint8_t> decrypt_hash;		//签名中的hash值
	{
		RSA *rsa = EVP_PKEY_get1_RSA(pkey);
		decrypt_sign.resize(l, 0xff);
		if ((ret = RSA_public_decrypt(l, data, decrypt_sign.data(), rsa, RSA_PKCS1_PADDING)) <= 0) {
			return;
		}
		decrypt_sign.resize(ret);
		RSA_free(rsa);

		const unsigned char *pasn1 = decrypt_sign.data();
		BIO *asn1_dump_bio = BIO_new(BIO_s_mem());
		if (ASN1_parse_dump(asn1_dump_bio, pasn1, decrypt_sign.size(), 0, 0) <= 0)
		{
			return;
		}
		std::string asn1_dump;
		asn1_dump.resize(BIO_pending(asn1_dump_bio));
		BIO_read(asn1_dump_bio, (void*)asn1_dump.data(), asn1_dump.size());
		if (!get_hash_from_asn1(decrypt_sign.data(), decrypt_sign.size(), decrypt_hash)) {
			return;
		}


		BIO_write(bio, crt, strlen(crt));
		char *name = NULL, *header = NULL;
		unsigned char *data = NULL;
		long pem_len = 0;
		if (PEM_read_bio_ex(bio, &name, &header, &data, &pem_len, PEM_FLAG_EAY_COMPATIBLE) <= 0) {
			return;
		}

		if (ASN1_parse_dump(asn1_dump_bio, data, pem_len, 0, 0) <= 0)
		{
			return;
		}
		std::string data_dump;
		data_dump.resize(BIO_pending(asn1_dump_bio));
		BIO_read(asn1_dump_bio, (void*)data_dump.data(), data_dump.size());
		BIO_free(asn1_dump_bio);
		
		g_begin = data;
		get_sign_begin(data, pem_len);

		std::vector<uint8_t> body_data = get_asn1_body_data(data, pem_len);
		const EVP_MD *sha1 = EVP_get_digestbyname("SHA1");
		EVP_MD_CTX *sha1_ctx = EVP_MD_CTX_new();
		if (EVP_MD_CTX_init(sha1_ctx) <= 0) {
			return;
		}
		EVP_DigestInit_ex(sha1_ctx, sha1, NULL);
		if (EVP_DigestUpdate(sha1_ctx, body_data.data(), body_data.size()) <= 0) {
			return;
		}
		unsigned char body_hash[20];
		unsigned int body_hash_length = sizeof(body_hash);
		if (EVP_DigestFinal(sha1_ctx, body_hash, &body_hash_length) <= 0) {
			return;
		}
		EVP_MD_CTX_free(sha1_ctx);
		assert(0 == memcmp(body_hash, decrypt_hash.data(), decrypt_hash.size()));
#if 0
		unsigned char hash_buf[EVP_MAX_MD_SIZE];
		unsigned int hash_len;
		if (X509_digest(x509, EVP_sha1(), hash_buf, &hash_len) < 0) {
			return;
		}
		assert(hash_len == decrypt_sign.size());
		if (0 != memcmp(hash_buf, decrypt_sign.data(), hash_len))
		{
			return;
		}
#endif
#if 0
		const char public_key[] = R"(-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA2g7mmY3Oo+NPin778YuD
JWvqSB/xKrC5lREEvfBj0eJnZs8c3c8bSCvujYmOmq8pgGWr6cctEsurHExwB6E9
CjDNFY1P+N3UjFAVHO9Q7sQu9/zpUvKRfeBt1TUwjl5Dc/JB6dVq47KJOlY5OG8G
PIhpWypNxadUuGyJzJv5PMrl/Yn1EjySeJbW3HRuk0Rh0Y3HRrJ1DoboGYrVbWzV
eBaVounICjjr8iQTT3NUkxOFOhu8HjS1iwWMuXeLsdsfIJGrCVNukM57N3S5cEeR
IlFjFnmusa5BJgjIGSvRRqpI1mQq14M0/ywqwWwZQ0oHhefTfPYhaO/q8lKff5OQ
zwIDAQAB
-----END PUBLIC KEY-----
)";
		BIO *bio_public_key = BIO_new_mem_buf(public_key, -1);
		RSA *rsa = 0;
		rsa = PEM_read_bio_RSA_PUBKEY(bio_public_key, &rsa, NULL, NULL);
			
		decrypt_data.resize(l, 0xff);
		if ((ret = RSA_public_decrypt(l, data, decrypt_data.data(), rsa, RSA_PKCS1_PADDING)) <= 0) {
			return;
		}
		BIO_free(bio_public_key);
		RSA_free(rsa);
#endif
	}
	auto ext = X509_get0_extensions(x509);

	EVP_PKEY_free(pkey);
	BN_free(bn);
	OPENSSL_free(tmp);
	BIO_free(bio);
	X509_free(x509);
	
}
void testrsa()
{
	ERR_print_errors_cb(&openssl_error_print, NULL);
	test_rsa_gen();
	test_rsa_encrypt();
	test_rsa_decrypt();
	test_sign();
	test_verify();
	test_read_crt();
}
#if 0
void testrsa1()
{
	//RSA *rsa = RSA_new();
	//BIGNUM *bn = BN_new();
	//int ret = BN_set_word(bn, RSA_F4);
	//ret = RSA_generate_key_ex(rsa, RSA_BITS, bn, NULL);
	RSA *rsa = RSA_generate_key(RSA_BITS, RSA_F4, NULL, NULL);
	BIO *pri = BIO_new(BIO_s_mem());
	BIO *pub = BIO_new(BIO_s_mem());
	PEM_write_bio_RSAPrivateKey(pri, rsa, NULL, NULL, 0, NULL, NULL);
	PEM_write_bio_RSA_PUBKEY(pub, rsa);

	BIO *pri_file = BIO_new(BIO_s_file());
	BIO *pub_file = BIO_new(BIO_s_file());
	BIO_write_filename(pri_file, (void*)"./pri.pem");
	BIO_write_filename(pub_file, (void*)"./pub.pem");
	PEM_write_bio_RSAPrivateKey(pri_file, rsa, NULL, NULL, 0, NULL, NULL);
	PEM_write_bio_RSA_PUBKEY(pub_file, rsa);
	BIO_free_all(pri_file);
	BIO_free_all(pub_file);



	int pri_length = BIO_pending(pri);
	int pub_length = BIO_pending(pub);
	std::vector<uint8_t> pri_buf, pub_buf;
	pri_buf.resize(pri_length);
	pub_buf.resize(pub_length);

	BIO_read(pri, pri_buf.data(), pri_length);
	BIO_read(pub, pub_buf.data(), pub_length);

	//BN_clear_free(bn);
	RSA_free(rsa);
	BIO_free_all(pri);
	BIO_free_all(pub);
	//CRYPTO_cleanup_all_ex_data();
}
#endif
int main()
{
	testrsa();
	testcurl();
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
