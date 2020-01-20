/*
����http���󣬶�����
*/
#pragma once
#include <string>

class UPNPHttp
{
public:
	UPNPHttp();
	~UPNPHttp();
public:
	//���������URL host �� port
	void setHttpInfo(const std::string &host, unsigned short port, unsigned int scope_id);
	//���ÿ���url path
	void setControlURLPath(const std::string &path);
	void setRegURLPath(const std::string &path);
	//����soap����
	int soapPostSubmit(const std::string &action, const std::string &body, const std::string &httpVersion, std::string &result);
	int sendAndReceive(const std::string &data, std::string &result);
	int regCallback(const std::string &event, const std::string & callbackURL, int timeout);
private:
	//������ip
	std::string mHost;
	//�������˿�
	unsigned short mPort;
	unsigned int mScopeId;
	//����action��url
	std::string mControlURL;
	std::string mRegURL;
};

