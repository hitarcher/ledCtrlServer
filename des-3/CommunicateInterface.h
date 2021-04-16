/*
* Copyright (c) YYYY��ĳ��˾
* All rights reserved.
*
* �ļ����ƣ�CommunicateInterface.h
* ժ    Ҫ��ʵ����ATMP��ͨ�ż����㷨
*
* ��ǰ�汾��1.0.4.0
* ��    �ߣ�mingl
* ������ڣ�2017/2/14
*/
#pragma once
#ifndef __COMMUNICATE_INTERFACE_H__
#define __COMMUNICATE_INTERFACE_H__

#ifdef RN_API_EXPORTS
#define RN_API __declspec(dllexport) WINAPI
#else
#define RN_API __declspec(dllimport) WINAPI
#endif

#include <string>
using namespace std;

typedef DWORD RN_RESULT;
typedef DWORD RN_STATUS;

typedef enum {
	LOGLEVEL_NULL    = 0,
	LOGLEVEL_ERR     = 1,
	LOGLEVEL_ENTER   = 2,
	LOGLEVEL_DETAIL  = 3
}LOGLEVEL;

typedef enum {
	SUCCESS       = 0,	// �ɹ�
	ERR_LMK_NUL   = 1,	// LMKΪ��
	ERR_LMK_FORM  = 2,	// LMK��ʽ����
	ERR_WK_NUL    = 3,	// WKΪ��
	ERR_WK_FORM   = 4,	// WK��ʽ����
	ERR_MAC_FROM  = 5,	// ����MAC�����ݸ�ʽ����
	ERR_COMM_CONN = 6,	// �޷����ӷ�����
	ERR_COMM_FROM = 7,	// ���ݰ�����ʧ��
	ERR_ECB_EN    = 8,	// 3DES ECBģʽ����ʧ��
	ERR_ECB_DE    = 9	// 3DES ECBģʽ����ʧ��
}ERR_CODE;

typedef enum {
	encrpyt = 0,
	decrypt
}ENCRYPT_TYPE;

/*
* �������ܣ����ñ���/ͨ������Կ
* ���������strWK  ����ԿBCD��8421���룻16λ
* ���������
* ����ֵ  ���� CCommunicateWithAtmp::ERR_CODE
* ��ע    �������ټ���mac֮ǰִ��
*/
EXTERN_C RN_RESULT RN_API COMM_SetLMK(const char* strLMK);
EXTERN_C RN_RESULT RN_API COMM_SetLMK3(const char* strLMK);

/*
* �������ܣ����ù�����Կ
* ���������strWK  ������ԿBCD��8421���룻16λ
* ���������
* ����ֵ  ���� CCommunicateWithAtmp::ERR_CODE
* ��ע    �������ټ���mac֮ǰִ��
*/
EXTERN_C RN_RESULT RN_API COMM_SetWK(const char* strWK);
EXTERN_C RN_RESULT RN_API COMM_SetWK3(const char* strWK);

/*
* �������ܣ�����MAC ANSI X9.9 ��DES
* ���������strSecurityMsg  ��Ҫ����MAC�����ݣ����ȱ�����ż��
* ���������strMAC          ������
* ����ֵ  ���� CCommunicateWithAtmp::ERR_CODE
* ��ע    ���������������LMK��WK֮�����
*/
EXTERN_C RN_RESULT RN_API COMM_ComputeMAC_X99(const char* strSecurityMsg, char* strMAC);
/*
* �������ܣ�����MAC ANSI X9.19 3DES˫��������
* ���������strSecurityMsg  ��Ҫ����MAC�����ݣ����ȱ�����ż��
* ���������strMAC          ������
* ����ֵ  ���� CCommunicateWithAtmp::ERR_CODE
* ��ע    ���������������LMK��WK֮�����
*/
EXTERN_C RN_RESULT RN_API COMM_ComputeMAC_X919(const char* strSecurityMsg, char* strMAC);
EXTERN_C RN_RESULT RN_API COMM_ComputeMACPOS(const char* strSecurityMsg, char* strMAC);

EXTERN_C RN_RESULT RN_API COMM_ComputePIN(const unsigned char* ppinkblock, char* strPIN, int nEncrypt); // 1 ������  2 ˫����  3 ���ܣ��ԣ�

EXTERN_C RN_RESULT RN_API COMM_DES(const char* strKey, const char* strIn, char* strOut, ENCRYPT_TYPE bEncrypt); // bEncrypt 0���� 1����
EXTERN_C RN_RESULT RN_API COMM_DES3(const char* strKey, const char* strIn, char* strOut, ENCRYPT_TYPE bEncrypt);// bEncrypt 0���� 1����

/*
* �������ܣ�3DES ECB�ӽ���
* ���������strKey 24���ֽڵ���Կ
*           strPlain  ���ģ�����ʱΪ��Σ�����ʱΪ����
*           strCipher ���ģ�����ʱΪ���Σ�����ʱΪ��Σ���ʽΪbase64
*           bEncrypt  enum ENCRYPT_TYPE ���ݲ������ӽ���
* �����������
* ����ֵ  ���� CCommunicateWithAtmp::ERR_CODE
*/
EXTERN_C RN_RESULT RN_API COMM_DES3_ECB(std::string strKey, std::string& strPlain, std::string& strCipher, ENCRYPT_TYPE bEncrypt);// bEncrypt 0���� 1����

/*
* �������ܣ������ݴ��͸�
* ���������strIP      ������ip
*           uPort      �������˿�
*           strMsgpack ���Ͱ�
*           dwTimeout  ��ʱʱ��
* ���������strReceipt ��ִ,���Ȳ��õ���1024
* ����ֵ  ���� CCommunicateWithAtmp::ERR_CODE
* ��ע    ������������
*/
EXTERN_C RN_RESULT RN_API COMM_CommunicateWithAtmp(const char* strIP, UINT uPort, const char* strMsgpack, char* strReceipt, DWORD dwTimeout);



#endif