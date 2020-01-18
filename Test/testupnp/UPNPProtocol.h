#ifndef __UPNP_PROTOCOL_H__
#define __UPNP_PROTOCOL_H__
#include <string>
#include <vector>


//�汾��
struct UPNPDDDSpecVersion
{
	int major;
	int minor;

	UPNPDDDSpecVersion()
		: major()
		, minor()
	{}
};

//�豸��Ϣ
struct UPNPDDDService
{
	std::string serviceType;			//��������,urn:schemas-upnp-org:service:AVTransport:1
	std::string serviceId;				//�����ʶ��,����ʵ����Ψһ��ʶ,����һ�豸�����б���Ψһ��
	std::string SCPDURL;				//Service Control Protocol Description on URL,��ȡ���������ĵ���url
	std::string controlURL;				//������Ϳ�����Ϣ��URL
	std::string eventSubURL;			//���ķ����¼���URL
};

//device����
struct UPNPDDDDevice
{
	std::string deviceType;				//urn:schemas-upnp-org:device:MediaRenderer:1
	std::string presentationURL;		//�豸չʾ��URL,�Ǳ���
	std::string friendlyName;			//���û�չʾ����������
	std::string manufacturer;			//����������
	std::string manufacturerURL;		//������URL
	std::string modelDescription;		//���û��Ķ�����ϸ����,���128�ַ�,�Ǳ���
	std::string modelName;				//�ͺ�
	std::string modelURL;				//�ͺ���ϢURL,�Ǳ���
	std::string UDN;					//Ψһ�豸��,�豸UUID,��ʽ:uuid:F7CA5454-3F48-4390-8009-283ee448c1ab
	std::vector<UPNPDDDService> serviceList;//������Ϣ,xml���ӽڵ�����Ϊservice
};

//UPNP Device Description Document
//�豸�����ĵ�
struct UPNPDDDRoot
{
	UPNPDDDSpecVersion specVersion;		//version
	UPNPDDDDevice device;				//�豸��Ϣ
	std::string URLBase;				//�ṹ����url��Ҫƴ�ӵ�ͷ��,1.0�汾����,1.0���ϰ汾������,

	UPNPDDDRoot()
	{}
};
///////////////////////////////////////////////////
//����������
struct UPNPSDDArgument
{
	std::string name;					//��������,���32�ַ�,��Ӧ����-
	std::string direction;				//in����,out���,in��ǰ,out�ں�
	std::string relatedStateVariable;	//�������ͺ�ߵ�ĳ��״̬����
};

//������
struct UPNPSDDAction
{
	std::string name;					//��������,���32�ַ�,��Ӧ����-
	std::vector<UPNPSDDArgument> argumentList;//�����б�,xml�ڲ���Ŀ����Ϊargument
};

//�Ϸ�ֵ��Χ
struct UPNPSDDAllowedValueRange
{
	std::string minimum;				//��Сֵ
	std::string maximum;				//���ֵ
	std::string step;					//����
};

//����״̬
struct UPNPSDDServiceState
{
	std::string sendEvents;				//״̬����ֵ�����仯,�Ƿ������¼���Ϣ,�洢��xml������,no yes
	std::string name;					//״̬����,���32�ַ�,���ܰ���-,���̶�����X_��ͷ,��׼����Ĳ���X_,A_��ͷ
	std::string dataType;				//��������,string,i4,ui4,��
	std::vector<std::string> allowedValueList;//����Ĳ���ֵ,�Ƽ�ʹ��,xml�ֶ�����ΪallowedValue
	std::string defaultValue;			//�����ĳ�ֵ,�Ƽ�ʹ��
	UPNPSDDAllowedValueRange allowedValueRange;//������Χ,�Ƽ�ʹ��
};
//����,
//Service Description Document
//root name scpd
struct UPNPSDDRoot
{
	UPNPDDDSpecVersion specVersion;		//version
	std::vector<UPNPSDDAction> actionList;//�����б�,xml�ڲ���Ŀ����action
};

#endif