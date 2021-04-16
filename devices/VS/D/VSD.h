#pragma once
#include "winsock.h"
#include <windows.h>

//缺省数据包大小
#define VSD_DEFAULT_PKP_LENGTH     512

//IP地址、MAC地址长度定义
#define VSD_IP_ADDRESS_LENGTH      4
#define VSD_ETHER_ADDRESS_LENGTH   6

//通讯设备类型
#define VSD_DEVICE_TYPE_COM    0  //串口通讯
#define VSD_DEVICE_TYPE_UDP    1  //网络通讯
#define VSD_DEVICE_TYPE_485    2  //485通讯

//串口或者485通讯使用得通讯速度(波特率)
#define VSD_SBR_57600          0
#define VSD_SBR_38400          1
#define VSD_SBR_19200          2
#define VSD_SBR_9600           3

//是否等待下位机应答，直接发送所有数据
#define VSD_NOTIFY_NONE        1
//是否阻塞方式；是则等到发送完成或者超时，才返回；否则立即返回
#define VSD_NOTIFY_BLOCK       2
//是否将发送结果以Windows窗体消息方式送到调用得应用
#define VSD_NOTIFY_EVENT       4
//使用一个本地端口，和多个目标IP通讯
#define VSD_NOTIFY_MULTI       8

#define VSD_R_DEVICE_READY     0
#define VSD_R_DEVICE_INVALID   -1
#define VSD_R_DEVICE_BUSY      -2
#define VSD_R_FONTSET_INVALID  -3
#define VSD_R_DLL_INIT_IVALID  -4
#define VSD_R_IGNORE_RESPOND   -5

//Chapter和Leaf中，播放时间控制
#define VSD_WAIT_USE_TIME      0  //按照指定的时间长度播放，到时间就切到下一个
#define VSD_WAIT_CHILD         1  //等待子项目的播放，如果到了指定的时间长度，而子项目还没有播完，则等待播完

#define VSD_V_FALSE            0
#define VSD_V_TRUE             1

//显示屏基色类型
#define VSD_COLOR_MODE_MONO              1  //单色
#define VSD_COLOR_MODE_DOUBLE            2  //双色
#define VSD_COLOR_MODE_THREE             3  //无灰度全彩
#define VSD_COLOR_MODE_FULLCOLOR         4  //全彩

//显示数据命令
#define VSD_ROOT_UPDATE            0x13  //更新下位机程序
#define VSD_ROOT_FONTSET           0x14  //下载字库
#define VSD_ROOT_PLAY              0x21  //节目数据，保存到RAM，掉电丢失
#define VSD_ROOT_DOWNLOAD          0x22  //节目数据，保存到Flash
#define VSD_ROOT_PLAY_CHAPTER      0x23  //插入或者更新某一节目
#define VSD_ROOT_PLAY_REGION       0x25  //插入或者更新某一分区
#define VSD_ROOT_PLAY_LEAF         0x27  //插入或者更新某一页面
#define VSD_ROOT_PLAY_OBJECT       0x29  //插入或者更新某一对象
		
#define VSD_ACTMODE_INSERT         0  //插入操作
#define VSD_ACTMODE_REPLACE        1  //替换操作

//RAM节目播放
#define VSD_ROOT_SURVIVE_ALWAYS    -1

//Windows字体类型定义
#define VSD_WFS_NONE               0x0   //普通样式
#define VSD_WFS_BOLD               0x01  //粗体
#define VSD_WFS_ITALIC             0x02  //斜体
#define VSD_WFS_UNDERLINE          0x04  //下划线
#define VSD_WFS_STRIKEOUT          0x08  //删除线

//流控制常量
#define VSD_FLOW_NONE          0
#define VSD_FLOW_RTS_CTS       1

//下位机应答标识
#define VSD_LM_RX_COMPLETE         1
#define VSD_LM_TX_COMPLETE         2
#define VSD_LM_RESPOND             3
#define VSD_LM_TIMEOUT             4
#define VSD_LM_NOTIFY              5
#define VSD_LM_PARAM               6
#define VSD_LM_TX_PROGRESS         7
#define VSD_LM_RX_PROGRESS         8
#define VSD_RESULT_FLASH           0xff

//电源开关状态
#define VSD_LED_POWER_ON       1
#define VSD_LED_POWER_OFF      0

//内码文字大小
#define VSD_FONT_SET_16        0      //16点阵字符
#define VSD_FONT_SET_24        1      //24点阵字符
  
//正计时、倒计时type参数
#define VSD_CT_COUNTUP         0      //正计时
#define VSD_CT_COUNTDOWN       1      //倒计时
//正计时、倒计时format参数
#define VSD_CF_HNS             0      //时分秒（相对值）
#define VSD_CF_HN              1      //时分（相对值）
#define VSD_CF_NS              2      //分秒（相对值）
#define VSD_CF_H               3      //时（相对值）
#define VSD_CF_N               4      //分（相对值）
#define VSD_CF_S               5      //秒（相对值）
#define VSD_CF_DAY             6      //天数（绝对数量）
#define VSD_CF_HOUR            7      //小时数（绝对数量）
#define VSD_CF_MINUTE          8      //分钟数（绝对数量）
#define VSD_CF_SECOND          9      //秒数（绝对数量）

//模拟时钟边框形状
#define VSD_SHAPE_RECTANGLE    0      //方形
#define VSD_SHAPE_ROUNDRECT    1      //圆角方形
#define VSD_SHAPE_CIRCLE       2      //圆形

//命令代码定义
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
#define VSD_NOTIFY_ROOT_DOWNLOAD      0x00010003  //更新Flash播放节目
#define VSD_NOTIFY_SET_PARAM          0x00010004  //设置参数
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
  DWORD txTimeo;   //发送后等待应答时间 ====超时时间应为txTimeo*txRepeat
  DWORD txRepeat;  //失败重发次数
  DWORD txMovewin; //划动窗口
  DWORD key;
  long  pkpLength; //数据包大小
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
	char  dev_name[32];  //设备名称
	DWORD dev_id;        //设备标识
	DWORD dev_ip;        //设备IP地址
	WORD  dev_addr;      //设备地址
	WORD  dev_port;      //设备端口
	DWORD reserved[5];   //系统保留
}VSD_TDevInfo, *VSD_PDevInfo;

typedef struct VSD_DEVICEREPORT{
	VSD_TDevInfo devinfo;    //设备信息
	double   timeupdate; //最后刷新时间
}VSD_TDeviceReport, *VSD_PDeviceReport;

/************************************************************************/
/* 在线控制卡列表相关接口函数                                           */
/************************************************************************/
//动态链接库初始化
typedef long (_stdcall *_LED_Startup)(void);

//动态链接库销毁
typedef long (_stdcall *_LED_Cleanup)(void);
//创建控制卡在线监听服务
//  serverindex 控制卡在线监听服务编号(可以在多个socket udp端口监听)
//  localport 本地端口
typedef long (_stdcall *_LED_Report_CreateServer)(long serverindex, long localport);

//删除控制卡在线监听服务
//  serverindex 控制卡在线监听服务编号
typedef void (_stdcall *_LED_Report_RemoveServer)(long serverindex);

//删除全部控制卡在线监听服务
typedef void (_stdcall *_LED_Report_RemoveAllServer)(void);

//获得控制卡在线列表
//必须先创建控制卡在线监听服务，即调用LED_Report_CreateServer后使用，否则返回值无效
//  serverindex 控制卡在线监听服务编号
//  plist 输出在线列表的用户外部缓冲区，
//        如果传入空(NULL/0)，则输出到动态链接库内部的缓冲区，继续调用下面的接口取得详细信息
//  count 最大读取个数
//--返回值-- 小于0表示失败(未创建该在线监听服务)，大于等于0表示在线的控制卡数量
typedef long (_stdcall *_LED_Report_GetOnlineList)(long serverindex, void* plist, long count);

//获得某个在线控制卡的上报控制卡名称
//必须先创建控制卡在线监听服务，即调用LED_Report_CreateServer后使用，否则返回值无效
//  serverindex 控制卡在线监听服务编号
//  itemindex 该监听服务的在线列表中，在线控制卡的编号
//--返回值-- 在线控制卡的上报控制卡名称
typedef char* (_stdcall *_LED_Report_GetOnlineItemName)(long serverindex, long itemindex);

//获得某个在线控制卡的上报控制卡IP地址
//必须先创建控制卡在线监听服务，即调用LED_Report_CreateServer后使用，否则返回值无效
//  serverindex 控制卡在线监听服务编号
//  itemindex 该监听服务的在线列表中，在线控制卡的编号
//--返回值-- 在线控制卡的IP地址
typedef char* (_stdcall *_LED_Report_GetOnlineItemHost)(long serverindex, long itemindex);

//获得某个在线控制卡的上报控制卡远程UDP端口号
//必须先创建控制卡在线监听服务，即调用LED_Report_CreateServer后使用，否则返回值无效
//  serverindex 控制卡在线监听服务编号
//  itemindex 该监听服务的在线列表中，在线控制卡的编号
//--返回值-- 在线控制卡的远程UDP端口号
typedef long (_stdcall *_LED_Report_GetOnlineItemPort)(long serverindex, long itemindex);

//获得某个在线控制卡的上报控制卡地址
//必须先创建控制卡在线监听服务，即调用LED_Report_CreateServer后使用，否则返回值无效
//  serverindex 控制卡在线监听服务编号
//  itemindex 该监听服务的在线列表中，在线控制卡的编号
//--返回值-- 在线控制卡的硬件地址
typedef long (_stdcall *_LED_Report_GetOnlineItemAddr)(long serverindex, long itemindex);

/************************************************************************/
/* 填写通讯参数接口函数，用于一些无法传递结构体和指针的开发环境来调用   */
/************************************************************************/

//填写网络通讯参数，供发送时使用
//  index 参数数组编号
//  localport 本地端口
//  host 控制卡IP地址
//  remoteport 远程端口
//  address 控制卡地址
//  notifymode 通讯同步异步模式
//  wmhandle 接收消息窗体句柄
//  wmmessage 接收消息的消息号
//--返回值-- 小于0表示失败，大于等于0表示参数的id号
typedef long (_stdcall *_LED_UDP_SenderParam)(long index, long localport, char* host, long remoteport, long address, long notifymode, long wmhandle, long wmmessage);

//填写串口通讯参数，供发送时使用
//  index 参数数组编号
//  comport 串口号
//  baudrate 波特率
//  address 控制卡地址
//  notifymode 通讯同步异步模式
//  wmhandle 接收消息窗体句柄
//  wmmessage 接收消息的消息号
//--返回值-- 小于0表示失败，大于等于0表示参数的id号
typedef long (_stdcall *_LED_COM_SenderParam)(long index, long comport, long baudrate, long address, long notifymode, long wmhandle, long wmmessage);

//填写网络通讯参数，供发送时使用
//  index 参数数组编号
//  localport 本地端口
//  serverindex 在线监听服务编号
//  name 控制卡名称(控制卡上报来的名称)
//  notifymode 通讯同步异步模式
//  wmhandle 接收消息窗体句柄
//  wmmessage 接收消息的消息号
//--返回值-- 小于0表示失败，大于等于0表示参数的id号
typedef long (_stdcall *_LED_UDP_SenderParam_ByReportName)(long index, long localport, long serverindex, char* name, long notifymode, long wmhandle, long wmmessage);
//预览显示内容
typedef void (_stdcall *_LED_Preview)(long index, long width, long height, char* previewfile);
//复位控制卡节目播放，重新显示控制卡Flash中存储的节目
typedef long (_stdcall *_LED_ResetDisplay)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_ResetDisplay2)(long senderparam_index);
//校正时间，以当前计算机的系统时间校正控制卡的时钟
typedef long (_stdcall *_LED_AdjustTime)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_AdjustTime2)(long senderparam_index);
//校正时间扩展，以指定的时间校正控制卡的时钟
typedef long (_stdcall *_LED_AdjustTimeEx)(VSD_PSenderParam param, LPSYSTEMTIME time);
typedef long (_stdcall *_LED_AdjustTimeEx2)(long senderparam_index, LPSYSTEMTIME time);
//设置当前显示的节目
typedef long (_stdcall *_LED_SetCurChapter)(VSD_PSenderParam param, long value);
typedef long (_stdcall *_LED_SetCurChapter2)(long senderparam_index, long value);
//设置当前显示的节目
typedef long (_stdcall *_LED_GetCurChapter)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_GetCurChapter2)(long senderparam_index);
//设置控制卡电源 value=LED_POWER_ON表示开启电源 value=LED_POWER_OFF表示关闭电源
typedef long (_stdcall *_LED_SetPower)(VSD_PSenderParam param, long value);
typedef long (_stdcall *_LED_SetPower2)(long senderparam_index, long value);
//串口转发数据
typedef long (_stdcall *_LED_ComTransfer)(VSD_PSenderParam param, BYTE* buffer, DWORD size);
typedef long (_stdcall *_LED_ComTransfer2)(long senderparam_index, BYTE* buffer, DWORD size);
//读取控制卡电源状态
typedef long (_stdcall *_LED_GetPower)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_GetPower2)(long senderparam_index);
//设置控制卡亮度 value取值范围0-7
typedef long (_stdcall *_LED_SetBright)(VSD_PSenderParam param, long value);
typedef long (_stdcall *_LED_SetBright2)(long senderparam_index, long value);
//读取控制卡亮度
typedef long (_stdcall *_LED_GetBright)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_GetBright2)(long senderparam_index);
//设置控制卡的定时开关屏计划
typedef long (_stdcall *_LED_SetPowerSchedule)(VSD_PSenderParam param, VSD_PPowerSchedule value);
typedef long (_stdcall *_LED_SetPowerSchedule2)(long senderparam_index, VSD_PPowerSchedule value);
//读取控制卡的定时开关屏计划
typedef long (_stdcall *_LED_GetPowerSchedule)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_GetPowerSchedule2)(long senderparam_index);
//设置控制卡的定时亮度调节计划
typedef long (_stdcall *_LED_SetBrightSchedule)(VSD_PSenderParam param, VSD_PBrightSchedule value);
typedef long (_stdcall *_LED_SetBrightSchedule2)(long senderparam_index, VSD_PBrightSchedule value); 
//读取控制卡的定时亮度调节计划
typedef long (_stdcall *_LED_GetBrightSchedule)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_GetBrightSchedule2)(long senderparam_index);
//发送节目数据 index为MakeRoot、MakeChapter、MakeRegion、MakeLeaf、MakeObject函数的返回值
typedef long (_stdcall *_LED_SendToScreen)(VSD_PSenderParam param, long index);
typedef long (_stdcall *_LED_SendToScreen2)(long senderparam_index, long index);
 
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // 用于对控制卡进行一些参数设置
 // 流程为：读取控制卡参数--提取各个参数--
 //                       --修改各个参数--将修改后的参数接入控制卡
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 //读取控制卡参数
typedef long (_stdcall *_LED_Cache_GetBoardParam)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_Cache_GetBoardParam2)(long senderparam_index);
 //提取各个参数
typedef long (_stdcall *_LED_Cache_GetBoardParam_SaveToFile)(char* filename);  //将控制卡回读的参数，写入文件
typedef char* (_stdcall *_LED_Cache_GetBoardParam_IP)(void);
typedef char* (_stdcall *_LED_Cache_GetBoardParam_Mac)(void);
typedef long (_stdcall *_LED_Cache_GetBoardParam_Addr)(void);
typedef long (_stdcall *_LED_Cache_GetBoardParam_Width)(void);
typedef long (_stdcall *_LED_Cache_GetBoardParam_Height)(void);
typedef long (_stdcall *_LED_Cache_GetBoardParam_Brightness)(void);
 //修改各个参数
typedef long (_stdcall *_LED_Cache_SetBoardParam_LoadFromFile)(char* filename);  //从文件读取参数，保存到动态链接库中，以供写入到控制卡
typedef void (_stdcall *_LED_Cache_SetBoardParam_IP)(char* value);
typedef void (_stdcall *_LED_Cache_SetBoardParam_Mac)(char* value);
typedef void (_stdcall *_LED_Cache_SetBoardParam_Addr)(long value);
typedef void (_stdcall *_LED_Cache_SetBoardParam_Width)(long value);
typedef void (_stdcall *_LED_Cache_SetBoardParam_Height)(long value);
typedef void (_stdcall *_LED_Cache_SetBoardParam_Brightness)(long value);
 //将修改后的参数接入控制卡
typedef long (_stdcall *_LED_Cache_SetBoardParam)(VSD_PSenderParam param);
typedef long (_stdcall *_LED_Cache_SetBoardParam2)(long senderparam_index);

 //获取控制卡应答结果的数据
typedef long (_stdcall *_LED_GetNotifyParam)(VSD_PNotifyParam notify, long index);
 
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 //节目数据组织形式
 //  ROOT
 //   |
 //   |---Chapter(节目)
 //   |      |
 //   |      |---Region(分区)
 //   |      |     |
 //   |      |     |---Leaf(页面)
 //   |      |     |    |
 //   |      |     |    |---Object(对象[文字、时钟、图片等])
 //   |      |     |    |
 //   |      |     |    |---Object(对象[文字、时钟、图片等])
 //   |      |     |    |
 //   |      |     |    |   ......
 //   |      |     |    |
 //   |      |     |
 //   |      |     |---Leaf(页面)
 //   |      |     |
 //   |      |     |   ......
 //   |      |     |
 //   |      |
 //   |      |---Region(分区)
 //   |      |
 //   |      |   ......
 //   |      |
 //   |---Chapter(节目)
 //   |
 //   |   ......
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 //生成播放数据（从VisionShow软件编辑的Vsq文件载入，并生成要下发的节目数据）
 //  RootType 为播放类型；=ROOT_PLAY表示更新控制卡RAM中的节目(掉电丢失)；=ROOT_DOWNLOAD表示更新控制卡Flash中的节目(掉电不丢失)
 //  ColorMode 为颜色模式；取值为COLOR_MODE_MONO或者COLOR
 //  survive 为RAM节目生存时间，在RootType=ROOT_PLAY时有效，当RAM节目播放达到时间后，恢复显示FLASH中的节目
 //  filename 由VisionShow软件编辑的节目文件
typedef long (_stdcall *_MakeFromVsqFile)(char* filename, long RootType, long ColorMode, long survive);
 
 //生成播放数据
 //  RootType 为播放类型；=ROOT_PLAY表示更新控制卡RAM中的节目(掉电丢失)；=ROOT_DOWNLOAD表示更新控制卡Flash中的节目(掉电不丢失)
 //  ColorMode 为颜色模式；取值为COLOR_MODE_MONO或者COLOR
 //  survive 为RAM节目生存时间，在RootType=ROOT_PLAY时有效，当RAM节目播放达到时间后，恢复显示FLASH中的节目
typedef long (_stdcall *_MakeRoot)(long RootType, long ColorMode, long survive);
 
 //生成节目数据，后续需要调用[AddRegion]->[AddLeaf]->[AddObject]->[AddWindows/AddDateTime等]
 //  RootType 必须设为ROOT_PLAY_CHAPTER
 //  ActionMode 必须设为0
 //  ChapterIndex 要更新的节目序号
 //  ColorMode 同MakeRoot中的定义
 //  time 播放的时间长度
 //  wait 等待模式，=WAIT_CHILD，表示当达到播放时间长度时，需要等待子节目播放完成再切换；
 //                 =WAIT_USE_TIME，表示当达到播放时间长度时，不等待子节目播放完成，直接切换下一节目
typedef long (_stdcall *_MakeChapter)(long RootType, long ActionMode, long ChapterIndex, long ColorMode, DWORD time, WORD wait);
 
 //生成分区，后续需要调用[AddLeaf]->[AddObject]->[AddWindows/AddDateTime等]
 //  RootType 必须设为ROOT_PLAY_REGION
 //  ActionMode 必须设为0
 //  ChapterIndex 要更新的节目序号
 //  RegionIndex 要更新的分区序号
 //  ColorMode 同MakeRoot中的定义
 //  left、top、width、height 左、上、宽度、高度
 //  border 流水边框
typedef long (_stdcall *_MakeRegion)(long RootType, long ActionMode, long ChapterIndex, long RegionIndex, long ColorMode, long left, long top, long width, long height, long border);
 
 //生成页面，后续需要调用[AddObject]->[AddWindows/AddDateTime等]
 //  RootType 必须设为ROOT_PLAY_LEAF
 //  ActionMode 必须设为0
 //  ChapterIndex 要更新的节目序号
 //  RegionIndex 要更新的分区序号
 //  LeafIndex 要更新的页面序号
 //  ColorMode 同MakeRoot中的定义
 //  time 播放的时间长度
 //  wait 等待模式，=WAIT_CHILD，表示当达到播放时间长度时，需要等待子节目播放完成再切换；
 //                 =WAIT_USE_TIME，表示当达到播放时间长度时，不等待子节目播放完成，直接切换下一页面
typedef long (_stdcall *_MakeLeaf)(long RootType, long ActionMode, long ChapterIndex, long RegionIndex, long LeafIndex, long ColorMode, DWORD time, WORD wait);
 
 //生成播放对象，后续需要调用[AddWindows/AddDateTime等]
 //  RootType 必须设为ROOT_PLAY_OBJECT
 //  ActionMode 必须设为0
 //  ChapterIndex 要更新的节目序号
 //  RegionIndex 要更新的分区序号
 //  LeafIndex 要更新的页面序号
 //  ObjectIndex 要更新的对象序号
 //  ColorMode 同MakeRoot中的定义
typedef long (_stdcall *_MakeObject)(long RootType, long ActionMode, long ChapterIndex, long RegionIndex, long LeafIndex, long ObjectIndex, long ColorMode);
 
 //添加节目
 //  num 节目数据缓冲区编号，是MakeRoot的返回值
 //  time 播放的时间长度
 //  wait 等待模式，=WAIT_CHILD，表示当达到播放时间长度时，需要等待子节目播放完成再切换；
 //                 =WAIT_USE_TIME，表示当达到播放时间长度时，不等待子节目播放完成，直接切换下一节目
typedef long (_stdcall *_AddChapter)(WORD num, DWORD time, WORD wait); //time为毫秒
 //  priority 优先级0-2
 //  kind 播放计划模式  =0始终播放  =1按每周七天播放  =2按起始时间播放
 //  week 周定义  bit0到bit6，表示周日到周六 当kind=1时有效
 //  fromtime 起始时间  当kind=1时，只时间部分有效，当kind=2时，日期时间全有效
 //  totime 结束时间  当kind=1时，只时间部分有效，当kind=2时，日期时间全有效
typedef long (_stdcall *_AddChapterEx2)(WORD num, DWORD time, WORD wait, WORD priority, WORD kind, WORD week, char* fromtime, char* totime); //time为毫秒
 
 //添加分区
 //  num 节目数据缓冲区编号，是MakeRoot、MakeChapter的返回值
 //  left、top、width、height 左、上、宽度、高度
 //  border 流水边框
typedef long (_stdcall *_AddRegion)(WORD num, long left, long top, long width, long height, long border);
 
 //添加页面
 //  num 节目数据缓冲区编号，是MakeRoot、MakeChapter、MakeRegion的返回值
 //  time 播放的时间长度
 //  wait 等待模式，=WAIT_CHILD，表示当达到播放时间长度时，需要等待子节目播放完成再切换；
 //                 =WAIT_USE_TIME，表示当达到播放时间长度时，不等待子节目播放完成，直接切换下一页面
typedef long (_stdcall *_AddLeaf)(WORD num, DWORD time, WORD wait); //time为毫秒
 
 //添加日期时间显示
 //  num 节目数据缓冲区编号，是MakeRoot、MakeChapter、MakeRegion、MakeLeaf、MakeObject的返回值
 //  left、top、width、height 左、上、宽度、高度
 //  transparent 是否透明 =1表示透明；=0表示不透明
 //  border 流水边框(未实现)
 //  fontname 字体名称
 //  fontsize 字体大小
 //  fontcolor 字体颜色
 //  fontstyle 字体样式 举例：=WFS_BOLD表示粗体；=WFS_ITALIC表示斜体；=WFS_BOLD+WFS_ITALIC表示粗斜体
 //  year_offset 年偏移量
 //  month_offset 月偏移量
 //  day_offset 日偏移量
 //  sec_offset 秒偏移量
 //  format 显示格式 
 //      #y表示年 #m表示月 #d表示日 #h表示时 #n表示分 #s表示秒 #w表示星期 #c表示农历
 //      举例： format="#y年#m月#d日 #h时#n分#s秒 星期#w 农历#c"时，显示为"2009年06月27日 12时38分45秒 星期六 农历五月初五"
typedef long (_stdcall *_AddDateTime)(WORD num, long left, long top, long width, long height, long transparent, long border,
 		char* fontname, long fontsize, long fontcolor, long fontstyle, 
         long year_offset, long month_offset, long day_offset, long sec_offset, char* format);
 
 //添加作战时间显示
 //  num 节目数据缓冲区编号，是MakeRoot、MakeChapter、MakeRegion、MakeLeaf、MakeObject的返回值
 //  left、top、width、height 左、上、宽度、高度
 //  transparent 是否透明 =1表示透明；=0表示不透明
 //  border 流水边框(未实现)
 //  fontname 字体名称
 //  fontsize 字体大小
 //  fontcolor 字体颜色
 //  fontstyle 字体样式 举例：=WFS_BOLD表示粗体；=WFS_ITALIC表示斜体；=WFS_BOLD+WFS_ITALIC表示粗斜体
 //  format 显示格式 
 //      #y表示年 #m表示月 #d表示日 #h表示时 #n表示分 #s表示秒
 //  basetime 作战时间
 //  fromtime 开始时间
 //  totime 结束时间
 //  step 计时走秒时间步长（多少毫秒走一秒）
typedef long (_stdcall *_AddCampaignEx)(WORD num, long left, long top, long width, long height, long transparent, long border, 
 		char* fontname, long fontsize, long fontcolor, long fontstyle, 
 		char* format, VSD_PTimeStamp basetime, VSD_PTimeStamp fromtime, VSD_PTimeStamp totime, long step);
 
 //添加模拟时钟
 //  num 节目数据缓冲区编号，是MakeRoot、MakeChapter、MakeRegion、MakeLeaf、MakeObject的返回值
 //  left、top、width、height 左、上、宽度、高度
 //  transparent 是否透明 =1表示透明；=0表示不透明
 //  border 流水边框(未实现)
 //  offset 秒偏移量
 //  bkcolor: 背景颜色
 //  framecolor: 表框颜色
 //  framewidth: 表框颜色
 //  frameshape: 表框形状 =0表示正方形；=1表示圆角方形；=2表示圆形
 //  dotradius: 刻度距离表盘中心半径
 //  adotwidth: 0369点刻度大小
 //  adotcolor: 0369点刻度颜色
 //  bdotwidth: 其他点刻度大小
 //  bdotcolor: 其他点刻度颜色
 //  hourwidth: 时针粗细
 //  hourcolor: 时针颜色
 //  minutewidth: 分针粗细
 //  minutecolor: 分针颜色
 //  secondwidth: 秒针粗细
 //  secondcolor: 秒针颜色
typedef long (_stdcall *_AddClock)(WORD num, long left, long top, long width, long height, long transparent, long border, long offset,
 		DWORD bkcolor, DWORD framecolor, DWORD framewidth, long frameshape,
 		long dotradius, long adotwidth, DWORD adotcolor, long bdotwidth, DWORD bdotcolor,
         long hourwidth, DWORD hourcolor, long minutewidth, DWORD minutecolor, long secondwidth, DWORD secondcolor);
 
 //添加动画
 //  num 节目数据缓冲区编号，是MakeRoot、MakeChapter、MakeRegion、MakeLeaf、MakeObject的返回值
 //  left、top、width、height 左、上、宽度、高度
 //  transparent 是否透明 =1表示透明；=0表示不透明
 //  border 流水边框(未实现)
 //  filename avi文件名
 //  stretch: 图像是否拉伸以适应对象大小
typedef long (_stdcall *_AddMovie)(WORD num, long left, long top, long width, long height, long transparent, long border, char* filename, long stretch);
 
 //添加图片组播放
 //  num 节目数据缓冲区编号，是MakeRoot、MakeChapter、MakeRegion、MakeLeaf、MakeObject的返回值
 //  left、top、width、height 左、上、宽度、高度
 //  transparent 是否透明 =1表示透明；=0表示不透明
 //  border 流水边框(未实现)
typedef long (_stdcall *_AddWindows)(WORD num, long left, long top, long width, long height, long transparent, long border);
 
 //添加图片组的子图片 此函数要跟在AddWindows后面调用
 //  num 节目数据缓冲区编号，是MakeRoot、MakeChapter、MakeRegion、MakeLeaf、MakeObject的返回值
 //  dc 源图片DC句柄
 //  width 图片宽度
 //  height 图片高度
 //  inmethod 引入方式(下面有列表说明)
 //  inspeed 引入速度(取值范围0-5，从快到慢)
 //  outmethod 引出方式(下面有列表说明)
 //  outspeed 引出速度(取值范围0-5，从快到慢)
 //  stopmethod 停留方式(下面有列表说明)
 //  stopspeed 停留速度(取值范围0-5，从快到慢)
 //  stoptime 停留时间(单位毫秒)
typedef long (_stdcall *_AddChildWindow)(WORD num, HDC dc, long width, long height, long alignment, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime单位为秒
 
 //添加图片组的子图片 此函数要跟在AddWindows后面调用
 //  num 节目数据缓冲区编号，是MakeRoot、MakeChapter、MakeRegion、MakeLeaf、MakeObject的返回值
 //  filename 图片文件名
 //  inmethod 引入方式(下面有列表说明)
 //  inspeed 引入速度(取值范围0-5，从快到慢)
 //  outmethod 引出方式(下面有列表说明)
 //  outspeed 引出速度(取值范围0-5，从快到慢)
 //  stopmethod 停留方式(下面有列表说明)
 //  stopspeed 停留速度(取值范围0-5，从快到慢)
 //  stoptime 停留时间(单位毫秒)
typedef long (_stdcall *_AddChildPicture)(WORD num, char* filename, long alignment, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime单位为秒
 
 //添加图片组的子图片 此函数要跟在AddWindows后面调用
 //  num 节目数据缓冲区编号，是MakeRoot、MakeChapter、MakeRegion、MakeLeaf、MakeObject的返回值
 //  str 文字字符串
 //  fontname 字体名称
 //  fontsize 字体大小
 //  fontcolor 字体颜色
 //  fontstyle 字体样式 举例：=WFS_BOLD表示粗体；=WFS_ITALIC表示斜体；=WFS_BOLD+WFS_ITALIC表示粗斜体
 //  wordwrap 是否自动换行 =1自动换行；=0不自动换行
 //  inmethod 引入方式(下面有列表说明)
 //  inspeed 引入速度(取值范围0-5，从快到慢)
 //  outmethod 引出方式(下面有列表说明)
 //  outspeed 引出速度(取值范围0-5，从快到慢)
 //  stopmethod 停留方式(下面有列表说明)
 //  stopspeed 停留速度(取值范围0-5，从快到慢)
 //  stoptime 停留时间(单位毫秒)
typedef long (_stdcall *_AddChildText)(WORD num, char* str, char* fontname, long fontsize, long fontcolor, long fontstyle, long wordwrap, long alignment, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime单位为毫秒
 
 //添加内码文字组播放
 //  num 节目数据缓冲区编号，是MakeRoot、MakeChapter、MakeRegion、MakeLeaf、MakeObject的返回值
 //  left、top、width、height 左、上、宽度、高度
 //  transparent 是否透明 =1表示透明；=0表示不透明
 //  border 流水边框(未实现)
typedef long (_stdcall *_AddStrings)(WORD num, long left, long top, long width, long height, long transparent, long border);
 
 //添加图片组的子图片 此函数要跟在AddWindows后面调用
 //  num 节目数据缓冲区编号，是MakeRoot、MakeChapter、MakeRegion、MakeLeaf、MakeObject的返回值
 //  str 文字字符串
 //  fontset 字库 =FONTSET_16P表示16点阵字库；=FONTSET_24P表示24点阵字库
 //  color 颜色
 //  inmethod 引入方式(下面有列表说明)
 //  inspeed 引入速度(取值范围0-5，从快到慢)
 //  outmethod 引出方式(下面有列表说明)
 //  outspeed 引出速度(取值范围0-5，从快到慢)
 //  stopmethod 停留方式(下面有列表说明)
 //  stopspeed 停留速度(取值范围0-5，从快到慢)
 //  stoptime 停留时间(单位毫秒)
typedef long (_stdcall *_AddChildString)(WORD num, char* str, long fontset, long color, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime单位为毫秒
 
 //添加图片点阵播放
 //  num 节目数据缓冲区编号，是MakeRoot、MakeChapter、MakeRegion、MakeLeaf、MakeObject的返回值
 //  left、top、width、height 左、上、宽度、高度
 //  transparent 是否透明 =1表示透明；=0表示不透明
 //  border 流水边框(未实现)
 //  dc 源图片DC句柄
 //  src_width 图片宽度
 //  src_height 图片高度
 //  inmethod 引入方式(下面有列表说明)
 //  inspeed 引入速度(取值范围0-5，从快到慢)
 //  outmethod 引出方式(下面有列表说明)
 //  outspeed 引出速度(取值范围0-5，从快到慢)
 //  stopmethod 停留方式(下面有列表说明)
 //  stopspeed 停留速度(取值范围0-5，从快到慢)
 //  stoptime 停留时间(单位毫秒)
typedef long (_stdcall *_AddWindow)(WORD num, long left, long top, long width, long height, long transparent, long border,
 		HDC dc, long src_width, long src_height, long alignment, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime单位为毫秒
 
 //添加图片文件播放
 //  num 节目数据缓冲区编号，是MakeRoot、MakeChapter、MakeRegion、MakeLeaf、MakeObject的返回值
 //  left、top、width、height 左、上、宽度、高度
 //  transparent 是否透明 =1表示透明；=0表示不透明
 //  border 流水边框(未实现)
 //  filename 图片文件
 //  inmethod 引入方式(下面有列表说明)
 //  inspeed 引入速度(取值范围0-5，从快到慢)
 //  outmethod 引出方式(下面有列表说明)
 //  outspeed 引出速度(取值范围0-5，从快到慢)
 //  stopmethod 停留方式(下面有列表说明)
 //  stopspeed 停留速度(取值范围0-5，从快到慢)
 //  stoptime 停留时间(单位毫秒)
typedef long (_stdcall *_AddPicture)(WORD num, long left, long top, long width, long height, long transparent, long border,
 		char* filename, long alignment, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime单位为毫秒
 
 //添加文字播放
 //  num 节目数据缓冲区编号，是MakeRoot、MakeChapter、MakeRegion、MakeLeaf、MakeObject的返回值
 //  left、top、width、height 左、上、宽度、高度
 //  transparent 是否透明 =1表示透明；=0表示不透明
 //  border 流水边框(未实现)
 //  str 文字字符串
 //  fontname 字体名称
 //  fontsize 字体大小
 //  fontcolor 字体颜色
 //  fontstyle 字体样式 举例：=WFS_BOLD表示粗体；=WFS_ITALIC表示斜体；=WFS_BOLD+WFS_ITALIC表示粗斜体
 //  wordwrap 是否自动换行 =1自动换行；=0不自动换行
 //  alignment 对齐方式 0靠左 1居中 2靠右
 //  inmethod 引入方式(下面有列表说明)
 //  inspeed 引入速度(取值范围0-5，从快到慢)
 //  outmethod 引出方式(下面有列表说明)
 //  outspeed 引出速度(取值范围0-5，从快到慢)
 //  stopmethod 停留方式(下面有列表说明)
 //  stopspeed 停留速度(取值范围0-5，从快到慢)
 //  stoptime 停留时间(单位毫秒)
typedef long (_stdcall *_AddText)(WORD num, long left, long top, long width, long height, long transparent, long border,
 		char* str, char* fontname, long fontsize, long fontcolor, long fontstyle, long wordwrap, long alignment, 
 		long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime单位为毫秒
 //添加文字播放(增强)
 //  同名参数定义同上
 //  bkcolor 背景色(双色屏不能用)
 //  vertical 置0
 //  verspace 行间距
 //  horfit 横向自间距自适应  0禁用 1启用
typedef long (_stdcall *_AddTextEx2)(WORD num, long left, long top, long width, long height, long transparent, long border,
 		char* str, char* fontname, long fontsize, long fontcolor, long fontstyle, long bkcolor, long wordwrap, 
 		long vertical, long alignment, long verspace, long horfit, 
 		long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime单位为毫秒
 
 //添加内码文字播放
 //  num 节目数据缓冲区编号，是MakeRoot、MakeChapter、MakeRegion、MakeLeaf、MakeObject的返回值
 //  left、top、width、height 左、上、宽度、高度
 //  transparent 是否透明 =1表示透明；=0表示不透明
 //  border 流水边框(未实现)
 //  str 文字字符串
 //  fontset 字库 =FONTSET_16P表示16点阵字库；=FONTSET_24P表示24点阵字库
 //  color 颜色
 //  inmethod 引入方式(下面有列表说明)
 //  inspeed 引入速度(取值范围0-5，从快到慢)
 //  outmethod 引出方式(下面有列表说明)
 //  outspeed 引出速度(取值范围0-5，从快到慢)
 //  stopmethod 停留方式(下面有列表说明)
 //  stopspeed 停留速度(取值范围0-5，从快到慢)
 //  stoptime 停留时间(单位毫秒)
typedef long (_stdcall *_AddString)(WORD num, long left, long top, long width, long height, long transparent, long border,
 		char* str, long fontset, long color, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime); //stoptime单位为毫秒
 
 //添加表格
 //  num 节目数据缓冲区编号，是MakeRoot、MakeChapter、MakeRegion、MakeLeaf、MakeObject的返回值
 //  left、top、width、height 左、上、宽度、高度
 //  transparent 是否透明 =1表示透明；=0表示不透明
 //  profile 表格配置文件
 //  content 表格内容
 //  inmethod 引入方式(下面有列表说明)
 //  inspeed 引入速度(取值范围0-5，从快到慢)
 //  outmethod 引出方式(下面有列表说明)
 //  outspeed 引出速度(取值范围0-5，从快到慢)
 //  stopmethod 停留方式(下面有列表说明)
 //  stopspeed 停留速度(取值范围0-5，从快到慢)
 //  stoptime 停留时间(单位毫秒)
typedef long (_stdcall *_AddTable)(WORD num, long left, long top, long width, long height, long transparent, char* profile, char* content,
             long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime);
 
 ///////////////////////////////////////////////////////////////////////////////////////////////////
 // 深圳人才市场项目专门定制
 //生成文字播放对象
 //  ObjectIndex 需要更新替换掉的对象编号
 //  width 对象宽度
 //  height 对象高度
 //  str 文字字符串
 //  fontname 字体名称
 //  fontsize 字体大小
 //  fontcolor 字体颜色
 //  FontStyle 字体类型
 //  wordwrap 自动换行
 //  alignment 对齐方式
 //  inmethod 引入方式(下面有列表说明)
 //  inspeed 引入速度(取值范围0-5，从快到慢)
 //  outmethod 引出方式(下面有列表说明)
 //  outspeed 引出速度(取值范围0-5，从快到慢)
 //  stopmethod 停留方式(下面有列表说明)
 //  stopspeed 停留速度(取值范围0-5，从快到慢)
 //  stoptime 停留时间(单位毫秒)
 //  istitle 是否标题
typedef long (_stdcall *_SZRC_MakeTextObject)(long ObjectIndex, long width, long height, 
		char* str, char* fontname, long fontsize, long fontcolor, long fontstyle, long wordwrap, long alignment,
		long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime, long istitle);

// ====引入动作方式列表(数值从0开始)====
//    0 = '随机'
//    1 = '立即显示,
//    2 = '左滚显示'
//    3 = '上滚显示'
//    4 = '右滚显示'
//    5 = '下滚显示'
//    6 = '连续左滚显示'
//    7 = '连续上滚显示'
//    8 = '中间向上下展开',
//    9 = '中间向两边展开',
//   10 = '中间向四周展开',
//   11 = '从右向左移入',
//   12 = '从左向右移入',
//   13 = '从左向右展开',
//   14 = '从右向左展开',
//   15 = '从右上角移入',
//   16 = '从右下角移入',
//   17 = '从左上角移入',
//   18 = '从左下角移入',
//   19 = '从上向下移入',
//   20 = '从下向上移入',
//   21 = '横向百叶窗',
//   22 = '纵向百叶窗',
// =====================================

// ====引出动作方式列表(数值从0开始)====
//    0 = '随机'
//    1 = '不消失'
//    2 = '立即消失'
//    3 = '上下向中间合拢'
//    4 = '两边向中间合拢'
//    5 = '四周向中间合拢'
//    6 = '从左向右移出'
//    7 = '从右向左移出'
//    8 = '从右向左合拢'
//    9 = '从左向右合拢'
//   10 = '从右上角移出'
//   11 = '从右下角移出'
//   12 = '从左上角移出'
//   13 = '从左下角移出'
//   14 = '从下向上移出'
//   15 = '从上向下移出'
//   16 = '横向百叶窗'
//   17 = '纵向百叶窗'
// =====================================

// ====停留动作方式列表(数值从0开始)====
//    0 = '静态显示'
//    1 = '闪烁显示'
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