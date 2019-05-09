// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� TESTLOADERDLL2_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// TESTLOADERDLL2_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef TESTLOADERDLL2_EXPORTS
#define TESTLOADERDLL2_API __declspec(dllexport)
#else
#define TESTLOADERDLL2_API __declspec(dllimport)
#endif
#include "LoaderInterface.h"
#include "UnknownImp.h"

// �����Ǵ� testloaderdll2.dll ������
class Ctestloaderdll2 : public UnknownImp<IPlugin>
{
public:
	Ctestloaderdll2(void);
	virtual ~Ctestloaderdll2();
public:
	//��ʼ�����
	virtual HRESULT STDMETHODCALLTYPE Init(ILoader *loader)override;
	//�������
	virtual HRESULT STDMETHODCALLTYPE Destroy()override;
	//�����ӿ�
	virtual HRESULT STDMETHODCALLTYPE QueryPluginInterface(REFIID iid, void **ppvObject)override;
	//�Ƿ�����ж��
	virtual HRESULT STDMETHODCALLTYPE CallUnload()override;
	//��ȡ�����Ϣ
	virtual HRESULT STDMETHODCALLTYPE GetPluginInfo(PluginInfo *pluginInfo)override;
	//��ȡ���������
	virtual HRESULT STDMETHODCALLTYPE GetDependentPlugin(GUID *pluginIds, INT32 *count)override;
};

extern TESTLOADERDLL2_API int ntestloaderdll2;

TESTLOADERDLL2_API int fntestloaderdll2(void);
extern "C"
{
	int CreatePluginInterface(IPlugin **pp);
}