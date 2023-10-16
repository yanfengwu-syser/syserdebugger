#ifndef _WISP_3D_H_
#define _WISP_3D_H_

#include "WispDC.h"

#define MAX_NV 30
#define MAX_NV_3D 30

struct VS_2D
{
	float x;
	float y;
};

struct VS_3D
{
	float x;
	float y;
	float z;
};

struct ES_2D
{
	VS_2D vp[MAX_NV];
	unsigned vn;
};


struct ES_3D
{
	VS_3D vp[MAX_NV_3D];
	unsigned vn;
};

struct OBJ
{
	ES_3D *ep;
	unsigned en;
};

struct WISP_WIN
{
	int min_x;
	int min_y;
	int max_x;
	int max_y;
};

struct WISP_VIEW
{
	float dp;
	float ox,oy,oz;
	float u1,u2,u3;
	float v1,v2,v3;
	float w1,w2,w3;
};

void draw_obj(WISP_WIN*win,WISP_VIEW*view,OBJ *obj,COLORREF color,CWispDC*pDC);
void change_view(WISP_VIEW*view,float rl,float du);

#endif
