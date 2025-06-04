#ifndef _RECIPE_DEFINE_H_
#define _RECIPE_DEFINE_H_

#pragma once

#include <atlstr.h>

//#include "../define.h"
#include "../RUN_MODULE/RunningDefine.h"



typedef struct DEF_RECIPE_PATH_DISP
{

#define DEF_RECIPE_PATH_DISP_COUNT 3

	TCHAR* RECIPE_PATH_DISP_NAME[DEF_RECIPE_PATH_DISP_COUNT];

	DEF_RECIPE_PATH_DISP(void)
	{
		Clear();
	}

	void Clear()
	{
		RECIPE_PATH_DISP_NAME[0] = _T("Equiment Log Path");
		RECIPE_PATH_DISP_NAME[1] = _T("System Log Path");
		RECIPE_PATH_DISP_NAME[2] = _T("MES Log Path");
	}

}RECIPE_PATH_DISP;



//////////////////////////////////////////////////////////////////////////

//Init Spread Sheet
#define RECIPE_TITLE_SUB_TITLE	2


#define RECIPE_BODY_MAX_COLS			5
#define RECIPE_BODY_MAX_ROWS			5
#define RECIPE_BODY_ACTUAL_ROW			1
#define RECIPE_BODY_MAX_ITEM	RECIPE_BODY_MAX_ROWS - 2

#define RECIPE_MERGE_COLS_CNT  4

#define RECIPE_MAP_LASER_COLS_CNT  3


class CRecipeDisp
{

	public:
		void InitSpreadSheet(CFpspread8* a_pSpread ,CString a_strTitle, int a_nRow, TCHAR* a_aszItem[], TCHAR* a_szUnit[], TCHAR* a_szExplanation[])
		{
			a_pSpread->SetReDraw(FALSE);	

	
			a_pSpread->SetFontBold(DISPID_FONT_BOLD);

			a_pSpread->SetMaxRows(a_nRow + RECIPE_TITLE_SUB_TITLE); //열 셋팅
			a_pSpread->SetMaxCols(RECIPE_BODY_MAX_COLS );			 //행 셋팅


			a_pSpread->AddCellSpan(	1						, //Col 시작위치.
									1						, //Row 시작위치
									RECIPE_BODY_MAX_COLS	, //Col 합병 셀수
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
			a_pSpread->SetFontSize(15);
			a_pSpread->SetText(_T("NO"));
			a_pSpread->SetBackColor(clSubTitle);
			a_pSpread->SetForeColor(clWhite);
			a_pSpread->SetTypeHAlign(2);
	
			//item name
			a_pSpread->SetCol(2);
			a_pSpread->SetRow(2);
			a_pSpread->SetFontSize(15);
			a_pSpread->SetText(_T("ITEM NAME"));
			a_pSpread->SetBackColor(clSubTitle);
			a_pSpread->SetForeColor(clWhite);
			a_pSpread->SetTypeHAlign(2);

			//item name
			a_pSpread->SetCol(3);
			a_pSpread->SetRow(2);
			a_pSpread->SetFontSize(15);
			a_pSpread->SetText(_T("UNIT"));
			a_pSpread->SetBackColor(clSubTitle);
			a_pSpread->SetForeColor(clWhite);
			a_pSpread->SetTypeHAlign(2);

			//value
			a_pSpread->SetCol(4);
			a_pSpread->SetRow(2);
			a_pSpread->SetFontSize(15);
			a_pSpread->SetText(_T("VALUE"));
			a_pSpread->SetBackColor(clSubTitle);
			a_pSpread->SetForeColor(clWhite);

			//Explanation
			a_pSpread->SetCol(5);
			a_pSpread->SetRow(2);
			a_pSpread->SetFontSize(15);
			a_pSpread->SetText(_T("EXPLANATION"));
			a_pSpread->SetBackColor(clHighlight);
			a_pSpread->SetForeColor(clWhite);
			a_pSpread->SetTypeHAlign(2);

 
			int i,j;
			int nColWidth, nColValueWidth;
			int nColItemWidth;
			int nUnitColWidth;
			int nExplanationWidth;

			int nRowHeight;
			int nRowTitleHeight;

			for(i = 3; i<= a_nRow + RECIPE_TITLE_SUB_TITLE; i++)
			{
				for(j = 1; j <= RECIPE_BODY_MAX_COLS; j++)
				{
					if( !(i % 2))
					{
						a_pSpread->SetCol(j);
						a_pSpread->SetRow(i);
						a_pSpread->SetBackColor(clSilver);
					}

				}
			}
			nColWidth			= 60;
			nColValueWidth		= 20;
			nColItemWidth		= 5;
			nUnitColWidth		= 14;
			nExplanationWidth	= 80;

			nRowHeight			= 20;
			nRowTitleHeight		= 25;


			for(i = 1; i <= a_nRow + RECIPE_TITLE_SUB_TITLE; i++)
			{
				if( i == 1)
					a_pSpread->SetRowHeight(i,nRowTitleHeight);
				else
					a_pSpread->SetRowHeight(i,nRowHeight);
			}

			for(i = 1; i <= RECIPE_BODY_MAX_COLS; i++)
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
					a_pSpread->SetColWidth(i,nExplanationWidth);

			}

			CString strNumber = TEXT("");
	

			for(i = 0; i <= RECIPE_BODY_MAX_COLS ;i++)
			{
		
				for(j = 0; j < a_nRow; j++)
				{
					if(j > RECIPE_TITLE_SUB_TITLE)
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
						//if(j < a_nRow) break;

						a_pSpread->SetCol(i+1);
						a_pSpread->SetRow(j+3);
						a_pSpread->SetText(a_aszItem[j]);
						a_pSpread->SetTypeHAlign(0);
					}

					else if(i == 2)
					{
						//if(j < a_nRow) break;

						a_pSpread->SetCol(i+1);
						a_pSpread->SetRow(j+3);
						a_pSpread->SetText(a_szUnit[j]);
						a_pSpread->SetTypeHAlign(0);
					}

					else if(i == 5)
					{
						//if(j < a_nRow) break;

						a_pSpread->SetCol(i+1);
						a_pSpread->SetRow(j+3);
						//a_pSpread->SetBackColor(clLinen);
						a_pSpread->SetForeColor(clDarkBlue);
						a_pSpread->SetText(a_szExplanation[j]);
						a_pSpread->SetTypeHAlign(0);
						a_pSpread->SetTypeVAlign(2);
					}

				}
			
			}

			a_pSpread->SetReDraw(TRUE);
		}

};

#endif