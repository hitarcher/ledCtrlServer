#include "stdafx.h"
#include "SCL2008.h"

SCL2008::SCL2008()
{
}

SCL2008::~SCL2008()
{
}

BOOL SCL2008::LED_SCL2008Initialize()
{
	hSCL_Dll = LoadLibrary("SCL_API_stdcall.Dll");
	if (hSCL_Dll != NULL)
	{
		SCL_NetInitial = (_SCL_NetInitial)GetProcAddress(hSCL_Dll, "SCL_NetInitial");
		SCL_ComInitial = (_SCL_ComInitial)GetProcAddress(hSCL_Dll, "SCL_ComInitial");
		SCL_Close = (_SCL_Close)GetProcAddress(hSCL_Dll, "SCL_Close");
		SCL_SetRemoteIP = (_SCL_SetRemoteIP)GetProcAddress(hSCL_Dll, "SCL_SetRemoteIP");
		SCL_SetLEDNum = (_SCL_SetLEDNum)GetProcAddress(hSCL_Dll, "SCL_SetLEDNum");
		SCL_TargetSCL2008 = (_SCL_TargetSCL2008)GetProcAddress(hSCL_Dll, "SCL_TargetSCL2008");
		SCL_GetLastResult = (_SCL_GetLastResult)GetProcAddress(hSCL_Dll, "SCL_GetLastResult");

		SCL_InitForPackage = (_SCL_InitForPackage)GetProcAddress(hSCL_Dll, "SCL_InitForPackage");
		SCL_GetPackage = (_SCL_GetPackage)GetProcAddress(hSCL_Dll, "SCL_GetPackage");
		SCL_CheckAnswer = (_SCL_CheckAnswer)GetProcAddress(hSCL_Dll, "SCL_CheckAnswer");

		SCL_FormatDisk = (_SCL_FormatDisk)GetProcAddress(hSCL_Dll, "SCL_FormatDisk");
		SCL_FreeSpace = (_SCL_FreeSpace)GetProcAddress(hSCL_Dll, "SCL_FreeSpace");
		SCL_DirItemCount = (_SCL_DirItemCount)GetProcAddress(hSCL_Dll, "SCL_DirItemCount");
		SCL_GetDirItem = (_SCL_GetDirItem)GetProcAddress(hSCL_Dll, "SCL_GetDirItem");
		SCL_SendFile = (_SCL_SendFile)GetProcAddress(hSCL_Dll, "SCL_SendFile");
		SCL_ReceiveFile = (_SCL_ReceiveFile)GetProcAddress(hSCL_Dll, "SCL_ReceiveFile");
		SCL_RemoveFile = (_SCL_RemoveFile)GetProcAddress(hSCL_Dll, "SCL_RemoveFile");
		SCL_MD = (_SCL_MD)GetProcAddress(hSCL_Dll, "SCL_MD");
		SCL_RD = (_SCL_RD)GetProcAddress(hSCL_Dll, "SCL_RD");
		SCL_SaveFile = (_SCL_SaveFile)GetProcAddress(hSCL_Dll, "SCL_SaveFile");
		SCL_LoadFile = (_SCL_LoadFile)GetProcAddress(hSCL_Dll, "SCL_LoadFile");
		SCL_SendData = (_SCL_SendData)GetProcAddress(hSCL_Dll, "SCL_SendData");
		SCL_ReceiveData = (_SCL_ReceiveData)GetProcAddress(hSCL_Dll, "SCL_ReceiveData");
		SCL_ShowString = (_SCL_ShowString)GetProcAddress(hSCL_Dll, "SCL_ShowString");

		SCL_Reset = (_SCL_Reset)GetProcAddress(hSCL_Dll, "SCL_Reset");
		SCL_Replay = (_SCL_Replay)GetProcAddress(hSCL_Dll, "SCL_Replay");
		SCL_SetTimer = (_SCL_SetTimer)GetProcAddress(hSCL_Dll, "SCL_SetTimer");
		SCL_SetBright = (_SCL_SetBright)GetProcAddress(hSCL_Dll, "SCL_SetBright");
		SCL_SetOnOffTime = (_SCL_SetOnOffTime)GetProcAddress(hSCL_Dll, "SCL_SetOnOffTime");
		SCL_SetTempOffset = (_SCL_SetTempOffset)GetProcAddress(hSCL_Dll, "SCL_SetTempOffset");
		SCL_SetPowerMode = (_SCL_SetPowerMode)GetProcAddress(hSCL_Dll, "SCL_SetPowerMode");
		SCL_GetRunTimeInfo = (_SCL_GetRunTimeInfo)GetProcAddress(hSCL_Dll, "SCL_GetRunTimeInfo");
		SCL_LedShow = (_SCL_LedShow)GetProcAddress(hSCL_Dll, "SCL_LedShow");
		SCL_SetExtSW = (_SCL_SetExtSW)GetProcAddress(hSCL_Dll, "SCL_SetExtSW");
		SCL_GetPlayInfo = (_SCL_GetPlayInfo)GetProcAddress(hSCL_Dll, "SCL_GetPlayInfo");

		SCL_PictToXMPFile = (_SCL_PictToXMPFile)GetProcAddress(hSCL_Dll, "SCL_PictToXMPFile");
		SCL_GetMaxFileSize = (_SCL_GetMaxFileSize)GetProcAddress(hSCL_Dll, "SCL_GetMaxFileSize");
		SCL_AddXMPToXMP = (_SCL_AddXMPToXMP)GetProcAddress(hSCL_Dll, "SCL_AddXMPToXMP");
		SCL_GetFileDosDateTime = (_SCL_GetFileDosDateTime)GetProcAddress(hSCL_Dll, "SCL_GetFileDosDateTime");
	}
	// 判断函数指针获取成功否
	// Check these pointer
	if ((!hSCL_Dll) ||
		(!SCL_NetInitial) ||
		(!SCL_ComInitial) ||
		(!SCL_Close) ||
		(!SCL_SetLEDNum) ||
		(!SCL_SetRemoteIP) ||
		(!SCL_TargetSCL2008) ||
		(!SCL_GetLastResult) ||

		(!SCL_InitForPackage) ||
		(!SCL_GetPackage) ||
		(!SCL_CheckAnswer) ||

		(!SCL_FormatDisk) ||
		(!SCL_FreeSpace) ||
		(!SCL_DirItemCount) ||
		(!SCL_GetDirItem) ||
		(!SCL_SendFile) ||
		(!SCL_ReceiveFile) ||
		(!SCL_RemoveFile) ||
		(!SCL_MD) ||
		(!SCL_RD) ||
		(!SCL_SaveFile) ||
		(!SCL_LoadFile) ||
		(!SCL_SendData) ||
		(!SCL_ReceiveData) ||
		(!SCL_ShowString) ||

		(!SCL_Reset) ||
		(!SCL_Replay) ||
		(!SCL_SetTimer) ||
		(!SCL_SetBright) ||
		(!SCL_SetOnOffTime) ||
		(!SCL_SetTempOffset) ||
		(!SCL_SetPowerMode) ||
		(!SCL_GetRunTimeInfo) ||
		(!SCL_GetPlayInfo) ||
		(!SCL_LedShow) ||
		(!SCL_SetExtSW) ||

		(!SCL_PictToXMPFile) ||
		(!SCL_GetMaxFileSize) ||
		(!SCL_AddXMPToXMP) ||
		(!SCL_GetFileDosDateTime)
		)
	{
		FreeLibrary(hSCL_Dll);
		hSCL_Dll = NULL;
		return FALSE;
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void SCL2008::LED_SCL2008FreeDll()
{
	if (hSCL_Dll != NULL) FreeLibrary(hSCL_Dll);
}