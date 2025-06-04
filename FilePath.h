// FilePath.h: interface for the CFilePath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEPATH_H__C4183825_4DC8_497B_B0E0_7E55EAA17C73__INCLUDED_)
#define AFX_FILEPATH_H__C4183825_4DC8_497B_B0E0_7E55EAA17C73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFilePath  
{
public:
	CFilePath();
	virtual ~CFilePath();

	void	SetScribeFilePath(CString strScribe);
	CString GetScribeFilePath();
	void	SetDeviceFilePath(CString strDevice);
	CString GetDeviceFilePath();
	void	SetMarkFilePath(CString strMark);
	CString GetMarkFilePath();

	static CFilePath *GetInstance();
	
	CString m_strScribe;

private:
	static CFilePath *m_pFilePath; // ¿Ø¿œ«— instance

	CString m_strDevice;
	CString m_strMark;
};

#endif // !defined(AFX_FILEPATH_H__C4183825_4DC8_497B_B0E0_7E55EAA17C73__INCLUDED_)
