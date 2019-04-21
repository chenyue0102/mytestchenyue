// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� TESTLOADERDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// TESTLOADERDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef TESTLOADERDLL_EXPORTS
#define TESTLOADERDLL_API __declspec(dllexport)
#else
#define TESTLOADERDLL_API __declspec(dllimport)
#endif
#include "LoaderInterface.h"
#include "UnknownImp.h"

// �����Ǵ� testloaderdll.dll ������
class Ctestloaderdll : public UnknownImp<IPlugin>
{
public:
	Ctestloaderdll(void);
	virtual ~Ctestloaderdll();
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

extern TESTLOADERDLL_API int ntestloaderdll;

TESTLOADERDLL_API int fntestloaderdll(void);

extern "C"
{
int CreatePluginInterface(IPlugin **pp);
}
