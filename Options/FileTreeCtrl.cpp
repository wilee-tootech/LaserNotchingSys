// FileTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "Option.h"
#include "FileTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileTreeCtrl
#include "def.h"
#include "DlgSelectDir.h"

CFileTreeCtrl::CFileTreeCtrl()
{
	// 이미지 리스트를 만든다
	m_IsBeDrive = TRUE;
}

CFileTreeCtrl::~CFileTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CFileTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CFileTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileTreeCtrl message handlers

int CFileTreeCtrl::SetImageList()
{
	if (m_imageDrives.Create(IDB_DRIVES, 16, 1, RGB(0,128,128)))
		CTreeCtrl::SetImageList(&m_imageDrives, TVSIL_NORMAL);
	return 0;
}

int CFileTreeCtrl::InitDriveCtrl()
{
	int nPos=0;
	int nDrives = 0;
	CString strDrive = "?:\\";

	// 디스크 드라이브 정보 얻기
	DWORD dwDriveList = ::GetLogicalDrives();

	while(dwDriveList)
	{
		if(dwDriveList & 1)
		{
			// "C:\\"와 같이 드아리브를 표시하는 문자열을 만듦
			strDrive.SetAt(0, 'A'+nPos);
			// 드라이브 문자열을 트리컨트롤에 노드로 추가
			if(AddDriveNode(strDrive))
				nDrives++;
		}
		// 우로 1비트 이동
		dwDriveList >>= 1;
		nPos++;
	}
	return nDrives;
}

/////////////////////////////////////////////////////
// 시스템에 있는 디스크를 컴색하여 컨트롤에 추가 한다
BOOL CFileTreeCtrl::AddDriveNode(CString &strDrive)
{
	CString str;
	HTREEITEM hItem;
	//static BOOL bFirst = TRUE;
	static BOOL bFirst = TRUE;

	// 디스크 드라이브의 타입을 얻음
	UINT nType = ::GetDriveType((LPCTSTR)strDrive);
	CWnd * pWnd = GetParent();

	switch(nType)
	{
	case DRIVE_REMOVABLE: // 플로피 드라이브 경우
		hItem = InsertItem(strDrive, ID_FLOPPY, ID_FLOPPY);
		InsertItem("", ID_CLOSEDFOLDER, ID_CLOSEDFOLDER, hItem);
		break;
	case DRIVE_FIXED:	// 하드 드라이브 경우
		hItem = InsertItem(strDrive, ID_HARDDISK, ID_HARDDISK);
		SetButtonState(hItem, strDrive);
		if(bFirst)
		{
			SelectItem(hItem);
			Expand(hItem, TVE_EXPAND);
			if (pWnd)
				pWnd->PostMessage(WM_USER_PATHCHANGED,(WPARAM)hItem);
			bFirst = FALSE;
		}
		break;
	case DRIVE_REMOTE: // 네트웍 드라이브인경우
		hItem = InsertItem(strDrive, ID_NETDRIVE, ID_NETDRIVE);
		SetButtonState(hItem, strDrive);
		break;
	case DRIVE_CDROM:	// CD롬 드라이브인 경우
		hItem = InsertItem(strDrive, ID_CDROM, ID_CDROM);
		InsertItem("", ID_CLOSEDFOLDER, ID_CLOSEDFOLDER, hItem);
		break;
	case DRIVE_RAMDISK: // RAM 드라이브인 경우
		hItem = InsertItem(strDrive, ID_HARDDISK, ID_HARDDISK);
		SetButtonState(hItem, strDrive);
		break;
	default:
		break;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////
// 서브 디렉토리의 존재 여부를 확인한다
BOOL CFileTreeCtrl::SetButtonState(HTREEITEM hItem, CString strPath)
{
	if(strPath.Right(1) != "\\")
		strPath += "\\";
	strPath += "*.*";

	CString strDirName;
	CFileFind filefind;
	BOOL bContinue;
	if(!(bContinue = filefind.FindFile(strPath)))
		return FALSE;

	while(bContinue)
	{
		bContinue = filefind.FindNextFile();
		// 디렉토리이면
		if(filefind.IsDirectory())
		{
			strDirName = filefind.GetFileName();
			if((strDirName !=".")&&(strDirName!=".."))
			{
				// .나 .. 가 아닌 디렉토리이면
				// 더미노드를 하나 추가 한다
				InsertItem("", ID_CLOSEDFOLDER, ID_CLOSEDFOLDER, hItem);
				break;
			}
		}
	}
	filefind.Close();
	return TRUE;
}

/////////////////////////////////////////////////////////////////
// 노드가 확장 하거나 축소 할 때 
void CFileTreeCtrl::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	// 확장 되거나 축소된 노드를 얻음
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	// 확장 되거나 축소된 노드가 나타내는 디렉토리명을 얻음
	CString str = GetPathFromNode(hItem);
	*pResult = FALSE;

	// 노드가 확장하는 경우
	if(pNMTreeView->action == TVE_EXPAND)
	{
		// 앞서 추가했던 더미 노드 제거
		DeleteFirstChild(hItem);
		// 진짜 디렉토리 구조를 읽어 표시
		if(AddDir(hItem, str) == 0)
			*pResult = TRUE;
	} else
	{	// 노드가 축소 되는 경우
		DeleteAllChildren(hItem);
		// 십자가 모양의 버튼 표시를 위해 더미 노드 추가
		if (GetParentItem(hItem) == NULL)
			InsertItem("", ID_CLOSEDFOLDER, ID_CLOSEDFOLDER, hItem);
		else
			SetButtonState(hItem, str);
	}
	*pResult = 0;
}

///////////////////////////////////////////////////////////////////
// 노드 확장, 축소 후 호출 된다
void CFileTreeCtrl::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	HTREEITEM hItem = pNMTreeView->itemNew.hItem;

	if(pNMTreeView->action == TVE_EXPAND)
	{
		if (m_IsBeDrive == FALSE)
		{	// 드라이브이고
			Expand(hItem, TVE_COLLAPSE);
			m_IsBeDrive = TRUE;
		}
	}
	m_IsBeDrive = TRUE;

	*pResult = 0;
}

///////////////////////////////////////////////////////
// 핸재 핸들의 Path를 구한다
CString CFileTreeCtrl::GetPathFromNode(HTREEITEM hItem)
{
	CString strResult = GetItemText(hItem);

	HTREEITEM hParent;
	// 루트 노드를 만날 때 까지 진행...
	while((hParent = GetParentItem(hItem)) != NULL)
	{
		CString str = GetItemText(hParent);
		if (str.Right(1) != "\\")
			str += "\\";
		strResult = str + strResult;
		hItem = hParent;
	}
	return strResult;
}

//////////////////////////////////////////////////////
// 첫번째 노드를 지운다(더미 노드 제거할 때 사용)
void CFileTreeCtrl::DeleteFirstChild(HTREEITEM hParent)
{
	HTREEITEM hItem;
	if(( hItem = GetChildItem(hParent)) != NULL)
		DeleteItem(hItem);
}

////////////////////////////////////////////////
// 모든 자식 노드를 제거한다
void CFileTreeCtrl::DeleteAllChildren(HTREEITEM hParent)
{
	HTREEITEM hItem;
	if((hItem = GetChildItem(hParent)) == NULL)
		return;
	do
	{
		HTREEITEM hNextItem = GetNextSiblingItem(hItem);
		DeleteItem(hItem);
		hItem = hNextItem;
	} while(hItem != NULL);
}

////////////////////////////////////////////////////////////
// 디렉토리를 입력으로 들어온 노드에 추가한다
int CFileTreeCtrl::AddDir(HTREEITEM hItem, CString &strPath)
{
	CString strFindPath;
	HTREEITEM hNewItem;
	int nCount = 0;

	// 지정된 디렉토리 뒤에 "\\*.*"를 덧붙임
	strFindPath = strPath;
	if(strFindPath.Right(1) != "\\")
		strFindPath += "\\";
	strFindPath += "*.*";

	CString strFileName, strNewPath;
	CFileFind filefind;

	// 탐색할 디렉토리 지정
	BOOL bContinue;
	if(!(bContinue = filefind.FindFile(strFindPath)))
	{
		if(GetParentItem(hItem) == NULL)
		{
			InsertItem("", ID_CLOSEDFOLDER, ID_CLOSEDFOLDER, hItem);
			m_IsBeDrive = FALSE;
		}
		return 0;
	}
	// 디렉토리 탐색
	while(bContinue)
	{
		bContinue = filefind.FindNextFile();
		// 디렉토리인 경우...
		if(filefind.IsDirectory())
		{
			strFileName = filefind.GetFileName();
			if(strFileName != "." && strFileName != "..")
			{	// 노드추가
				hNewItem = InsertItem((LPCTSTR)strFileName, ID_CLOSEDFOLDER, ID_OPENFOLDER, hItem);

				strNewPath = strPath;
				if(strNewPath.Right(1) != "\\")
					strNewPath += "\\";

				// 추가된 노드가 서브디렉토리를 가졌는지 확인
				strNewPath += strFileName;
				SetButtonState(hNewItem, strNewPath);
				nCount++;
			}
		}
	}
	filefind.Close();
	return nCount;
}

//////////////////////////////////////////////////////
// Path를 입력 받아 해당 경로를 보여준다
BOOL CFileTreeCtrl::SetFilePathTree(CString filepath)
{
	HTREEITEM hItem;
	hItem = GetRootItem();

	CString name;
	CString searchname;
	BOOL success = FALSE;

	//name=GetNextNameFromPath(filepath);
	while( (name=GetNextNameFromPath(filepath)) != "")
	{	
		name.MakeUpper();
		success = FALSE;
		do
		{
			searchname = GetItemText(hItem);
			searchname.MakeUpper();
			if( searchname == name)
			{
				SelectItem(hItem);
				Expand(hItem, TVE_EXPAND);
				hItem = GetChildItem(hItem);
				success = TRUE;
				break;
			}
		} while((hItem = GetNextSiblingItem(hItem)) != NULL);
	}
//	if (success == TRUE)
//		SelectItem(hItem);
	return success;
}

//////////////////////////////////////////////
// 경로를 입력 받아 첫번째 화일 이름을 반환 한다
CString CFileTreeCtrl::GetNextNameFromPath(CString& path)
{
	int index;
	CString result;

	index = path.Find('\\');
	
	if( index >= 0)
	{
		result = path.Left(index);
		path.Delete(0, index+1);

		if(result.GetAt(result.GetLength()-1) == ':')
			result += "\\";
	} else
	{
		result = path;
		path = "";
	}

	return result;
}

void CFileTreeCtrl::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	CWnd *pWnd = GetParent();
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;

	if (pWnd)
		pWnd->PostMessage(WM_USER_PATHCHANGED,(WPARAM)hItem);
	
	*pResult = 0;
}
