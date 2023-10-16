#include "StdAfx.h"
#include <sys/stat.h>

#ifdef WIN32
	// Windows Head Files
	#include <sys/utime.h>
	#include <winsock.h>
	#pragma comment(lib, "wsock32.lib")
#else
	// Unix Head Files
	#include <stdlib.h>
	#include <ctype.h>
	#include <utime.h>
	#include <unistd.h>
	#include <netdb.h>
	#include <sys/socket.h>
	#include <sys/socketvar.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif	// WIN32

#include "HttpDownload.h"
#define strdup _strdup

enum HTTPSTATUS
{
	HTTP_OK = 0,
	HTTP_PARTIAL,
	HTTP_ERROR,
	HTTP_REDIRECT
};

#ifndef INVALID_SOCKET
#define INVALID_SOCKET  (unsigned int)(~0)
#endif

#ifndef SOCKET_ERROR
#define SOCKET_ERROR            (-1)
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#define BUF_LEN 10240
char	g_szBase64TAB[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
int		g_nBase64Mask[]= { 0, 1, 3, 7, 15, 31, 63, 127, 255 };

bool DefaultCallback(long wParam, long lParam)
{
	return true;
}

//////////////////////////////////////////////////////////////////////////////////
//	函数名：int Base64Encode(
//				IN LPCTSTR lpszEncoding,
//				char* lpszOutEncoded
//				long lOutSize) 
//	用  途：BASE64编码
//	对全局变量的影响：无
//	参  数：
//		lpszEncoding : 待编码的字符串
//		strEncoded   : 编码结果(调用前需要开出足够的内存)
//		lOutSize	 : 编码结果内存大小
//	返回值：int，编码后的长度，-1表示内存不够
////////////////////////////////////////////////////////////////////////////////
int Base64Encode(const char* lpszEncoding, char* lpszOutEncoded, long lOutSize)
{
	int nDigit;
	int nNumBits = 6;
	int nIndex = 0;
	size_t nInputSize = 0;
	int nEncodeLength = 0;

	memset(lpszOutEncoded, 0, strlen(lpszOutEncoded));
	if( lpszEncoding == NULL )
		return 0;

	if( ( nInputSize = strlen(lpszEncoding) ) == 0 )
		return 0;

	int nBitsRemaining = 0;
	long lBitsStorage	=0;
	long lScratch		=0;
	int nBits;
	unsigned char c;

	while( nNumBits > 0 )
	{
		while( ( nBitsRemaining < nNumBits ) &&  ( nIndex < (int)nInputSize ) ) 
		{
			c = lpszEncoding[ nIndex++ ];
			lBitsStorage <<= 8;
			lBitsStorage |= (c & 0xff);
			nBitsRemaining += 8;
		}
		if( nBitsRemaining < nNumBits ) 
		{
			lScratch = lBitsStorage << ( nNumBits - nBitsRemaining );
			nBits    = nBitsRemaining;
			nBitsRemaining = 0;
		}	 
		else 
		{
			lScratch = lBitsStorage >> ( nBitsRemaining - nNumBits );
			nBits	 = nNumBits;
			nBitsRemaining -= nNumBits;
		}
		nDigit = (int)(lScratch & g_nBase64Mask[nNumBits]);
		nNumBits = nBits;
		if( nNumBits <=0 )
			break;
		

		lpszOutEncoded[nEncodeLength] = g_szBase64TAB[ nDigit ];
		nEncodeLength++;
		if(nEncodeLength >= lOutSize - 4)
		{
			printf("Err: Over Base64 out buf!\n");
			return -1;
		}
	}
	// Pad with '=' as per RFC 1521
	while( nEncodeLength % 4 != 0 )
	{
		lpszOutEncoded[nEncodeLength] = '=';
		nEncodeLength++;
	}

	return nEncodeLength;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHttpDownload::CHttpDownload()
{
	m_hSocket = INVALID_SOCKET;

	memset(m_strDownURL,0,sizeof(m_strDownURL));
	memset(m_strServer,0,sizeof(m_strServer));

	memset(m_strSaveFileName,0,sizeof(m_strSaveFileName));

	m_nHeaderLength = 0;
	m_nContentLength = 0;
	m_nFileTotalSize = 0;
	time(&m_TimeLastModified);

	m_bStopDownload = false;
	m_nErrorCode = ERROR_DOWNLOAD_NONE;

	m_lpCallbackProc = NULL;

	m_bProxy = false;
	memset(m_strProxyServer, 0, sizeof(m_strProxyServer));
	m_nProxyPort = 0;

	m_bProxyAuthorization = false;
	memset(m_szProxyUser, 0, sizeof(m_szProxyUser));
	memset(m_szProxyPwd, 0, sizeof(m_szProxyPwd));
	m_lpCallbackProc=DefaultCallback;
}

CHttpDownload::~CHttpDownload()
{
	CloseSocket();
}

bool CHttpDownload::StartupWinsock()
{
#ifdef WIN32
	WSADATA wsaData;
	return (WSAStartup(0x0101,&wsaData) == 0);
#else
	return true;
#endif
}

void CHttpDownload::CleanupWinsock()
{
#ifdef WIN32
	WSACleanup();
#endif
}

bool CHttpDownload::CreateSocket()
{
	CloseSocket();
	m_hSocket = (unsigned int)socket(AF_INET,SOCK_STREAM,0);
	return (m_hSocket != INVALID_SOCKET);
}

void CHttpDownload::CloseSocket()
{
	if (m_hSocket != INVALID_SOCKET)
	{
#ifdef WIN32
		closesocket(m_hSocket);
#else
		close(m_hSocket);
#endif
		m_hSocket = INVALID_SOCKET;
	}
}
int CHttpDownload::DownloadToBuffer(const char *lpszDownloadURL, char *Buffer,int BufLen,int* ReturnedLength)
{
	strcpy_s(m_strDownURL,sizeof(m_strDownURL),lpszDownloadURL);

	m_bStopDownload = false;
	

ReDownload:
	int nStatusCode = SendRequest();
	if (nStatusCode == HTTP_ERROR)
	{
		CloseSocket();
		return -1;
	}

	long nDownloadedSize = 0;

	m_nErrorCode = ERROR_RECEIVE_FILE;

	m_lpCallbackProc(MSG_DOWNLOAD_STATUS,STATUS_DOWNLOAD_FILE);
	m_lpCallbackProc(MSG_FILE_TOTAL_SIZE,m_nFileTotalSize);


	char* ReadBuf=new char[BufLen+m_nHeaderLength+1];
	if(ReadBuf==NULL)
	{
		CloseSocket();
		return -1;
	}
	long nRecv = 0;
	int begin=0;
	bool bFirstRecv = true;
	int currentlen=BufLen+m_nHeaderLength;	
	memset(ReadBuf,0,BufLen+m_nHeaderLength+1);
	memset(Buffer,0,BufLen);
	do
	{
		if (m_bStopDownload)
		{			
			delete []ReadBuf;
			CloseSocket();
			return -1;
		}
		int nRet = recv(m_hSocket,&ReadBuf[begin],currentlen,0);
		if (nRet == SOCKET_ERROR)
		{
			CloseSocket();
			//再次发送请求
			delete []ReadBuf;
			goto ReDownload;
		}
		if (nRet == 0)
			break;	
		nRecv+=nRet;
		begin+=nRet;
		currentlen-=nRet;
		m_lpCallbackProc(MSG_DOWNLOADED_SIZE,nRecv+nDownloadedSize);
	}while(currentlen);
	*ReturnedLength=0;
	if(nRecv>m_nHeaderLength)
	{
		*ReturnedLength=nRecv-m_nHeaderLength;
		memcpy(Buffer,&ReadBuf[m_nHeaderLength],*ReturnedLength);
	}
	delete []ReadBuf;
	
	//检查一下已下载的文件长度是否正确
	
	CloseSocket();

	m_nErrorCode = ERROR_DOWNLOAD_NONE;
	m_lpCallbackProc(MSG_DOWNLOAD_STATUS,STATUS_DOWN_FINISHED);
	m_bStopDownload = true;

	return 0;
}
//返回值：
//0：下载成功完成；
//-1：下载失败；
//1：要下载的文件与本地当前文件完全相同（文件大小、文件时间）
int CHttpDownload::Download(const char *lpszDownloadURL, const char *lpszSaveFileName)
{
	strcpy_s(m_strDownURL,sizeof(m_strDownURL),lpszDownloadURL);
	sprintf_s(m_strSaveFileName,sizeof(m_strSaveFileName),"%s.sy",lpszSaveFileName);

	m_bStopDownload = false;
	struct stat fs;
	
ReDownload:
	int nStatusCode = SendRequest();
	if (nStatusCode == HTTP_ERROR)
	{
		CloseSocket();
		return -1;
	}

	long nDownloadedSize = 0;
	if (stat(m_strSaveFileName,&fs) != 0)
	{
		//说明文件尚未下载过
		if (stat(lpszSaveFileName,&fs) == 0)
		{
			if( (fs.st_size == m_nFileTotalSize) && (abs((int)(fs.st_mtime - m_TimeLastModified)) <= 2) )
			{
				//要下载的文件与本地当前文件完全相同（文件大小、文件时间）
				CloseSocket();
				return 1;
			}
		}
	}
	else
	{
		if (nStatusCode == HTTP_PARTIAL)
			nDownloadedSize = fs.st_size;
	}

	m_nErrorCode = ERROR_RECEIVE_FILE;

	m_lpCallbackProc(MSG_DOWNLOAD_STATUS,STATUS_DOWNLOAD_FILE);
	m_lpCallbackProc(MSG_FILE_TOTAL_SIZE,m_nFileTotalSize);


	FILE *fileDown = fopen(m_strSaveFileName,"a+b");
	if (fileDown == NULL)
	{
		CloseSocket();
		return -1;
	}
	if (nStatusCode == HTTP_PARTIAL)
		fseek(fileDown,0,SEEK_END);

	char szBuf[BUF_LEN];
	long nRecv = 0;
	bool bFirstRecv = true;
	do
	{
		if (m_bStopDownload)
		{
			fclose(fileDown);
			CloseSocket();
			return -1;
		}
		
		memset(szBuf,0,BUF_LEN);
		int nRet = recv(m_hSocket,szBuf,BUF_LEN,0);
		if (nRet == SOCKET_ERROR)
		{
			fclose(fileDown);
			CloseSocket();
			//再次发送请求
			goto ReDownload;
		}
		if (nRet == 0)
			break;

		try
		{
			if (bFirstRecv)
			{
				if (nRet >= m_nHeaderLength)
				{
					fwrite(&szBuf[m_nHeaderLength],sizeof(char),nRet-m_nHeaderLength,fileDown);
					fflush(fileDown);
					nRecv += nRet - m_nHeaderLength;
					bFirstRecv = false;
				}
				else
				{
					fclose(fileDown);
					CloseSocket();
					//再次发送请求
					goto ReDownload;
				}
			}
			else
			{
				fwrite(szBuf,sizeof(char),nRet,fileDown);
				fflush(fileDown);
				nRecv += nRet;
			}
		}
		catch(...)
		{
			fclose(fileDown);
			CloseSocket();
			goto ReDownload;
		}
		m_lpCallbackProc(MSG_DOWNLOADED_SIZE,nRecv+nDownloadedSize);
	}while(nRecv < m_nContentLength);

	//检查一下已下载的文件长度是否正确
	fflush(fileDown);
	if (m_nFileTotalSize != ftell(fileDown))
	{
		fclose(fileDown);
		CloseSocket();
		//删除已下载的不正确的文件
		remove(m_strSaveFileName);
		goto ReDownload;
	}

	fclose(fileDown);
	CloseSocket();

	m_nErrorCode = ERROR_DOWNLOAD_NONE;

	m_lpCallbackProc(MSG_DOWNLOAD_STATUS,STATUS_DOWN_FINISHED);

	//首先将已有的文件删除
	remove(lpszSaveFileName);
	//再将新下载的文件改名
	rename(m_strSaveFileName,lpszSaveFileName);
	//再将新下载的文件的时间改回去
	struct utimbuf newTime;
	newTime.actime = 0;
	newTime.modtime = m_TimeLastModified;
	utime(lpszSaveFileName,&newTime);

	m_bStopDownload = true;

	return 0;
}

void delStrSpace(char *str)
{
	char *ptr;

	for (ptr =str;*ptr != '\0' && *ptr == ' ';ptr++);
	strcpy(str,ptr);	
}

		
int CHttpDownload::GetInformation(const char *lpszReceived,long &nHeaderLength,long &nContentLength,time_t &TimeLastModified)
{
	size_t newLen;
	char *szPos = strstr((char*)lpszReceived,"\r\n\r\n");
	if (szPos == NULL)
		return HTTP_ERROR;

	//HTTP应答的头信息长度
	newLen = strlen("\r\n\r\n");
	nHeaderLength = *(long*)&szPos-*(long*)&lpszReceived+(long)newLen;
	char *strHeader = (char *)malloc(nHeaderLength+1);
	strHeader[nHeaderLength]=0;
	//HTTP应答的头信息应包括一个空白行"\r\n"
	strncpy(strHeader,lpszReceived,nHeaderLength);

	char *strLowerHeader = strdup(strHeader);
	StringMakeLower(strLowerHeader);

	//拆分出HTTP应答的头信息的第一行，并获得返回的HTTP状态码
	szPos = strstr(strHeader,"\r\n");
	char *strStatusCode = (char *)malloc(szPos-strHeader+1);
	strncpy(strStatusCode,strHeader,szPos-strHeader);
	szPos = strchr(strStatusCode,' ');
	if (szPos == NULL)
	{
		free(strStatusCode);
		free(strLowerHeader);
		free(strHeader);
		return HTTP_ERROR;
	}
	char *szPos1 = szPos+1;
	szPos = strchr(szPos1,' ');
	if (szPos == NULL)
	{
		free(strStatusCode);
		free(strLowerHeader);
		free(strHeader);
		return HTTP_ERROR;
	}
	*szPos = '\0';
	int nStatusCode = atoi(szPos1);
	free(strStatusCode);

	//首先检测一下服务器的应答是否为重定向
	if (nStatusCode >= 300 && nStatusCode < 400)
	{
		szPos = strstr(strLowerHeader,"location:");
		if (szPos == NULL)
		{
			free(strLowerHeader);
			free(strHeader);
			return HTTP_ERROR;
		}
		
		char *strRedirectURL = strdup(szPos+strlen("location:"));
		szPos = strstr(strRedirectURL,"\r\n");
		if (szPos == NULL)
		{
			free(strRedirectURL);
			free(strLowerHeader);
			free(strHeader);
			return HTTP_ERROR;
		}

		*szPos = '\0';
		char *p=strRedirectURL;
		do
		{
			if (*p == '\\')
				*p = '/';
			p++;
		}while (*p != '\0');

		/* del the space in the string 01/12/05 */
		delStrSpace(strRedirectURL);

		//判断是否为重定向到其他的服务器
		if (strncmp(strRedirectURL,"http://",strlen("http://")) == 0)
		{
			strcpy(m_strDownURL,strRedirectURL);
			free(strRedirectURL);
			free(strLowerHeader);
			free(strHeader);
			return HTTP_REDIRECT;
		}

		//判断是否为相对于根目录
		if (*strRedirectURL == '/')
		{
			sprintf(m_strDownURL,"http://%s%s",m_strServer,strRedirectURL);
			free(strRedirectURL);
			free(strLowerHeader);
			free(strHeader);
			return HTTP_REDIRECT;
		}

		//说明是相对于当前目录
		int nParentDirCount = 0;
		char *szPos1 = strRedirectURL;
		szPos = strstr(szPos1,"../");
		while (szPos != NULL)
		{
			szPos1 = szPos+3;
			nParentDirCount++;
			szPos = strstr(szPos1,"../");
		}
		for (int i=0; i<=nParentDirCount; i++)
		{
			szPos = strrchr(m_strDownURL,'/');
			if (szPos == NULL)
			{
				free(strRedirectURL);
				free(strLowerHeader);
				free(strHeader);
				return HTTP_ERROR;
			}
			*szPos = '\0';
		}

		strcat(m_strDownURL,"/");
		strcat(m_strDownURL,szPos1);
		
		free(strRedirectURL);
		free(strLowerHeader);
		free(strHeader);
		return HTTP_REDIRECT;
	}

	//再检查一次服务器的应答是否为200(OK)或是206(Partial Content)
	if (nStatusCode != 200 && nStatusCode != 206)
	{
		free(strLowerHeader);
		free(strHeader);
		return HTTP_ERROR;
	}

	//获得Content-Length
	szPos = strstr(strLowerHeader,"content-length:");
	if (szPos == NULL)
	{
		free(strLowerHeader);
		free(strHeader);
		return HTTP_ERROR;
	}
	
	char *strLength = strdup(szPos+strlen("content-length:"));	
	szPos = strstr(strLength,"\r\n");
	if (szPos == NULL)
	{
		free(strLength);
		free(strLowerHeader);
		free(strHeader);
		return HTTP_ERROR;
	}

	*szPos = '\0';
	nContentLength = atol(strLength);
	free(strLength);

	//获得Last-Modified
	time(&TimeLastModified);
	szPos = strstr(strLowerHeader,"last-modified:");
	if (szPos != NULL)
	{
		char *strTime = strdup(szPos+strlen("last-modified:"));
		szPos = strstr(strTime,"\r\n");
		if (szPos != NULL)
		{
			*szPos = '\0';
			ConvertTime(strTime,TimeLastModified);
		}
		free(strTime);
	}

	free(strLowerHeader);
	free(strHeader);
	if (nStatusCode == 200)
		return HTTP_OK;
	else if (nStatusCode == 206)
		return HTTP_PARTIAL;
	else
		return HTTP_ERROR;
}

void CHttpDownload::ConvertTime(const char *lpszTime,time_t &TimeLastModified)
{
	int nDay,nMonth,nYear,nHour,nMinute,nSecond;
	char *strTime = strdup(lpszTime);
	char *szPos = strchr(strTime,',');
	if (szPos != NULL)
	{
		char *szPos1 = szPos+1;
		while (*szPos1==' ')
			szPos1++;

		const char *strAllMonth = "jan,feb,mar,apr,may,jan,jul,aug,sep,oct,nov,dec";
		char strDay[3] = { 0 };
		strncpy(strDay,szPos1,2);
		nDay = atoi(strDay);
		char strMonth[4] = { 0 };
		strncpy(strMonth,szPos1+3,3);
		StringMakeLower(strMonth);
		szPos = strstr((char*)strAllMonth,strMonth);
		if (szPos != NULL)
		{
			sprintf(strMonth,"%d",(((szPos-strAllMonth)/4)+1));
			nMonth = atoi(strMonth)-1;
		}
		else
			nMonth = 0;
		szPos1 += 6;
		while (*szPos1==' ')
			szPos1++;
		szPos = strchr(szPos1,' ');
		char strYear[5] = { 0 };
		if (szPos != NULL)
		{
			strncpy(strYear,szPos1,4);
			nYear = atoi(strYear);
			if (strlen(strYear) > 3)
				nYear -= 1900;
		}
		else
			nYear = 2001-1900;
		szPos1 = szPos+1;
		char strHour[3] = { 0 };
		strncpy(strHour,szPos1,2);
		nHour = atoi(strHour);
		char strMinute[3] = { 0 };
		strncpy(strMinute,szPos1+3,2);
		nMinute = atoi(strMinute);
		char strSecond[3] = { 0 };
		strncpy(strSecond,szPos1+6,2);
		nSecond = atoi(strSecond);
	}

	free(strTime);
	struct tm tmLastModified;
	tmLastModified.tm_year = nYear;
	tmLastModified.tm_mon = nMonth;
	tmLastModified.tm_mday = nDay;
	tmLastModified.tm_hour = nHour;
	tmLastModified.tm_min = nMinute;
	tmLastModified.tm_sec = nSecond;
	TimeLastModified = mktime(&tmLastModified);
}

char *CHttpDownload::URLEncode(const char *lpszURL, char *szURL)
{
#define ToHex(nNumber) ((nNumber < 10) ? (nNumber+'0') : (nNumber+'A'-10))

	char *pszOut = szURL;
	char *pch = (char *)lpszURL;
	if (strchr(lpszURL, '%') != NULL)
	{
		strcpy(szURL, lpszURL);
		return szURL;
	}

	for (; pch!=NULL && *pch!='\0'; pch++)
	{
		if (isalnum(*pch))
			*pszOut++ = *pch;
		else if (*pch=='/' || *pch=='\\' || *pch=='.' || *pch==':' || *pch=='?' || *pch=='&' || *pch=='=')
			*pszOut++ = *pch;
		else
		{
			*pszOut++ = '%';
			*pszOut++ = ToHex(*pch/16);
			*pszOut++ = ToHex(*pch%16);
		}
	}

	*pszOut = '\0';
	return szURL;
}

bool CHttpDownload::ParseURL(const char *lpszURL,char *strServer,char *strObject)
{
	//拆分主机地址与主机上的目标文件位置
	char *strLowerURL = strdup(lpszURL);
	StringMakeLower(strLowerURL);

	char *szPos = strstr(strLowerURL,"http://");
	if (szPos == NULL)
	{
		free(strLowerURL);
		return false;
	}

	const char *strURL = lpszURL+(szPos-strLowerURL)+strlen("http://");
	free(strLowerURL);
	
	szPos = strchr((char*)strURL,'/');
	if (szPos == NULL)
		return false;

	memset(strServer, 0, sizeof(strServer));
	strncpy(strServer,strURL,szPos-strURL);
	//strcpy(strObject, szPos);
	URLEncode(szPos, strObject);
	return true;
}

bool CHttpDownload::GetHostIP(char *strServer)
{
//	printf("gethostbyname %s\n", strServer);
	struct hostent *pHost = gethostbyname(strServer);
	if(pHost == NULL)
	{
		printf("gethostbyname %s error : %d\n", strServer, h_errno);
		return false;
	}

	strcpy(strServer,inet_ntoa(*(struct in_addr *)*pHost->h_addr_list));
	return true;
}

int CHttpDownload::SendRequest()
{
	char szAuthIn[256] = {0};
	char szAuthOut[501] = {0};
	char szOriServer[512]={0};
	int	 nOutLength = 0;
	m_nErrorCode = ERROR_RESOLVE_HOST;
	m_lpCallbackProc(MSG_DOWNLOAD_STATUS,STATUS_RESOLVE_HOST);

	char strObject[2048]= { 0 };
	memset(m_strServer, 0, 128);
	if (!ParseURL(m_strDownURL,m_strServer,strObject))
		return HTTP_ERROR;

	struct sockaddr_in sockAddr;
	sockAddr.sin_family	= 2;

	strncpy(szOriServer,m_strServer,511);

	
	if (!m_bProxy)
	{
		//解析域名
		sockAddr.sin_port			= htons(80);
		sockAddr.sin_addr.s_addr	= inet_addr(m_strServer);	
		if (sockAddr.sin_addr.s_addr == 0xffffffff)
		{
			if (m_bStopDownload)
				return HTTP_ERROR;
			if (!GetHostIP(m_strServer))
				return HTTP_ERROR;
			sockAddr.sin_addr.s_addr = inet_addr(m_strServer);
		}
	}
	else
	{
		//解析Proxy的域名
		sockAddr.sin_port			= htons(m_nProxyPort);
		sockAddr.sin_addr.s_addr	= inet_addr(m_strProxyServer);	
		if (sockAddr.sin_addr.s_addr == 0xffffffff)
		{
			if (m_bStopDownload)
				return HTTP_ERROR;
			if (!GetHostIP(m_strProxyServer))
				return HTTP_ERROR;
			sockAddr.sin_addr.s_addr = inet_addr(m_strProxyServer);
		}
	}

	if (!CreateSocket())
		return HTTP_ERROR;

	if (m_bStopDownload)
		return HTTP_ERROR;

	m_nErrorCode = ERROR_CONNECT_HOST;
	m_lpCallbackProc(MSG_DOWNLOAD_STATUS,STATUS_CONNECT_HOST);

	//连接主机
	int nRet = connect(m_hSocket,(struct sockaddr *)&sockAddr,sizeof(sockAddr));
	if (nRet == SOCKET_ERROR)
		return HTTP_ERROR;

	if (m_bStopDownload)
		return HTTP_ERROR;

	//向HTTP服务器发送请求
	char strSend[10240];
	if (!m_bProxy)
		sprintf(strSend,"GET %s HTTP/1.1\r\n",strObject);
	else
		sprintf(strSend,"GET http://%s%s HTTP/1.1\r\n",m_strServer,strObject);

	strcat(strSend,"Host: ");
	strcat(strSend,szOriServer);
	strcat(strSend,"\r\n");
	strcat(strSend,"Accept: */*\r\n");
	strcat(strSend,"Cache-Control: no-cache\r\n");
	strcat(strSend,"User-Agent: HttpDownload/1.00\r\n");
	if( m_bProxyAuthorization )
	{
		sprintf(szAuthIn, "%s:%s", m_szProxyUser, m_szProxyPwd);
		nOutLength = Base64Encode(szAuthIn, szAuthOut, 500);
		if(nOutLength > 0)
		{
			strcat(strSend, "Authorization: Basic ");
			strcat(strSend, szAuthOut);
			strcat(strSend, "\r\n");
		}
	}

	strcat(strSend,"Connection: close\r\n");

	//查看文件已下载的字节长度
	struct stat fs;
	long nRange = 0;
	if (stat(m_strSaveFileName,&fs) == 0)
		nRange = fs.st_size;
	if (nRange > 0)
	{
		char strRange[128];
		sprintf(strRange,"Range: bytes=%d-\r\n",nRange);
		strcat(strSend,strRange);
	}
	//必须要加一个空行，否则Http服务器将不会应答
	strcat(strSend,"\r\n");

	m_nErrorCode = ERROR_SEND_REQUEST;
	m_lpCallbackProc(MSG_DOWNLOAD_STATUS,STATUS_SEND_REQUEST);

	//发送请求
	nRet = send(m_hSocket,strSend,(int)strlen(strSend),0);
	if (nRet == SOCKET_ERROR)
		return HTTP_ERROR;

	if (m_bStopDownload)
		return HTTP_ERROR;

	m_nErrorCode = ERROR_RECV_RESPONSE;
	m_lpCallbackProc(MSG_DOWNLOAD_STATUS,STATUS_RECV_RESPONSE);

	char szBuf[BUF_LEN];
	memset(szBuf,0,sizeof(szBuf));
	//首先查看一下输入数据，将数据拷入到Buffer中，但不从输入队列中清除
	nRet = recv(m_hSocket,szBuf,sizeof(szBuf),MSG_PEEK);
	if (nRet == SOCKET_ERROR)
		return HTTP_ERROR;

	nRet = GetInformation(szBuf,m_nHeaderLength,m_nContentLength,m_TimeLastModified);
	if (nRet == HTTP_ERROR)
		return HTTP_ERROR;
	if (nRet == HTTP_OK || nRet == HTTP_PARTIAL)
	{
		if (m_nHeaderLength == 0)
			return HTTP_ERROR;
		m_nFileTotalSize = m_nContentLength;
		if (nRet == HTTP_PARTIAL)
			m_nFileTotalSize += nRange;

		return nRet;
	}

	if (m_bStopDownload)
		return HTTP_ERROR;
	if (nRet == HTTP_REDIRECT)
	{
		m_lpCallbackProc(MSG_DOWNLOAD_STATUS,STATUS_HOST_REDIRECT);

		//再次发送请求
		nRet = SendRequest();
		if (nRet != HTTP_REDIRECT)
			return nRet;
	}

	return HTTP_ERROR;
}

void CHttpDownload::SetCalllbackProc(DownloadCallbackProc proc)
{
	if(proc==NULL)
		m_lpCallbackProc=DefaultCallback;
	else
		m_lpCallbackProc = proc;
}

void CHttpDownload::SetProxy(const char *lpszProxyServer,unsigned short nProxyPort)
{
	m_bProxy = true;
	strcpy(m_strProxyServer,lpszProxyServer);
	m_nProxyPort = nProxyPort;
}
void CHttpDownload::SetProxy(const char *lpszProxyServer,unsigned short nProxyPort, bool bProxyAuthorization, const char *lpszProxyUser, char *lpszProxyPwd)
{
	m_bProxyAuthorization = bProxyAuthorization;
	strcpy(m_szProxyUser, lpszProxyUser);
	strcpy(m_szProxyPwd, lpszProxyPwd);
	SetProxy(lpszProxyServer, nProxyPort);
}
void CHttpDownload::StopDownload()
{
	m_nErrorCode = ERROR_STOP_DOWNLOAD;
	m_bStopDownload = true;
}

int CHttpDownload::GetErrorCode()
{
	return m_nErrorCode;
}

void CHttpDownload::StringMakeLower(char *str)
{
	for (char *p=str; *p!='\0'; p++)
	{
		if (isupper(*p))
			*p = tolower(*p);
	}
}

bool CHttpDownload::SendFinishRequest(const char *lpszFinishURL)
{
	strcpy(m_strDownURL,lpszFinishURL);
	strcpy(m_strSaveFileName,"|");
	
	m_bStopDownload = false;
	int nRet = SendRequest();
	CloseSocket();
	m_bStopDownload = true;
	return (nRet != HTTP_ERROR);
}
