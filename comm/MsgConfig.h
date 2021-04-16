// Config.h: interface for the CConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIG_H__D45302DB_BA75_455B_977F_CA089913B187__INCLUDED_)
#define AFX_CONFIG_H__D45302DB_BA75_455B_977F_CA089913B187__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "commfun.h"
#include "DeviceStruct.h"

#define KILOBYTE 1024

class MsgConfig  
{
public:
	MsgConfig();
	virtual ~MsgConfig();

private:
	CString m_strLastErr;
	CString m_strPathConfigBase;
	CString m_strPathConfigDev;
	CString m_strPathConfigImage;
	CString m_strRegCode;
	UINT	m_uLogType;
	CString	m_strMainPath;
	CString	m_strWebServiceUrl;

private:
	DEVICE m_devDAMIO;

public:
	std::vector<DEVICE_DAMIO_MSG>	m_vctDAMIOMsg;
	CString m_strDeviceID;
	CString m_strOrganCode;
	std::vector<IMG_BTN_NET_MSG>	m_vctIMGMsg;

public:
	BOOL CheckFileExist(CString strFilePath,CString strFileName);
	BOOL LoadBaseConfig();
	BOOL LoadImageConfig();
	BOOL LoadDeviceConfig();

public:
	CString GetLastErr() {return m_strLastErr;}
	CString GetRegCode() {return m_strRegCode;}
	DEVICE	GetDAMIOConfig() {return m_devDAMIO;}
	UINT	GetLogType() {return m_uLogType;}
	CString	GetMainPagePath() {return m_strMainPath;}
	CString GetSubPagePath(CString strSubPage);
	CString GetSubDeviceConfig(CString strSubDevice);
	CString	GetWebServiceUrl() {return m_strWebServiceUrl;}
};

#endif // !defined(AFX_CONFIG_H__D45302DB_BA75_455B_977F_CA089913B187__INCLUDED_)
