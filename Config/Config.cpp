#include "stdafx.h"
#include "Config.h"
#include "CommonFun.h"
#include "COMMFCN.h"

CConfig::CConfig(void)
{
	m_strLastErr = "";
}

CConfig::~CConfig(void)
{

}

BOOL CConfig::LoadUrl()
{
	m_strCfgPath = GetFullPath("Config\\Config.ini");

	if (CheckFileExist(m_strCfgPath) == FALSE)
	{
		m_strLastErr.Format("缺失系统文件[%s]", GetFullPath("Config\\Config.ini"));
		return FALSE;
	}
	GetPrivateProfileString("BASE", "HttpUrl", "FFFFFFFFFFFF", m_strHttpUrl.GetBuffer(MAX_BUFF), MAX_BUFF, m_strCfgPath.GetBuffer(0));
	m_strHttpUrl.ReleaseBuffer();
	GetPrivateProfileString("BASE", "HttpDwonloadUrl", "FFFFFFFFFFFF", m_strHttpDwonloadUrl.GetBuffer(MAX_BUFF), MAX_BUFF, m_strCfgPath.GetBuffer(0));
	m_strHttpDwonloadUrl.ReleaseBuffer();
	GetPrivateProfileString("RMQ", "QueueName", "", m_strDeviceCode.GetBuffer(MAX_BUFF), MAX_BUFF, m_strCfgPath.GetBuffer(0));
	m_strDeviceCode.ReleaseBuffer();
	return TRUE;
}

BOOL CConfig::LoadBaseCfg()
{
	m_strCfgPath = GetFullPath("Config\\Config.ini");

	if(CheckFileExist(m_strCfgPath) == FALSE)
	{
		m_strLastErr.Format("缺失系统文件[%s]",GetFullPath("Config\\Config.ini"));
		return FALSE;
	}
	m_nLogLevel = GetPrivateProfileInt("LOG", "LogLevel", 0, m_strCfgPath.GetBuffer(0));
	m_nThreadNum = GetPrivateProfileInt("CONFIG", "MaxThreadNum", 100, m_strCfgPath.GetBuffer(0));
	m_nDelLogDay = GetPrivateProfileInt("CONFIG", "DelLogDays", 30, m_strCfgPath.GetBuffer(0));

	GetPrivateProfileString("RMQ", "IPAddress", "", m_strIPAddress.GetBuffer(MAX_BUFF), MAX_BUFF, m_strCfgPath.GetBuffer(0));
	m_strIPAddress.ReleaseBuffer();
	GetPrivateProfileString("RMQ", "Account", "", m_strAccount.GetBuffer(MAX_BUFF), MAX_BUFF, m_strCfgPath.GetBuffer(0));
	m_strAccount.ReleaseBuffer();
	GetPrivateProfileString("RMQ", "Password", "", m_strPassword.GetBuffer(MAX_BUFF), MAX_BUFF, m_strCfgPath.GetBuffer(0));
	m_strPassword.ReleaseBuffer();
	GetPrivateProfileString("RMQ", "QueueName", "", m_strDeviceCode.GetBuffer(MAX_BUFF), MAX_BUFF, m_strCfgPath.GetBuffer(0));
	m_strDeviceCode.ReleaseBuffer();
	GetPrivateProfileString("RMQ", "ExchangeName", "", m_strExchangeName.GetBuffer(MAX_BUFF), MAX_BUFF, m_strCfgPath.GetBuffer(0));
	m_strExchangeName.ReleaseBuffer();
	GetPrivateProfileString("RMQ", "RouteKey", "", m_strRouteKeyIndex.GetBuffer(MAX_BUFF), MAX_BUFF, m_strCfgPath.GetBuffer(0));
	m_strRouteKeyIndex.ReleaseBuffer();
	GetPrivateProfileString("RMQ", "DeviceType", "", m_strDeviceType.GetBuffer(MAX_BUFF), MAX_BUFF, m_strCfgPath.GetBuffer(0));
	m_strDeviceType.ReleaseBuffer();

	m_nPort = GetPrivateProfileInt("RMQ", "Port", 0, m_strCfgPath.GetBuffer(0));
	m_nChannel = GetPrivateProfileInt("RMQ", "Channel", 0, m_strCfgPath.GetBuffer(0));
	m_nModeName = GetPrivateProfileInt("RMQ", "ModeName", 0, m_strCfgPath.GetBuffer(0));
	m_bAutoConfig = GetPrivateProfileInt("RMQ", "AutoConfig", 0, m_strCfgPath.GetBuffer(0));

	vector<CString> vecIndex = SplitString(m_strRouteKeyIndex, "|");
	if (m_bAutoConfig)	//自动修改本地配置开关，通过本地配置获取。限定格式和个数
	{
		if (vecIndex.size() != 5)
		{
			m_strLastErr.Format("RouteKey不为5个");
			return FALSE;
		}
		CString strTemp("");
		strTemp = "ry.mq." + g_strOrgCode + "." + m_strDeviceType + "." + m_strDeviceCode;
		m_vecRouteKey.push_back(strTemp);
		WriteStringToCfgDev("RMQ", vecIndex[0], strTemp);

		strTemp = "ry.mq." + g_strOrgCode + "." + m_strDeviceType;
		m_vecRouteKey.push_back(strTemp);
		WriteStringToCfgDev("RMQ", vecIndex[1], strTemp);

		strTemp = "ry.mq." + m_strDeviceType;
		m_vecRouteKey.push_back(strTemp);
		WriteStringToCfgDev("RMQ", vecIndex[2], strTemp);

		strTemp = "ry." + g_strOrgCode;
		m_vecRouteKey.push_back(strTemp);
		WriteStringToCfgDev("RMQ", vecIndex[3], strTemp);

		strTemp = "*";
		m_vecRouteKey.push_back(strTemp);
		WriteStringToCfgDev("RMQ", vecIndex[4], strTemp);

	}
	else//直接读取
	{
		for (int i = 0; i < vecIndex.size(); i++)
		{
			CString strTemp("");
			GetPrivateProfileString("RMQ", vecIndex[i], "", strTemp.GetBuffer(MAX_BUFF), MAX_BUFF, m_strCfgPath.GetBuffer(0));
			strTemp.ReleaseBuffer();
			m_vecRouteKey.push_back(strTemp);
		}
	}

	return TRUE;
}

CString CConfig::GetStringFromCfgDev(LPCTSTR lpAppName, LPCTSTR lpKeyName)
{
	CString strtmp;
	GetPrivateProfileString(lpAppName,lpKeyName,"FFFFFFFFFFFF",strtmp.GetBuffer(MAX_BUFF), MAX_BUFF,m_strCfgPath.GetBuffer(0));
	strtmp.ReleaseBuffer();
	//ConvertUtf8ToGBK(strtmp);
	return strtmp;
}

UINT CConfig::GetIntgFromCfgDev(CString strAppName, CString strKeyName)
{
	int iTemp = GetPrivateProfileInt(strAppName, strKeyName, 0, m_strCfgPath.GetBuffer(0));
	return iTemp;
}

BOOL CConfig::WriteStringToCfgDev(LPCTSTR lpAppName, LPCTSTR lpKeyName, CString strValue)
{
	return WritePrivateProfileString(lpAppName, lpKeyName, strValue, m_strCfgPath);
}