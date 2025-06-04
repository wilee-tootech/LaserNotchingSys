#ifndef _SETUP_DEFINE_H_
#define _SETUP_DEFINE_H_

#pragma once

#include <cstringt.h>
#include <atlstr.h>
#include <afxctl.h>

#include "../Include/EXTERN/picture.h"
#include "../Include/EXTERN/fpspread8.h"
//#include "../RUN_MODULE/RunningDefine.h"
#include "../BeamEditor6.h"

//Image
//{{

// #ifdef _DEBUG
// #define IMG_SETUP_BODY_IMG_PATH			_T("Debug\\Image\\Body.bmp")
// #define IMG_SETUP_FEEDER_IMG_PATH		_T("Debug\\Image\\Feeder.bmp")
// #define IMG_SETUP_BACKGROUND_PATH		_T("Debug\\Image\\BackGround.bmp")
// #else 
// #define IMG_SETUP_BODY_IMG_PATH			_T("Release\\Image\\Body.bmp")
// #define IMG_SETUP_FEEDER_IMG_PATH		_T("Release\\Image\\Feeder.bmp")
// #define IMG_SETUP_BACKGROUND_PATH		_T("Release\\Image\\BackGround.bmp")
// #endif

//}}

//선언
//void InitSpreadSheet(CSpreadSheet* a_pSpread ,CString a_strTitle, int a_nRow, TCHAR* a_aszItem[], TCHAR* a_szUnit[]);

//Init Spread Sheet
#define SETUP_TITLE_SUB_TITLE	2


#define SETUP_BODY_MAX_COLS			5
#define SETUP_BODY_MAX_ROWS			5
#define SETUP_BODY_ACTUAL_ROW		1
#define SETUP_BODY_MAX_ITEM	SETUP_BODY_MAX_ROWS - 2

#define SETUP_MERGE_COLS_CNT  5

class CSetupDisp 
{

public:
	
	void InitSpreadSheet(CFpspread8* a_pSpread ,CString a_strTitle, int a_nRow, TCHAR* a_aszItem[], TCHAR* a_szUnit[])
	{
		a_pSpread->SetReDraw(FALSE);	

	
		a_pSpread->SetFontBold(DISPID_FONT_BOLD);

		a_pSpread->SetMaxRows(a_nRow + SETUP_TITLE_SUB_TITLE + SETUP_BODY_ACTUAL_ROW  ); //열 셋팅
		a_pSpread->SetMaxCols(SETUP_BODY_MAX_COLS );									 //행 셋팅


		a_pSpread->AddCellSpan(	1						, //Col 시작위치.
								1						, //Row 시작위치
								SETUP_MERGE_COLS_CNT	, //Col 합병 셀수
								1);						  //Row 합병 셀수


		a_pSpread->SetGridColor(clBlack);
		a_pSpread->SetBackColorStyle(1);
		//Speed Setting
		a_pSpread->SetCol(1);
		a_pSpread->SetRow(1);
		a_pSpread->SetFontSize(18);
		a_pSpread->SetText(a_strTitle);
		a_pSpread->SetBackColor(RGB(39, 46, 54));
		a_pSpread->SetForeColor(clWhite);
		a_pSpread->SetTypeHAlign(2);
		/*
		0 - Left
		1 - Right
		2 - Center
		*/
		//No.
		a_pSpread->SetCol(1);
		a_pSpread->SetRow(2);
		a_pSpread->SetFontSize(10);
		a_pSpread->SetText(_T("NO"));
		a_pSpread->SetBackColor(clSubTitle);
		a_pSpread->SetForeColor(clWhite);
		a_pSpread->SetTypeHAlign(2);
	
		//item name
		a_pSpread->SetCol(2);
		a_pSpread->SetRow(2);
		a_pSpread->SetFontSize(10);
		a_pSpread->SetText(_T("ITEM NAME"));
		a_pSpread->SetBackColor(clSubTitle);
		a_pSpread->SetForeColor(clWhite);
		a_pSpread->SetTypeHAlign(2);

		//item name
		a_pSpread->SetCol(3);
		a_pSpread->SetRow(2);
		a_pSpread->SetFontSize(10);
		a_pSpread->SetText(_T("UNIT"));
		a_pSpread->SetBackColor(clSubTitle);
		a_pSpread->SetForeColor(clWhite);
		a_pSpread->SetTypeHAlign(2);

		//value
		a_pSpread->SetCol(4);
		a_pSpread->SetRow(2);
		a_pSpread->SetFontSize(10);
		a_pSpread->SetText(_T("VALUE"));
		a_pSpread->SetBackColor(clSubTitle);
		a_pSpread->SetForeColor(clWhite);

		//SET
		a_pSpread->SetCol(5);
		a_pSpread->SetRow(2);
		a_pSpread->SetText(_T("SET"));
		a_pSpread->SetBackColor(clTitle);
		a_pSpread->SetForeColor(clWhite);
		a_pSpread->SetTypeHAlign(2);

 
		int i,j;
		int nColWidth, nColValueWidth;
		int nColItemWidth;
		int nUnitColWidth;
		int nColSetWidth;

		int nRowHeight;
		int nRowTitleHeight;

		for(i = 3; i<= a_nRow + SETUP_TITLE_SUB_TITLE + SETUP_BODY_ACTUAL_ROW; i++)
		{
			for(j = 1; j <= SETUP_BODY_MAX_COLS; j++)
			{
				if( !(i % 2))
				{
					a_pSpread->SetCol(j);
					a_pSpread->SetRow(i);
					a_pSpread->SetBackColor(clSilver);
				}

			}
		}
		nColWidth		= 38;
		nColValueWidth	= 20;
		nColItemWidth   = 5;
		nUnitColWidth	= 14;
		nColSetWidth	= 8;

		nRowHeight		= 20;
		nRowTitleHeight = 25;

		CPictureHolder picture, picture2;
		HBITMAP hBitmap = (HBITMAP)LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_UPLOAD));
		HBITMAP hBitmap2 = (HBITMAP)LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_UPLOAD2));

		picture.CreateFromBitmap(hBitmap);
		picture2.CreateFromBitmap(hBitmap2);


		for(i = 1; i <= a_nRow + SETUP_TITLE_SUB_TITLE + SETUP_BODY_ACTUAL_ROW; i++)
		{
			if( i == 1)
				a_pSpread->SetRowHeight(i,nRowTitleHeight);
			else
				a_pSpread->SetRowHeight(i,nRowHeight);


			if(i >= 4)
			{
				// Specify a cell
				a_pSpread->SetCol(5);
				a_pSpread->SetRow(i);

				a_pSpread->SetCellType(9);


				if((i) % 2)
					a_pSpread->SetTypePictPicture(picture.GetPictureDispatch());
				else
					a_pSpread->SetTypePictPicture(picture2.GetPictureDispatch());

				// Center the picture 
				a_pSpread->SetTypePictCenter(TRUE);


			}
		}

		for(i = 1; i <= SETUP_BODY_MAX_COLS; i++)
		{

			if( i == 1)
				a_pSpread->SetColWidth(i,nColItemWidth);
			else if( i == 2 )
				a_pSpread->SetColWidth(i,nColWidth);
			else if( i == 3 )
				a_pSpread->SetColWidth(i,nUnitColWidth);
			else if( i == 4 )
				a_pSpread->SetColWidth(i,nColValueWidth);
			else if( i == 5 )
				a_pSpread->SetColWidth(i,nColSetWidth);

		}

		CString strNumber = TEXT("");
	

		for(i = 0; i < SETUP_BODY_MAX_COLS ;i++)
		{
		
			for(j = 0; j < a_nRow + SETUP_BODY_ACTUAL_ROW; j++)
			{
				a_pSpread->SetFontSize(10);

				//NO
				if(i == 0)
				{
					a_pSpread->SetCol(i+1);
					a_pSpread->SetRow(j+3);
					strNumber.Format(_T("%02d"),j+1);
					a_pSpread->SetText(strNumber);
					a_pSpread->SetTypeHAlign(2);
				}
				else if(i == 1)
				{
					if(j < a_nRow) break;

					a_pSpread->SetCol(i+1);
					a_pSpread->SetRow(j+3);
					a_pSpread->SetText(a_aszItem[j]);
					a_pSpread->SetTypeHAlign(0);
				}

				else if(i == 2)
				{
					if(j < a_nRow) break;

					a_pSpread->SetCol(i+1);
					a_pSpread->SetRow(j+3);
					a_pSpread->SetText(a_szUnit[j]);
					a_pSpread->SetTypeHAlign(0);
				}

			}

			
		}

		a_pSpread->SetReDraw(TRUE);
	}

};


#endif