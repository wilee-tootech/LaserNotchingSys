// Ctd.h: interface for the CCtd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTD_H__D85C871D_30A0_4E00_B51C_5A8F28E4CB33__INCLUDED_)
#define AFX_CTD_H__D85C871D_30A0_4E00_B51C_5A8F28E4CB33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCtd  
{
public:
	CCtd();
	virtual ~CCtd();

	BOOL OpenCtd(CString fileName, CPoint (*point)[MAX_CAL_DATA]);
	BOOL SaveCtd(CString fileName, CPoint (*baseData)[MAX_CAL_DATA], CPoint (*point)[MAX_CAL_DATA]);
	BOOL SaveCtd(CString fileName, CPoint (*point)[MAX_CAL_DATA]);

protected:
	CString m_fileName;
	CFile  *m_pFile;
};

#endif // !defined(AFX_CTD_H__D85C871D_30A0_4E00_B51C_5A8F28E4CB33__INCLUDED_)
