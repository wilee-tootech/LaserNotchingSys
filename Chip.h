#ifndef _Chip
#define _Chip

class  CChip  
{
public:
	BOOL IsIn(CPoint point);
	BOOL Check(CPoint point);
	void Draw(CDC *pDC);
	BOOL m_selected;
	int m_height;
	int m_width;
	void Copy(CChip Source);
	CPoint m_position;
	int m_offsetY;
	int m_offsetX;
	CChip();
	virtual ~CChip();
};

#endif // _Chip