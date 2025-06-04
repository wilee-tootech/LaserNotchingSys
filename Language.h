// Language.h: interface for the CLanguage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANGUAGE_H__770DE4A5_BF30_48F1_B1CC_5645A5C92E4C__INCLUDED_)
#define AFX_LANGUAGE_H__770DE4A5_BF30_48F1_B1CC_5645A5C92E4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLanguage  
{
public:
	CLanguage();
	virtual ~CLanguage();

	int	   GetString(int BaseString);
	void   SetLanguage(int Language);
	static CLanguage *GetInstance();// 유일한 instance 반환

private:
	int m_iLanguage;
	static CLanguage *m_pLanguage; // 유일한 instance
};

#endif // !defined(AFX_LANGUAGE_H__770DE4A5_BF30_48F1_B1CC_5645A5C92E4C__INCLUDED_)
