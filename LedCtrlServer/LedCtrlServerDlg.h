
// LedCtrlServerDlg.h : 头文件
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

// CLedCtrlServerDlg 对话框
class CLedCtrlServerDlg : public CDialogEx
{
// 构造
public:
	CLedCtrlServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LEDCTRLSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox Tips;   //界面提示框变量
	CTrade m_toolTrade;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	void DealPublicPrgm(CString strJson, CString strUrl, CString strUser, CString strTime, CString strID);//处理发布节目
	BOOL LoadDeviceConfig();
	BOOL RMQ_DealCustomMsg(CString strMsg);	// RMQ下发操作
	BOOL LoadRMQPubAndRMQSUBDLL();			//加载Pub和SUB两个动态库
	BOOL RMQ_SUBConnect();
	void UploadMMPDeviceStatus(CString strIP, CString strCode);
	void ThreadPoolPublishPrgm(CString strHttpAddr, CString strPrgmID,CString strPublicUser,CString strPublicTime, CString strDeviceModel,CString strCardAddr,CString strDeviceID,CString strIP,CString strPort,CString strLedType,CString strControlCardType,CString strHeight,CString strWidth,CString strPrgmType,CString strPrgmFontSize,CString strPrgmContent,CString strPrfmIndex,CString strPrgmEffect,CString strPrgmStayTime,CString strPrgmPlaySpeed);
	BOOL EQSendPrgm(const char* pFile, CString strLedType, CString strDeviceModel, CString strIP, CString strPrgmEffect, CString strPrgmContent, CString strHeight, CString strWidth, CString strPrgmFontSize, CString strPrgmPlaySpeed, CString strPrgmStayTime);//诣阔编辑发送节目
	BOOL CLSendPrgm(CString strLedType, CString strDeviceModel, CString strIP, CString strPort, CString strPrgmContent, CString strHeight, CString strWidth, CString strPrgmFontSize, CString strPrgmPlaySpeed);
public:
	//签到线程
	HANDLE m_hReSign;
	HANDLE m_hReSignEvent;
	//上传设备状态
	HANDLE m_hDviceStatus;
	HANDLE m_hDviceStatusEvent;
	//RMQ线程
	HANDLE m_hRMQ;
	HANDLE m_hRMQEvent;
	//签到线程
	static DWORD WINAPI	ReSignThreadProc(LPVOID pParam);
	DWORD WINAPI ReSignThreadContent(LPVOID pParam);
	//上送设备状态
	static DWORD WINAPI	DeviceStatusThreadProc(LPVOID pParam);
	DWORD WINAPI DeviceStatusThreadContent(LPVOID pParam);
	// RMQ线程
	static DWORD WINAPI	RMQThreadProc(LPVOID pParam);
	DWORD WINAPI RMQThreadContent(LPVOID pParam);

public:

	BOOL m_bExit;								//程序退出标志
	CString m_strLastErr;
	CString m_MMPDeviceCode;					//跑马屏终端设备状态使用的DeviceCode;
	CString m_MMPDeviceIP;                      //跑马屏终端设备状态使用的IP
	CString m_strMMPIDlist;						//门楣屏ID列表
	CString m_strPrgmID;                        //节目ID
	CString m_strPublishUers;					//发布用户
	CString m_strPublishTime;					//发布时间
	CString m_strPrgmJson = "";					//门楣屏节目json
	int     m_iCardNum;
	int     m_iProgramIndex;
	// 实现

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
	HINSTANCE             hMU_DLL;//导入动态库
#if (LIBRARY_CALL_MODE==MODE_STDCALL)
#define LIBRARY_MODE    __stdcall
#else   
#define LIBRARY_MODE    __cdecl
#endif
	typedef BOOL(LIBRARY_MODE *_MC_PicToXMPXFile)(int colortype, int width, int height, BOOL bstretch, char* Pictfilename, char* XMPfilename);
	_MC_PicToXMPXFile	  MC_PicToXMPXFile;
};
