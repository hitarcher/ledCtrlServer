
// LedCtrlServerDlg.cpp : ʵ���ļ�
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
//��������ָ�뺯��  
ICMPCREATEFILE pIcmpCreateFile;
ICMPCLOSEHANDLE pIcmpCloseHandle;
ICMPSENDECHO pIcmpSendEcho;
// �������ܣ���ʼ��ICMP������
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

// �������ܣ��ж��Ƿ���pingͨIP
// ����������IP��ַ������

BOOL ICMPPing(char* host)
{
	DWORD timeOut = 1000;                                              //���ó�ʱ  
	ULONG hAddr = inet_addr(host);                                     //�����IP��ַ��ֱ��ת��  
	if (hAddr == INADDR_NONE)
	{
		hostent* hp = gethostbyname(host);                             //�������������DNS������IP��ַ  
		if (hp)
			memcpy(&hAddr, hp->h_addr_list, hp->h_length);             //IP��ַ  
		else
		{
			return FALSE;
		}
	}
	HANDLE hIp = pIcmpCreateFile();
	IP_OPTION_INFORMATION ipoi;
	memset(&ipoi, 0, sizeof(IP_OPTION_INFORMATION));
	ipoi.Ttl = 128;                  //Time-To-Live  
	unsigned char pSend[36];                                                                   //���Ͱ�  
	memset(pSend, 'E', 32);
	int repSize = sizeof(ICMP_ECHO_REPLY) + 32;
	unsigned char pReply[100];                                                                 //���հ�  
	ICMP_ECHO_REPLY* pEchoReply = (ICMP_ECHO_REPLY*)pReply;
	DWORD nPackets = pIcmpSendEcho(hIp, hAddr, pSend, 32, &ipoi, pReply, repSize, timeOut); //����ICMP���ݱ���  
	if (pEchoReply->Status != 0)                                                    //��ʱ������������������ICMP ����Ŀ������������ 
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
#define FileName            "Test.Txt"      // �ı��ļ���


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
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// CLedCtrlServerDlg �Ի���

CLedCtrlServerDlg::CLedCtrlServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LEDCTRLSERVER_DIALOG, pParent)
{
	g_CLedCtrlServerDlg = this;
	m_MMPDeviceCode = "";
	m_MMPDeviceIP = "";
	//RMQ
	m_hRMQ = NULL;
	m_hRMQEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//ǩ��
	m_hReSign = NULL;
	m_hReSignEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//�ϴ��豸״̬
	m_hDviceStatus = NULL;
	m_hDviceStatusEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	//���ƿ���ַ
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

// CLedCtrlServerDlg ��Ϣ�������

BOOL CLedCtrlServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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
	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// �����̳߳�
	pool_EQ = new threadpool(1);
	pool_CL = new threadpool(1);
	pool_BX = new threadpool(1);
	pool_VSA = new threadpool(1);
	pool_VSD = new threadpool(1);
	pool_UploadStauts = new threadpool(1);

	//TODO:�ڴ���Ӷ���ĳ�ʼ������
	//��ȥƽ̨ǩ�����õ�������
	BOOL bResult = g_Config.LoadUrl();
	if (!bResult)
	{
		LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "[OnInitDialog]--��ȡ�����ļ��е�ƽ̨��ַ�ֶ�ʧ�ܣ�");
		tips(_T("[OnInitDialog]--��ȡ�����ļ��е�ƽ̨��ַ�ֶ�ʧ�ܣ�"));
		return FALSE;
	}
	DWORD dwThreadId = 0;
	m_hReSign = CreateThread(NULL, 0, ReSignThreadProc, this, 0, &dwThreadId);
	LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "[OnInitDialog]--CreateThread ReSignThreadProc");
	tips(_T("[OnInitDialog]--CreateThread ReSignThreadProc"));
	SetTimer(TIMER_RESIGN, 10, NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLedCtrlServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLedCtrlServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLedCtrlServerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	KillTimer(nIDEvent);
	switch (nIDEvent)
	{
	case TIMER_RESIGN:
		SetEvent(m_hReSignEvent);
		break;
	case TIMER_RECV_MSG:				//��ȡ����
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
	// TODO: �ڴ˴������Ϣ����������
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
	//��չVSA
	vsa.Destroy();
	vsa.Preview_VSAFinalize();
	//��չVSD
	vsd.LED_VSDDestroy();
	onbon.OnbonReleaseSdk();
	//����SCL2008
	scl2008.LED_SCL2008FreeDll();
	LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "[OnDestroy]--�����˳�");
}

BOOL CLedCtrlServerDlg::LoadDeviceConfig()
{
	if (FALSE == g_Config.LoadBaseCfg())
	{
		AfxMessageBox(g_Config.GetLastErr());
		EndDialog(FALSE);
		return FALSE;
	}
	tips(_T("��ʼ����ʼ"));
	//���������־
	DeleteLog(GetFullPath("LOG").GetBuffer(0), g_Config.m_nDelLogDay);
	// �������ж�̬���ӿ�
	if (!LoadMiniLEDdll())
	{
		MessageBox("��̬���ӿ��ʼ��ʧ��", "MiniLED", MB_OK);
		SendMessage(WM_CLOSE, 0, 0L);
		return FALSE;
	}
	// ���붯̬���ӿ�"MiniUtil.Dll"�����У�
	hMU_DLL = LoadLibrary("MiniUtil.Dll");
	if (hMU_DLL != NULL)
	{
		MC_PicToXMPXFile = (_MC_PicToXMPXFile)::GetProcAddress(hMU_DLL, "MC_PicToXMPXFile");
	}
	// �жϺ���ָ���ȡ�ɹ���
	if ((!hMU_DLL) || (!MC_PicToXMPXFile))
	{
		FreeLibrary(hMU_DLL);
		hMU_DLL = NULL;
		MessageBox("��̬���ӿ��ʼ��ʧ��", "MiniUtil", MB_OK);
		SendMessage(WM_CLOSE, 0, 0L);
		return FALSE;
	}
	//add by Chengzhi
	//VSA��ʼ��
	BOOL bInitVSAOk = FALSE;
	bInitVSAOk = vsa.LED_VSAInitialize();
	if (!bInitVSAOk)
	{
		MessageBox("��̬���ӿ��ʼ��ʧ��", "LEDSender", MB_OK);
		SendMessage(WM_CLOSE, 0, 0L);
		return FALSE;
	}
	vsa.Preview_VSAInitialize();
	//��ʼ����չD����̬��
	BOOL bInitVSDOk = FALSE;
	bInitVSDOk = vsd.LED_VSDInitialize();
	if (!bInitVSAOk)
	{
		MessageBox("��̬���ӿ��ʼ��ʧ��", "LEDSender2010", MB_OK);
		SendMessage(WM_CLOSE, 0, 0L);
		return FALSE;
	}
	//��ʼ������BX-5��̬���ӿ�
	BOOL bIsLoadDll = onbon.InitOnbonSdk();
	if (!bIsLoadDll)
	{
		MessageBox("��̬���ӿ��ʼ��ʧ��", "bx_sdk_dual.dll", MB_OK);
		SendMessage(WM_CLOSE, 0, 0L);
		return FALSE;
	}
	BOOL bIsLoadSCLDll = scl2008.LED_SCL2008Initialize();
	if (!bIsLoadDll)
	{
		MessageBox("��̬���ӿ��ʼ��ʧ��", "SCL_API_stdcall.dll", MB_OK);
		SendMessage(WM_CLOSE, 0, 0L);
		return FALSE;
	}
	BOOL bLoadPingDll = InitIcmp();
	if (!bLoadPingDll)
	{
		MessageBox("��̬���ӿ��ʼ��ʧ��", "icmp.dll", MB_OK);
		SendMessage(WM_CLOSE, 0, 0L);
		return FALSE;
	}

	m_bExit = FALSE;

	DWORD dwThreadId = 0;
	m_hRMQ = CreateThread(NULL, 0, RMQThreadProc, this, 0, &dwThreadId);
	m_hDviceStatus = CreateThread(NULL, 0, DeviceStatusThreadProc, this, 0, &dwThreadId);

	if (FALSE == LoadRMQPubAndRMQSUBDLL())
	{
		LOG(LOGTYPE_DEBUG, SERVERLOG, "[LoadDeviceConfig]-��̬�����ʧ��:[%s]", m_strLastErr);
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
	//�ϴ�������ն��豸״̬
	BOOL bIsPing = ICMPPing(strIP.GetBuffer(0));
	if (bIsPing)
	{
		BOOL bRet = m_toolTrade.UpLoadMMPDeviceStatus(g_Config.m_strHttpUrl, strCode);
		LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "DeviceStatusThreadContent--[%s]", "��������������豸״̬�ӿ�");
		if (bRet)
		{
			CTime tmBegin = CTime::GetCurrentTime();
			CString str_Begin = tmBegin.Format("%Y%m%d%H%M%S");
			LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "DeviceStatusThreadContent--[������豸������״̬�ϴ��ɹ���][%s],[%s]", str_Begin, m_MMPDeviceCode);
		}
		else
		{
			CTime tmBegin = CTime::GetCurrentTime();
			CString str_Begin = tmBegin.Format("%Y%m%d%H%M%S");
			LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "DeviceStatusThreadContent--[������豸״̬���ߵ�״̬�ϴ�ʧ�ܣ�][%s],[%s]", str_Begin, m_MMPDeviceCode);
		}
	}
	else
	{
		CTime tmBegin = CTime::GetCurrentTime();
		CString str_Begin = tmBegin.Format("%Y%m%d%H%M%S");
		LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "DeviceStatusThreadContent--[������豸����],[%s],[%s],[%s]", str_Begin, m_MMPDeviceCode, m_MMPDeviceIP);
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
		m_strLastErr = "RMQ_SUB��̬�����ʧ��...";
		goto EXIT;
	}
	if (NULL == _RMQ_CALLBACK)
	{
		m_strLastErr = "_RMQ_CALLBACK����ʧ��...";
		goto EXIT;
	}
	if (NULL == _RMQ_SUB)
	{
		m_strLastErr = "_RMQ_SUB����ʧ��...";
		goto EXIT;
	}
	_RMQ_CALLBACK(_Recv);
	LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[LoadRMQPubAndRMQSUBDLL]--��̬��RMQ.dll���سɹ�");
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
		LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQSUBConnect]--�����ļ�������д�쳣...");
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
		LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQSUBConnect]--RMQ����ʧ��...");
		return FALSE;
	}
	LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQSUBConnect]--RMQ���ӳɹ�...");
	return TRUE;
}

BOOL CLedCtrlServerDlg::RMQ_DealCustomMsg(CString strMsg)
{
	LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQ_DealCustomMsg]--RMQ�յ���Ϣ[%s]", strMsg);
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
				strJsonIn.Format("\"itemtype\":\"%d\",\"deviceIDs\":\"%s\",\"itemId\":\"%s\"", 3, m_strMMPIDlist, m_strPrgmID);//3�����������Ŀ
				BOOL bRet = m_toolTrade.GetPrgms(g_Config.m_strHttpUrl, strJsonIn, m_strPrgmJson);
				if (bRet)
				{
					LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQ_DealCustomMsg]--���ؽ�Ŀjson�ɹ�[%s]", m_strPrgmJson);
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
						tips(_T("[RMQ_DealCustomMsg]--����ƽ̨��Ŀ�����ӿ�ʧ�ܣ�"));
						LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQ_DealCustomMsg]--[m_toolTrade.GetPrgms][err][%s]", m_toolTrade.GetLastErr());
					}
				}
			}
			else
			{
				LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQ_DealCustomMsg]--[RMQ_DealCustomMsg][err][δ֪�豸][%s]", vct[1]);
			}
		}
		else if (vct[0].CompareNoCase("OFFLINE") == 0)
		{
			if (vct.size() == 5)
			{
				LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQ_DealCustomMsg]--�յ�ƽ̨���͵�����������ն��豸״̬����Ϣ");
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
				LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQ_DealCustomMsg]--�յ�ƽ̨���͵�������ת����״̬����Ϣ");
				SetEvent(m_hDviceStatusEvent);
			}
		}
		else
		{
			// δ֪��Ϣ
			LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQ_DealCustomMsg]--[RMQ_DealCustomMsg][err][δ֪��Ϣ][%s]", vct[0]);
		}
	}
	else
	{
		// ���ĸ�ʽ��
		LOG_DD(LOGTYPE_DEBUG, RMQLOG, "[RMQ_DealCustomMsg]--[RMQ_DealCustomMsg][err][���ĸ�ʽ��][%s]", strMsg);
	}
	return TRUE;
}

/********************************************************************/
/*              �豸ǩ��������״̬�Լ�����MQ��Ϣ�߳�                */
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
				//ǩ��ʧ�ܣ�10s����ǩ��һ��
				SetTimer(TIMER_RESIGN, 10 * 1000, NULL);
				icount++;
				if (icount == 2)
				{
					LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "[ReSignThreadContent]--[%s]", "ǩ��ʧ��...");
					tips(_T("[ReSignThreadContent]--ǩ��ʧ��..."));
				}
			}
			else
			{
				icount = 0;
				LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "[ReSignThreadContent]--[%s]", "ǩ���ɹ���");
				tips(_T("[ReSignThreadContent]--ǩ���ɹ�"));
				//ǩ���ɹ���ͨ�����Ļ�ȡ��������Ȼ���ٶ�ȡ�����ļ�
				BOOL bRent = LoadDeviceConfig();
				if (!bRent)
				{
					LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "[ReSignThreadContent]--[%s]", "�����ʼ��ʧ��...");
					tips(_T("[ReSignThreadContent]--�����ʼ��ʧ��..."));
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
			//�ϴ��豸״̬
			BOOL bRet = m_toolTrade.UpLoadDeviceStatus(g_Config.m_strHttpUrl);
			if (bRet)
			{
				CTime tmBegin = CTime::GetCurrentTime();
				CString str_Begin = tmBegin.Format("%Y%m%d%H%M%S");
				LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "DeviceStatusThreadContent--[�豸״̬�ϴ��ɹ���][%s]", str_Begin);
			}
			else
			{
				CTime tmBegin = CTime::GetCurrentTime();
				CString str_Begin = tmBegin.Format("%Y%m%d%H%M%S");
				LOG_DD(LOGTYPE_DEBUG, SERVERLOG, "DeviceStatusThreadContent--[�豸״̬�ϴ�ʧ�ܣ�][%s]", str_Begin);
			}
		}
		ResetEvent(m_hDviceStatusEvent);
	}
	return TRUE;
}

/**********************************************************************/
/*                   ����Json��������Ŀ�����߳�                       */
/**********************************************************************/

void CLedCtrlServerDlg::ThreadPoolPublishPrgm(CString strHttpAddr,CString strPrgmID, CString strPublicUser, CString strPublicTime, CString strDeviceModel, CString strCardAddr, CString strDeviceID, CString strIP, CString strPort, CString strLedType, CString strControlCardType, CString strHeight, CString strWidth, CString strPrgmType, CString strPrgmFontSize, CString strPrgmContent, CString strPrfmIndex, CString strPrgmEffect, CString strPrgmStayTime, CString strPrgmPlaySpeed)
{
	//�ײ�sdk�������̳߳������ĵ��÷����ᵼ�³�����������á�
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
	//			tips(_T("[ThreadPoolPublishPrgm]--�������ƿ���Ŀ�·��ɹ�"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]-�������·���Ŀ�ɹ�[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//		else
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--�������ƿ���Ŀ�·��ɹ�"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--�������ƿ���Ŀ�·��ɹ�,���ͽ�Ŀ�·����ʧ��[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//	}
	//	else
	//	{
	//		strBody = "";
	//		strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", t_strDeviceID, t_strPublicUser, t_strPublicTime, t_strPrgmID);
	//		IsSuccess = m_toolTrade.UpLoadProGrameStatus(t_strHttpAddr, strBody);
	//		if (IsSuccess)
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--�������ƿ���Ŀ����ʧ��"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--�������ƿ��·���Ŀʧ�ܣ����ͽ�Ŀ�·�״̬�ɹ�[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//		else
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--�������ƿ���Ŀ����ʧ��"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--�������ƿ���Ŀ�·�ʧ��,���ͽ�Ŀ�·����ʧ��[%s][%s]", t_strIP, t_strPrgmID);
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
	//			tips(_T("[ThreadPoolPublishPrgm]--���п��ƿ���Ŀ�·��ɹ�"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]-���п��ƿ��·���Ŀ�ɹ�[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//		else
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--���п��ƿ���Ŀ�·��ɹ�"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--���п��ƿ���Ŀ�·��ɹ�,���ͽ�Ŀ�·����ʧ��[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//	}
	//	else
	//	{
	//		strBody = "";
	//		strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", t_strDeviceID, t_strPublicUser, t_strPublicTime, t_strPrgmID);
	//		IsSuccess = m_toolTrade.UpLoadProGrameStatus(t_strHttpAddr, strBody);
	//		if (IsSuccess)
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--���п���Ŀ�·�ʧ��!"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--���п���Ŀ�·�ʧ��[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//		else
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--���п��·�ʧ��,���ͽ�Ŀ�·����ʧ��"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--���п��·�ʧ��,���ͽ�Ŀ�·����ʧ��[%s][%s]", t_strIP, t_strPrgmID);
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
	//			tips(_T("[ThreadPoolPublishPrgm]--����·���Ŀ�ɹ�"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--����·���Ŀ�ɹ�[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//		else
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--�����Ŀ�·��ɹ�"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--�����Ŀ�·��ɹ�,���ͽ�Ŀ�·����ʧ��[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//	}
	//	else
	//	{
	//		strBody = "";
	//		strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", t_strDeviceID, t_strPublicUser, t_strPublicTime, t_strPrgmID);
	//		IsSuccess = m_toolTrade.UpLoadProGrameStatus(t_strHttpAddr, strBody);
	//		if (IsSuccess)
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--�����Ŀ�·�ʧ��!"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--�����Ŀ�·�ʧ��[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//		else
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--�����Ŀ�·�ʧ��"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--����·�ʧ��,���ͽ�Ŀ�·����ʧ��[%s][%s]", t_strIP, t_strPrgmID);
	//		}
	//	}
	//}
	//else if (t_strDeviceModel == "VSA")
	//{
	//	//���豸
	//	BOOL bRet = vsa.LED_VSAOpenDevice();
	//	if (bRet)
	//	{
	//		strBody = "";
	//		strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", t_strDeviceID, t_strPublicUser, t_strPublicTime, t_strPrgmID);
	//		IsSuccess = m_toolTrade.UpLoadProGrameStatus(t_strHttpAddr, strBody);
	//		tips(_T("[ThreadPoolPublishPrgm]--��չA�����豸ʧ��!"));
	//		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--��չA����Ŀ�·�ʧ��[%s][%s]", t_strIP, t_strPrgmID);
	//	}
	//	else
	//	{
	//		vsa.LED_VSASendPrgm(atoi(t_strWidth), atoi(t_strHeight), t_strPrgmContent, atoi(t_strPrgmEffect), atoi(t_strPrgmPlaySpeed), 0, t_strIP);
	//		IsSuccess = m_toolTrade.UpLoadProGrameStatus(t_strHttpAddr, strBody);
	//		if (IsSuccess)
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--��չA���·���Ŀ�ɹ�"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--��չA���·���Ŀ�ɹ�[%s][%s]", t_strIP, t_strPrgmID);
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
	//		tips(_T("[ThreadPoolPublishPrgm]--��չD��������Ŀʧ��!"));
	//		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--��չD����Ŀ�·�ʧ��[%s][%s]", t_strIP, t_strPrgmID);
	//	}
	//	else
	//	{
	//		strBody = "";
	//		strBody.Format("\"itemtype\":\"3\",\"status\":\"0\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", t_strDeviceID, t_strPublicUser, t_strPublicTime, t_strPrgmID);
	//		IsSuccess = m_toolTrade.UpLoadProGrameStatus(t_strHttpAddr, strBody);
	//		if (IsSuccess)
	//		{
	//			tips(_T("[ThreadPoolPublishPrgm]--��չD���·���Ŀ�ɹ�"));
	//			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--��չD���·���Ŀ�ɹ�[%s][%s]", t_strIP, t_strPrgmID);
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
	//		tips(_T("[ThreadPoolPublishPrgm]--�·�ʧ�ܣ���֧�ִ��ֿ��ƿ�"));
	//		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--��֧�ִ��ֿ��ƿ�[%s]", t_strDeviceModel);
	//	}
	//	else
	//	{
	//		tips(_T("[ThreadPoolPublishPrgm]--�·�ʧ��,���ͽ�Ŀ�·����ʧ��"));
	//		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[ThreadPoolPublishPrgm]--���ͽ�Ŀ�·����ʧ��[%s]", t_strPrgmID);
	//	}
	//}
}

void CLedCtrlServerDlg::DealPublicPrgm(CString strJson,CString strUrl,CString strUser,CString strTime,CString strID)
{
	LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--��ʼ������Ŀ");
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
						strTips.Format("[DealPublicPrgm]--�·�ʧ�ܣ���֧�ִ��ֿ��ƿ�[%s][%s]", strDeviceModel, strIP);
						tips(strTips);
						LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--��֧�ִ��ֿ��ƿ�[%s][%s]", strDeviceModel, strIP);
					}
					else
					{
						strTips.Format("[DealPublicPrgm]--�·�ʧ��,��֧�ִ��ֿ��ƿ�,���ͽ�Ŀ�·����ʧ��[%s][%s]", strDeviceModel, strIP);
						tips(strTips);
						LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--���ͽ�Ŀ�·����ʧ��[%s][%s]", strPrgmID, strIP);
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
			tips(_T("[DealPublicPrgm]--����json��body�ֶ�ʧ�ܣ������·�״̬�ɹ�"));
			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--����json��body�ֶ�ʧ��,�����·�״̬�ɹ�");
		}
		else
		{
			tips(_T("[DealPublicPrgm]--����json��body�ֶ�ʧ�ܣ������·�״̬ʧ��"));
			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--����json��body�ֶ�ʧ��,�����·�״̬ʧ��");
		}
	}
	LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--������Ŀ����");
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
	start = clock();		//������ʼ��ʱ
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
				strTips.Format("[DealPublicPrgm]--�������ƿ���Ŀ�·��ɹ�[%s],��ʱ%f", strIP,endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]-�������·���Ŀ�ɹ�[%s][%s]", strIP, strPrgmID);
			}
			else
			{
				strTips.Format("[DealPublicPrgm]--�������ƿ���Ŀ�·��ɹ�[%s],��ʱ%f", strIP, endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--�������ƿ���Ŀ�·��ɹ�,���ͽ�Ŀ�·����ʧ��[%s][%s]", strIP, strPrgmID);
			}
		}
		else
		{
			strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", strDeviceID, strPublicUser, strPublicTime, strPrgmID);
			BOOL IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
			if (IsSuccess)
			{
				strTips.Format("[DealPublicPrgm]--�������ƿ���Ŀ�·�ʧ��[%s],��ʱ%f", strIP, endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--�������ƿ��·���Ŀʧ�ܣ����ͽ�Ŀ�·�״̬�ɹ�[%s][%s]", strIP, strPrgmID);
			}
			else
			{
				strTips.Format("[DealPublicPrgm]--�������ƿ���Ŀ�·�ʧ��[%s],��ʱ%f", strIP, endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--�������ƿ���Ŀ�·�ʧ��,���ͽ�Ŀ�·����ʧ��[%s][%s]", strIP, strPrgmID);
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
		WritePrivateProfileString("��ַ��0", "ColorStyle ", "0", pFile);
	}
	else if (strLedType == "2")
	{
		WritePrivateProfileString("��ַ��0", "ColorStyle ", "1", pFile);
	}
	else
	{
		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[EQSendPrgm]--�����ݲ�֧�ִ������͵���Ļ1����ɫ����2����˫ɫ��[%s]", strLedType);
		return FALSE;
	}
	if (strDeviceModel == "EQ3002-I")
	{
		WritePrivateProfileString("��ַ��0", "CardType ", "0", pFile);
	}
	else if (strDeviceModel == "EQ3002-II")
	{
		WritePrivateProfileString("��ַ��0", "CardType ", "1", pFile);
	}
	else if (strDeviceModel == "EQ3002-III")
	{
		WritePrivateProfileString("��ַ��0", "CardType ", "2", pFile);
	}
	else if (strDeviceModel == "EQ2008-I/II")
	{
		WritePrivateProfileString("��ַ��0", "CardType ", "3", pFile);
	}
	else if (strDeviceModel == "EQ2010-I")
	{
		WritePrivateProfileString("��ַ��0", "CardType ", "4", pFile);
	}
	else if (strDeviceModel == "EQ2008-IE")
	{
		WritePrivateProfileString("��ַ��0", "CardType ", "5", pFile);
	}
	else if (strDeviceModel == "EQ2011")
	{
		WritePrivateProfileString("��ַ��0", "CardType ", "7", pFile);
	}
	else if (strDeviceModel == "EQ2012")
	{
		WritePrivateProfileString("��ַ��0", "CardType ", "8", pFile);
	}
	else if (strDeviceModel == "EQ2008-M")
	{
		WritePrivateProfileString("��ַ��0", "CardType ", "9", pFile);
	}
	else if (strDeviceModel == "EQ2013")
	{
		WritePrivateProfileString("��ַ��0", "CardType ", "21", pFile);
	}
	else if (strDeviceModel == "EQ2023")
	{
		WritePrivateProfileString("��ַ��0", "CardType ", "22", pFile);
	}
	else if (strDeviceModel == "EQ2033")
	{
		WritePrivateProfileString("��ַ��0", "CardType ", "23", pFile);
	}
	else
	{
		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[EQSendPrgm]--��ʱ��֧�ִ������͵��������ƿ�[%s]", strDeviceModel);
		return FALSE;
	}
	WritePrivateProfileString("��ַ��0", "IpAddress0", strIP0, pFile);
	WritePrivateProfileString("��ַ��0", "IpAddress1", strIP1, pFile);
	WritePrivateProfileString("��ַ��0", "IpAddress2", strIP2, pFile);
	WritePrivateProfileString("��ַ��0", "IpAddress3", strIP3, pFile);
	WritePrivateProfileString("��ַ��0", "ScreemHeight", strHeight, pFile);
	WritePrivateProfileString("��ַ��0", "ScreemWidth", strWidth, pFile);

	CString strFilepath = GetFullPath("EQ2008_Dll_Set.ini");
	strFilepath.Replace("/", "\\");
	User_ReloadIniFile(strFilepath.GetBuffer(0));
	if (!User_OpenScreen(m_iCardNum))
	{
		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[EQSendPrgm]--����ʾ��ʧ��[%s]", strIP);
		return FALSE;
	}
	else
	{
		BOOL b_ret_clear = User_DelAllProgram(m_iCardNum);
		if (!b_ret_clear)
		{
			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[EQSendPrgm]--ɾ����Ŀʧ��[%s]", strIP);
			return FALSE;
		}
		else
		{
			m_iProgramIndex = User_AddProgram(m_iCardNum, FALSE, 60 * 60 * 24);
			if (m_iProgramIndex == -1)
			{
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[EQSendPrgm]--��ӽ�Ŀʧ��[%s]", strIP);
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
				SingleText.FontInfo.iFontSize = atoi(strPrgmFontSize);    //�����С
				SingleText.PartInfo.FrameColor = 0;
				SingleText.FontInfo.strFontName = "";  //��������
				SingleText.FontInfo.iAlignStyle = 0;   //���뷽ʽ 0 �������  1 ������  2 ���Ҷ���
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
						SingleText.MoveSet.iActionType = 1;     //������ʾ
					}
					else if (strPrgmEffect == "2")
					{
						SingleText.MoveSet.iActionType = 3;     //��������
					}
					else if (strPrgmEffect == "3")
					{
						SingleText.MoveSet.iActionType = 7;     //����
					}
					else if (strPrgmEffect == "4")
					{
						SingleText.MoveSet.iActionType = 4;     //����
					}
					else if (strPrgmEffect == "5")
					{
						SingleText.MoveSet.iActionType = 5;     //����
					}
					else
					{
						SingleText.MoveSet.iActionType = 1;     //������ʾ
					}
				}
				else
				{
					SingleText.MoveSet.iActionSpeed = 1;   //�����ٶ�
					SingleText.MoveSet.iFrameTime = (11 - atoi(strPrgmPlaySpeed)) * 20; //�����ٶ�
					if (strPrgmEffect == "1")
					{
						SingleText.MoveSet.iActionType = 1;     //������ʾ
					}
					else if (strPrgmEffect == "2")
					{
						SingleText.MoveSet.iActionType = 20;     //����
					}
					else if (strPrgmEffect == "3")
					{
						SingleText.MoveSet.iActionType = 23;     //����
					}
					else if (strPrgmEffect == "4")
					{
						SingleText.MoveSet.iActionType = 21;     //����
					}
					else if (strPrgmEffect == "5")
					{
						SingleText.MoveSet.iActionType = 22;     //����
					}
					else
					{
						SingleText.MoveSet.iActionType = 1;     //������ʾ
					}
				}
				SingleText.MoveSet.iHoldTime = 10 * (atoi(strPrgmStayTime));    //ͣ��ʱ��
				SingleText.MoveSet.iClearActionType = 0;
				SingleText.MoveSet.iClearSpeed = 4;
				if (-1 == User_AddSingleText(m_iCardNum, &SingleText, m_iProgramIndex))
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[EQSendPrgm]--��ӵ����ı�ʧ��[%s]", strIP);
					return FALSE;
				}
				else
				{
					if (!User_SendToScreen(m_iCardNum))
					{
						LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[EQSendPrgm]--�����ı�ʧ��[%s]", strIP);
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
	start = clock();		//������ʼ��ʱ

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
		strcat(S, "   `A1`H2`C0000FF��ɫ12����ʾ");
		strcat(S, "\n\r");

		// Use 8x16,16x16 fonts
		strcat(S, "`A3`H4`C00FF00��ɫ16����ʾAB");

		// Use 12x24,24x24 fonts
		strcat(S, "`A5`H6`C00FFFF��ɫ24����ʾCD`Y000");

		// Use 16x32,32x32 fonts
		strcat(S, "`M3`A7`H8`C00FFFF����32����ʾEF");

		// ����Ϊ�ı��ļ�
		F = fopen(FileName, "w+t");
		fprintf(F, "%s", S);
		fclose(F);

		// ͨѶ��ʼ��
		bOK = scl2008.SCL_NetInitial(1, "", strIP.GetBuffer(0), 20, 0, atoi(strPort), TRUE);
		if (!bOK)  goto Thread;
		// �����ļ�
		if (bOK)
		{
			// ��ֵķ����ı��ļ�
			scl2008.SCL_GetFileDosDateTime(FileName, &Da, &Ti);
			bOK = scl2008.SCL_SendData(1, 0, strlen(S), (BYTE*)S);
			if (bOK) bOK = scl2008.SCL_SaveFile(1, 2, FileName, strlen(S), Da, Ti);
			if (!bOK) goto Thread;
		}
		// ֪ͨ���������²��Ž�Ŀ
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
				strTips.Format("[DealPublicPrgm]--���п��ƿ���Ŀ�·��ɹ�[%s],��ʱ%f", strIP, endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]-���п��ƿ��·���Ŀ�ɹ�[%s][%s]", strIP, strPrgmID);
			}
			else
			{
				strTips.Format("[DealPublicPrgm]--���п��ƿ���Ŀ�·��ɹ�[%s],��ʱ%f", strIP, endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--���п��ƿ���Ŀ�·��ɹ�,���ͽ�Ŀ�·����ʧ��[%s][%s]", strIP, strPrgmID);
			}
		}
		else {
			strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", strDeviceID, strPublicUser, strPublicTime, strPrgmID);
			BOOL IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
			if (IsSuccess)
			{
				strTips.Format("[DealPublicPrgm]--���п��ƿ���Ŀ�·�ʧ��[%s],��ʱ%f", strIP, endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--���п���Ŀ�·�ʧ��[%s][%s]", strIP, strPrgmID);
			}
			else
			{
				strTips.Format("[DealPublicPrgm]--���п��ƿ���Ŀ�·�ʧ��[%s],��ʱ%f", strIP, endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--���п��·�ʧ��,���ͽ�Ŀ�·����ʧ��[%s][%s]", strIP, strPrgmID);
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
		start = clock();		//������ʼ��ʱ

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
					strTips.Format("[DealPublicPrgm]--������ƿ���Ŀ�·��ɹ�[%s],��ʱ%f", strIP, endtime);
					tips(strTips);
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--����·���Ŀ�ɹ�[%s][%s]", strIP, strPrgmID);
				}
				else
				{
					strTips.Format("[DealPublicPrgm]--������ƿ���Ŀ�·��ɹ�[%s],��ʱ%f", strIP, endtime);
					tips(strTips);
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--�����Ŀ�·��ɹ�,���ͽ�Ŀ�·����ʧ��[%s][%s]", strIP, strPrgmID);
				}
			}
			else
			{
				strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", strDeviceID, strPublicUser, strPublicTime, strPrgmID);
				BOOL IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
				if (IsSuccess)
				{
					strTips.Format("[DealPublicPrgm]--������ƿ���Ŀ�·�ʧ��[%s],��ʱ%f", strIP, endtime);
					tips(strTips);
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--�����Ŀ�·�ʧ��[%s][%s]", strIP, strPrgmID);
				}
				else
				{
					strTips.Format("[DealPublicPrgm]--������ƿ���Ŀ�·�ʧ��[%s],��ʱ%f", strIP, endtime);
					tips(strTips);
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--����·�ʧ��,���ͽ�Ŀ�·����ʧ��[%s][%s]", strIP, strPrgmID);
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
		//���豸
		CString strBody = "";
		BOOL IsSuccess = FALSE;
		CString strTips = "";
		BOOL bRet = vsa.LED_VSAOpenDevice();
		if (bRet)
		{
			strBody = "";
			strBody.Format("\"itemtype\":\"3\",\"status\":\"1\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", strDeviceID, strPublicUser, strPublicTime, strPrgmID);
			IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
			strTips.Format("[DealPublicPrgm]---��չ��A�����豸ʧ��[%s");
			tips(strTips);
			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--��չ��A����Ŀ�·�ʧ��[%s][%s]", strIP, strPrgmID);
		}
		else
		{
			clock_t start, end;
			start = clock();		//������ʼ��ʱ
			vsa.LED_VSASendPrgm(atoi(strWidth), atoi(strHeight), strPrgmContent, atoi(strPrgmEffect), atoi(strPrgmPlaySpeed), 0, strIP);
			end = clock();
			double endtime = (double)(end - start) / CLOCKS_PER_SEC;

			pool_UploadStauts->enqueue([=]() {
				CString strTips = "";
				CString strBody = "";
				BOOL IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
				if (IsSuccess)
				{
					strTips.Format("[DealPublicPrgm]--��չ��A����Ŀ�·��ɹ�[%s],��ʱ%f", strIP, endtime);
					tips(strTips);
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--��չ��A���·���Ŀ�ɹ�[%s][%s]", strIP, strPrgmID);
				}
				else
				{
					strTips.Format("[DealPublicPrgm]--��չ�ؿ�A����Ŀ�·��ɹ�[%s],��ʱ%f", strIP, endtime);
					tips(strTips);
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]---��չ��A���·���Ŀ�ɹ�,���ͽ�Ŀ�·����ʧ��[%s][%s]", strIP, strPrgmID);
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
		start = clock();		//������ʼ��ʱ

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
				strTips.Format("[DealPublicPrgm]--��չ��D����Ŀ�·�ʧ��[%s],��ʱ%f", strIP, endtime);
				tips(strTips);
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--��չ��D����Ŀ�·�ʧ��[%s][%s]", strIP, strPrgmID);
			}
			else
			{
				strBody = "";
				strBody.Format("\"itemtype\":\"3\",\"status\":\"0\",\"mmpdeviceid\":\"%s\",\"releaseuser\":\"%s\",\"releasetime\":\"%s\",\"itemId\":\"%s\"", strDeviceID, strPublicUser, strPublicTime, strPrgmID);
				IsSuccess = m_toolTrade.UpLoadProGrameStatus(strHttpAddr, strBody);
				if (IsSuccess)
				{
					strTips.Format("[DealPublicPrgm]--��չ��D����Ŀ�·��ɹ�[%s],��ʱ%f", strIP, endtime);
					tips(strTips);
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[DealPublicPrgm]--��չ��D���·���Ŀ�ɹ�[%s][%s]", strIP, strPrgmID);
				}
			}
		});
		return TRUE;
}
