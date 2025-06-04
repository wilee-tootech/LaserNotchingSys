// StatusDisplay.h: interface for the CStatusDisplay class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSDISPLAY_H__BFAFE236_A717_4AE1_A502_D4CEB1B27FFD__INCLUDED_)
#define AFX_STATUSDISPLAY_H__BFAFE236_A717_4AE1_A502_D4CEB1B27FFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStatusDisplay  
{
public:
	void CalCurrentPoint(CPoint cpCurrent);
	CStatusDisplay();
	virtual ~CStatusDisplay();

	void DisplayStatus();
	void SetString(CString strStatus);
	void SetCurrentPoint(CPoint cpCurrent);
private:
	CString m_strStatus;
};

#endif // !defined(AFX_STATUSDISPLAY_H__BFAFE236_A717_4AE1_A502_D4CEB1B27FFD__INCLUDED_)
