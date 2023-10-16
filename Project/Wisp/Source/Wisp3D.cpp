#include "StdAfx.h"
#include "Wisp3D.h"


//*****************************clip_edges************************************
BYTE cross_code(WISP_WIN*win,char edge, VS_2D v1,VS_2D v2)
{
	switch(edge)
	{
	case 0:{ if(v1.x>=win->min_x && v2.x>=win->min_x) return 0;
		if(v1.x< win->min_x && v2.x>=win->min_x) return 1;
		if(v1.x>=win->min_x && v2.x< win->min_x) return 2;
		if(v1.x< win->min_x && v2.x< win->min_x) return 3;
		   }

	case 1:{ if(v1.x<=win->max_x && v2.x<=win->max_x) return 0;
		if(v1.x> win->max_x && v2.x<=win->max_x) return 1;
		if(v1.x<=win->max_x && v2.x> win->max_x) return 2;
		if(v1.x> win->max_x && v2.x> win->max_x) return 3;
		   }

	case 2:{ if(v1.y>=win->min_y && v2.y>=win->min_y) return 0;
		if(v1.y< win->min_y && v2.y>=win->min_y) return 1;
		if(v1.y>=win->min_y && v2.y< win->min_y) return 2;
		if(v1.y< win->min_y && v2.y< win->min_y) return 3;
		   }

	case 3:{ if(v1.y<=win->max_y && v2.y<=win->max_y) return 0;
		if(v1.y> win->max_y && v2.y<=win->max_y) return 1;
		if(v1.y<=win->max_y && v2.y> win->max_y) return 2;
		if(v1.y> win->max_y && v2.y> win->max_y) return 3;
		   }
	default:return 0;       
	}

}


VS_2D cross_v(WISP_WIN*win,char edge,VS_2D v1,VS_2D v2)
{
	float m=0,edge_xy;
	VS_2D v;

	if(edge<2)
	{
		if(edge==0)edge_xy=(float)win->min_x;
		else       edge_xy=(float)win->max_x;

		if(v1.x!=v2.x) m=(v2.y-v1.y)/(v2.x-v1.x);

		v.x=edge_xy;
		v.y=m*(v.x-v1.x)+v1.y;
	}
	else
	{
		if(edge==2)edge_xy=(float)win->min_y;
		else       edge_xy=(float)win->max_y;

		if(v1.y!=v2.y)m=(v2.x-v1.x)/(v2.y-v1.y);

		v.y=edge_xy;
		v.x=m*(v.y-v1.y)+v1.x;
	}

	return v;
}


void copy_es_2d(ES_2D*se,ES_2D*de)
{
	VS_2D*p1,*p2;
	p1=se->vp;
	p2=de->vp;

	for(unsigned n=0;n<=se->vn;n++)
		p2[n]=p1[n];

	de->vn=se->vn;

	return;
}

void link_hd(ES_2D*e)
{
	VS_2D*p=e->vp;
	p[e->vn]=p[0];
	return;
}


void clipedges(WISP_WIN*win,ES_2D*sp)
{
	BYTE code;
	VS_2D*svp,*dvp; 
	ES_2D temp;
	unsigned tvn;

	svp=temp.vp;
	dvp=sp->vp;

	for(char edge=0;edge<4;edge++)
	{ 
		copy_es_2d(sp,&temp);
		link_hd(&temp);
		tvn=0;

		for(unsigned n=0;n<temp.vn;n++)
		{
			code=cross_code(win,edge,svp[n],svp[n+1]);
			switch(code)
			{
			case 0:{dvp[tvn]=svp[n+1];
				tvn++;
				break;
				   }
			case 1:{dvp[tvn]=cross_v(win,edge,svp[n],svp[n+1]);
				tvn++;
				dvp[tvn]=svp[n+1];
				tvn++;
				break;
				   }
			case 2:{dvp[tvn]=cross_v(win,edge,svp[n],svp[n+1]);
				tvn++;
				break;
				   }

			default:break;
			}//end switch

		}//end for(vn)
		sp->vn=tvn;

	}//end for(edge)
	return;
}//end fuction



//****************************************************************
void wctovc(WISP_VIEW*view,VS_3D*vs)
{

	float x,y,z;
	x=vs->x-view->ox;
	y=vs->y-view->oy;
	z=vs->z-view->oz;

	vs->x=view->u1*x+view->u2*y+view->u3*z;
	vs->y=view->v1*x+view->v2*y+view->v3*z;
	vs->z=view->w1*x+view->w2*y+view->w3*z;

	return;
}

void vcto2dc(WISP_VIEW*view,VS_3D *s,VS_2D *d)
{
	float u;
	u=view->dp/(view->dp+s->z);

	d->x=s->x*u;
	d->y=s->y*u;

	return;
}

BYTE cross_code_3d(VS_3D v1,VS_3D v2)
{
	if(v1.z>=0&&v2.z>=0)return 0;
	if(v1.z< 0&&v2.z>=0)return 1;
	if(v1.z>=0&&v2.z< 0)return 2;
	return 3;
}

VS_3D cross_v_3d(VS_3D v1,VS_3D v2)
{
	float ux,uy;
	VS_3D res;
	ux=(v1.x-v2.x)/(v2.z-v1.z);
	uy=(v1.y-v2.y)/(v2.z-v1.z);

	res.x=ux*v1.z+v1.x;
	res.y=uy*v1.z+v1.y;
	res.z=0;
	return res;
}

void link_hd_3d(ES_3D*e)
{
	VS_3D*p=e->vp;
	p[e->vn]=p[0];
	return;
}

void copy_es_3d(ES_3D*se,ES_3D*de)
{
	VS_3D*p1,*p2;
	p1=se->vp;
	p2=de->vp;

	for(unsigned n=0;n<=se->vn;n++)
		p2[n]=p1[n];

	de->vn=se->vn;

	return;
}

void clip_z0_es_3d(ES_3D*sp)
{
	BYTE code;   
	unsigned tvn=0;

	ES_3D temp;

	copy_es_3d(sp,&temp);
	link_hd_3d(&temp);

	VS_3D*svp=temp.vp;
	VS_3D*dvp=sp->vp;  

	for(unsigned n=0;n<temp.vn;n++)
	{
		code=cross_code_3d(svp[n],svp[n+1]);
		switch(code)
		{
		case 0:{dvp[tvn]=svp[n+1];
			tvn++;
			break;
			   }
		case 1:{dvp[tvn]=cross_v_3d(svp[n],svp[n+1]);
			tvn++;
			dvp[tvn]=svp[n+1];
			tvn++;
			break;
			   }
		case 2:{dvp[tvn]=cross_v_3d(svp[n],svp[n+1]);
			tvn++;
			break;
			   }

		default:break;
		}//end switch

	}//end for(vn)
	sp->vn=tvn;
	return;
}


void clipwin_E3toE2(WISP_WIN*win,WISP_VIEW*view,ES_3D *s_p,ES_2D *d_p,CWispDC*pDC)
{
	BYTE code1=0,code2=0;
	VS_3D*s_vp=s_p->vp;
	VS_2D*d_vp=d_p->vp;
	unsigned n;
	for( n=0;n<s_p->vn;n++)
		wctovc(view,&s_vp[n]);

	for(n=0;n<s_p->vn;n++) 
	{     
		if(s_vp[n].z<0)code2=1;
		else           code1=1;   
	}  

	if(code1==1&&code2==1)clip_z0_es_3d(s_p);

	if(code2==1&&code1==0){d_p->vn=0;return;}

	for(n=0;n<s_p->vn;n++)
		vcto2dc(view,&s_vp[n],&d_vp[n]);

	d_p->vn=s_p->vn;

	clipedges(win,d_p);

	for(n=0;n<d_p->vn;n++)
	{
		d_vp[n].x+=pDC->m_pRect->cx/2;
		d_vp[n].y+=pDC->m_pRect->cy/2;
	}
}


void draw_edges(ES_2D*ep,COLORREF color,CWispDC*pDC)
{
	float x1,y1,x2,y2; 
	link_hd(ep);
	for(unsigned n=0;n<ep->vn;n++)
	{ 
		x1=ep->vp[n].x;y1=ep->vp[n].y;
		x2=ep->vp[n+1].x;y2=ep->vp[n+1].y;
		pDC->DrawLine((int)x1,(int)y1,(int)x2,(int)y2,color);
	}
}

void draw_obj(WISP_WIN*win,WISP_VIEW*view,OBJ *obj,COLORREF color,CWispDC*pDC)
{
	ES_2D tes2D;
	ES_3D tes3D;
	for(unsigned n=0;n<obj->en;n++)
	{
		copy_es_3d(&(obj->ep[n]),&tes3D);
		clipwin_E3toE2(win,view,&tes3D,&tes2D,pDC);
		draw_edges(&tes2D,color,pDC);
	}
}

void draw_sky_ground(char sky,char ground)
{
	return;
}

void change_view(WISP_VIEW*view,float rl,float du)
{
	float x,y,cos_a,sin_a; 

	if(rl!=0)
	{
		x=view->w1;y=view->w2;
		cos_a=cos(rl);sin_a=sin(rl);
		view->w1=x*cos_a-y*sin_a;
		view->w2=x*sin_a+y*cos_a;

		x=view->u1;y=view->u2;
		view->u1=x*cos_a-y*sin_a;
		view->u2=x*sin_a+y*cos_a;

		x=view->v1;y=view->v2;
		view->v1=x*cos_a-y*sin_a;
		view->v2=x*sin_a+y*cos_a;
	}
	return;
}
