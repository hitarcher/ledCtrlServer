#pragma once

#ifdef RN_API_EXPORTS
#define RN_API __declspec(dllexport) WINAPI
#else
#define RN_API __declspec(dllimport) WINAPI
#endif

typedef DWORD RN_RESULT;
typedef DWORD RN_STATUS;

//enum LOGLEVEL
//{
//	LOGLEVEL_NULL = 0,
//	LOGLEVEL_ERR = 1,
//	LOGLEVEL_ENTER = 2,
//	LOGLEVEL_DETAIL = 3
//};
#define RN_OK   0

/* example */
//==================================================
// ��������_expFunction
// ���  ����
// ����  ����
// ����ֵ��RN_RESULT
//==================================================
//EXTERN_C RN_RESULT RN_API _expFunction(void);

//==================================================
// ��������_startread ��ʼ��ȡ������Ͷ�ң�Ӳ��
// ���  ��_in_iCom    ���ڣ�COM1��
//         _in_Serial  �˴ν��ܵ���ˮ��
// ����  ����
// ����ֵ��RN_RESULT
//==================================================
EXTERN_C RN_RESULT RN_API _StartRead(const int _in_iCom,const char* _in_pSerial);

//==================================================
// ��������_stopread  ֹͣ��ȡ����ֹͶ�ң�Ӳ����
// ���  ����
// ����  ����
// ����ֵ��RN_RESULT
//==================================================
EXTERN_C RN_RESULT RN_API _StopRead(void);

//==================================================
// ��������_SetCallBack ���ûص��������ܹ���ȡӲ������
// ���  ��
// ����  ����
// ����ֵ��RN_RESULT
//==================================================
typedef void (CALLBACK *CallbackReceiver)(
	const char* _in_pSerial,	// �˴���ˮ��
	int _in_nAll,				// ��ǰ��ˮ���»�ȡ���ܽ��
	int _in_nCurr				// ��ǰ��ˮ���»�ȡ�ĵ��ν��
	);
EXTERN_C RN_RESULT RN_API _SetCallBack(CallbackReceiver pFunctionReceiver);


