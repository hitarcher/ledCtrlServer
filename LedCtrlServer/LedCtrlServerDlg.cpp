
// LedCtrlServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LedCtrlServer.h"
#include "LedCtrlServerDlg.h"
#include "afxdialogex.h"
#include <Winsock2.h>
#include "iphlpapi.h" 
#include <iostream>
#include <thread>
#pragma comment(lib,"Iphlpapi.lib")
#pragma comment(lib,"Ws2_32.lib")

typedef HANDLE(WINAPI* ICMPCREATEFILE)(VOID);
typedef BOOL(WINAPI* ICMPCLOSEHANDLE)(HANDLE);
typedef DWORD(WINAPI* ICMPSENDECHO)(HANDLE, DWORD, LPVOID, WORD, PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD);
//定义三个指针函数  
ICMPCREATEFILE pIcmpCreateFile;
ICMPCLOSEHANDLE pIcmpCloseHandle;
ICMPSENDECHO pIcmpSendEcho;
// 函数功能：初始化ICMP函数：
BOOL InitIcmp()
{
	HINSTANCE hIcmp = LoadLibrary("icmp.dll");
	if (hIcmp == NULL)
	{
		return FALSE;
	}
	pIcmpCreateFile = (ICMPCREATEFILE)GetProcAddress(hIcmp, "IcmpCreateFile");
	pIcmpCloseHandle = (ICMPCLOSEHANDLE)GetProcAddress(hIcmp, "IcmpCloseHandle");
	pIcmpSendEcho = (ICMPSENDECHO)GetProcAddress(hIcmp, "IcmpSendEcho");
	if ((pIcmpCreateFile == NULL) || (pIcmpCloseHandle == NULL) || (pIcmpSendEcho == NULL))
		return FALSE;
	return TRUE;
}

// 函数功能：判断是否能ping通IP
// 函数参数：IP地址或域名

BOOL ICMPPing(char* host)
{
	DWORD timeOut = 1000;                                              //设置超时  
	ULONG hAddr = inet_addr(host);                                     //如果是IP地址就直接转换  
	if (hAddr == INADDR_NONE)
	{
		hostent* hp = gethostbyname(host);                             //如果是域名就用DNS解析出IP地址  
		if (hp)
			memcpy(&hAddr, hp->h_addr_list, hp->h_length);             //IP地址  
		else
		{
			return FALSE;
		}
	}
	HANDLE hIp = pIcmpCreateFile();
	IP_OPTION_INFORMATION ipoi;
	memset(&ipoi, 0, sizeof(IP_OPTION_INFORMATION));
	ipoi.Ttl = 128;                  //Time-To-Live  
	unsigned char pSend[36];                                                                   //发送包  
	memset(pSend, 'E', 32);
	int repSize = sizeof(ICMP_ECHO_REPLY) + 32;
	unsigned char pReply[100];                                                                 //接收包  
	ICMP_ECHO_REPLY* pEchoReply = (ICMP_ECHO_REPLY*)pReply;
	DWORD nPackets = pIcmpSendEcho(hIp, hAddr, pSend, 32, &ipoi, pReply, repSize, timeOut); //发送ICMP数据报文  
	if (pEchoReply->Status != 0)                                                    //超时，可能是主机禁用了ICMP 或者目标主机不存在 
	{
		pIcmpCloseHandle(hIp);
		return FALSE;
	}
	pIcmpCloseHandle(hIp);
	return TRUE;
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef DEBUG                            
#pragma comment(lib, "CommUtilsd.lib")  
#else                                   
#pragma comment(lib, "CommUtils.lib")   
#endif     

#define TIMER_RESIGN		1001
#define TIMER_RECV_MSG		1005
#define FileName            "Test.Txt"      // 文本文件名


VSA vsa;
VSD vsd;
Onbon onbon;
SCL2008 scl2008;
CLedCtrlServerDlg* g_CLedCtrlServerDlg = NULL;
static CString g_strRecvMsg = "";
typedef void(__stdcall *_CallBack_Recv)(char* bMsg);
typedef int(_stdcall *lpRMQ_CALLBACK)(_CallBack_Recv);
typedef int(_stdcall *lpRMQ_SUB)(const char *, int, const char *, const char *, const char *, const char *, const char *, int, int);
lpRMQ_SUB _RMQ_SUB;
lpRMQ_CALLBACK _RMQ_CALLBACK;

static void CALLBACK _Recv(char* bMsg)
{
	g_strRecvMsg = bMsg;
	g_CLedCtrlServerDlg->SetTimer(TIMER_RECV_MSG, 10, NULL);
}
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CLedCtrlServerDlg 对话框

CLedCtrlServerDlg::CLedCtrlServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LEDCTRLSERVER_DIALOG, pParent)
{
	g_CLedCtrlServerDlg = this;
	m_MMPDeviceCode = "";
	m_MMPDeviceIP = "";
	//RMQ
	m_hRMQ = NULL;
	m_hRMQEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//签到
	m_hReSign = NULL;
	m_hReSignEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//上传设备状态
	m_hDviceStatus = NULL;
	m_hDviceStatusEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	//控制卡地址
	m_iCardNum = 1;
	m_iProgramIndex = -1;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLedCtrlServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, Tips);
}

BEGIN_MESSAGE_MAP(CLedCtrlServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CLedCtrlServerDlg 消息处理程序

BOOL CLedCtrlServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 创建线程池
	pool_EQ = new threadpool(1);
	pool_CL = new threadpool(1);
	pool_BX = new threadpool(1);
	pool_VSA = new threadpool(1);
	pool_VSD = new threadpool(1);
	pool_UploadStauts = new threadpool(1);

	//TODO:在此添加额外的初始化代码
	//先去平台签到，拿到机构号
	BOOL bResult = g_Config.LoadUrl();
	if (!bResult)
	{
		LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "[OnInitDialog]--获取配置文件中的平台地址字段失败！");
		tips(_T("[OnInitDialog]--获取配置文件中的平台地址字段失败！"));
		return FALSE;
	}
	DWORD dwThreadId = 0;
	m_hReSign = CreateThread(NULL, 0, ReSignThreadProc, this, 0, &dwThreadId);
	LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "[OnInitDialog]--CreateThread ReSignThreadProc");
	tips(_T("[OnInitDialog]--CreateThread ReSignThreadProc"));
	SetTimer(TIMER_RESIGN, 10, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLedCtrlServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLedCtrlServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLedCtrlServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLedCtrlServerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	KillTimer(nIDEvent);
	switch (nIDEvent)
	{
	case TIMER_RESIGN:
		SetEvent(m_hReSignEvent);
		break;
	case TIMER_RECV_MSG:				//获取数据
		SetEvent(m_hRMQEvent);
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CLedCtrlServerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	delete pool_EQ;
	delete pool_CL;
	delete pool_BX;
	delete pool_VSD;
	delete pool_VSA;
	delete pool_UploadStauts;
	// TODO: 在此处添加消息处理程序代码
	m_bExit = TRUE;
	SetEvent(m_hRMQEvent);
	WaitForSingleObject(m_hRMQ, 3000);
	m_hRMQ = NULL;

	SetEvent(m_hReSignEvent);
	WaitForSingleObject(m_hReSign, 3000);
	m_hReSign = NULL;

	SetEvent(m_hDviceStatusEvent);
	WaitForSingleObject(m_hDviceStatus, 3000);
	m_hDviceStatus = NULL;
	//视展VSA
	vsa.Destroy();
	vsa.Preview_VSAFinalize();
	//视展VSD
	vsd.LED_VSDDestroy();
	onbon.OnbonReleaseSdk();
	//励研SCL2008
	scl2008.LED_SCL2008FreeDll();
	LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "[OnDestroy]--程序退出");
}

BOOL CLedCtrlServerDlg::LoadDeviceConfig()
{
	if (FALSE == g_Config.LoadBaseCfg())
	{
		AfxMessageBox(g_Config.GetLastErr());
		EndDialog(FALSE);
		return FALSE;
	}
	tips(_T("初始化开始"));
	//定期清除日志
	DeleteLog(GetFullPath("LOG").GetBuffer(0), g_Config.m_nDelLogDay);
	// 导入砺研动态链接库
	if (!LoadMiniLEDdll())
	{
		MessageBox("动态链接库初始化失败", "MiniLED", MB_OK);
		SendMessage(WM_CLOSE, 0, 0L);
		return FALSE;
	}
	// 导入动态链接库"MiniUtil.Dll"（砺研）
	hMU_DLL = LoadLibrary("MiniUtil.Dll");
	if (hMU_DLL != NULL)
	{
		MC_PicToXMPXFile = (_MC_PicToXMPXFile)::GetProcAddress(hMU_DLL, "MC_PicToXMPXFile");
	}
	// 判断函数指针获取成功否
	if ((!hMU_DLL) || (!MC_PicToXMPXFile))
	{
		FreeLibrary(hMU_DLL);
		hMU_DLL = NULL;
		MessageBox("动态链接库初始化失败", "MiniUtil", MB_OK);
		SendMessage(WM_CLOSE, 0, 0L);
		return FALSE;
	}
	//add by Chengzhi
	//VSA初始化
	BOOL bInitVSAOk = FALSE;
	bInitVSAOk = vsa.LED_VSAInitialize();
	if (!bInitVSAOk)
	{
		MessageBox("动态链接库初始化失败", "LEDSender", MB_OK);
		SendMessage(WM_CLOSE, 0, 0L);
		return FALSE;
	}
	vsa.Preview_VSAInitialize();
	//初始化视展D卡动态库
	BOOL bInitVSDOk = FALSE;
	bInitVSDOk = vsd.LED_VSDInitialize();
	if (!bInitVSAOk)
	{
		MessageBox("动态链接库初始化失败", "LEDSender2010", MB_OK);
		SendMessage(WM_CLOSE, 0, 0L);
		return FALSE;
	}
	//初始化仰邦BX-5动态链接库
	BOOL bIsLoadDll = onbon.InitOnbonSdk();
	if (!bIsLoadDll)
	{
		MessageBox("动态链接库初始化失败", "bx_sdk_dual.dll", MB_OK);
		SendMessage(WM_CLOSE, 0, 0L);
		return FALSE;
	}
	BOOL bIsLoadSCLDll = scl2008.LED_SCL2008Initialize();
	if (!bIsLoadDll)
	{
		MessageBox("动态链接库初始化失败", "SCL_API_stdcall.dll", MB_OK);
		SendMessage(WM_CLOSE, 0, 0L);
		return FALSE;
	}
	BOOL bLoadPingDll = InitIcmp();
	if (!bLoadPingDll)
	{
		MessageBox("动态链接库初始化失败", "icmp.dll", MB_OK);
		SendMessage(WM_CLOSE, 0, 0L);
		return FALSE;
	}

	m_bExit = FALSE;

	DWORD dwThreadId = 0;
	m_hRMQ = CreateThread(NULL, 0, RMQThreadProc, this, 0, &dwThreadId);
	m_hDviceStatus = CreateThread(NULL, 0, DeviceStatusThreadProc, this, 0, &dwThreadId);

	if (FALSE == LoadRMQPubAndRMQSUBDLL())
	{
		LOG(LOGTYPE_DEBUG, SERVERLOG, "[LoadDeviceConfig]-动态库加载失败:[%s]", m_strLastErr);
		return FALSE;
	}
	RMQ_SUBConnect();
	LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "[LoadDeviceConfig]--CreateThread RMQThreadProc");
	LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "[LoadDeviceConfig]--CreateThread DeviceStatusThreadProc");
	LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "[LoadDeviceConfig]--CreateThread MMPDeviceStatusThreadProc");

	tips(_T("[LoadDeviceConfig]--CreateThread RMQThreadProc"));
	tips(_T("[LoadDeviceConfig]--CreateThread DeviceStatusThreadProc"));
	tips(_T("[LoadDeviceConfig]--CreateThread MMPDeviceStatusThreadProc"));
	return TRUE;
}

void CLedCtrlServerDlg::UploadMMPDeviceStatus(CString strIP, CString strCode)
{
	//上传门楣屏终端设备状态
	BOOL bIsPing = ICMPPing(strIP.GetBuffer(0));
	if (bIsPing)
	{
		BOOL bRet = m_toolTrade.UpLoadMMPDeviceStatus(g_Config.m_strHttpUrl, strCode);
		LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "DeviceStatusThreadContent--[%s]", "调用上送门楣屏设备状态接口");
		if (bRet)
		{
			CTime tmBegin = CTime::GetCurrentTime();
			CString str_Begin = tmBegin.Format("%Y%m%d%H%M%S");
			LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "DeviceStatusThreadContent--[门楣屏设备在线且状态上传成功！][%s],[%s]", str_Begin, m_MMPDeviceCode);
		}
		else
		{
			CTime tmBegin = CTime::GetCurrentTime();
			CString str_Begin = tmBegin.Format("%Y%m%d%H%M%S");
			LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "DeviceStatusThreadContent--[门楣屏设备状态在线但状态上传失败！][%s],[%s]", str_Begin, m_MMPDeviceCode);
		}
	}
	else
	{
		CTime tmBegin = CTime::GetCurrentTime();
		CString str_Begin = tmBegin.Format("%Y%m%d%H%M%S");
		LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "DeviceStatusThreadContent--[门楣屏设备离线],[%s],[%s],[%s]", str_Begin, m_MMPDeviceCode, m_MMPDeviceIP);
	}
}

void CLedCtrlServerDlg::tips(CString tips)
{
	Tips.InsertString(0, tips);
	LOG_DD(LOGTYPE_DEBUG, TIPSLOG, "%s", tips);
}

/***************************************************************/
/*                               RMQ                           */
/***************************************************************/

BOOL CLedCtrlServerDlg::LoadRMQPubAndRMQSUBDLL()
{
	HINSTANCE hRMQDll = LoadLibrary("RMQ.dll");
	_RMQ_SUB = (lpRMQ_SUB)GetProcAddress(hRMQDll, "_RMQ_SUB");
	_RMQ_CALLBACK = (lpRMQ_CALLBACK)GetProcAddress(hRMQDll, "_RMQ_CALLBACK");
	if (NULL == hRMQDll)
	{
		m_strLastErr = "RMQ_SUB动态库加载失败...";
		goto EXIT;
	}
	if (NULL == _RMQ_CALLBACK)
	{
		m_strLastErr = "_RMQ_CALLBACK加载失败...";
		goto EXIT;
	}
	if (NULL == _RMQ_SUB)
	{
		m_strLastErr = "_RMQ_SUB加载失败...";
		goto EXIT;
	}
	_RMQ_CALLBACK(_Recv);
	LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[LoadRMQPubAndRMQSUBDLL]--动态库RMQ.dll加载成功");
	return TRUE;
EXIT:
	return FALSE;
}

BOOL CLedCtrlServerDlg::RMQ_SUBConnect()
{
	if (g_Config.m_strDeviceCode.GetLength() <= 0 || g_Config.m_strIPAddress.GetLength() <= 0 || g_Config.m_nPort < 0
		|| g_Config.m_strAccount.GetLength() <= 0 || g_Config.m_strPassword.GetLength() <= 0 || g_Config.m_nModeName < 0
		|| g_Config.m_strExchangeName.GetLength() <= 0 || g_Config.m_vecRouteKey.size() <= 0 || g_Config.m_nChannel < 0)
	{
		LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQSUBConnect]--配置文件参数填写异常...");
		return FALSE;
	}
	CString strRouteKey = "";
	for (int i = 0; i < g_Config.m_vecRouteKey.size(); i++)
	{
		if ("" != g_Config.m_vecRouteKey[i])
			strRouteKey += ("" == strRouteKey ? "" : "|") + g_Config.m_vecRouteKey[i];
	}

	int nState = _RMQ_SUB(g_Config.m_strIPAddress, g_Config.m_nPort, g_Config.m_strAccount,
		g_Config.m_strPassword, g_Config.m_strExchangeName, g_Config.m_strDeviceCode,
		strRouteKey, g_Config.m_nModeName, g_Config.m_nChannel);

	if (nState != 0)
	{
		LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQSUBConnect]--RMQ连接失败...");
		return FALSE;
	}
	LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQSUBConnect]--RMQ连接成功...");
	return TRUE;
}

BOOL CLedCtrlServerDlg::RMQ_DealCustomMsg(CString strMsg)
{
	LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQ_DealCustomMsg]--RMQ收到消息[%s]", strMsg);
	if (strMsg == "") return FALSE;
	std::vector<CString> vct = SplitString(strMsg.GetBuffer(), "|");
	if (vct.size() >= 1)
	{
		if (vct[0].CompareNoCase("PUBLISH") == 0)
		{
			if (vct[1].CompareNoCase(g_Config.m_strDeviceCode) == 0)
			{
				m_strPrgmID = vct[2];
				m_strMMPIDlist = vct[3];
				m_strPublishUers = vct[5];
				m_strPublishTime = vct[6];
				m_strPrgmJson = "";
				CString strJsonIn = "";
				strJsonIn.Format("\"itemtype\":\"%d\",\"deviceIDs\":\"%s\",\"itemId\":\"%s\"", 3, m_strMMPIDlist, m_strPrgmID);//3代表门楣屏节目
				BOOL bRet = m_toolTrade.GetPrgms(g_Config.m_strHttpUrl, strJsonIn, m_strPrgmJson);
				if (bRet)
				{
					LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQ_DealCustomMsg]--下载节目json成功[%s]", m_strPrgmJson);
					std::thread t1([&](CString t1_strJson, CString t1_strUrl,CString t1_strUser,CString t1_strTime,CString t1_strID){
						DealPublicPrgm(t1_strJson,t1_strUrl,t1_strUser,t1_strTime,t1_strID);
					}, m_strPrgmJson, g_Config.m_strHttpUrl, m_strPublishUers, m_strPublishTime, m_strPrgmID);
					/*edit by mingl*/
					t1.detach();
					
					Sleep(10);
				}
				else
				{
					CString strBody = "";
					strBody.Format("\"itemtype\":\"%d\",\"status\":\"%d\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", "3", "4", m_strMMPIDlist, m_strPublishUers, m_strPublishTime, m_strPrgmID);
					bRet = m_toolTrade.UpLoadProGrameStatus(g_Config.m_strHttpUrl, strBody);
					if (!bRet)
					{
						LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQ_DealCustomMsg]--[m_toolTrade.UpLoadProGrameStatus][err][%s]", m_toolTrade.GetLastErr());
					}
					else
					{
						tips(_T("[RMQ_DealCustomMsg]--调用平台节目发布接口失败！"));
						LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQ_DealCustomMsg]--[m_toolTrade.GetPrgms][err][%s]", m_toolTrade.GetLastErr());
					}
				}
			}
			else
			{
				LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQ_DealCustomMsg]--[RMQ_DealCustomMsg][err][未知设备][%s]", vct[1]);
			}
		}
		else if (vct[0].CompareNoCase("OFFLINE") == 0)
		{
			if (vct.size() == 5)
			{
				LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQ_DealCustomMsg]--收到平台推送的上送门楣屏终端设备状态的消息");
				m_MMPDeviceCode = vct[3];
				m_MMPDeviceIP = vct[4];
				/*edit by mingl*/
				//std::thread t(&CLedCtrlServerDlg::UploadMMPDeviceStatus,this);
				std::thread t([&](CString t_device_ip, CString t_device_code) {
					UploadMMPDeviceStatus(t_device_ip, t_device_code);
				}, vct[4], vct[3]);
				/*edit by mingl*/
				t.detach();
			}
			else
			{
				LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQ_DealCustomMsg]--收到平台推送的上送中转服务状态的消息");
				SetEvent(m_hDviceStatusEvent);
			}
		}
		else
		{
			// 未知消息
			LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQ_DealCustomMsg]--[RMQ_DealCustomMsg][err][未知消息][%s]", vct[0]);
		}
	}
	else
	{
		// 报文格式错
		LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQ_DealCustomMsg]--[RMQ_DealCustomMsg][err][报文格式错][%s]", strMsg);
	}
	return TRUE;
}

/********************************************************************/
/*              设备签到、上送状态以及接收MQ消息线程                */
/********************************************************************/

DWORD CLedCtrlServerDlg::RMQThreadProc(LPVOID pParam)
{
	CLedCtrlServerDlg* pDlg = (CLedCtrlServerDlg*)pParam;
	return pDlg->RMQThreadContent(pParam);
}

DWORD CLedCtrlServerDlg::RMQThreadContent(LPVOID pParam)
{
	while (FALSE == m_bExit)
	{
		Sleep(100);
		DWORD dwResult = WaitForSingleObject(m_hRMQEvent, INFINITE);
		if (TRUE == m_bExit) return TRUE;
		if (dwResult == WAIT_OBJECT_0)
		{
			RMQ_DealCustomMsg(g_strRecvMsg);
		}
		ResetEvent(m_hRMQEvent);
	}
	return TRUE;
}

DWORD CLedCtrlServerDlg::ReSignThreadProc(LPVOID pParam)
{
	CLedCtrlServerDlg* pDlg = (CLedCtrlServerDlg*)pParam;
	return pDlg->ReSignThreadContent(pParam);
}

DWORD CLedCtrlServerDlg::ReSignThreadContent(LPVOID pParam)
{
	static int icount = 0;
	while (FALSE == m_bExit)
	{
		DWORD dwResult = WaitForSingleObject(m_hReSignEvent, INFINITE);
		if (TRUE == m_bExit) return TRUE;
		if (dwResult == WAIT_OBJECT_0)
		{
			BOOL bRet = m_toolTrade.Login(g_Config.m_strHttpUrl.GetBuffer(0));
			if (FALSE == bRet)
			{
				LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "[ReSignThreadContent]--[m_toolTrade.Login][err][%s]", m_toolTrade.GetLastErr());
				//签到失败，10s重新签到一次
				SetTimer(TIMER_RESIGN, 10 * 1000, NULL);
				icount++;
				if (icount == 2)
				{
					LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "[ReSignThreadContent]--[%s]", "签到失败...");
					tips(_T("[ReSignThreadContent]--签到失败..."));
				}
			}
			else
			{
				icount = 0;
				LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "[ReSignThreadContent]--[%s]", "签到成功！");
				tips(_T("[ReSignThreadContent]--签到成功"));
				//签到成功后通过报文获取到机构号然后再读取配置文件
				BOOL bRent = LoadDeviceConfig();
				if (!bRent)
				{
					LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "[ReSignThreadContent]--[%s]", "程序初始化失败...");
					tips(_T("[ReSignThreadContent]--程序初始化失败..."));
				}
				ResetEvent(m_hReSignEvent);
			}
		}
	}
	return TRUE;
}

DWORD CLedCtrlServerDlg::DeviceStatusThreadProc(LPVOID pParam)
{
	CLedCtrlServerDlg* pDlg = (CLedCtrlServerDlg*)pParam;
	return pDlg->DeviceStatusThreadContent(pParam);
}

DWORD CLedCtrlServerDlg::DeviceStatusThreadContent(LPVOID pParam)
{
	while (FALSE == m_bExit)
	{
		DWORD dwResult = WaitForSingleObject(m_hDviceStatusEvent, INFINITE);
		if (TRUE == m_bExit) return TRUE;
		if (dwResult == WAIT_OBJECT_0)
		{
			//上传设备状态
			BOOL bRet = m_toolTrade.UpLoadDeviceStatus(g_Config.m_strHttpUrl);
			if (bRet)
			{
				CTime tmBegin = CTime::GetCurrentTime();
				CString str_Begin = tmBegin.Format("%Y%m%d%H%M%S");
				LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "DeviceStatusThreadContent--[设备状态上传成功！][%s]", str_Begin);
			}
			else
			{
				CTime tmBegin = CTime::GetCurrentTime();
				CString str_Begin = tmBegin.Format("%Y%m%d%H%M%S");
				LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "DeviceStatusThreadContent--[设备状态上传失败！][%s]", str_Begin);
			}
		}
		ResetEvent(m_hDviceStatusEvent);
	}
	return TRUE;
}

/**********************************************************************/
/*                   解析Json并开启节目处理线程                       */
/**********************************************************************/

void CLedCtrlServerDlg::ThreadPoolPublishPrgm(CString strHttpAddr,CString strPrgmID, CString strPublicUser, CString strPublicTime, CString strDeviceModel, CString strCardAddr, CString strDeviceID, CString strIP, CString strPort, CString strLedType, CString strControlCardType, CString strHeight, CString strWidth, CString strPrgmType, CString strPrgmFontSize, CString strPrgmContent, CString strPrfmIndex, CString strPrgmEffect, CString strPrgmStayTime, CString strPrgmPlaySpeed)
{
	//底层sdk不允许线程池这样的调用发布会导致程序崩溃，弃用。
	//CString t_strHttpAddr = strHttpAddr;
	//CString t_strPrgmID = strPrgmID;
	//CString t_strPublicUser = strPublicUser;
	//CString t_strPublicTime = strPublicTime;
	//CString t_strDeviceModel = strDeviceModel;
	//CString t_strCardAddr = strCardAddr;
	//CString t_strDeviceID = strDeviceID;
	//CString t_strIP = strIP;
	//CString t_strPort = strPort;
	//CString t_strLedType = strLedType;
	//CString t_strControlCardType = strControlCardType;
	//CString t_strHeight = strHeight;
	//CString t_strWidth = strWidth;
	//CString t_strPrgmType = strPrgmType;
	//CString t_strPrgmFontSize = strPrgmFontSize;
	//CString t_strPrgmContent = strPrgmContent;
	//CString t_strPrfmIndex = strPrfmIndex;
	//CString t_strPrgmEffect = strPrgmEffect;
	//CString t_strPrgmStayTime = strPrgmStayTime;
	//CString t_strPrgmPlaySpeed = strPrgmPlaySpeed;

	//BOOL IsSuccess = FALSE;
	//CString strBody = "";
	//if (t_strDeviceModel == "EQ3002-I" || t_strDeviceModel == "EQ3002-II" || t_strDeviceModel == "EQ3002-III" || t_strDeviceModel == "EQ2008-I/II" || t_strDeviceModel == "EQ2010-I" || t_strDeviceModel == "EQ2008 - IE" || t_strDeviceModel == "EQ2011" || t_strDeviceModel == "EQ2012" || t_strDeviceModel == "EQ2008-M" || t_strDeviceModel == "EQ2013" || t_strDeviceModel == "EQ2023" || t_strDeviceModel == "EQ2033")
	//{
	//	CString strFilepath = GetFullPath("EQ2008_Dll_Set.ini");
	//	strFilepath.Replace("/", "\\");
	//	IsSuccess = EQSendPrgm(strFilepath.GetBuffer(0), t_strLedType, t_strDeviceModel, t_strIP, t_strPrgmEffect, t_strPrgmContent, t_strHeight, t_strWidth, t_strPrgmFontSize, t_strPrgmPlaySpeed, t_strPrgmStayTime);
	//	if (IsSuccess)
	//	{
	//		strBody = "";
	//		strBody.Format("\"itemtype\":\"3\",\"status\":\"0\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", t_strDeviceID, t_strPublicUser, t_strPublicTime, t_strPrgmID);
	//		IsSuccess = m_toolTrade.UpLoadProGrameStatus(t_strHttpAddr, strBody);
	//		if (IsSuccess)
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--诣阔控制卡节目下发成功"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]-诣阔卡下发节目成功[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//		else
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--诣阔控制卡节目下发成功"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--诣阔控制卡节目下发成功,上送节目下发结果失败[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//	}
	//	else
	//	{
	//		strBody = "";
	//		strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", t_strDeviceID, t_strPublicUser, t_strPublicTime, t_strPrgmID);
	//		IsSuccess = m_toolTrade.UpLoadProGrameStatus(t_strHttpAddr, strBody);
	//		if (IsSuccess)
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--诣阔控制卡节目发布失败"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--诣阔控制卡下发节目失败，上送节目下发状态成功[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//		else
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--诣阔控制卡节目发布失败"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--诣阔控制卡节目下发失败,上送节目下发结果失败[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//	}
	//}
	//else if (t_strDeviceModel == "CL3000" || t_strDeviceModel == "SCL2008")
	//{
	//	IsSuccess = CLSendPrgm(t_strLedType, t_strDeviceModel, t_strIP, t_strPort, t_strPrgmContent, t_strHeight, t_strWidth, t_strPrgmFontSize, t_strPrgmPlaySpeed);
	//	if (IsSuccess)
	//	{
	//		strBody = "";
	//		strBody.Format("\"itemtype\":\"3\",\"status\":\"0\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", t_strDeviceID, t_strPublicUser, t_strPublicTime, t_strPrgmID);
	//		IsSuccess = m_toolTrade.UpLoadProGrameStatus(t_strHttpAddr, strBody);
	//		if (IsSuccess)
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--励研控制卡节目下发成功"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]-励研控制卡下发节目成功[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//		else
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--励研控制卡节目下发成功"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--励研控制卡节目下发成功,上送节目下发结果失败[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//	}
	//	else
	//	{
	//		strBody = "";
	//		strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", t_strDeviceID, t_strPublicUser, t_strPublicTime, t_strPrgmID);
	//		IsSuccess = m_toolTrade.UpLoadProGrameStatus(t_strHttpAddr, strBody);
	//		if (IsSuccess)
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--励研卡节目下发失败!"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--励研卡节目下发失败[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//		else
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--励研卡下发失败,上送节目下发结果失败"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--励研卡下发失败,上送节目下发结果失败[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//	}
	//}
	//else if (t_strDeviceModel == "BX-5" || t_strDeviceModel == "BX-E" || t_strDeviceModel == "BX-5E")
	//{
	//	IsSuccess = onbon.PublishPrograms(t_strIP, t_strPort, t_strLedType, t_strDeviceModel, t_strPrgmContent, atoi(t_strWidth), atoi(t_strHeight), atoi(t_strPrgmFontSize), atoi(t_strPrgmEffect), atoi(t_strPrgmPlaySpeed), atoi(t_strPrgmStayTime));
	//	if (IsSuccess)
	//	{
	//		strBody = "";
	//		strBody.Format("\"itemtype\":\"3\",\"status\":\"0\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", t_strDeviceID, t_strPublicUser, t_strPublicTime, t_strPrgmID);
	//		IsSuccess = m_toolTrade.UpLoadProGrameStatus(t_strHttpAddr, strBody);
	//		if (IsSuccess)
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--仰邦卡下发节目成功"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--仰邦卡下发节目成功[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//		else
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--仰邦卡节目下发成功"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--仰邦卡节目下发成功,上送节目下发结果失败[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//	}
	//	else
	//	{
	//		strBody = "";
	//		strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", t_strDeviceID, t_strPublicUser, t_strPublicTime, t_strPrgmID);
	//		IsSuccess = m_toolTrade.UpLoadProGrameStatus(t_strHttpAddr, strBody);
	//		if (IsSuccess)
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--仰邦卡节目下发失败!"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--仰邦卡节目下发失败[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//		else
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--仰邦卡节目下发失败"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--仰邦卡下发失败,上送节目下发结果失败[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//	}
	//}
	//else if (t_strDeviceModel == "VSA")
	//{
	//	//打开设备
	//	BOOL bRet = vsa.LED_VSAOpenDevice();
	//	if (bRet)
	//	{
	//		strBody = "";
	//		strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", t_strDeviceID, t_strPublicUser, t_strPublicTime, t_strPrgmID);
	//		IsSuccess = m_toolTrade.UpLoadProGrameStatus(t_strHttpAddr, strBody);
	//		tips(_T("[ThreadPoolPublishPrgm]--视展A卡打开设备失败!"));
	//		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--视展A卡节目下发失败[%s][%s]", t_strIP, t_strPrgmID);
	//	}
	//	else
	//	{
	//		vsa.LED_VSASendPrgm(atoi(t_strWidth), atoi(t_strHeight), t_strPrgmContent, atoi(t_strPrgmEffect), atoi(t_strPrgmPlaySpeed), 0, t_strIP);
	//		IsSuccess = m_toolTrade.UpLoadProGrameStatus(t_strHttpAddr, strBody);
	//		if (IsSuccess)
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--视展A卡下发节目成功"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--视展A卡下发节目成功[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//	}
	//}
	//else if (t_strDeviceModel == "VSD")
	//{
	//	int nRet = vsd.LED_VSDSendPrgm(t_strIP, t_strPort, atoi(t_strWidth), atoi(t_strHeight), t_strPrgmContent, t_strPrgmFontSize, atoi(t_strPrgmEffect), atoi(t_strPrgmPlaySpeed));
	//	if (nRet != 0)
	//	{
	//		strBody = "";
	//		strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", t_strDeviceID, t_strPublicUser, t_strPublicTime, t_strPrgmID);
	//		IsSuccess = m_toolTrade.UpLoadProGrameStatus(t_strHttpAddr, strBody);
	//		tips(_T("[ThreadPoolPublishPrgm]--视展D卡发布节目失败!"));
	//		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--视展D卡节目下发失败[%s][%s]", t_strIP, t_strPrgmID);
	//	}
	//	else
	//	{
	//		strBody = "";
	//		strBody.Format("\"itemtype\":\"3\",\"status\":\"0\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", t_strDeviceID, t_strPublicUser, t_strPublicTime, t_strPrgmID);
	//		IsSuccess = m_toolTrade.UpLoadProGrameStatus(t_strHttpAddr, strBody);
	//		if (IsSuccess)
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--视展D卡下发节目成功"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--视展D卡下发节目成功[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//	}
	//}
	//else
	//{
	//	strBody = "";
	//	strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", t_strDeviceID, t_strPublicUser, t_strPublicTime, t_strPrgmID);
	//	IsSuccess = m_toolTrade.UpLoadProGrameStatus(t_strHttpAddr, strBody);
	//	if (IsSuccess)
	//	{
	//		tips(_T("[ThreadPoolPublishPrgm]--下发失败，不支持此种控制卡"));
	//		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--不支持此种控制卡[%s]", t_strDeviceModel);
	//	}
	//	else
	//	{
	//		tips(_T("[ThreadPoolPublishPrgm]--下发失败,上送节目下发结果失败"));
	//		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--上送节目下发结果失败[%s]", t_strPrgmID);
	//	}
	//}
}

void CLedCtrlServerDlg::DealPublicPrgm(CString strJson,CString strUrl,CString strUser,CString strTime,CString strID)
{
	LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--开始发布节目");
	CString strPrgm = strJson;
	CString strHttpAddr = strUrl;
	CString strPublicUser = strUser;
	CString strPublicTime = strTime;
	CString strPrgmID = strID;
	BOOL IsSuccess = FALSE;
	json jAll = json::parse(strPrgm.GetBuffer(0));
	json jBody = jAll["body"];
	json jdata = jBody["data"];
	if (!jdata.is_null())
	{
		if (jdata.is_array())
		{
			for (json::iterator it = jdata.begin(); it != jdata.end(); ++it)
			{
				json SubData = *it;
				CString strTips = "";
				CString strDeviceModel = SubData["DeviceModel"].get<std::string>().c_str();
				CString strCardAddr = SubData["CardAddr"].get<std::string>().c_str();
				CString strDeviceID = SubData["DeviceID"].get<std::string>().c_str();
				CString strIP = SubData["IP"].get<std::string>().c_str();
				CString strPort = SubData["Port"].get<std::string>().c_str();
				CString strLedType = SubData["LedType"].get<std::string>().c_str();
				CString strControlCardType = SubData["ControlCardType"].get<std::string>().c_str();
				CString strHeight = SubData["Height"].get<std::string>().c_str();
				CString strWidth = SubData["Width"].get<std::string>().c_str();
				CString strPrgmType = SubData["Prgm"]["Type"].get<std::string>().c_str();
				CString strPrgmFontSize = SubData["Prgm"]["FontSize"].get<std::string>().c_str();
				CString strPrgmContent = SubData["Prgm"]["Content"].get<std::string>().c_str();
				strPrgmContent.Replace("\n", "");
				CString strPrfmIndex = SubData["Prgm"]["Index"].get<std::string>().c_str();
				CString strPrgmEffect = SubData["Prgm"]["Effect"].get<std::string>().c_str();
				CString strPrgmStayTime = SubData["Prgm"]["StayTime"].get<std::string>().c_str();
				CString strPrgmPlaySpeed = SubData["Prgm"]["PlaySpeed"].get<std::string>().c_str();
				CString strBody = "";
				BOOL IsSuccess = FALSE;
				if (strDeviceModel == "EQ3002-I" || strDeviceModel == "EQ3002-II" || strDeviceModel == "EQ3002-III" || strDeviceModel == "EQ2008-I/II" || 
					strDeviceModel == "EQ2010-I" || strDeviceModel == "EQ2008 - IE" || strDeviceModel == "EQ2011" || strDeviceModel == "EQ2012" || 
					strDeviceModel == "EQ2008-M" || strDeviceModel == "EQ2013" || strDeviceModel == "EQ2023" || strDeviceModel == "EQ2033")
				{
					pool_EQ->enqueue([=]() {
						SendToEQ(strHttpAddr, strLedType, strDeviceModel, strIP, strPrgmEffect, strPrgmContent, strHeight, strWidth, strPrgmFontSize,
							strPrgmPlaySpeed, strPrgmStayTime, strDeviceID, strPublicUser, strPublicTime, strPrgmID);
					});
				}
				else if (strDeviceModel == "CL3000" || strDeviceModel == "SCL2008")
				{
					pool_CL->enqueue([=]() {
						SendToCLQ(strHttpAddr, strLedType, strDeviceModel, strPort, strIP, /*strPrgmEffect,*/ strPrgmContent, strHeight, strWidth,
							strPrgmFontSize, strPrgmPlaySpeed, /*strPrgmStayTime,*/ strDeviceID, strPublicUser, strPublicTime, strPrgmID);
					});
				}
				else if (strDeviceModel == "BX-5" || strDeviceModel == "BX-E" || strDeviceModel == "BX-5E" || strDeviceModel == "BX-6E" || strDeviceModel == "BX-6")
				{
					pool_CL->enqueue([=]() {
						SendToBX(strHttpAddr, strLedType, strDeviceModel,  strIP, strPort, strPrgmEffect, strPrgmContent,
							strHeight, strWidth, strPrgmFontSize, strPrgmPlaySpeed, strPrgmStayTime, strDeviceID, strPublicUser, strPublicTime, strPrgmID);
					});
				}
				else if (strDeviceModel == "VSA")
				{
					pool_CL->enqueue([=]() {
						SendToVSA(strHttpAddr,strIP, strPrgmEffect, strPrgmContent, strHeight, strWidth,
							 strPrgmPlaySpeed,strDeviceID, strPublicUser, strPublicTime, strPrgmID);
					});
				}
				else if (strDeviceModel == "VSD")
				{
					pool_CL->enqueue([=]() {
						SendToVSD(strHttpAddr, strLedType, strPort, strIP, strPrgmEffect, strPrgmContent,
							strHeight, strWidth, strPrgmFontSize, strPrgmPlaySpeed,strDeviceID, strPublicUser, strPublicTime, strPrgmID);
					});
				}
				else
				{
					strBody = "";
					strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", strDeviceID, strPublicUser, strPublicTime, strPrgmID);
					IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
					if (IsSuccess)
					{
						strTips.Format("[DealPublicPrgm]--下发失败，不支持此种控制卡[%s][%s]", strDeviceModel, strIP);
						tips(strTips);
						LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--不支持此种控制卡[%s][%s]", strDeviceModel, strIP);
					}
					else
					{
						strTips.Format("[DealPublicPrgm]--下发失败,不支持此种控制卡,上送节目下发结果失败[%s][%s]", strDeviceModel, strIP);
						tips(strTips);
						LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--上送节目下发结果失败[%s][%s]", strPrgmID, strIP);
					}
				}
				//std::thread t2([&](CString t2_strHttpAddr, CString t2_strPrgmID, CString t2_strPublicUser, CString t2_strPublicTime, CString t2_strDeviceModel, CString t2_strCardAddr, CString t2_strDeviceID, CString t2_strIP, CString t2_strPort, CString t2_strLedType, CString t2_strControlCardType, CString t2_strHeight, CString t2_strWidth, CString t2_strPrgmType, CString t2_strPrgmFontSize, CString t2_strPrgmContent, CString t2_strPrfmIndex, CString t2_strPrgmEffect, CString t2_strPrgmStayTime, CString t2_strPrgmPlaySpeed){
				//	ThreadPoolPublishPrgm(t2_strHttpAddr, t2_strPrgmID, t2_strPublicUser, t2_strPublicTime, t2_strDeviceModel, t2_strCardAddr, t2_strDeviceID, t2_strIP, t2_strPort, t2_strLedType, t2_strControlCardType, t2_strHeight, t2_strWidth, t2_strPrgmType, t2_strPrgmFontSize, t2_strPrgmContent, t2_strPrfmIndex, t2_strPrgmEffect, t2_strPrgmStayTime, t2_strPrgmPlaySpeed);
				//}, strHttpAddr, strPrgmID, strPublicUser, strPublicTime, strDeviceModel, strCardAddr, strDeviceID, strIP, strPort, strLedType, strControlCardType, strHeight, strWidth, strPrgmType, strPrgmFontSize, strPrgmContent, strPrfmIndex, strPrgmEffect, strPrgmStayTime, strPrgmPlaySpeed);
				//if (t2.joinable())
				//{
				//	t2.detach();
				//}
				Sleep(10);
			}
		}
	}
	else
	{
		CString strBody = "";
		strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", "error id", strPublicUser, strPublicTime, strPrgmID);
		BOOL IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
		if (IsSuccess)
		{
			tips(_T("[DealPublicPrgm]--解析json的body字段失败，上送下发状态成功"));
			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--解析json的body字段失败,上送下发状态成功");
		}
		else
		{
			tips(_T("[DealPublicPrgm]--解析json的body字段失败，上送下发状态失败"));
			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--解析json的body字段失败,上送下发状态失败");
		}
	}
	LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--发布节目结束");
}


BOOL CLedCtrlServerDlg:: SendToEQ(
	CString strHttpAddr
	,CString strLedType
	,CString strDeviceModel
	,CString strIP
	,CString strPrgmEffect
	,CString strPrgmContent
	,CString strHeight
	,CString strWidth
	,CString strPrgmFontSize
	,CString strPrgmPlaySpeed
	,CString strPrgmStayTime
	,CString strDeviceID
	,CString strPublicUser
	,CString strPublicTime
	,CString strPrgmID)
{
	CString strFilepath = GetFullPath("EQ2008_Dll_Set.ini");
	strFilepath.Replace("/", "\\");

	clock_t start, end;
	start = clock();		//函数开始计时
	BOOL IsSuccess = EQSendPrgm(strFilepath.GetBuffer(0), strLedType, strDeviceModel, strIP, strPrgmEffect, strPrgmContent, strHeight, strWidth, strPrgmFontSize, strPrgmPlaySpeed, strPrgmStayTime);
	end = clock();
	double endtime = (double)(end - start) / CLOCKS_PER_SEC;

	pool_UploadStauts->enqueue([=]() {
		CString strBody = "";
		CString strTips = "";

		if (IsSuccess)
		{
			strBody.Format("\"itemtype\":\"3\",\"status\":\"0\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", strDeviceID, strPublicUser, strPublicTime, strPrgmID);
			BOOL IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
			if (IsSuccess)
			{
				strTips.Format("[DealPublicPrgm]--诣阔控制卡节目下发成功[%s],耗时%f", strIP,endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]-诣阔卡下发节目成功[%s][%s]", strIP, strPrgmID);
			}
			else
			{
				strTips.Format("[DealPublicPrgm]--诣阔控制卡节目下发成功[%s],耗时%f", strIP, endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--诣阔控制卡节目下发成功,上送节目下发结果失败[%s][%s]", strIP, strPrgmID);
			}
		}
		else
		{
			strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", strDeviceID, strPublicUser, strPublicTime, strPrgmID);
			BOOL IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
			if (IsSuccess)
			{
				strTips.Format("[DealPublicPrgm]--诣阔控制卡节目下发失败[%s],耗时%f", strIP, endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--诣阔控制卡下发节目失败，上送节目下发状态成功[%s][%s]", strIP, strPrgmID);
			}
			else
			{
				strTips.Format("[DealPublicPrgm]--诣阔控制卡节目下发失败[%s],耗时%f", strIP, endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--诣阔控制卡节目下发失败,上送节目下发结果失败[%s][%s]", strIP, strPrgmID);
			}
		}
	});

	return TRUE;
}


BOOL CLedCtrlServerDlg::EQSendPrgm(const char* pFile, CString strLedType, CString strDeviceModel, CString strIP, 
	CString strPrgmEffect, CString strPrgmContent, CString strHeight, CString strWidth, CString strPrgmFontSize,
	CString strPrgmPlaySpeed, CString strPrgmStayTime)
{
	int index = strIP.Find(".");
	CString strIP0 = strIP.Left(index);
	CString strIP_temp = strIP.Mid(index + 1);
	int index1 = strIP_temp.Find(".");
	CString strIP1 = strIP_temp.Left(index1);
	strIP_temp = strIP_temp.Mid(index1 + 1);
	int index2 = strIP_temp.Find(".");
	CString strIP2 = strIP_temp.Left(index2);
	CString strIP3 = strIP_temp.Mid(index2 + 1);
	if (strLedType == "1")
	{
		WritePrivateProfileString("地址：0", "ColorStyle ", "0", pFile);
	}
	else if (strLedType == "2")
	{
		WritePrivateProfileString("地址：0", "ColorStyle ", "1", pFile);
	}
	else
	{
		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[EQSendPrgm]--诣阔暂不支持此种类型的屏幕1代表单色屏，2代表双色屏[%s]", strLedType);
		return FALSE;
	}
	if (strDeviceModel == "EQ3002-I")
	{
		WritePrivateProfileString("地址：0", "CardType ", "0", pFile);
	}
	else if (strDeviceModel == "EQ3002-II")
	{
		WritePrivateProfileString("地址：0", "CardType ", "1", pFile);
	}
	else if (strDeviceModel == "EQ3002-III")
	{
		WritePrivateProfileString("地址：0", "CardType ", "2", pFile);
	}
	else if (strDeviceModel == "EQ2008-I/II")
	{
		WritePrivateProfileString("地址：0", "CardType ", "3", pFile);
	}
	else if (strDeviceModel == "EQ2010-I")
	{
		WritePrivateProfileString("地址：0", "CardType ", "4", pFile);
	}
	else if (strDeviceModel == "EQ2008-IE")
	{
		WritePrivateProfileString("地址：0", "CardType ", "5", pFile);
	}
	else if (strDeviceModel == "EQ2011")
	{
		WritePrivateProfileString("地址：0", "CardType ", "7", pFile);
	}
	else if (strDeviceModel == "EQ2012")
	{
		WritePrivateProfileString("地址：0", "CardType ", "8", pFile);
	}
	else if (strDeviceModel == "EQ2008-M")
	{
		WritePrivateProfileString("地址：0", "CardType ", "9", pFile);
	}
	else if (strDeviceModel == "EQ2013")
	{
		WritePrivateProfileString("地址：0", "CardType ", "21", pFile);
	}
	else if (strDeviceModel == "EQ2023")
	{
		WritePrivateProfileString("地址：0", "CardType ", "22", pFile);
	}
	else if (strDeviceModel == "EQ2033")
	{
		WritePrivateProfileString("地址：0", "CardType ", "23", pFile);
	}
	else
	{
		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[EQSendPrgm]--暂时不支持此种类型的诣阔控制卡[%s]", strDeviceModel);
		return FALSE;
	}
	WritePrivateProfileString("地址：0", "IpAddress0", strIP0, pFile);
	WritePrivateProfileString("地址：0", "IpAddress1", strIP1, pFile);
	WritePrivateProfileString("地址：0", "IpAddress2", strIP2, pFile);
	WritePrivateProfileString("地址：0", "IpAddress3", strIP3, pFile);
	WritePrivateProfileString("地址：0", "ScreemHeight", strHeight, pFile);
	WritePrivateProfileString("地址：0", "ScreemWidth", strWidth, pFile);

	CString strFilepath = GetFullPath("EQ2008_Dll_Set.ini");
	strFilepath.Replace("/", "\\");
	User_ReloadIniFile(strFilepath.GetBuffer(0));
	if (!User_OpenScreen(m_iCardNum))
	{
		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[EQSendPrgm]--打开显示屏失败[%s]", strIP);
		return FALSE;
	}
	else
	{
		BOOL b_ret_clear = User_DelAllProgram(m_iCardNum);
		if (!b_ret_clear)
		{
			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[EQSendPrgm]--删除节目失败[%s]", strIP);
			return FALSE;
		}
		else
		{
			m_iProgramIndex = User_AddProgram(m_iCardNum, FALSE, 60 * 60 * 24);
			if (m_iProgramIndex == -1)
			{
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[EQSendPrgm]--添加节目失败[%s]", strIP);
				return FALSE;
			}
			else
			{
				User_SingleText  SingleText;

				SingleText.BkColor = 0;
				SingleText.chContent = strPrgmContent.GetBuffer(0);
				SingleText.PartInfo.iFrameMode = 0;
				SingleText.PartInfo.iHeight = atoi(strHeight);
				SingleText.PartInfo.iWidth = atoi(strWidth);
				SingleText.PartInfo.iX = 0;
				SingleText.PartInfo.iY = 0;
				SingleText.FontInfo.bFontBold = 0;
				SingleText.FontInfo.bFontItaic = 0;
				SingleText.FontInfo.bFontUnderline = 0;
				SingleText.FontInfo.colorFont = 0xFFFF;
				SingleText.FontInfo.iFontSize = atoi(strPrgmFontSize);    //字体大小
				SingleText.PartInfo.FrameColor = 0;
				SingleText.FontInfo.strFontName = "";  //字体名称
				SingleText.FontInfo.iAlignStyle = 0;   //对齐方式 0 －左对齐  1 －居中  2 －右对齐
				SingleText.FontInfo.iVAlignerStyle = 0;
				SingleText.MoveSet.bClear = 0;
				if (strDeviceModel == "EQ2013" || strDeviceModel == "EQ2023" || strDeviceModel == "EQ2033")
				{
					if (atoi(strPrgmPlaySpeed) > 10)
					{
						SingleText.MoveSet.iActionSpeed = 10;
					}
					else
					{
						SingleText.MoveSet.iActionSpeed = atoi(strPrgmPlaySpeed);
					}
					SingleText.MoveSet.iFrameTime = 50;
					if (strPrgmEffect == "1")
					{
						SingleText.MoveSet.iActionType = 1;     //立即显示
					}
					else if (strPrgmEffect == "2")
					{
						SingleText.MoveSet.iActionType = 3;     //连续左移
					}
					else if (strPrgmEffect == "3")
					{
						SingleText.MoveSet.iActionType = 7;     //下移
					}
					else if (strPrgmEffect == "4")
					{
						SingleText.MoveSet.iActionType = 4;     //右移
					}
					else if (strPrgmEffect == "5")
					{
						SingleText.MoveSet.iActionType = 5;     //上移
					}
					else
					{
						SingleText.MoveSet.iActionType = 1;     //立即显示
					}
				}
				else
				{
					SingleText.MoveSet.iActionSpeed = 1;   //播放速度
					SingleText.MoveSet.iFrameTime = (11 - atoi(strPrgmPlaySpeed)) * 20; //播放速度
					if (strPrgmEffect == "1")
					{
						SingleText.MoveSet.iActionType = 1;     //立即显示
					}
					else if (strPrgmEffect == "2")
					{
						SingleText.MoveSet.iActionType = 20;     //左移
					}
					else if (strPrgmEffect == "3")
					{
						SingleText.MoveSet.iActionType = 23;     //下移
					}
					else if (strPrgmEffect == "4")
					{
						SingleText.MoveSet.iActionType = 21;     //右移
					}
					else if (strPrgmEffect == "5")
					{
						SingleText.MoveSet.iActionType = 22;     //上移
					}
					else
					{
						SingleText.MoveSet.iActionType = 1;     //立即显示
					}
				}
				SingleText.MoveSet.iHoldTime = 10 * (atoi(strPrgmStayTime));    //停留时间
				SingleText.MoveSet.iClearActionType = 0;
				SingleText.MoveSet.iClearSpeed = 4;
				if (-1 == User_AddSingleText(m_iCardNum, &SingleText, m_iProgramIndex))
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[EQSendPrgm]--添加单行文本失败[%s]", strIP);
					return FALSE;
				}
				else
				{
					if (!User_SendToScreen(m_iCardNum))
					{
						LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[EQSendPrgm]--发送文本失败[%s]", strIP);
						return FALSE;
					}
					else
					{
						return TRUE;
					}
				}
			}
		}
	}

}

BOOL CLedCtrlServerDlg::SendToCLQ(
	CString strHttpAddr
	, CString strLedType
	, CString strDeviceModel
	, CString strPort
	, CString strIP
// 	, CString strPrgmEffect
	, CString strPrgmContent
	, CString strHeight
	, CString strWidth
	, CString strPrgmFontSize
	, CString strPrgmPlaySpeed
// 	, CString strPrgmStayTime
	, CString strDeviceID
	, CString strPublicUser
	, CString strPublicTime
	, CString strPrgmID) 
{
	//IsSuccess = CLSendPrgm(strLedType, strDeviceModel, strIP, strPort, strPrgmContent, strHeight, strWidth, strPrgmFontSize, strPrgmPlaySpeed);
	clock_t start, end;
	start = clock();		//函数开始计时

	CString strBody = "";
	BOOL IsSuccess = FALSE;
	if (strDeviceModel == "CL3000")
	{

	}
	else if (strDeviceModel == "SCL2008")
	{
		char    S[1024];
		BOOL    bOK;
		FILE    *F;
		int     Da, Ti;

		// Clear LED
		sprintf(S, "`R00000000%04d%04d", atoi(strWidth), atoi(strHeight));

		// Use 6x12,12x12 fonts
		strcat(S, "   `A1`H2`C0000FF红色12点显示");
		strcat(S, "\n\r");

		// Use 8x16,16x16 fonts
		strcat(S, "`A3`H4`C00FF00绿色16点显示AB");

		// Use 12x24,24x24 fonts
		strcat(S, "`A5`H6`C00FFFF黄色24点显示CD`Y000");

		// Use 16x32,32x32 fonts
		strcat(S, "`M3`A7`H8`C00FFFF反白32点显示EF");

		// 保存为文本文件
		F = fopen(FileName, "w+t");
		fprintf(F, "%s", S);
		fclose(F);

		// 通讯初始化
		bOK = scl2008.SCL_NetInitial(1, "", strIP.GetBuffer(0), 20, 0, atoi(strPort), TRUE);
		if (!bOK)  goto Thread;
		// 发送文件
		if (bOK)
		{
			// 拆分的发送文本文件
			scl2008.SCL_GetFileDosDateTime(FileName, &Da, &Ti);
			bOK = scl2008.SCL_SendData(1, 0, strlen(S), (BYTE*)S);
			if (bOK) bOK = scl2008.SCL_SaveFile(1, 2, FileName, strlen(S), Da, Ti);
			if (!bOK) goto Thread;
		}
		// 通知控制器重新播放节目
		if (bOK)
		{
			bOK = scl2008.SCL_Replay(1, 0, 0);
			if (!bOK)  goto Thread;
		}
		scl2008.SCL_Close(1);
	}
	else
	{

	}
	IsSuccess = TRUE;
Thread:
	end = clock();
	double endtime = (double)(end - start) / CLOCKS_PER_SEC;
	pool_UploadStauts->enqueue([=]() {
		CString strTips = "";
		CString strBody = "";
		if (IsSuccess)
		{
			strBody.Format("\"itemtype\":\"3\",\"status\":\"0\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"",
				strDeviceID, strPublicUser, strPublicTime, strPrgmID);
			BOOL IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
			if (IsSuccess)
			{
				strTips.Format("[DealPublicPrgm]--励研控制卡节目下发成功[%s],耗时%f", strIP, endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]-励研控制卡下发节目成功[%s][%s]", strIP, strPrgmID);
			}
			else
			{
				strTips.Format("[DealPublicPrgm]--励研控制卡节目下发成功[%s],耗时%f", strIP, endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--励研控制卡节目下发成功,上送节目下发结果失败[%s][%s]", strIP, strPrgmID);
			}
		}
		else {
			strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", strDeviceID, strPublicUser, strPublicTime, strPrgmID);
			BOOL IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
			if (IsSuccess)
			{
				strTips.Format("[DealPublicPrgm]--励研控制卡节目下发失败[%s],耗时%f", strIP, endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--励研卡节目下发失败[%s][%s]", strIP, strPrgmID);
			}
			else
			{
				strTips.Format("[DealPublicPrgm]--励研控制卡节目下发失败[%s],耗时%f", strIP, endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--励研卡下发失败,上送节目下发结果失败[%s][%s]", strIP, strPrgmID);
			}
		}

		
	});
	return TRUE;
}


	BOOL CLedCtrlServerDlg::SendToBX(
		CString strHttpAddr
		, CString strLedType
		, CString strDeviceModel
		, CString strIP
		, CString strPort
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
		, CString strPrgmID)
	{
		CString strBody = "";
		CString strTips = "";
		BOOL IsSuccess = FALSE;
		clock_t start, end;
		start = clock();		//函数开始计时

		IsSuccess = onbon.PublishPrograms(strIP, strPort, strLedType, strDeviceModel, strPrgmContent, atoi(strWidth), atoi(strHeight),
			atoi(strPrgmFontSize), atoi(strPrgmEffect), atoi(strPrgmPlaySpeed), atoi(strPrgmStayTime));
		end = clock();
		double endtime = (double)(end - start) / CLOCKS_PER_SEC;
		pool_UploadStauts->enqueue([=]() {
			CString strTips = "";
			CString strBody = "";
			if (IsSuccess)
			{
				strBody.Format("\"itemtype\":\"3\",\"status\":\"0\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", strDeviceID, strPublicUser, strPublicTime, strPrgmID);
				BOOL IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
				if (IsSuccess)
				{
					strTips.Format("[DealPublicPrgm]--仰邦控制卡节目下发成功[%s],耗时%f", strIP, endtime);
					tips(strTips);
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--仰邦卡下发节目成功[%s][%s]", strIP, strPrgmID);
				}
				else
				{
					strTips.Format("[DealPublicPrgm]--仰邦控制卡节目下发成功[%s],耗时%f", strIP, endtime);
					tips(strTips);
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--仰邦卡节目下发成功,上送节目下发结果失败[%s][%s]", strIP, strPrgmID);
				}
			}
			else
			{
				strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", strDeviceID, strPublicUser, strPublicTime, strPrgmID);
				BOOL IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
				if (IsSuccess)
				{
					strTips.Format("[DealPublicPrgm]--仰邦控制卡节目下发失败[%s],耗时%f", strIP, endtime);
					tips(strTips);
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--仰邦卡节目下发失败[%s][%s]", strIP, strPrgmID);
				}
				else
				{
					strTips.Format("[DealPublicPrgm]--仰邦控制卡节目下发失败[%s],耗时%f", strIP, endtime);
					tips(strTips);
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--仰邦卡下发失败,上送节目下发结果失败[%s][%s]", strIP, strPrgmID);
				}
			}
		});

		return TRUE;
		
	}

	BOOL CLedCtrlServerDlg::SendToVSA(
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
		, CString strPrgmID)
	{
		//打开设备
		CString strBody = "";
		BOOL IsSuccess = FALSE;
		CString strTips = "";
		BOOL bRet = vsa.LED_VSAOpenDevice();
		if (bRet)
		{
			strBody = "";
			strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", strDeviceID, strPublicUser, strPublicTime, strPrgmID);
			IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
			strTips.Format("[DealPublicPrgm]---视展控A卡打开设备失败[%s");
			tips(strTips);
			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--视展控A卡节目下发失败[%s][%s]", strIP, strPrgmID);
		}
		else
		{
			clock_t start, end;
			start = clock();		//函数开始计时
			vsa.LED_VSASendPrgm(atoi(strWidth), atoi(strHeight), strPrgmContent, atoi(strPrgmEffect), atoi(strPrgmPlaySpeed), 0, strIP);
			end = clock();
			double endtime = (double)(end - start) / CLOCKS_PER_SEC;

			pool_UploadStauts->enqueue([=]() {
				CString strTips = "";
				CString strBody = "";
				BOOL IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
				if (IsSuccess)
				{
					strTips.Format("[DealPublicPrgm]--视展控A卡节目下发成功[%s],耗时%f", strIP, endtime);
					tips(strTips);
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--视展控A卡下发节目成功[%s][%s]", strIP, strPrgmID);
				}
				else
				{
					strTips.Format("[DealPublicPrgm]--视展控控A卡节目下发成功[%s],耗时%f", strIP, endtime);
					tips(strTips);
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]---视展控A卡下发节目成功,上送节目下发结果失败[%s][%s]", strIP, strPrgmID);
				}
			});
			return TRUE;

		}

	}
	BOOL CLedCtrlServerDlg::SendToVSD(
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
		, CString strPrgmID)
	{
		CString strBody = "";
		BOOL IsSuccess = FALSE;
		clock_t start, end;
		start = clock();		//函数开始计时

		int nRet = vsd.LED_VSDSendPrgm(strIP, strPort, strLedType, atoi(strWidth), atoi(strHeight), strPrgmContent, strPrgmFontSize,
			atoi(strPrgmEffect), atoi(strPrgmPlaySpeed));
		end = clock();
		double endtime = (double)(end - start) / CLOCKS_PER_SEC;

		pool_UploadStauts->enqueue([=]() {
			BOOL IsSuccess = FALSE;
			CString strBody = "";
			CString strTips = "";

			if (nRet != 0)
			{
				strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", strDeviceID, strPublicUser, strPublicTime, strPrgmID);
				IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
				strTips.Format("[DealPublicPrgm]--视展控D卡节目下发失败[%s],耗时%f", strIP, endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--视展控D卡节目下发失败[%s][%s]", strIP, strPrgmID);
			}
			else
			{
				strBody = "";
				strBody.Format("\"itemtype\":\"3\",\"status\":\"0\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", strDeviceID, strPublicUser, strPublicTime, strPrgmID);
				IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
				if (IsSuccess)
				{
					strTips.Format("[DealPublicPrgm]--视展控D卡节目下发成功[%s],耗时%f", strIP, endtime);
					tips(strTips);
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--视展控D卡下发节目成功[%s][%s]", strIP, strPrgmID);
				}
			}
		});
		return TRUE;
}
