#ifndef __EQ2008_DLL__
#define __EQ2008_DLL__

#ifdef DLL_API
#else
#define DLL_API _declspec(dllimport) 
#endif

#include "EQ2008_DataStruct.h" 

/****************����˵��******************/
//��ɫ����
#define RED					0x0000FF
#define GREEN				0x00FF00
#define YELLOW				0x00FFFF

//����ֵ����
#define EQ_FALSE			0
#define EQ_TRUE			    1

//1����Ŀ����������===================================================
//��ӽ�Ŀ
DLL_API int __stdcall User_AddProgram(int CardNum,BOOL bWaitToEnd,int iPlayTime);
//ɾ�����н�Ŀ
DLL_API BOOL __stdcall User_DelAllProgram(int CardNum);

//���ͼ����
DLL_API int  __stdcall User_AddBmpZone(int CardNum,User_Bmp *pBmp,int iProgramIndex);
DLL_API BOOL __stdcall User_AddBmp(int CardNum,int iBmpPartNum,HBITMAP hBitmap,User_MoveSet* pMoveSet,int iProgramIndex);
DLL_API BOOL __stdcall User_AddBmpFile(int CardNum,int iBmpPartNum,char *strFileName,User_MoveSet* pMoveSet,int iProgramIndex);
//����ı���
DLL_API int __stdcall User_AddText(int CardNum,User_Text *pText,int iProgramIndex);
//��ӵ����ı���
DLL_API int __stdcall User_AddSingleText(int CardNum,User_SingleText *pSingleText,int iProgramIndex);
//���ʱ����
DLL_API int __stdcall User_AddTime(int CardNum,User_DateTime *pDateTime,int iProgramIndex);
//��Ӽ�ʱ��
DLL_API int __stdcall User_AddTimeCount(int CardNum,User_Timer *pTimeCount,int iProgramIndex);
//����¶���
DLL_API int __stdcall User_AddTemperature(int CardNum,User_Temperature *pTemperature,int iProgramIndex);

//��������
DLL_API BOOL __stdcall User_SendToScreen(int CardNum);


//2��ʵʱ���º�����=================================================
//ʵʱ�������ݽ�������
DLL_API BOOL __stdcall User_RealtimeConnect(int CardNum);
//ʵʱ����ͼƬ���
DLL_API BOOL __stdcall User_RealtimeSendData(int CardNum,int x,int y,int iWidth,int iHeight,HBITMAP hBitmap);
//ʵʱ����ͼƬ�ļ�
DLL_API BOOL __stdcall User_RealtimeSendBmpData(int CardNum,int x,int y,int iWidth,int iHeight,char *strFileName);	 
//ʵʱ�����ı�
DLL_API BOOL __stdcall User_RealtimeSendText(int CardNum,int x,int y,int iWidth,int iHeight,char *strText,User_FontSet	*pFontInfo);	
//ʵʱ���ͶϿ�����
DLL_API BOOL __stdcall User_RealtimeDisConnect(int CardNum);	
//ʵʱ��������
DLL_API BOOL __stdcall User_RealtimeScreenClear(int CardNum);	


//3����ʾ�����ƺ�����==============================================
//����
DLL_API BOOL __stdcall User_OpenScreen(int CardNum);
//����
DLL_API BOOL __stdcall User_CloseScreen(int CardNum);
//У��ʱ��
DLL_API BOOL __stdcall User_AdjustTime(int CardNum);
//���ȵ���
DLL_API BOOL __stdcall User_SetScreenLight(int CardNum,int iLightDegreen);
//Reload�����ļ�
DLL_API void __stdcall User_ReloadIniFile(char *pEQ2008_Dll_Set_Path);

/********************************************************************************/

#endif __EQ2008_DLL__
