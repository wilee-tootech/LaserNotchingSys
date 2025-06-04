// FileDoc.cpp: implementation of the CFileDoc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CFileDoc::CFileDoc()
{
}

CFileDoc::CFileDoc(CString fileName)
{
	if(fileName.IsEmpty()) return;

	m_strFileRoot.Empty();
	m_strFileTitle.Empty();
	m_strFileExt.Empty();

	if(!Open(fileName))
	{
		m_strFileRoot.Empty();
		m_strFileTitle.Empty();
		m_strFileExt.Empty();
		m_strFilePath.Empty();
	}
}

CFileDoc::~CFileDoc()
{

}


BOOL CFileDoc::Open(CString strFileName)
{
	strFileName.Replace("\\\\","\\");

	TCHAR szDir[255], szDrive[255], szFileName[255], szFileExt[20];

	_tsplitpath((LPCTSTR)strFileName, szDrive, szDir,szFileName, szFileExt);	

	CString strDrive = szDrive;
	CString strDir = szDir;

	if(strDrive.IsEmpty() || strDir.IsEmpty())
	{
		char arRoot[100];
		::GetCurrentDirectory(100, arRoot);

		m_strFileRoot = arRoot;
	}
	else
		m_strFileRoot.Format("%s%s", szDrive, szDir);

	m_strFileTitle	=	szFileName;
	m_strFileExt	=	szFileExt;
	m_strFileExt.Replace(".","");

	// 경로 + 파일명 + 확장자
	/////////////////////////////////////////////////////////
	m_strFilePath  = m_strFileRoot + m_strFileTitle + "." + m_strFileExt;

	return true;
}

CString CFileDoc::GetFilePath()
{
	return m_strFilePath;
}

CString CFileDoc::GetRoot()
{
	return m_strFileRoot;
}

CString CFileDoc::GetFileName()
{
	if(m_strFileTitle.IsEmpty() && m_strFileExt.IsEmpty()) return "";

	CString buf = m_strFileTitle + "." + m_strFileExt;

	return buf;
}

CString CFileDoc::GetFileTitle()
{
	return m_strFileTitle;
}

CString CFileDoc::GetFileExt()
{
	return m_strFileExt;
}

CString CFileDoc::GetFileNameAddNumber(int number, CString strFormat)
{
	// Open하면 자동으로 경로와 이름, 확장자를 분석한다.
	// 만약 경로를 포함한 File명을 얻지 못했을 경우 리턴 ""
	if(m_strFileRoot.IsEmpty() && m_strFileTitle.IsEmpty() && m_strFileExt.IsEmpty()) return "";

	CString strNum, imsi;
	strNum.Format("%d", number);

	int len = strFormat.GetLength();
	int len1 = strNum.GetLength();

	// 모자란 공백만큼 "0"을 채우고 숫자를 덧붙임.
	if(len>len1)
	{
		for(int i=0; i<(len-len1); i++) imsi += "0";
		strNum = imsi + strNum;
	}

	// 얻고자 하는 파일로 만든다.
	CString buf;
	buf	= m_strFileRoot + "\\";
	buf += m_strFileTitle + strNum + "." + m_strFileExt;

	buf.Replace("\\\\","\\");
	buf.Replace("\\\\","\\");
	return buf;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//
//	File 관련 함수.
//


//////////////////////////////////////////////////////////////////////////////
// 텍스트 문장을 화일에 기록하기.
//////////////////////////////////////////////////////////////////////////////
BOOL CFileDoc::WriteTextToFile(CString strFileName, CString& Buff, BOOL bAttach)
{
	strFileName.Replace("\\\\", "\\");

	CFile file;

	if(bAttach)
	{
		if(!file.Open(strFileName, CFile::modeWrite)) 
			if(!file.Open(strFileName, CFile::modeWrite | CFile::modeCreate )) return false;
	}
	else
	{
		if(!file.Open(strFileName, CFile::modeWrite | CFile::modeCreate )) return false;
	}

	// 본래 \r\n이 들어왔을 경우.
	// \n이라고 속이게 하고..
	Buff.Replace("\r\n", "\n");	

	// \n이 라면 CRLF로 대치한다.
	Buff.Replace("\n", "\r\n");

	UINT length = Buff.GetLength();
	char* pBuff = (LPSTR)(LPCTSTR) Buff;

	if(bAttach) file.SeekToEnd();

	file.Write(pBuff, length);
	file.Close();

	return true;
}

//////////////////////////////////////////////////////////////////////////////
// 지정된 File로부터 텍스트 화일 읽어 Buff에 담기.
//////////////////////////////////////////////////////////////////////////////
BOOL CFileDoc::ReadTextFromFile(CString strFileName, CString& Buff)
{
	strFileName.Replace("\\\\", "\\");

	CFile file;
	if ( ! file.Open(strFileName, CFile::modeRead ) )
	{
		return false;
	}

	DWORD length = file.GetLength();
	
	if(!length) { Buff.Empty(); return false; }

	char* pBuff = new char[length+1];

	file.Read(pBuff, (UINT)length);
	pBuff[length] = '\0';
	file.Close();

	Buff = pBuff;
	Buff.Replace("\r\n","\n");

	delete[] pBuff;
	return true;
}

int CFileDoc::GetNumberOfLinesInFile(CString strFileName)
{
	strFileName.Replace("\\\\", "\\"); // 이중 백슬래시를 단일 백슬래시로 변경합니다.

    CFile file;
    if (!file.Open(strFileName, CFile::modeRead))
    {
        return -1; // 파일을 열지 못한 경우 -1을 반환합니다.
    }

    DWORD length = file.GetLength();

    if (!length)
    {
        file.Close();
        return 0; // 파일이 비어있는 경우 0을 반환합니다.
    }

    char* pBuff = new char[length + 1];

    file.Read(pBuff, (UINT)length);
    pBuff[length] = '\0';
    file.Close();

    // 버퍼에서 개행 문자('\n')의 개수를 세어 라인 수를 계산합니다.
    int lineCount = 0;
    for (DWORD i = 0; i < length; ++i)
    {
        if (pBuff[i] == '\n')
        {
            lineCount++;
        }
    }

    delete[] pBuff;
    return lineCount + 1; // 개행 문자 다음에 있는 줄이 마지막 줄이므로 1을 더합니다.
}

//////////////////////////////////////////////////////////////////////////////
// 텍스트 문장을 줄단위로 나누기 읽기.
//
// return : 라인수를 리턴.
//
//////////////////////////////////////////////////////////////////////////////
int CFileDoc::GetStringFromText(CString strFullText, CString* pLineBuffs, int nBuffSu)
{
	if(strFullText.IsEmpty()) return 0;
	int i = 0;
	for( i=0; i<nBuffSu; i++)
	{
		if(!AfxExtractSubString(pLineBuffs[i], strFullText, i, '\n')) break;
	}

	for (int j=i; j<nBuffSu; j++) pLineBuffs[j].Empty();

	return i;
}

//////////////////////////////////////////////////////////////////////////////
// 콤마로 이루어진 문장을 단어로 나누기.
//
// return : 워드수를 리턴.
//
//////////////////////////////////////////////////////////////////////////////
int CFileDoc::GetWordFromComma(CString strCommaString, CString* pWordBuff, int nBuffSu, char chSep)
{
	if(strCommaString.IsEmpty()) return 0;
	int i=0;
	for( i=0; i<nBuffSu; i++)
	{
		if(!AfxExtractSubString(pWordBuff[i], strCommaString, i, chSep)) break;
	}

	for (int j=i; j<nBuffSu; j++) pWordBuff[j].Empty();

	return i;
}


//////////////////////////////////////////////////////////////////////////////
// 경로안에 있는 폴더 이름들 얻기.
//////////////////////////////////////////////////////////////////////////////
int CFileDoc::GetFolders(CString& strFolders, CString strRoot)
{
	CString Files;
	Files = strRoot + "\\*.*";
	Files.Replace("\\\\", "\\");

	CFileFind Find;
	BOOL bFind;
	bFind =	Find.FindFile(Files);

	CString buf;
	int nSu=0;

	while(bFind) {
		bFind = Find.FindNextFile();
		if(Find.IsDots() || !Find.IsDirectory()) continue;
		buf += Find.GetFileName() + ",";
		nSu++;
	}

	strFolders = buf.Left(buf.GetLength() - 1);
	strFolders.Replace("\\\\", "\\");

	return nSu;
}

//////////////////////////////////////////////////////////////////////////////
// 경로안에 있는 파일찾기. "찾은 예 ) strFileNames == "A.txt, B.Txt, C.Txt"
// 만약 strRoot가 비어있고 strFilter가 지정되어 있다면, 
//		strFilter의 Root에 Filter를 적용시켜 파일을 찾게한다.
//		strFilter안에 디렉토리를 포함하고 있다면 그는 strRoot보다 우선한다..
//////////////////////////////////////////////////////////////////////////////
int CFileDoc::GetFiles(CString& strFileNames, CString strFilter, CString strRoot, BOOL bSubFolder)
{
	CString strDrive, strDir, strName, strExt;

	if(strFilter.IsEmpty()) { strName = "*"; strExt = ".*"; }
	else 
	{

		TCHAR szDir[255], szDrive[255], szFileName[255], szFileExt[20];

		_tsplitpath((LPCTSTR)strFilter, szDrive, szDir,szFileName, szFileExt);	

		strDrive = szDrive;
		strDir = szDir;
		strName = szFileName;
		strExt = szFileExt;

		if(strName.IsEmpty()) strName = "*";
		if(strExt.IsEmpty()) strExt = "*";

		if(strDrive.IsEmpty() ^ strDir.IsEmpty())
		{
			// 잘못되었습니다. 어느 하나만 포함 할 수 없당..

			strFileNames = "";
			return 0;
		}

		if(strDrive.IsEmpty() || strDir.IsEmpty())
		{
			if(strRoot.IsEmpty())
			{
				CFileDoc fileDoc(strFilter);
				strRoot = fileDoc.GetRoot();
			}
			else
			{
				_tsplitpath((LPCTSTR)strRoot, szDrive, szDir,szFileName, szFileExt);	

				CString strDrive1 = szDrive;

				if(strDrive1.IsEmpty())
				{
					// Root에는 반드시 드라이브 정보가 있어야한다.
					strFileNames = "";
					return 0;
				}
			}
		}
		else
		{
			strRoot = strDrive+strDir;
		}

		strRoot += "\\";
		strRoot.Replace("\\\\", "\\");
	}

	strFilter = strName + strExt;

	CFileFind Find;
	CString buf;
	int nFileSu=0;

	CString strSearchFilter = strRoot + "\\" + strFilter;
	strSearchFilter.Replace("\\\\", "\\");

	// 필터에 맞는 파일을 찾는다..
	BOOL bFind = Find.FindFile(strSearchFilter);

	while(bFind) 
	{
		bFind = Find.FindNextFile();

		// FindNextFile() ==> 폴더 일 때..
		//
		// 만약 서브 폴더에서도 찾아야 한다면 스킵.
		//////////////////////////////////////////////////////////////////////
		if(Find.IsDots() || Find.IsDirectory()) continue;

		// FindNextFile() ==> 파일일때..
		//
		// 파일에 필터링을 적용하여 원하는 파일을 얻는다.
		//////////////////////////////////////////////////////////////////////
		CString strFilename = Find.GetFilePath();

		// 원하는데로 필터링이 되었다면 기록한다.
		buf += strFilename + ",";
		nFileSu++;
	}

	if(bSubFolder)
	{
		// 서브폴더에서 계속 찾아야한다....
		BOOL bFind = Find.FindFile( strRoot + "\\*.*" );

		CString bufXXX;

		while(bFind) 
		{
			bFind = Find.FindNextFile();

			bufXXX += Find.GetFileName() + ",";

			if(Find.IsDots()) continue;
			if(!Find.IsDirectory()) continue;

			// FindNextFile() ==> 폴더 일 때..
			//
			// 만약 서브 폴더에서도 찾아야 한다면  재귀호출에 의해 찾게한다.
			//////////////////////////////////////////////////////////////////////

			CString Names1, Root1;
			Root1 = strRoot + "\\" + Find.GetFileName();
			int nSu = GetFiles(Names1, strFilter, Root1, bSubFolder);
			
			if(nSu) 
			{
				nFileSu += nSu; 
				buf += Names1 + ",";
			}
		}
	}

	// 맨끝에 ","는 제거한다.
	strFileNames = buf.Left(buf.GetLength() - 1);
	strFileNames.Replace("\\\\", "\\");

	return nFileSu;
}

//////////////////////////////////////////////////////////////////////////////
// 파일이 존재하냐 존재하지 않느냐 - 해당 파일이 있다면 True
//////////////////////////////////////////////////////////////////////////////
BOOL CFileDoc::IsFileFind(CString strFileName)
{
	CFileFind Find;
	return	Find.FindFile(strFileName);
}

CString CFileDoc::GetCurrentDirectory()
{
	char pRoot[255]; memset(pRoot,0,255);
	::GetCurrentDirectory(255, pRoot);
	CString directory = pRoot;

	return directory;
}

CString CFileDoc::GetExeDirectory()
{
	char pRoot[255]; memset(pRoot,0,255);
	GetModuleFileName(AfxGetApp()->m_hInstance, pRoot,255);
	CString directory = pRoot;

	return directory;
}


void CFileDoc::SetCurrentDirectory(CString strDirectory)
{
	::SetCurrentDirectory(strDirectory);
}

BOOL CFileDoc::DeleteFile(CString strSrcFileName)
{
	strSrcFileName.Replace("\\\\", "\\");

	// AfxMessageBox가 화면의 중앙에 뜨지 않는 관계로 
	// 코딩을 삭제하였다.

	// 이 함수를 콜하는 상위에서 메세지 박스를 띄울 것이다.

	if( ::DeleteFile(strSrcFileName) ) 
	{
		// 잘 수행이 되었다.
		// AfxMessageBox("삭제되었습니다.");
	}
	else 
	{
		// Delete되지 않았다.
		// 화일이 없다.
		// 읽기 전용이다..
		return false;
	}

	return true;
}

BOOL CFileDoc::CopyFile(CString strSrcFileName, CString strTrgFileName, BOOL bForce)
{
	strSrcFileName.Replace("\\\\", "\\");
	strTrgFileName.Replace("\\\\", "\\");

	if(bForce)
	{
		::CopyFile(strSrcFileName, strTrgFileName, false);
		return true;
	}

	if( ::CopyFile(strSrcFileName, strTrgFileName, true)) 
	{
		// 잘 수행이 되었다.
		/*AfxMessageBox("Copy Ok");*/
	}
	else {

		// 무슨 이유에서인지 Copy가 되지 않았다.
		// 다음과 같은 이유중 하나일 것이다. (두번째 인자가 true)로 주어졌을 경우)
		//	  1. 디렉토리가 존재하지 않는다.
		//	  2. 이미 똑같은 화일이 존재한다.
		//    3. 원본화일이 없다.
		//	  4. 그 박에 다른 에러가 있다. 이 때는 GetLastError()함수로 그 원인을 찾는다.
		if( ERROR_FILE_EXISTS == GetLastError()) 
		{
			CString Buf;
			Buf.Format("Aleady Exist File.\n\nRetry?");
			if ( IDYES == AfxMessageBox(Buf, MB_ICONWARNING|MB_YESNO) ) 
			{
				::CopyFile(strSrcFileName, strTrgFileName, false);
			}
			else return false;
		}
		else
		{
			if( ERROR_NOT_READY == GetLastError()) 
			{
				CString Buf;
				Buf.Format("Drive Not Ready.\n");
				AfxMessageBox(Buf, MB_ICONSTOP);
			}
			else
			{
				CString Buf;
				Buf.Format("Error Code : %d\n",GetLastError());
				AfxMessageBox(Buf, MB_ICONSTOP);
			}
			return false;
		}
	}

	return true;
}

