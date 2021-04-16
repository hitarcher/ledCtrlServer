#pragma once
class SCL2008
{
public:
	SCL2008();
	~SCL2008();
public:
	/* FAT16���ļ�Ŀ¼����
	define of directory item of FAT16
	struct _DIR_INFO
	{
	char	Name[8];		// �Կո���չ�����ļ���,�޽�����       , Filename
	char	Ext[3];			// �Կո���չ������չ��,�޽�����       , Extension
	BYTE	Attr;			// ����, 0x00��ʾ��ͨ�ļ�, 0x10��ʾ��Ŀ¼, Attribute,0x00:Normal file, 0x10:Sub-directary
	BYTE	Reserved1[10];	// ����                                  , Reserved
	WORD	Time;			// �ļ�������ʱ��,ר�Ÿ�ʽ               , Time when the file created, special format.
	WORD	Date;			// �ļ�����������,ר�Ÿ�ʽ               , Date when the file created, special format.
	WORD	Reserved2;		// ����                                  , Reserved
	UINT	Length;			// ���ֽ�Ϊ��λ���ļ�����                , File length in bytes.
	};
	*/

	// ����״̬�ṹ���Ͷ���
	// Structure of runtime-information
	struct	RunTimeInfoStru
	{
		WORD	Start[15];			// �޹�����      , Reserved.
		WORD	TotalProgCount;		// �ܽ�Ŀ��      , Total program count.
		WORD	CurrentProg;		// ��ǰ���ŵĽ�Ŀ, Which program is playing in current programs.
		WORD	NotUsed1;			// �޹�����      , Reserved.
		WORD	ProgDrv;            // ��Ŀ����������, Disk number of the program from
		WORD	SD_OK;              // SD��������־  , Ready Flag of the SD card.
		WORD	NotUsed2;           // ����          , Reserved.
		WORD	Humid;              // ʪ��          , Humidity from the sensor
		short	Temprature;         // �¶�          , Tempeature from DS18B20
		WORD	PowerSwitch;        // �����Դ      , State of the power supply of LED.
		int     NotUsed3;           // ����          , Reserved.
		BYTE	ProgramIndex;       // ��Ŀ����      , Which set of program now playing.
		BYTE	ProgramDrv;         // ��Ŀ������    , Such as ProgDrv
		WORD	NotUsed4[8];        // ����          , Reserved.
		WORD	Second;             // ����оƬ֮��  , Second of the RTC in the controller.
		WORD	Minute;             // ����оƬ֮��  , Minute of the RTC in the controller.
		WORD	Hour;               // ����оƬ֮ʱ  , Hour   of the RTC in the controller.
		WORD	Day;                // ����оƬ֮��  , Day of month of the RTC in the controller.
		WORD	Month;              // ����оƬ֮��  , Month  of the RTC in the controller.
		WORD	Week;               // ����оƬ֮����, Day of week of the RTC in the controller.
		WORD	Year;               // ����оƬ֮��  , Year   of the RTC in the controller.
		WORD	Brightness;         // ����          , Brightness set to LED.
		WORD	NotUsed5;           // ����          , Reserved.
		char	Com1Data[8][8];     // COM1���յ�����, 8 groups of data received from serial-port 1
		char	Com2Data[8][8];     // COM2���յ�����, 8 groups of data received from serial-port 2
		char	Com3Data[8][8];	    // COM3���յ�����, 8 groups of data received from serial-port 3
		int	    NotUsed6[24];       // ����          , Reserved.
		WORD	NotUsed7;           // ����          , Reserved.
		WORD	PowerMode;          // ��Դģʽ      , Mode of Power supply of LED.
		WORD	NotUsed8[7];        // ����          , Reserved.
		WORD	SW1;                // SW1��״̬     , State of the SW1 port.
		WORD	SW2;                // SW2��״̬     , State of the SW2 port
		WORD	NotUsed9[57];       // ����          , Reserved.
	};
	typedef	struct RunTimeInfoStru	RunTimeInfo;

	struct	TextOutInfo
	{
		WORD	Left;		// ������   , Left coordinate of the area.
		WORD	Top;		// ������   , Top  coordinate of the area.
		WORD	Width;		// �����   , Width  of the area.
		WORD	Height;		// �����   , Height of the area.
		LONG	Color;		// ��ɫ     , Text color
		WORD	ASCFont;	// Ӣ������ , Font index of ASCII charactors.
		WORD	HZFont;		// �������� , Font index of Local language charactors.
		WORD	XPos;		// x����    , X coordinate for output text.
		WORD	YPos;		// y����    , Y coordinate for output text.
	};
	typedef struct TextOutInfo	TEXTINFO;

	typedef BOOL(__stdcall *_SCL_NetInitial)(WORD mDevID, char *Password, char *RemoteIP, int SecTimeOut, int RetryTimes, WORD UDPPort, BOOL bSCL2008);
	typedef BOOL(__stdcall *_SCL_ComInitial)(WORD mDevID, int ComPort, int Baudrate, int LedNum, int SecTimeOut, int RetryTimes, BOOL bSCL2008);
	typedef BOOL(__stdcall *_SCL_Close)(WORD mDevID);
	typedef BOOL(__stdcall *_SCL_SetRemoteIP)(WORD mDevID, char *RemoteIP);
	typedef BOOL(__stdcall *_SCL_SetLEDNum)(WORD mDevID, int  LedNum);
	typedef BOOL(__stdcall *_SCL_TargetSCL2008)(WORD mDevID, BOOL b2008);
	typedef BOOL(__stdcall *_SCL_GetLastResult)(WORD mDevID);
	typedef BOOL(__stdcall *_SCL_InitForPackage)(WORD mDevID, BOOL bNet, BOOL bSCL2008);
	typedef int(__stdcall *_SCL_GetPackage)(WORD mDevID, BYTE *Data, int *AnswerCount);
	typedef BOOL(__stdcall *_SCL_CheckAnswer)(WORD mDevID, int AnswerCount, BYTE *AnswerData);
	typedef BOOL(__stdcall *_SCL_SendFile)(WORD mDevID, int Drv, char *Path, char *LocalFilename);
	typedef int(__stdcall *_SCL_ReceiveFile)(WORD mDevID, int Drv, char *RemoteFileName, char *LocalFilename);
	typedef BOOL(__stdcall *_SCL_FormatDisk)(WORD mDevID, int drv);
	typedef int(__stdcall *_SCL_FreeSpace)(WORD mDevID, int Drv);
	typedef int(__stdcall *_SCL_DirItemCount)(WORD mDevID, int Drv, char *Path);
	typedef BOOL(__stdcall *_SCL_GetDirItem)(WORD mDevID, int ItemCount, void *Buff);
	typedef BOOL(__stdcall *_SCL_RemoveFile)(WORD mDevID, int Drv, char *FileName);
	typedef BOOL(__stdcall *_SCL_MD)(WORD mDevID, int Drv, char *PathName);
	typedef BOOL(__stdcall *_SCL_RD)(WORD mDevID, int Drv, char *PathName);
	typedef LONG(__stdcall *_SCL_LoadFile)(WORD mDevID, int DrvNo, char *FileName);
	typedef BOOL(__stdcall *_SCL_SaveFile)(WORD mDevID, int DrvNo, char *FileName, int Len, int Date, int Time);
	typedef BOOL(__stdcall *_SCL_SendData)(WORD mDevID, int Offset, int SendBytes, BYTE *Buff);
	typedef BOOL(__stdcall *_SCL_ReceiveData)(WORD mDevID, int Offset, int ReadBytes, BYTE *Buff);
	typedef BOOL(__stdcall *_SCL_ShowString)(WORD mDevID, short *Info, char *Str);
	typedef BOOL(__stdcall *_SCL_Reset)(WORD mDevID);
	typedef BOOL(__stdcall *_SCL_Replay)(WORD mDevID, int Drv, int PlayListIndex);
	typedef BOOL(__stdcall *_SCL_SetTimer)(WORD mDevID);
	typedef BOOL(__stdcall *_SCL_SetBright)(WORD mDevID, short Brightness);
	typedef BOOL(__stdcall *_SCL_SetOnOffTime)(WORD mDevID, short OnTime, short OffTime);
	typedef BOOL(__stdcall *_SCL_SetTempOffset)(WORD mDevID, short Offset);
	typedef BOOL(__stdcall *_SCL_SetPowerMode)(WORD mDevID, int PowerMode);
	typedef BOOL(__stdcall *_SCL_GetRunTimeInfo)(WORD mDevID, void *Buff512Bytes);
	typedef BOOL(__stdcall *_SCL_GetPlayInfo)(WORD mDevID, BYTE *PlayInfo);
	typedef BOOL(__stdcall *_SCL_LedShow)(WORD mDevID, BOOL OnOff);
	typedef BOOL(__stdcall *_SCL_SetExtSW)(WORD mDevID, WORD OnOff);
	typedef BOOL(__stdcall *_SCL_PictToXMPFile)(int ColorType, int Width, int Height, BOOL bStretched, char *PictFileName, char *XMPFileName);
	typedef int(__stdcall *_SCL_GetMaxFileSize)(int TotalBuffCount, BOOL bSmallest);
	typedef int(__stdcall *_SCL_AddXMPToXMP)(char *InFileName, char *OutFileName, int BuffSize);
	typedef BOOL(__stdcall *_SCL_GetFileDosDateTime)(char *Name, int *Date, int *Time);

	_SCL_NetInitial		    SCL_NetInitial;
	_SCL_ComInitial		    SCL_ComInitial;
	_SCL_Close			    SCL_Close;
	_SCL_SetRemoteIP	    SCL_SetRemoteIP;
	_SCL_SetLEDNum		    SCL_SetLEDNum;
	_SCL_TargetSCL2008      SCL_TargetSCL2008;
	_SCL_GetLastResult		SCL_GetLastResult;
	_SCL_InitForPackage     SCL_InitForPackage;
	_SCL_GetPackage	        SCL_GetPackage;
	_SCL_CheckAnswer	    SCL_CheckAnswer;
	_SCL_FormatDisk		    SCL_FormatDisk;
	_SCL_FreeSpace		    SCL_FreeSpace;
	_SCL_DirItemCount	    SCL_DirItemCount;
	_SCL_GetDirItem		    SCL_GetDirItem;
	_SCL_SendFile		    SCL_SendFile;
	_SCL_ReceiveFile	    SCL_ReceiveFile;
	_SCL_RemoveFile		    SCL_RemoveFile;
	_SCL_MD				    SCL_MD;
	_SCL_RD				    SCL_RD;
	_SCL_LoadFile			SCL_LoadFile;
	_SCL_SaveFile			SCL_SaveFile;
	_SCL_SendData			SCL_SendData;
	_SCL_ReceiveData		SCL_ReceiveData;
	_SCL_ShowString		    SCL_ShowString;
	_SCL_Reset			    SCL_Reset;
	_SCL_Replay			    SCL_Replay;
	_SCL_SetTimer		    SCL_SetTimer;
	_SCL_SetBright		    SCL_SetBright;
	_SCL_SetOnOffTime	    SCL_SetOnOffTime;
	_SCL_SetTempOffset	    SCL_SetTempOffset;
	_SCL_SetPowerMode	    SCL_SetPowerMode;
	_SCL_GetRunTimeInfo	    SCL_GetRunTimeInfo;
	_SCL_GetPlayInfo	    SCL_GetPlayInfo;
	_SCL_LedShow			SCL_LedShow;
	_SCL_SetExtSW			SCL_SetExtSW;
	_SCL_PictToXMPFile	    SCL_PictToXMPFile;
	_SCL_GetMaxFileSize	    SCL_GetMaxFileSize;
	_SCL_AddXMPToXMP	    SCL_AddXMPToXMP;
	_SCL_GetFileDosDateTime	SCL_GetFileDosDateTime;

	HINSTANCE				hSCL_Dll;

public:
	BOOL LED_SCL2008Initialize();
	void LED_SCL2008FreeDll();
};

