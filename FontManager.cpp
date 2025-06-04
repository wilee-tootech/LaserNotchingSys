// FontManager.cpp: implementation of the CFontManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "beameditor6.h"
#include "FontManager.h"
#include "Return.h"
#include "MKFileWriter.h"
#include "MKFileReader.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
/*******************************************************************
 CFontManager 
 ���� : ��Ʈ ĳ�� + ��Ʈ ��ü�� �����Ұ�� ��� 
 Jinsuk
*********************************************************************/



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFontManager::CFontManager()
{

}

CFontManager::~CFontManager()
{
	DeleteAll();
}

void CFontManager::DeleteAll()
{
	// ����Ʈ�� ��ϵ� ��� ����Ÿ�� �����.

	POSITION pos = m_lstFontData.GetHeadPosition();
	CFontData *pData;

	while( pos )
	{
		pData = m_lstFontData.GetNext(pos);
		ASSERT( IsBadReadPtr( pData, sizeof(CFontData) ) == FALSE);
		delete pData;
	}

	m_lstFontData.RemoveAll();
}


BYTE *CFontManager::GetFont(CString strFileName, DWORD &dwSize)
{
//	CFontData *pFontData;
	BYTE *pchTempData;


//	pFontData = Find(strFileName);
	
	//if(pFontData != NULL)  // ����Ʈ �߿� �̸��� ��ϵǾ����� ������ ȭ�Ͽ��� ���� �ε�
	{
		pchTempData = LoadFont(strFileName,dwSize);
//		if( pchTempData != NULL)
//			Add(strFileName, pchTempData, dwSize);
		return pchTempData;
	}
//	else // ����Ʈ �߿� �̹� �̸��� ��ϵǾ�������
//	{
 //		dwSize = pFontData->GetFontSize();
//		return pFontData->GetFontData();
//	}
}
void CFontManager::Add(CFontManager::CFontData *pData)
{
	m_lstFontData.AddTail(pData);
}
void CFontManager::Add(CString strFileName, BYTE *pchFontData, DWORD dwSize)
{
	CFontData *pFontData = new CFontData;
	pFontData->SetFontData(pchFontData);
	pFontData->SetFontName(strFileName);
	pFontData->SetFontSize(dwSize);
	m_lstFontData.AddTail(pFontData);		
}

BYTE *CFontManager::LoadFont(CString strFileName, DWORD &dwSize)
{
	CFile FontFile;
	CFileException e;
	BYTE *pFontData;
	
	if( !FontFile.Open( strFileName, CFile::modeRead, &e ))
	//if( !FontFile.Open( strFileName, CFile::modeRead ))
	{
		#ifdef _DEBUG
			afxDump << "File Open Error!" << e.m_cause << "\n";
		#endif
			return NULL;
	}

	dwSize = FontFile.GetLength();
	
//	if(pFontData != NULL) delete [] pFontData;	
	pFontData = new BYTE[dwSize];
	ASSERT(pFontData != NULL);
	FontFile.Read(pFontData, dwSize);
	FontFile.Close();
	return pFontData;
}

CFontManager &CFontManager::Instance()
{
	static CFontManager s_FontManager;
	return s_FontManager;
}

CFontManager::CFontData *CFontManager::Find(CString strFileName)
{
	POSITION pos;
	CFontData *pFontData;

	pos = m_lstFontData.GetHeadPosition();
	while( pos ) 
	{
		pFontData = m_lstFontData.GetNext(pos);
		if( pFontData->GetFontName() == strFileName )
		{
			return pFontData;
		}
	}
	return NULL;
}


char *CFontManager::Serialize(DWORD &dwLength)
{
	CMKFileWriter MKFW;
	CFontData *pFontData;
	DWORD dwID = 0 , dwSize;
	char *pData; POSITION pos;
	
	pos = m_lstFontData.GetHeadPosition();
	while (pos)
	{
		pFontData = m_lstFontData.GetNext(pos);
		pData = pFontData->Serialize(dwSize);
		
		if(pData == NULL) // NULL�� ��ȯ�Ǹ�
		{
			OutputDebugString("CFontManager::Serialize - Error Occured when doing serialize");
			return NULL;
		}
		
		MKFW.Add(dwID,dwSize,pData); //������Ʈ�� ������� 0������ 1�� �����ϴ� ID�� ������ ������� ����ȴ�.
		delete [] pData;
		dwID++;
	}
	return MKFW.GetTotalData(dwLength);
}

void CFontManager::Unserialize(char *pstrSerial)
{
	CMKFileReader MKFR;
	DeleteAll(); // �ϴ� �����ϰ� �ִµ���Ÿ�� ��� �����Ѵ� . �װ� �ùٸ� ��ø���������� ������ �ƴұ�. 
	CFontData *pFontData;
	char *pData;
	DWORD dwGetID, dwGetSize;
	
	MKFR.SeekInit(); // Ž�� ��ġ�� �Ǿ����� �ű��. ��ü�� �����ɶ� �⺻���� �Ǿ��̱� �ϴ�.
	while(1)
	{
		pData = MKFR.GetNext(pstrSerial,dwGetID,dwGetSize); 
		if( pData == NULL) return;
		pFontData = new CFontData;
		ASSERT( pFontData != NULL);
		pFontData->Unserialize(pData);  
		delete pData;
		m_lstFontData.AddTail(pFontData);
	}
}
///////////////////////////////////// CFontData ///////////////////////////
char *CFontManager::CFontData::Serialize(DWORD &dwLength)
{
	
	CMKFileWriter MKFW;
	MKFW.Add(ID_FONT_NAME,	m_strFontName.GetLength()+1,	(LPCTSTR)m_strFontName);
	MKFW.Add(ID_FONT_SIZE,	sizeof(DWORD),					&m_dwFontSize);
	MKFW.Add(ID_FONT_DATA,	m_dwFontSize,					m_pchFontData);

	return MKFW.GetTotalData(dwLength);
}

void CFontManager::CFontData::Unserialize(char *pstrSerial)
{
	CMKFileReader MKFR;
	char *pchData;
	DWORD dwSize, dwID;

	MKFR.GetAt(pstrSerial,   ID_FONT_SIZE, &m_dwFontSize);
	m_pchFontData = new BYTE[m_dwFontSize+1];
	MKFR.GetAt(pstrSerial,   ID_FONT_DATA, m_pchFontData);
	
	pchData = MKFR.GetAt(pstrSerial, ID_FONT_NAME,dwSize,dwID);
	m_strFontName = pchData;
	delete pchData;
}
		

void CFontManager::AddXvector(double xvector)
{

}
