#include "stdafx.h"
#include "COMMFCN.h"

UINT g_bLogType = LOGTYPE_DEBUG;
CConfig	g_Config;

BOOL Automatic_log(BYTE bType, LPCTSTR strFile, LPCTSTR lpszFormat, ...)
{
	char* pBuf = (char*)malloc(MAX_BUFF+1);
	if(!pBuf) return FALSE;
	memset(pBuf, 0x00, MAX_BUFF+1);

	va_list argList;
	va_start(argList, lpszFormat);
	int iRet = _vsnprintf(pBuf, MAX_BUFF, lpszFormat, argList);
	if(iRet==-1)
	{
		char* pBuf2 = (char*)realloc(pBuf, 50*MAX_BUFF+1);
		memset(pBuf2, 0x00, 50*MAX_BUFF+1);
		if(pBuf2)
		{
			pBuf = pBuf2;
			_vsnprintf(pBuf, 50*MAX_BUFF, lpszFormat, argList);
		}
	}
	va_end(argList);

	BOOL bRet = FALSE;
	switch(g_bLogType & bType){
	case LOGTYPE_DEBUG:
		{
			CString strContent = "";
			strContent.Format("<<%s#%s>>	%s",GetCurTime(TIME_LONG,NULL).c_str(),LOG_MSG,pBuf);
			bRet = WriteFileEx(FILE_IMPORTANT, 
				GetPathLogFile(strFile,"").GetBuffer(0), strContent.GetBuffer(0), NULL);
		}
		break;
	case LOGTYPE_ERROR:
		{
			CString strContent = "";
			strContent.Format("<<%s#%s>>	%s",GetCurTime(TIME_LONG,NULL).c_str(),LOG_ERR,pBuf);
			bRet = WriteFileEx(FILE_IMPORTANT, 
				GetPathLogFile(strFile,"").GetBuffer(0), strContent.GetBuffer(0), NULL);
		}
		break;
	case LOGTYPE_SPECIAL:
		{
			CString strContent = "";
			strContent.Format("<<%s#%s>>	",GetCurTime(TIME_LONG,NULL).c_str(),pBuf);
			bRet = WriteFileEx(FILE_IMPORTANT, 
				GetPathLogFile(strFile,"").GetBuffer(0), strContent.GetBuffer(0), NULL);
		}
		break;
	default:
		break;
	}

	free(pBuf);
	return bRet;
}

BOOL Automatic_level(UINT uLevel)
{
	g_bLogType = uLevel;
	return TRUE;
}

CString ReadFileContent(const char* pFile)
{
	CStdioFile file;
	CString szLine = "";
	CString strText = "";
	if (!file.Open(pFile, CFile::modeRead))
	{
		return "";
	}
	//���ж�ȡ�ַ���
	while( file.ReadString( szLine ) )
	{
		strText += szLine;
	}
	file.Close();
	return strText;
}

BOOL WriteFileContent(const char* pFile, CString strContent)
{
	CStdioFile file;
	CString szLine = "";
	CString strText = "";
	file.Open(pFile, CFile::modeWrite | CFile::modeCreate);
	file.Seek(0,CFile::end);
	file.WriteString(strContent);
	file.Close();
	return TRUE;
}

BOOL GetHttpMsg(CString strHttpAddr, CString& strHtml)
{
	CInternetSession session;
	CHttpFile *file = NULL;
	try
	{
		file = (CHttpFile*)session.OpenURL(strHttpAddr);
	}
	catch(CInternetException * m_pException)
	{
		file = NULL;
		m_pException->m_dwError;
		m_pException->Delete();
		session.Close();
		return FALSE;
	}
	CString strLine;
	if(file != NULL)
	{
		while(file->ReadString(strLine) != NULL)
		{
			strHtml += strLine;
		}
	}
	else
	{
		return FALSE;
	}
	session.Close();
	file->Close();
	delete file;
	file = NULL;
	return TRUE;
}
//��ָ��url������, ���������Ľ��
CString SendURLPost(CString strServerName, CString strFormActionUrl, CString strPostStr)
{
	CString strFormData(strPostStr.GetBuffer(0));    // ��Ҫ�ύ������
	CInternetSession sess("HttpClient");

	//���ᳬʱûЧ����, ���ͳ�ʱ����ճ�ʱ����, ���ᳬʱ�����ö��߳�WaitForSingleObject��ʵ��
	sess.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 5000); // 5000��������ӳ�ʱ
	sess.SetOption(INTERNET_OPTION_SEND_TIMEOUT, 5000); // 5000����ķ��ͳ�ʱ
	sess.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, 5000); // 5000����Ľ��ճ�ʱ
	sess.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 5000); // 5000����ķ��ͳ�ʱ
	sess.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 5000); // 5000����Ľ��ճ�ʱ
	sess.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1); // 1������

	CString strHeaders = "Content-Type: application/x-www-form-urlencoded"; // ����ͷ
	CHttpConnection *pConnection = sess.GetHttpConnection(strServerName.GetBuffer(0));
	CHttpFile *pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST, strFormActionUrl.GetBuffer(0));

	CString strSentence, strGetSentence = "";
	if(pFile)
	{
		BOOL result = pFile->SendRequest(strHeaders, (LPVOID)(LPCTSTR)strFormData, strFormData.GetLength());
		while(pFile->ReadString(strSentence))  // ��ȡ�ύ���ݺ�ķ��ؽ��
			strGetSentence = strGetSentence + strSentence + char(13) + char(10);
		pFile->Close();
		delete pFile;
		sess.Close();
		return strGetSentence;
	}
	return "";
}

//CString GetCurTime(TIME_TYPE nType)
//{
//	CString strTime = "";
//	CTime tmCur = CTime::GetCurrentTime();
//	switch(nType)
//	{
//	case DATE_LONG:
//		strTime = tmCur.Format("%Y-%m-%d %H:%M:%S");
//		break;
//	case DATE_LONG2:
//		strTime = tmCur.Format("%Y-%m-%d %H:%M:%S.000");
//		break;
//	case DAY_NORMAL:
//		strTime = tmCur.Format("%Y%m%d");
//		break;
//	case TIME_NORMAL:
//		strTime = tmCur.Format("%H%M%S");
//		break;
//	case DATE_NORMAL:
//		strTime = tmCur.Format("%Y%m%d%H%M%S");
//		break;
//	case DAY_SHORT:
//		strTime = tmCur.Format("%m%d");
//		break;
//	case DAY_LONG:
//		strTime = tmCur.Format("%Y-%m-%d");
//		break;
//	case TIME_LONG:
//		strTime = tmCur.Format("%H:%M:%S");
//		break;
//	case TIME_SHORT1:
//		strTime = tmCur.Format("%H:%M");
//		break;
//	case TIME_SHORT2:
//		strTime = tmCur.Format("%H %M");
//		break;
//	case MONTH_NORMAL:
//		strTime = tmCur.Format("%Y%m");
//		break;
//	case MONTH_LONG:
//		strTime = tmCur.Format("%Y��%m��%d��");
//		break;
//	case BANK_NORMAL:
//		strTime = tmCur.Format("%m%d%H%M%S");
//		break;
//	}
//	return strTime.GetBuffer(0);
//}

CString GetFileName(CString strFilePath)
{
	CString str = strFilePath;
	str.Replace("\\", "/");
	return str.Mid(str.ReverseFind('/')+1, str.GetLength());
}
