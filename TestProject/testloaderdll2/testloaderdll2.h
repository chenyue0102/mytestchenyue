// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 TESTLOADERDLL2_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// TESTLOADERDLL2_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef TESTLOADERDLL2_EXPORTS
#define TESTLOADERDLL2_API __declspec(dllexport)
#else
#define TESTLOADERDLL2_API __declspec(dllimport)
#endif
#include "LoaderInterface.h"
#include "UnknownImp.h"

// 此类是从 testloaderdll2.dll 导出的
class Ctestloaderdll2 : public UnknownImp<IPlugin>
{
public:
	Ctestloaderdll2(void);
	virtual ~Ctestloaderdll2();
public:
	//初始化组件
	virtual HRESULT STDMETHODCALLTYPE Init(ILoader *loader)override;
	//销毁组件
	virtual HRESULT STDMETHODCALLTYPE Destroy()override;
	//创建接口
	virtual HRESULT STDMETHODCALLTYPE QueryPluginInterface(REFIID iid, void **ppvObject)override;
	//是否允许卸载
	virtual HRESULT STDMETHODCALLTYPE CallUnload()override;
	//获取组件信息
	virtual HRESULT STDMETHODCALLTYPE GetPluginInfo(PluginInfo *pluginInfo)override;
	//获取依赖的组件
	virtual HRESULT STDMETHODCALLTYPE GetDependentPlugin(GUID *pluginIds, INT32 *count)override;
};

extern TESTLOADERDLL2_API int ntestloaderdll2;

TESTLOADERDLL2_API int fntestloaderdll2(void);
extern "C"
{
	int CreatePluginInterface(IPlugin **pp);
}