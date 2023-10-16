#include "StdAfx.h"
#include "Ripple.h"

CRipple::CRipple()
{
	m_buf1 = NULL;
	m_buf2 = NULL;
}

CRipple::~CRipple()
{
	CleanRippleData();
}

bool CRipple::InitRipple(int nBackWidth, int nBackHeight, int nDepth, int Pitch)
{
	m_BackWidth  = nBackWidth;
	m_BackHeight = nBackHeight;
	m_PixelBytes = (nDepth+7)/8;
	if(Pitch)
		m_Pitch = Pitch;
	else
		m_Pitch = m_PixelBytes*m_BackWidth;
    m_buf1 = new short[m_BackWidth*m_BackHeight];
	m_buf2 = new short[m_BackWidth*m_BackHeight];
	ZeroMemory(m_buf1,m_BackWidth*m_BackHeight*sizeof(short));
	ZeroMemory(m_buf2,m_BackWidth*m_BackHeight*sizeof(short));
	return true;
}

//*****************************************************
//增加波源
//*****************************************************
void CRipple::DropStone(int x,int y,int stonesize,int stoneweight)
{
	//判断坐标是否在屏幕范围内
	if(x+stonesize>=m_BackWidth || y+stonesize>=m_BackHeight||x-stonesize<0||y-stonesize<0)
		return;
	for(int posx=x-stonesize; posx<x+stonesize; posx++)
		for(int posy=y-stonesize; posy<y+stonesize; posy++)
			if((posx-x)*(posx-x) + (posy-y)*(posy-y) < stonesize*stonesize)
				m_buf1[m_BackWidth*posy+posx] = -stoneweight;
}

//*******************************************************
//计算波能数据缓冲区
//*******************************************************
bool CRipple::RippleSpread()
{
	bool Result;
	int pos;
	Result=false;
	for(int j=1; j<m_BackHeight-1; j++)
	{
		for(int i=1; i<m_BackWidth-1; i++)
		{
			pos = i+m_BackWidth*j;
			if(m_buf2[pos] = ((m_buf1[pos-1]+m_buf1[pos+1]+m_buf1[pos-m_BackWidth]+m_buf1[pos+m_BackWidth])>>1)-m_buf2[pos])
				Result = true;
			if(m_buf2[pos] -= m_buf2[pos]>>5)
				Result = true;
		}
	}
	short *ptmp =m_buf1;
	m_buf1 = m_buf2;
	m_buf2 = ptmp;
	return Result;
}

//*******************************************************
//根据波能数据缓冲区对离屏页面进行渲染
//*******************************************************
void CRipple::RenderRipple(void* Bitmap1,void* Bitmap2)
{
	//下面进行页面渲染
	int pos1,pos2,xoff,yoff;
	int k = m_BackWidth;
	for(int y=1; y<m_BackHeight-1;y++)
	{
		for(int x=0; x<m_BackWidth;x++)
		{
			//计算偏移量
			xoff = m_buf1[k-1]-m_buf1[k+1];
			yoff = m_buf1[k-m_BackWidth]-m_buf1[k+m_BackWidth];
			//判断坐标是否在窗口范围内
			if(y+yoff < 0 || y+yoff >= m_BackHeight || x+xoff < 0 || x+xoff >= m_BackWidth)
			{
				k++;
				continue;
			}
			//计算出偏移象素和原始象素的内存地址偏移量
			pos1=m_Pitch*(y+yoff)+ m_PixelBytes*(x+xoff);
			pos2=m_Pitch*y+ m_PixelBytes*x;
			//复制象素
			for(int d=0; d<m_PixelBytes; d++)
				((BYTE*)Bitmap2)[pos2++]=((BYTE*)Bitmap1)[pos1++];
			k++;
		}
	}
}
// 释放内存
void CRipple::CleanRippleData()
{
	SafeDelete(m_buf1);
	SafeDelete(m_buf2);
}

