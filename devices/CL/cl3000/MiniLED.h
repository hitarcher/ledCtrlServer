/* Copyright (C) Lytec Inc., 2010 */
/* All rights reserved */

#ifndef MiniLEDH
#define MiniLEDH

#include <windows.h>

// ��Ŀ����Ч��
enum
{
  EFFECT_FOLLOW = 0, // ͬǰһ��Ŀ���˳�Ч��/ͬ��һ��Ŀ�Ľ���Ч��
  EFFECT_RANDOM,     // ���ģʽ
  EFFECT_DIRECT,     // ֱ����ʾ/��ʧ
  EFFECT_TOLEFT,     // ��������/�Ƴ�
  EFFECT_TOUP,       // ��������/�Ƴ�
  EFFECT_MELT,       // ����/�ܳ�
  EFFECT_EXRIGHT,    // ����չ��/����
  EFFECT_EXDOWN,     // ����չ��/����
  EFFECT_EXLEFT,     // ����չ��/����
  EFFECT_EXUP,       // ����չ��/����
  EFFECT_ARROUND,    // ������������չ��/����
  EFFECT_EXHCENTER,  // ���м�����������չ��/����
  EFFECT_EXHSIDE,    // �������������м�չ��/����
  EFFECT_EXVCENTER,  // ���м�����������չ��/����
  EFFECT_EXVSIDE,    // �������������м�չ��/����
  EFFECT_TODOWN,     // ��������/�Ƴ�
  EFFECT_TORIGHT,    // ��������/�Ƴ�
  EFFECT_HDWINDOW,   // ˮƽ������Ҷ��
  EFFECT_HUWINDOW,   // ˮƽ������Ҷ��
  EFFECT_VRWINDOW,   // ��ֱ������ҳ��
  EFFECT_VLWINDOW,   // ��ֱ������ҳ��
  EFFECT_CIRCLE,     // ����չ��
  EFFECT_LOZENGE,    // ����չ��
  EFFECT_DROPDOWN,   // ��������/����
  EFFECT_DROPRIGHT,  // ��������/����
  EFFECT_FLASH3      // ��˸����
};

#pragma pack(1)

/*
 * ��Ŀ����ṹ����
 */
typedef struct               // 16�ֽ�
{
  WORD  Flag;                // D1-D0   : ����Ŀ�����������(0-3)
                             // D5-D2   : 0000-����Ŀ����Ϊ�ļ� 0001-����Ŀ����Ϊʵʱ����
                             // D15-D6  : ����Ŀ�����������0-999��ȱʡ��0
  WORD	PicFIndex;           // D10-D0  : ͼƬ�ļ����(0-2047)��ʵʱ�������(0-3)
                             // D15-D11 : ��������00000
  DWORD	Effect;              // D5-D0   : ���벥��Ч������EFFECT_�궨��
                             // D11-D6  : �˳�����Ч������EFFECT_�궨��
                             // D31-D12 : ��������0
  DWORD SpeedStay;           // D3-D0   : �����ƶ��ٶȣ�0-12�ֱ��ʾ�����������ƶ��ٶȣ�����12��12����
                             // D7-D4   : �˳��ƶ��ٶȣ�0-12�ֱ��ʾ�����������ƶ��ٶȣ�����12��12����
                             // D27-D8  : ͣ��ʱ�䣬�룬��Ϊ0xFFFFF������ͣ��
                             // D31-D28 : ��������0
  DWORD	Schedule;            // �����ŵĿ�ʼ����ʱ�䣬���ö�ʱ��0xFFFFFFFF
                             // D5-D0   : ��ʼ��
                             // D11-D6  : ������
                             // D16-D12 : ��ʼСʱ
                             // D21-D17 : ����Сʱ
                             // D24-D22 : ��������111
                             // D31-D25 : �ܶ�ʱ��D31��Ӧ���գ�D30-D25��Ӧ����-��һ
} ProgItemType;

typedef struct
{
  BYTE Type;                 // �ļ����� 0-����ͼƬ 1-����˫ɫͼƬ
  BYTE PicCount;             // ͼƬ����
  WORD PicHeight;            // ͼƬ�߶�
  WORD PicWidth;             // ͼƬ���
  WORD PicOffset;            // ��һ��ͼƬ���ļ��ڵ�ƫ�ƣ��ļ��ĵ�һ���ֽ�ƫ��Ϊ0��
  WORD LastPicH;             // ���һ��ͼƬ�߶�
  WORD LastPicW;             // ���һ��ͼƬ���
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
  BYTE NC;                   // ��������0
} ClockType;

// ϵͳ����״̬�ṹ
typedef struct
{
  BYTE  Ver[4];              // �汾��Ver[0]Ӳ�����ΰ汾��BCD�룬��0x10����1.0�����汾Ϊ�����ͣ��ΰ汾ΪPCB�汾
                             //       Ver[1]Ӳ�����ܸ���˵���룬��������0
                             //       ���������ֽ���ϵͳ��ʼ��ʱ���Ӳ�����ú���д
                             //       Ver[2],Ver[3]������汾��BCD�룬��ϵͳ��ʼ��ʱ����
  BYTE  RSFlag;              // D0    : �Ƿ���ϲ��Զ�·�� 0δ���� 1����
                             // D1    : LEDPwrSwitch �����Դ����״̬ 0 - �ϵ� 1 - ͨ��
                             // D2    : DS18B20�¶�оƬ����״̬ 0-������ 1-����
                             // D3    : DS3231ʱ��оƬ����״̬  0-������ 1-����
                             // D7-D4 : ��������0
  BYTE  BrightLevel;         // ���ƿ�ʵ����������ȵȼ� 0 - ���� 1..16 - 16���������ã��ֱ����1/16���ȵ�ȫ��
  BYTE  Brightness;          // ���ȴ������ɼ����ȵȼ�
  BYTE  Humidity;            // ʪ�ȴ������ɼ�ʪ��ֵ, 0 ~ 99
  signed short Temperature;  // �¶ȴ������ɼ��¶�ֵ, -55 ~ +125
  WORD  ChipTemp;            // ���ƿ��¶Ȳɼ�ֵ
  WORD  Analog1;             // ģ����1�ɼ�ֵ
  WORD  Analog2;             // ģ����2�ɼ�ֵ
  BYTE  NC0[4];              // ��������0
  BYTE  Clock[8];            // ʱ�ӣ�8���ֽڷֱ��Ӧ��0-59����0-59��ʱ0-23����1-31����1-12������0-6����0-99��һ�ֽ�δ��
  BYTE  PowerMode;           // ���������� 0:ǿ�й��� 1:ǿ�п��� 2:�Զ�������
  BYTE  NC1[11];             // ��������0
  DWORD StorgeTotalSize;     // �ⲿ�洢Flash������������λ���ֽ�
  DWORD StorgePicSize;       // ͼƬ�ļ�������������λ���ֽ�
  DWORD PicFileSize;         // ʵ��ʹ�õ�ͼƬ�ļ������ֽ������ɷ�����С����õ���ΪExFlash������С�ı���
  WORD  ProgGroup;           // ��ǰ���ŵĽ�Ŀ��������0-1023��
  BYTE  LoadedFonts;         // װ�صĿ����ֿ���
  BYTE  NC2;                 // �����ֽڣ���0
} RunningStateStru;

/*
 * ���ֽڱ����Range�̶�Ϊ32..255
 * Unicode��˫(��)�ֽڱ����Range��FontRange_t[]����
 */
typedef union
{
  struct                     // ��ӦUnicode����
  {
    WORD  CodeStart;	       // �������
    WORD  CodeEnd;           // �����յ�
  } Unicode;
  struct                     // ��Ӧ˫(��)�ֽڱ���
  {
    BYTE  Code1Start;	       // ��1�������㣬Ҳ���ڱ��ֽڱ����е��ֽڱ�������
    BYTE  Code1End;          // ��1������յ㣬Ҳ���ڱ��ֽڱ����е��ֽڱ�����յ�
    BYTE  Code2Start;	       // ��2��������
    BYTE  Code2End;          // ��2������յ�
  } DBCS;
} FontRange_t;

typedef struct               // 100�ֽ�
{
  DWORD FontDotAddr;         // �ֿ����洢��ַ��SPI FLASH��ַ��������Ϊҳ��ʼ��ַ��0xFFFFFFFF��ʾ����δ��
  WORD  Flag;                // ��ʶ��bit1..0:�ַ���������, 0:���ֽڱ���(ASCII, ISO8859) 1:Unicode 2:˫(��)�ֽڱ���(GB2312, BIG5) ����λ������0
  BYTE  FontWidth;           // �����ȣ�0xFF��Ч
  BYTE  FontHeight;	         // ����߶ȣ�0xFF��Ч
  WORD  CharBytes;           // ÿ�ַ��ֽ���
  WORD  CharCount;           // �ֿ����ַ�����������ÿ�ַ��ֽ�����Ϊ�ֿ�����С
  BYTE  RangeCount;          // ���������������֧��8��Range
  BYTE  RangeCountH;         // ����ַ���ʵ���ַ����Ϊ�����ȵ�һ�룩������������
                             // �����ֿ�ɰ�����Ǻ�ȫ�����ֿ�ȵ��ַ�������ַ��洢���ֿ��ǰ�棬������ȫ���ַ�
  BYTE  NC[6];               // ��������0
  char  Name[16];            // �ֿ����ƣ�����ʹ�������������ֿ⣬���ַ�ֻ��ʹ��ASCII�룬��ʽΪ�� songti-16x16
  FontRange_t Range[16];     // �ֿ�������ṹ�����֧��16��Range
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
