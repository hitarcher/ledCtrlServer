#include "stdafx.h"
#include "VSA.h"

_VSALED_SetDebugMode LED_SetDebugMode;
_VSALED_Open LED_Open;
_VSALED_Open2 LED_Open2;
_VSALED_Close LED_Close;
_VSALED_CloseAll LED_CloseAll;
_VSALED_Query LED_Query;
_VSALED_Reset LED_Reset;
_VSALED_AdjustTime LED_AdjustTime;
_VSALED_AdjustTimeEx LED_AdjustTimeEx;
_VSALED_AdjustTimeEx2 LED_AdjustTimeEx2;
_VSALED_SendToScreen LED_SendToScreen;
_VSALED_SendToScreenByName LED_SendToScreenByName;
_VSALED_GetPower LED_GetPower;
_VSALED_SetPower LED_SetPower;
_VSALED_GetLeaf LED_GetLeaf;
_VSALED_SetLeaf LED_SetLeaf;
_VSALED_SetSwitch LED_SetSwitch;
_VSALED_GetImport LED_GetImport;
_VSALED_GetBrightness LED_GetBrightness;
_VSALED_SetBrightness LED_SetBrightness;
_VSALED_GetAutoPowerList LED_GetAutoPowerList;
_VSALED_SetAutoPowerList LED_SetAutoPowerList;
_VSALED_GetAutoBrightTable LED_GetAutoBrightTable;
_VSALED_SetAutoBrightTable LED_SetAutoBrightTable;
_VSALED_GetDisplayBuffer LED_GetDisplayBuffer;
_VSALED_SetIP LED_SetIP;
_VSALED_SetOption LED_SetOption;
_VSALED_GetLEDParam LED_GetLEDParam;
_VSALED_SetLEDParam LED_SetLEDParam;
_VSALED_GetNotifyMessage LED_GetNotifyMessage;
_VSALED_GetNotifyMessageIdent LED_GetNotifyMessageIdent;
_VSALED_GetNotifyMessageCommand LED_GetNotifyMessageCommand;
_VSALED_GetDeviceStatus LED_GetDeviceStatus;
_VSALED_GetDeviceNotifyMessage LED_GetDeviceNotifyMessage;
_VSARtfToBitmap RtfToBitmap;
_VSAMakeRoot MakeRoot;
_VSAMakeRootEx MakeRootEx;
_VSAMakeRootEx_4Byte MakeRootEx_4Byte;
_VSAAddLeaf  AddLeaf;//DisplayTime单位为毫秒
_VSAAddWindow AddWindow;
_VSAAddWindow2 AddWindow2;
_VSAAddPicture AddPicture;
_VSAAddPicture2 AddPicture2;
_VSAAddRtf AddRtf;
_VSAAddRtf2 AddRtf2;
_VSAAddDateTime AddDateTime;
_VSAAddDateTime2 AddDateTime2;
_VSAAddString AddString;
_VSAAddString2 AddString2;
_VSAAddText AddText;
_VSAAddText2 AddText2;
_VSAAddTextEx AddTextEx;
_VSAAddTextEx2 AddTextEx2;
_VSAAddTextVSplit AddTextVSplit;
_VSAAddTextVSplit2 AddTextVSplit2;
_VSAAddMovie AddMovie;
_VSAAddMovie2 AddMovie2;
_VSAAddCountUp AddCountUp;
_VSAAddCountDown AddCountDown;
_VSAAddCampaignTime AddCampaignTime;
//发送多行文本，可以自动换行，当文字超出显示范围，按照指定动作方式动作，否则静态显示
//  RangeMode为超出范围方式
//      =0表示始终使用指定动作方式
//      =1表示长度超出显示范围时，使用指定动作方式，否则按照HAlign指定的对齐方式显示
//      =2表示高度超出显示范围时，使用指定动作方式，否则按照VAlign指定的对齐方式显示
_VSAAddTextRange AddTextRange;

/*{
('DotM|整点半径'); ('DotH|3,6,9点半径');
('ColorH|小时指针颜色'); ('ColorM|分钟指针颜色'); ('ColorS|秒指针颜色');
('ColorD|3,6,9点颜色'); ('ColorN|整点颜色');
('WidthH|小时指针宽度'); ('WidthM|分钟指针宽度');
}*/
_VSAAddClock AddClock;
_VSAAddClock2 AddClock2;
_VSAConstructerOpen ConstructerOpen;
_VSAConstructerClose ConstructerClose;
_VSAConstructerMakeRoot ConstructerMakeRoot;
_VSALED_CreateReportServer LED_CreateReportServer;
_VSALED_ReleaseReportServer LED_ReleaseReportServer;
_VSALED_GetOnlineCount LED_GetOnlineCount;
_VSALED_GetOnlineList LED_GetOnlineList; 
_VSALED_CreateReportServerEx LED_CreateReportServerEx;
_VSALED_ReleaseReportServerEx LED_ReleaseReportServerEx;
_VSALED_GetOnlineCountEx LED_GetOnlineCountEx;
_VSALED_GetOnlineListEx LED_GetOnlineListEx;

////////////////////////////////////////////////////////
_VSALED_GetOnlineList_Java LED_GetOnlineList_Java;
_VSALED_GetOnlineItemIP_Java LED_GetOnlineItemIP_Java;
_VSALED_GetOnlineItemPort_Java LED_GetOnlineItemPort_Java;
_VSALED_GetOnlineItemAddr_Java LED_GetOnlineItemAddr_Java;
_VSALED_GetOnlineItemName_Java LED_GetOnlineItemName_Java;
////////////////////////////////////////////////////////
_VSAPreview_Create Preview_Create;
_VSAPreview_Step Preview_Step;
_VSAPreview_Destroy Preview_Destroy;

VSA::VSA(void)
{
	m_Dev = 0;
}

VSA::~VSA(void)
{
}

void VSA::Preview_VSAInitialize()
{
	disp_buffer=NULL;
	if ((preview_hInstance=LoadLibrary("Interface.dll"))!=NULL)
	{
		Preview_Create=(_VSAPreview_Create)GetProcAddress(preview_hInstance, "Display_Create");
		Preview_Step=(_VSAPreview_Step)GetProcAddress(preview_hInstance, "Display_Step");
		Preview_Destroy=(_VSAPreview_Destroy)GetProcAddress(preview_hInstance, "Display_Destroy");
	}
}

void VSA::Preview_VSAFinalize()
{
	//Preview_Destroy();
	if (disp_buffer!=NULL) free(disp_buffer);
	if (preview_hInstance!=NULL) FreeLibrary(preview_hInstance);
}

BOOL VSA::LED_VSAInitialize()
{
	if ((hDllInstance=LoadLibrary("VSA\\LEDSender.Dll"))!=NULL)
	{
		LED_SetDebugMode=(_VSALED_SetDebugMode)GetProcAddress(hDllInstance,"LED_SetDebugMode");
		LED_Open=(_VSALED_Open)GetProcAddress(hDllInstance,"LED_Open");
		LED_Open2=(_VSALED_Open2)GetProcAddress(hDllInstance,"LED_Open2");
		LED_Close=(_VSALED_Close)GetProcAddress(hDllInstance,"LED_Close");
		LED_CloseAll=(_VSALED_CloseAll)GetProcAddress(hDllInstance,"LED_CloseAll");
		LED_Query=(_VSALED_Query)GetProcAddress(hDllInstance,"LED_Query");
		LED_Reset=(_VSALED_Reset)GetProcAddress(hDllInstance,"LED_Reset");
		LED_AdjustTime=(_VSALED_AdjustTime)GetProcAddress(hDllInstance,"LED_AdjustTime");
		LED_AdjustTimeEx=(_VSALED_AdjustTimeEx)GetProcAddress(hDllInstance,"LED_AdjustTimeEx");
		LED_AdjustTimeEx2=(_VSALED_AdjustTimeEx2)GetProcAddress(hDllInstance,"LED_AdjustTimeEx2");
		LED_SendToScreen=(_VSALED_SendToScreen)GetProcAddress(hDllInstance,"LED_SendToScreen");
		LED_SendToScreenByName=(_VSALED_SendToScreenByName)GetProcAddress(hDllInstance,"LED_SendToScreenByName");
		LED_GetPower=(_VSALED_GetPower)GetProcAddress(hDllInstance,"LED_GetPower");
		LED_SetPower=(_VSALED_SetPower)GetProcAddress(hDllInstance,"LED_SetPower");
		LED_GetLeaf=(_VSALED_GetLeaf)GetProcAddress(hDllInstance,"LED_GetLeaf");
		LED_SetLeaf=(_VSALED_SetLeaf)GetProcAddress(hDllInstance,"LED_SetLeaf");
		LED_SetSwitch=(_VSALED_SetSwitch)GetProcAddress(hDllInstance,"LED_SetSwitch");
		LED_GetImport=(_VSALED_GetImport)GetProcAddress(hDllInstance,"LED_GetImport");
		LED_GetBrightness=(_VSALED_GetBrightness)GetProcAddress(hDllInstance,"LED_GetBrightness");
		LED_SetBrightness=(_VSALED_SetBrightness)GetProcAddress(hDllInstance,"LED_SetBrightness");
		LED_GetAutoPowerList=(_VSALED_GetAutoPowerList)GetProcAddress(hDllInstance,"LED_GetAutoPowerList");
		LED_SetAutoPowerList=(_VSALED_SetAutoPowerList)GetProcAddress(hDllInstance,"LED_SetAutoPowerList");
		LED_GetAutoBrightTable=(_VSALED_GetAutoBrightTable)GetProcAddress(hDllInstance,"LED_GetAutoBrightTable");
		LED_SetAutoBrightTable=(_VSALED_SetAutoBrightTable)GetProcAddress(hDllInstance,"LED_SetAutoBrightTable");
		LED_GetDisplayBuffer=(_VSALED_GetDisplayBuffer)GetProcAddress(hDllInstance,"LED_GetDisplayBuffer");
		LED_SetIP=(_VSALED_SetIP)GetProcAddress(hDllInstance,"LED_SetIP");
		LED_GetLEDParam=(_VSALED_GetLEDParam)GetProcAddress(hDllInstance,"LED_GetLEDParam");
		LED_SetLEDParam=(_VSALED_SetLEDParam)GetProcAddress(hDllInstance,"LED_SetLEDParam");
		LED_SetOption=(_VSALED_SetOption)GetProcAddress(hDllInstance,"LED_SetOption");

		LED_GetNotifyMessage=(_VSALED_GetNotifyMessage)GetProcAddress(hDllInstance,"LED_GetNotifyMessage");
		LED_GetNotifyMessageIdent=(_VSALED_GetNotifyMessageIdent)GetProcAddress(hDllInstance,"LED_GetNotifyMessageIdent");
		LED_GetNotifyMessageCommand=(_VSALED_GetNotifyMessageCommand)GetProcAddress(hDllInstance,"LED_GetNotifyMessageCommand");
		LED_GetDeviceStatus=(_VSALED_GetDeviceStatus)GetProcAddress(hDllInstance,"LED_GetDeviceStatus");
		LED_GetDeviceNotifyMessage=(_VSALED_GetDeviceNotifyMessage)GetProcAddress(hDllInstance,"LED_GetDeviceNotifyMessage");

		RtfToBitmap=(_VSARtfToBitmap)GetProcAddress(hDllInstance,"RtfToBitmap");

		MakeRoot=(_VSAMakeRoot)GetProcAddress(hDllInstance,"MakeRoot");
		MakeRootEx=(_VSAMakeRootEx)GetProcAddress(hDllInstance,"MakeRootEx");
		MakeRootEx_4Byte=(_VSAMakeRootEx_4Byte)GetProcAddress(hDllInstance,"MakeRootEx_4Byte");
		AddLeaf=(_VSAAddLeaf)GetProcAddress(hDllInstance,"AddLeaf");
		AddWindow=(_VSAAddWindow)GetProcAddress(hDllInstance,"AddWindow");
		AddWindow2=(_VSAAddWindow2)GetProcAddress(hDllInstance,"AddWindow2");
		AddPicture=(_VSAAddPicture)GetProcAddress(hDllInstance,"AddPicture");
		AddPicture2=(_VSAAddPicture2)GetProcAddress(hDllInstance,"AddPicture2");
		AddRtf=(_VSAAddRtf)GetProcAddress(hDllInstance,"AddRtf");
		AddRtf2=(_VSAAddRtf2)GetProcAddress(hDllInstance,"AddRtf2");
		AddDateTime=(_VSAAddDateTime)GetProcAddress(hDllInstance,"AddDateTime");
		AddDateTime2=(_VSAAddDateTime2)GetProcAddress(hDllInstance,"AddDateTime2");
		AddString=(_VSAAddString)GetProcAddress(hDllInstance,"AddString");
		AddString2=(_VSAAddString2)GetProcAddress(hDllInstance,"AddString2");
		AddText=(_VSAAddText)GetProcAddress(hDllInstance,"AddText");
		AddText2=(_VSAAddText2)GetProcAddress(hDllInstance,"AddText2");
		AddTextEx=(_VSAAddTextEx)GetProcAddress(hDllInstance,"AddTextEx");
		AddTextEx2=(_VSAAddTextEx2)GetProcAddress(hDllInstance,"AddTextEx2");
		AddTextRange=(_VSAAddTextRange)GetProcAddress(hDllInstance,"AddTextRange");
		AddTextVSplit=(_VSAAddTextVSplit)GetProcAddress(hDllInstance,"AddTextVSplit");
		AddTextVSplit2=(_VSAAddTextVSplit2)GetProcAddress(hDllInstance,"AddTextVSplit2");
		AddMovie=(_VSAAddMovie)GetProcAddress(hDllInstance,"AddMovie");
		AddMovie2=(_VSAAddMovie2)GetProcAddress(hDllInstance,"AddMovie2");
		AddCountUp=(_VSAAddCountUp)GetProcAddress(hDllInstance,"AddCountUp");
		AddCountDown=(_VSAAddCountDown)GetProcAddress(hDllInstance,"AddCountDown");
		AddCampaignTime=(_VSAAddCampaignTime)GetProcAddress(hDllInstance,"AddCampaignTime");
		AddClock=(_VSAAddClock)GetProcAddress(hDllInstance,"AddClock");
		AddClock2=(_VSAAddClock2)GetProcAddress(hDllInstance,"AddClock2");

		ConstructerOpen=(_VSAConstructerOpen)GetProcAddress(hDllInstance,"ConstructerOpen");
		ConstructerClose=(_VSAConstructerClose)GetProcAddress(hDllInstance,"ConstructerClose");
		ConstructerMakeRoot=(_VSAConstructerMakeRoot)GetProcAddress(hDllInstance,"ConstructerMakeRoot");

		LED_CreateReportServer=(_VSALED_CreateReportServer)GetProcAddress(hDllInstance,"LED_CreateReportServer");
		LED_ReleaseReportServer=(_VSALED_ReleaseReportServer)GetProcAddress(hDllInstance,"LED_ReleaseReportServer");
		LED_GetOnlineCount=(_VSALED_GetOnlineCount)GetProcAddress(hDllInstance,"LED_GetOnlineCount");
		LED_GetOnlineList=(_VSALED_GetOnlineList)GetProcAddress(hDllInstance,"LED_GetOnlineList");
		LED_CreateReportServerEx=(_VSALED_CreateReportServerEx)GetProcAddress(hDllInstance,"LED_CreateReportServerEx");
		LED_ReleaseReportServerEx=(_VSALED_ReleaseReportServerEx)GetProcAddress(hDllInstance,"LED_ReleaseReportServerEx");
		LED_GetOnlineCountEx=(_VSALED_GetOnlineCountEx)GetProcAddress(hDllInstance,"LED_GetOnlineCountEx");
		LED_GetOnlineListEx=(_VSALED_GetOnlineListEx)GetProcAddress(hDllInstance,"LED_GetOnlineListEx");

		////////////////////////////////////////////////////////////////////////////////
		LED_GetOnlineList_Java=(_VSALED_GetOnlineList_Java)GetProcAddress(hDllInstance,"LED_GetOnlineList_Java");
		LED_GetOnlineItemIP_Java=(_VSALED_GetOnlineItemIP_Java)GetProcAddress(hDllInstance,"LED_GetOnlineItemIP_Java");
		LED_GetOnlineItemPort_Java=(_VSALED_GetOnlineItemPort_Java)GetProcAddress(hDllInstance,"LED_GetOnlineItemPort_Java");
		LED_GetOnlineItemAddr_Java=(_VSALED_GetOnlineItemAddr_Java)GetProcAddress(hDllInstance,"LED_GetOnlineItemAddr_Java");
		LED_GetOnlineItemName_Java=(_VSALED_GetOnlineItemName_Java)GetProcAddress(hDllInstance,"LED_GetOnlineItemName_Java");
		////////////////////////////////////////////////////////////////////////////////

		//启动在线控制卡监听服务
		//LED_CreateReportServer(8888);
		Preview_VSAInitialize();
		return TRUE;
	}
	else
	{
		FreeLibrary(hDllInstance);
		hDllInstance=NULL;
		return FALSE;
	}
}

BOOL VSA::LED_VSAOpenDevice()
{
	TDeviceParam param;
	memset(&param, 0, sizeof(TDeviceParam));
	//网络方式
	param.devType = DEVICE_TYPE_UDP;
	param.locPort = 8001;
	param.rmtPort = 6666;
	m_Dev = LED_Open(&param, NOTIFY_MODE_SYNC, 0, 0);
	if(m_Dev==-1)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL VSA::LED_VSASendPrgm(int nWidth,int nHeight,CString strPrgm,int nEffect,int nPlaySpeed,int nCardAddr,CString strIP)
{
	RECT rect;
	MakeRoot(ROOT_DOWNLOAD,SCREEN_COLOR);      //创建一个发送序列,以前的将被清除
	AddLeaf(1000*60*60*24);
	SetRect(&rect,0,0,nWidth,nHeight);
	AddText(strPrgm.GetBuffer(0), &rect,nEffect,nPlaySpeed,1,"宋体",12,RGB(255,0,0),0);
	LED_SendToScreen(m_Dev,nCardAddr,strIP.GetBuffer(0),6666);//发送到0地址显示屏，此处需要根据现场情况修改*/
	return TRUE;
}

void VSA::Destroy()
{
	//LED_ReleaseReportServer();
	if (hDllInstance!=NULL)
	{
		FreeLibrary(hDllInstance);
		hDllInstance=NULL;
	}
}