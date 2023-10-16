#ifndef _RIPPLE_H_
#define _RIPPLE_H_

class CRipple
{
public:
	CRipple();
	~CRipple();
	bool	InitRipple(int nBackWidth, int nBackHeight, int nDepth, int Pitch = 0);
	void	CleanRippleData();
	void	DropStone(int x,int y,int stonesize,int stoneweight);
	bool	RippleSpread();
	void	RenderRipple(void* Bitmap1, void* Bitmap2);
private:
	int		m_BackWidth;	//背景图宽度
	int		m_BackHeight;	//背景图高度
	int		m_PixelBytes;	//颜色深度 
	int		m_Pitch;		//水平跨距
	short*	m_buf1;			//波能数据缓冲区
	short*	m_buf2;			//波能数据缓冲区
};
#endif

