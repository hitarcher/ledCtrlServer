#pragma once
#include "winsock.h"
#include <windows.h>

//ȱʡ���ݰ���С
#define VSD_DEFAULT_PKP_LENGTH     512

//IP��ַ��MAC��ַ���ȶ���
#define VSD_IP_ADDRESS_LENGTH      4
#define VSD_ETHER_ADDRESS_LENGTH   6

//ͨѶ�豸����
#define VSD_DEVICE_TYPE_COM    0  //����ͨѶ
#define VSD_DEVICE_TYPE_UDP    1  //����ͨѶ
#define VSD_DEVICE_TYPE_485    2  //485ͨѶ

//���ڻ���485ͨѶʹ�õ�ͨѶ�ٶ�(������)
#define VSD_SBR_57600          0
#define VSD_SBR_38400          1
#define VSD_SBR_19200          2
#define VSD_SBR_9600           3

//�Ƿ�ȴ���λ��Ӧ��ֱ�ӷ�����������
#define VSD_NOTIFY_NONE        1
//�Ƿ�������ʽ������ȵ�������ɻ��߳�ʱ���ŷ��أ�������������
#define VSD_NOTIFY_BLOCK       2
//�Ƿ񽫷��ͽ����Windows������Ϣ��ʽ�͵����õ�Ӧ��
#define VSD_NOTIFY_EVENT       4
//ʹ��һ�����ض˿ڣ��Ͷ��Ŀ��IPͨѶ
#define VSD_NOTIFY_MULTI       8

#define VSD_R_DEVICE_READY     0
#define VSD_R_DEVICE_INVALID   -1
#define VSD_R_DEVICE_BUSY      -2
#define VSD_R_FONTSET_INVALID  -3
#define VSD_R_DLL_INIT_IVALID  -4
#define VSD_R_IGNORE_RESPOND   -5

//Chapter��Leaf�У�����ʱ�����
#define VSD_WAIT_USE_TIME      0  //����ָ����ʱ�䳤�Ȳ��ţ���ʱ����е���һ��
#define VSD_WAIT_CHILD         1  //�ȴ�����Ŀ�Ĳ��ţ��������ָ����ʱ�䳤�ȣ�������Ŀ��û�в��꣬��ȴ�����

#define VSD_V_FALSE            0
#define VSD_V_TRUE             1

//��ʾ����ɫ����
#define VSD_COLOR_MODE_MONO              1  //��ɫ
#define VSD_COLOR_MODE_DOUBLE            2  //˫ɫ
#define VSD_COLOR_MODE_THREE             3  //�޻Ҷ�ȫ��
#define VSD_COLOR_MODE_FULLCOLOR         4  //ȫ��

//��ʾ��������
#define VSD_ROOT_UPDATE            0x13  //������λ������
#define VSD_ROOT_FONTSET           0x14  //�����ֿ�
#define VSD_ROOT_PLAY              0x21  //��Ŀ���ݣ����浽RAM�����綪ʧ
#define VSD_ROOT_DOWNLOAD          0x22  //��Ŀ���ݣ����浽Flash
#define VSD_ROOT_PLAY_CHAPTER      0x23  //������߸���ĳһ��Ŀ
#define VSD_ROOT_PLAY_REGION       0x25  //������߸���ĳһ����
#define VSD_ROOT_PLAY_LEAF         0x27  //������߸���ĳһҳ��
#define VSD_ROOT_PLAY_OBJECT       0x29  //������߸���ĳһ����
		
#define VSD_ACTMODE_INSERT         0  //�������
#define VSD_ACTMODE_REPLACE        1  //�滻����

//RAM��Ŀ����
#define VSD_ROOT_SURVIVE_ALWAYS    -1

//Windows�������Ͷ���
#define VSD_WFS_NONE               0x0   //��ͨ��ʽ
#define VSD_WFS_BOLD               0x01  //����
#define VSD_WFS_ITALIC             0x02  //б��
#define VSD_WFS_UNDERLINE          0x04  //�»���
#define VSD_WFS_STRIKEOUT          0x08  //ɾ����

//�����Ƴ���
#define VSD_FLOW_NONE          0
#define VSD_FLOW_RTS_CTS       1

//��λ��Ӧ���ʶ
#define VSD_LM_RX_COMPLETE         1
#define VSD_LM_TX_COMPLETE         2
#define VSD_LM_RESPOND             3
#define VSD_LM_TIMEOUT             4
#define VSD_LM_NOTIFY              5
#define VSD_LM_PARAM               6
#define VSD_LM_TX_PROGRESS         7
#define VSD_LM_RX_PROGRESS         8
#define VSD_RESULT_FLASH           0xff

//��Դ����״̬
#define VSD_LED_POWER_ON       1
#define VSD_LED_POWER_OFF      0

//�������ִ�С
#define VSD_FONT_SET_16        0      //16�����ַ�
#define VSD_FONT_SET_24        1      //24�����ַ�
  
//����ʱ������ʱtype����
#define VSD_CT_COUNTUP         0      //����ʱ
#define VSD_CT_COUNTDOWN       1      //����ʱ
//����ʱ������ʱformat����
#define VSD_CF_HNS             0      //ʱ���루���ֵ��
#define VSD_CF_HN              1      //ʱ�֣����ֵ��
#define VSD_CF_NS              2      //���루���ֵ��
#define VSD_CF_H               3      //ʱ�����ֵ��
#define VSD_CF_N               4      //�֣����ֵ��
#define VSD_CF_S               5      //�루���ֵ��
#define VSD_CF_DAY             6      //����������������
#define VSD_CF_HOUR            7      //Сʱ��������������
#define VSD_CF_MINUTE          8      //������������������
#define VSD_CF_SECOND          9      //����������������

//ģ��ʱ�ӱ߿���״
#define VSD_SHAPE_RECTANGLE    0      //����
#define VSD_SHAPE_ROUNDRECT    1      //Բ�Ƿ���
#define VSD_SHAPE_CIRCLE       2      //Բ��

//������붨��
#define VSD_PKC_RESPOND               3
#define VSD_PKC_QUERY                 4
#define VSD_PKC_OVERFLOW              5
#define VSD_PKC_ADJUST_TIME           6
#define VSD_PKC_GET_PARAM             7
#define VSD_PKC_SET_PARAM             8
#define VSD_PKC_GET_POWER             9
#define VSD_PKC_SET_POWER             10
#define VSD_PKC_GET_BRIGHT            11
#define VSD_PKC_SET_BRIGHT            12
#define VSD_PKC_COM_TRANSFER          21
#define VSD_PKC_GET_POWER_SCHEDULE    60
#define VSD_PKC_SET_POWER_SCHEDULE    61
#define VSD_PKC_GET_BRIGHT_SCHEDULE   62
#define VSD_PKC_SET_BRIGHT_SCHEDULE   63
#define VSD_PKC_SET_CURRENT_CHAPTER   66
#define VSD_PKC_GET_CURRENT_CHAPTER   67
#define VSD_PKC_NOTIFY                100
#define VSD_PKC_MODIFY_IP             7654
#define VSD_PKC_MODIFY_MAC            7655
#define VSD_NOTIFY_ROOT_DOWNLOAD      0x00010003  //����Flash���Ž�Ŀ
#define VSD_NOTIFY_SET_PARAM          0x00010004  //���ò���
#define VSD_NOTIFY_BUFFER_LEN		  512

typedef struct VSD_TIMESTAMP
{
  long   time;
  long   date;
}VSD_TTimeStamp, *VSD_PTimeStamp;

typedef struct VSD_DEVICE_PARAM
{
  WORD  devType;
  WORD  comSpeed;
  WORD  comPort;
  WORD  comFlow;
  WORD  locPort;
  WORD  rmtPort;
  WORD  srcAddr;
  WORD  dstAddr;
  char  rmtHost[16];
  DWORD txTimeo;   //���ͺ�ȴ�Ӧ��ʱ�� ====��ʱʱ��ӦΪtxTimeo*txRepeat
  DWORD txRepeat;  //ʧ���ط�����
  DWORD txMovewin; //��������
  DWORD key;
  long  pkpLength; //���ݰ���С
}VSD_TDeviceParam, *VSD_PDeviceParam;

typedef struct VSD_SENDER_PARAM{
  VSD_TDeviceParam devParam;
  long  wmHandle;
  long  wmMessage;
  long  wmLParam;
  long  notifyMode;
}VSD_TSenderParam, *VSD_PSenderParam;

typedef struct VSD_NOTIFY_PARAM{
  WORD  Notify;
  WORD  Command;
  long  Result;
  long  Status;
  VSD_TSenderParam Param;
  BYTE  Buffer[VSD_NOTIFY_BUFFER_LEN];
  DWORD Size;
}VSD_TNotifyParam, *VSD_PNotifyParam;

typedef struct VSD_POWER_SCHEDULE{
  DWORD Enabled;
  DWORD Mode;
  VSD_TTimeStamp OpenTime[21];
  VSD_TTimeStamp CloseTime[21];
  DWORD Checksum;
}VSD_TPowerSchedule, *VSD_PPowerSchedule;

typedef struct VSD_BRIGHT_SCHEDULE{
  DWORD Enabled;
  BYTE  Bright[24];
  DWORD Checksum;
}VSD_TBrightSchedule, *VSD_PBrightSchedule;

typedef struct VSD_DEVINFO{
	char  dev_name[32];  //�豸����
	DWORD dev_id;        //�豸��ʶ
	DWORD dev_ip;        //�豸IP��ַ
	WORD  dev_addr;      //�豸��ַ
	WORD  dev_port;      //�豸�˿�
	DWORD reserved[5];   //ϵͳ����
}VSD_TDevInfo, *VSD_PDevInfo;

typedef struct VSD_DEVICEREPORT{
	VSD_TDevInfo devinfo;    //�豸��Ϣ
	double   timeupdate; //���ˢ��ʱ��
}VSD_TDeviceReport, *VSD_PDeviceReport;

/************************************************************************/
/* ���߿��ƿ��б���ؽӿں���                                           */
/************************************************************************/
//��̬���ӿ��ʼ��
typedef long (_stdcall *_LED_Startup)(void);

//��̬���ӿ�����
typedef long (_stdcall *_LED_Cleanup)(void);
//�������ƿ����߼�������
//  serverindex ���ƿ����߼���������(�����ڶ��socket udp�˿ڼ���)
//  localport ���ض˿�
typedef long (_stdcall *_LED_Report_CreateServer)(long serverindex, long localport);

//ɾ�����ƿ����߼�������
//  serverindex ���ƿ����߼���������
typedef void (_stdcall *_LED_Report_RemoveServer)(long serverindex);

//ɾ��ȫ�����ƿ����߼�������
typedef void (_stdcall *_LED_Report_RemoveAllServer)(void);

//��ÿ��ƿ������б�
//�����ȴ������ƿ����߼������񣬼�����LED_Report_CreateServer��ʹ�ã����򷵻�ֵ��Ч
//  serverindex ���ƿ����߼���������
//  plist ��������б���û��ⲿ��������
//        ��������(NULL/0)�����������̬���ӿ��ڲ��Ļ�������������������Ľӿ�ȡ����ϸ��Ϣ
//  count ����ȡ����
//--����ֵ-- С��0��ʾʧ��(δ���������߼�������)�����ڵ���0��ʾ���ߵĿ��ƿ�����
typedef long (_stdcall *_LED_Report_GetOnlineList)(long serverindex, void* plist, long count);

//���ĳ�����߿��ƿ����ϱ����ƿ�����
//�����ȴ������ƿ����߼������񣬼�����LED_Report_CreateServer��ʹ�ã����򷵻�ֵ��Ч
//  serverindex ���ƿ����߼���������
//  itemindex �ü�������������б��У����߿��ƿ��ı��
//--����ֵ-- ���߿��ƿ����ϱ����ƿ�����
typedef char* (_stdcall *_LED_Report_GetOnlineItemName)(long serverindex, long itemindex);

//���ĳ�����߿��ƿ����ϱ����ƿ�IP��ַ
//�����ȴ������ƿ����߼������񣬼�����LED_Report_CreateServer��ʹ�ã����򷵻�ֵ��Ч
//  serverindex ���ƿ����߼���������
//  itemindex �ü�������������б��У����߿��ƿ��ı��
//--����ֵ-- ���߿��ƿ���IP��ַ
typedef char* (_stdcall *_LED_Report_GetOnlineItemHost)(long serverindex, long itemindex);

//���ĳ�����߿��ƿ����ϱ����ƿ�Զ��UDP�˿ں�
//�����ȴ������ƿ����߼������񣬼�����LED_Report_CreateServer��ʹ�ã����򷵻�ֵ��Ч
//  serverindex ���ƿ����߼���������
//  itemindex �ü�������������б��У����߿��ƿ��ı��
//--����ֵ-- ���߿��ƿ���Զ��UDP�˿ں�
typedef long (_stdcall *_LED_Report_GetOnlineItemPort)(long serverindex, long itemindex);

//���ĳ�����߿��ƿ����ϱ����ƿ���ַ
//�����ȴ������ƿ����߼������񣬼�����LED_Report_CreateServer��ʹ�ã����򷵻�ֵ��Ч
//  serverindex ���ƿ����߼���������
//  itemindex �ü�������������б��У����߿��ƿ��ı��
//--����ֵ-- ���߿��ƿ���Ӳ����ַ
typedef long (_stdcall *_LED_Report_GetOnlineItemAddr)(long serverindex, long itemindex);

/************************************************************************/
/* ��дͨѶ�����ӿں���������һЩ�޷����ݽṹ���ָ��Ŀ�������������   */
/************************************************************************/

//��д����ͨѶ������������ʱʹ��
//  index ����������
//  localport ���ض˿�
//  host ���ƿ�IP��ַ
//  remoteport Զ�̶˿�
//  address ���ƿ���ַ
//  notifymode ͨѶͬ���첽ģʽ
//  wmhandle ������Ϣ������
//  wmmessage ������Ϣ����Ϣ��
//--����ֵ-- С��0��ʾʧ�ܣ����ڵ���0��ʾ������id��
typedef long (_stdcall *_LED_UDP_SenderParam)(long index, long localport, char* host, long remoteport, long address, long notifymode, long wmhandle, long wmmessage);

//��д����ͨѶ������������ʱʹ��
//  index ����������
//  comport ���ں�
//  baudrate ������
//  address ���ƿ���ַ
//  notifymode ͨѶͬ���첽ģʽ
//  wmhandle ������Ϣ������
//  wmmessage ������Ϣ����Ϣ��
//--����ֵ-- С��0��ʾʧ�ܣ����ڵ���0��ʾ������id��
typedef long (_stdcall *_LED_COM_SenderParam)(long index, long comport, long baudrate, long address, long notifymode, long wmhandle, long wmmessage);

//��д����ͨѶ������������ʱʹ��
//  index ����������
//  localport ���ض˿�
//  serverindex ���߼���������
//  name ���ƿ�����(���ƿ��ϱ���������)
//  notifymode ͨѶͬ���첽ģʽ
//  wmhandle ������Ϣ������
//  wmmessage ������Ϣ����Ϣ��
//--����ֵ-- С��0��ʾʧ�ܣ����ڵ���0��ʾ������id��
typedef long (_stdcall *_LED_UDP_SenderParam_ByReportName)(long index, long localport, long serverindex, char* name, long notifymode, long wmhandle, long wmmessage);
//Ԥ����ʾ����
typedef void (_stdcall *_LED_Preview)(long index, long width, long height, char* previewfile);
//��λ���ƿ���Ŀ���ţ�������ʾ���ƿ�Flash�д洢�Ľ�Ŀ
typedef long (_stdcall *_LED_ResetDisplay)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_ResetDisplay2)(long senderparam_index);
//У��ʱ�䣬�Ե�ǰ�������ϵͳʱ��У�����ƿ���ʱ��
typedef long (_stdcall *_LED_AdjustTime)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_AdjustTime2)(long senderparam_index);
//У��ʱ����չ����ָ����ʱ��У�����ƿ���ʱ��
typedef long (_stdcall *_LED_AdjustTimeEx)(VSD_PSenderParam param, LPSYSTEMTIME time);
typedef long (_stdcall *_LED_AdjustTimeEx2)(long senderparam_index, LPSYSTEMTIME time);
//���õ�ǰ��ʾ�Ľ�Ŀ
typedef long (_stdcall *_LED_SetCurChapter)(VSD_PSenderParam param, long value);
typedef long (_stdcall *_LED_SetCurChapter2)(long senderparam_index, long value);
//���õ�ǰ��ʾ�Ľ�Ŀ
typedef long (_stdcall *_LED_GetCurChapter)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_GetCurChapter2)(long senderparam_index);
//���ÿ��ƿ���Դ value=LED_POWER_ON��ʾ������Դ value=LED_POWER_OFF��ʾ�رյ�Դ
typedef long (_stdcall *_LED_SetPower)(VSD_PSenderParam param, long value);
typedef long (_stdcall *_LED_SetPower2)(long senderparam_index, long value);
//����ת������
typedef long (_stdcall *_LED_ComTransfer)(VSD_PSenderParam param, BYTE* buffer, DWORD size);
typedef long (_stdcall *_LED_ComTransfer2)(long senderparam_index, BYTE* buffer, DWORD size);
//��ȡ���ƿ���Դ״̬
typedef long (_stdcall *_LED_GetPower)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_GetPower2)(long senderparam_index);
//���ÿ��ƿ����� valueȡֵ��Χ0-7
typedef long (_stdcall *_LED_SetBright)(VSD_PSenderParam param, long value);
typedef long (_stdcall *_LED_SetBright2)(long senderparam_index, long value);
//��ȡ���ƿ�����
typedef long (_stdcall *_LED_GetBright)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_GetBright2)(long senderparam_index);
//���ÿ��ƿ��Ķ�ʱ�������ƻ�
typedef long (_stdcall *_LED_SetPowerSchedule)(VSD_PSenderParam param, VSD_PPowerSchedule value);
typedef long (_stdcall *_LED_SetPowerSchedule2)(long senderparam_index, VSD_PPowerSchedule value);
//��ȡ���ƿ��Ķ�ʱ�������ƻ�
typedef long (_stdcall *_LED_GetPowerSchedule)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_GetPowerSchedule2)(long senderparam_index);
//���ÿ��ƿ��Ķ�ʱ���ȵ��ڼƻ�
typedef long (_stdcall *_LED_SetBrightSchedule)(VSD_PSenderParam param, VSD_PBrightSchedule value);
typedef long (_stdcall *_LED_SetBrightSchedule2)(long senderparam_index, VSD_PBrightSchedule value); 
//��ȡ���ƿ��Ķ�ʱ���ȵ��ڼƻ�
typedef long (_stdcall *_LED_GetBrightSchedule)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_GetBrightSchedule2)(long senderparam_index);
//���ͽ�Ŀ���� indexΪMakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�����ķ���ֵ
typedef long (_stdcall *_LED_SendToScreen)(VSD_PSenderParam param, long index);
typedef long (_stdcall *_LED_SendToScreen2)(long senderparam_index, long index);
 
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // ���ڶԿ��ƿ�����һЩ��������
 // ����Ϊ����ȡ���ƿ�����--��ȡ��������--
 //                       --�޸ĸ�������--���޸ĺ�Ĳ���������ƿ�
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 //��ȡ���ƿ�����
typedef long (_stdcall *_LED_Cache_GetBoardParam)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_Cache_GetBoardParam2)(long senderparam_index);
 //��ȡ��������
typedef long (_stdcall *_LED_Cache_GetBoardParam_SaveToFile)(char* filename);  //�����ƿ��ض��Ĳ�����д���ļ�
typedef char* (_stdcall *_LED_Cache_GetBoardParam_IP)(void);
typedef char* (_stdcall *_LED_Cache_GetBoardParam_Mac)(void);
typedef long (_stdcall *_LED_Cache_GetBoardParam_Addr)(void);
typedef long (_stdcall *_LED_Cache_GetBoardParam_Width)(void);
typedef long (_stdcall *_LED_Cache_GetBoardParam_Height)(void);
typedef long (_stdcall *_LED_Cache_GetBoardParam_Brightness)(void);
 //�޸ĸ�������
typedef long (_stdcall *_LED_Cache_SetBoardParam_LoadFromFile)(char* filename);  //���ļ���ȡ���������浽��̬���ӿ��У��Թ�д�뵽���ƿ�
typedef void (_stdcall *_LED_Cache_SetBoardParam_IP)(char* value);
typedef void (_stdcall *_LED_Cache_SetBoardParam_Mac)(char* value);
typedef void (_stdcall *_LED_Cache_SetBoardParam_Addr)(long value);
typedef void (_stdcall *_LED_Cache_SetBoardParam_Width)(long value);
typedef void (_stdcall *_LED_Cache_SetBoardParam_Height)(long value);
typedef void (_stdcall *_LED_Cache_SetBoardParam_Brightness)(long value);
 //���޸ĺ�Ĳ���������ƿ�
typedef long (_stdcall *_LED_Cache_SetBoardParam)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_Cache_SetBoardParam2)(long senderparam_index);

 //��ȡ���ƿ�Ӧ����������
typedef long (_stdcall *_LED_GetNotifyParam)(VSD_PNotifyParam notify, long index);
 
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 //��Ŀ������֯��ʽ
 //  ROOT
 //   |
 //   |---Chapter(��Ŀ)
 //   |      |
 //   |      |---Region(����)
 //   |      |     |
 //   |      |     |---Leaf(ҳ��)
 //   |      |     |    |
 //   |      |     |    |---Object(����[���֡�ʱ�ӡ�ͼƬ��])
 //   |      |     |    |
 //   |      |     |    |---Object(����[���֡�ʱ�ӡ�ͼƬ��])
 //   |      |     |    |
 //   |      |     |    |   ......
 //   |      |     |    |
 //   |      |     |
 //   |      |     |---Leaf(ҳ��)
 //   |      |     |
 //   |      |     |   ......
 //   |      |     |
 //   |      |
 //   |      |---Region(����)
 //   |      |
 //   |      |   ......
 //   |      |
 //   |---Chapter(��Ŀ)
 //   |
 //   |   ......
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 //���ɲ������ݣ���VisionShow����༭��Vsq�ļ����룬������Ҫ�·��Ľ�Ŀ���ݣ�
 //  RootType Ϊ�������ͣ�=ROOT_PLAY��ʾ���¿��ƿ�RAM�еĽ�Ŀ(���綪ʧ)��=ROOT_DOWNLOAD��ʾ���¿��ƿ�Flash�еĽ�Ŀ(���粻��ʧ)
 //  ColorMode Ϊ��ɫģʽ��ȡֵΪCOLOR_MODE_MONO����COLOR
 //  survive ΪRAM��Ŀ����ʱ�䣬��RootType=ROOT_PLAYʱ��Ч����RAM��Ŀ���Ŵﵽʱ��󣬻ָ���ʾFLASH�еĽ�Ŀ
 //  filename ��VisionShow����༭�Ľ�Ŀ�ļ�
typedef long (_stdcall *_MakeFromVsqFile)(char* filename, long RootType, long ColorMode, long survive);
 
 //���ɲ�������
 //  RootType Ϊ�������ͣ�=ROOT_PLAY��ʾ���¿��ƿ�RAM�еĽ�Ŀ(���綪ʧ)��=ROOT_DOWNLOAD��ʾ���¿��ƿ�Flash�еĽ�Ŀ(���粻��ʧ)
 //  ColorMode Ϊ��ɫģʽ��ȡֵΪCOLOR_MODE_MONO����COLOR
 //  survive ΪRAM��Ŀ����ʱ�䣬��RootType=ROOT_PLAYʱ��Ч����RAM��Ŀ���Ŵﵽʱ��󣬻ָ���ʾFLASH�еĽ�Ŀ
typedef long (_stdcall *_MakeRoot)(long RootType, long ColorMode, long survive);
 
 //���ɽ�Ŀ���ݣ�������Ҫ����[AddRegion]->[AddLeaf]->[AddObject]->[AddWindows/AddDateTime��]
 //  RootType ������ΪROOT_PLAY_CHAPTER
 //  ActionMode ������Ϊ0
 //  ChapterIndex Ҫ���µĽ�Ŀ���
 //  ColorMode ͬMakeRoot�еĶ���
 //  time ���ŵ�ʱ�䳤��
 //  wait �ȴ�ģʽ��=WAIT_CHILD����ʾ���ﵽ����ʱ�䳤��ʱ����Ҫ�ȴ��ӽ�Ŀ����������л���
 //                 =WAIT_USE_TIME����ʾ���ﵽ����ʱ�䳤��ʱ�����ȴ��ӽ�Ŀ������ɣ�ֱ���л���һ��Ŀ
typedef long (_stdcall *_MakeChapter)(long RootType, long ActionMode, long ChapterIndex, long ColorMode, DWORD time, WORD wait);
 
 //���ɷ�����������Ҫ����[AddLeaf]->[AddObject]->[AddWindows/AddDateTime��]
 //  RootType ������ΪROOT_PLAY_REGION
 //  ActionMode ������Ϊ0
 //  ChapterIndex Ҫ���µĽ�Ŀ���
 //  RegionIndex Ҫ���µķ������
 //  ColorMode ͬMakeRoot�еĶ���
 //  left��top��width��height ���ϡ���ȡ��߶�
 //  border ��ˮ�߿�
typedef long (_stdcall *_MakeRegion)(long RootType, long ActionMode, long ChapterIndex, long RegionIndex, long ColorMode, long left, long top, long width, long height, long border);
 
 //����ҳ�棬������Ҫ����[AddObject]->[AddWindows/AddDateTime��]
 //  RootType ������ΪROOT_PLAY_LEAF
 //  ActionMode ������Ϊ0
 //  ChapterIndex Ҫ���µĽ�Ŀ���
 //  RegionIndex Ҫ���µķ������
 //  LeafIndex Ҫ���µ�ҳ�����
 //  ColorMode ͬMakeRoot�еĶ���
 //  time ���ŵ�ʱ�䳤��
 //  wait �ȴ�ģʽ��=WAIT_CHILD����ʾ���ﵽ����ʱ�䳤��ʱ����Ҫ�ȴ��ӽ�Ŀ����������л���
 //                 =WAIT_USE_TIME����ʾ���ﵽ����ʱ�䳤��ʱ�����ȴ��ӽ�Ŀ������ɣ�ֱ���л���һҳ��
typedef long (_stdcall *_MakeLeaf)(long RootType, long ActionMode, long ChapterIndex, long RegionIndex, long LeafIndex, long ColorMode, DWORD time, WORD wait);
 
 //���ɲ��Ŷ��󣬺�����Ҫ����[AddWindows/AddDateTime��]
 //  RootType ������ΪROOT_PLAY_OBJECT
 //  ActionMode ������Ϊ0
 //  ChapterIndex Ҫ���µĽ�Ŀ���
 //  RegionIndex Ҫ���µķ������
 //  LeafIndex Ҫ���µ�ҳ�����
 //  ObjectIndex Ҫ���µĶ������
 //  ColorMode ͬMakeRoot�еĶ���
typedef long (_stdcall *_MakeObject)(long RootType, long ActionMode, long ChapterIndex, long RegionIndex, long LeafIndex, long ObjectIndex, long ColorMode);
 
 //��ӽ�Ŀ
 //  num ��Ŀ���ݻ�������ţ���MakeRoot�ķ���ֵ
 //  time ���ŵ�ʱ�䳤��
 //  wait �ȴ�ģʽ��=WAIT_CHILD����ʾ���ﵽ����ʱ�䳤��ʱ����Ҫ�ȴ��ӽ�Ŀ����������л���
 //                 =WAIT_USE_TIME����ʾ���ﵽ����ʱ�䳤��ʱ�����ȴ��ӽ�Ŀ������ɣ�ֱ���л���һ��Ŀ
typedef long (_stdcall *_AddChapter)(WORD num, DWORD time, WORD wait); //timeΪ����
 //  priority ���ȼ�0-2
 //  kind ���żƻ�ģʽ  =0ʼ�ղ���  =1��ÿ�����첥��  =2����ʼʱ�䲥��
 //  week �ܶ���  bit0��bit6����ʾ���յ����� ��kind=1ʱ��Ч
 //  fromtime ��ʼʱ��  ��kind=1ʱ��ֻʱ�䲿����Ч����kind=2ʱ������ʱ��ȫ��Ч
 //  totime ����ʱ��  ��kind=1ʱ��ֻʱ�䲿����Ч����kind=2ʱ������ʱ��ȫ��Ч
typedef long (_stdcall *_AddChapterEx2)(WORD num, DWORD time, WORD wait, WORD priority, WORD kind, WORD week, char* fromtime, char* totime); //timeΪ����
 
 //��ӷ���
 //  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter�ķ���ֵ
 //  left��top��width��height ���ϡ���ȡ��߶�
 //  border ��ˮ�߿�
typedef long (_stdcall *_AddRegion)(WORD num, long left, long top, long width, long height, long border);
 
 //���ҳ��
 //  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion�ķ���ֵ
 //  time ���ŵ�ʱ�䳤��
 //  wait �ȴ�ģʽ��=WAIT_CHILD����ʾ���ﵽ����ʱ�䳤��ʱ����Ҫ�ȴ��ӽ�Ŀ����������л���
 //                 =WAIT_USE_TIME����ʾ���ﵽ����ʱ�䳤��ʱ�����ȴ��ӽ�Ŀ������ɣ�ֱ���л���һҳ��
typedef long (_stdcall *_AddLeaf)(WORD num, DWORD time, WORD wait); //timeΪ����
 
 //�������ʱ����ʾ
 //  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
 //  left��top��width��height ���ϡ���ȡ��߶�
 //  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
 //  border ��ˮ�߿�(δʵ��)
 //  fontname ��������
 //  fontsize �����С
 //  fontcolor ������ɫ
 //  fontstyle ������ʽ ������=WFS_BOLD��ʾ���壻=WFS_ITALIC��ʾб�壻=WFS_BOLD+WFS_ITALIC��ʾ��б��
 //  year_offset ��ƫ����
 //  month_offset ��ƫ����
 //  day_offset ��ƫ����
 //  sec_offset ��ƫ����
 //  format ��ʾ��ʽ 
 //      #y��ʾ�� #m��ʾ�� #d��ʾ�� #h��ʾʱ #n��ʾ�� #s��ʾ�� #w��ʾ���� #c��ʾũ��
 //      ������ format="#y��#m��#d�� #hʱ#n��#s�� ����#w ũ��#c"ʱ����ʾΪ"2009��06��27�� 12ʱ38��45�� ������ ũ�����³���"
typedef long (_stdcall *_AddDateTime)(WORD num, long left, long top, long width, long height, long transparent, long border,
 		char* fontname, long fontsize, long fontcolor, long fontstyle, 
         long year_offset, long month_offset, long day_offset, long sec_offset, char* format);
 
 //�����սʱ����ʾ
 //  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
 //  left��top��width��height ���ϡ���ȡ��߶�
 //  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
 //  border ��ˮ�߿�(δʵ��)
 //  fontname ��������
 //  fontsize �����С
 //  fontcolor ������ɫ
 //  fontstyle ������ʽ ������=WFS_BOLD��ʾ���壻=WFS_ITALIC��ʾб�壻=WFS_BOLD+WFS_ITALIC��ʾ��б��
 //  format ��ʾ��ʽ 
 //      #y��ʾ�� #m��ʾ�� #d��ʾ�� #h��ʾʱ #n��ʾ�� #s��ʾ��
 //  basetime ��սʱ��
 //  fromtime ��ʼʱ��
 //  totime ����ʱ��
 //  step ��ʱ����ʱ�䲽�������ٺ�����һ�룩
typedef long (_stdcall *_AddCampaignEx)(WORD num, long left, long top, long width, long height, long transparent, long border, 
 		char* fontname, long fontsize, long fontcolor, long fontstyle, 
 		char* format, VSD_PTimeStamp basetime, VSD_PTimeStamp fromtime, VSD_PTimeStamp totime, long step);
 
 //���ģ��ʱ��
 //  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
 //  left��top��width��height ���ϡ���ȡ��߶�
 //  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
 //  border ��ˮ�߿�(δʵ��)
 //  offset ��ƫ����
 //  bkcolor: ������ɫ
 //  framecolor: �����ɫ
 //  framewidth: �����ɫ
 //  frameshape: �����״ =0��ʾ�����Σ�=1��ʾԲ�Ƿ��Σ�=2��ʾԲ��
 //  dotradius: �̶Ⱦ���������İ뾶
 //  adotwidth: 0369��̶ȴ�С
 //  adotcolor: 0369��̶���ɫ
 //  bdotwidth: ������̶ȴ�С
 //  bdotcolor: ������̶���ɫ
 //  hourwidth: ʱ���ϸ
 //  hourcolor: ʱ����ɫ
 //  minutewidth: �����ϸ
 //  minutecolor: ������ɫ
 //  secondwidth: �����ϸ
 //  secondcolor: ������ɫ
typedef long (_stdcall *_AddClock)(WORD num, long left, long top, long width, long height, long transparent, long border, long offset,
 		DWORD bkcolor, DWORD framecolor, DWORD framewidth, long frameshape,
 		long dotradius, long adotwidth, DWORD adotcolor, long bdotwidth, DWORD bdotcolor,
         long hourwidth, DWORD hourcolor, long minutewidth, DWORD minutecolor, long secondwidth, DWORD secondcolor);
 
 //��Ӷ���
 //  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
 //  left��top��width��height ���ϡ���ȡ��߶�
 //  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
 //  border ��ˮ�߿�(δʵ��)
 //  filename avi�ļ���
 //  stretch: ͼ���Ƿ���������Ӧ�����С
typedef long (_stdcall *_AddMovie)(WORD num, long left, long top, long width, long height, long transparent, long border, char* filename, long stretch);
 
 //���ͼƬ�鲥��
 //  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
 //  left��top��width��height ���ϡ���ȡ��߶�
 //  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
 //  border ��ˮ�߿�(δʵ��)
typedef long (_stdcall *_AddWindows)(WORD num, long left, long top, long width, long height, long transparent, long border);
 
 //���ͼƬ�����ͼƬ �˺���Ҫ����AddWindows�������
 //  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
 //  dc ԴͼƬDC���
 //  width ͼƬ���
 //  height ͼƬ�߶�
 //  inmethod ���뷽ʽ(�������б�˵��)
 //  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  outmethod ������ʽ(�������б�˵��)
 //  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stopmethod ͣ����ʽ(�������б�˵��)
 //  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stoptime ͣ��ʱ��(��λ����)
typedef long (_stdcall *_AddChildWindow)(WORD num, HDC dc, long width, long height, long alignment, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime��λΪ��
 
 //���ͼƬ�����ͼƬ �˺���Ҫ����AddWindows�������
 //  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
 //  filename ͼƬ�ļ���
 //  inmethod ���뷽ʽ(�������б�˵��)
 //  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  outmethod ������ʽ(�������б�˵��)
 //  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stopmethod ͣ����ʽ(�������б�˵��)
 //  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stoptime ͣ��ʱ��(��λ����)
typedef long (_stdcall *_AddChildPicture)(WORD num, char* filename, long alignment, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime��λΪ��
 
 //���ͼƬ�����ͼƬ �˺���Ҫ����AddWindows�������
 //  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
 //  str �����ַ���
 //  fontname ��������
 //  fontsize �����С
 //  fontcolor ������ɫ
 //  fontstyle ������ʽ ������=WFS_BOLD��ʾ���壻=WFS_ITALIC��ʾб�壻=WFS_BOLD+WFS_ITALIC��ʾ��б��
 //  wordwrap �Ƿ��Զ����� =1�Զ����У�=0���Զ�����
 //  inmethod ���뷽ʽ(�������б�˵��)
 //  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  outmethod ������ʽ(�������б�˵��)
 //  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stopmethod ͣ����ʽ(�������б�˵��)
 //  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stoptime ͣ��ʱ��(��λ����)
typedef long (_stdcall *_AddChildText)(WORD num, char* str, char* fontname, long fontsize, long fontcolor, long fontstyle, long wordwrap, long alignment, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime��λΪ����
 
 //������������鲥��
 //  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
 //  left��top��width��height ���ϡ���ȡ��߶�
 //  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
 //  border ��ˮ�߿�(δʵ��)
typedef long (_stdcall *_AddStrings)(WORD num, long left, long top, long width, long height, long transparent, long border);
 
 //���ͼƬ�����ͼƬ �˺���Ҫ����AddWindows�������
 //  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
 //  str �����ַ���
 //  fontset �ֿ� =FONTSET_16P��ʾ16�����ֿ⣻=FONTSET_24P��ʾ24�����ֿ�
 //  color ��ɫ
 //  inmethod ���뷽ʽ(�������б�˵��)
 //  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  outmethod ������ʽ(�������б�˵��)
 //  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stopmethod ͣ����ʽ(�������б�˵��)
 //  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stoptime ͣ��ʱ��(��λ����)
typedef long (_stdcall *_AddChildString)(WORD num, char* str, long fontset, long color, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime��λΪ����
 
 //���ͼƬ���󲥷�
 //  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
 //  left��top��width��height ���ϡ���ȡ��߶�
 //  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
 //  border ��ˮ�߿�(δʵ��)
 //  dc ԴͼƬDC���
 //  src_width ͼƬ���
 //  src_height ͼƬ�߶�
 //  inmethod ���뷽ʽ(�������б�˵��)
 //  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  outmethod ������ʽ(�������б�˵��)
 //  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stopmethod ͣ����ʽ(�������б�˵��)
 //  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stoptime ͣ��ʱ��(��λ����)
typedef long (_stdcall *_AddWindow)(WORD num, long left, long top, long width, long height, long transparent, long border,
 		HDC dc, long src_width, long src_height, long alignment, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime��λΪ����
 
 //���ͼƬ�ļ�����
 //  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
 //  left��top��width��height ���ϡ���ȡ��߶�
 //  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
 //  border ��ˮ�߿�(δʵ��)
 //  filename ͼƬ�ļ�
 //  inmethod ���뷽ʽ(�������б�˵��)
 //  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  outmethod ������ʽ(�������б�˵��)
 //  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stopmethod ͣ����ʽ(�������б�˵��)
 //  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stoptime ͣ��ʱ��(��λ����)
typedef long (_stdcall *_AddPicture)(WORD num, long left, long top, long width, long height, long transparent, long border,
 		char* filename, long alignment, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime��λΪ����
 
 //������ֲ���
 //  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
 //  left��top��width��height ���ϡ���ȡ��߶�
 //  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
 //  border ��ˮ�߿�(δʵ��)
 //  str �����ַ���
 //  fontname ��������
 //  fontsize �����С
 //  fontcolor ������ɫ
 //  fontstyle ������ʽ ������=WFS_BOLD��ʾ���壻=WFS_ITALIC��ʾб�壻=WFS_BOLD+WFS_ITALIC��ʾ��б��
 //  wordwrap �Ƿ��Զ����� =1�Զ����У�=0���Զ�����
 //  alignment ���뷽ʽ 0���� 1���� 2����
 //  inmethod ���뷽ʽ(�������б�˵��)
 //  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  outmethod ������ʽ(�������б�˵��)
 //  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stopmethod ͣ����ʽ(�������б�˵��)
 //  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stoptime ͣ��ʱ��(��λ����)
typedef long (_stdcall *_AddText)(WORD num, long left, long top, long width, long height, long transparent, long border,
 		char* str, char* fontname, long fontsize, long fontcolor, long fontstyle, long wordwrap, long alignment, 
 		long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime��λΪ����
 //������ֲ���(��ǿ)
 //  ͬ����������ͬ��
 //  bkcolor ����ɫ(˫ɫ��������)
 //  vertical ��0
 //  verspace �м��
 //  horfit �����Լ������Ӧ  0���� 1����
typedef long (_stdcall *_AddTextEx2)(WORD num, long left, long top, long width, long height, long transparent, long border,
 		char* str, char* fontname, long fontsize, long fontcolor, long fontstyle, long bkcolor, long wordwrap, 
 		long vertical, long alignment, long verspace, long horfit, 
 		long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime��λΪ����
 
 //����������ֲ���
 //  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
 //  left��top��width��height ���ϡ���ȡ��߶�
 //  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
 //  border ��ˮ�߿�(δʵ��)
 //  str �����ַ���
 //  fontset �ֿ� =FONTSET_16P��ʾ16�����ֿ⣻=FONTSET_24P��ʾ24�����ֿ�
 //  color ��ɫ
 //  inmethod ���뷽ʽ(�������б�˵��)
 //  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  outmethod ������ʽ(�������б�˵��)
 //  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stopmethod ͣ����ʽ(�������б�˵��)
 //  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stoptime ͣ��ʱ��(��λ����)
typedef long (_stdcall *_AddString)(WORD num, long left, long top, long width, long height, long transparent, long border,
 		char* str, long fontset, long color, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime��λΪ����
 
 //��ӱ��
 //  num ��Ŀ���ݻ�������ţ���MakeRoot��MakeChapter��MakeRegion��MakeLeaf��MakeObject�ķ���ֵ
 //  left��top��width��height ���ϡ���ȡ��߶�
 //  transparent �Ƿ�͸�� =1��ʾ͸����=0��ʾ��͸��
 //  profile ��������ļ�
 //  content �������
 //  inmethod ���뷽ʽ(�������б�˵��)
 //  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  outmethod ������ʽ(�������б�˵��)
 //  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stopmethod ͣ����ʽ(�������б�˵��)
 //  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stoptime ͣ��ʱ��(��λ����)
typedef long (_stdcall *_AddTable)(WORD num, long left, long top, long width, long height, long transparent, char* profile, char* content,
             long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime);
 
 ///////////////////////////////////////////////////////////////////////////////////////////////////
 // �����˲��г���Ŀר�Ŷ���
 //�������ֲ��Ŷ���
 //  ObjectIndex ��Ҫ�����滻���Ķ�����
 //  width ������
 //  height ����߶�
 //  str �����ַ���
 //  fontname ��������
 //  fontsize �����С
 //  fontcolor ������ɫ
 //  FontStyle ��������
 //  wordwrap �Զ�����
 //  alignment ���뷽ʽ
 //  inmethod ���뷽ʽ(�������б�˵��)
 //  inspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  outmethod ������ʽ(�������б�˵��)
 //  outspeed �����ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stopmethod ͣ����ʽ(�������б�˵��)
 //  stopspeed ͣ���ٶ�(ȡֵ��Χ0-5���ӿ쵽��)
 //  stoptime ͣ��ʱ��(��λ����)
 //  istitle �Ƿ����
typedef long (_stdcall *_SZRC_MakeTextObject)(long ObjectIndex, long width, long height, 
		char* str, char* fontname, long fontsize, long fontcolor, long fontstyle, long wordwrap, long alignment,
		long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime, long istitle);

// ====���붯����ʽ�б�(��ֵ��0��ʼ)====
//    0 = '���'
//    1 = '������ʾ,
//    2 = '�����ʾ'
//    3 = '�Ϲ���ʾ'
//    4 = '�ҹ���ʾ'
//    5 = '�¹���ʾ'
//    6 = '���������ʾ'
//    7 = '�����Ϲ���ʾ'
//    8 = '�м�������չ��',
//    9 = '�м�������չ��',
//   10 = '�м�������չ��',
//   11 = '������������',
//   12 = '������������',
//   13 = '��������չ��',
//   14 = '��������չ��',
//   15 = '�����Ͻ�����',
//   16 = '�����½�����',
//   17 = '�����Ͻ�����',
//   18 = '�����½�����',
//   19 = '������������',
//   20 = '������������',
//   21 = '�����Ҷ��',
//   22 = '�����Ҷ��',
// =====================================

// ====����������ʽ�б�(��ֵ��0��ʼ)====
//    0 = '���'
//    1 = '����ʧ'
//    2 = '������ʧ'
//    3 = '�������м��£'
//    4 = '�������м��£'
//    5 = '�������м��£'
//    6 = '���������Ƴ�'
//    7 = '���������Ƴ�'
//    8 = '���������£'
//    9 = '�������Һ�£'
//   10 = '�����Ͻ��Ƴ�'
//   11 = '�����½��Ƴ�'
//   12 = '�����Ͻ��Ƴ�'
//   13 = '�����½��Ƴ�'
//   14 = '���������Ƴ�'
//   15 = '���������Ƴ�'
//   16 = '�����Ҷ��'
//   17 = '�����Ҷ��'
// =====================================

// ====ͣ��������ʽ�б�(��ֵ��0��ʼ)====
//    0 = '��̬��ʾ'
//    1 = '��˸��ʾ'
// =====================================

class VSD
{
public:
	VSD(void);
	~VSD(void);
public:
	HINSTANCE hInstance;
	BOOL LED_VSDInitialize(void);
	void LED_VSDDestroy(void);
	int LED_VSDSendPrgm(CString strIP, CString strPort, CString strLedType,long nWidth,long nHeight,CString strPrgm, CString strPrgmFontSize,long Effect,long nPlaySpeed);
};