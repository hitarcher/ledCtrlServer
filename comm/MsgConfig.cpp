// Config.cpp: implementation of the CConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MsgConfig.h"
#include <IO.H>
#include <shlwapi.h>
#include "CommonFun.h"

#pragma comment(lib,"Shlwapi.lib")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MsgConfig::MsgConfig()
{
	m_strDeviceID = "";
	m_strOrganCode = "";
}

MsgConfig::~MsgConfig()
{

}

BOOL MsgConfig::CheckFileExist(CString strFilePath,CString strFileName)
{
	if(-1 == _access(strFilePath.GetBuffer(0),0))
	{
		m_strLastErr.Format("系统文件已经缺失[%s]!",strFileName);
		return FALSE;
	}
	m_strLastErr = "";
	return TRUE;
}

BOOL MsgConfig::LoadBaseConfig()
{
	m_strPathConfigBase = GetFullPath("index.ini");
	if(FALSE == CheckFileExist(m_strPathConfigBase,"index.ini")) return FALSE;
	
	GetPrivateProfileString("REG","REGCODE","FFFFFFFFFFFFFFFFFFFFFFFF",m_strRegCode.GetBuffer(KILOBYTE),KILOBYTE,m_strPathConfigBase.GetBuffer(0));
	GetPrivateProfileString("INDEX","DEV","",m_strPathConfigDev.GetBuffer(KILOBYTE),KILOBYTE,m_strPathConfigBase.GetBuffer(0));
	GetPrivateProfileString("INDEX","IMAGE","",m_strPathConfigImage.GetBuffer(KILOBYTE),KILOBYTE,m_strPathConfigBase.GetBuffer(0));
	m_strRegCode.ReleaseBuffer();
	m_strPathConfigDev.ReleaseBuffer();
	m_strPathConfigImage.ReleaseBuffer();

	m_uLogType = GetPrivateProfileInt("LOG","LOGTYPE",0,m_strPathConfigBase.GetBuffer(0));

	if(PathIsRelative(m_strPathConfigDev.GetBuffer(0))) m_strPathConfigDev=GetFullPath(m_strPathConfigDev);
	if(PathIsRelative(m_strPathConfigImage.GetBuffer(0))) m_strPathConfigImage=GetFullPath(m_strPathConfigImage);

	if(FALSE == CheckFileExist(m_strPathConfigDev,"DEVICE")) return FALSE;
	if(FALSE == CheckFileExist(m_strPathConfigImage,"IMAGE")) return FALSE;

	return TRUE;
}

BOOL MsgConfig::LoadDeviceConfig()
{
	CString strDAMIO;

	//获取配置文件路径
	GetPrivateProfileString("DEVICECONFIG","WEBSERVICE","",m_strWebServiceUrl.GetBuffer(KILOBYTE),KILOBYTE,m_strPathConfigDev.GetBuffer(0));
	GetPrivateProfileString("DEVICECONFIG","DAMIO","",strDAMIO.GetBuffer(KILOBYTE),KILOBYTE,m_strPathConfigDev.GetBuffer(0));
	m_strWebServiceUrl.ReleaseBuffer();
	strDAMIO.ReleaseBuffer();

	//获取设备接口信息（串口、USB口）
	m_devDAMIO << strDAMIO.GetBuffer(0);

	//获取DAM继电器具体信息
	CString strTempDAM;
	GetPrivateProfileString("DEVICEMSG","DAMIO","",strTempDAM.GetBuffer(KILOBYTE),KILOBYTE,m_strPathConfigDev.GetBuffer(0));
	strTempDAM.ReleaseBuffer();

	std::vector<CString> vctDAMtemp = SplitString(strTempDAM,"|");
	for(UINT i=0;i<vctDAMtemp.size();i++)
	{
		DEVICE_DAMIO_MSG msg;
		msg << vctDAMtemp[i].GetBuffer(0);
		m_vctDAMIOMsg.push_back(msg);
	}
	//获取图片按钮信息
	CString strTempIMG;
	GetPrivateProfileString("PAGECONTENT","NETBTN","",strTempIMG.GetBuffer(KILOBYTE),KILOBYTE,m_strPathConfigImage.GetBuffer(0));
	strTempIMG.ReleaseBuffer();

	std::vector<CString> vctIMGIndex = SplitString(strTempIMG,"|");
	for(UINT i=0;i<vctIMGIndex.size();i++)
	{
		CString strIMG;
		GetPrivateProfileString("PAGECONTENT",vctIMGIndex[i],"",strIMG.GetBuffer(KILOBYTE),KILOBYTE,m_strPathConfigImage.GetBuffer(0));

		IMG_BTN_NET_MSG msg;
		msg << strIMG.GetBuffer(0);
		msg.nID = i;
		m_vctIMGMsg.push_back(msg);
		strIMG.ReleaseBuffer();
	}
	return TRUE;
}

BOOL MsgConfig::LoadImageConfig()
{
	GetPrivateProfileString("PAGECONTENT","MAINPATH","",m_strMainPath.GetBuffer(KILOBYTE),KILOBYTE,m_strPathConfigImage.GetBuffer(0));
	m_strMainPath.ReleaseBuffer();

//	m_strPathIndex = (PathIsRelative(m_strPathIndex.GetBuffer(0))) ? GetFullPath(m_strPathIndex).GetBuffer(0):m_strPathIndex.GetBuffer(0);

	return TRUE;
}

CString MsgConfig::GetSubPagePath(CString strSubPage)
{
	CString strTemp;
	GetPrivateProfileString("PAGECONTENT",strSubPage,"",strTemp.GetBuffer(KILOBYTE),KILOBYTE,m_strPathConfigImage.GetBuffer(0));
	strTemp.ReleaseBuffer();

//	if(FALSE == strTemp.IsEmpty()) strTemp = (PathIsRelative(strTemp.GetBuffer(0))) ? GetFullPath(strTemp).GetBuffer(0):strTemp.GetBuffer(0);
	return strTemp;
}

CString MsgConfig::GetSubDeviceConfig(CString strSubDevice)
{
	CString strTemp;
	GetPrivateProfileString("DEVICEMSG",strSubDevice,"",strTemp.GetBuffer(KILOBYTE),KILOBYTE,m_strPathConfigDev.GetBuffer(0));
	strTemp.ReleaseBuffer();

	//	if(FALSE == strTemp.IsEmpty()) strTemp = (PathIsRelative(strTemp.GetBuffer(0))) ? GetFullPath(strTemp).GetBuffer(0):strTemp.GetBuffer(0);
	return strTemp;
}
