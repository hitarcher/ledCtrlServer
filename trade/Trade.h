#pragma once
#include <json.hpp>
using json = nlohmann::json;
class CTrade
{
public:
	CTrade(void);
	~CTrade(void);

private:
	CString m_strLastErr;
private:
	CString AddMsgContent(CString strType, CString strOrgancode ="",CString strBody="",CString strReserve="");	// ��ѯ����
public:
	//��ô��󱨸�
	CString GetLastErr() {return m_strLastErr;}
	// ǩ��
	BOOL Login(const char* pUrl);
	// �·���Ŀ/��Ŀ��
	BOOL GetPrgms(const char* pUrl, CString strJson, CString &strJsonOut);
	// �ϴ��·���Ľ�Ŀ״̬
	BOOL UpLoadProGrameStatus(const char* pUrl, CString strBody);
	// �ϴ���ת�����豸״̬
	BOOL UpLoadDeviceStatus(const char* pUrl);
	// �ϴ�������豸״̬
	BOOL UpLoadMMPDeviceStatus(const char* pUrl,CString steMMPDeviceCode);
};

