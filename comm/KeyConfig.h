#pragma once
#include "CommonFun.h"
#include <vector>
using namespace std;

typedef struct tagKeyButtonCfg
{
	int nX;
	int nY;
	int nID;
	char szBtnUP[128];
	char szBtnDOWN[128];
	char szBtnName[256];

	tagKeyButtonCfg()
	{
		memset(this, 0x00, sizeof(tagKeyButtonCfg));
	}
	BOOL operator << (char* pStr)
	{
		if(pStr == NULL || strlen(pStr) == 0) return FALSE;
		std::vector<CString> vct= SplitString(pStr, ",");
		nX = (vct.size() > 0) ? atoi(vct[0].GetBuffer(0)):0;
		nY = (vct.size() > 1) ? atoi(vct[1].GetBuffer(0)):0;
		if(vct.size() > 2) 
		{
			strcpy_s(szBtnUP, vct[2].GetBuffer(0));
		}
		if(vct.size() > 3) 
		{
			strcpy_s(szBtnDOWN, vct[3].GetBuffer(0));
		}

		return TRUE;
	}
} KeyButtonCfg, *LPKeyButtonCfg;



class CKeyConfig
{
public:
	CKeyConfig(void);
	~CKeyConfig(void);

	BOOL LoadBaseConfig();

	BOOL LoadKeyConfig();


public:
	vector<KeyButtonCfg> m_vctKeyBtn;

private:
	CString m_strBtnConfigPath;

};

