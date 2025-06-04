#include "StdAfx.h"
#include "FontLoader.h"
//#include "MKObject.h"
#include "Return.h"
#include <MATH.H>
#include "MathUtil.h"
#include "FieldParameter.h"
#include "TransUnit.h"
#include "InitialTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define PER_FIELD_VALUE 356.65289928789420142

//  : 11.08작성시작
//       11.13끝. 디버깅완료.


CFontLoader::CFontLoader()
{
	m_pVector = NULL;
	m_pFontData = NULL;
	m_bEqualSpan = FALSE;
	m_bArcArray = FALSE;
	m_FontName = _T("");
	
	m_pVectorRel = NULL;
	m_pVectorAbs = NULL;
	m_pVectorTmp = NULL;

	m_dAngle = 0.0;
}

CFontLoader::~CFontLoader()
{
	if( m_pFontData )
	{
		delete [] m_pFontData;
		m_pFontData = NULL;
	}
	if( m_pVector )
	{
		delete [] m_pVector;
		m_pVector = NULL;
	}
	if( m_pVectorAbs )
	{
		delete m_pVectorAbs;
		m_pVectorAbs = NULL;
	}
	if( m_pVectorRel )
	{
		delete m_pVectorRel;
		m_pVectorRel = NULL;
	}
	if( m_pVectorTmp )
	{
		delete m_pVectorTmp;
		m_pVectorTmp = NULL;
	}
}


/*void Save(Vector *Data, DWORD dwLength)
{
	CFile file;
	file.Open("dumpfnt.txt",CFile::modeCreate |CFile::modeWrite);
	file.WriteHuge(Data, dwLength *sizeof(Vector) );
	file.Close();
}*/  // 디버깅용...


DWORD CFontLoader::LoadString(CString strData)
{
	int iStrLength, iStartPos,tmpLineCnt,iOrValue=0;
	double xMaxT,xMinT,xMax,yMaxT,yMinT,xMin,yMax,yMin, iCharHeight, iCharWidth;
	double xMaxF,xMinF,yMaxF,yMinF;
	int iLineCount=0 , k, iLineMulti=0, m_ibeforePosition=0;
	int iMinValue = 0;
	int beforePoint = 0;
	int itmpLine = 0;
	int m_lineIndex = 0;

	CMathUtil mathUtil;
	DWORD dwStorePos=0, dwCharSize, dwVecSize;
	CPoint ptEndPoint;
	long lDistance = 0;
	tmpLineCnt=0;
	iStartPos=0;
	iStrLength = strData.GetLength();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	
	
	
	// 문자 전체에 대한 
	GetMinMaxinFont(xMinF,xMaxF,yMinF,yMaxF);
	iCharWidth = xMaxF - xMinF;  //폰트 전체에 대한 최대 너비
	iCharHeight = yMaxF - yMinF;   //폰트 전체에 대한 최대 높이
	
	
	xMaxT =0;xMinT = 0;yMaxT=0;yMinT=0;
	

	double addsize ;
	

	if(m_FontName == _T("OCR") || m_FontName == _T("ocr"))
		GetMinMaxinChar('O',xMin,xMax,yMin,yMax); // EO에서 'O'(대문자)를 기준으로 하기때문에
	else
		GetMinMaxinChar('W',xMin,xMax,yMin,yMax); // EO에서 'W'(대문자)를 기준으로 하기때문에
	
	yMaxT = yMax; yMinT = yMin; xMaxT=xMax;xMinT=xMin;

	
	double nWidth,nHeight;
	GetMaxWidthHeightinFont( nWidth ,  nHeight);
	ASSERT(m_pFontData!=NULL);
	if( m_pFontData == NULL){
#ifdef _DEBUG
		OutputDebugString("You Must Load Font First");
		
#endif
		return NULL;
	}
	
//	if( m_pVector != NULL ) delete [] m_pVector;
//	
//	m_pVector = CreateVectorArray(strData, dwVecSize); // 필요한 벡터 크기만큼 벡터 배열을 생성한다.
	
	int MaxstrLength,tmpLength,SpaceMinPos,tmpSpos;
	MaxstrLength=0;tmpLength=0;SpaceMinPos=100;tmpSpos=0;
	char* pBuffer = new char[iStrLength+1];
	CString strtmp,strEndData;
	strEndData=_T("");strtmp=_T("");
	int SpaceCnt=0;
	double newYMag=0;
	int iTotalline = GetTotalLine(strData);
	
	
	for(int x = 0;x<iStrLength;x++)
	{
		strtmp+=strData[x];
		if( strData[x] =='\n' || x == iStrLength-1)
		{
			
			int size = strtmp.GetLength(); 
			int k = size-1;
			strcpy(pBuffer, strtmp);
			while(1)
			{
				if((pBuffer[k] == 0x0d) || (pBuffer[k] == 0x0a) )
				{
					k--;
					continue;
				}
				if(pBuffer[k] == ' ') {
					SpaceCnt++;
				}
				else
					break;
				k--;
				
			}
			if((pBuffer[size-1] == 0x0d) || (pBuffer[size-1] == 0x0a) )
			{
				strEndData+= strtmp.Left(size - (SpaceCnt+2));
				strEndData+=(LPCTSTR)0x0d;
				strEndData+=(LPCTSTR)0x0a;
				
			}
			else
				strEndData+= strtmp.Left(size - SpaceCnt);
			
			SpaceCnt=0;
			strtmp.Empty(); 
		}
	}
	
	strData = strEndData;
	
	strcpy(pBuffer, strData);
	iStrLength = strData.GetLength();
	
	BOOL txtSflag = FALSE;
	
	for( int i = 0;  i< iStrLength; i++ ) //strData내의 모든 문자에 대해서 루프를 돈다. 
	{
		if(txtSflag == FALSE && pBuffer[i] == ' ') 
			tmpSpos++;
		else
			txtSflag = TRUE;
		
		if((pBuffer[i] != 0x0d) && (pBuffer[i] != 0x0a) )
			tmpLength++;
		
		if( strData[i] =='\n' || i == iStrLength-1) 
		{
			if(MaxstrLength > tmpLength)
				MaxstrLength = MaxstrLength;
			else
				MaxstrLength= tmpLength;
			if(SpaceMinPos > tmpSpos)
				SpaceMinPos = tmpSpos;
			else
				SpaceMinPos = SpaceMinPos;
			
			tmpSpos = 0;
			tmpLength=0;
			txtSflag = FALSE;
		}	
	}
	
	MaxstrLength-=SpaceMinPos;
	int count=0;
	
	CString strResult;
	for(int i = 0;  i< iStrLength; i++ ) 
	{
		
		if(count>=SpaceMinPos)
			strtmp+=strData[i];
		
		if( strData[i] =='\n'|| (i== iStrLength-1) )
		{
			strResult+=strtmp;
			strtmp=_T("");
			count=0; 	
			continue;
		}
		count++;
	}
	
	strData=strResult;
	strcpy(pBuffer, strData);


	if( m_pVector != NULL ) 
	{
		delete [] m_pVector;
		m_pVector = NULL;
	}
	

	m_pVector = CreateVectorArray(strData, dwVecSize); // 필요한 벡터 크기만큼 벡터 배열을 생성한다.
	delete [] pBuffer;
	
	iStrLength = strData.GetLength();
	
	for(int   i = 0;  i< iStrLength; i++ )
	{
		if( strData[i] == NULL)
			continue;
		if( strData[i] =='\n') // 개행 문자가 나오면 iOrValue의 값을 셋팅한다.
		{
			iOrValue=0x10;
			iLineCount++;
			m_lineIndex++;
			continue;
		}
		else if( strData[i] =='\r')
		{
			continue;
		}
		
		//dwCharSize = LoadCharacter(strData[i],dwStorePos,iOrValue); //문자 하나를 로딩한다 
		dwCharSize = LoadCharacter(strData.GetAt(i),dwStorePos,iOrValue); //문자 하나를 로딩한다 
		GetMinMaxinChar(strData[i],xMin,xMax,yMin,yMax);
		CString tmp = strData[i];
		if (xMax == -999999) //스페이스바인경우 따로 처리를 해준다.
		{
			yMin = 0;
			yMax = iCharHeight;
			xMin = 0;
			xMax = iCharWidth;
		}
		
		ptEndPoint.x = 0;	ptEndPoint.y = 0;
		ptEndPoint = GoThrough(dwStorePos,dwStorePos+dwCharSize-1);
		
		if( m_bEqualSpan == TRUE) // 고정 길이 폰트일때  (동간격)
		{
			//---------------Orginal----------------------------------------------------
			//동간격이 설정 되어있을때 문자의 시작 벡터와 끝 벡터 위치를 수정한다.
			//시작 위치와 끝 위치 보정
			m_pVector[dwStorePos].d.x -= xMin;     
			m_pVector[dwStorePos+dwCharSize-1].d.x= xMax  - ptEndPoint.x;
			/////////////////////////////////
			//문자의 간격을 조정 할수 있다.//
			/////////////////////////////////
			//lDistance = long ( ( xMaxT-xMinT) - (xMax - xMin ) /*+ (m_dLetterSpace )*/ );
			lDistance = long ( ( xMaxT-xMinT) - (xMax - xMin ) /*+ (m_dLetterSpace )*/ );
			m_pVector[dwStorePos].d.x += lDistance/2;
			m_pVector[dwStorePos+dwCharSize -1].d.x += lDistance/2;
			m_dwWidth = xMaxT - xMinT;
			DWORD dwVectorLength = GetVectorSize();
			double addsize = m_dCharSpace - m_dwWidth;
			double newXMag = (m_dwWidth+addsize)/m_dwWidth;
			double widthratio = m_dWidthScale;
			double xpoint,ypoint;
			xpoint =0; ypoint =0;
			if(tmpLineCnt != iLineCount)
			{
				tmpLineCnt = iLineCount;
				iStartPos=dwStorePos;
			}
			
			//---------------------------------------------------------------------------------
			GetMinMaxinChar(strData[i],xMin,xMax,yMin,yMax);
			CString tmpStr = strData[i];
			
			double tmpHeight= yMax-yMin;
			
			for(int k = (int)dwStorePos; k< (int)dwStorePos + (int)dwCharSize; k++)
			{   
//				if(strData[i] ==  '0' && m_pVector[k].t == 4)
//				   m_pVector[k].t = 1;
				if(iTotalline > 1)
				m_pVector[k].d.x = (int)(m_pVector[k].d.x* newXMag);
				else
				m_pVector[k].d.x = (m_pVector[k].d.x* newXMag);

			
			}
			m_pVector[dwStorePos+dwCharSize -1].d.x += m_dLetterSpace;
		
			
		}
		else  // 고정 길이가 아닐 때  
		{
			//------------------------Orginal---------------------------------------
			m_pVector[dwStorePos].d.x -= xMin;     
			m_pVector[dwStorePos+dwCharSize-1].d.x= xMax  - ptEndPoint.x;
			/////////////////////////////////
			//문자의 간격을 조정 할수 있다.//
			/////////////////////////////////
			
			lDistance += (int)(m_dLetterSpace ) ;
			m_dwWidth = xMaxT-xMinT;
			lDistance = long ( ( xMaxT-xMinT) - (xMax - xMin ) /*+ (m_dLetterSpace )*/ );
			DWORD dwVectorLength = GetVectorSize();
			//double addsize = (m_dCharSpace-lDistance) - m_dwWidth;
			double addsize = (m_dCharSpace) - m_dwWidth;
			double newXMag = (m_dwWidth+addsize)/m_dwWidth;
			double widthratio = m_dWidthScale;
			double xpoint,ypoint;
			xpoint =0; ypoint =0;
			double tmpHeight= yMax - yMin;
			

			for(int k = (int)dwStorePos; k< (int)dwStorePos + (int)dwCharSize; k++)
			{   
//				if(strData[i] ==  '0' && m_pVector[k].t == 4)
//				   m_pVector[k].t = 1;
				if(iTotalline > 1)
				m_pVector[k].d.x = int(m_pVector[k].d.x* newXMag);
				else
				m_pVector[k].d.x = (m_pVector[k].d.x* newXMag);
			}
			
			m_pVector[dwStorePos+dwCharSize -1].d.x += (int)m_dLetterSpace;
			
		}
		
		
		CString tmpStr = strData[i];
		//개행 문자에대한 처리를 할 차례
		if(m_pVector[dwStorePos].t & 0x10) //캐릭터의 첫번째에 개행 문자 표시가 있으면 ( 즉 현재 캐릭터 전이 개행 문자였으면)
		{
			m_pVector[dwStorePos].t &= (~0x10);
			memmove( &m_pVector[dwStorePos+iLineCount], &m_pVector[dwStorePos], sizeof(Vector)* dwCharSize ); // 개행문자를 위한 공간 마련 위해 한칸씩 뒤로 밀어낸다.
			
			GetMinMax(m_pVector,dwStorePos,xMin,xMax,yMin,yMax);
			// 다음행으로 가는 시작 벡터를 보정한다.
			for( k = 0 ; k < iLineCount ; k++)
			{
				if( (m_dCharSpace >= ( xMax - xMin )) ||(iOrValue==0x10)  )
				{
					m_pVector[dwStorePos+k].d.x = 0; // 아직 얼마나 가야하는지 모르므로 0으로 셋팅
				}
				else
				{
					m_pVector[dwStorePos+k].d.x = (( xMax - xMin) - m_dCharSpace);
				}
				
				//if(m_dLetterHeight > 0)
				//m_pVector[dwStorePos+k].d.y =  0;
				//m_pVector[dwStorePos+k].d.y =  -(m_dLineSpace);  // 설정한 높이만큼 아래로 향하는 벡터가 된다.
				//m_pVector[dwStorePos+k].d.y =  -(m_dLetterHeight+m_dLineSpace);  // 설정한 높이만큼 아래로 향하는 벡터가 된다.
					m_pVector[dwStorePos+k].d.y =  0;
				//	m_pVector[dwStorePos+k].d.y =  -(m_dLetterHeight);  // 설정한 높이만큼 아래로 향하는 벡터가 된다.
				//else
				//	m_pVector[dwStorePos+k].d.y =  (-(m_dLineSpace + m_dLetterHeight + iCharHeight/*iCharHeight */ ));  // 설정한 높이만큼 아래로 향하는 벡터가 된다.
				
				m_pVector[dwStorePos+k].t = 0x02 | 0x10;
			}
			
			GetMinMax(m_pVector,dwStorePos+dwCharSize,xMin,xMax,yMin,yMax);
			double addsize = m_dTotalHeight - (yMax-yMin);	
			double tmpHeight= yMax - yMin;
			double newYMag = ((((double)1*(double)tmpHeight)+(double)addsize)/(double)tmpHeight);
			GetMinMax(m_pVector,dwStorePos+dwCharSize,xMin,xMax,yMin,yMax);
			
			//// 여기까지 개행 문자 처리 상태는 이렇다.
			///////     ABCD
			///////	        EFGH   이런식으로 아직 앞으로 이동되진 않은 상태.
			
		}
		
		//m_ibeforePosition+= dwCharSize;
		dwStorePos += (dwCharSize + iLineCount);
		iLineCount = 0;
		iLineMulti=0;
		iOrValue =0;
	}
	
	////////////////////////////////////////////////////////////////////////////////
	// 기본 처리 과정 후에 해야할 처리들
	////////////////////////////////////////////////////////////////////////////////
	DWORD dwVectorLength = GetVectorSize();
	GetMinMax(m_pVector,dwVectorLength,xMin,xMax,yMin,yMax);
	
	CPoint point(0,0);
	
	
	//int iTotalline = GetTotalLine(strData);
	dwVectorLength = GetVectorSize();
	

	
	double yMinTmp, yMaxTmp;
	int cnt = 0;
	int m_lineCount=0;
	int m_itmp=0;


	for(cnt = 0; cnt < (int)dwVectorLength; cnt++)
	{
		
		if(m_pVector[cnt].t & 0x10 || m_lineIndex == 0)
		{
			GetMinMaxVector(m_pVector,m_itmp, dwVectorLength,xMin,xMax,yMin,yMax);
			if(yMax - yMin > yMaxT - yMinT && yMin < -15 ) //2006.03.30 정종섭 필드오차 발생때문에....
			{
				//addsize =   (m_dTotalHeight+m_dLineSpace) - (yMax-yMin);
				//newYMag = (yMax-yMin+ addsize)/(yMax - yMin)*(iTotalline+1);
				addsize =   m_dTotalHeight - (yMax-yMin);
				newYMag = (yMax-yMin+ addsize)/(yMax - yMin);
				
			}
			else if(yMax - yMin < yMaxT - yMinT )
			{
				//addsize =   (m_dLetterHeight*0.67+m_dLineSpace) - (yMax-yMin);
				//newYMag = (yMax-yMin+ addsize)/(yMax - yMin)*(iTotalline+1);
				addsize =   m_dLetterHeight*0.67 - (yMax-yMin);
				newYMag = (yMax-yMin+ addsize)/(yMax - yMin);
			}
			else
			{
				addsize =   (m_dLetterHeight) - (yMax-yMin);	
				newYMag = (yMax-yMin+ addsize)/(yMax - yMin);
			}
			m_itmp = cnt;
			
			//if(m_lineIndex != 0 && m_lineCount != m_lineIndex)
			//	m_pVector[cnt].d.y =  -(yMaxT - yMinT+m_dLineSpace+(yMinT-m_pVector[cnt].d.y));
			m_lineCount++;
			if(m_lineIndex == 0) break;
		}
	}
	
	m_lineCount=0;
	for(int n = 0; n < (int)dwVectorLength; n++)
	{
		m_pVector[n].d.y = m_pVector[n].d.y*newYMag;
		if(m_pVector[n].t & 0x10)
		{
			if(m_lineIndex != 0 && m_lineCount != m_lineIndex)
			m_pVector[n].d.y =  -(m_dLetterHeight+m_dLineSpace);
			
		}
		m_lineCount++;
	}

//	for(int cnt = 0; cnt < dwVectorLength; cnt++)
	{
		//if( iTotalline > 0 )	
		//if(m_pVector[cnt].t & 0x10 || cnt == dwVectorLength-1  )
		{
			//	GetMinMax(m_pVector,dwVectorLength,xMin,xMax,yMin,yMax);
			//	m_pVector[0].d.y += (yMax - yMin - iCharHeight);
			m_ibeforePosition+=cnt;
		
			
			GetMinMax(m_pVector,cnt,xMin,xMax,yMin,yMax);
			//m_pVector[beforePoint].d.y = 0;
			//GetMinMaxVector(m_pVector,beforePoint, cnt,xMin,xMax,yMin,yMax);
			GetMinMaxVector(m_pVector,0, dwVectorLength,xMin,xMax,yMin,yMax);
			yMinTmp = yMin;
			yMaxTmp = yMax;
			iMinValue = int(abs(yMinF - yMin));
			//if(yMax - yMin > yMaxT - yMinT && yMin < 0 )
			//if(yMax - yMin > yMaxT - yMinT && (yMin < 0 && iMinValue < 10)) //2006.03.30 정종섭 필드오차 발생때문에....
			if(yMax - yMin > yMaxT - yMinT && yMin <= 0 ) //2006.03.30 정종섭 필드오차 발생때문에....
			{
				//addsize =   (m_dTotalHeight+m_dLineSpace) - (yMax-yMin);
				//newYMag = (yMax-yMin+ addsize)/(yMax - yMin)*(iTotalline+1);
				addsize =   m_dTotalHeight - (yMax-yMin);
				newYMag = (yMax-yMin+ addsize)/(yMax - yMin);

			}
			else if(yMax - yMin < yMaxT - yMinT )
			{
				//addsize =   (m_dLetterHeight*0.67+m_dLineSpace) - (yMax-yMin);
				//newYMag = (yMax-yMin+ addsize)/(yMax - yMin)*(iTotalline+1);
				addsize =   m_dLetterHeight*0.67 - (yMax-yMin);
				newYMag = (yMax-yMin+ addsize)/(yMax - yMin);
			}
			else
			{
				addsize =   (m_dLetterHeight) - (yMax-yMin);
				newYMag = (yMax-yMin+ addsize)/(yMax - yMin);
			}
			//addsize = 0;
			//if(itmpLine == 2) newYMag = 3;
				int itmp=0;
				itmp = (int)(yMaxT-yMinT);
				double m_dLineTmp = 0;
				//if(m_dLineSpace > 0)
				//m_dLineSpace = m_dLineSpace*(itmp/m_dLineSpace) ; 
				//m_dLineSpace = m_dLineSpace + 51;
				//m_dLineTmp = 2*(m_dLineSpace* 0.8351321);//0.83513209181462911243761348873743;
				m_dLineTmp = m_dLineSpace;

				double tmp=0;
//				for(int n = beforePoint; n < cnt-1; n++)
//				{
//				//	m_pVector[n].d.y = m_pVector[n].d.y*newYMag;
//				}

				//if(m_lineIndex != 0 && itmpLine != m_lineIndex)
				//	m_pVector[cnt].d.y =  -(itmp+m_dLineTmp+(yMinT-m_pVector[cnt].d.y));

//				for( n = 0; n < (int)dwVectorLength; n++)
//				{
//				//	m_pVector[n].d.y = m_pVector[n].d.y*newYMag;		
//				}
				
				
			
			//	else
			//		m_pVector[cnt].d.y =  -((yMaxT-yMinT)+m_dLineSpace);

				
				//m_pVector[cnt].d.y = m_pVector[cnt].d.y*newYMag;	
				

				//m_pVector[n].d.y = m_pVector[n].d.y*newYMag;
					GetMinMaxVector(m_pVector,beforePoint, cnt,xMin,xMax,yMin,yMax);
					//m_pVector[n+itmpLine].d.y =  -((yMaxT - yMinT)+m_dLineSpace);  // 설정한 높이만큼 아래로 향하는 벡터가 된다.
				//	m_pVector[cnt].d.y =  -(m_dLetterHeight+m_dLineSpace);  
			
			//		if(m_dLetterHeight > 0)
			//			m_pVector[dwStorePos+k].d.y =  (-(m_dLineSpace + m_dLetterHeight));  // 설정한 높이만큼 아래로 향하는 벡터가 된다.
			//		else
			//			m_pVector[dwStorePos+k].d.y =  (-(m_dLineSpace + m_dLetterHeight/*iCharHeight */ ));  // 설정한 높이만큼 아래로 향하는 벡터가 된다.
			
			//		m_pVector[dwStorePos+k].t = 0x02 | 0x10;
			
			
			beforePoint=cnt+1;
			itmpLine++;
		}
		
		
	}
	
	/*
	else
	{
	
		iMinValue = abs(yMinF - yMin);
		//if(yMax - yMin > yMaxT - yMinT && yMin < 0 )
		if(yMax - yMin > yMaxT - yMinT && (yMin < 0 && iMinValue < 10)) //2006.03.30 정종섭 필드오차 발생때문에....

		{
			addsize =   (m_dTotalHeight) - (yMax-yMin);
			newYMag = (yMax-yMin+ addsize)/(yMax - yMin);
		}
		else if(yMax - yMin < yMaxT - yMinT && yMin >=0)
		{
			addsize =   (m_dLetterHeight*0.67) - (yMax-yMin);
			newYMag = (yMax-yMin+ addsize)/(yMax - yMin);
		}
		else
		{
			addsize =   (m_dLetterHeight) - (yMax-yMin);
			newYMag = (yMax-yMin+ addsize)/(yMax - yMin);
		}
		
		
		for(int n = 0; n < dwVectorLength; n++)
		{
			m_pVector[n].d.y = m_pVector[n].d.y*newYMag;		
		}
				
	}
	*/
//		for(int n = 0; n < dwVectorLength; n++)
//		{
//			m_pVector[n].d.y = m_pVector[n].d.y*newYMag;		
//		}

	point= CDPoint(0,0);

	DoAlign(); // 정렬 ( Middle, Left, Right 정렬)

	
	// 2011. 03. 04 syhun START - 폰트에서 각도변경 관련 추가
	//if (m_dAngle != 0)
//	{
//		if (m_pVectorRel != NULL  )
//		{
//			delete [] m_pVectorRel;
//			m_pVectorRel = NULL;
//		}
//		if (m_pVectorAbs != NULL)
//		{
//			delete [] m_pVectorAbs;
//			m_pVectorAbs = NULL;
//		}
//		if (m_pVectorTmp != NULL)
//		{
//			delete [] m_pVectorTmp;
//			m_pVectorTmp = NULL;
//		}
//		m_pVectorRel = new Vector[dwVectorLength];
//		m_pVectorAbs = new Vector[dwVectorLength];
//		m_pVectorTmp = new Vector[dwVectorLength];
//		
//		double dAngle = GetAngle();
//		// Center점을 찾는다.
//		GetMinMax(m_pVector,dwVectorLength,xMin,xMax,yMin,yMax);
//		//double centerX = xMin + (xMax - xMin) / 2;
//		//double centerY = yMin + (yMax - yMin) / 2;
//		double oldMinX = xMin, newMinX = 999999;
//		
//		double cs, sn;
//		cs = cos(PI * dAngle / 180);
//		sn = sin(PI * dAngle / 180);
//		
//		BOOL bFirst = TRUE;
//		for (i = 0; i < dwVectorLength; i++)	// 상대좌표를 절대좌표로 바꾼후 중심을 기준으로 각도 변경.
//		{
//			m_pVectorAbs[i].t = m_pVector[i].t;
//			
//			if (bFirst)
//			{
//				m_pVectorAbs[i].d.x = m_pVector[i].d.x;
//				m_pVectorAbs[i].d.y = m_pVector[i].d.y;
//				bFirst = FALSE;
//			}
//			else
//			{
//				m_pVectorAbs[i].d.x = m_pVectorAbs[i-1].d.x + m_pVector[i].d.x;
//				m_pVectorAbs[i].d.y = m_pVectorAbs[i-1].d.y + m_pVector[i].d.y;
//			}
//			
//			m_pVectorTmp[i].t = m_pVectorAbs[i].t;
//			m_pVectorTmp[i].d.x = (m_pVectorAbs[i].d.x/* - centerX*/) * cs - (m_pVectorAbs[i].d.y/* - centerY*/) * sn;
//			m_pVectorTmp[i].d.y = (m_pVectorAbs[i].d.x/* - centerX*/) * sn + (m_pVectorAbs[i].d.y/* - centerY*/) * cs;
//			//m_pVectorTmp[i].d.x += centerX;
//			//m_pVectorTmp[i].d.y += centerY;
//		}
//		memcpy(m_pVectorAbs, m_pVectorTmp,  sizeof(Vector) * dwVectorLength);
//		
//		bFirst = TRUE;
//		for (i = 0; i < dwVectorLength; i++)	// 절대좌표를 상대좌표로 다시 바꿈.
//		{
//			m_pVectorRel[i].t = m_pVectorAbs[i].t;
//			
//			if (bFirst)
//			{
//				m_pVectorRel[i].d.x = m_pVectorAbs[i].d.x;
//				m_pVectorRel[i].d.y = m_pVectorAbs[i].d.y;
//				bFirst = FALSE;
//			}
//			else
//			{
//				m_pVectorRel[i].d.x = m_pVectorAbs[i].d.x - m_pVectorAbs[i-1].d.x;
//				m_pVectorRel[i].d.y = m_pVectorAbs[i].d.y - m_pVectorAbs[i-1].d.y;
//			}
//		}
//		
//		GetMinMax(m_pVectorRel,dwVectorLength,xMin,xMax,yMin,yMax);
//		newMinX = xMin;
//		bFirst = TRUE;
//		for (i = 0; i < dwVectorLength; i++)
//		{
//			m_pVectorAbs[i].d.x += (oldMinX - newMinX);
//			
//			if (bFirst)
//			{
//				m_pVectorRel[i].d.x = m_pVectorAbs[i].d.x;
//				m_pVectorRel[i].d.y = m_pVectorAbs[i].d.y;
//				bFirst = FALSE;
//			}
//			else
//			{
//				m_pVectorRel[i].d.x = m_pVectorAbs[i].d.x - m_pVectorAbs[i-1].d.x;
//				m_pVectorRel[i].d.y = m_pVectorAbs[i].d.y - m_pVectorAbs[i-1].d.y;
//			}
//		}
//		memcpy(m_pVector, m_pVectorRel, sizeof(Vector) * dwVectorLength);
//		
////		if (m_pVectorRel != NULL)
////		{
////			delete [] m_pVectorRel;
////			m_pVectorRel = NULL;
////		}
////		if (m_pVectorAbs != NULL)
////		{
////			delete [] m_pVectorAbs;
////			m_pVectorAbs = NULL;
////		}
////		if (m_pVectorTmp != NULL)
////		{
////			delete [] m_pVectorTmp;
////			m_pVectorTmp = NULL;
////		}
//	}
	// syhun END.


	// 글상자 크기 구할 차례
	//yMax = yMin + (iTotalline+1)*iCharHeight + (int)((iTotalline)*(m_dLineSpace));
	//GetMinMax(m_pVector,dwVectorLength,xMin,xMax,yMin,yMax);


	
// 	if(TRUE==m_bArcArray) DoArcArray();
	
	GetMinMax(m_pVector,dwVectorLength,xMin,xMax,yMin,yMax);
	m_dwWidth = xMax - xMin;
	m_dwHeight = yMax - yMin;
//	m_pVector[0].d.x -=xMin; //지대로 정렬이 될라나?
//	m_pVector[0].d.y -=yMin;
	


	//Save(m_pVector, dwVectorLength); //디버깅용.. .
	// 원형 배열 작성.
	
	if(TRUE!=m_bArcArray) 
	{
		double  m_dwtmpWidth;
		if( m_bEqualSpan == TRUE)
		{
			if(MaxstrLength > 1)
			{
				double dAngle = GetAngle();
				if (dAngle >= 180)
					dAngle -= 180;

				m_dwtmpWidth = (((m_dCharSpace*MaxstrLength)+(m_dLetterSpace*(MaxstrLength-1)))-(xMax));
				m_dwtmpWidth = cos(PI * dAngle / 180) * m_dwtmpWidth;
			}
			else
				m_dwtmpWidth = (m_dCharSpace*MaxstrLength)-(xMax);
			
			m_dwWidth = (xMax)+m_dwtmpWidth;// -  xMin;
		}
		else
		{
			m_dwtmpWidth = (xMax -  xMin);
			m_dwWidth = m_dwtmpWidth;// -  xMin;
		}
		
		m_dwHeight = (yMax - yMin) ;
		if(m_dwHeight <= 0 )
			m_dwHeight = 1;
		m_pVector[0].d.y -=yMin;
	}
	else
	{
		DoArcArray();
		GetMinMax(m_pVector,dwVectorLength,xMin,xMax,yMin,yMax);
		m_dwWidth = xMax - xMin;
		m_dwHeight = yMax - yMin;

		if(m_dwHeight <= 0 )
			m_dwHeight = 1;
		m_pVector[0].d.x -=xMin; //지대로 정렬이 될라나?
		m_pVector[0].d.y -=yMin;
	}
	
	
	return R_DEFAULT;

}
  


double CFontLoader::GetCharCenter(int index, CDPoint point)
{
	int i, j, check = 0;
	double _max = -2147483647 , _min = 2147483647;

	DWORD dwVectorLength = GetVectorSize();
	
//	ASSERT(index != 13);
	
	if (m_pVector[index].t == 4)
	{
		if (_max < point.x)
			_max = point.x;
		if (_min > point.x)
			_min = point.x;
		check = 1;
	}

	for(i = index + 1 ; i < (signed) dwVectorLength; i++) 
	{
		switch (m_pVector[i].t)
		{
		case 10: // 캐릭터의 끝
			point.x += m_pVector[i].d.x;
			point.y += m_pVector[i].d.y;

			if (check == 0)
			{	// 공백 이면
				for( j = index+1; j <= i; j++)
				{
					if (_max < point.x)
						_max = point.x;
					if (_min > point.x)
						_min = point.x;

					point.x += m_pVector[i].d.x;
					point.y += m_pVector[i].d.y;

					if (_max < point.x)
						_max = point.x;
					if (_min > point.x)
						_min = point.x;
				}
			}
			return (_min + (_max - _min)/2);
		case 18:// 개행벡터 
			return 0;
		default:

			if (m_pVector[i].t == 4)
			{
				if (_max < point.x)
					_max = point.x;
				if (_min > point.x)
					_min = point.x;

				point.x += m_pVector[i].d.x;
				point.y += m_pVector[i].d.y;

				if (_max < point.x)
					_max = point.x;
				if (_min > point.x)
					_min = point.x;
				check = 1;
			} else {
				point.x += m_pVector[i].d.x;
				point.y += m_pVector[i].d.y;
			}

			break;
		}
	}
	return (_min + (_max - _min)/2);
}


void CFontLoader::DoArcArray()
{  // 아크 어레이를 하자.
	
	double dRadius, pointr, lx,l, theta, offsettheta;
	double theta1, dStartAngle;
	CDPoint temppoint, tempp;
	int charcount = 0;
	//LONG templong;
	double templong;

	double xmin,ymin,xmax,ymax;

	DWORD dwVectorLength;
	CDPoint p,c;
	int i;
	
	


	p = CDPoint(0, 0);
	c = CDPoint(0, 0);
	// 글자 원형 배열 작성 하기

	dStartAngle = GetArcStartAngle();

	dRadius = GetArcRadius();
	
	dwVectorLength = GetVectorSize();
	ASSERT(dwVectorLength != 0 );
	{
		xmin = 999999;	ymin = 999999;
		xmax = -999999;	ymax = -999999;

		// 첫번째 문자의 최소값을 구한다
		for (i = 0; i < (signed)dwVectorLength; i++)
		{
			// 문자끝이거나 개행 벡터 이면
			if (m_pVector[i].t == 10 || m_pVector[i].t == 18)
				break;
			
		}
		GetMinMax(m_pVector,i,xmin,xmax,ymin,ymax);
		
		// 한캐릭터를 비튼다
		p.x = m_pVector[0].d.x;
		p.y = m_pVector[0].d.y;

		// 각도 설정 
		dRadius = GetArcRadius(); // r/ tobj->Radius;
		pointr = dRadius;

		offsettheta = -((xmax - xmin) / dRadius - dStartAngle);
		
		l = ( xmax - xmin ) - GetCharCenter(0, p);
		theta1 = double(l /dRadius + offsettheta);		// 각 글자 회전각 

		temppoint.x =  (pointr + m_pVector[0].d.y)  * cos(theta1);
		temppoint.y =  (pointr + m_pVector[0].d.y)  * sin(theta1);


		temppoint.x = ( temppoint.x - (GetCharCenter(0, p) - m_pVector[0].d.x)* cos(theta1 - PI/2) );
		temppoint.y = ( temppoint.y - (GetCharCenter(0, p) - m_pVector[0].d.x)* sin(theta1 - PI/2) );


		c.x = temppoint.x;
		c.y = temppoint.y;

		m_pVector[0].d = c;

		// 점의 반지름 = lx - dy;
		for(i = 1; i < (signed)dwVectorLength; i++) 
		{
			switch (m_pVector[i].t)
			{
			case 10: // 캐릭터의 끝
				p.x += m_pVector[i].d.x; // 소스 벡터 위치
				p.y += m_pVector[i].d.y; // 소스 벡터 위치

				// 다음 글자의 회전 각도 조정
				if (GetCharCenter(i, p) == 0)
				{	// 행의 마지막 문자 라면 
					templong = m_pVector[i].d.x;
					m_pVector[i].d.x =  (double(cos(PI/2-theta1)) * double(m_pVector[i].d.x) + double(sin(PI/2-theta1))*double(m_pVector[i].d.y));
					m_pVector[i].d.y = (double(-sin(PI/2-theta1)) * double(templong)+ double(cos(PI/2-theta1))*double(m_pVector[i].d.y));

					c.x  += m_pVector[i].d.x ;
					c.y  += m_pVector[i].d.y ;
					break;
				} 

				l = (xmax - xmin ) - GetCharCenter(i, p); //+ 38;  //(xmax - xmin ) - p.x - tobj->CharSpace/2 ; // l - tobj->CharSpace;
				theta1 = double(l / dRadius + offsettheta);

				// 초기 벡터 설정
				tempp = c;

				// 원형 상의 좌표 구하기
				temppoint.x =  ((pointr + p.y) * cos(theta1));
				temppoint.y = ((pointr + p.y) * sin(theta1));

				temppoint.x =  ( temppoint.x - ( GetCharCenter(i, p) - p.x )*cos(theta1 - PI/2) );
				temppoint.y =  ( temppoint.y - ( GetCharCenter(i, p) - p.x )*sin(theta1 - PI/2) );

				c.x = temppoint.x; //pointr * cos(theta) + tempp.x - c.x;
				c.y = temppoint.y; //pointr * sin(theta) + tempp.y - c.y;

				m_pVector[i].d = c - tempp; // 원형 좌표 상에서 현 좌표 점과 다음 좌표 점의 변위 구하기
				

				charcount++;
				break;
			case 18: // 개행 벡터
				p.x += m_pVector[i].d.x; // 소스 벡터 위치
				p.y += m_pVector[i].d.y; // 소스 벡터 위치
				// 각도 설정
				lx = ((xmax - xmin ) - p.x);
				theta  = lx / dRadius + offsettheta;

				// 개향 벡터 설정 
				temppoint = c;
//				pointr = pointr - charheight - tobj->LineSpace;
				c.x =  ( (pointr + p.y)  * cos(theta) );
				c.y = ( (pointr + p.y) * sin(theta) );
				m_pVector[i].d = c - temppoint;


				// 초기 위치로 가는 벡터 설정
				tempp =  p;
				i++;
				p.x += m_pVector[i].d.x; // 소스 벡터 위치
				p.y += m_pVector[i].d.y; // 소스 벡터 위치

				// 각도 설정
				l = ( xmax - xmin ) - GetCharCenter(i, p);
				theta1 = double(l /dRadius + offsettheta);		// 각 글자 회전각 

				// 초기 벡터 설정
				temppoint.x = ( (pointr + p.y) * cos(theta1) );
				temppoint.y = ( (pointr + p.y) * sin(theta1));

				temppoint.x = ( temppoint.x - (GetCharCenter(i, p) - p.x) * cos(theta1 - PI/2));
				temppoint.y =  ( temppoint.y - (GetCharCenter(i, p) - p.x) * sin(theta1 - PI/2));

				tempp = c;
				c = temppoint;

				m_pVector[i].d = c - tempp;
				
				break;
			default: // 기본 벡터
				p.x += m_pVector[i].d.x; // 소스 벡터 위치
				p.y += m_pVector[i].d.y; // 소스 벡터 위치

				// 각도만큼 변환 
				templong = m_pVector[i].d.x;
				m_pVector[i].d.x =  double(cos(PI/2-theta1)) * double(m_pVector[i].d.x) + double(sin(PI/2-theta1))*double(m_pVector[i].d.y);
				m_pVector[i].d.y = double(-sin(PI/2-theta1)) * double(templong) + double(cos(PI/2-theta1))*double(m_pVector[i].d.y);
				
				c.x += m_pVector[i].d.x;
				c.y += m_pVector[i].d.y;
				break;
			}

		}
		m_pVector[i-1].d.x = 0;
		m_pVector[i-1].d.y = 0;
		// 글상자의 크기를 구한다
		p = CDPoint(0,0);
		for(i = 0; i < (signed) dwVectorLength; i++) 
		{
			if (m_pVector[i].t == 4)
			{
				xmin = ( p.x < xmin ) ? p.x : xmin;
				ymin = ( p.y < ymin ) ? p.y : ymin;
				xmax = ( p.x > xmax ) ? p.x : xmax;
				ymax = ( p.y > ymax ) ? p.y : ymax;

				p.x += m_pVector[i].d.x;
				p.y += m_pVector[i].d.y;
	
				//if(m_pVector[i].t==18) p.x = 0;
				xmin = ( p.x < xmin ) ? p.x : xmin;
				ymin = ( p.y < ymin ) ? p.y : ymin;
				xmax = ( p.x > xmax ) ? p.x : xmax;
				ymax = ( p.y > ymax ) ? p.y : ymax;
			} else 
			{
				p.x += m_pVector[i].d.x;
				p.y += m_pVector[i].d.y;
			}
		}
	}

}

void CFontLoader::SetArcArray(BOOL bFlag)
{
	m_bArcArray = bFlag;

}

BOOL CFontLoader::GetArcArray()
{
	return m_bArcArray;
}
	
void CFontLoader::SetArcRadius(double dRadius)
{
	//ASSERT(dRadius > 0 );
	m_dArcRadius = dRadius;
}

double CFontLoader::GetArcRadius()
{
	return m_dArcRadius;
}

void CFontLoader::SetArcStartAngle(double dStartAngle)
{	
	m_dStartAngle = dStartAngle;
}

double CFontLoader::GetArcStartAngle()
{
	return m_dStartAngle;
}

void CFontLoader::DoAlign()
{
	int ixMin=0, ixMax=0, iyMin=0, iyMax=0;

	int ixMinT=0, ixMaxT=0, iyMinT=0, iyMaxT=0;

	int iCurrentWidth=0;

	int i, j;

	DWORD dwLength;

	CPoint point;

	int iNewLine = 1;


	dwLength = GetVectorSize();
	ASSERT(dwLength != 0 );
	if( dwLength == 0 ) return;
	
	int iTotalWidth = GetMaxWidth_LineFeed(m_pVector,dwLength);  //글상자 최대폭
	
	for ( i=0; i < (signed)dwLength ; i++)
	{
		ixMinT = iyMinT =0;
		ixMaxT = iyMaxT =0;
		iCurrentWidth = 0;
		point= CPoint(0,0);
		j=i;
	
		// 한 행의 최대, 최소 좌표를 구한다 길이를 구한다
		// 개행 문자나 데이터의 끝일때 루프를 빠져 나온다
		for( ; i< (signed)dwLength; i++) 
		{
			if(m_pVector[i].t == 18) 
			// 개행 을 하는 벡터라면
				break;
			//if(i >= (signed)dwLength -1) 
			{	// 현재의 위치가 데이터의 끝에 걸치거나 넘어가면
				// j는 벡터의 끝을 가르키고 다음 문자로 넘어 간다 
				
		//		break; 
			}

			ixMinT = ( point.x < ixMinT ) ? point.x : ixMinT;
			iyMinT = ( point.y < iyMinT ) ? point.y : iyMinT;
			ixMaxT = ( point.x > ixMaxT ) ? point.x : ixMaxT;
			iyMaxT = ( point.y > iyMaxT ) ? point.y : iyMaxT;

			point.x += (int)m_pVector[i].d.x; // 좌표상의 현 벡터의 x 위치 
			point.y += (int)m_pVector[i].d.y; // 좌표상의 현 벡터의 y 위치

			// 캐릭터 내의 최대, 최소 좌표를 구한다
			
			//TRACE(" i, x, y : %d, %d, %d; %d,%d\n",i,m_pVector[i].d.x,m_pVector[i].d.y,m_xmin, m_xmax);
		}
		ixMinT = ( point.x < ixMinT ) ? point.x : ixMinT;
		iyMinT = ( point.y < iyMinT ) ? point.y : iyMinT;
		ixMaxT = ( point.x > ixMaxT ) ? point.x : ixMaxT;
		iyMaxT = ( point.y > iyMaxT ) ? point.y : iyMaxT;
		iCurrentWidth = ixMaxT - ixMinT; // 현재의 라인의 최대 폭 
		
		m_dwAlignFlag = modeLEFT; //2006.05.25 EO방식에 맞춤 정종섭
		switch(m_dwAlignFlag)
		{
		case modeRIGHT:
			// 개행줄이면 시작 위치를 전체 넓이의 끝
			// 시작 위치 = 시작 위치 - 문자행의 넓이
			if(iNewLine)
				m_pVector[j].d.x += iTotalWidth;
			
			m_pVector[j].d.x -= iCurrentWidth;
			break;
		case modeMIDDLE:
			if(i <(signed)dwLength)
			m_pVector[i].d.x -= iCurrentWidth;
			m_pVector[j].d.x += (iTotalWidth/2 - iCurrentWidth/2);
			if(i <(signed)dwLength)
			m_pVector[i].d.x -= (iTotalWidth/2 - iCurrentWidth/2);
			break;
		case modeLEFT:
		default      :
			if(i <(signed)dwLength)
			m_pVector[i].d.x -= iCurrentWidth;
			//m_pVector[i].d.x = 0;
		}
		
		iNewLine = 0;
	}

}

DWORD CFontLoader::GetMaxWidth_LineFeed(Vector *pData, DWORD dwLength)
{
	int xMaxOther=-999999, xMinOther=999999;
	int xMin = 999999, xMax = -999999;
	int i;
	CPoint point(0,0);
	
	
	for ( i = 0 ; i < (signed)dwLength; i++)
	{
		if( point.x < xMin )xMin = point.x;
		if( point.x > xMax )xMax = point.x;
		point.x += (int)m_pVector[i].d.x;
		if( m_pVector[i].t == 18) //데이타가 쓰여지지 않은 개행문자라면
		{
			 if(  xMin < xMinOther ) xMinOther = (DWORD)xMin;
			 if(  xMax > xMaxOther ) xMaxOther = (DWORD)xMax;
			 point.x = 0;
			 xMin = 0;
			 xMax = 0;
			 continue;
		}
		if( point.x < xMin ) xMin = point.x;
		if( point.x > xMax ) xMax = point.x;
	}
	if(  xMin < xMinOther ) xMinOther = (DWORD)xMin;
	if(  xMax > xMaxOther ) xMaxOther = (DWORD)xMax;
	return (xMaxOther - xMinOther);
}

void CFontLoader::SetAlign(DWORD dwFlag)
{
	m_dwAlignFlag = dwFlag;
}
DWORD CFontLoader::GetAlign()
{
	return m_dwAlignFlag;
}
void CFontLoader::GetMinMaxVector(Vector *pData, DWORD dwStartPos,DWORD dwEndPos, double &nMinX, double &nMaxX, double &nMinY, double &nMaxY)
{
	int i;
	double iMaxX=-999999,iMinX=999999,iMaxY=-999999,iMinY=999999;
	
	CDPoint point = CDPoint(0,0);
	

	for( i=dwStartPos ; i< (int)dwEndPos; i++ )
	{
		if( pData[i].t == 04 ||pData[i].t == 01 )
		{
			if( point.x > iMaxX ) iMaxX = point.x;
			if( point.x < iMinX ) iMinX = point.x;
			if( point.y > iMaxY ) iMaxY = point.y;
			if( point.y < iMinY ) iMinY = point.y;

			point.x +=pData[i].d.x;
			point.y +=pData[i].d.y;

			if( point.x > iMaxX ) iMaxX = point.x;
			if( point.x < iMinX ) iMinX = point.x;
			if( point.y > iMaxY ) iMaxY = point.y;
			if( point.y < iMinY ) iMinY = point.y;
		}
		else
		
		{
			point.x +=pData[i].d.x;
			point.y +=pData[i].d.y;
		}
		
		

	}

	nMinX = iMinX; 
	nMaxX = iMaxX;
	nMinY = iMinY;
	nMaxY = iMaxY;
}

void CFontLoader::GetMinMax(Vector *pData, DWORD dwLength, double &nMinX, double &nMaxX, double &nMinY, double &nMaxY)
{
	int i;
	double iMaxX=-999999,iMinX=999999,iMaxY=-999999,iMinY=999999;
	
	CDPoint point = CDPoint(0,0);
	

	for( i=0 ; i< (int)dwLength; i++ )
	{
		/*	point.x +=(long)pData[i].d.x;
			point.y +=(long)pData[i].d.y;
	
			if( point.x > iMaxX ) iMaxX = point.x;
			if( point.x < iMinX ) iMinX = point.x;
			if( point.y > iMaxY ) iMaxY = point.y;
			if( point.y < iMinY ) iMinY = point.y;

			point.x +=(long)pData[i].d.x;
			point.y +=(long)pData[i].d.y;

			if( point.x > iMaxX ) iMaxX = point.x;
			if( point.x < iMinX ) iMinX = point.x;
			if( point.y > iMaxY ) iMaxY = point.y;
			if( point.y < iMinY ) iMinY = point.y;
		*/
		
		
		if( pData[i].t == 04 || pData[i].t == 01 )
		{
			if( point.x > iMaxX ) iMaxX = point.x;
			if( point.x < iMinX ) iMinX = point.x;
			if( point.y > iMaxY ) iMaxY = point.y;
			if( point.y < iMinY ) iMinY = point.y;

			point.x +=pData[i].d.x;
			point.y +=pData[i].d.y;

			if( point.x > iMaxX ) iMaxX = point.x;
			if( point.x < iMinX ) iMinX = point.x;
			if( point.y > iMaxY ) iMaxY = point.y;
			if( point.y < iMinY ) iMinY = point.y;
		}
		else
		{
			point.x +=pData[i].d.x;
			point.y +=pData[i].d.y;
		}
	}

	nMinX = iMinX; 
	nMaxX = iMaxX;
	nMinY = iMinY;
	nMaxY = iMaxY;
}

void CFontLoader::SetLetterSpace(double dLetterSpace)
{
	m_dLetterSpace = dLetterSpace;
}

double CFontLoader::GetLetterSpace()
{
	return m_dLetterSpace;
}

void CFontLoader::SetCharSpace(double dCharSpace)
{
	m_dCharSpace = dCharSpace;
}
double CFontLoader::GetCharSpace()
{
	return m_dCharSpace;
}
void CFontLoader::SetLineSpace(double dLineSpace)
{
	m_dLineSpace = dLineSpace;
}
double CFontLoader::GetLineSpace()
{
	return m_dLineSpace;
}

CPoint CFontLoader::GoThrough(DWORD dwStartPos,DWORD dwEndPos)
{
	CPoint ptEnd = CPoint(0,0);

	for(int i = dwStartPos; i < (signed)dwEndPos ; i++)
	{
		ptEnd += m_pVector[i].d;
	}
	return ptEnd;
}

UINT CFontLoader::LoadFont(CString strFileName) //폰트를 로딩한다.m_pFontHeader,m_pFontData,m_pFontIndex가 셋팅됨.
{
	CFile FontFile;
	CFileException e;

	

	if( !FontFile.Open( strFileName, CFile::modeRead, &e ))
	{
		#ifdef _DEBUG
			afxDump << "File Open Error!" << e.m_cause << "\n";
		#endif
			return R_FILE_OPEN_ERROR;
	}

	m_dwFileSize = FontFile.GetLength();
	
	m_pFontData = new BYTE[m_dwFileSize];
	ASSERT(m_pFontData != NULL);

	FontFile.Read(m_pFontData, m_dwFileSize);
	FontFile.Close();

	memcpy(m_pFontHeader, m_pFontData, HEADER_LENGTH);
	memcpy(m_pFontIndex, (m_pFontData +HEADER_LENGTH) , (INDEX_LENGTH*4));

	return R_DEFAULT;
}

UINT CFontLoader::LoadFont(BYTE *pFontData, DWORD dwByte) //화일에서 직접 로딩하지 않고 
{

	if(pFontData == NULL) return R_FAILED;

	ASSERT(pFontData != NULL);

	m_pFontData = new BYTE[dwByte];
	memcpy(m_pFontData, pFontData, dwByte);

	memcpy(m_pFontHeader, m_pFontData, HEADER_LENGTH);
	memcpy(m_pFontIndex, (m_pFontData +HEADER_LENGTH) , (INDEX_LENGTH*4));

	return R_DEFAULT;
}



Vector *CFontLoader::GetVectorData() // 생성한 벡터를 돌려준다.
{
	Vector *pVector = new Vector[m_dwVectorSize];
	memcpy( pVector, m_pVector, m_dwVectorSize * sizeof(Vector));
	return pVector;
}

DWORD CFontLoader::GetVectorSize()
{

	return m_dwVectorSize;
}


DWORD CFontLoader::GetTotalLine(CString strData) //strData안에 있는 총 엔터 갯수, 문자열끝에 연속된 엔터는 새지 않는다.
{
	int i;
	int iDataLength, iTotalLine=0;

	iDataLength = strData.GetLength();
	for(  i= 0 ; i < iDataLength ; i++)
	{
		if( strData[i] == '\n')
		{
			iTotalLine++;
		}
	}

	for ( i = iDataLength-1; i >= 0; i--)
	{
		if( strData[i] == '\n') 
			iTotalLine--;
		else if (strData[i] == '\r')
			continue;
		else 
			break;
	}
	return (DWORD)iTotalLine;
}


Vector* CFontLoader::CreateVectorArray(CString strData, DWORD &dwSize)
{
	Vector *pVector;
	dwSize = GetVectorCount(strData);
	m_dwVectorSize = dwSize;  // 생성할때 멤버변수에 크기도 저장해놓음.


	pVector = new Vector[dwSize];
	return pVector;
}


DWORD CFontLoader::GetRequireVectorSpace(CString strData) //순수 글자만을 벡터로 표현하기위한 공간 바이트단위.
{
	int i;
	int iDataLength, iTotalLine=0;
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	int Zeroindex=0; 
	CPoint m_area(0,0);
	for(int x=0;x<100;x++)
	{
		pFieldParameter->SetZeroArea(m_area, x); 
	}

	iDataLength = strData.GetLength();
	DWORD dwChar,dwDataOffset,dwNumberofVectorinByte;
	DWORD dwRequireVectorSpace=0;



	for(  i= 0 ; i < iDataLength ; i++)
	{
		if(strData[i]=='\n')
		{
			continue;
		}
		if(strData[i]=='\r')
		{
			continue;
		}
		dwChar = (DWORD)strData[i];
		GetCharInfo(dwChar,dwDataOffset,dwNumberofVectorinByte);
		if(strData[i] == '0')
		{
		    m_area.x = dwRequireVectorSpace/5;
			m_area.y = (dwRequireVectorSpace/5)+(dwNumberofVectorinByte/5);
			pFieldParameter->SetZeroArea(m_area, Zeroindex); 
			Zeroindex++;
		}
		dwRequireVectorSpace+=dwNumberofVectorinByte;
		
	}

	return dwRequireVectorSpace;
}


DWORD CFontLoader::GetVectorCount(CString strData) //벡터 배열 공간이 몇개 필요한지를 계산
{
	DWORD dwTotalSpace,dwLine;

	dwLine = GetTotalLine(strData);

	dwTotalSpace = GetRequireVectorSpace(strData);
	// 문자의 갯수를 벡터의 길이로 바꾼다
	// 문자의 길이 + "\n"의 길이 + "\0"의 길이 = 벡터의 갯수
	dwTotalSpace = dwTotalSpace / 5 + dwLine;
	

	return dwTotalSpace;
}

void CFontLoader::GetCharInfo(DWORD dwChar, DWORD  &dwDataOffset, DWORD &dwNumberofVectorinByte)
{
	dwDataOffset = (DWORD)m_pFontIndex[dwChar * 2];
	dwNumberofVectorinByte = (DWORD)m_pFontIndex[dwChar * 2 + 1];
}



void CFontLoader::GetPositionData(DWORD dwDataOffset, char &pen, short &iX, short &iY)
{
//해당 오프셋에서 5바이트의 정보를 가져온다.
//순서대로 pen,x좌표 ,y좌표 
		pen = m_pFontData[dwDataOffset ]; // 펜을 얻어온다.

		iX = m_pFontData[dwDataOffset + 2];   //X 좌표를 얻어온다.
		iX <<= 8;
		iX += m_pFontData[dwDataOffset  + 1];

		iY = m_pFontData[dwDataOffset  + 4];  //Y 좌표를 얻어온다.
		iY <<= 8;
		iY += m_pFontData[dwDataOffset  + 3]; 
}


DWORD CFontLoader::LoadCharacter(DWORD dwChar, int pos, int orValue) 
{
	char pen;
	short iX, iY;
	DWORD dwReadPos = 0;
	
	DWORD dwDataOffset,dwNumberofVectorinByte;
	DWORD dwNumberofVector;

	GetCharInfo( dwChar, dwDataOffset, dwNumberofVectorinByte);
	dwNumberofVector = dwNumberofVectorinByte / 5;
	
	int i = 0;
	for (i = 0; i < (int)dwNumberofVector; i++)
	{
		GetPositionData(dwDataOffset+dwReadPos,pen,iX,iY);
		m_pVector[pos+i].t = pen | orValue;
		m_pVector[pos+i].d.x = iX;
		m_pVector[pos+i].d.y = iY;
		orValue = 0;
		dwReadPos=dwReadPos + 5; // 5씩 데이타가 떨어져있다.(Font 에서) 
	}
	m_pVector[pos + i-1].t |= 0x08; // 마지막 벡터에 문자의 끝이라고 표시 
	
	return (dwNumberofVector); //몇개의 벡터가 사용되었는지를 리턴한다.
}

void CFontLoader::GetMinMaxinChar(DWORD dwChar, double &MinX, double &MaxX, double &MinY, double &MaxY)
{
	DWORD dwDataOffset, dwNumberofVectorinByte;

	GetCharInfo(dwChar,dwDataOffset,dwNumberofVectorinByte);
	GetMinMaxinChar(dwDataOffset,dwNumberofVectorinByte,MinX,MaxX,MinY,MaxY);
	
}



void CFontLoader::GetMinMaxinChar(DWORD dwDataOffset, DWORD dwNumberofVector, double &MinX,double &MaxX, double &MinY, double &MaxY)
{
	int i, iMaxX=-999999,iMinX=999999,iMaxY=-999999,iMinY=999999;
	char chPen;
	CPoint point = CPoint(0,0);
	short iX,iY;

    int testCount =0;
	for( i=0 ; i< (int)dwNumberofVector ; i+=5 )
	{
	   GetPositionData(dwDataOffset+i, chPen, iX, iY); //5바이트를 가져온다.
	   CString tmp;  
	   tmp.Format("Count: %d, cpen = %d, iX = %d, iY = %d",testCount,chPen ,iX,iY) ;
	   if(testCount < 20)
       //  AfxMessageBox(tmp);
		testCount++;
	   
/*
	
		if( point.x > iMaxX ) iMaxX = point.x;
		if( point.x < iMinX ) iMinX = point.x;
		if( point.y > iMaxY ) iMaxY = point.y;
		if( point.y < iMinY ) iMinY = point.y;

		point.x +=(long)iX;
		point.y +=(long)iY;

//		if( point.x > iMaxX ) iMaxX = point.x;
//		if( point.x < iMinX ) iMinX = point.x;
//		if( point.y > iMaxY ) iMaxY = point.y;
//		if( point.y < iMinY ) iMinY = point.y;
		
*/
// =================Orginal========================================
		if( chPen == 04 )
		{
			if( point.x > iMaxX ) iMaxX = point.x;
			if( point.x < iMinX ) iMinX = point.x;
			if( point.y > iMaxY ) iMaxY = point.y;
			if( point.y < iMinY ) iMinY = point.y;

			point.x +=iX;
			point.y +=iY;

			if( point.x > iMaxX ) iMaxX = point.x;
			if( point.x < iMinX ) iMinX = point.x;
			if( point.y > iMaxY ) iMaxY = point.y;
			if( point.y < iMinY ) iMinY = point.y;
		}
		else
		{
			point.x +=iX;
			point.y +=iY;
		}
		
//==================================================================		
	}

	MinX = iMinX; 
	MaxX = iMaxX;
	MinY = iMinY;
	MaxY = iMaxY;
	
}

// 현재 작업 11.08 여기까지!!
void CFontLoader::GetMaxWidthHeightinFont(double &nWidth , double &nHeight)
{
	double iMinX, iMaxX, iMinY, iMaxY;
	GetMinMaxinFont(iMinX, iMaxX, iMinY, iMaxY);
	nWidth = iMaxX - iMinX;      // 문자 너비.
	nHeight = iMaxY - iMinY;     // 문자 높이.

}


void CFontLoader::GetMinMaxinFont(double &nMinX, double &nMaxX, double &nMinY, double &nMaxY)
{
	int i;
	DWORD dwDataOffset;
	DWORD dwNumberOfVector;
	double TestMaxX,TestMaxY,TestMinY,cnt;
	TestMaxX=0;
	TestMaxY=0;
	TestMinY=0;
	cnt=0;
	
	double itmpMinX, itmpMaxX, itmpMinY, itmpMaxY;
	double iMinX=999999, iMaxX=-999999, iMinY=999999, iMaxY=-999999;

	//GetCharInfo( 'W', dwDataOffset, dwNumberOfVector );

	for( i = 'a'; i < 'z' ; i++)
	{
		GetCharInfo( i, dwDataOffset, dwNumberOfVector );
		GetMinMaxinChar(dwDataOffset, dwNumberOfVector, itmpMinX, itmpMaxX, itmpMinY, itmpMaxY);
		if( itmpMinX < iMinX ) iMinX = itmpMinX;
		if( itmpMaxX > iMaxX ) iMaxX = itmpMaxX;
		if( itmpMinY < iMinY) iMinY = itmpMinY;
		if( itmpMaxY > iMaxY) iMaxY = itmpMaxX;
	}
	for( i = 'A'; i < 'Z' ; i++)
	{
		GetCharInfo( i, dwDataOffset, dwNumberOfVector );
		GetMinMaxinChar(dwDataOffset, dwNumberOfVector, itmpMinX, itmpMaxX, itmpMinY, itmpMaxY);
		TestMaxY+=itmpMaxY;
		TestMinY+=itmpMinY;
		cnt++;

		if( itmpMinX < iMinX ) iMinX = itmpMinX;
		if( itmpMaxX > iMaxX ) iMaxX = itmpMaxX;
		if( itmpMinY < iMinY) iMinY = itmpMinY;
		if( itmpMaxY > iMaxY) iMaxY = itmpMaxX;
		
	}

	for( i = '0'; i < '9' ; i++)
	{
		GetCharInfo( i, dwDataOffset, dwNumberOfVector );
		GetMinMaxinChar(dwDataOffset, dwNumberOfVector, itmpMinX, itmpMaxX, itmpMinY, itmpMaxY);
		if( itmpMinX < iMinX ) iMinX = itmpMinX;
		if( itmpMaxX > iMaxX ) iMaxX = itmpMaxX;
		if( itmpMinY < iMinY) iMinY = itmpMinY;
		if( itmpMaxY > iMaxY) iMaxY = itmpMaxX;
	}

	
	int AvrTestY =0;
	
	nMinX = iMinX; nMaxX = iMaxX; nMinY = iMinY; nMaxY = iMaxY;

}
void CFontLoader::SetEqualSpan(BOOL nFlag)
{
	m_bEqualSpan = nFlag;


}
BOOL CFontLoader::GetEqualSpan()
{
	return m_bEqualSpan;
}


DWORD CFontLoader::GetWidth()
{
	return (DWORD)m_dwWidth;
	

}
DWORD CFontLoader::GetHeight()
{
	return (DWORD)m_dwHeight;
}

void CFontLoader::AddXVector(double xvector)
{
 AddX = (unsigned long)xvector;
}

void CFontLoader::SetWidtScale(double WidthScale)
{
  m_dWidthScale = WidthScale;
}

void CFontLoader::SetOrgRatio(double xratio)
{
 m_orgMag = xratio;
}


void CFontLoader::SetLetterHeight(double dLetterHeight)
{
	if(dLetterHeight > 0)
	m_dLetterHeight = dLetterHeight;

}

void CFontLoader::SetTotalLetterHeight(double dTotalHeight)
{
	if(dTotalHeight > 0)
	m_dTotalHeight = dTotalHeight;
}

void CFontLoader::SetDefaultFont(CString m_strFont)
{
	CString strTmp;
	TCHAR lpszName[256];
	TCHAR lpszExt[256];
	char drive[_MAX_DRIVE], dir[_MAX_DIR];

	_splitpath((LPSTR)(LPCTSTR)m_strFont, drive, dir, lpszName, lpszExt);
	
	strTmp.Format("%s", lpszName);
	m_FontName = strTmp.Left(3); 
}

// syhun START - 각도 관련 추가.
void CFontLoader::SetAngle(double dAngle)
{
	m_dAngle = dAngle;
}

double CFontLoader::GetAngle()
{
	return m_dAngle;
}
// syhun END.