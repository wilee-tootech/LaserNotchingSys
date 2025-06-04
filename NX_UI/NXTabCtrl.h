#pragma once


// CNXTabCtrl

class AFX_EXT_CLASS CNXTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CNXTabCtrl)

public:
	CNXTabCtrl();
	virtual ~CNXTabCtrl();

protected:
	DECLARE_MESSAGE_MAP()

private:
	CBitmap m_background;

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


