// ExportImageForm.cpp : implementation file
//

#include "stdafx.h"
#include "MK.h"
#include "ExportImageForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ExportImageForm dialog




//-----------------------------------------------------------------------------------------
void ExportImageForm::SetupTALDialog(CTALBarCd * pTALBarCodeOCX)
{
	if (pTALBarCodeOCX == NULL) return;
	
	m_pTALBarCodeOCX = pTALBarCodeOCX;
}
//-----------------------------------------------------------------------------------------
// Initialize the Image Export Dialog
//-----------------------------------------------------------------------------------------
BOOL ExportImageForm::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 2003.05.01   ¼ø¼­ ¹Ù²Þ
	m_ExportFileNameCombo.AddString("C:\\TEST.BMP");
	m_ExportFileNameCombo.AddString("C:\\TEST.WMF");
	m_ExportFileNameCombo.AddString("C:\\TEST.PNG");
	m_ExportFileNameCombo.AddString("C:\\TEST.GIF");
	m_ExportFileNameCombo.AddString("C:\\TEST.JPG");
	m_ExportFileNameCombo.AddString("C:\\TEST.TIF");
	m_ExportFileNameCombo.AddString("C:\\TEST.EPS");
	m_ExportFileNameCombo.AddString("C:\\TEST.PCX");
	m_ExportFileNameCombo.AddString("C:\\TEST.TGA");	
	m_ExportFileNameCombo.SetCurSel(0);

	m_BitsPerPixelCombo.AddString("24");
	m_BitsPerPixelCombo.AddString("8");
	m_BitsPerPixelCombo.AddString("1");
	m_BitsPerPixelCombo.SetCurSel(0);

	m_PNGFilterCombo.AddString("0 - PNGALLFILTERS (Best)");
	m_PNGFilterCombo.AddString("2 - PNGNOFILTER");
	m_PNGFilterCombo.AddString("4 - PNGSUBFILTER");
	m_PNGFilterCombo.AddString("6 - PNGUPFILTER");
	m_PNGFilterCombo.AddString("8 - PNGAVGFILTER");
	m_PNGFilterCombo.AddString("10 - PNGPAETHFILTER");
	m_PNGFilterCombo.SetCurSel(0);

	m_TIFFCompressionCombo.AddString("0 - None");
	m_TIFFCompressionCombo.AddString("1 - LZW");
	m_TIFFCompressionCombo.AddString("2 - PackBits");
	m_TIFFCompressionCombo.AddString("3 - Group3");
	m_TIFFCompressionCombo.AddString("4 - Group4");
	m_TIFFCompressionCombo.SetCurSel(0);

	m_JPEGQualityEdit.SetWindowText("100");
	m_PixelsPerInchEdit.SetWindowText("300");


	// Now Change Values to the BarCode if Present.
	if (m_pTALBarCodeOCX)
	{
		char TempBuffer[64];

		memset(TempBuffer,0,sizeof(TempBuffer));

		itoa(m_pTALBarCodeOCX->GetJPEGQuality(),TempBuffer,10);

		m_JPEGQualityEdit.SetWindowText(TempBuffer);

		memset(TempBuffer,0,sizeof(TempBuffer));

		itoa(m_pTALBarCodeOCX->GetRasterImageResolution(),TempBuffer,10);

		m_PixelsPerInchEdit.SetWindowText(TempBuffer);
		
		m_TIFFCompressionCombo.SetCurSel(m_pTALBarCodeOCX->GetTIFFCompression());

		switch (m_pTALBarCodeOCX->GetPNGFilter())
		{
		case 0:
			{
				m_PNGFilterCombo.SetCurSel(0);
			}
			break;
		case 2:
			{
				m_PNGFilterCombo.SetCurSel(1);
			}
			break;
		case 4:
			{
				m_PNGFilterCombo.SetCurSel(2);
			}
			break;
		case 6:
			{
				m_PNGFilterCombo.SetCurSel(3);
			}
			break;
		case 8:
			{
				m_PNGFilterCombo.SetCurSel(4);
			}
			break;
		case 10:
			{
				m_PNGFilterCombo.SetCurSel(5);
			}
			break;
		}


		switch (m_pTALBarCodeOCX->GetBitsPerPixel())
		{
		case 1:
			{
				m_BitsPerPixelCombo.SetCurSel(0);
			}
			break;
		case 4:
		case 8:
			{
				m_BitsPerPixelCombo.SetCurSel(1);
			}
			break;
		case 16:
		case 24:
		case 32:
		default:
			{
				m_BitsPerPixelCombo.SetCurSel(2);
			}
			break;
		}

		if (m_pTALBarCodeOCX->GetPNGInterlace() == FALSE)
		{
			m_PNGBtn.SetCheck(FALSE);
		}
		else
		{
			m_PNGBtn.SetCheck(TRUE);
		}

		if (m_pTALBarCodeOCX->GetGIFCompression() == FALSE)
		{
			m_GIFBtn.SetCheck(FALSE);
		}
		else
		{
			m_GIFBtn.SetCheck(TRUE);
		}


		if (m_pTALBarCodeOCX->GetBMPCompression() == FALSE)
		{
			m_BMPBtn.SetCheck(FALSE);
		}
		else
		{
			m_BMPBtn.SetCheck(TRUE);
		}

		if (m_pTALBarCodeOCX->GetTGACompression() == FALSE)
		{
			m_TGABtn.SetCheck(FALSE);
		}
		else
		{
			m_TGABtn.SetCheck(TRUE);
		}

		// 2003.05.01  
		m_pTALBarCodeOCX->SetBitsPerPixel(24);
	}

	return(TRUE);
}


//-----------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------
ExportImageForm::ExportImageForm(CWnd* pParent /*=NULL*/)
	: CDialog(ExportImageForm::IDD, pParent)
{
	m_pTALBarCodeOCX = NULL;
	
	EnableAutomation();

	//{{AFX_DATA_INIT(ExportImageForm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ExportImageForm::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void ExportImageForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ExportImageForm)
	DDX_Control(pDX, IDCANCEL2, m_CloseBtn);
	DDX_Control(pDX, IDC_TIFFCOMPRESSIONCOMBO, m_TIFFCompressionCombo);
	DDX_Control(pDX, IDC_PNGFILTERCOMBO, m_PNGFilterCombo);
	DDX_Control(pDX, IDC_BITSPERPIXELCOMBO, m_BitsPerPixelCombo);
	DDX_Control(pDX, IDC_LZWEDIT, m_LZWEdit);
	DDX_Control(pDX, IDC_JPEGQUALITYEDIT, m_JPEGQualityEdit);
	DDX_Control(pDX, IDC_PIXELSPERINCHEDIT, m_PixelsPerInchEdit);
	DDX_Control(pDX, IDC_PNGCHECK, m_PNGBtn);
	DDX_Control(pDX, IDC_GIFCHECK, m_GIFBtn);
	DDX_Control(pDX, IDC_TGACHECK, m_TGABtn);
	DDX_Control(pDX, IDC_EXPORTFILENAMECOMBO, m_ExportFileNameCombo);
	DDX_Control(pDX, IDC_BMPCHECK, m_BMPBtn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ExportImageForm, CDialog)
	//{{AFX_MSG_MAP(ExportImageForm)
	ON_BN_CLICKED(IDC_BMPCHECK, OnBmpcheck)
	ON_BN_CLICKED(IDC_SAVEBARCODE, OnSavebarcode)
	ON_BN_CLICKED(IDC_TGACHECK, OnTgacheck)
	ON_BN_CLICKED(IDC_GIFCHECK, OnGifcheck)
	ON_BN_CLICKED(IDC_PNGCHECK, OnPngcheck)
	ON_EN_CHANGE(IDC_PIXELSPERINCHEDIT, OnChangePixelsperinchedit)
	ON_EN_CHANGE(IDC_JPEGQUALITYEDIT, OnChangeJpegqualityedit)
	ON_EN_CHANGE(IDC_LZWEDIT, OnChangeLzwedit)
	ON_CBN_SELCHANGE(IDC_BITSPERPIXELCOMBO, OnSelchangeBitsperpixelcombo)
	ON_BN_CLICKED(IDCANCEL2, OnCancel2)
	ON_CBN_SELCHANGE(IDC_PNGFILTERCOMBO, OnSelchangePngfiltercombo)
	ON_CBN_SELCHANGE(IDC_TIFFCOMPRESSIONCOMBO, OnSelchangeTiffcompressioncombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(ExportImageForm, CDialog)
	//{{AFX_DISPATCH_MAP(ExportImageForm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IExportImageForm to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {8EA7C183-B8E4-11D4-85DD-E0C947C10000}
static const IID IID_IExportImageForm =
{ 0x8ea7c183, 0xb8e4, 0x11d4, { 0x85, 0xdd, 0xe0, 0xc9, 0x47, 0xc1, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(ExportImageForm, CDialog)
	INTERFACE_PART(ExportImageForm, IID_IExportImageForm, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ExportImageForm message handlers

// -----------------------------------------------------------------------------------------
// BMP Compression Box
// -----------------------------------------------------------------------------------------
void ExportImageForm::OnBmpcheck() 
{
	if (m_BMPBtn.GetCheck())
	{
		if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetBMPCompression(TRUE);
	}
	else
	{
		if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetBMPCompression(FALSE);
	}
}
// -----------------------------------------------------------------------------------------
// Save the Bar Code to Disk
// -----------------------------------------------------------------------------------------
void ExportImageForm::OnSavebarcode() 
{
	CString FileName;

	m_ExportFileNameCombo.GetWindowText(FileName);
	
	if (m_pTALBarCodeOCX)
	{
		
		m_pTALBarCodeOCX->SaveBarCode(LPCTSTR(FileName));
	}
	// 2003.05.01  
	EndDialog(IDCLOSE);
}
// -----------------------------------------------------------------------------------------
// TGA Compression Box
// -----------------------------------------------------------------------------------------
void ExportImageForm::OnTgacheck() 
{
	if (m_TGABtn.GetCheck())
	{
		if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetTGACompression(TRUE);
	}
	else
	{
		if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetTGACompression(FALSE);
	}
}
// -----------------------------------------------------------------------------------------
// Handle GIF Compression Box
// -----------------------------------------------------------------------------------------

void ExportImageForm::OnGifcheck() 
{
	if (m_GIFBtn.GetCheck())
	{
		if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetGIFCompression(TRUE);
	}
	else
	{
		if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetGIFCompression(FALSE);
	}
}
// -----------------------------------------------------------------------------------------
// Handle PNG Check
// -----------------------------------------------------------------------------------------
void ExportImageForm::OnPngcheck() 
{
	if (m_PNGBtn.GetCheck())
	{
		if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetPNGInterlace(TRUE);
	}
	else
	{
		if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetPNGInterlace(FALSE);
	}
}
// -----------------------------------------------------------------------------------------
// Handle Pixels Per Inch Edit
// -----------------------------------------------------------------------------------------

void ExportImageForm::OnChangePixelsperinchedit() 
{
	// DO NOTHING.	
	TRACE("OnChangePixelsPerInchEdit \n");
	
	long DPI = 0;

	char TempBuffer[264];

	memset(TempBuffer,0,sizeof(TempBuffer));
	
	// Change the Bar Code's Message Edit Field
	m_PixelsPerInchEdit.GetWindowText(TempBuffer,sizeof(TempBuffer)-1);

	DPI = atoi(TempBuffer);
	if (DPI < 20)
	{
		DPI = 300;

		itoa(DPI,TempBuffer,10);

		m_PixelsPerInchEdit.SetWindowText(TempBuffer);
	}
	else if (DPI > 2540)
	{
		DPI = 2540;

		itoa(DPI,TempBuffer,10);

		m_PixelsPerInchEdit.SetWindowText(TempBuffer);
	}

	if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetRasterImageResolution(DPI);
}
// -----------------------------------------------------------------------------------------
// Handle JPEG Quality
// -----------------------------------------------------------------------------------------
void ExportImageForm::OnChangeJpegqualityedit() 
{
	// DO NOTHING.	
	TRACE("OnChangeJpegQualityEdit \n");
	
	long JPEGQuality = 0;

	char TempBuffer[264];

	memset(TempBuffer,0,sizeof(TempBuffer));
	
	// Change the Bar Code's Message Edit Field
	m_JPEGQualityEdit.GetWindowText(TempBuffer,sizeof(TempBuffer)-1);

	JPEGQuality = atoi(TempBuffer);
	if ((JPEGQuality <= 0) || (JPEGQuality > 100))
	{
		JPEGQuality = 100;

		itoa(JPEGQuality,TempBuffer,10);

		m_JPEGQualityEdit.SetWindowText(TempBuffer);
	}

	if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetJPEGQuality(JPEGQuality);
}
// -----------------------------------------------------------------------------------------
// Handle LZW Key
// -----------------------------------------------------------------------------------------
void ExportImageForm::OnChangeLzwedit() 
{
	// DO NOTHING.	
	TRACE("OnChangeLZWEdit \n");

	long LZWkey = 0;
	
	char TempBuffer[264];

	memset(TempBuffer,0,sizeof(TempBuffer));
	
	// Change the Bar Code's Message Edit Field
	m_LZWEdit.GetWindowText(TempBuffer,sizeof(TempBuffer)-1);

	if (strlen(TempBuffer))
	{
		LZWkey = atoi(TempBuffer);

		if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetLZWUnlockKey(LZWkey);
	}
}
// -----------------------------------------------------------------------------------------
// Handle Bits Per Pixel Dialog
// -----------------------------------------------------------------------------------------

void ExportImageForm::OnSelchangeBitsperpixelcombo() 
{
	switch(m_BitsPerPixelCombo.GetCurSel())
	{
	case 0: // 1
		{
			if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetBitsPerPixel(1);
		}
		break;
	case 1: // 8
		{
			if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetBitsPerPixel(8);
		}
		break;
	case 2: // 24
		{
			if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetBitsPerPixel(24);
		}
		break;
	}

}
//-----------------------------------------------------------------------------------------
// Close the Dialog
//-----------------------------------------------------------------------------------------
void ExportImageForm::OnCancel2() 
{
	EndDialog(IDCLOSE);
}

//-----------------------------------------------------------------------------------------
// Handle PNG Filter Combo Box
//-----------------------------------------------------------------------------------------
void ExportImageForm::OnSelchangePngfiltercombo() 
{
	
	switch(m_PNGFilterCombo.GetCurSel())
	{
	case 0:
		{
			if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetPNGFilter(0);
		}
		break;
	case 1:
		{
			if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetPNGFilter(2);
		}
		break;
	case 2:
		{
			if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetPNGFilter(4);
		}
		break;

	case 3:
		{
			if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetPNGFilter(6);
		}
		break;
	case 4:
		{
			if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetPNGFilter(8);
		}
		break;
	case 5:
		{
			if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetPNGFilter(10);
		}
		break;
	}
	
}
//-----------------------------------------------------------------------------------------
// Handle TIFF Compression Combo Box
//-----------------------------------------------------------------------------------------
void ExportImageForm::OnSelchangeTiffcompressioncombo() 
{
	switch(m_TIFFCompressionCombo.GetCurSel())
	{
	case 0:
		{
			if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetTIFFCompression(0);
		}
		break;
	case 1:
		{
			if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetTIFFCompression(1);
		}
		break;
	case 2:
		{
			if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetTIFFCompression(2);
		}
		break;

	case 3:
		{
			if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetTIFFCompression(3);
		}
		break;
	case 4:
		{
			if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetTIFFCompression(4);
		}
		break;
	case 5:
		{
			if (m_pTALBarCodeOCX) m_pTALBarCodeOCX->SetTIFFCompression(5);
		}
		break;
	}
}
