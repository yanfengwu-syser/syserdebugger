#ifndef _WISP_APP_H_
#define _WISP_APP_H_

class  CWispApp : public CWispBase
{
public:
	CWispApp();
	~CWispApp();
public:
	virtual	bool	InitInstance();
	virtual	int		ExitInstance();
	virtual int		Run();
};

#endif
