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
	// �̹��� ����Ʈ�� �����
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

	// ��ũ ����̺� ���� ���
	DWORD dwDriveList = ::GetLogicalDrives();

	while(dwDriveList)
	{
		if(dwDriveList & 1)
		{
			// "C:\\"�� ���� ��Ƹ��긦 ǥ���ϴ� ���ڿ��� ����
			strDrive.SetAt(0, 'A'+nPos);
			// ����̺� ���ڿ��� Ʈ����Ʈ�ѿ� ���� �߰�
			if(AddDriveNode(strDrive))
				nDrives++;
		}
		// ��� 1��Ʈ �̵�
		dwDriveList >>= 1;
		nPos++;
	}
	return nDrives;
}

/////////////////////////////////////////////////////
// �ý��ۿ� �ִ� ��ũ�� �Ļ��Ͽ� ��Ʈ�ѿ� �߰� �Ѵ�
BOOL CFileTreeCtrl::AddDriveNode(CString &strDrive)
{
	CString str;
	HTREEITEM hItem;
	//static BOOL bFirst = TRUE;
	static BOOL bFirst = TRUE;

	// ��ũ ����̺��� Ÿ���� ����
	UINT nType = ::GetDriveType((LPCTSTR)strDrive);
	CWnd * pWnd = GetParent();

	switch(nType)
	{
	case DRIVE_REMOVABLE: // �÷��� ����̺� ���
		hItem = InsertItem(strDrive, ID_FLOPPY, ID_FLOPPY);
		InsertItem("", ID_CLOSEDFOLDER, ID_CLOSEDFOLDER, hItem);
		break;
	case DRIVE_FIXED:	// �ϵ� ����̺� ���
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
	case DRIVE_REMOTE: // ��Ʈ�� ����̺��ΰ��
		hItem = InsertItem(strDrive, ID_NETDRIVE, ID_NETDRIVE);
		SetButtonState(hItem, strDrive);
		break;
	case DRIVE_CDROM:	// CD�� ����̺��� ���
		hItem = InsertItem(strDrive, ID_CDROM, ID_CDROM);
		InsertItem("", ID_CLOSEDFOLDER, ID_CLOSEDFOLDER, hItem);
		break;
	case DRIVE_RAMDISK: // RAM ����̺��� ���
		hItem = InsertItem(strDrive, ID_HARDDISK, ID_HARDDISK);
		SetButtonState(hItem, strDrive);
		break;
	default:
		break;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////
// ���� ���丮�� ���� ���θ� Ȯ���Ѵ�
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
		// ���丮�̸�
		if(filefind.IsDirectory())
		{
			strDirName = filefind.GetFileName();
			if((strDirName !=".")&&(strDirName!=".."))
			{
				// .�� .. �� �ƴ� ���丮�̸�
				// ���̳�带 �ϳ� �߰� �Ѵ�
				InsertItem("", ID_CLOSEDFOLDER, ID_CLOSEDFOLDER, hItem);
				break;
			}
		}
	}
	filefind.Close();
	return TRUE;
}

/////////////////////////////////////////////////////////////////
// ��尡 Ȯ�� �ϰų� ��� �� �� 
void CFileTreeCtrl::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	// Ȯ�� �ǰų� ��ҵ� ��带 ����
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	// Ȯ�� �ǰų� ��ҵ� ��尡 ��Ÿ���� ���丮���� ����
	CString str = GetPathFromNode(hItem);
	*pResult = FALSE;

	// ��尡 Ȯ���ϴ� ���
	if(pNMTreeView->action == TVE_EXPAND)
	{
		// �ռ� �߰��ߴ� ���� ��� ����
		DeleteFirstChild(hItem);
		// ��¥ ���丮 ������ �о� ǥ��
		if(AddDir(hItem, str) == 0)
			*pResult = TRUE;
	} else
	{	// ��尡 ��� �Ǵ� ���
		DeleteAllChildren(hItem);
		// ���ڰ� ����� ��ư ǥ�ø� ���� ���� ��� �߰�
		if (GetParentItem(hItem) == NULL)
			InsertItem("", ID_CLOSEDFOLDER, ID_CLOSEDFOLDER, hItem);
		else
			SetButtonState(hItem, str);
	}
	*pResult = 0;
}

///////////////////////////////////////////////////////////////////
// ��� Ȯ��, ��� �� ȣ�� �ȴ�
void CFileTreeCtrl::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	HTREEITEM hItem = pNMTreeView->itemNew.hItem;

	if(pNMTreeView->action == TVE_EXPAND)
	{
		if (m_IsBeDrive == FALSE)
		{	// ����̺��̰�
			Expand(hItem, TVE_COLLAPSE);
			m_IsBeDrive = TRUE;
		}
	}
	m_IsBeDrive = TRUE;

	*pResult = 0;
}

///////////////////////////////////////////////////////
// ���� �ڵ��� Path�� ���Ѵ�
CString CFileTreeCtrl::GetPathFromNode(HTREEITEM hItem)
{
	CString strResult = GetItemText(hItem);

	HTREEITEM hParent;
	// ��Ʈ ��带 ���� �� ���� ����...
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
// ù��° ��带 �����(���� ��� ������ �� ���)
void CFileTreeCtrl::DeleteFirstChild(HTREEITEM hParent)
{
	HTREEITEM hItem;
	if(( hItem = GetChildItem(hParent)) != NULL)
		DeleteItem(hItem);
}

////////////////////////////////////////////////
// ��� �ڽ� ��带 �����Ѵ�
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
// ���丮�� �Է����� ���� ��忡 �߰��Ѵ�
int CFileTreeCtrl::AddDir(HTREEITEM hItem, CString &strPath)
{
	CString strFindPath;
	HTREEITEM hNewItem;
	int nCount = 0;

	// ������ ���丮 �ڿ� "\\*.*"�� ������
	strFindPath = strPath;
	if(strFindPath.Right(1) != "\\")
		strFindPath += "\\";
	strFindPath += "*.*";

	CString strFileName, strNewPath;
	CFileFind filefind;

	// Ž���� ���丮 ����
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
	// ���丮 Ž��
	while(bContinue)
	{
		bContinue = filefind.FindNextFile();
		// ���丮�� ���...
		if(filefind.IsDirectory())
		{
			strFileName = filefind.GetFileName();
			if(strFileName != "." && strFileName != "..")
			{	// ����߰�
				hNewItem = InsertItem((LPCTSTR)strFileName, ID_CLOSEDFOLDER, ID_OPENFOLDER, hItem);

				strNewPath = strPath;
				if(strNewPath.Right(1) != "\\")
					strNewPath += "\\";

				// �߰��� ��尡 ������丮�� �������� Ȯ��
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
// Path�� �Է� �޾� �ش� ��θ� �����ش�
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
// ��θ� �Է� �޾� ù��° ȭ�� �̸��� ��ȯ �Ѵ�
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
