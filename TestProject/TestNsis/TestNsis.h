// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� TESTNSIS_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// TESTNSIS_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef TESTNSIS_EXPORTS
#define TESTNSIS_API __declspec(dllexport)
#else
#define TESTNSIS_API __declspec(dllimport)
#endif

// �����Ǵ� TestNsis.dll ������
class TESTNSIS_API CTestNsis {
public:
	CTestNsis(void);
	// TODO: �ڴ�������ķ�����
};

extern TESTNSIS_API int nTestNsis;

TESTNSIS_API int fnTestNsis(void);
