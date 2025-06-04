// Parser.h: interface for the CParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSER_H__326C773A_B96F_4D4E_8E50_C116C04E5E0A__INCLUDED_)
#define AFX_PARSER_H__326C773A_B96F_4D4E_8E50_C116C04E5E0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//
//
//    :   SavingPath = C:\Windows    
//  이런 형식의 저장 화일에서 = 뒤의 필요한 정보만 빼오는 클래스 
//
//

class CParser  
{
public:
	CParser();
	virtual ~CParser();
	
	CString GetString(CString &strSource, CString strIndex);

private:
	CString m_strSource;
};


#endif // !defined(AFX_PARSER_H__326C773A_B96F_4D4E_8E50_C116C04E5E0A__INCLUDED_)
