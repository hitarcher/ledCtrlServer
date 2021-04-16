#pragma once
#include <windows.h>

#define ST_RED_GREEN_REVERSE    0x00000002    //���̷�ɫ
#define PREVIEW_TIMER_EVENT 10
//IP��ַ��MAC��ַ���ȶ���
#define IP_ADDRESS_LENGTH      4
#define ETHER_ADDRESS_LENGTH   6

#define DEVICE_TYPE_COM    0
#define DEVICE_TYPE_UDP    1
//#define DEVICE_TYPE_485    2

#define SBR_9600           0
#define SBR_14400          1
#define SBR_19200          2
#define SBR_38400          3
#define SBR_57600          4
#define SBR_115200         5

//���豸��Notify
//���ȴ��豸Ӧ���������أ������ʹ�����Ϣ
#define NOTIFY_MODE_NONE   0
//���ȴ��豸Ӧ���������أ����ʹ�����Ϣ
#define NOTIFY_MODE_EVENT  1
//�ȴ��豸Ӧ����ٷ��أ������ʹ�����Ϣ
#define NOTIFY_MODE_SYNC   2

#define ROOT_PLAY       0x11
#define ROOT_DOWNLOAD   0x12
#define ROOT_PLAY2      0x18
#define ROOT_DOWNLOAD2  0x16

#define SCREEN_UNICOLOR    1
#define SCREEN_COLOR       2
#define SCREEN_RGB         3
#define SCREEN_FULL	       4

#define LM_RX_COMPLETE     1
#define LM_TX_COMPLETE     2
#define LM_RESPOND         3
#define LM_TIMEOUT         4
#define LM_NOTIFY          5
#define LM_PARAM           6
#define LM_TX_PROGRESS     7
#define LM_RX_PROGRESS     8

#define DF_YMD             1      //������  "2004��12��31��"
#define DF_HN              2      //ʱ��    "19:20"
#define DF_HNS             3      //ʱ����  "19:20:30"
#define DF_Y               4      //��      "2004"
#define DF_M               5      //��      "12" "01" ע�⣺ʼ����ʾ��λ����
#define DF_D               6      //��
#define DF_H               7      //ʱ
#define DF_N               8      //��
#define DF_S               9      //��
#define DF_W               10     //����    "������"

//����ʱ������ʱformat����
#define CF_DAY             0      //����
#define CF_HOUR            1      //Сʱ��
#define CF_HMS             2      //ʱ����
#define CF_HM              3      //ʱ��
#define CF_MS              4      //����
#define CF_S               5      //��

#define LED_POWER_ON       1
#define LED_POWER_OFF      0

//�����Ƴ���
#define FLOW_NONE          0
#define FLOW_RTS_CTS       1

//�������ִ�С
#define FONT_SET_16        0      //16�����ַ�
#define FONT_SET_24        1      //24�����ַ�
  
#define PKC_QUERY          4
#define PKC_ADJUST_TIME    6
#define PKC_GET_PARAM      7
#define PKC_SET_PARAM      8
#define PKC_GET_POWER      9
#define PKC_SET_POWER      10
#define PKC_GET_BRIGHT     11
#define PKC_SET_BRIGHT     12
#define PKC_SET_SWITCH     20
#define PKC_GET_AUTO_POWER  60
#define PKC_SET_AUTO_POWER  61
#define PKC_GET_AUTO_BRIGHT 62
#define PKC_SET_AUTO_BRIGHT 63
#define PKC_GET_IMPORT      64
#define PKC_GET_LEAF        65
#define PKC_SET_LEAF        66
#define PKC_RESET_DISPLAY   99

#define PKC_MODIFY_IP          7654
#define PKC_GET_DISPLAY_BUFFER 8925

//LED_GetOption, LED_SetOption����ֵ
#define OPTION_TX_TIMER    1      //���÷��ͳ�ʱʱ��(�Ժ���Ϊ��λ)
#define OPTION_REPEAT      2      //���÷������Դ���(1-64)
#define OPTION_MOVE_WINDOW 3      //���÷��ͻ������ڴ�С(1-8),�������Ϊ1����ͨѶ��ʽΪͣ����Э�飬
                                  //�ȷ���һ�����ݰ���ȴ�Ӧ��Ȼ���ٴ�����һ�����ݰ�����������Ч�ʱȽϵ�
typedef struct DEVICEPARAM{
  DWORD  devType;
  DWORD  Speed;
  DWORD  ComPort;
  DWORD  FlowCon;
  DWORD  locPort;
  DWORD  rmtPort;
  DWORD  memory;
  WORD   src_udp_ident;
  WORD   src_udp_port;
  char   src_host[28];
  DWORD  Reserved[5];
}TDeviceParam, *PDeviceParam;

typedef struct DEVINFO{
  char devName[32];     //�豸����
  DWORD devID;          //�豸��ʶ
  DWORD devIP;          //�豸IP��ַ
  WORD devAddr;         //�豸��ַ
  WORD devPort;         //�豸�˿�
  DWORD reserved[5];    //ϵͳ����
}TDevInfo, *PDevInfo;

typedef struct DEVREPORT{
  TDevInfo devInfo;
  double timeUpdate;
}TDevReport, *PDevReport;

typedef struct NOTIFYMESSAGE{
  long   Message;
  long   Command;
  long   Result;
  long   Status;
  long   Address;
  long   Size;
  char   *Buffer;
  TDeviceParam param;
  char   Host[16];
  long   port;
}TNotifyMessage, *PNotifyMessage;

typedef struct BOARDPARAM{
  WORD   width;
  WORD   height;
  WORD   type;
  WORD   frequency;
  DWORD  flag;
  DWORD  uart;
  BYTE   mac[ETHER_ADDRESS_LENGTH];
  BYTE   ip[IP_ADDRESS_LENGTH];
  BYTE   GateMAC[ETHER_ADDRESS_LENGTH];
  BYTE   host[IP_ADDRESS_LENGTH];
  DWORD  brightness;
  DWORD  rom_size;
  long   left;
  long   top;
  WORD   scan_mode;
  WORD   remote_port;
  WORD   line_order;
  WORD   oe_time;
  WORD   shift_freq;
  WORD   refresh_freq;
  BYTE   GateIP[IP_ADDRESS_LENGTH];
  BYTE   ipMask[IP_ADDRESS_LENGTH];
  BYTE   name[32];
  DWORD  ident;
  DWORD  address;
}TBoardParam, *PBoardParam;

typedef struct TIMESTAMP{
  long   time;
  long   date;
}TTimeStamp, *PTimeStamp;

typedef struct _AUTOPOWERTIME
{
	DWORD enabled;
	TTimeStamp opentime[7];
	TTimeStamp closetime[7];
}TAutoPowerTime, *PAutoPowerTime;

typedef struct _BRIGHTTABLE
{
	DWORD enabled;
	BYTE bright[24];
}TBrightTable, *PBrightTable;

typedef void (_stdcall *_VSALED_SetDebugMode)(void);
typedef long (_stdcall *_VSALED_Open)(const PDeviceParam param, long Notify, long Window, long Message);
typedef long (_stdcall *_VSALED_Open2)(long devType, long ComPort, long Speed, long locPort, long Notify, long Window, long Message);
typedef void (_stdcall *_VSALED_Close)(long dev);
typedef void (_stdcall *_VSALED_CloseAll)(void);
typedef void (_stdcall *_VSALED_Query)(long dev, BYTE Address, char *Host, long port);
typedef void (_stdcall *_VSALED_Reset)(long dev, BYTE Address, char *Host, long port);
typedef void (_stdcall *_VSALED_AdjustTime)(long dev, BYTE Address, char *Host, long port);
typedef void (_stdcall *_VSALED_AdjustTimeEx)(long dev, BYTE Address, char *Host, long port, LPSYSTEMTIME psystime);
typedef void (_stdcall *_VSALED_AdjustTimeEx2)(long dev, BYTE Address, char *Host, long port, WORD Year, WORD Month, WORD Day, WORD Hour, WORD Minute, WORD Second);
typedef void (_stdcall *_VSALED_SendToScreen)(long dev, BYTE Address, char *Host, long port);
typedef long (_stdcall *_VSALED_SendToScreenByName)(long dev, char *name);
typedef void (_stdcall *_VSALED_GetPower)(long dev, BYTE Address, char *Host, long port);
typedef void (_stdcall *_VSALED_SetPower)(long dev, BYTE Address, char *Host, long port, int Power);
typedef void (_stdcall *_VSALED_GetLeaf)(long dev, BYTE Address, char *Host, long port);
typedef void (_stdcall *_VSALED_SetLeaf)(long dev, BYTE Address, char *Host, long port, int value);
typedef void (_stdcall *_VSALED_SetSwitch)(long dev, BYTE Address, char *Host, long port, int Value);
typedef void (_stdcall *_VSALED_GetImport)(long dev, BYTE Address, char *Host, long port, int Index);
typedef void (_stdcall *_VSALED_GetBrightness)(long dev, BYTE Address, char *Host, long port);
typedef void (_stdcall *_VSALED_SetBrightness)(long dev, BYTE Address, char *Host, long port, int Brightness);
typedef void (_stdcall *_VSALED_GetAutoPowerList)(long dev, BYTE Address, char *Host, long port);
typedef void (_stdcall *_VSALED_SetAutoPowerList)(long dev, BYTE Address, char *Host, long port, PAutoPowerTime value);
typedef void (_stdcall *_VSALED_GetAutoBrightTable)(long dev, BYTE Address, char *Host, long port);
typedef void (_stdcall *_VSALED_SetAutoBrightTable)(long dev, BYTE Address, char *Host, long port, PBrightTable value);
typedef void (_stdcall *_VSALED_GetDisplayBuffer)(long dev, BYTE Address, char *Host, long port);
typedef void (_stdcall *_VSALED_SetIP)(long dev, BYTE Address, char *Host, long port, char* IP);
typedef void (_stdcall *_VSALED_SetOption)(long optionid, DWORD value);
typedef void (_stdcall *_VSALED_GetLEDParam)(long dev, BYTE Address, char *Host, long port);
typedef void (_stdcall *_VSALED_SetLEDParam)(long dev, BYTE Address, char *Host, long port, PBoardParam param);
typedef void (_stdcall *_VSALED_GetNotifyMessage)(PNotifyMessage Notify);
typedef long (_stdcall *_VSALED_GetNotifyMessageIdent)(void);
typedef long (_stdcall *_VSALED_GetNotifyMessageCommand)(void);
typedef long (_stdcall *_VSALED_GetDeviceStatus)(long dev);
typedef long (_stdcall *_VSALED_GetDeviceNotifyMessage)(long dev, PNotifyMessage Notify);
typedef long (_stdcall *_VSARtfToBitmap)(char* bmpfilename, char *rtffilename, long width, long wordwrap);
typedef long (_stdcall *_VSAMakeRoot)(long RootType, long ScreenType);
typedef long (_stdcall *_VSAMakeRootEx)(long RootType, long ScreenType, long survive);
typedef long (_stdcall *_VSAMakeRootEx_4Byte)(long RootType, long ScreenType, long survive);
typedef long (_stdcall *_VSAAddLeaf)(long DisplayTime); //DisplayTime��λΪ����
typedef long (_stdcall *_VSAAddWindow)(HDC dc,short width, short height, LPRECT rect, long method, long speed, long transparent);
typedef long (_stdcall *_VSAAddWindow2)(HDC dc,short width, short height, long X, long Y, long CX, long CY, long method, long speed, long transparent);
typedef long (_stdcall *_VSAAddPicture)(char *filename, LPRECT rect, long method, long speed, long transparent, long stretch);
typedef long (_stdcall *_VSAAddPicture2)(char *filename, long X, long Y, long CX, long CY, long method, long speed, long transparent, long stretch);
typedef long (_stdcall *_VSAAddRtf)(char *filename, LPRECT rect, long method, long speed, long transparent, long wordwrap);
typedef long (_stdcall *_VSAAddRtf2)(char *filename, long X, long Y, long CX, long CY, long method, long speed, long transparent, long wordwrap);
typedef long (_stdcall *_VSAAddDateTime)(LPRECT rect, long transparent, char *fontname, long fontsize, long fontcolor, long format, long fontstyle);
typedef long (_stdcall *_VSAAddDateTime2)(long X, long Y, long CX, long CY, long transparent, char *fontname, long fontsize, long fontcolor, long format, long fontstyle);
typedef long (_stdcall *_VSAAddString)(char *str, LPRECT rect, long method, long speed, long transparent, long fontset, long fontcolor);
typedef long (_stdcall *_VSAAddString2)(char *str, long X, long Y, long CX, long CY, long method, long speed, long transparent, long fontset, long fontcolor);
typedef long (_stdcall *_VSAAddText)(char *str, LPRECT rect, long method, long speed, long transparent, char *fontname, long fontsize, long fontcolor, long fontstyle);
typedef long (_stdcall *_VSAAddText2)(char *str, long X, long Y, long CX, long CY, long method, long speed, long transparent, char *fontname, long fontsize, long fontcolor, long fontstyle);
typedef long (_stdcall *_VSAAddTextEx)(char *str, LPRECT rect, long method, long speed, long transparent, char *fontname, long fontsize, long fontcolor, long fontstyle, long wordwrap);
typedef long (_stdcall *_VSAAddTextEx2)(char *str, long X, long Y, long CX, long CY, long method, long speed, long transparent, char *fontname, long fontsize, long fontcolor, long fontstyle, long wordwrap);
typedef long (_stdcall *_VSAAddTextVSplit)(char *str, LPRECT rect, long method, long speed, long transparent, long count_a, char *fontname_a, long fontsize_a, long fontcolor_a, long fontstyle_a, char *fontname_b, long fontsize_b, long fontcolor_b, long fontstyle_b);
typedef long (_stdcall *_VSAAddTextVSplit2)(char *str, long X, long Y, long CX, long CY, long method, long speed, long transparent, long count_a, char *fontname_a, long fontsize_a, long fontcolor_a, long fontstyle_a, char *fontname_b, long fontsize_b, long fontcolor_b, long fontstyle_b);
typedef long (_stdcall *_VSAAddMovie)(char *filename, LPRECT rect, long stretch);
typedef long (_stdcall *_VSAAddMovie2)(char *filename, long X, long Y, long CX, long CY, long stretch);
typedef long (_stdcall *_VSAAddCountUp)(LPRECT rect, long transparent, char *fontname, long fontsize, long fontcolor, long format, LPSYSTEMTIME starttime, long fontstyle);
typedef long (_stdcall *_VSAAddCountDown)(LPRECT rect, long transparent, char *fontname, long fontsize, long fontcolor, long format, LPSYSTEMTIME endtime, long fontstyle);
typedef long (_stdcall *_VSAAddCampaignTime)(LPRECT rect, long transparent, char *fontname, long fontsize, long fontcolor, long format, LPSYSTEMTIME starttime, LPSYSTEMTIME endtime, LPSYSTEMTIME campaigntime, long step, long fontstyle);

//���Ͷ����ı��������Զ����У������ֳ�����ʾ��Χ������ָ��������ʽ����������̬��ʾ
//  RangeModeΪ������Χ��ʽ
//      =0��ʾʼ��ʹ��ָ��������ʽ
//      =1��ʾ���ȳ�����ʾ��Χʱ��ʹ��ָ��������ʽ��������HAlignָ���Ķ��뷽ʽ��ʾ
//      =2��ʾ�߶ȳ�����ʾ��Χʱ��ʹ��ָ��������ʽ��������VAlignָ���Ķ��뷽ʽ��ʾ
typedef long (_stdcall *_VSAAddTextRange)(char *str, LPRECT rect, long method, long speed, long transparent, long halign, long valign, long rangemode, char *fontname, long fontsize, long fontcolor, long fontstyle, long wordwrap);

/*{
  ('DotM|����뾶'); ('DotH|3,6,9��뾶');
  ('ColorH|Сʱָ����ɫ'); ('ColorM|����ָ����ɫ'); ('ColorS|��ָ����ɫ');
  ('ColorD|3,6,9����ɫ'); ('ColorN|������ɫ');
  ('WidthH|Сʱָ����'); ('WidthM|����ָ����');
}*/
typedef long (_stdcall *_VSAAddClock)(LPRECT rect, long transparent, long WidthH, long WidthM, long DotH, long DotM, DWORD ColorH, DWORD ColorM, DWORD ColorS, DWORD ColorD, DWORD ColorN);
typedef long (_stdcall *_VSAAddClock2)(long X, long Y, long CX, long CY, long transparent, long WidthH, long WidthM, long DotH, long DotM, DWORD ColorH, DWORD ColorM, DWORD ColorS, DWORD ColorD, DWORD ColorN);
typedef long (_stdcall *_VSAConstructerOpen)(char* filename);
typedef long (_stdcall *_VSAConstructerClose)(void);
typedef long (_stdcall *_VSAConstructerMakeRoot)(char* ledname, long RootType, long ScreenType);
typedef void (_stdcall *_VSALED_CreateReportServer)(WORD port);
typedef void (_stdcall *_VSALED_ReleaseReportServer)(void);
typedef long (_stdcall *_VSALED_GetOnlineCount)(void);
typedef long (_stdcall *_VSALED_GetOnlineList)(BYTE* obuffer);
typedef void (_stdcall *_VSALED_CreateReportServerEx)(long index, WORD port);
typedef void (_stdcall *_VSALED_ReleaseReportServerEx)(long index);
typedef long (_stdcall *_VSALED_GetOnlineCountEx)(long index);
typedef long (_stdcall *_VSALED_GetOnlineListEx)(long index, BYTE* obuffer);
typedef long (_stdcall *_VSALED_GetOnlineList_Java)(void);
typedef long (_stdcall *_VSALED_GetOnlineItemIP_Java)(long index);
typedef long (_stdcall *_VSALED_GetOnlineItemPort_Java)(long index);
typedef long (_stdcall *_VSALED_GetOnlineItemAddr_Java)(long index);
typedef char*(_stdcall *_VSALED_GetOnlineItemName_Java)(long index);
////////////////////////////////////////////////////////////////////////////////
typedef long (_stdcall *_VSAPreview_Create)(char* FontSetFile, DWORD ScreenType, DWORD Width, DWORD Height, long Window, char* Stream, PBoardParam Param);
typedef long (_stdcall *_VSAPreview_Step)(long Window);
typedef void (_stdcall *_VSAPreview_Destroy)(void);

class VSA
{
public:
	VSA(void);
	~VSA(void);

	//add by chengzhi	
	//��ʼ����չA����̬��
	BOOL LED_VSAInitialize(void);
	BOOL LED_VSAOpenDevice();
	BOOL LED_VSASendPrgm(int nWidth,int nHeight,CString strPrgm,int nEffect,int nPlaySpeed,int nCardAddr,CString strIP);
	void Destroy();
	////////////////////////////////////////////////////////////////////////////////
	void Preview_VSAInitialize();
	void Preview_VSAFinalize();
public:
	HINSTANCE hDllInstance;
	HINSTANCE preview_hInstance;
	int m_Dev;
	char* disp_buffer;
};

