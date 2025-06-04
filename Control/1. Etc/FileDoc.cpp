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

	// ��� + ���ϸ� + Ȯ����
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
	// Open�ϸ� �ڵ����� ��ο� �̸�, Ȯ���ڸ� �м��Ѵ�.
	// ���� ��θ� ������ File���� ���� ������ ��� ���� ""
	if(m_strFileRoot.IsEmpty() && m_strFileTitle.IsEmpty() && m_strFileExt.IsEmpty()) return "";

	CString strNum, imsi;
	strNum.Format("%d", number);

	int len = strFormat.GetLength();
	int len1 = strNum.GetLength();

	// ���ڶ� ���鸸ŭ "0"�� ä��� ���ڸ� ������.
	if(len>len1)
	{
		for(int i=0; i<(len-len1); i++) imsi += "0";
		strNum = imsi + strNum;
	}

	// ����� �ϴ� ���Ϸ� �����.
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
//	File ���� �Լ�.
//


//////////////////////////////////////////////////////////////////////////////
// �ؽ�Ʈ ������ ȭ�Ͽ� ����ϱ�.
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

	// ���� \r\n�� ������ ���.
	// \n�̶�� ���̰� �ϰ�..
	Buff.Replace("\r\n", "\n");	

	// \n�� ��� CRLF�� ��ġ�Ѵ�.
	Buff.Replace("\n", "\r\n");

	UINT length = Buff.GetLength();
	char* pBuff = (LPSTR)(LPCTSTR) Buff;

	if(bAttach) file.SeekToEnd();

	file.Write(pBuff, length);
	file.Close();

	return true;
}

//////////////////////////////////////////////////////////////////////////////
// ������ File�κ��� �ؽ�Ʈ ȭ�� �о� Buff�� ���.
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
	strFileName.Replace("\\\\", "\\"); // ���� �齽���ø� ���� �齽���÷� �����մϴ�.

    CFile file;
    if (!file.Open(strFileName, CFile::modeRead))
    {
        return -1; // ������ ���� ���� ��� -1�� ��ȯ�մϴ�.
    }

    DWORD length = file.GetLength();

    if (!length)
    {
        file.Close();
        return 0; // ������ ����ִ� ��� 0�� ��ȯ�մϴ�.
    }

    char* pBuff = new char[length + 1];

    file.Read(pBuff, (UINT)length);
    pBuff[length] = '\0';
    file.Close();

    // ���ۿ��� ���� ����('\n')�� ������ ���� ���� ���� ����մϴ�.
    int lineCount = 0;
    for (DWORD i = 0; i < length; ++i)
    {
        if (pBuff[i] == '\n')
        {
            lineCount++;
        }
    }

    delete[] pBuff;
    return lineCount + 1; // ���� ���� ������ �ִ� ���� ������ ���̹Ƿ� 1�� ���մϴ�.
}

//////////////////////////////////////////////////////////////////////////////
// �ؽ�Ʈ ������ �ٴ����� ������ �б�.
//
// return : ���μ��� ����.
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
// �޸��� �̷���� ������ �ܾ�� ������.
//
// return : ������� ����.
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
// ��ξȿ� �ִ� ���� �̸��� ���.
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
// ��ξȿ� �ִ� ����ã��. "ã�� �� ) strFileNames == "A.txt, B.Txt, C.Txt"
// ���� strRoot�� ����ְ� strFilter�� �����Ǿ� �ִٸ�, 
//		strFilter�� Root�� Filter�� ������� ������ ã���Ѵ�.
//		strFilter�ȿ� ���丮�� �����ϰ� �ִٸ� �״� strRoot���� �켱�Ѵ�..
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
			// �߸��Ǿ����ϴ�. ��� �ϳ��� ���� �� �� ����..

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
					// Root���� �ݵ�� ����̺� ������ �־���Ѵ�.
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

	// ���Ϳ� �´� ������ ã�´�..
	BOOL bFind = Find.FindFile(strSearchFilter);

	while(bFind) 
	{
		bFind = Find.FindNextFile();

		// FindNextFile() ==> ���� �� ��..
		//
		// ���� ���� ���������� ã�ƾ� �Ѵٸ� ��ŵ.
		//////////////////////////////////////////////////////////////////////
		if(Find.IsDots() || Find.IsDirectory()) continue;

		// FindNextFile() ==> �����϶�..
		//
		// ���Ͽ� ���͸��� �����Ͽ� ���ϴ� ������ ��´�.
		//////////////////////////////////////////////////////////////////////
		CString strFilename = Find.GetFilePath();

		// ���ϴµ��� ���͸��� �Ǿ��ٸ� ����Ѵ�.
		buf += strFilename + ",";
		nFileSu++;
	}

	if(bSubFolder)
	{
		// ������������ ��� ã�ƾ��Ѵ�....
		BOOL bFind = Find.FindFile( strRoot + "\\*.*" );

		CString bufXXX;

		while(bFind) 
		{
			bFind = Find.FindNextFile();

			bufXXX += Find.GetFileName() + ",";

			if(Find.IsDots()) continue;
			if(!Find.IsDirectory()) continue;

			// FindNextFile() ==> ���� �� ��..
			//
			// ���� ���� ���������� ã�ƾ� �Ѵٸ�  ���ȣ�⿡ ���� ã���Ѵ�.
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

	// �ǳ��� ","�� �����Ѵ�.
	strFileNames = buf.Left(buf.GetLength() - 1);
	strFileNames.Replace("\\\\", "\\");

	return nFileSu;
}

//////////////////////////////////////////////////////////////////////////////
// ������ �����ϳ� �������� �ʴ��� - �ش� ������ �ִٸ� True
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

	// AfxMessageBox�� ȭ���� �߾ӿ� ���� �ʴ� ����� 
	// �ڵ��� �����Ͽ���.

	// �� �Լ��� ���ϴ� �������� �޼��� �ڽ��� ��� ���̴�.

	if( ::DeleteFile(strSrcFileName) ) 
	{
		// �� ������ �Ǿ���.
		// AfxMessageBox("�����Ǿ����ϴ�.");
	}
	else 
	{
		// Delete���� �ʾҴ�.
		// ȭ���� ����.
		// �б� �����̴�..
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
		// �� ������ �Ǿ���.
		/*AfxMessageBox("Copy Ok");*/
	}
	else {

		// ���� ������������ Copy�� ���� �ʾҴ�.
		// ������ ���� ������ �ϳ��� ���̴�. (�ι�° ���ڰ� true)�� �־����� ���)
		//	  1. ���丮�� �������� �ʴ´�.
		//	  2. �̹� �Ȱ��� ȭ���� �����Ѵ�.
		//    3. ����ȭ���� ����.
		//	  4. �� �ڿ� �ٸ� ������ �ִ�. �� ���� GetLastError()�Լ��� �� ������ ã�´�.
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

