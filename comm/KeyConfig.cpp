#include "stdafx.h"
#include "KeyConfig.h"


#define KILOBYTE 1024

CKeyConfig::CKeyConfig(void)
{
	m_strBtnConfigPath = "";
}


CKeyConfig::~CKeyConfig(void)
{
}


BOOL CKeyConfig::LoadBaseConfig()
{
	m_strBtnConfigPath = GetFullPath("Config\\KeyConfig.ini");
	if(FALSE == CheckFileExist(m_strBtnConfigPath)) return FALSE;
	return TRUE;
}

BOOL CKeyConfig::LoadKeyConfig()
{
	//获取图片按钮信息
	CString strTempIMG;
	GetPrivateProfileString("KEYBASE","ALLBTN","",strTempIMG.GetBuffer(KILOBYTE),KILOBYTE, m_strBtnConfigPath.GetBuffer(0));
	strTempIMG.ReleaseBuffer();

	std::vector<CString> vctIMGIndex = SplitString(strTempIMG,"|");
	for(UINT i=0;i<vctIMGIndex.size();i++)
	{
		CString strIMG;
		GetPrivateProfileString("KEYBASE",vctIMGIndex[i],"",strIMG.GetBuffer(KILOBYTE),KILOBYTE,m_strBtnConfigPath.GetBuffer(0));

		KeyButtonCfg msg;
		msg << strIMG.GetBuffer(0);
		msg.nID = i;
		strcpy(msg.szBtnName, vctIMGIndex[i].GetBuffer(0));
		m_vctKeyBtn.push_back(msg);

		strIMG.ReleaseBuffer();
	}
	return TRUE;
}