// Option.h: interface for the COption class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTION_H__A2D5D653_5C3D_4DD5_8307_C82B3E8746C0__INCLUDED_)
#define AFX_OPTION_H__A2D5D653_5C3D_4DD5_8307_C82B3E8746C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COption  
{
public:
	char * m_cpLaserControl;
	void SetVariable(CString Index, CString Variable);
	BOOL LoadFile(char *cpFileName);
	COption();
	virtual ~COption();

private:
	int   m_iMm;
	int   m_iField;
	int   m_iKindOfLaser;
	int   m_iHead;
	char *m_cpDspFileName;
	char *m_cpUnit;
	float m_fFieldAngle;
	int   m_iKindOfUser;
	BOOL  m_bShutter;
	BOOL  m_bUseChipSelect;
	BOOL  m_bUseTwoPart;
	BOOL  m_bUseLoadingImage;
	BOOL  m_bUseNetwork;
	BOOL  m_bUseHKImage;
	BOOL  m_bUseDefaultFile;
};

#endif // !defined(AFX_OPTION_H__A2D5D653_5C3D_4DD5_8307_C82B3E8746C0__INCLUDED_)
