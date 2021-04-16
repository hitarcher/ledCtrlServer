
// LedCtrlServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "Trade.h"
#include "CommonFun.h"
#include "EQ2008_Dll.h"
#include "MiniLED.h"
#include "VSA.h"
#include "VSD.h"
#include "SCL2008.h"
#include "Onbon.h"
#include "CommTbl.h"
#include "COMMFCN.h"
#include "json.hpp"
using json = nlohmann::json;
#include "mythreadpool.h"

// CLedCtrlServerDlg �Ի���
class CLedCtrlServerDlg : public CDialogEx
{
// ����
public:
	CLedCtrlServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LEDCTRLSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox Tips;   //������ʾ�����
	CTrade m_toolTrade;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	void DealPublicPrgm(CString strJson, CString strUrl, CString strUser, CString strTime, CString strID);//��������Ŀ
	BOOL LoadDeviceConfig();
	BOOL RMQ_DealCustomMsg(CString strMsg);	// RMQ�·�����
	BOOL LoadRMQPubAndRMQSUBDLL();			//����Pub��SUB������̬��
	BOOL RMQ_SUBConnect();
	void UploadMMPDeviceStatus(CString strIP, CString strCode);
	void ThreadPoolPublishPrgm(CString strHttpAddr, CString strPrgmID,CString strPublicUser,CString strPublicTime, CString strDeviceModel,CString strCardAddr,CString strDeviceID,CString strIP,CString strPort,CString strLedType,CString strControlCardType,CString strHeight,CString strWidth,CString strPrgmType,CString strPrgmFontSize,CString strPrgmContent,CString strPrfmIndex,CString strPrgmEffect,CString strPrgmStayTime,CString strPrgmPlaySpeed);
	BOOL EQSendPrgm(const char* pFile, CString strLedType, CString strDeviceModel, CString strIP, CString strPrgmEffect, CString strPrgmContent, CString strHeight, CString strWidth, CString strPrgmFontSize, CString strPrgmPlaySpeed, CString strPrgmStayTime);//�����༭���ͽ�Ŀ
	BOOL CLSendPrgm(CString strLedType, CString strDeviceModel, CString strIP, CString strPort, CString strPrgmContent, CString strHeight, CString strWidth, CString strPrgmFontSize, CString strPrgmPlaySpeed);
public:
	//ǩ���߳�
	HANDLE m_hReSign;
	HANDLE m_hReSignEvent;
	//�ϴ��豸״̬
	HANDLE m_hDviceStatus;
	HANDLE m_hDviceStatusEvent;
	//RMQ�߳�
	HANDLE m_hRMQ;
	HANDLE m_hRMQEvent;
	//ǩ���߳�
	static DWORD WINAPI	ReSignThreadProc(LPVOID pParam);
	DWORD WINAPI ReSignThreadContent(LPVOID pParam);
	//�����豸״̬
	static DWORD WINAPI	DeviceStatusThreadProc(LPVOID pParam);
	DWORD WINAPI DeviceStatusThreadContent(LPVOID pParam);
	// RMQ�߳�
	static DWORD WINAPI	RMQThreadProc(LPVOID pParam);
	DWORD WINAPI RMQThreadContent(LPVOID pParam);

public:

	BOOL m_bExit;								//�����˳���־
	CString m_strLastErr;
	CString m_MMPDeviceCode;					//�������ն��豸״̬ʹ�õ�DeviceCode;
	CString m_MMPDeviceIP;                      //�������ն��豸״̬ʹ�õ�IP
	CString m_strMMPIDlist;						//�����ID�б�
	CString m_strPrgmID;                        //��ĿID
	CString m_strPublishUers;					//�����û�
	CString m_strPublishTime;					//����ʱ��
	CString m_strPrgmJson = "";					//�������Ŀjson
	int     m_iCardNum;
	int     m_iProgramIndex;
	// ʵ��

public:
	void tips(CString tips);

public:
	threadpool* pool_EQ;
	BOOL SendToEQ(
		CString strHttpAddr
		, CString strLedType
		, CString strDeviceModel
		, CString strIP
		, CString strPrgmEffect
		, CString strPrgmContent
		, CString strHeight
		, CString strWidth
		, CString strPrgmFontSize
		, CString strPrgmPlaySpeed
		, CString strPrgmStayTime
		, CString strDeviceID
		, CString strPublicUser
		, CString strPublicTime
		, CString strPrgmID);
	threadpool* pool_CL;
	BOOL SendToCLQ(
		CString strHttpAddr
		, CString strLedType
		, CString strDeviceModel
		, CString strPort
		, CString strIP
// 		, CString strPrgmEffect
		, CString strPrgmContent
		, CString strHeight
		, CString strWidth
		, CString strPrgmFontSize
		, CString strPrgmPlaySpeed
// 		, CString strPrgmStayTime
		, CString strDeviceID
		, CString strPublicUser
		, CString strPublicTime
		, CString strPrgmID);
	threadpool* pool_BX;
	BOOL SendToBX(
		CString strHttpAddr
		, CString strLedType
		, CString strDeviceModel
		, CString strPort
		, CString strIP
		, CString strPrgmEffect
		, CString strPrgmContent
		, CString strHeight
		, CString strWidth
		, CString strPrgmFontSize
		, CString strPrgmPlaySpeed
		, CString strPrgmStayTime
		, CString strDeviceID
		, CString strPublicUser
		, CString strPublicTime
		, CString strPrgmID);
	threadpool* pool_VSA;
	BOOL SendToVSA(
		CString strHttpAddr
// 		, CString strLedType
// 		, CString strDeviceModel
		, CString strIP
		, CString strPrgmEffect
		, CString strPrgmContent
		, CString strHeight
		, CString strWidth
// 		, CString strPrgmFontSize
		, CString strPrgmPlaySpeed
// 		, CString strPrgmStayTime
		, CString strDeviceID
		, CString strPublicUser
		, CString strPublicTime
		, CString strPrgmID);
	threadpool* pool_VSD;
	BOOL SendToVSD(
		CString strHttpAddr
 		, CString strLedType
// 		, CString strDeviceModel
		, CString strPort
		, CString strIP
		, CString strPrgmEffect
		, CString strPrgmContent
		, CString strHeight
		, CString strWidth
 		, CString strPrgmFontSize
		, CString strPrgmPlaySpeed
// 		, CString strPrgmStayTime
		, CString strDeviceID
		, CString strPublicUser
		, CString strPublicTime
		, CString strPrgmID);

	threadpool* pool_UploadStauts;


protected:
	HINSTANCE             hMU_DLL;//���붯̬��
#if (LIBRARY_CALL_MODE==MODE_STDCALL)
#define LIBRARY_MODE    __stdcall
#else   
#define LIBRARY_MODE    __cdecl
#endif
	typedef BOOL(LIBRARY_MODE *_MC_PicToXMPXFile)(int colortype, int width, int height, BOOL bstretch, char* Pictfilename, char* XMPfilename);
	_MC_PicToXMPXFile	  MC_PicToXMPXFile;
};
