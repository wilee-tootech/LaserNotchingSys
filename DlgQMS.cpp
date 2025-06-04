// DlgQMS.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgQMS.h"
#include "afxdialogex.h"
#include "WriteLog.h"
#include "MainFrm.h"
#include "Defines.h"
#include "./Include/EXTERN/CColorDefine.h"

// CDlgQMS 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgQMS, CDialogEx)

CDlgQMS::CDlgQMS(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgQMS::IDD, pParent)
{
	CDlgQMS::SetQMS(this);
}

void CDlgQMS::SetQMS(CDlgQMS *pDlgQMS)
{
	m_pDlgQMS = pDlgQMS;
}

CDlgQMS::~CDlgQMS()
{
}

void CDlgQMS::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FPSPREAD_QMS, m_SpreadQms);
}


BEGIN_MESSAGE_MAP(CDlgQMS, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgQMS::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgQMS::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgQMS 메시지 처리기입니다.
void CDlgQMS::GetTitle(CString tmpPath)
{
}

// 우상단에 제목 가지고와서 체크하기
void CDlgQMS::OnBnClickedOk()
{


	// CDialogEx::OnOK();
}


void CDlgQMS::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
BEGIN_EVENTSINK_MAP(CDlgQMS, CDialogEx)
	ON_EVENT(CDlgQMS, IDOK, DISPID_CLICK, CDlgQMS::ClickOk, VTS_NONE)
	ON_EVENT(CDlgQMS, IDCANCEL, DISPID_CLICK, CDlgQMS::ClickCancel, VTS_NONE)
END_EVENTSINK_MAP()

void CDlgQMS::TitleChange(CString title)
{
	strTitle = title;
}

void CDlgQMS::ClickOk()
{
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp();
	FILE *pFile;
	CString strFilePath = pApp->m_strCwd + "\\EqTitle.ini";
	pFile = fopen(strFilePath, "rt");

	CString tmpTitle;
	if (pFile)
	{
		if (fscanf(pFile, "%s", tmpTitle) != 1)
		{
			TRACE("Error reading data from EqTitle.ini file!");
		}
		fclose(pFile);
	}

	CFileDoc fd;
	CString strPath;
	CString strData;
	strPath = fd.GetCurrentDirectoryA();
	CString folderPath = _T(strPath + "\\MES\\PARAM\\");

	strFilePath.Format(_T("%s%s"), folderPath, strTitle); // 여기 이상

	SetDlgItemText(IDC_TEXT_QMS_TITLE, strTitle);

	m_SpreadQms.SetColWidth(1,3);
	m_SpreadQms.SetCol(1);
	m_SpreadQms.SetRow(0);
	m_SpreadQms.SetText(_T("NO"));

	m_SpreadQms.SetColWidth(2,10);
	m_SpreadQms.SetCol(2);
	m_SpreadQms.SetRow(0);
	m_SpreadQms.SetText(_T("Code"));
	m_SpreadQms.SetBackColor(clBlack);
	m_SpreadQms.SetForeColor(clWhite);

	m_SpreadQms.SetColWidth(3,30);
	m_SpreadQms.SetCol(3);
	m_SpreadQms.SetRow(0);
	m_SpreadQms.SetText(_T("Name"));
	m_SpreadQms.SetBackColor(clBlack);
	m_SpreadQms.SetForeColor(clWhite);

	m_SpreadQms.SetColWidth(4,10);
	m_SpreadQms.SetCol(4);
	m_SpreadQms.SetRow(0);
	m_SpreadQms.SetText(_T("Value"));
	m_SpreadQms.SetBackColor(clBlack);
	m_SpreadQms.SetForeColor(clWhite);

	CoInitialize(NULL);

	IXMLDOMDocumentPtr pXMLDoc;
	HRESULT hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument));

	if (SUCCEEDED(hr)) 
	{
		VARIANT varFilePath;
		VariantInit(&varFilePath);
		varFilePath.vt = VT_BSTR;
		varFilePath.bstrVal = strFilePath.AllocSysString();

		// isSuccessful 변수
		VARIANT_BOOL bSuccess;

		// XML 파일 로드 시도
		hr = pXMLDoc->load(varFilePath, &bSuccess);

		if (SUCCEEDED(hr) && bSuccess == VARIANT_TRUE)
		{
			// 로드 성공
			// 처리할 작업 수행
			// TRACE("\nxml파일 읽기 성공\n");

			_bstr_t bstrXPath = "//PARAM_COUNT";
			IXMLDOMNodeListPtr pNodeList;
			hr = pXMLDoc->selectNodes(bstrXPath, &pNodeList);

			if (SUCCEEDED(hr) && pNodeList != NULL) {
				long nodeListLength;
				pNodeList->get_length(&nodeListLength);

				if (nodeListLength > 0) {
					IXMLDOMNodePtr pNode;
					pNodeList->get_item(0, &pNode);  // 첫 번째 항목 가져오기

					if (pNode != NULL) {
						BSTR bstrText;
						pNode->get_text(&bstrText);  // 텍스트 내용 가져오기

						CString strName = bstrText;
						SysFreeString(bstrText);
						int nDataLeng = _ttoi(strName);

						// PARAM_DATA 노드 목록 가져오기
						bstrXPath = "//PARAM_DATA";
						hr = pXMLDoc->selectNodes(bstrXPath, &pNodeList);
						if (SUCCEEDED(hr) && pNodeList != NULL)
						{
							pNodeList->get_length(&nodeListLength);

							for (int i = 0; i < nDataLeng && i < nodeListLength; ++i) 
							{
								pNodeList->get_item(i, &pNode);

								if (pNode != NULL) 
								{
									// PARAM_NAME 가져오기
									IXMLDOMNodePtr pNameNode;
									pNode->selectSingleNode(_bstr_t("PARAM_NAME"), &pNameNode);
									BSTR bstrName;
									pNameNode->get_text(&bstrName);
									CString strName = bstrName;
									SysFreeString(bstrName);

									// PARAM_VALUE 가져오기
									IXMLDOMNodePtr pValueNode;
									pNode->selectSingleNode(_bstr_t("PARAM_VALUE"), &pValueNode);
									BSTR bstrValue;
									pValueNode->get_text(&bstrValue);
									CString strValue = bstrValue;
									SysFreeString(bstrValue);

									// 표에 기입하는 실제 코드를 여기에 작성
									CString strTemp;

									m_SpreadQms.SetCol(1);
									m_SpreadQms.SetRow(i + 1);
									strTemp.Format(_T("%d"), i+1);
									m_SpreadQms.SetText(strTemp);

									m_SpreadQms.SetCol(2);
									m_SpreadQms.SetRow(i + 1);
									strTemp.Format(_T("%d"), _ttoi(strName));
									m_SpreadQms.SetText(strTemp);

									CDlgMES mes;

									CString strTmpName = mes.getCodeNameMES(_ttoi(strName));

									m_SpreadQms.SetCol(3);
									m_SpreadQms.SetRow(i + 1);
									strTemp.Format(_T("%s"), strTmpName);
									m_SpreadQms.SetText(strTemp);

									m_SpreadQms.SetCol(4);
									m_SpreadQms.SetRow(i + 1);
									strTemp.Format(_T("%.2f"), _ttof(strValue));
									m_SpreadQms.SetText(strTemp);
								}
							}
						}
					}
				}
				VariantClear(&varFilePath);
			}
		}
	}
}


void CDlgQMS::ClickCancel()
{
	CDialogEx::OnCancel();
}

CDlgQMS* CDlgQMS::m_pDlgQMS = nullptr;
CDlgQMS* CDlgQMS::GetInstance()
{
	if(m_pDlgQMS == NULL)
	{
		m_pDlgQMS = new CDlgQMS;
	}

	return m_pDlgQMS;
}