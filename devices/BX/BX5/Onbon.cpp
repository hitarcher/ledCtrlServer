#include "stdafx.h"
#include "Onbon.h"
#include "Obasic_types.h"
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <fstream>

#define NSCREEN_PX	1//显示屏类型；双基色；单基色时为1；

Onbon::Onbon(void)
{
	ret = -1;
}

Onbon::~Onbon(void)
{
	bxDual_ReleaseSdk();
}

BOOL Onbon::InitOnbonSdk()
{
	hdll = ::LoadLibrary("bx_sdk_dual.dll");
	if (hdll == NULL)
	{
		AfxMessageBox("加载动态库bx_sdk_dual.dll失败");
		return FALSE;
	}
	bxDual_InitSdk = (PbxDual_InitSdk)GetProcAddress(hdll, "bxDual_InitSdk");
	bxDual_ReleaseSdk = (PbxDual_ReleaseSdk)GetProcAddress(hdll, "bxDual_ReleaseSdk");
	bxDual_program_setScreenParams_G56 = (PbxDual_program_setScreenParams_G56)GetProcAddress(hdll, "bxDual_program_setScreenParams_G56");
	bxDual_cmd_tcpPing = (PbxDual_cmd_tcpPing)GetProcAddress(hdll, "bxDual_cmd_tcpPing");
	bxDual_cmd_ofsStartFileTransf = (PbxDual_cmd_ofsStartFileTransf)GetProcAddress(hdll, "bxDual_cmd_ofsStartFileTransf");
	bxDual_cmd_ofsWriteFile = (PbxDual_cmd_ofsWriteFile)GetProcAddress(hdll, "bxDual_cmd_ofsWriteFile");
	bxDual_cmd_ofsEndFileTransf = (PbxDual_cmd_ofsEndFileTransf)GetProcAddress(hdll, "bxDual_cmd_ofsEndFileTransf");
	bxDual_program_deleteProgram = (PbxDual_program_deleteProgram)GetProcAddress(hdll, "bxDual_program_deleteProgram");
	bxDual_cmd_uart_ofsStartFileTransf = (PbxDual_cmd_uart_ofsStartFileTransf)GetProcAddress(hdll, "bxDual_cmd_uart_ofsStartFileTransf");
	bxDual_cmd_uart_ofsEndFileTransf = (PbxDual_cmd_uart_ofsEndFileTransf)GetProcAddress(hdll, "bxDual_cmd_uart_ofsEndFileTransf");

	bxDual_dynamicAreaS_AddTxtDetails_6G = (PbxDual_dynamicAreaS_AddTxtDetails_6G)GetProcAddress(hdll, "bxDual_dynamicAreaS_AddTxtDetails_6G");
	bxDual_dynamicAreaS_AddTxtDetails_WithProgram_6G = (PbxDual_dynamicAreaS_AddTxtDetails_WithProgram_6G)GetProcAddress(hdll, "bxDual_dynamicAreaS_AddTxtDetails_WithProgram_6G");
	bxDual_dynamicAreaS_AddAreaPic_6G = (PbxDual_dynamicAreaS_AddAreaPic_6G)GetProcAddress(hdll, "bxDual_dynamicAreaS_AddAreaPic_6G");
	bxDual_dynamicAreaS_AddAreaPic_WithProgram_6G = (PbxDual_dynamicAreaS_AddAreaPic_WithProgram_6G)GetProcAddress(hdll, "bxDual_dynamicAreaS_AddAreaPic_WithProgram_6G");
	bxDual_dynamicArea_DelArea_6G = (PbxDual_dynamicArea_DelArea_6G)GetProcAddress(hdll, "bxDual_dynamicArea_DelArea_6G");
	bxDual_dynamicArea_DelAreas_6G = (PbxDual_dynamicArea_DelAreas_6G)GetProcAddress(hdll, "bxDual_dynamicArea_DelAreas_6G");
	bxDual_program_IntegrateProgramFile_G6 = (PbxDual_program_IntegrateProgramFile_G6)GetProcAddress(hdll, "bxDual_program_IntegrateProgramFile_G6");
	bxDual_program_deleteProgram_G6 = (PbxDual_program_deleteProgram_G6)GetProcAddress(hdll, "bxDual_program_deleteProgram_G6");
	bxDual_program_addProgram_G6 = (PbxDual_program_addProgram_G6)GetProcAddress(hdll, "bxDual_program_addProgram_G6");
	bxDual_program_addArea_G6 = (PbxDual_program_addArea_G6)GetProcAddress(hdll, "bxDual_program_addArea_G6");
	bxDual_program_pictureAreaAddPic_G6 = (PbxDual_program_pictureAreaAddPic_G6)GetProcAddress(hdll, "bxDual_program_pictureAreaAddPic_G6");
	bxDual_program_picturesAreaAddTxt_G6 = (PbxDual_program_picturesAreaAddTxt_G6)GetProcAddress(hdll, "bxDual_program_picturesAreaAddTxt_G6");
	bxDual_program_timeAreaAddContent_G6 = (PbxDual_program_timeAreaAddContent_G6)GetProcAddress(hdll, "bxDual_program_timeAreaAddContent_G6");
	bxDual_program_timeAreaAddAnalogClock_G6 = (PbxDual_program_timeAreaAddAnalogClock_G6)GetProcAddress(hdll, "bxDual_program_timeAreaAddAnalogClock_G6");

	bxDual_program_addProgram = (PbxDual_program_addProgram)GetProcAddress(hdll, "bxDual_program_addProgram");
	bxDual_program_AddArea = (PbxDual_program_AddArea)GetProcAddress(hdll, "bxDual_program_AddArea");
	bxDual_program_picturesAreaAddTxt = (PbxDual_program_picturesAreaAddTxt)GetProcAddress(hdll, "bxDual_program_picturesAreaAddTxt");
	bxDual_program_pictureAreaAddPic = (PbxDual_program_pictureAreaAddPic)GetProcAddress(hdll, "bxDual_program_pictureAreaAddPic");
	bxDual_program_timeAreaAddContent = (PbxDual_program_timeAreaAddContent)GetProcAddress(hdll, "bxDual_program_timeAreaAddContent");
	bxDual_program_timeAreaAddAnalogClock = (PbxDual_program_timeAreaAddAnalogClock)GetProcAddress(hdll, "bxDual_program_timeAreaAddAnalogClock");
	bxDual_dynamicArea_AddAreaWithTxt_5G = (PbxDual_dynamicArea_AddAreaWithTxt_5G)GetProcAddress(hdll, "bxDual_dynamicArea_AddAreaWithTxt_5G");
	bxDual_dynamicArea_AddAreaWithPic_5G = (PbxDual_dynamicArea_AddAreaWithPic_5G)GetProcAddress(hdll, "bxDual_dynamicArea_AddAreaWithPic_5G");
	bxDual_program_IntegrateProgramFile = (PbxDual_program_IntegrateProgramFile)GetProcAddress(hdll, "bxDual_program_IntegrateProgramFile");

	bxDual_cmd_coerceOnOff = (PbxDual_cmd_coerceOnOff)GetProcAddress(hdll, "bxDual_cmd_coerceOnOff");
	bxDual_cmd_timingOnOff = (PbxDual_cmd_timingOnOff)GetProcAddress(hdll, "bxDual_cmd_timingOnOff");
	bxDual_cmd_coerceOnOff = (PbxDual_cmd_coerceOnOff)GetProcAddress(hdll, "bxDual_cmd_coerceOnOff");
	bxDual_cmd_cancelTimingOnOff = (PbxDual_cmd_cancelTimingOnOff)GetProcAddress(hdll, "bxDual_cmd_cancelTimingOnOff");
	bxDual_cmd_setBrightness = (PbxDual_cmd_setBrightness)GetProcAddress(hdll, "bxDual_cmd_setBrightness");
	bxDual_cmd_readControllerID = (PbxDual_cmd_readControllerID)GetProcAddress(hdll, "bxDual_cmd_readControllerID");
	bxDual_cmd_screenLock = (PbxDual_cmd_screenLock)GetProcAddress(hdll, "bxDual_cmd_screenLock");
	bxDual_cmd_programLock = (PbxDual_cmd_programLock)GetProcAddress(hdll, "bxDual_cmd_programLock");
	bxDual_cmd_check_controllerStatus = (PbxDual_cmd_check_controllerStatus)GetProcAddress(hdll, "bxDual_cmd_check_controllerStatus");
	bxDual_cmd_setPassword = (PbxDual_cmd_setPassword)GetProcAddress(hdll, "bxDual_cmd_setPassword");
	bxDual_cmd_deletePassword = (PbxDual_cmd_deletePassword)GetProcAddress(hdll, "bxDual_cmd_deletePassword");
	bxDual_cmd_setBtnFunc = (PbxDual_cmd_setBtnFunc)GetProcAddress(hdll, "bxDual_cmd_setBtnFunc");
	bxDual_cmd_setDelayTime = (PbxDual_cmd_setDelayTime)GetProcAddress(hdll, "bxDual_cmd_setDelayTime");
	bxDual_cmd_setTimingReset = (PbxDual_cmd_setTimingReset)GetProcAddress(hdll, "bxDual_cmd_setTimingReset");

	//BX-E

	hBX_EDll = ::LoadLibrary("BxEDLL.dll");
	if (hdll == NULL)
	{
		AfxMessageBox("加载动态库BxEDLL.dll失败");
		return FALSE;
	}
	m_bSendBusy = FALSE;
	api_SetScreenParameter = (SetScreenParameter)GetProcAddress(hBX_EDll, "SetScreenParameter");
	api_SetScreenState = (SetScreenState)GetProcAddress(hBX_EDll, "SetScreenState");
	api_SetScreenLight = (SetScreenLight)GetProcAddress(hBX_EDll, "SetScreenLight");
	api_SetScreenDial = (SetScreenDial)GetProcAddress(hBX_EDll, "SetScreenDial");
	api_SetScreenTitle = (SetScreenTitle)GetProcAddress(hBX_EDll, "SetScreenTitle");
	api_SetDynamicAttrib = (SetDynamicAttrib)GetProcAddress(hBX_EDll, "SetDynamicAttrib");
	api_TranDynamicData = (TranDynamicData)GetProcAddress(hBX_EDll, "TranDynamicData");
	api_TranDynamicString = (TranDynamicString)GetProcAddress(hBX_EDll, "TranDynamicString");
	api_GetAllDataHead = (GetAllDataHead)GetProcAddress(hBX_EDll, "GetAllDataHead");
	api_GetProgramHead = (GetProgramHead)GetProcAddress(hBX_EDll, "GetProgramHead");
	api_GetCurDataTime = (GetCurDataTime)GetProcAddress(hBX_EDll, "GetCurDataTime");
	api_SetScreenBmpText = (SetScreenBmpText)GetProcAddress(hBX_EDll, "SetScreenBmpText");
	api_SendTCPIPData = (SendTCPIPData)GetProcAddress(hBX_EDll, "SendTCPIPData");
	api_ResiveCurTime = (ResiveCurTime)GetProcAddress(hBX_EDll, "ResiveCurTime");
	api_UnionAreaDataToFile = (UnionAreaDataToFile)GetProcAddress(hBX_EDll, "UnionAreaDataToFile");
	api_SetScreenDateTime = (SetScreenDateTime)GetProcAddress(hBX_EDll, "SetScreenDateTime");
	api_SetScreenTimer = (SetScreenTimer)GetProcAddress(hBX_EDll, "SetScreenTimer");

	ret = bxDual_InitSdk();//初始化动态库
	if (ret != 0)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL Onbon::PublishPrograms(CString strIP, CString strPort, CString strLedType, CString strDeviceModel, CString strPrgm, int nWidth, int nHieght, int nFontSize, int nEffect, int nPlaySpeed, int nStayTime)
{
	BOOL IsSUccess = FALSE;
	if (strDeviceModel == "BX-5"|| strDeviceModel == "BX-6")
	{
		Ouint16 c_type = 0;
		Ping_data retdata;
		unsigned char ip[20] = { 0 };
		unsigned short port = atoi(strPort);
		memcpy(ip, strIP.GetBuffer(0), strIP.GetLength());
		ret = 0;
		ret = bxDual_cmd_tcpPing(ip, port, &retdata);
		if (ret != 0)
		{
			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[bxDual_cmd_tcpPing]--通过TCP方式获取到控制器相关属性和IP地址失败！[%s]-[%d]", ip, port);
			return FALSE;
		}
		else
		{
			c_type = retdata.ControllerType;
			BYTE cmb_ping_Color = 1;
			if (retdata.Color == 1) { cmb_ping_Color = 1; }
			else if (retdata.Color == 3) { cmb_ping_Color = 2; }
			else if (retdata.Color == 7) { cmb_ping_Color = 3; }
			else { cmb_ping_Color = 4; }
			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[bxDual_program_setScreenParams_G56]--[%d],[%d]", (E_ScreenColor_G56)cmb_ping_Color, retdata.ControllerType);
			ret = bxDual_program_setScreenParams_G56((E_ScreenColor_G56)cmb_ping_Color, retdata.ControllerType, eDOUBLE_COLOR_PIXTYPE_1);
			if (ret != 0)
			{
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[bxDual_program_setScreenParams_G56]--设置屏相关属性失败");
				return FALSE;
			}
			if (strDeviceModel == "BX-5")
			{

				IsSUccess = addProgram_G5();
				if (IsSUccess == FALSE)
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[addProgram_G5]--添加屏幕节目失败");
					return FALSE;
				}
				IsSUccess = addArea_G5(0, 0, 0, 0, nWidth, nHieght);
				if (IsSUccess == FALSE)
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[addArea_G5]--添加屏幕区域失败");
					return FALSE;
				}
				IsSUccess = addAreaPicture_G5(0, (unsigned char*)strPrgm.GetBuffer(0), nFontSize, nPlaySpeed);
				if (IsSUccess == FALSE)
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[addAreaPicture_G5]--添加文本失败");
					return FALSE;
				}
				IsSUccess = tcp_send_program_G5(ip, port);
				if (IsSUccess == FALSE)
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[tcp_send_program_G5]--发送节目失败");
					return FALSE;
				}
			}
			else
			{
				IsSUccess = addProgram_G6();
				if (IsSUccess == FALSE)
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[addProgram_G6]--添加屏幕节目失败");
					return FALSE;
				}
				IsSUccess = addArea_G6(0, 0, 0, 0, nWidth, nHieght);
				if (IsSUccess == FALSE)
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[addArea_G6]--添加屏幕区域失败");
					return FALSE;
				}
				IsSUccess = addAreaPicture_G6(0, (unsigned char*)strPrgm.GetBuffer(0), nFontSize, nPlaySpeed);
				if (IsSUccess == FALSE)
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[addAreaPicture_G6]--添加文本失败");
					return FALSE;
				}
				IsSUccess = tcp_send_program_G6(ip, port);
				if (IsSUccess == FALSE)
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[tcp_send_program_G6]--发送节目失败");
					return FALSE;
				}
			}
		}
	}
	else if (strDeviceModel == "BX-5E")
	{
		EQareaframeHeader Frame;
		Frame.AreaFFlag = 0; //如果此字段为 0x00，则以下 区域边框属性不发送
		Frame.AreaFDispStyle = 0;//边框显示方式： 0x00 –闪烁 0x01 –顺时针转动 0x02 –逆时针转动 0x03 –闪烁加顺时针转动 0x04 –闪烁加逆时针转动 0x05 –红绿交替闪烁 0x06 –红绿交替转动 0x07 –静止打出 
		Frame.AreaFDispSpeed = 0;//边框显示速度 1-7
		Frame.AreaFMoveStep = 0;//边框移动步长，单位为点，此参 数范围为 1~16 
		Frame.AreaFWidth = 0;//边框组元宽度，此参数范围为 1~8 
		Frame.AreaFBackup = 0;//备用字 0
		EQfontData oFont;
		oFont.arrMode = eSINGLELINE;//排列方式--单行多行  E_arrMode::	eSINGLELINE,   //单行 eMULTILINE,    //多行
		oFont.fontSize = nFontSize;//字体大小
		oFont.color = eRED;//字体颜色 E_Color_G56 此通过此枚举值可以直接配置七彩色，如果大于枚举范围使用RGB888模式
		oFont.fontBold = false;//是否为粗体
		oFont.fontItalic = false;//是否为斜体
		oFont.tdirection = pNORMAL;//文字方向
		oFont.txtSpace = 0;//文字间隔   
		oFont.Valign = 2;//横向对齐方式（0系统自适应、1左对齐、2居中、3右对齐）
		oFont.Halign = 2;//纵向对齐方式（0系统自适应、1上对齐、2居中、3下对齐）
		Ouint16 uRelateProgID[1];  uRelateProgID[0] = 0;
		unsigned char ip5e[20] = { 0 };
		unsigned short port5e = atoi(strPort);
		memcpy(ip5e, strIP.GetBuffer(0), strIP.GetLength());
		int nStunt5e = 18;
		if (nEffect == 1)   //立即显示
		{
			nStunt5e = 1;
		}
		else if (nEffect == 2)   //左移
		{
			nStunt5e = 4;
		}
		else if (nEffect == 3)   //下移
		{
			nStunt5e = 32;
		}
		else if (nEffect == 4)    //右移
		{
			nStunt5e = 18;
		}
		else if (nEffect == 5)    //上移
		{
			nStunt5e = 6;
		}
		else
		{
			nStunt5e = 4;
		}
		//| 参数 | 说明 |
		//	| ---------------- - | ------------------------------------------------------------ |
		//	| pIP | 控制卡IP |
		//	| nPort | 控制卡端口 |
		//	| color | 屏型 |
		//	| uAreaId | 区域编号 |
		//	| RunMode | 动态区运行模式 0— 动态区数据循环显示。 1— 动态区数据显示完成后静止显 示最后一页数据。 2— 动态区数据循环显示，超过设 定时间后数据仍未更新时不再 显示 3— 动态区数据循环显示，超过设 定时间后数据仍未更新时显示 Logo 信息, Logo 信息即为动 态区域的最后一页信息 4— 动态区数据顺序显示，显示完 最后一页后就不再显示 |
		//	| Timeout | 动态区数据超时时间，单位为秒 |
		//	| RelateAllPro | 当该字节为 1 时，所有异步节目 播放时都允许播放该动态区域； 为 0 时，绑定节目 |
		//	| RelateProNum | 动态区域关联了多少个异步节目 |
		//	| RelateProSerial | 动态区域关联的异步节 目的编号 |
		//	| ImmePlay | 是否立即播放 该字节为 0 时，该动态区域与异 步节目一起播放， 该字节为 1 时，异步节目停止播 放，仅播放该动态区域 |
		//	| uAreaX | 区域左上角横坐标 |
		//	| uAreaY | 区域左上角纵坐标 |
		//	| uWidth | 区域宽度 |
		//	| uHeight | 区域高度 |
		//	| oFrame | 区域边框属性[EQareaframeHeader](#EQareaframeHeader) |
		//	| DisplayMode | 显示方式 |
		//	| ClearMode | 退出方式 / 清屏方式，固定 0 |
		//	| Speed | 速度等级 1 - 65 |
		//	| StayTime | 停留时间，单位为 10ms |
		//	| RepeatTime | 重复次数 |
		//	| oFont | 字体格式[EQfontData](#EQfontData) |
		//	| fontName | 字体名称 |
		//	| strAreaTxtContent | 显示文本 |
		int err = 0;
		nPlaySpeed = (10 - nPlaySpeed) * 6 + 1;
		if (strLedType == "1")
		{
			err = bxDual_dynamicArea_AddAreaWithTxt_5G(ip5e, port5e, eSCREEN_COLOR_SINGLE, 1, 0, 0, 1, 0, uRelateProgID,
				1, 0, 0, nWidth, nHieght, Frame, nStunt5e, 0, nPlaySpeed,0, 0, oFont, (Ouint8*)"宋体", (unsigned char*)strPrgm.GetBuffer(0));
			if (err != 0)
			{
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[PublishPrograms]--bxDual_dynamicArea_AddAreaWithTxt_5G单色屏发送节目失败");
				return FALSE;
			}
		}
		else
		{
			err = bxDual_dynamicArea_AddAreaWithTxt_5G(ip5e, port5e, eSCREEN_COLOR_DOUBLE, 1, 0, 0, 1, 0, uRelateProgID,
				1, 0, 0, nWidth, nHieght, Frame, nStunt5e, 0, nPlaySpeed, 0, 0, oFont, (Ouint8*)"宋体", (unsigned char*)strPrgm.GetBuffer(0));
			if (err != 0)
			{
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[PublishPrograms]--bxDual_dynamicArea_AddAreaWithTxt_5G双色屏发送节目失败");
				return FALSE;
			}
		}
	}
	else if (strDeviceModel == "BX-6E")
	{
		EQareaHeader_G6 oAreaHeader_G6;
		oAreaHeader_G6.AreaType = 0x10; //0x10 动态区域

		oAreaHeader_G6.AreaX = 0;
		oAreaHeader_G6.AreaY = 0;
		oAreaHeader_G6.AreaWidth = nWidth;
		oAreaHeader_G6.AreaHeight = nHieght;
		//AreaFrame N 区域边框属性，详细参考
		oAreaHeader_G6.BackGroundFlag = 0x00;
		oAreaHeader_G6.Transparency = 101;
		oAreaHeader_G6.AreaEqual = 0x00;

		//Ouint8* strSoundTxt = (Ouint8*)"仰邦。";
		//Ouint8 nSize = sizeof(strSoundTxt);
		//Ouint8 nStrLen = strlen((const char*)strSoundTxt);
		//oAreaHeader_G6.stSoundData.SoundDataLen = nStrLen;		// 4 语音数据长度; 只有 SoundFlag（是否使能语音播放）为 1 时才发送该字节，否则不发送
		//oAreaHeader_G6.stSoundData.SoundData = strSoundTxt;			// N 语音数据只有 SoundFlag（是否使能语音播放）为 1 时才发送该字节，否则不发送
		//{
		//	oAreaHeader_G6.stSoundData.SoundFlag = 0x00;	//1 0x00 是否使能语音播放;0 表示不使能语音; 1 表示播放下文中;
		//	oAreaHeader_G6.stSoundData.SoundPerson = 0x01;	//1 0x00 发音人 该值范围是 0 - 5，共 6 种选择只有 SoundFlag（是否使能语音播放）为 1 时才发送该字节，否则不发送该值默认为 0
		//	oAreaHeader_G6.stSoundData.SoundVolum = 1;		//1 0x05 音量该值范围是 0~10，共 11 种，0表示静音只有 SoundFlag（是否使能语音播放）为 1 时才发送该字节，否则不发送该值默认为 5
		//	oAreaHeader_G6.stSoundData.SoundSpeed = 0x2;	//1 0x05 语速该值范围是 0~10，共 11 种只有 SoundFlag（是否使能语音播放）为 1 时才发送该字节，否则不发送该值默认为 5
		//	oAreaHeader_G6.stSoundData.SoundDataMode = 0x00;//1 0x00 SoundData 的编码格式：该值意义如下：0x00 GB2312; 0x01 GBK; 0x02 BIG5; 0x03 UNICODE只有 SoundFlag（是否使能语音播放）为 1 时才发送该字节，否则不发送
		//	oAreaHeader_G6.stSoundData.SoundReplayTimes = 0x01;// 0xffffffff;	//4 0x00000000 重播次数该值为 0，表示播放 1 次该值为 1，表示播放 2 次
		//													   //......
		//													   //该值为 0xffffffff，表示播放无限次只有 SoundFlag（是否使能语播放）为 1 时才发送该字节，否则不发送该值默认为 0
		//	oAreaHeader_G6.stSoundData.SoundReplayDelay = 200;	//4 0x00000000 重播时间间隔该值表示两次播放语音的时间间隔，单位为 10ms只有 SoundFlag（是否使能语音播放）为 1 时才发送该字节，否则不发送该值默认为 0
		//	oAreaHeader_G6.stSoundData.SoundReservedParaLen = 0x03;//1 0x03 语音参数保留参数长度
		//	oAreaHeader_G6.stSoundData.Soundnumdeal = 0x00;		//1 0 0：自动判断1：数字作号码处理 2：数字作数值处理只有当 SoundFlag 为 1 且SoundReservedParaLen不为 0才发送此参数
		//	oAreaHeader_G6.stSoundData.Soundlanguages = 0x00;		// 1 0 0：自动判断语种1：阿拉伯数字、度量单位、特殊符号等合成为中文2：阿拉伯数字、度量单位、特殊符号等合成为英文只有当 SoundFlag 为 1 且 SoundReservedParaLen不为 0才发送此参数（目前只支持中英文）
		//	oAreaHeader_G6.stSoundData.Soundwordstyle = 0x00;		// 1 0 0：自动判断发音方式1：字母发音方式2：单词发音方式只有当 SoundFlag 为 1 且SoundReservedParaLen不为 0才发送此参数
		//	oAreaHeader_G6.stSoundData.SoundDataLen = nStrLen;		// 4 语音数据长度; 只有 SoundFlag（是否使能语音播放）为 1 时才发送该字节，否则不发送
		//	oAreaHeader_G6.stSoundData.SoundData = strSoundTxt;			// N 语音数据只有 SoundFlag（是否使能语音播放）为 1 时才发送该字节，否则不发送
		//}

		EQpageHeader_G6 stPageHeader;
		stPageHeader.PageStyle = 0x00;
		stPageHeader.DisplayMode = 0x04;
		stPageHeader.ClearMode = 0x00;
		stPageHeader.Speed = nPlaySpeed = (10 - nPlaySpeed) * 6 + 1;;
		stPageHeader.StayTime = 0;
		stPageHeader.RepeatTime = 1;
		stPageHeader.ValidLen = oAreaHeader_G6.AreaWidth;
		stPageHeader.CartoonFrameRate = 0x00;
		stPageHeader.BackNotValidFlag = 0x00;
		stPageHeader.arrMode = eSINGLELINE; //eMULTILINE;//
		stPageHeader.fontSize = nFontSize;
		stPageHeader.color = eRED;
		stPageHeader.fontBold = false;
		stPageHeader.fontItalic = false;
		stPageHeader.tdirection = pNORMAL;
		stPageHeader.txtSpace = 0;
		stPageHeader.Valign = 0;
		stPageHeader.Halign = 0;

		Ouint16 nAreaID = 0;
		Ouint16 uRelateProgID[1];  uRelateProgID[0] = 0;
		int err = 0;
		unsigned char ip6e[20] = { 0 };
		unsigned short port6e = atoi(strPort);
		memcpy(ip6e, strIP.GetBuffer(0), strIP.GetLength());
		DynamicAreaParams oAreaParams_1;
		oAreaParams_1.uAreaId = 0;
		oAreaParams_1.oAreaHeader_G6 = oAreaHeader_G6;
		oAreaParams_1.stPageHeader = stPageHeader;
		oAreaParams_1.strAreaTxtContent = (unsigned char*)strPrgm.GetBuffer(0);
		oAreaParams_1.fontName = (Ouint8*)"宋体";
		DynamicAreaParams arrParams[1];
		arrParams[0] = oAreaParams_1;
		if (strLedType == "1")
		{
			err = bxDual_dynamicAreaS_AddTxtDetails_6G(ip6e, port6e, eSCREEN_COLOR_SINGLE, 1, arrParams);
			if (err != 0)
			{
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[bxDual_dynamicAreaS_AddTxtDetails_6G]--单色屏发送节目失败");
				return FALSE;
			}
		}
		else
		{

			err = bxDual_dynamicAreaS_AddTxtDetails_6G(ip6e, port6e, eSCREEN_COLOR_DOUBLE, 1, arrParams);
			if (err != 0)
			{
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[bxDual_dynamicAreaS_AddTxtDetails_6G]--双色屏发送节目失败");
				return FALSE;
			}
		}
	}
	else if (strDeviceModel == "BX-E")
	{
		//if (m_bSendBusy == FALSE)
		//{
		//	m_bSendBusy = TRUE;
		//	int nSendResult = -1;
		//	int nStunt = 18;
		//	if (nEffect == 1)   //立即显示
		//	{
		//		nStunt = 1;
		//	}
		//	else if (nEffect == 2)   //左移
		//	{
		//		nStunt = 18;
		//	}
		//	else if (nEffect == 3)   //下移
		//	{
		//		nStunt = 11;
		//	}
		//	else if (nEffect == 4)    //右移
		//	{
		//		nStunt = 19;
		//	}
		//	else if (nEffect == 5)    //上移
		//	{
		//		nStunt = 8;
		//	}
		//	else
		//	{
		//		nStunt = 18;
		//	}
		//	/*
		//	函数作用：得到显示屏数据的头信息，保存到文件pFileName中。
		//	函数说明：
		//	nScreenNO：显示屏屏号；从1开始
		//	nProgramCount：显示屏的节目个数；
		//	pFileName：显示屏头信息保存的文件名
		//	*/
		//	api_GetAllDataHead(1, 1, "SendAllDataHead1");
		//	/*
		//	函数说明：合并显示区域信息文件
		//	参数说明：
		//	pSourceFile：预合并信息文件名称
		//	pUnionedFile：合并目标文件名称。
		//	bDeleted：0：在原文件下添加合并信息文件；1：删除原文件信息，重新创建合并信息文件
		//	返回值：无
		//	*/
		//	api_UnionAreaDataToFile("SendAllDataHead1", "SendAllData1", 1);
		//	/*
		//	函数作用：取得显示屏当前节目的头信息，在添加显示区域信息前添加。
		//	参数说明：
		//	nProgramOrd：节目序号，从0开始计数
		//	nAreaCount：显示屏中区域的个数。在一个显示屏中的动态区域只可以放置一个。表盘、字幕可以放置多个，但是总共最多可以有8个区域。
		//	nProgPlayMode：节目播放模式，0：定长播放；1：定时播放
		//	nProgPlayLength：节目定长播放时的播放长度；单位为秒；1~ 65535
		//	nProgWeekAttrib：节目定时播放时的星期播放属性，从周一到周日循环，对应该字节内的低位(bit0)到高位(bit6)。如果如果周一播放，则bit0=1，否则bit0=0；依次如果周日播放bit6=1，否则bit6=0；
		//	nPlayHour：当天该节目开始播放的小时值；
		//	nPlayHour：当天该节目开始播放的分值；
		//	nPlayHour：当天该节目开始播放的秒值；
		//	nPlayHour：当天该节目结束播放的小时值；
		//	nPlayHour：当天该节目结束播放的分值；
		//	nPlayHour：当天该节目结束播放的秒值；
		//	pFileName：节目头信息保存的文件名称
		//	*/
		//	api_GetProgramHead(0, 1, 0, 65534, 0x7F, 4, 0, 0, 22, 0, 0, "ProgramHead0");
		//	api_UnionAreaDataToFile("ProgramHead0", "SendAllData1", 0);
		//	/*
		//	函数作用：转换字幕区域显示信息；
		//	参数说明：
		//	nX：字幕区域的横坐标
		//	nY：字幕区域的纵坐标
		//	nWidth：字幕区域的长度；
		//	nHeight：字幕区域的高度；
		//	nScreenType：显示屏类型；1：单基色；2：双基色
		//	nMkType：点阵类型；1：R+G型；2：G+R型；
		//	pFontName：字幕区域显示字体；支持Windows所有字体
		//	nFontSize：字幕区域显示字号
		//	nFontColor：字幕区域显示颜色; 1：红色；2：绿色；3：黄色
		//	bBold：粗体
		//	bItalic：斜体
		//	bUnderLine：下划线
		//	pTitle：字幕区域显示的字幕滚动信息
		//	nStunt：字幕区域显示特技；具体特技特征字见注1；
		//	nRunSpeed：字幕区域信息运行速度
		//	nShowTime：字幕区域信息停留时间
		//	pFileName：字幕区域信息保存的文件名；
		//	*/
		//	api_SetScreenTitle(nWidth, 0, nWidth, nHieght, atoi(strLedType), 1, "宋体", nFontSize, 1, 0, 0, 0, strPrgm.GetBuffer(0), nStunt, nPlaySpeed, 0, "SendDataTitle1");
		//	api_UnionAreaDataToFile("SendDataTitle1", "SendAllData1", 0);

		//	api_GetCurDataTime("CurTimeData1");
		//	api_UnionAreaDataToFile("CurTimeData1", "SendAllData1", 0);
		//	/*
		//	函数作用：TCP/IP模式下发送信息
		//	参数说明：
		//	pTCPAddress：显示屏IP地址；格式为“***.***.***.***”
		//	nPort：显示屏端口信息
		//	nSendType：通讯数据类型；
		//	0xC1：设置显示屏参数
		//	0xC8：设置显示屏亮度
		//	0xD1：发送显示屏全部数据
		//	0xD2：更新显示屏动态区域数据
		//	0xC4：强制开、关机
		//	0xE6：修改IP地址信息
		//	0xCD：校正时间
		//	nWidth：显示屏的长度；
		//	nHeight：显示屏的高度；
		//	nScreenType：显示屏类型；1：单基色；2：双基色
		//	pSendBufFile：显示屏数据、命令信息
		//	返回值：
		//	0：向显示屏发送信息成功。
		//	1：向显示屏发送信息失败。
		//	*/
		//	nSendResult = api_SendTCPIPData(strIP.GetBuffer(0), atoi(strPort), 0xD1, nWidth, nHieght, atoi(strLedType), "SendAllData1");
		//	if (nSendResult == 0)
		//	{
		//		m_bSendBusy = FALSE;
		//	}
		//	else
		//	{
		//		m_bSendBusy = FALSE;
		//		return FALSE;
		//	}
		//}
		//else
		//{
		//	return FALSE;
		//}
		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[PublishPrograms]--BX-E类型板卡暂不支持");
		return FALSE;
	}
	else
	{
		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[PublishPrograms]--仰邦板卡类型匹配失败");
		return FALSE;
	}
	return TRUE;
}

void Onbon::OnbonReleaseSdk()
{
	bxDual_ReleaseSdk();
}
//添加节目
BOOL Onbon::addProgram_G5()
{
	int n_ret = 0;
	EQprogramHeader header;
	header.FileType = 0x00;
	header.ProgramID = 0;
	header.ProgramStyle = 0x00;
	header.ProgramPriority = 0x00;
	header.ProgramPlayTimes = 1;
	header.ProgramTimeSpan = 0;
	header.ProgramWeek = 0xff;
	header.ProgramLifeSpan_sy = 0xffff;
	header.ProgramLifeSpan_sm = 0x03;
	header.ProgramLifeSpan_sd = 0x05;
	header.ProgramLifeSpan_ey = 0xffff;
	header.ProgramLifeSpan_em = 0x04;
	header.ProgramLifeSpan_ed = 0x12;
	n_ret = bxDual_program_addProgram(&header);
	if (n_ret != 0)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL Onbon::addProgram_G6()
{
	int n_ret = 0;
	EQprogramHeader_G6 pHeader;
	pHeader.FileType = 0x00;
	pHeader.ProgramID = 0;
	pHeader.ProgramStyle = 0x00;
	pHeader.ProgramPriority = 0x00;
	pHeader.ProgramPlayTimes = 1;
	pHeader.ProgramTimeSpan = 0;
	pHeader.SpecialFlag = 0;
	pHeader.CommExtendParaLen = 0x00;
	pHeader.ScheduNum = 0;
	pHeader.LoopValue = 0;
	pHeader.Intergrate = 0x00;
	pHeader.TimeAttributeNum = 0x00;
	pHeader.TimeAttribute0Offset = 0x0000;
	pHeader.ProgramWeek = 0xff;
	pHeader.ProgramLifeSpan_sy = 0xffff;
	pHeader.ProgramLifeSpan_sm = 0x03;
	pHeader.ProgramLifeSpan_sd = 0x14;
	pHeader.ProgramLifeSpan_ey = 0xffff;
	pHeader.ProgramLifeSpan_em = 0x03;
	pHeader.ProgramLifeSpan_ed = 0x14;
	//pHeader.PlayPeriodGrpNum=0;

	n_ret=bxDual_program_addProgram_G6(&pHeader);
	if (n_ret != 0)
	{
		return FALSE;
	}
	return TRUE;
}
//添加区域
BOOL Onbon::addArea_G5(Ouint16 AreaID, Ouint8 AreaType, Ouint16 AreaX, Ouint16 AreaY, Ouint16 AreaWidth, Ouint16 AreaHeight)
{
	int n_ret = 0;
	Ouint16 nAreaID = AreaID;
	EQareaHeader aheader;
	aheader.AreaType = AreaType;
	aheader.AreaX = AreaX;
	aheader.AreaY = AreaY;
	aheader.AreaWidth = AreaWidth;
	aheader.AreaHeight = AreaHeight;
	n_ret = bxDual_program_AddArea(nAreaID, &aheader);
	if (n_ret != 0)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL Onbon::addArea_G6(Ouint16 AreaID, Ouint8 AreaType, Ouint16 AreaX, Ouint16 AreaY, Ouint16 AreaWidth, Ouint16 AreaHeight)
{
	int n_ret = 0;
	Ouint16 nAreaID = AreaID;
	EQareaHeader_G6 aHeader1;
	aHeader1.AreaType = AreaType;
	aHeader1.AreaX = AreaX;
	aHeader1.AreaY = AreaY;
	aHeader1.AreaWidth = AreaWidth;
	aHeader1.AreaHeight = AreaHeight;
	aHeader1.BackGroundFlag = 0x00;
	aHeader1.Transparency = 101;
	aHeader1.AreaEqual = 0x00;
	n_ret =bxDual_program_addArea_G6(nAreaID, &aHeader1);
	if (n_ret != 0)
	{
		return FALSE;
	}
	return TRUE;
}
//添加文本
BOOL Onbon::addAreaPicture_G5(Ouint16 AreaID, Ouint8 str[], int nFontSize, int nPlaySpeed)
{
	int n_ret = 0;
	EQpageHeader pheader;
	pheader.PageStyle = 0x00;
	pheader.DisplayMode = 0x04;
	pheader.ClearMode = 0x01;
	pheader.Speed =(10-nPlaySpeed)*6+1;
	pheader.StayTime = 0;
	pheader.RepeatTime = 1;
	pheader.ValidLen = 0;
	pheader.arrMode = eSINGLELINE;
	pheader.fontSize = nFontSize;
	pheader.color = eRED;
	pheader.fontBold = false;
	pheader.fontItalic = false;
	pheader.tdirection = pNORMAL;
	pheader.txtSpace = 0;
	n_ret = bxDual_program_picturesAreaAddTxt(0, str, (Ouint8*)"宋体", &pheader);
	if (n_ret != 0)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL Onbon::addAreaPicture_G6(Ouint16 AreaID, Ouint8 str[], int nFontSize, int nPlaySpeed)
{
	int n_ret = 0;
	EQpageHeader_G6 pheader1;
	pheader1.PageStyle = 0x00;
	pheader1.DisplayMode = 0x04;
	pheader1.ClearMode = 0x01;
	pheader1.Speed = (10 - nPlaySpeed) * 6 + 1;;
	pheader1.StayTime = 0;
	pheader1.RepeatTime = 1;
	pheader1.ValidLen = 0;
	pheader1.CartoonFrameRate = 0x00;
	pheader1.BackNotValidFlag = 0x00;
	pheader1.arrMode = eSINGLELINE; //eMULTILINE;// 
	pheader1.fontSize = nFontSize;
	pheader1.color = E_Color_G56::eRED;   // E_Color_G56
	pheader1.fontBold = false;
	pheader1.fontItalic = false;
	pheader1.tdirection = pNORMAL;
	pheader1.txtSpace = 0;
	pheader1.Valign = 0;
	pheader1.Halign = 0;

	n_ret=bxDual_program_picturesAreaAddTxt_G6(AreaID, str, (Ouint8*)"宋体", &pheader1);
	if (n_ret != 0)
	{
		return FALSE;
	}
	return TRUE;
}
//发送节目
BOOL Onbon::tcp_send_program_G5(Ouint8* ip, Ouint16 port)
{
	EQprogram program;
	memset((void*)&program, 0, sizeof(program));
	ret = bxDual_program_IntegrateProgramFile(&program);
	if (ret != 0)
	{
		return FALSE;
	}
	Oint8 ret;
	ret = bxDual_cmd_ofsStartFileTransf(ip, port);
	if (ret != 0)
	{
		return FALSE;
	}
	ret = bxDual_cmd_ofsWriteFile(ip, port, program.fileName, program.fileType, program.fileLen, 1, program.fileAddre);
	if (ret != 0)
	{
		return FALSE;
	}
	ret = bxDual_cmd_ofsEndFileTransf(ip, port);
	if (ret != 0)
	{
		return FALSE;
	}
	ret = bxDual_program_deleteProgram();
	if (ret != 0)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL Onbon::tcp_send_program_G6(Ouint8* ip, Ouint16 port)
{
	Oint8 ret;
	EQprogram_G6 program;
	memset((void*)&program, 0, sizeof(program));
	ret = bxDual_program_IntegrateProgramFile_G6(&program);
	if (ret != 0)
	{
		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[tcp_send_program_G6]--bxDual_program_IntegrateProgramFile_G6 run error...");
		return FALSE;
	}

	ret = bxDual_cmd_ofsStartFileTransf(ip, port);
	if (ret != 0) 
	{
		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[tcp_send_program_G6]--cmd_ofsStartFileTransf run error...");
		return FALSE;
	}

	ret = bxDual_cmd_ofsWriteFile(ip, port, program.dfileName, program.dfileType, program.dfileLen, 1, program.dfileAddre);
	if (ret != 0) 
	{
		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[bxDual_cmd_ofsWriteFile]--cmd_ofsWriteFile run error...");
		return FALSE;
	}

	ret = bxDual_cmd_ofsWriteFile(ip, port, program.fileName, program.fileType, program.fileLen, 1, program.fileAddre);
	if (ret != 0) 
	{
		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[bxDual_cmd_ofsWriteFile]--cmd_ofsWriteFile run error...");
		return FALSE;
	}

	ret = bxDual_cmd_ofsEndFileTransf(ip, port);
	if (ret != 0) 
	{
		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[bxDual_cmd_ofsWriteFile]--cmd_ofsEndFileTransf run error...");
		return FALSE;
	}

	//删除本地内存中的节目
	ret = bxDual_program_deleteProgram_G6();
	if (ret != 0)
	{
		return FALSE;
	}
	return TRUE;
}