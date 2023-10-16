#ifndef _WISP_RGB_SELECT_H_
#define _WISP_RGB_SELECT_H_

#include "WispButton.h"
#include "WispEdit.h"
#include "WispForm.h"

class CWispRGBSelect : public CWispForm
{
public:
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	CWispRGBSelect();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate);
	DECLARE_WISP_MSG(OnUpdateClient);
	DECLARE_WISP_MSG(OnDestroy);
	DECLARE_WISP_MSG(OnMouseMove);
	DECLARE_WISP_MSG(OnKeyEvent);
	DECLARE_WISP_MSG_CMD_MAP;
	DECLARE_WISP_MSG_CMD(OnCmdGetCmd);

	void	FillRGBRect(CWispDIB*pRGBDIB);
	void	UpdateLumColor(bool bGather = true);
	void	UpdateColor();
	void	UpdateColorValue();
	void	ShowColorValue();

	WISP_RECT		m_RGBFrameRect;
	WISP_RECT		m_RGBRect;
	WISP_RECT		m_LumFrameRect;
	WISP_RECT		m_LumRect;
	WISP_RECT		m_LumDragRect;
	WISP_RECT		m_CurRGBRect;
	WISP_POINT		m_PTSelected;
	int				m_LumYPos;
	CWispDIB		m_RGBDIB;
	CWispDIB		m_LumDIB;
	CWispBaseWnd*	m_pRGBGroupCtrl;
	CWispEdit*		m_pRedEdit;
	CWispEdit*		m_pGreenEdit;
	CWispEdit*		m_pBlueEdit;
	COLORREF		m_RGBClr;
};



#define DEFAULT_LumINANCE 0.50f

void		RGBtoHSL( COLORREF rgb, double *H, double *S, double *L );
double		HueToRGB(double m1, double m2, double h );
COLORREF	HLStoRGB_ONE( double H, double L, double S );

#endif
