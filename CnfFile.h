// CnfFile.h: interface for the CCnfFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNFFILE_H__E0978161_38E5_11D6_97D6_0000B4BB2A6F__INCLUDED_)
#define AFX_CNFFILE_H__E0978161_38E5_11D6_97D6_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCnfFile  
{
public:
	BOOL SaveFile(int maxField, int maxMmSize);
	CString m_fileName;
	BOOL SaveFile();
	int m_maxMmSize;
	int m_maxField;
	BOOL Open(CString fileName);
	CCnfFile();
	virtual ~CCnfFile();
};

#endif // !defined(AFX_CNFFILE_H__E0978161_38E5_11D6_97D6_0000B4BB2A6F__INCLUDED_)
