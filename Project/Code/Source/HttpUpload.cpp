#include "stdafx.h"
#include "HttpUpload.h"


CHttpUpload::CHttpUpload()
{
	WSADATA  wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);		
	DataVarInit();
}

CHttpUpload::~CHttpUpload()
{
	WSACleanup();
}

void CHttpUpload::DataVarInit()
{
	m_hSock     = INVALID_SOCKET;
	m_nSvrPort  = 80;
	
	m_bChunkTransferEncoding = FALSE;

	memset(m_szRetData, 0, sizeof(m_szRetData));
	memset(m_szReqObj, 0, sizeof(m_szReqObj));
	memset(m_szSvrName, 0, sizeof(m_szSvrName));
}

int CHttpUpload::Init(const char* cszUrl, int nUrlLen)
{
	DataVarInit();

	if(!UrlParse(cszUrl, nUrlLen))
	{
		return ERROR_CODE_ELSE;
	}

	if (!CreateSock())
	{
		return ERROR_CODE_ELSE;
	}

	if (!ConnectSvr())
	{
		return ERROR_CODE_CONNECT_FAILURE;
	}

	return 0;
}

BOOL CHttpUpload::CreateSock()
{
	if (m_hSock == INVALID_SOCKET)
	{
		m_hSock = socket(AF_INET, SOCK_STREAM, 0);
		if (m_hSock == INVALID_SOCKET)
			return FALSE;
	}
	
	return TRUE;
}

BOOL CHttpUpload::ConnectSvr()
{
	if (m_hSock == INVALID_SOCKET)
		return FALSE;
	
	sockaddr_in addrSvr;
	memset(&addrSvr, 0, sizeof(addrSvr));
	
	PHOSTENT pHost = gethostbyname(m_szSvrName);
	if (pHost == NULL)
		return FALSE;
	
	addrSvr.sin_family = AF_INET;
	addrSvr.sin_port   = htons((u_short)m_nSvrPort);
	addrSvr.sin_addr.s_addr = *(ULONG*)pHost->h_addr_list[0];
	if (SOCKET_ERROR == connect(m_hSock, (sockaddr*)&addrSvr, sizeof(addrSvr)))
		return FALSE;
	
	return TRUE;
}

BOOL CHttpUpload::AddFormTextField(const char* cszFieldName,  const char* cszValue)
{
	if ((cszFieldName == NULL) || (cszValue == 0))
		return FALSE;

	char szSend[2 * 1024];
	sprintf_s(szSend,sizeof(szSend), "--FORM_BOUNDARY\r\ncontent-disposition: form-data; name=\"%s\"\r\n\r\n", cszFieldName);
	strcat_s(szSend,sizeof(szSend), cszValue);
	strcat_s(szSend,sizeof(szSend), "\r\n");
	m_strFormDataContent += szSend;

	return TRUE;
}

BOOL CHttpUpload::AddFormDataEndFlag()
{
	m_strFormDataContent += "--FORM_BOUNDARY--\r\n";

	return TRUE;
}

BOOL CHttpUpload::AddFormFileField(
	 const char* cszFieldName,  
	 const char* cszFileName,  
	 BOOL bIsBinary /* = FALSE  */
	 )
{
	if ((cszFieldName == NULL) || (cszFileName == NULL))
		return FALSE;

	//content type
	HKEY	hKEY;
	char* pszFileExt;
	char  szContentType[80] = {0};
	DWORD dwLen;
	dwLen = sizeof(szContentType);
	pszFileExt = strrchr((char*)cszFileName, '.');
	if(::RegOpenKeyEx(HKEY_CLASSES_ROOT, pszFileExt, 0, KEY_QUERY_VALUE, &hKEY)==ERROR_SUCCESS)
	{
		if(::RegQueryValueEx(hKEY, TEXT("Content Type"), NULL, NULL, (LPBYTE)szContentType, (unsigned long*)&dwLen)!=ERROR_SUCCESS)
			strcpy_s(szContentType,sizeof(szContentType), "application/octet-stream");
		::RegCloseKey(hKEY);
	}
	else
		strcpy_s(szContentType, sizeof(szContentType),"application/octet-stream");

	//form field header
	char szSend[1024] = {0};
	char szFilename[100] = {0};
	strcpy_s(szFilename, sizeof(szFilename),strrchr(cszFileName, '\\') + 1);
	sprintf_s(szSend, sizeof(szSend),
		"--FORM_BOUNDARY\r\ncontent-disposition: form-data; name=\"%s\"; filename=\"%s\"\r\nContent-Type: %s\r\n", 
		cszFieldName, szFilename, szContentType);
	if (bIsBinary)
		strcat_s(szSend, sizeof(szSend),"Content-Transfer-Encoding: Base64\r\n");
	strcat_s(szSend,sizeof(szSend), "\r\n");
	m_strFormDataContent += szSend;

	//file content encoded with base64
	BYTE pbDataBuf[3] = {0};
	char szEncodeStr[5];
	DWORD dwBytesRead;
	int nCurPosValue = 0;
	HANDLE hFile = ::CreateFile(cszFileName, GENERIC_READ, 0, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;
	
	while(TRUE)
	{
		memset(szEncodeStr, 0, sizeof(szEncodeStr));
		if (0 == ::ReadFile(hFile, (LPVOID)pbDataBuf, 3, &dwBytesRead, NULL))
			return FALSE;
		if (bIsBinary) //encode data
		{   
			switch(dwBytesRead)
			{
			case 3:
				nCurPosValue = (pbDataBuf[0] >> 2) & (0x3F);
				szEncodeStr[0] = BASE64_Alphabet[nCurPosValue];  //first 6-bits
				nCurPosValue = ((pbDataBuf[0] << 4) & (0x30))  + ((pbDataBuf[1] >> 4) & (0x0F));
				szEncodeStr[1] = BASE64_Alphabet[nCurPosValue];  //second 6-bits
				nCurPosValue = ((pbDataBuf[1] << 2) & (0x3C)) + ((pbDataBuf[2] >> 6) & (0x03));
				szEncodeStr[2] = BASE64_Alphabet[nCurPosValue];  //third 6-bits
				nCurPosValue = pbDataBuf[2] & (0x3F);
				szEncodeStr[3] = BASE64_Alphabet[nCurPosValue]; //forth 6-bits
				szEncodeStr[4] = 0;
				break;
			case 2:
				nCurPosValue = (pbDataBuf[0] >> 2) & (0x3F);
				szEncodeStr[0] = BASE64_Alphabet[nCurPosValue];  //first 6-bits
				nCurPosValue = ((pbDataBuf[0] << 4) & (0x30))  + ((pbDataBuf[1] >> 4) & (0x0F));
				szEncodeStr[1] = BASE64_Alphabet[nCurPosValue];  //second 6-bits
				nCurPosValue = (pbDataBuf[1] << 2) & (0x3C);
				szEncodeStr[2] = BASE64_Alphabet[nCurPosValue];  //third 6-bits 
				szEncodeStr[3] = '=';
				szEncodeStr[4] = 0;
				break;
			case 1:
				nCurPosValue = (pbDataBuf[0] >> 2) & (0x3F);
				szEncodeStr[0] = BASE64_Alphabet[nCurPosValue];  //first 6-bits
				nCurPosValue = (pbDataBuf[0] << 4) & (0x30);
				szEncodeStr[1] = BASE64_Alphabet[nCurPosValue];  //second 6-bits
				szEncodeStr[2] = '=';
				szEncodeStr[3] = '=';
				szEncodeStr[4] = 0;
				break;
			default:
				szEncodeStr[0] = 0;
			}
		}
		else
		{
			if (dwBytesRead == 0)
				szEncodeStr[0] = 0;
			else
			{
				memset(szEncodeStr, 0, sizeof(szEncodeStr));
				memcpy(szEncodeStr, pbDataBuf, dwBytesRead);
			}
		}
		if (szEncodeStr[0] == 0)
		{
			::CloseHandle(hFile);
			hFile = INVALID_HANDLE_VALUE;
			break;
		}
		m_strFormDataContent += szEncodeStr;
	}

	m_strFormDataContent += "\r\n";
	
	if (hFile != INVALID_HANDLE_VALUE)
		::CloseHandle(hFile);

	return TRUE;
}

BOOL  CHttpUpload::Request()
{	
	char	szSend[1024] = {0};
	int		nLen;

	AddFormDataEndFlag();

	//request web server
	sprintf_s(szSend, sizeof(szSend),"POST %s HTTP/1.1\r\nHOST: %s\r\nContent-Length: %d\r\n", 
		m_szReqObj, m_szSvrName, m_strFormDataContent.size());
	strcat_s(szSend, sizeof(szSend),"Connection: close\r\n");
	strcat_s(szSend, sizeof(szSend),"Content-type: multipart/form-data, boundary=FORM_BOUNDARY\r\n\r\n");
	nLen = send(m_hSock, szSend, (int)strlen(szSend), 0);
	if ((nLen == SOCKET_ERROR) || (nLen < (int)strlen(szSend)))
		return FALSE;
	AMLOGDEVINFO("%s", szSend);
	nLen = send(m_hSock, (const char*)m_strFormDataContent.c_str(), (int)m_strFormDataContent.size(), 0);
	if ((nLen == SOCKET_ERROR) || (nLen < (int)m_strFormDataContent.size()))
		return FALSE;

	AMLOGDEVINFO("%s",m_strFormDataContent.c_str());
	return TRUE;
}

char* CHttpUpload::RetRecvDataPt()
{
	if (!RecvResponse())
	{
		memset(m_szRetData, 0, sizeof(m_szRetData));
		AMLOGDEVINFO("RetRecvDataPt = %s",m_szRetData);
	}
	if (m_szRetData[0] == 0)
		return NULL;

	return m_szRetData;
}

BOOL CHttpUpload::RecvResponse()
{
	char	szRetHeader[1024] = {0}; 	
	int		nLen;
	char    szRecvBuf[1024] = {0};
	char*   pTemp = NULL;
	
	//receive header
	while(TRUE)
	{
		nLen = recv(m_hSock, szRecvBuf, sizeof(szRecvBuf), 0);
		if (nLen == SOCKET_ERROR)
			return FALSE;
		
		AMLOGDEVINFO("%s",szRecvBuf);
		pTemp = strstr(szRecvBuf, "\r\n\r\n");
		if (pTemp != NULL)    //header receive finish
		{
			*pTemp = 0;
			strcat_s(szRetHeader,sizeof(szRetHeader), szRecvBuf);
			pTemp += 4;
			nLen = nLen - (int)strlen(szRecvBuf) - 4;
			memcpy((void*)m_szRetData, pTemp, nLen);
			break;
		}
		
		strcat_s(szRetHeader, sizeof(szRetHeader),szRecvBuf); 
	}
	
	//response header parse
	if (!ParseRetHeader(szRetHeader, (int)strlen(szRetHeader)))
		return FALSE;

	while(TRUE)
	{
		memset(szRecvBuf, 0, sizeof(szRecvBuf));
		nLen = recv(m_hSock, szRecvBuf, sizeof(szRecvBuf), 0);
		if (nLen == SOCKET_ERROR)
			return FALSE;
	
		if (nLen == 0)  //data receive finish
			break;
		strcat_s(m_szRetData,sizeof(m_szRetData), szRecvBuf);
	}
	
	//chunk process
	if (m_bChunkTransferEncoding)
	{
		char szSectionLen[50];
		int  nSectionLen;
		char* pEndPos = NULL;
		char* pStartPos = NULL;
		int   nDataLenCopyed = 0;
		
		pStartPos = m_szRetData;
		while(*pStartPos != 0)
		{
			pEndPos = strstr(pStartPos, "\r\n");
			memset(szSectionLen, 0, sizeof(szSectionLen));
			strcpy_s(szSectionLen,sizeof(szSectionLen), "0x");
			memcpy(szSectionLen + 2, pStartPos, pEndPos - pStartPos);
			nSectionLen = HexStrToInt(szSectionLen, (int)strlen(szSectionLen));
			if (nSectionLen == 0)
				break;
			
			pStartPos = pEndPos + 2;
			pEndPos = pStartPos + nSectionLen;
			memcpy(m_szRetData + nDataLenCopyed, pStartPos, pEndPos - pStartPos);
			nDataLenCopyed += nSectionLen;

			pStartPos = pEndPos + 2;
		}
		
		*(m_szRetData + nDataLenCopyed) = 0;
	}

	if (m_hSock != INVALID_SOCKET)
	{
		::closesocket(m_hSock);
		m_hSock = INVALID_SOCKET;
	}

	return TRUE;
}

BOOL CHttpUpload::UrlParse(const char* cszUrl, int nUrlLen)
{
	if ((cszUrl == NULL) || (nUrlLen == 0))
		return FALSE;
	
	if (_strnicmp(cszUrl, "http://", strlen("http://")))
		return FALSE;
	
	char  szTemp[1024] = {0};
	char* pPos = (char*)cszUrl;
	pPos += 7;
	strcpy_s(szTemp, sizeof(szTemp),pPos);
	pPos = strchr(szTemp, '/');
	strcpy_s(m_szReqObj,sizeof(m_szReqObj), pPos);   //get object requested
	*pPos = 0;
	strcpy_s(m_szSvrName,sizeof(m_szSvrName),szTemp);//get server name
	
	return TRUE;
}

BOOL CHttpUpload::ParseRetHeader(const char* cszRetHeader, int nHeaderLen)
{
	if ((cszRetHeader == NULL) || (nHeaderLen == 0))
		return FALSE;

	char*	pTemp = NULL;
	char    szStatusStr[4] = {0};
	int     nStatusCode;

	//response code
	pTemp = strchr((char*)cszRetHeader, ' ');
	pTemp++;
	memcpy((void*)szStatusStr, (void*)pTemp, 3);
	nStatusCode = atoi(szStatusStr);
	if ((nStatusCode < 200) || (nStatusCode >= 300))
		return FALSE;
	
	//chunking ?
	if (strstr(cszRetHeader, "Transfer-Encoding: chunked\r\n"))
		m_bChunkTransferEncoding = TRUE;
	else
		m_bChunkTransferEncoding = FALSE;

	return TRUE;
}

/*
first: 	0xabc101
second:	10000001
 */
int  CHttpUpload::HexStrToInt(const char* cszHexStr, int nStrLen)
{
	if ((cszHexStr == NULL) || (nStrLen == 0))
		return -1;
	const char* pstr=cszHexStr;
	int nResult = 0,i;
	for(i = 0; cszHexStr[i];i++)
	{
		if(cszHexStr[i]=='x' || cszHexStr[i]=='X')
		{
			pstr=&cszHexStr[i+1];
			break;
		}
	}
	for(i = 0; pstr[i];i++)
	{
		if((pstr[i]>='a'&&pstr[i]<='f'))
		{
			nResult = nResult*16;
			nResult	+= pstr[i]-'a'+10;
		}
		else if((pstr[i]>='A'&&pstr[i]<='F'))
		{
			nResult = nResult*16;
			nResult	+= pstr[i]-'A'+10;
		}
		else if((pstr[i]>='0'&&pstr[i]<='9'))
		{
			nResult = nResult*16+pstr[i]-'0';
		}
	}
	
	return nResult;
} 