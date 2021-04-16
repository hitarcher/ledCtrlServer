#pragma once

#include <vector>
#include <iostream>
using namespace std;
class CConfig
{
public:
	CConfig(void);
	~CConfig(void);
private:
	CString m_strLastErr;
	CString m_strCfgPath;
public:

	CString m_strHttpUrl;
	CString m_strHttpDwonloadUrl;
	CString m_strIPAddress;
	CString m_strAccount;
	CString m_strPassword;
	CString m_strDeviceCode;
	CString m_strExchangeName;
	CString m_strRouteKeyIndex;
	vector<CString> m_vecRouteKey;
	CString m_strDeviceType;
	int m_nDelLogDay;
	int m_nLogLevel;
	int m_nThreadNum;
	int m_nPort;
	int	m_nModeName;
	int	m_nChannel;
	BOOL m_bAutoConfig;
	CString m_strRelatePath;
	CString m_strTemporaryJson;
	CString m_strTempalteJson;
	CString m_strOldTemplate;

public:
	CString GetLastErr() {return m_strLastErr;}
	BOOL LoadBaseCfg();
	BOOL LoadUrl();
	CString GetStringFromCfgDev(LPCTSTR lpAppName, LPCTSTR lpKeyName);
	BOOL WriteStringToCfgDev(LPCTSTR lpAppName, LPCTSTR lpKeyName, CString strValue);
	UINT GetIntgFromCfgDev(CString strAppName, CString strKeyName);
};

