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
// 函数名：_expFunction
// 入参  ：空
// 出参  ：空
// 返回值：RN_RESULT
//==================================================
//EXTERN_C RN_RESULT RN_API _expFunction(void);

//==================================================
// 函数名：_startread 开始读取（允许投币）硬币
// 入参  ：_in_iCom    串口（COM1）
//         _in_Serial  此次接受的流水号
// 出参  ：空
// 返回值：RN_RESULT
//==================================================
EXTERN_C RN_RESULT RN_API _StartRead(const int _in_iCom,const char* _in_pSerial);

//==================================================
// 函数名：_stopread  停止读取（禁止投币）硬币数
// 入参  ：空
// 出参  ：空
// 返回值：RN_RESULT
//==================================================
EXTERN_C RN_RESULT RN_API _StopRead(void);

//==================================================
// 函数名：_SetCallBack 设置回调函数，能够获取硬币总数
// 入参  ：
// 出参  ：空
// 返回值：RN_RESULT
//==================================================
typedef void (CALLBACK *CallbackReceiver)(
	const char* _in_pSerial,	// 此次流水号
	int _in_nAll,				// 当前流水号下获取的总金额
	int _in_nCurr				// 当前流水号下获取的单次金额
	);
EXTERN_C RN_RESULT RN_API _SetCallBack(CallbackReceiver pFunctionReceiver);


