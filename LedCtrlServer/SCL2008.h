#pragma once
class SCL2008
{
public:
	SCL2008();
	~SCL2008();
public:
	/* FAT16的文件目录定义
	define of directory item of FAT16
	struct _DIR_INFO
	{
	char	Name[8];		// 以空格扩展填充的文件名,无结束符       , Filename
	char	Ext[3];			// 以空格扩展填充的扩展名,无结束符       , Extension
	BYTE	Attr;			// 属性, 0x00表示普通文件, 0x10表示子目录, Attribute,0x00:Normal file, 0x10:Sub-directary
	BYTE	Reserved1[10];	// 保留                                  , Reserved
	WORD	Time;			// 文件创建的时间,专门格式               , Time when the file created, special format.
	WORD	Date;			// 文件创建的日期,专门格式               , Date when the file created, special format.
	WORD	Reserved2;		// 保留                                  , Reserved
	UINT	Length;			// 以字节为单位的文件长度                , File length in bytes.
	};
	*/

	// 运行状态结构类型定义
	// Structure of runtime-information
	struct	RunTimeInfoStru
	{
		WORD	Start[15];			// 无关数据      , Reserved.
		WORD	TotalProgCount;		// 总节目数      , Total program count.
		WORD	CurrentProg;		// 当前播放的节目, Which program is playing in current programs.
		WORD	NotUsed1;			// 无关数据      , Reserved.
		WORD	ProgDrv;            // 节目所在驱动器, Disk number of the program from
		WORD	SD_OK;              // SD卡就绪标志  , Ready Flag of the SD card.
		WORD	NotUsed2;           // 保留          , Reserved.
		WORD	Humid;              // 湿度          , Humidity from the sensor
		short	Temprature;         // 温度          , Tempeature from DS18B20
		WORD	PowerSwitch;        // 屏体电源      , State of the power supply of LED.
		int     NotUsed3;           // 保留          , Reserved.
		BYTE	ProgramIndex;       // 节目索引      , Which set of program now playing.
		BYTE	ProgramDrv;         // 节目驱动器    , Such as ProgDrv
		WORD	NotUsed4[8];        // 保留          , Reserved.
		WORD	Second;             // 日历芯片之秒  , Second of the RTC in the controller.
		WORD	Minute;             // 日历芯片之分  , Minute of the RTC in the controller.
		WORD	Hour;               // 日历芯片之时  , Hour   of the RTC in the controller.
		WORD	Day;                // 日历芯片之日  , Day of month of the RTC in the controller.
		WORD	Month;              // 日历芯片之月  , Month  of the RTC in the controller.
		WORD	Week;               // 日历芯片之星期, Day of week of the RTC in the controller.
		WORD	Year;               // 日历芯片之年  , Year   of the RTC in the controller.
		WORD	Brightness;         // 亮度          , Brightness set to LED.
		WORD	NotUsed5;           // 保留          , Reserved.
		char	Com1Data[8][8];     // COM1接收的数据, 8 groups of data received from serial-port 1
		char	Com2Data[8][8];     // COM2接收的数据, 8 groups of data received from serial-port 2
		char	Com3Data[8][8];	    // COM3接收的数据, 8 groups of data received from serial-port 3
		int	    NotUsed6[24];       // 保留          , Reserved.
		WORD	NotUsed7;           // 保留          , Reserved.
		WORD	PowerMode;          // 电源模式      , Mode of Power supply of LED.
		WORD	NotUsed8[7];        // 保留          , Reserved.
		WORD	SW1;                // SW1的状态     , State of the SW1 port.
		WORD	SW2;                // SW2的状态     , State of the SW2 port
		WORD	NotUsed9[57];       // 保留          , Reserved.
	};
	typedef	struct RunTimeInfoStru	RunTimeInfo;

	struct	TextOutInfo
	{
		WORD	Left;		// 区域左   , Left coordinate of the area.
		WORD	Top;		// 区域上   , Top  coordinate of the area.
		WORD	Width;		// 区域宽   , Width  of the area.
		WORD	Height;		// 区域高   , Height of the area.
		LONG	Color;		// 颜色     , Text color
		WORD	ASCFont;	// 英文字体 , Font index of ASCII charactors.
		WORD	HZFont;		// 中文字体 , Font index of Local language charactors.
		WORD	XPos;		// x坐标    , X coordinate for output text.
		WORD	YPos;		// y坐标    , Y coordinate for output text.
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

