// FontManager.h: interface for the CFontManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FONTMANAGER_H__D417DB8A_ED43_4FED_B561_6A0925657A47__INCLUDED_)
#define AFX_FONTMANAGER_H__D417DB8A_ED43_4FED_B561_6A0925657A47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <AFXTEMPL.H>


#define FM    CFontManager::Instance()




class CFontManager  
{
public:
	class CFontData;	

	CFontManager();
	virtual ~CFontManager();

	BYTE *GetFont(CString strFileName, DWORD &dwSize);
	static CFontManager &Instance();

	CFontManager::CFontData *Find(CString strFileName);
	
private:
	
	BYTE *LoadFont(CString strFileName, DWORD &);
	void Add(CString strFileName, BYTE *pchFontData, DWORD dwSize);
	void Add(CFontManager::CFontData *pData);
	void DeleteAll();

	
public:
	class CFontData
	{
	public:
		enum VariableID
		{
			ID_FONT_DATA = 1,
			ID_FONT_SIZE = 2,
			ID_FONT_NAME = 3
		};
	public:

		CFontData()
		{
			m_pchFontData = NULL;
			m_dwFontSize = 0;
			m_strFontName = _T("");
		}
		~CFontData()
		{
			if( m_pchFontData != NULL) 
				delete m_pchFontData;
		}
		void SetFontName(CString strFontName)
		{
			m_strFontName = strFontName;
		}
		void SetFontData(BYTE *pchFontData)
		{
			ASSERT( pchFontData != NULL);
			m_pchFontData = pchFontData;
		}
		void SetFontSize(DWORD dwSize)
		{
			ASSERT(dwSize < 1000000);  // 이렇게 큰 경우는 보통 엉뚱 한값이 들어올때 버그잡기 쉽겠지?
			m_dwFontSize = dwSize;
		}

		CString GetFontName() const
		{
			return m_strFontName;
		}
		BYTE *GetFontData() const
		{
			return m_pchFontData;
		}
		DWORD GetFontSize() const
		{
			return m_dwFontSize;
		}

		char *Serialize(DWORD &dwLength);
		void Unserialize(char *pstrSerial);
		
		
	private:
		CString m_strFontName;
		BYTE *m_pchFontData;
		DWORD m_dwFontSize;
	};

public:
	void AddXvector(double xvector);
	char *Serialize(DWORD &dwLength);
	void Unserialize(char *pstrSerial);

private:
	CList <CFontData *,CFontData *> m_lstFontData;

};

#endif // !defined(AFX_FONTMANAGER_H__D417DB8A_ED43_4FED_B561_6A0925657A47__INCLUDED_)
