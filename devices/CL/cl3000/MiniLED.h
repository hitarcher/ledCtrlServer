/* Copyright (C) Lytec Inc., 2010 */
/* All rights reserved */

#ifndef MiniLEDH
#define MiniLEDH

#include <windows.h>

// 节目播放效果
enum
{
  EFFECT_FOLLOW = 0, // 同前一节目的退出效果/同后一节目的进入效果
  EFFECT_RANDOM,     // 随机模式
  EFFECT_DIRECT,     // 直接显示/消失
  EFFECT_TOLEFT,     // 向左移入/移出
  EFFECT_TOUP,       // 向上移入/移出
  EFFECT_MELT,       // 溶入/溶出
  EFFECT_EXRIGHT,    // 向右展开/擦除
  EFFECT_EXDOWN,     // 向下展开/擦除
  EFFECT_EXLEFT,     // 向左展开/擦除
  EFFECT_EXUP,       // 向上展开/擦除
  EFFECT_ARROUND,    // 从中心向四周展开/擦除
  EFFECT_EXHCENTER,  // 从中间向左右两边展开/擦除
  EFFECT_EXHSIDE,    // 从左右两边向中间展开/擦除
  EFFECT_EXVCENTER,  // 从中间向上下两边展开/擦除
  EFFECT_EXVSIDE,    // 从上下两边向中间展开/擦除
  EFFECT_TODOWN,     // 向下移入/移出
  EFFECT_TORIGHT,    // 向右移入/移出
  EFFECT_HDWINDOW,   // 水平下拉百叶窗
  EFFECT_HUWINDOW,   // 水平上拉百叶窗
  EFFECT_VRWINDOW,   // 垂直右拉百页窗
  EFFECT_VLWINDOW,   // 垂直左拉百页窗
  EFFECT_CIRCLE,     // 扇形展开
  EFFECT_LOZENGE,    // 菱形展开
  EFFECT_DROPDOWN,   // 向下拉入/拉出
  EFFECT_DROPRIGHT,  // 向右拉入/拉出
  EFFECT_FLASH3      // 闪烁三次
};

#pragma pack(1)

/*
 * 节目表项结构定义
 */
typedef struct               // 16字节
{
  WORD  Flag;                // D1-D0   : 本节目项所属区域号(0-3)
                             // D5-D2   : 0000-本节目表项为文件 0001-本节目表项为实时版面
                             // D15-D6  : 本节目表项所属组号0-999，缺省填0
  WORD	PicFIndex;           // D10-D0  : 图片文件序号(0-2047)或实时版面序号(0-3)
                             // D15-D11 : 保留，填00000
  DWORD	Effect;              // D5-D0   : 进入播放效果，见EFFECT_宏定义
                             // D11-D6  : 退出播放效果，见EFFECT_宏定义
                             // D31-D12 : 保留，填0
  DWORD SpeedStay;           // D3-D0   : 进入移动速度，0-12分别表示最慢到最快的移动速度，大于12按12处理
                             // D7-D4   : 退出移动速度，0-12分别表示最慢到最快的移动速度，大于12按12处理
                             // D27-D8  : 停留时间，秒，若为0xFFFFF则无限停留
                             // D31-D28 : 保留，填0
  DWORD	Schedule;            // 允许播放的开始结束时间，不用定时填0xFFFFFFFF
                             // D5-D0   : 开始分
                             // D11-D6  : 结束分
                             // D16-D12 : 开始小时
                             // D21-D17 : 结束小时
                             // D24-D22 : 保留，填111
                             // D31-D25 : 周定时，D31对应周日，D30-D25对应周六-周一
} ProgItemType;

typedef struct
{
  BYTE Type;                 // 文件类型 0-单红图片 1-红绿双色图片
  BYTE PicCount;             // 图片个数
  WORD PicHeight;            // 图片高度
  WORD PicWidth;             // 图片宽度
  WORD PicOffset;            // 第一个图片在文件内的偏移（文件的第一个字节偏移为0）
  WORD LastPicH;             // 最后一个图片高度
  WORD LastPicW;             // 最后一个图片宽度
} PicFileHdr;

typedef struct
{
  BYTE Second;
  BYTE Minute;
  BYTE Hour;
  BYTE Day;
  BYTE Month;
  BYTE Week;
  BYTE Year;
  BYTE NC;                   // 保留，填0
} ClockType;

// 系统运行状态结构
typedef struct
{
  BYTE  Ver[4];              // 版本：Ver[0]硬件主次版本，BCD码，即0x10代表1.0，主版本为卡类型，次版本为PCB版本
                             //       Ver[1]硬件功能附加说明码，保留，填0
                             //       以上两个字节由系统初始化时检测硬件设置后填写
                             //       Ver[2],Ver[3]，软件版本，BCD码，由系统初始化时拷贝
  BYTE  RSFlag;              // D0    : 是否插上测试短路插 0未插上 1插上
                             // D1    : LEDPwrSwitch 屏体电源开关状态 0 - 断电 1 - 通电
                             // D2    : DS18B20温度芯片存在状态 0-不可用 1-可用
                             // D3    : DS3231时钟芯片存在状态  0-不可用 1-可用
                             // D7-D4 : 保留，填0
  BYTE  BrightLevel;         // 控制卡实际输出的亮度等级 0 - 关屏 1..16 - 16级亮度设置，分别代表1/16亮度到全亮
  BYTE  Brightness;          // 亮度传感器采集亮度等级
  BYTE  Humidity;            // 湿度传感器采集湿度值, 0 ~ 99
  signed short Temperature;  // 温度传感器采集温度值, -55 ~ +125
  WORD  ChipTemp;            // 控制卡温度采集值
  WORD  Analog1;             // 模拟量1采集值
  WORD  Analog2;             // 模拟量2采集值
  BYTE  NC0[4];              // 保留，填0
  BYTE  Clock[8];            // 时钟，8个字节分别对应秒0-59、分0-59、时0-23、日1-31、月1-12、星期0-6、年0-99，一字节未用
  BYTE  PowerMode;           // 开关屏控制 0:强行关屏 1:强行开屏 2:自动开关屏
  BYTE  NC1[11];             // 保留，填0
  DWORD StorgeTotalSize;     // 外部存储Flash的总容量。单位：字节
  DWORD StorgePicSize;       // 图片文件可用容量。单位：字节
  DWORD PicFileSize;         // 实际使用的图片文件最大的字节数，由分区大小计算得到，为ExFlash扇区大小的倍数
  WORD  ProgGroup;           // 当前播放的节目组索引（0-1023）
  BYTE  LoadedFonts;         // 装载的可用字库数
  BYTE  NC2;                 // 对齐字节，填0
} RunningStateStru;

/*
 * 单字节编码的Range固定为32..255
 * Unicode和双(变)字节编码的Range由FontRange_t[]定义
 */
typedef union
{
  struct                     // 对应Unicode编码
  {
    WORD  CodeStart;	       // 编码起点
    WORD  CodeEnd;           // 编码终点
  } Unicode;
  struct                     // 对应双(变)字节编码
  {
    BYTE  Code1Start;	       // 第1组编码起点，也用于变字节编码中单字节编码的起点
    BYTE  Code1End;          // 第1组编码终点，也用于变字节编码中单字节编码的终点
    BYTE  Code2Start;	       // 第2组编码起点
    BYTE  Code2End;          // 第2组编码终点
  } DBCS;
} FontRange_t;

typedef struct               // 100字节
{
  DWORD FontDotAddr;         // 字库点阵存储地址（SPI FLASH地址），必须为页开始地址，0xFFFFFFFF表示该项未用
  WORD  Flag;                // 标识：bit1..0:字符编码类型, 0:单字节编码(ASCII, ISO8859) 1:Unicode 2:双(变)字节编码(GB2312, BIG5) 其它位保留填0
  BYTE  FontWidth;           // 字体宽度，0xFF无效
  BYTE  FontHeight;	         // 字体高度，0xFF无效
  WORD  CharBytes;           // 每字符字节数
  WORD  CharCount;           // 字库中字符个数，乘以每字符字节数即为字库点阵大小
  BYTE  RangeCount;          // 编码区个数，最多支持8个Range
  BYTE  RangeCountH;         // 半角字符（实际字符宽度为字体宽度的一半）编码区个数。
                             // 定宽字库可包含半角和全角两种宽度的字符，半角字符存储在字库的前面，后面是全角字符
  BYTE  NC[6];               // 保留，填0
  char  Name[16];            // 字库名称，可以使用名称来引用字库，其字符只能使用ASCII码，格式为例 songti-16x16
  FontRange_t Range[16];     // 字库编码区结构，最多支持16个Range
} FontInfoStru;

#pragma pack()

typedef int  (__cdecl *_MC_ComInitial    )(WORD mDevID, int ComPort, int Baudrate, int TimeOut, int Retries, int LedNum);
typedef int  (__cdecl *_MC_NetInitial    )(WORD mDevID, char *Password, char *RemoteIP, int TimeOut, int Retries, WORD UDPPort);
typedef BOOL (__cdecl *_MC_Close         )(WORD mDevID);
typedef BOOL (__cdecl *_MC_Reset         )(WORD mDevID, DWORD flag);
typedef BOOL (__cdecl *_MC_SetLEDNum     )(WORD mDevID, int LedNum);
typedef BOOL (__cdecl *_MC_SetRemoteIP   )(WORD mDevID, char *RemoteIP);
typedef BOOL (__cdecl *_MC_ControlPlay   )(WORD mDevID, DWORD flag);
typedef BOOL (__cdecl *_MC_SetBright     )(WORD mDevID, BYTE Brightness);
typedef BOOL (__cdecl *_MC_SetPowerMode  )(WORD mDevID, BYTE Mode);
typedef BOOL (__cdecl *_MC_SetAutoPower  )(WORD ID, BYTE OnHour, BYTE OnMinute, BYTE OffHour, BYTE OffMinute);
typedef BOOL (__cdecl *_MC_SendBrightTable)(WORD mDevID, WORD *pBrightTable);
typedef BOOL (__cdecl *_MC_SetDispParams )(WORD mDevID, BYTE *pData, WORD Len);
typedef BOOL (__cdecl *_MC_SetClock      )(WORD mDevID);
typedef BOOL (__cdecl *_MC_GetClock      )(WORD mDevID, ClockType *clk);
typedef BOOL (__cdecl *_MC_GetRunTimeInfo)(WORD mDevID, BYTE *Buff, WORD offset, WORD len);
typedef BOOL (__cdecl *_MC_ChangeGroup   )(WORD mDevID, WORD group, BYTE flag, BYTE *Param);

typedef BOOL (__cdecl *_MC_SendProgList  )(WORD mDevID, BYTE *pProgList, WORD ProgCount);
typedef BOOL (__cdecl *_MC_SendXMPXPic   )(WORD mDevID, WORD PicIndex, BYTE *PicBuff, DWORD PicLength);
typedef BOOL (__cdecl *_MC_GetXMPXPic    )(WORD mDevID, WORD PicIndex, BYTE *PicBuff, DWORD PicLength);
typedef BOOL (__cdecl *_MC_SendText      )(WORD mDevID, WORD TxtIndex, unsigned short Color, unsigned char *Str, BYTE Encode);
typedef BOOL (__cdecl *_MC_SendRTView    )(WORD mDevID, BYTE *pData, WORD len);
typedef BOOL (__cdecl *_MC_GetRTViewPkt  )(WORD mDevID, BYTE *pData, WORD offset, WORD Len);
typedef BOOL (__cdecl *_MC_SendFontInfo  )(WORD mDevID, BYTE *pData, WORD Len);
typedef BOOL (__cdecl *_MC_SendFontLibPkt)(WORD mDevID, BYTE FIdx, BYTE *pData, WORD Len, DWORD Offset);
typedef BOOL (__cdecl *_MC_ShowString    )(WORD mDevID, WORD Left, WORD Top, WORD Width, WORD Height, WORD XPos, WORD YPos, WORD Color, BYTE *str, BYTE Option);
typedef BOOL (__cdecl *_MC_TxtToXMPXFile )(WORD mDevID, WORD PicFIndex, WORD Width, WORD Height, WORD Color, BYTE *Str, BYTE Encode, BYTE Mode);
typedef BOOL (__cdecl *_MC_ShowXMPXPic   )(WORD mDevID, WORD Left, WORD Top, WORD Width, WORD Height, BYTE *PicBuff, DWORD PicLength);

typedef BOOL (__cdecl *_MC_InitForPackage)(WORD mDevID, BOOL bNet);
typedef int  (__cdecl *_MC_GetPackage    )(WORD mDevID, BYTE *Data, int *AnswerCount);
typedef BOOL (__cdecl *_MC_CheckAnswer   )(WORD mDevID, BYTE *Data, int *AnswerCount);

extern _MC_ComInitial        MC_ComInitial;
extern _MC_NetInitial        MC_NetInitial;
extern _MC_Close             MC_Close;
extern _MC_Reset             MC_Reset;
extern _MC_SetLEDNum         MC_SetLEDNum;
extern _MC_SetRemoteIP       MC_SetRemoteIP;
extern _MC_ControlPlay       MC_ControlPlay;
extern _MC_SetBright         MC_SetBright;
extern _MC_SetPowerMode      MC_SetPowerMode;
extern _MC_SetAutoPower      MC_SetAutoPower;
extern _MC_SendBrightTable   MC_SendBrightTable;
extern _MC_SetDispParams     MC_SetDispParams;
extern _MC_SetClock          MC_SetClock;
extern _MC_GetClock          MC_GetClock;
extern _MC_GetRunTimeInfo    MC_GetRunTimeInfo;
extern _MC_ChangeGroup       MC_ChangeGroup;

extern _MC_SendProgList      MC_SendProgList;
extern _MC_SendXMPXPic       MC_SendXMPXPic;
extern _MC_GetXMPXPic        MC_GetXMPXPic;
extern _MC_SendText          MC_SendText;
extern _MC_SendRTView        MC_SendRTView;
extern _MC_GetRTViewPkt      MC_GetRTViewPkt;
extern _MC_SendFontInfo      MC_SendFontInfo;
extern _MC_SendFontLibPkt    MC_SendFontLibPkt;
extern _MC_ShowString        MC_ShowString;
extern _MC_TxtToXMPXFile     MC_TxtToXMPXFile;
extern _MC_ShowXMPXPic       MC_ShowXMPXPic;

extern _MC_InitForPackage    MC_InitForPackage;
extern _MC_GetPackage        MC_GetPackage;
extern _MC_CheckAnswer       MC_CheckAnswer;

extern HINSTANCE             hMC_DLL;

extern BOOL LoadMiniLEDdll( void );
extern void FreeMiniLEDdll( void );

#endif /* MiniLEDH */
