#ifndef __IBMASCIIWND_H__
#define __IBMASCIIWND_H__
class CIBMAsciiWnd:public CWispForm
{
	
public:
	static WISP_FORM_RES_ITEM m_FormRes[];
	CIBMAsciiWnd();
	~CIBMAsciiWnd();
	DECLARE_WISP_MSG_MAP	
	//DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnUpdateClient);
	void Popup();
	DECLARE_WISP_MSG(OnFormCreate)
	void DrawGrid(int x,int y,int cx,int cy);
	void DrawString(WCHAR* pStr,int x,int y,int Len);
	void DrawIndex(int x,int y);
	bool SetFont(int FontType);
private:
	int m_FontType;
	static WCHAR* m_gTitileName[3];
};
#endif //_IBMASCIIWND_H__