#ifndef __BASE_PACK_H__
#define __BASE_PACK_H__

#define SAFE_DELETE_PACK(p)	{if(p){if((p)->pszData){delete []((p)->pszData);}delete (p);(p) = NULL;}}

//消息包头类型
#define	USE_BASE_TYPE_HEADER	1
#define USE_UNION_HEADER		2
#define USE_STRING_HEADER		3

typedef struct BASE_MSG		//基本的包头，所有包均包含此包头
{
	UINT 	uSize;
	UINT	uType;
	BASE_MSG()
	{
		memset(this,0x00,sizeof(BASE_MSG));
	}
	BASE_MSG(UINT Size,UINT Type)
	{
		uSize = Size;
		uType = Type;
	}
}*LPBASE_MSG;

typedef struct BASE_MSG_PACK
{
	int		nSize;
	char*	pszData;
	BASE_MSG_PACK()
	{
		nSize=0;
		pszData=NULL;
	}
	int GetHeaderSize()	//获得包头大小，必须填写此函数
	{
		return sizeof(BASE_MSG);
	}
	UINT GetPackSize(char* szHeaderPack)	//获得包的大小，包括包头长度。必须填写此函数
	{
		LPBASE_MSG pMsg = (LPBASE_MSG)szHeaderPack;
		return pMsg->uSize;
	}
}*LPBASE_MSG_PACK;

#endif
