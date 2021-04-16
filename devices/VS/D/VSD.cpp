#include "stdafx.h"
#include "VSD.h"
#include "winsock.h"
#include <windows.h>

_LED_Startup LED_Startup;
_LED_Cleanup LED_Cleanup;

_LED_Report_CreateServer LED_Report_CreateServer;
_LED_Report_RemoveServer LED_Report_RemoveServer;
_LED_Report_RemoveAllServer LED_Report_RemoveAllServer;

_LED_Report_GetOnlineList LED_Report_GetOnlineList;
_LED_Report_GetOnlineItemName LED_Report_GetOnlineItemName;
_LED_Report_GetOnlineItemHost LED_Report_GetOnlineItemHost;
_LED_Report_GetOnlineItemPort LED_Report_GetOnlineItemPort;
_LED_Report_GetOnlineItemAddr LED_Report_GetOnlineItemAddr;
_LED_UDP_SenderParam LED_UDP_SenderParam;
_LED_COM_SenderParam LED_COM_SenderParam;
_LED_UDP_SenderParam_ByReportName LED_UDP_SenderParam_ByReportName;
_LED_Preview LED_Preview;
_LED_ResetDisplay LED_ResetDisplay;
_LED_ResetDisplay2 LED_ResetDisplay2;
_LED_AdjustTime LED_AdjustTime;
_LED_AdjustTime2 LED_AdjustTime2;
_LED_AdjustTimeEx LED_AdjustTimeEx;
_LED_AdjustTimeEx2 LED_AdjustTimeEx2;
_LED_SetCurChapter LED_SetCurChapter;
_LED_SetCurChapter2 LED_SetCurChapter2;
_LED_GetCurChapter LED_GetCurChapter;
_LED_GetCurChapter2 LED_GetCurChapter2;
_LED_SetPower LED_SetPower;
_LED_SetPower2 LED_SetPower2;
_LED_ComTransfer LED_ComTransfer;
_LED_ComTransfer2 LED_ComTransfer2;
_LED_GetPower LED_GetPower;
_LED_GetPower2 LED_GetPower2;
_LED_SetBright LED_SetBright;
_LED_SetBright2 LED_SetBright2;
_LED_GetBright LED_GetBright;
_LED_GetBright2 LED_GetBright2;
_LED_SetPowerSchedule LED_SetPowerSchedule;
_LED_SetPowerSchedule2 LED_SetPowerSchedule2;
_LED_GetPowerSchedule LED_GetPowerSchedule;
_LED_GetPowerSchedule2 LED_GetPowerSchedule2;
_LED_SetBrightSchedule LED_SetBrightSchedule;
_LED_SetBrightSchedule2 LED_SetBrightSchedule2;
_LED_GetBrightSchedule LED_GetBrightSchedule;
_LED_GetBrightSchedule2 LED_GetBrightSchedule2;
_LED_SendToScreen LED_SendToScreen;
_LED_SendToScreen2 LED_SendToScreen2;
_LED_Cache_GetBoardParam LED_Cache_GetBoardParam;
_LED_Cache_GetBoardParam2 LED_Cache_GetBoardParam2;
_LED_Cache_GetBoardParam_SaveToFile LED_Cache_GetBoardParam_SaveToFile;
_LED_Cache_GetBoardParam_IP LED_Cache_GetBoardParam_IP;
_LED_Cache_GetBoardParam_Mac LED_Cache_GetBoardParam_Mac;
_LED_Cache_GetBoardParam_Addr LED_Cache_GetBoardParam_Addr;
_LED_Cache_GetBoardParam_Width LED_Cache_GetBoardParam_Width;
_LED_Cache_GetBoardParam_Height LED_Cache_GetBoardParam_Height;
_LED_Cache_GetBoardParam_Brightness LED_Cache_GetBoardParam_Brightness;
_LED_Cache_SetBoardParam_LoadFromFile LED_Cache_SetBoardParam_LoadFromFile;
_LED_Cache_SetBoardParam_IP LED_Cache_SetBoardParam_IP;
_LED_Cache_SetBoardParam_Mac LED_Cache_SetBoardParam_Mac;
_LED_Cache_SetBoardParam_Addr LED_Cache_SetBoardParam_Addr;
_LED_Cache_SetBoardParam_Width LED_Cache_SetBoardParam_Width;
_LED_Cache_SetBoardParam_Height LED_Cache_SetBoardParam_Height;
_LED_Cache_SetBoardParam_Brightness LED_Cache_SetBoardParam_Brightness;
_LED_Cache_SetBoardParam LED_Cache_SetBoardParam;
_LED_Cache_SetBoardParam2 LED_Cache_SetBoardParam2;
_LED_GetNotifyParam LED_GetNotifyParam;
_MakeFromVsqFile MakeFromVsqFile;
_MakeRoot MakeRoot;
_MakeChapter MakeChapter;
_MakeRegion MakeRegion;
_MakeLeaf MakeLeaf;
_MakeObject MakeObject;
_AddChapter AddChapter;
_AddChapterEx2 AddChapterEx2;
_AddRegion AddRegion;
_AddLeaf AddLeaf;
_AddDateTime AddDateTime;
_AddCampaignEx AddCampaignEx;
_AddClock AddClock;
_AddMovie AddMovie;
_AddWindows AddWindows;
_AddChildWindow AddChildWindow;
_AddChildPicture AddChildPicture;
_AddChildText AddChildText;
_AddStrings AddStrings;
_AddChildString AddChildString;
_AddWindow AddWindow;
_AddPicture AddPicture;
_AddText AddText;
_AddTextEx2 AddTextEx2;
_AddString AddString;
_AddTable AddTable;
_SZRC_MakeTextObject SZRC_MakeTextObject;

VSD::VSD(void)
{
}

VSD::~VSD(void)
{
}

BOOL VSD::LED_VSDInitialize()
{
	if ((hInstance=LoadLibrary("LEDSender2010.dll"))!=NULL)
	{
		LED_Startup=(_LED_Startup)GetProcAddress(hInstance,"LED_Startup");
		LED_Cleanup=(_LED_Cleanup)GetProcAddress(hInstance,"LED_Cleanup");
		LED_Preview=(_LED_Preview)GetProcAddress(hInstance,"LED_Preview");

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//在线控制卡列表相关接口函数
		LED_Report_CreateServer=(_LED_Report_CreateServer)GetProcAddress(hInstance,"LED_Report_CreateServer");
		LED_Report_RemoveServer=(_LED_Report_RemoveServer)GetProcAddress(hInstance,"LED_Report_RemoveServer");
		LED_Report_RemoveAllServer=(_LED_Report_RemoveAllServer)GetProcAddress(hInstance,"LED_Report_RemoveAllServer");
		LED_Report_GetOnlineList=(_LED_Report_GetOnlineList)GetProcAddress(hInstance,"LED_Report_GetOnlineList");
		LED_Report_GetOnlineItemName=(_LED_Report_GetOnlineItemName)GetProcAddress(hInstance,"LED_Report_GetOnlineItemName");
		LED_Report_GetOnlineItemHost=(_LED_Report_GetOnlineItemHost)GetProcAddress(hInstance,"LED_Report_GetOnlineItemHost");
		LED_Report_GetOnlineItemPort=(_LED_Report_GetOnlineItemPort)GetProcAddress(hInstance,"LED_Report_GetOnlineItemPort");
		LED_Report_GetOnlineItemAddr=(_LED_Report_GetOnlineItemAddr)GetProcAddress(hInstance,"LED_Report_GetOnlineItemAddr");
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		LED_ResetDisplay=(_LED_ResetDisplay)GetProcAddress(hInstance,"LED_ResetDisplay");
		LED_AdjustTime=(_LED_AdjustTime)GetProcAddress(hInstance,"LED_AdjustTime");
		LED_AdjustTimeEx=(_LED_AdjustTimeEx)GetProcAddress(hInstance,"LED_AdjustTimeEx");
		LED_SetCurChapter=(_LED_SetCurChapter)GetProcAddress(hInstance,"LED_SetCurChapter");
		LED_GetCurChapter=(_LED_GetCurChapter)GetProcAddress(hInstance,"LED_GetCurChapter");
		LED_SetPower=(_LED_SetPower)GetProcAddress(hInstance,"LED_SetPower");
		LED_GetPower=(_LED_GetPower)GetProcAddress(hInstance,"LED_GetPower");
		LED_SetBright=(_LED_SetBright)GetProcAddress(hInstance,"LED_SetBright");
		LED_GetBright=(_LED_GetBright)GetProcAddress(hInstance,"LED_GetBright");
		LED_SetPowerSchedule=(_LED_SetPowerSchedule)GetProcAddress(hInstance,"LED_SetPowerSchedule");
		LED_GetPowerSchedule=(_LED_GetPowerSchedule)GetProcAddress(hInstance,"LED_GetPowerSchedule");
		LED_SetBrightSchedule=(_LED_SetBrightSchedule)GetProcAddress(hInstance,"LED_SetBrightSchedule");
		LED_GetBrightSchedule=(_LED_GetBrightSchedule)GetProcAddress(hInstance,"LED_GetBrightSchedule");
		LED_SendToScreen=(_LED_SendToScreen)GetProcAddress(hInstance,"LED_SendToScreen");
		LED_ComTransfer=(_LED_ComTransfer)GetProcAddress(hInstance,"LED_ComTransfer");

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//此处与之前同名函数功能相同，只是将结构体指针参数拆分成多个变量参数，方便PB、java等开发语言调用
		LED_UDP_SenderParam=(_LED_UDP_SenderParam)GetProcAddress(hInstance,"LED_UDP_SenderParam");
		LED_COM_SenderParam=(_LED_COM_SenderParam)GetProcAddress(hInstance,"LED_COM_SenderParam");
		LED_UDP_SenderParam_ByReportName=(_LED_UDP_SenderParam_ByReportName)GetProcAddress(hInstance,"LED_UDP_SenderParam_ByReportName");
		LED_ResetDisplay2=(_LED_ResetDisplay2)GetProcAddress(hInstance,"LED_ResetDisplay2");
		LED_AdjustTime2=(_LED_AdjustTime2)GetProcAddress(hInstance,"LED_AdjustTime2");
		LED_AdjustTimeEx2=(_LED_AdjustTimeEx2)GetProcAddress(hInstance,"LED_AdjustTimeEx2");
		LED_SetCurChapter2=(_LED_SetCurChapter2)GetProcAddress(hInstance,"LED_SetCurChapter2");
		LED_SetPower2=(_LED_SetPower2)GetProcAddress(hInstance,"LED_SetPower2");
		LED_GetPower2=(_LED_GetPower2)GetProcAddress(hInstance,"LED_GetPower2");
		LED_SetBright2=(_LED_SetBright2)GetProcAddress(hInstance,"LED_SetBright2");
		LED_GetBright2=(_LED_GetBright2)GetProcAddress(hInstance,"LED_GetBright2");
		LED_SetPowerSchedule2=(_LED_SetPowerSchedule2)GetProcAddress(hInstance,"LED_SetPowerSchedule2");
		LED_GetPowerSchedule2=(_LED_GetPowerSchedule2)GetProcAddress(hInstance,"LED_GetPowerSchedule2");
		LED_SetBrightSchedule2=(_LED_SetBrightSchedule2)GetProcAddress(hInstance,"LED_SetBrightSchedule2");
		LED_GetBrightSchedule2=(_LED_GetBrightSchedule2)GetProcAddress(hInstance,"LED_GetBrightSchedule2");
		LED_SendToScreen2=(_LED_SendToScreen2)GetProcAddress(hInstance,"LED_SendToScreen2");
		LED_ComTransfer2=(_LED_ComTransfer2)GetProcAddress(hInstance,"LED_ComTransfer2");

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//读取控制卡参数
		LED_Cache_GetBoardParam=(_LED_Cache_GetBoardParam)GetProcAddress(hInstance,"LED_Cache_GetBoardParam");
		LED_Cache_GetBoardParam2=(_LED_Cache_GetBoardParam2)GetProcAddress(hInstance,"LED_Cache_GetBoardParam2");
		//提取各个参数
		LED_Cache_GetBoardParam_SaveToFile=(_LED_Cache_GetBoardParam_SaveToFile)GetProcAddress(hInstance,"LED_Cache_GetBoardParam_SaveToFile");
		LED_Cache_GetBoardParam_IP=(_LED_Cache_GetBoardParam_IP)GetProcAddress(hInstance,"LED_Cache_GetBoardParam_IP");
		LED_Cache_GetBoardParam_Mac=(_LED_Cache_GetBoardParam_Mac)GetProcAddress(hInstance,"LED_Cache_GetBoardParam_Mac");
		LED_Cache_GetBoardParam_Addr=(_LED_Cache_GetBoardParam_Addr)GetProcAddress(hInstance,"LED_Cache_GetBoardParam_Addr");
		LED_Cache_GetBoardParam_Width=(_LED_Cache_GetBoardParam_Width)GetProcAddress(hInstance,"LED_Cache_GetBoardParam_Width");
		LED_Cache_GetBoardParam_Height=(_LED_Cache_GetBoardParam_Height)GetProcAddress(hInstance,"LED_Cache_GetBoardParam_Height");
		LED_Cache_GetBoardParam_Brightness=(_LED_Cache_GetBoardParam_Brightness)GetProcAddress(hInstance,"LED_Cache_GetBoardParam_Brightness");
		//修改各个参数
		LED_Cache_SetBoardParam_LoadFromFile=(_LED_Cache_SetBoardParam_LoadFromFile)GetProcAddress(hInstance,"LED_Cache_SetBoardParam_LoadFromFile");
		LED_Cache_SetBoardParam_IP=(_LED_Cache_SetBoardParam_IP)GetProcAddress(hInstance,"LED_Cache_SetBoardParam_IP");
		LED_Cache_SetBoardParam_Mac=(_LED_Cache_SetBoardParam_Mac)GetProcAddress(hInstance,"LED_Cache_SetBoardParam_Mac");
		LED_Cache_SetBoardParam_Addr=(_LED_Cache_SetBoardParam_Addr)GetProcAddress(hInstance,"LED_Cache_SetBoardParam_Addr");
		LED_Cache_SetBoardParam_Width=(_LED_Cache_SetBoardParam_Width)GetProcAddress(hInstance,"LED_Cache_SetBoardParam_Width");
		LED_Cache_SetBoardParam_Height=(_LED_Cache_SetBoardParam_Height)GetProcAddress(hInstance,"LED_Cache_SetBoardParam_Height");
		LED_Cache_SetBoardParam_Brightness=(_LED_Cache_SetBoardParam_Brightness)GetProcAddress(hInstance,"LED_Cache_SetBoardParam_Brightness");
		//将修改后的参数接入控制卡
		LED_Cache_SetBoardParam=(_LED_Cache_SetBoardParam)GetProcAddress(hInstance,"LED_Cache_SetBoardParam");
		LED_Cache_SetBoardParam2=(_LED_Cache_SetBoardParam2)GetProcAddress(hInstance,"LED_Cache_SetBoardParam2");

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		LED_GetNotifyParam=(_LED_GetNotifyParam)GetProcAddress(hInstance,"LED_GetNotifyParam");

		MakeFromVsqFile=(_MakeFromVsqFile)GetProcAddress(hInstance,"MakeFromVsqFile");
		MakeRoot=(_MakeRoot)GetProcAddress(hInstance,"MakeRoot");
		MakeChapter=(_MakeChapter)GetProcAddress(hInstance,"MakeChapter");
		MakeRegion=(_MakeRegion)GetProcAddress(hInstance,"MakeRegion");
		MakeLeaf=(_MakeLeaf)GetProcAddress(hInstance,"MakeLeaf");
		MakeObject=(_MakeObject)GetProcAddress(hInstance,"MakeObject");

		AddChapter=(_AddChapter)GetProcAddress(hInstance,"AddChapter");
		AddChapterEx2=(_AddChapterEx2)GetProcAddress(hInstance,"AddChapterEx2");
		AddRegion=(_AddRegion)GetProcAddress(hInstance,"AddRegion");
		AddLeaf=(_AddLeaf)GetProcAddress(hInstance,"AddLeaf");

		AddDateTime=(_AddDateTime)GetProcAddress(hInstance,"AddDateTime");
		AddCampaignEx=(_AddCampaignEx)GetProcAddress(hInstance,"AddCampaignEx");
		AddClock=(_AddClock)GetProcAddress(hInstance,"AddClock");
		AddMovie=(_AddMovie)GetProcAddress(hInstance,"AddMovie");

		AddWindows=(_AddWindows)GetProcAddress(hInstance,"AddWindows");
		AddChildWindow=(_AddChildWindow)GetProcAddress(hInstance,"AddChildWindow");
		AddChildPicture=(_AddChildPicture)GetProcAddress(hInstance,"AddChildPicture");
		AddChildText=(_AddChildText)GetProcAddress(hInstance,"AddChildText");
		AddStrings=(_AddStrings)GetProcAddress(hInstance,"AddStrings");
		AddChildString=(_AddChildString)GetProcAddress(hInstance,"AddChildString");

		AddWindow=(_AddWindow)GetProcAddress(hInstance,"AddWindow");
		AddPicture=(_AddPicture)GetProcAddress(hInstance,"AddPicture");
		AddText=(_AddText)GetProcAddress(hInstance,"AddText");
		AddTextEx2=(_AddTextEx2)GetProcAddress(hInstance,"AddTextEx2");
		AddString=(_AddString)GetProcAddress(hInstance,"AddString");
		AddTable=(_AddTable)GetProcAddress(hInstance,"AddTable");

		if (LED_Startup) LED_Startup();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int VSD::LED_VSDSendPrgm(CString strIP,CString strPort, CString strLedType,long nWidth,long nHeight,CString strPrgm,CString strPrgmFontSize,long Effect,long nPlaySpeed)
{

	nPlaySpeed = nPlaySpeed - 1;
	int nRet = 0;
	VSD_TSenderParam param;
	int K, R;
	VSD_TNotifyParam notifyparam;

	memset(&param, 0, sizeof(VSD_TSenderParam));
	param.devParam.devType=VSD_DEVICE_TYPE_UDP;
	param.devParam.locPort=atoi(strPort);
	memcpy(param.devParam.rmtHost, LPCTSTR(strIP), strIP.GetLength()*sizeof(TCHAR));
	param.devParam.rmtPort= 6666;

	param.notifyMode = VSD_NOTIFY_BLOCK;
	//param.wmHandle = (long)hWnd;
	//param.wmMessage = WM_LED_NOTIFY;
	
	if (strLedType == "1")
	{
		K = MakeRoot(VSD_ROOT_DOWNLOAD, VSD_COLOR_MODE_MONO, VSD_ROOT_SURVIVE_ALWAYS);
	}
	else
	{
		K = MakeRoot(VSD_ROOT_DOWNLOAD, VSD_COLOR_MODE_DOUBLE, VSD_ROOT_SURVIVE_ALWAYS);
	}
	AddChapter(K, 24*60*60*1000, WAIT_CHILD);
	AddRegion(K, 0, 0, nWidth, nHeight, 0);

	//第1页面
	AddLeaf(K, 24*60*60*1000, WAIT_CHILD);
	//非自动换行的文字
	AddText(K,0,0,nWidth,nHeight,VSD_V_TRUE,0,(char*)strPrgm.GetBuffer(0),"宋体",atoi(strPrgmFontSize),RGB(255,0,0),VSD_WFS_NONE,VSD_V_FALSE,0,Effect,nPlaySpeed,1, nPlaySpeed,0, nPlaySpeed,0);
	R=LED_SendToScreen(&param, K);
	if (R>=0)
	{
		LED_GetNotifyParam(&notifyparam, R);
		switch(notifyparam.Notify){
		case VSD_LM_TIMEOUT:
			nRet = 4;
			//发送超时
			break;
		case VSD_LM_TX_COMPLETE:
			if (notifyparam.Result==VSD_RESULT_FLASH)
			{
				nRet = 0;
				//数据传送完成，正在写入Flash
			}
			else
			{
				nRet = 0;
				//数据传送完成
			}
			break;
		case VSD_LM_NOTIFY:
			break;
		}
	}
	else
	{
		switch(R){ 
		case VSD_R_DEVICE_INVALID:
			nRet = -1;
			//打开通讯设备失败(串口不存在、或者串口已被占用、或者网络端口被占用)
			break;
		case VSD_R_DEVICE_BUSY:
			nRet = -2;
			//设备忙，正在通讯中...
			break;
		}
	}

	return nRet;
}

void VSD::LED_VSDDestroy()
{
	if (hInstance!=NULL) 
	{
		LED_Cleanup();
		FreeLibrary(hInstance);
	}
}