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
	CString AddMsgContent(CString strType, CString strOrgancode ="",CString strBody="",CString strReserve="");	// 查询类型
public:
	//获得错误报告
	CString GetLastErr() {return m_strLastErr;}
	// 签到
	BOOL Login(const char* pUrl);
	// 下发节目/节目单
	BOOL GetPrgms(const char* pUrl, CString strJson, CString &strJsonOut);
	// 上传下发后的节目状态
	BOOL UpLoadProGrameStatus(const char* pUrl, CString strBody);
	// 上传中转服务设备状态
	BOOL UpLoadDeviceStatus(const char* pUrl);
	// 上传门楣屏设备状态
	BOOL UpLoadMMPDeviceStatus(const char* pUrl,CString steMMPDeviceCode);
};

