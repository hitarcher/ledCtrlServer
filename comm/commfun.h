#ifndef __COMMFUN_H__
#define __COMMFUN_H__

#include <VECTOR>
#include "CommonFun.h"

//	��������
#define PORT_UNUSED			0
#define PORT_USED			1
#define PORT_KNOW			2
#define PORT_UNKNOW			3

#define VOUCHER				0
#define INVOICE				1

//typedef enum{DATE_LONG,DATE_LONG2 ,DAY_NORMAL, TIME_NORMAL, DATE_NORMAL, DAY_SHORT, DAY_LONG, TIME_LONG, TIME_SHORT1,TIME_SHORT2,MONTH_NORMAL, MONTH_LONG, BANK_NORMAL}TIME_TYPE;

typedef enum{DEV_ALL,DEV_VOUCHER,DEV_INVOICE,DEV_CASHCODE,DEV_IDCARD,DEV_UNIONCARD,DEV_PWDKEYBOARD}DEV_TYPE;

typedef struct INDEX_DOUBLE
{
	int nIndex;
	double fContent;
}*LPINDEX_DOUBLE;

typedef struct DAMIO_STATUS
{
	BOOL bBefor;
	BOOL bCurr;
	DAMIO_STATUS()
	{
		memset(this,0x00,sizeof(DAMIO_STATUS));
	}
	void operator = (BOOL bstatus)
	{
		bBefor = bCurr;
		bCurr = bstatus;
	}
	BOOL ISChanged()
	{
		return (bBefor == bCurr) ? FALSE:TRUE;
	}
}*LPDAMIO_STATUS;

#define DEV_LOG(t,c,s) {WriteDevLog(t,c,s);}
#define DEV_LOG2(t,c,s,a) {WriteDevLog(t,c,s,a);}

//	�豸��Ϣ
typedef struct _PORT_DEVICE {
	CString strPort;
	HANDLE hThread;// �߳̾��
	int iStatus; // 0 δռ�� 1 ��ռ�� 2 ��ʶ�� 3 �޷�ʶ��
	CString strInfo;// ���ʶ����Ϣ
	_PORT_DEVICE()
	{
		strPort = "";
		hThread = NULL;
		iStatus = PORT_UNUSED;
		strInfo = "";
	}
} PORT_DEVICE;

//	ͨ�ú���
bool GetComPorts(CStringArray* pPortList);
bool GetLPTPorts(CStringArray* pPortList);

BOOL SetPrivilege();

CString GetYesterdayTime(TIME_TYPE nType);
std::vector<CString> SplitString(CString sData, const char* sFlag);

int GetMaxIndex(std::vector<INDEX_DOUBLE> vctHist,double fBaseline=0.9);
int GetMinIndex(std::vector<INDEX_DOUBLE> vctHist,double fBaseline=0.1);


















#endif