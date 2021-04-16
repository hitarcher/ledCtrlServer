#include "stdafx.h"
#include "Trade.h"
#include "COMMFCN.h"
#include "HttpClient.h"
#include <string.h>
#include "CommunicateInterface.h"
#ifdef DEBUG                            
#pragma comment(lib, "Communicated.lib")  
#else                                   
#pragma comment(lib, "Communicate.lib")   
#endif   

bool IsJsonData(std::string strData);//�ж��Ƿ���json�ļ����Ƿ���Ϲ淶
extern CConfig g_Config;
CString g_strOrgCode;

CString Encode_3Des(CString strin)
{
	std::string strKey = "6C4E60E55552386C759569836DC0F83869836DC0F838C0F7";
	std::string strPlain = strin;
	std::string strCipher = "";
	COMM_DES3_ECB(strKey, strPlain, strCipher, encrpyt);
	return strCipher.c_str();
}

CString Decode_3Des(CString strin)
{
	std::string strKey = "6C4E60E55552386C759569836DC0F83869836DC0F838C0F7";
	std::string strPlain = "";
	std::string strCipher = strin;
	COMM_DES3_ECB(strKey, strPlain, strCipher, decrypt);
	return strPlain.c_str();
}

CTrade::CTrade(void)
{
	m_strLastErr = "";
}

CTrade::~CTrade(void)
{

}

CString CTrade::AddMsgContent(CString strType,CString strOrgancode,CString strBody,CString strReserve)
{
	//�°�ƽ̨��ʹ�ñ�׼ģ������json����
	CString strContent = "";
	json Head;
	json Body;
	json Root;
	Head["version"] = "1.0";
	Head["tradecode"] = strType.GetBuffer();
	Head["organcode"] = strOrgancode.GetBuffer();
	Head["devicecode"] = g_Config.m_strDeviceCode.GetBuffer();
	Head["workdate"] = GetCurTime(DAY_LONG).c_str();
	Head["senddate"] = GetCurTime(DAY_LONG).c_str();
	Head["sendtime"] = GetCurTime(TIME_LONG).c_str();
	CString serialnumber = GetCurTime(DATE_NORMAL).c_str() + strOrgancode + g_Config.m_strDeviceCode;//���ֶ�ƽ̨δУ�飬���д
	Head["serialnumber"] = serialnumber.GetBuffer();
	Head["reserve"] = strReserve.GetBuffer();
	Head["token"] = "0";
	//��װheadͷ
	Root["head"] = Head;
	//��װbody
	CString body = "";
	body.Format("{%s}", strBody);
	Root["body"] = json::parse(body.GetBuffer(0));

	std::string out = Root.dump(4);
	CString str_json = out.c_str();
	str_json.Replace("\\", "");
	//str_json.Replace(" ", "");
	str_json.Replace("\n", "");//ȥ�����еĿո񣬻س���//
	strContent.Format("%08d%s", str_json.GetLength(), str_json);
	LOG_DD(LOGTYPE_DEBUG, TRADELOG, "AddMsgContent--������Ϊ[%s]", strContent);
	CString strDes = "";
	strDes = Encode_3Des(strContent);
	return strDes;
}
//ǩ��
BOOL CTrade::Login(const char* pUrl)
{
	CHttpClient httpClient;
	m_strLastErr = "";
	httpClient.addParam("jsonparam", AddMsgContent("2011000001"));//addParam ��ȥ��jsonparam= ��&
	CString strBack = httpClient.doPost(pUrl);
	CString strGBKRsp = Decode_3Des(strBack);
	ConvertUtf8ToGBK(strGBKRsp);
	if (FALSE == IsJsonData(strGBKRsp.GetBuffer(0)))
	{
		m_strLastErr = "��json�ַ���";
		return FALSE;
	}
	json jMsg = json::parse(strGBKRsp.GetBuffer(0));
	if (jMsg.find("body") == jMsg.end())
	{
		m_strLastErr = "��ȡ�ֶ�ʧ��[body]";
		return FALSE;
	}
	json jBody = jMsg["body"];//����ͬһ������find
	if (jBody.find("result") == jBody.end() || jBody.find("msg") == jBody.end() || jBody.find("data") == jBody.end())
	{
		m_strLastErr = "��ȡ�ֶ�ʧ��[result][msg][body]";
		return FALSE;
	}
	json jData = jBody["data"];
	if (jData.find("organnbr") != jData.end())
	{
		g_strOrgCode = jData["organnbr"].get<std::string>().c_str();
	}
	if (jBody["result"].get<std::string>() != "0")
	{
		m_strLastErr.Format("error.result =%s,msg = %s", jBody["result"].get<std::string>().c_str(), jBody["msg"].get<std::string>().c_str());
		return FALSE;
	}
	return TRUE;
}
//��ȡ��������Ŀjson����
BOOL CTrade::GetPrgms(const char* pUrl, CString strJson,CString &strJsonOut)
{
	CHttpClient httpClient;
	m_strLastErr = "";
	CString str = AddMsgContent("2011000002", g_strOrgCode, strJson);
	httpClient.addParam("jsonparam", str);//addParam ��ȥ��jsonparam= ��&
	CString strBack = httpClient.doPost(pUrl); 
	CString strGBKRsp = Decode_3Des(strBack);
	ConvertUtf8ToGBK(strGBKRsp);
	LOG_DD(LOGTYPE_DEBUG, TRADELOG, "GetPrgms--��ȡ���Ľ�Ŀ��ϢΪ[%s]", strGBKRsp);
	if (FALSE == IsJsonData(strGBKRsp.GetBuffer(0)))
	{
		m_strLastErr = "��json�ַ���,"+ strGBKRsp;
		return FALSE;
	}
	json jMsg = json::parse(strGBKRsp.GetBuffer(0));
	if (jMsg.find("body") == jMsg.end())
	{
		m_strLastErr = "��ȡ�ֶ�ʧ��[body]";
		return FALSE;
	}
	json jBody = jMsg["body"];//����ͬһ������find
	if (jBody.find("result") == jBody.end() || jBody.find("msg") == jBody.end() || jBody.find("data") == jBody.end())
	{
		m_strLastErr = "��ȡ�ֶ�ʧ��[result][msg][body]";
		return FALSE;
	}
	if (jBody["result"].get<std::string>() != "0")
	{
		m_strLastErr.Format("error.result =%s,msg = %s", jBody["result"].get<std::string>().c_str(), jBody["msg"].get<std::string>().c_str());
		return FALSE;
	}
	//�ҵ���Ŀ
	std::string strTemp = jMsg.dump(4);//ȫ������
	strJsonOut = strTemp.c_str();
	return TRUE;
}
//�ϴ���Ŀ�·�״̬
BOOL CTrade::UpLoadProGrameStatus(const char* pUrl, CString strBody)
{
	CHttpClient httpClient;
	m_strLastErr = "";
	httpClient.addParam("jsonparam", AddMsgContent("2011000003", g_strOrgCode,strBody));//addParam ��ȥ��jsonparam= ��&
	CString strBack = httpClient.doPost(pUrl);
	CString strGBKRsp = Decode_3Des(strBack);
	ConvertUtf8ToGBK(strGBKRsp);
	if (FALSE == IsJsonData(strGBKRsp.GetBuffer(0)))
	{
		m_strLastErr = "��json�ַ���";
		return FALSE;
	}
	json jMsg = json::parse(strGBKRsp.GetBuffer(0));
	if (jMsg.find("body") == jMsg.end())
	{
		m_strLastErr = "��ȡ�ֶ�ʧ��[body]";
		return FALSE;
	}
	json jBody = jMsg["body"];//����ͬһ������find
	if (jBody.find("result") == jBody.end() || jBody.find("msg") == jBody.end() || jBody.find("data") == jBody.end())
	{
		m_strLastErr = "��ȡ�ֶ�ʧ��[result],[msg],[body]";
		return FALSE;
	}
	if ("0" != jBody["result"])
	{
		m_strLastErr.Format("error.result =%s,msg = %s", jBody["result"].get<std::string>().c_str(), jBody["msg"].get<std::string>().c_str());
		return FALSE;
	}
	return TRUE;
}
//�ϴ��豸״̬
BOOL CTrade::UpLoadDeviceStatus(const char* pUrl)
{
	CHttpClient httpClient;
	CString strBody = "";
	httpClient.addParam("jsonparam", AddMsgContent("2011000008", g_strOrgCode,strBody));
	CString strBack = httpClient.doPost(pUrl);
	CString strGBKRsp = Decode_3Des(strBack);
	ConvertUtf8ToGBK(strGBKRsp);
	if (FALSE == IsJsonData(strGBKRsp.GetBuffer(0)))
	{
		m_strLastErr = "��json�ַ���";
		return FALSE;
	}
	json jMsg = json::parse(strGBKRsp.GetBuffer(0));
	if (jMsg.find("body") == jMsg.end())
	{
		m_strLastErr = "��ȡ�ֶ�ʧ��[body]";
		return FALSE;
	}
	json jBody = jMsg["body"];//����ͬһ������find
	if (jBody.find("result") == jBody.end() || jBody.find("msg") == jBody.end() || jBody.find("data") == jBody.end())
	{
		m_strLastErr = "��ȡ�ֶ�ʧ��[result],[msg],[body]";
		return FALSE;
	}
	if ("0" != jBody["result"])
	{
		m_strLastErr.Format("error.result =%s,msg = %s", jBody["result"].get<std::string>().c_str(), jBody["msg"].get<std::string>().c_str());
		return FALSE;
	}
	return TRUE;
}

BOOL CTrade::UpLoadMMPDeviceStatus(const char* pUrl, CString steMMPDeviceCode)
{
	CHttpClient httpClient;
	CString strBody = "";
	strBody.Format("\"deviceCode\":\"%s\"", steMMPDeviceCode);
	httpClient.addParam("jsonparam", AddMsgContent("2011000008", g_strOrgCode, strBody));
	CString strBack = httpClient.doPost(pUrl);
	CString strGBKRsp = Decode_3Des(strBack);
	ConvertUtf8ToGBK(strGBKRsp);
	if (FALSE == IsJsonData(strGBKRsp.GetBuffer(0)))
	{
		m_strLastErr = "��json�ַ���";
		return FALSE;
	}
	json jMsg = json::parse(strGBKRsp.GetBuffer(0));
	if (jMsg.find("body") == jMsg.end())
	{
		m_strLastErr = "��ȡ�ֶ�ʧ��[body]";
		return FALSE;
	}
	json jBody = jMsg["body"];//����ͬһ������find
	if (jBody.find("result") == jBody.end() || jBody.find("msg") == jBody.end() || jBody.find("data") == jBody.end())
	{
		m_strLastErr = "��ȡ�ֶ�ʧ��[result],[msg],[body]";
		return FALSE;
	}
	if ("0" != jBody["result"])
	{
		m_strLastErr.Format("error.result =%s,msg = %s", jBody["result"].get<std::string>().c_str(), jBody["msg"].get<std::string>().c_str());
		return FALSE;
	}
	return TRUE;
}

bool IsJsonData(std::string strData)
{
	if (strData[0] != '{')
		return false;
	int num = 1;
	for (int i = 1; i < strData.length(); ++i)
	{
		if (strData[i] == '{')
		{
			++num;
		}
		else if (strData[i] == '}')
		{
			--num;
		}

		if (num == 0)
		{
			return true;
		}
	}
	return false;
}