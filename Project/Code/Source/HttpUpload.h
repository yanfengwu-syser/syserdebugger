#ifndef UPLOAD_H
#define UPLOAD_H

#include <winsock.h>
#include <string>

using namespace std;

#pragma comment(lib, "Ws2_32.lib")

const int ERROR_CODE_CONNECT_FAILURE		= -1;
const int ERROR_CODE_HTTP_REQUEST_FAILURE	= -2;
const int ERROR_CODE_ELSE                   = -3;

static char* BASE64_Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
#define AMLOGDEVINFO(x,y) 
class CHttpUpload
{
public:
	CHttpUpload();
	~CHttpUpload();

	BOOL    Init(const char* cszUrl, int nUrlLen);

	//add text content
	BOOL    AddFormTextField(
			const char* cszFieldName,    //the field name in form 
			const char* cszValue         //field value
			);

	//add a file
	BOOL    AddFormFileField(
			const char* cszFieldName,    //the field name in form 
			const char* cszFileName,     //the file name which need upload
			BOOL bIsBinary = FALSE
			);

	//upload request
	BOOL    Request();

	//return data (that received) pointer 
	char*   RetRecvDataPt();

protected:
	void    DataVarInit();
	BOOL	UrlParse(const char* cszUrl, int nUrlLen);  //url parse
	BOOL	CreateSock();									   
	BOOL	ConnectSvr();										
	BOOL    AddFormDataEndFlag();

	BOOL    RecvResponse();
	BOOL    ParseRetHeader(const char* cszRetHeader, int nHeaderLen);
	int		HexStrToInt(const char* cszHexStr, int nStrLen);
	
protected:
	SOCKET  m_hSock;
	char    m_szSvrName[1024];					 //web server name
	int		m_nSvrPort;							 //web server port
	char    m_szReqObj[1024];					 //request object
	
	BOOL    m_bChunkTransferEncoding;    //Is Transfer-Encoding: chunked ?
	
	char    m_szRetData[1024 * 5];		 //receive data(not include header)
	string  m_strFormDataContent;        //form data encoded
};

#endif