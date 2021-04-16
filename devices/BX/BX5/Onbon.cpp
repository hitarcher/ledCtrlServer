#include "stdafx.h"
#include "Onbon.h"
#include "Obasic_types.h"
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <fstream>

#define NSCREEN_PX	1//��ʾ�����ͣ�˫��ɫ������ɫʱΪ1��

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
		AfxMessageBox("���ض�̬��bx_sdk_dual.dllʧ��");
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
		AfxMessageBox("���ض�̬��BxEDLL.dllʧ��");
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

	ret = bxDual_InitSdk();//��ʼ����̬��
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
			LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[bxDual_cmd_tcpPing]--ͨ��TCP��ʽ��ȡ��������������Ժ�IP��ַʧ�ܣ�[%s]-[%d]", ip, port);
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
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[bxDual_program_setScreenParams_G56]--�������������ʧ��");
				return FALSE;
			}
			if (strDeviceModel == "BX-5")
			{

				IsSUccess = addProgram_G5();
				if (IsSUccess == FALSE)
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[addProgram_G5]--�����Ļ��Ŀʧ��");
					return FALSE;
				}
				IsSUccess = addArea_G5(0, 0, 0, 0, nWidth, nHieght);
				if (IsSUccess == FALSE)
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[addArea_G5]--�����Ļ����ʧ��");
					return FALSE;
				}
				IsSUccess = addAreaPicture_G5(0, (unsigned char*)strPrgm.GetBuffer(0), nFontSize, nPlaySpeed);
				if (IsSUccess == FALSE)
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[addAreaPicture_G5]--����ı�ʧ��");
					return FALSE;
				}
				IsSUccess = tcp_send_program_G5(ip, port);
				if (IsSUccess == FALSE)
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[tcp_send_program_G5]--���ͽ�Ŀʧ��");
					return FALSE;
				}
			}
			else
			{
				IsSUccess = addProgram_G6();
				if (IsSUccess == FALSE)
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[addProgram_G6]--�����Ļ��Ŀʧ��");
					return FALSE;
				}
				IsSUccess = addArea_G6(0, 0, 0, 0, nWidth, nHieght);
				if (IsSUccess == FALSE)
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[addArea_G6]--�����Ļ����ʧ��");
					return FALSE;
				}
				IsSUccess = addAreaPicture_G6(0, (unsigned char*)strPrgm.GetBuffer(0), nFontSize, nPlaySpeed);
				if (IsSUccess == FALSE)
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[addAreaPicture_G6]--����ı�ʧ��");
					return FALSE;
				}
				IsSUccess = tcp_send_program_G6(ip, port);
				if (IsSUccess == FALSE)
				{
					LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[tcp_send_program_G6]--���ͽ�Ŀʧ��");
					return FALSE;
				}
			}
		}
	}
	else if (strDeviceModel == "BX-5E")
	{
		EQareaframeHeader Frame;
		Frame.AreaFFlag = 0; //������ֶ�Ϊ 0x00�������� ����߿����Բ�����
		Frame.AreaFDispStyle = 0;//�߿���ʾ��ʽ�� 0x00 �C��˸ 0x01 �C˳ʱ��ת�� 0x02 �C��ʱ��ת�� 0x03 �C��˸��˳ʱ��ת�� 0x04 �C��˸����ʱ��ת�� 0x05 �C���̽�����˸ 0x06 �C���̽���ת�� 0x07 �C��ֹ��� 
		Frame.AreaFDispSpeed = 0;//�߿���ʾ�ٶ� 1-7
		Frame.AreaFMoveStep = 0;//�߿��ƶ���������λΪ�㣬�˲� ����ΧΪ 1~16 
		Frame.AreaFWidth = 0;//�߿���Ԫ��ȣ��˲�����ΧΪ 1~8 
		Frame.AreaFBackup = 0;//������ 0
		EQfontData oFont;
		oFont.arrMode = eSINGLELINE;//���з�ʽ--���ж���  E_arrMode::	eSINGLELINE,   //���� eMULTILINE,    //����
		oFont.fontSize = nFontSize;//�����С
		oFont.color = eRED;//������ɫ E_Color_G56 ��ͨ����ö��ֵ����ֱ�������߲�ɫ���������ö�ٷ�Χʹ��RGB888ģʽ
		oFont.fontBold = false;//�Ƿ�Ϊ����
		oFont.fontItalic = false;//�Ƿ�Ϊб��
		oFont.tdirection = pNORMAL;//���ַ���
		oFont.txtSpace = 0;//���ּ��   
		oFont.Valign = 2;//������뷽ʽ��0ϵͳ����Ӧ��1����롢2���С�3�Ҷ��룩
		oFont.Halign = 2;//������뷽ʽ��0ϵͳ����Ӧ��1�϶��롢2���С�3�¶��룩
		Ouint16 uRelateProgID[1];  uRelateProgID[0] = 0;
		unsigned char ip5e[20] = { 0 };
		unsigned short port5e = atoi(strPort);
		memcpy(ip5e, strIP.GetBuffer(0), strIP.GetLength());
		int nStunt5e = 18;
		if (nEffect == 1)   //������ʾ
		{
			nStunt5e = 1;
		}
		else if (nEffect == 2)   //����
		{
			nStunt5e = 4;
		}
		else if (nEffect == 3)   //����
		{
			nStunt5e = 32;
		}
		else if (nEffect == 4)    //����
		{
			nStunt5e = 18;
		}
		else if (nEffect == 5)    //����
		{
			nStunt5e = 6;
		}
		else
		{
			nStunt5e = 4;
		}
		//| ���� | ˵�� |
		//	| ---------------- - | ------------------------------------------------------------ |
		//	| pIP | ���ƿ�IP |
		//	| nPort | ���ƿ��˿� |
		//	| color | ���� |
		//	| uAreaId | ������ |
		//	| RunMode | ��̬������ģʽ 0�� ��̬������ѭ����ʾ�� 1�� ��̬��������ʾ��ɺ�ֹ�� ʾ���һҳ���ݡ� 2�� ��̬������ѭ����ʾ�������� ��ʱ���������δ����ʱ���� ��ʾ 3�� ��̬������ѭ����ʾ�������� ��ʱ���������δ����ʱ��ʾ Logo ��Ϣ, Logo ��Ϣ��Ϊ�� ̬��������һҳ��Ϣ 4�� ��̬������˳����ʾ����ʾ�� ���һҳ��Ͳ�����ʾ |
		//	| Timeout | ��̬�����ݳ�ʱʱ�䣬��λΪ�� |
		//	| RelateAllPro | �����ֽ�Ϊ 1 ʱ�������첽��Ŀ ����ʱ�������Ÿö�̬���� Ϊ 0 ʱ���󶨽�Ŀ |
		//	| RelateProNum | ��̬��������˶��ٸ��첽��Ŀ |
		//	| RelateProSerial | ��̬����������첽�� Ŀ�ı�� |
		//	| ImmePlay | �Ƿ��������� ���ֽ�Ϊ 0 ʱ���ö�̬�������� ����Ŀһ�𲥷ţ� ���ֽ�Ϊ 1 ʱ���첽��Ŀֹͣ�� �ţ������Ÿö�̬���� |
		//	| uAreaX | �������ϽǺ����� |
		//	| uAreaY | �������Ͻ������� |
		//	| uWidth | ������ |
		//	| uHeight | ����߶� |
		//	| oFrame | ����߿�����[EQareaframeHeader](#EQareaframeHeader) |
		//	| DisplayMode | ��ʾ��ʽ |
		//	| ClearMode | �˳���ʽ / ������ʽ���̶� 0 |
		//	| Speed | �ٶȵȼ� 1 - 65 |
		//	| StayTime | ͣ��ʱ�䣬��λΪ 10ms |
		//	| RepeatTime | �ظ����� |
		//	| oFont | �����ʽ[EQfontData](#EQfontData) |
		//	| fontName | �������� |
		//	| strAreaTxtContent | ��ʾ�ı� |
		int err = 0;
		nPlaySpeed = (10 - nPlaySpeed) * 6 + 1;
		if (strLedType == "1")
		{
			err = bxDual_dynamicArea_AddAreaWithTxt_5G(ip5e, port5e, eSCREEN_COLOR_SINGLE, 1, 0, 0, 1, 0, uRelateProgID,
				1, 0, 0, nWidth, nHieght, Frame, nStunt5e, 0, nPlaySpeed,0, 0, oFont, (Ouint8*)"����", (unsigned char*)strPrgm.GetBuffer(0));
			if (err != 0)
			{
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[PublishPrograms]--bxDual_dynamicArea_AddAreaWithTxt_5G��ɫ�����ͽ�Ŀʧ��");
				return FALSE;
			}
		}
		else
		{
			err = bxDual_dynamicArea_AddAreaWithTxt_5G(ip5e, port5e, eSCREEN_COLOR_DOUBLE, 1, 0, 0, 1, 0, uRelateProgID,
				1, 0, 0, nWidth, nHieght, Frame, nStunt5e, 0, nPlaySpeed, 0, 0, oFont, (Ouint8*)"����", (unsigned char*)strPrgm.GetBuffer(0));
			if (err != 0)
			{
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[PublishPrograms]--bxDual_dynamicArea_AddAreaWithTxt_5G˫ɫ�����ͽ�Ŀʧ��");
				return FALSE;
			}
		}
	}
	else if (strDeviceModel == "BX-6E")
	{
		EQareaHeader_G6 oAreaHeader_G6;
		oAreaHeader_G6.AreaType = 0x10; //0x10 ��̬����

		oAreaHeader_G6.AreaX = 0;
		oAreaHeader_G6.AreaY = 0;
		oAreaHeader_G6.AreaWidth = nWidth;
		oAreaHeader_G6.AreaHeight = nHieght;
		//AreaFrame N ����߿����ԣ���ϸ�ο�
		oAreaHeader_G6.BackGroundFlag = 0x00;
		oAreaHeader_G6.Transparency = 101;
		oAreaHeader_G6.AreaEqual = 0x00;

		//Ouint8* strSoundTxt = (Ouint8*)"���";
		//Ouint8 nSize = sizeof(strSoundTxt);
		//Ouint8 nStrLen = strlen((const char*)strSoundTxt);
		//oAreaHeader_G6.stSoundData.SoundDataLen = nStrLen;		// 4 �������ݳ���; ֻ�� SoundFlag���Ƿ�ʹ���������ţ�Ϊ 1 ʱ�ŷ��͸��ֽڣ����򲻷���
		//oAreaHeader_G6.stSoundData.SoundData = strSoundTxt;			// N ��������ֻ�� SoundFlag���Ƿ�ʹ���������ţ�Ϊ 1 ʱ�ŷ��͸��ֽڣ����򲻷���
		//{
		//	oAreaHeader_G6.stSoundData.SoundFlag = 0x00;	//1 0x00 �Ƿ�ʹ����������;0 ��ʾ��ʹ������; 1 ��ʾ����������;
		//	oAreaHeader_G6.stSoundData.SoundPerson = 0x01;	//1 0x00 ������ ��ֵ��Χ�� 0 - 5���� 6 ��ѡ��ֻ�� SoundFlag���Ƿ�ʹ���������ţ�Ϊ 1 ʱ�ŷ��͸��ֽڣ����򲻷��͸�ֵĬ��Ϊ 0
		//	oAreaHeader_G6.stSoundData.SoundVolum = 1;		//1 0x05 ������ֵ��Χ�� 0~10���� 11 �֣�0��ʾ����ֻ�� SoundFlag���Ƿ�ʹ���������ţ�Ϊ 1 ʱ�ŷ��͸��ֽڣ����򲻷��͸�ֵĬ��Ϊ 5
		//	oAreaHeader_G6.stSoundData.SoundSpeed = 0x2;	//1 0x05 ���ٸ�ֵ��Χ�� 0~10���� 11 ��ֻ�� SoundFlag���Ƿ�ʹ���������ţ�Ϊ 1 ʱ�ŷ��͸��ֽڣ����򲻷��͸�ֵĬ��Ϊ 5
		//	oAreaHeader_G6.stSoundData.SoundDataMode = 0x00;//1 0x00 SoundData �ı����ʽ����ֵ�������£�0x00 GB2312; 0x01 GBK; 0x02 BIG5; 0x03 UNICODEֻ�� SoundFlag���Ƿ�ʹ���������ţ�Ϊ 1 ʱ�ŷ��͸��ֽڣ����򲻷���
		//	oAreaHeader_G6.stSoundData.SoundReplayTimes = 0x01;// 0xffffffff;	//4 0x00000000 �ز�������ֵΪ 0����ʾ���� 1 �θ�ֵΪ 1����ʾ���� 2 ��
		//													   //......
		//													   //��ֵΪ 0xffffffff����ʾ�������޴�ֻ�� SoundFlag���Ƿ�ʹ���ﲥ�ţ�Ϊ 1 ʱ�ŷ��͸��ֽڣ����򲻷��͸�ֵĬ��Ϊ 0
		//	oAreaHeader_G6.stSoundData.SoundReplayDelay = 200;	//4 0x00000000 �ز�ʱ������ֵ��ʾ���β���������ʱ��������λΪ 10msֻ�� SoundFlag���Ƿ�ʹ���������ţ�Ϊ 1 ʱ�ŷ��͸��ֽڣ����򲻷��͸�ֵĬ��Ϊ 0
		//	oAreaHeader_G6.stSoundData.SoundReservedParaLen = 0x03;//1 0x03 ��������������������
		//	oAreaHeader_G6.stSoundData.Soundnumdeal = 0x00;		//1 0 0���Զ��ж�1�����������봦�� 2����������ֵ����ֻ�е� SoundFlag Ϊ 1 ��SoundReservedParaLen��Ϊ 0�ŷ��ʹ˲���
		//	oAreaHeader_G6.stSoundData.Soundlanguages = 0x00;		// 1 0 0���Զ��ж�����1�����������֡�������λ��������ŵȺϳ�Ϊ����2�����������֡�������λ��������ŵȺϳ�ΪӢ��ֻ�е� SoundFlag Ϊ 1 �� SoundReservedParaLen��Ϊ 0�ŷ��ʹ˲�����Ŀǰֻ֧����Ӣ�ģ�
		//	oAreaHeader_G6.stSoundData.Soundwordstyle = 0x00;		// 1 0 0���Զ��жϷ�����ʽ1����ĸ������ʽ2�����ʷ�����ʽֻ�е� SoundFlag Ϊ 1 ��SoundReservedParaLen��Ϊ 0�ŷ��ʹ˲���
		//	oAreaHeader_G6.stSoundData.SoundDataLen = nStrLen;		// 4 �������ݳ���; ֻ�� SoundFlag���Ƿ�ʹ���������ţ�Ϊ 1 ʱ�ŷ��͸��ֽڣ����򲻷���
		//	oAreaHeader_G6.stSoundData.SoundData = strSoundTxt;			// N ��������ֻ�� SoundFlag���Ƿ�ʹ���������ţ�Ϊ 1 ʱ�ŷ��͸��ֽڣ����򲻷���
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
		oAreaParams_1.fontName = (Ouint8*)"����";
		DynamicAreaParams arrParams[1];
		arrParams[0] = oAreaParams_1;
		if (strLedType == "1")
		{
			err = bxDual_dynamicAreaS_AddTxtDetails_6G(ip6e, port6e, eSCREEN_COLOR_SINGLE, 1, arrParams);
			if (err != 0)
			{
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[bxDual_dynamicAreaS_AddTxtDetails_6G]--��ɫ�����ͽ�Ŀʧ��");
				return FALSE;
			}
		}
		else
		{

			err = bxDual_dynamicAreaS_AddTxtDetails_6G(ip6e, port6e, eSCREEN_COLOR_DOUBLE, 1, arrParams);
			if (err != 0)
			{
				LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[bxDual_dynamicAreaS_AddTxtDetails_6G]--˫ɫ�����ͽ�Ŀʧ��");
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
		//	if (nEffect == 1)   //������ʾ
		//	{
		//		nStunt = 1;
		//	}
		//	else if (nEffect == 2)   //����
		//	{
		//		nStunt = 18;
		//	}
		//	else if (nEffect == 3)   //����
		//	{
		//		nStunt = 11;
		//	}
		//	else if (nEffect == 4)    //����
		//	{
		//		nStunt = 19;
		//	}
		//	else if (nEffect == 5)    //����
		//	{
		//		nStunt = 8;
		//	}
		//	else
		//	{
		//		nStunt = 18;
		//	}
		//	/*
		//	�������ã��õ���ʾ�����ݵ�ͷ��Ϣ�����浽�ļ�pFileName�С�
		//	����˵����
		//	nScreenNO����ʾ�����ţ���1��ʼ
		//	nProgramCount����ʾ���Ľ�Ŀ������
		//	pFileName����ʾ��ͷ��Ϣ������ļ���
		//	*/
		//	api_GetAllDataHead(1, 1, "SendAllDataHead1");
		//	/*
		//	����˵�����ϲ���ʾ������Ϣ�ļ�
		//	����˵����
		//	pSourceFile��Ԥ�ϲ���Ϣ�ļ�����
		//	pUnionedFile���ϲ�Ŀ���ļ����ơ�
		//	bDeleted��0����ԭ�ļ�����Ӻϲ���Ϣ�ļ���1��ɾ��ԭ�ļ���Ϣ�����´����ϲ���Ϣ�ļ�
		//	����ֵ����
		//	*/
		//	api_UnionAreaDataToFile("SendAllDataHead1", "SendAllData1", 1);
		//	/*
		//	�������ã�ȡ����ʾ����ǰ��Ŀ��ͷ��Ϣ���������ʾ������Ϣǰ��ӡ�
		//	����˵����
		//	nProgramOrd����Ŀ��ţ���0��ʼ����
		//	nAreaCount����ʾ��������ĸ�������һ����ʾ���еĶ�̬����ֻ���Է���һ�������̡���Ļ���Է��ö���������ܹ���������8������
		//	nProgPlayMode����Ŀ����ģʽ��0���������ţ�1����ʱ����
		//	nProgPlayLength����Ŀ��������ʱ�Ĳ��ų��ȣ���λΪ�룻1~ 65535
		//	nProgWeekAttrib����Ŀ��ʱ����ʱ�����ڲ������ԣ�����һ������ѭ������Ӧ���ֽ��ڵĵ�λ(bit0)����λ(bit6)����������һ���ţ���bit0=1������bit0=0������������ղ���bit6=1������bit6=0��
		//	nPlayHour������ý�Ŀ��ʼ���ŵ�Сʱֵ��
		//	nPlayHour������ý�Ŀ��ʼ���ŵķ�ֵ��
		//	nPlayHour������ý�Ŀ��ʼ���ŵ���ֵ��
		//	nPlayHour������ý�Ŀ�������ŵ�Сʱֵ��
		//	nPlayHour������ý�Ŀ�������ŵķ�ֵ��
		//	nPlayHour������ý�Ŀ�������ŵ���ֵ��
		//	pFileName����Ŀͷ��Ϣ������ļ�����
		//	*/
		//	api_GetProgramHead(0, 1, 0, 65534, 0x7F, 4, 0, 0, 22, 0, 0, "ProgramHead0");
		//	api_UnionAreaDataToFile("ProgramHead0", "SendAllData1", 0);
		//	/*
		//	�������ã�ת����Ļ������ʾ��Ϣ��
		//	����˵����
		//	nX����Ļ����ĺ�����
		//	nY����Ļ�����������
		//	nWidth����Ļ����ĳ��ȣ�
		//	nHeight����Ļ����ĸ߶ȣ�
		//	nScreenType����ʾ�����ͣ�1������ɫ��2��˫��ɫ
		//	nMkType���������ͣ�1��R+G�ͣ�2��G+R�ͣ�
		//	pFontName����Ļ������ʾ���壻֧��Windows��������
		//	nFontSize����Ļ������ʾ�ֺ�
		//	nFontColor����Ļ������ʾ��ɫ; 1����ɫ��2����ɫ��3����ɫ
		//	bBold������
		//	bItalic��б��
		//	bUnderLine���»���
		//	pTitle����Ļ������ʾ����Ļ������Ϣ
		//	nStunt����Ļ������ʾ�ؼ��������ؼ������ּ�ע1��
		//	nRunSpeed����Ļ������Ϣ�����ٶ�
		//	nShowTime����Ļ������Ϣͣ��ʱ��
		//	pFileName����Ļ������Ϣ������ļ�����
		//	*/
		//	api_SetScreenTitle(nWidth, 0, nWidth, nHieght, atoi(strLedType), 1, "����", nFontSize, 1, 0, 0, 0, strPrgm.GetBuffer(0), nStunt, nPlaySpeed, 0, "SendDataTitle1");
		//	api_UnionAreaDataToFile("SendDataTitle1", "SendAllData1", 0);

		//	api_GetCurDataTime("CurTimeData1");
		//	api_UnionAreaDataToFile("CurTimeData1", "SendAllData1", 0);
		//	/*
		//	�������ã�TCP/IPģʽ�·�����Ϣ
		//	����˵����
		//	pTCPAddress����ʾ��IP��ַ����ʽΪ��***.***.***.***��
		//	nPort����ʾ���˿���Ϣ
		//	nSendType��ͨѶ�������ͣ�
		//	0xC1��������ʾ������
		//	0xC8��������ʾ������
		//	0xD1��������ʾ��ȫ������
		//	0xD2��������ʾ����̬��������
		//	0xC4��ǿ�ƿ����ػ�
		//	0xE6���޸�IP��ַ��Ϣ
		//	0xCD��У��ʱ��
		//	nWidth����ʾ���ĳ��ȣ�
		//	nHeight����ʾ���ĸ߶ȣ�
		//	nScreenType����ʾ�����ͣ�1������ɫ��2��˫��ɫ
		//	pSendBufFile����ʾ�����ݡ�������Ϣ
		//	����ֵ��
		//	0������ʾ��������Ϣ�ɹ���
		//	1������ʾ��������Ϣʧ�ܡ�
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
		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[PublishPrograms]--BX-E���Ͱ忨�ݲ�֧��");
		return FALSE;
	}
	else
	{
		LOG_DD(LOGTYPE_DEBUG, PUBLISHRECOARD, "[PublishPrograms]--����忨����ƥ��ʧ��");
		return FALSE;
	}
	return TRUE;
}

void Onbon::OnbonReleaseSdk()
{
	bxDual_ReleaseSdk();
}
//��ӽ�Ŀ
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
//�������
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
//����ı�
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
	n_ret = bxDual_program_picturesAreaAddTxt(0, str, (Ouint8*)"����", &pheader);
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

	n_ret=bxDual_program_picturesAreaAddTxt_G6(AreaID, str, (Ouint8*)"����", &pheader1);
	if (n_ret != 0)
	{
		return FALSE;
	}
	return TRUE;
}
//���ͽ�Ŀ
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

	//ɾ�������ڴ��еĽ�Ŀ
	ret = bxDual_program_deleteProgram_G6();
	if (ret != 0)
	{
		return FALSE;
	}
	return TRUE;
}