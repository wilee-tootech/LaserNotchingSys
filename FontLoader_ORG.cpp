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

//  : 11.08�ۼ�����
//       11.13��. �����Ϸ�.


CFontLoader::CFontLoader()
{
	m_pVector = NULL;
	m_pFontData = NULL;
	m_bEqualSpan = FALSE;
	m_bArcArray = FALSE;
}

CFontLoader::~CFontLoader()
{
	if( m_pFontData != NULL ) delete [] m_pFontData;
	if( m_pVector != NULL ) delete [] m_pVector;

}


/*void Save(Vector *Data, DWORD dwLength)
{
	CFile file;
	file.Open("dumpfnt.txt",CFile::modeCreate |CFile::modeWrite);
	file.WriteHuge(Data, dwLength *sizeof(Vector) );
	file.Close();
}*/  // ������...


DWORD CFontLoader::LoadString(CString strData)
{
	int iStrLength, iStartPos,tmpLineCnt,iOrValue=0;
	double xMaxT,xMinT,xMax,yMaxT,yMinT,xMin,yMax,yMin, iCharHeight, iCharWidth;
	int iLineCount=0 , k, iLineMulti=0;
	CMathUtil mathUtil;
	DWORD dwStorePos=0, dwCharSize, dwVecSize,dwlowPos,dwhighPos;
	CPoint ptEndPoint;
	long lDistance;
	tmpLineCnt=0;
	iStartPos=0;
	dwlowPos=0;
	dwhighPos=0;

	iStrLength = strData.GetLength();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	
	
	
	// ���� ��ü�� ���� 
	GetMinMaxinFont(xMin,xMax,yMin,yMax);
	iCharWidth = xMax - xMin;  //��Ʈ ��ü�� ���� �ִ� �ʺ�
	iCharHeight = yMax - yMin;   //��Ʈ ��ü�� ���� �ִ� ����
	
	xMaxT =0;xMinT = 0;yMaxT=0;yMinT=0;
	
	GetMinMaxinChar('w',xMin,xMax,yMin,yMax); // EO���� 'W'(�빮��)�� �������� �ϱ⶧����
	yMaxT = yMax; yMinT = yMin; xMaxT=xMax;xMinT=xMin;
	double m_dwWidth_2 = xMaxT - xMinT;
	

	GetMinMaxinChar('W',xMin,xMax,yMin,yMax); // EO���� 'W'(�빮��)�� �������� �ϱ⶧����
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
	
	if( m_pVector != NULL ) delete [] m_pVector;
	
	m_pVector = CreateVectorArray(strData, dwVecSize); // �ʿ��� ���� ũ�⸸ŭ ���� �迭�� �����Ѵ�.
	
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
				strEndData+=0x0d;
				strEndData+=0x0a;
				
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
	
	for( int i = 0;  i< iStrLength; i++ ) //strData���� ��� ���ڿ� ���ؼ� ������ ����. 
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
	for( i = 0;  i< iStrLength; i++ ) 
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
	
	m_pVector = CreateVectorArray(strData, dwVecSize); // �ʿ��� ���� ũ�⸸ŭ ���� �迭�� �����Ѵ�.
	delete [] pBuffer;
	
	iStrLength = strData.GetLength();
	
	for(  i = 0;  i< iStrLength; i++ )
	{
		if( strData[i] == NULL)
			continue;
		if( strData[i] =='\n') // ���� ���ڰ� ������ iOrValue�� ���� �����Ѵ�.
		{
			iOrValue=0x10;
			iLineCount++;
			continue;
		}
		else if( strData[i] =='\r')
		{
			continue;
		}
		
		
		dwCharSize = LoadCharacter(strData[i],dwStorePos,iOrValue); //���� �ϳ��� �ε��Ѵ� 
		GetMinMaxinChar(strData[i],xMin,xMax,yMin,yMax);
		CString tmp = strData[i];
		if (xMax == -999999) //�����̽����ΰ�� ���� ó���� ���ش�.
		{
			yMin = 0;
			yMax = iCharHeight;
			xMin = 0;
			xMax = iCharWidth;
		}
		
		ptEndPoint.x = 0;	ptEndPoint.y = 0;
		ptEndPoint = GoThrough(dwStorePos,dwStorePos+dwCharSize-1);
		
		if( m_bEqualSpan == TRUE) // ���� ���� ��Ʈ�϶�  (������)
		{
			//---------------Orginal----------------------------------------------------
			//�������� ���� �Ǿ������� ������ ���� ���Ϳ� �� ���� ��ġ�� �����Ѵ�.
			//���� ��ġ�� �� ��ġ ����
			m_pVector[dwStorePos].d.x -= xMin;     
			//m_pVector[dwStorePos].d.y -= yMin;     
			//m_pVector[dwStorePos].d.y  = 0;

			m_pVector[dwStorePos+dwCharSize-1].d.x= xMax  - ptEndPoint.x;
			/////////////////////////////////
			//������ ������ ���� �Ҽ� �ִ�.//
			/////////////////////////////////
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
			//m_pVector[dwStorePos].d.y -= yMin;     
			
			double tmpHeight= yMax-yMin;

			for(int k = (int)dwStorePos; k< (int)dwStorePos + (int)dwCharSize; k++)
			{   
				if(strData[i] ==  '0' && m_pVector[k].t == 4)
				   m_pVector[k].t = 1;
				if(iTotalline > 1)
				m_pVector[k].d.x = (int)(m_pVector[k].d.x* newXMag);//*0.813;(m_pVector_temp[i].d.x);
				else
				m_pVector[k].d.x = (m_pVector[k].d.x* newXMag);//*0.813;(m_pVector_temp[i].d.x);
				//m_pVector[k].d.x = (m_pVector[k].d.x* newXMag);//*0.813;(m_pVector_temp[i].d.x);
			}
			m_pVector[dwStorePos+dwCharSize -1].d.x += m_dLetterSpace;
			//m_pVector[dwStorePos+dwCharSize -1].d.y   -= yMin;
			
			  
			
		
			
		}
		else  // ���� ���̰� �ƴ� ��  
		{
			
			//------------------------Orginal---------------------------------------
			m_pVector[dwStorePos].d.x -= xMin;     
			m_pVector[dwStorePos+dwCharSize-1].d.x= xMax  - ptEndPoint.x;
			/////////////////////////////////
			//������ ������ ���� �Ҽ� �ִ�.//
			/////////////////////////////////
			CString tmpStr = strData[i];

			GetMinMaxinChar(strData[i],xMin,xMax,yMin,yMax);
			lDistance += (int)(m_dLetterSpace ) ;
			m_dwWidth = xMaxT-xMinT;
			//m_dwWidth = xMax-xMin;
			lDistance = long ( ( xMaxT-xMinT) - (xMax - xMin ) /*+ (m_dLetterSpace )*/ );
			DWORD dwVectorLength = GetVectorSize();
			double addsize;
			if(tmpStr == " ")
				addsize = (m_dCharSpace*0.8) - m_dwWidth; // 2006.03.09 ������ : EO S/W���� SPACEó��-> �������� ���Ҷ� 0.8�� �ɼǿ��� ���� *0.8�� FIX�س����� ����
			else
    			addsize = m_dCharSpace - m_dwWidth;
			//double addsize = ((m_dCharSpace*m_dwWidth)/378);
			double newXMag = (m_dwWidth+addsize)/m_dwWidth;
			double widthratio = m_dWidthScale;
			double xpoint,ypoint;
			xpoint =0; ypoint =0;
			double tmpHeight= yMax - yMin;

			for(int k = (int)dwStorePos; k< (int)dwStorePos + (int)dwCharSize; k++)
			{   
				if(strData[i] ==  '0' && m_pVector[k].t == 4)
				   m_pVector[k].t = 1;
				//if(tmpStr != " ")
				{
				if(iTotalline > 1)
				m_pVector[k].d.x = int(m_pVector[k].d.x* newXMag);//*0.813;(m_pVector_temp[i].d.x);
				else
				m_pVector[k].d.x = (m_pVector[k].d.x* newXMag);//*0.813;(m_pVector_temp[i].d.x);
				}
				
			}
					m_pVector[dwStorePos+dwCharSize -1].d.x += (int)m_dLetterSpace;
			
		}
		
		//���� ���ڿ����� ó���� �� ����
		if(m_pVector[dwStorePos].t & 0x10) //ĳ������ ù��°�� ���� ���� ǥ�ð� ������ ( �� ���� ĳ���� ���� ���� ���ڿ�����)
		{
			m_pVector[dwStorePos].t &= (~0x10);
			memmove( &m_pVector[dwStorePos+iLineCount], &m_pVector[dwStorePos], sizeof(Vector)* dwCharSize ); // ���๮�ڸ� ���� ���� ���� ���� ��ĭ�� �ڷ� �о��.
			
			/*for(int n = 0; n < dwStorePos+dwCharSize ; n++)
			{
				if(m_pVector[n].t & 0x10) 
				{
					
					continue;
				}
				m_pVector[n].d.y = m_pVector[n].d.y*1.2;	
			}
			*/
	
			
			
			GetMinMax(m_pVector,dwStorePos+dwCharSize,xMin,xMax,yMin,yMax);
			// ���������� ���� ���� ���͸� �����Ѵ�.
			
			
			GetMinMax(m_pVector,dwStorePos+dwCharSize,xMin,xMax,yMin,yMax);
			for( k = 0 ; k < iLineCount ; k++)
			{
				//m_pVector[dwStorePos+k].d.x = (int)m_pVector[dwStorePos+k].d.x;
				if( (m_dCharSpace >= ( xMax - xMin )) ||(iOrValue==0x10)  )
				{
					m_pVector[dwStorePos+k].d.x = 0; // ���� �󸶳� �����ϴ��� �𸣹Ƿ� 0���� ����
					//m_pVector[dwStorePos+k].d.x = m_pVector[0].d.x;
					
				}
				else
				{
					m_pVector[dwStorePos+k].d.x = (( xMax - xMin) - m_dCharSpace);
					//m_pVector[dwStorePos+k].d.x = (( xMaxT - xMinT) - m_dCharSpace);
					
				}
				
				
				if(m_dLetterHeight > 0)
					m_pVector[dwStorePos+k].d.y =  (-(m_dLineSpace + m_dLetterHeight  ));  // ������ ���̸�ŭ �Ʒ��� ���ϴ� ���Ͱ� �ȴ�.
				else
					m_pVector[dwStorePos+k].d.y =  (-(m_dLineSpace + m_dLetterHeight));  // ������ ���̸�ŭ �Ʒ��� ���ϴ� ���Ͱ� �ȴ�.
				
				m_pVector[dwStorePos+k].t = 0x02 | 0x10;
			}
			
			GetMinMax(m_pVector,dwStorePos+dwCharSize,xMin,xMax,yMin,yMax);
			double addsize = m_dTotalHeight - (yMax-yMin);	
			double tmpHeight= yMax - yMin;
			double newYMag = ((((double)1*(double)tmpHeight)+(double)addsize)/(double)tmpHeight);
			GetMinMax(m_pVector,dwStorePos+dwCharSize,xMin,xMax,yMin,yMax);
			
			//// ������� ���� ���� ó�� ���´� �̷���.
			///////     ABCD
			///////	        EFGH   �̷������� ���� ������ �̵����� ���� ����.
			
			
		}
		
		dwStorePos += (dwCharSize + iLineCount);
		//dwcurPos+=dwCharSize;
		iLineCount = 0;
		iLineMulti=0;
		iOrValue =0;
		
	}
	
	////////////////////////////////////////////////////////////////////////////////
	// �⺻ ó�� ���� �Ŀ� �ؾ��� ó����
	////////////////////////////////////////////////////////////////////////////////
	DWORD dwVectorLength = GetVectorSize();
	
	GetMinMax(m_pVector,dwVectorLength,xMin,xMax,yMin,yMax);

	

	//-----------------------------------------------------------------------------------------------------
	
	GetMinMax(m_pVector,dwVectorLength,xMin,xMax,yMin,yMax);
	
	CPoint point(0,0);
	
	//int iTotalline = GetTotalLine(strData);
	dwVectorLength = GetVectorSize();


	double addsize;
	//if( iTotalline > 0 )
	//{
	//	GetMinMax(m_pVector,dwVectorLength,xMin,xMax,yMin,yMax);
	//	m_pVector[0].d.y += (yMax - yMin - iCharHeight);
	//}
	
	point= CDPoint(0,0);
	/*
	if(iTotalline > 0)
	{
		if(yMax - yMin > m_dLetterHeight)
		{
			//addsize =   ((iTotalline+1)*m_dTotalHeight+(iTotalline*m_dLineSpace)) - (yMax-yMin);
			addsize =   (m_dTotalHeight) - (yMax-yMin);
			newYMag = (yMax-yMin+ addsize)/(yMax - yMin);
		}
		else
		{
			//addsize =   ((iTotalline+1)*m_dLetterHeight+(iTotalline*m_dLineSpace)) - (yMax-yMin);
			addsize =   (m_dLetterHeight) - (yMax-yMin);
			newYMag = (yMax-yMin+ addsize)/(yMax - yMin);
		}
	}
	else
	{
		if(yMax - yMin > m_dLetterHeight)
		{
			addsize = m_dTotalHeight - (yMax-yMin);
			newYMag = (yMax-yMin+ addsize)/(yMax - yMin);
		}
		else
		{
			addsize =   m_dLetterHeight - (yMax-yMin);
			newYMag = (yMax-yMin+ addsize)/(yMax - yMin);
		}
	}
	
	
	for(int n = 0; n < dwVectorLength ; n++)
	{
		//if(m_pVector[n].t & 0x10) 
		//{
		//	if(m_dLetterHeight > 0)
		//		m_pVector[n].d.y =  (-(m_dLineSpace + m_dLetterHeight  )) + xMin;  // ������ ���̸�ŭ �Ʒ��� ���ϴ� ���Ͱ� �ȴ�.
		//	else
		//		m_pVector[n].d.y =  (-(m_dLineSpace + m_dLetterHeight)) + xMin;  // ������ ���̸�ŭ �Ʒ��� ���ϴ� ���Ͱ� �ȴ�.
		//	continue;
		//}
		m_pVector[n].d.y = m_pVector[n].d.y*newYMag;	
	}
	
	
	*/
	
	DoAlign(); // ���� ( Middle, Left, Right ����)
	
	// �ۻ��� ũ�� ���� ����
	yMax = yMin + (iTotalline+1)*iCharHeight + (int)((iTotalline)*(m_dLineSpace));
	GetMinMax(m_pVector,dwVectorLength,xMin,xMax,yMin,yMax);
	
	
	//Save(m_pVector, dwVectorLength); //������.. .
	// ���� �迭 �ۼ�.
	if(TRUE!=m_bArcArray) 
	{
		//DWORD m_dwtmpWidth;
		double  m_dwtmpWidth;
		if( m_bEqualSpan == TRUE)
		{
			if(MaxstrLength > 1)
				m_dwtmpWidth = (((m_dCharSpace*MaxstrLength)+(m_dLetterSpace*(MaxstrLength-1)))-(xMax));
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
		//	m_pVector[0].d.y -=yMin;
		
		
	}
	else{
		DoArcArray();
		GetMinMax(m_pVector,dwVectorLength,xMin,xMax,yMin,yMax);
		m_dwWidth = xMax - xMin;
		m_dwHeight = yMax - yMin;
		
		if(m_dwHeight <= 0 )
			m_dwHeight = 1;
		m_pVector[0].d.x -=xMin; 
		//m_pVector[0].d.y -=yMin;
	}
	
	GetMinMax(m_pVector,dwVectorLength,xMin,xMax,yMin,yMax);
	//m_pVector[0].d.x -=xMin; 
	m_pVector[0].d.y -=yMin;

	//m_dwWidth = xMax - xMin;
	m_dwHeight = yMax - yMin;


	//-----------------------------------------------------------------------------------------------------

	return R_DEFAULT;

}
  


int CFontLoader::GetCharCenter(int index, CPoint point)
{
	int i, j, check = 0;
	int _max = -2147483647 , _min = 2147483647;

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
		case 10: // ĳ������ ��
			point += m_pVector[i].d;

			if (check == 0)
			{	// ���� �̸�
				for( j = index+1; j <= i; j++)
				{
					if (_max < point.x)
						_max = point.x;
					if (_min > point.x)
						_min = point.x;

					point += m_pVector[i].d;

					if (_max < point.x)
						_max = point.x;
					if (_min > point.x)
						_min = point.x;
				}
			}
			return (_min + (_max - _min)/2);
		case 18:// ���຤�� 
			return 0;
		default:

			if (m_pVector[i].t == 4)
			{
				if (_max < point.x)
					_max = point.x;
				if (_min > point.x)
					_min = point.x;

				point += m_pVector[i].d;

				if (_max < point.x)
					_max = point.x;
				if (_min > point.x)
					_min = point.x;
				check = 1;
			} else
				point += m_pVector[i].d;

			break;
		}
	}
	return (_min + (_max - _min)/2);
}


void CFontLoader::DoArcArray()
{  // ��ũ ��̸� ����.
	
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
	// ���� ���� �迭 �ۼ� �ϱ�

	dStartAngle = GetArcStartAngle();

	dRadius = GetArcRadius();
	
	dwVectorLength = GetVectorSize();
	ASSERT(dwVectorLength != 0 );
	{
		xmin = 999999;	ymin = 999999;
		xmax = -999999;	ymax = -999999;

		// ù��° ������ �ּҰ��� ���Ѵ�
		for (i = 0; i < (signed)dwVectorLength; i++)
		{
			// ���ڳ��̰ų� ���� ���� �̸�
			if (m_pVector[i].t == 10 || m_pVector[i].t == 18)
				break;
			
		}
		GetMinMax(m_pVector,i,xmin,xmax,ymin,ymax);
		
		// ��ĳ���͸� ��ư��
		p = m_pVector[0].d;

		// ���� ���� 
		dRadius = GetArcRadius(); // r/ tobj->Radius;
		pointr = dRadius;

		offsettheta = -((xmax - xmin) / dRadius - dStartAngle);
		
		l = ( xmax - xmin ) - GetCharCenter(0, p);
		theta1 = double(l /dRadius + offsettheta);		// �� ���� ȸ���� 

		temppoint.x =  (pointr + m_pVector[0].d.y)  * cos(theta1);
		temppoint.y =  (pointr + m_pVector[0].d.y)  * sin(theta1);


		temppoint.x = ( temppoint.x - (GetCharCenter(0, p) - m_pVector[0].d.x)* cos(theta1 - PI/2) );
		temppoint.y = ( temppoint.y - (GetCharCenter(0, p) - m_pVector[0].d.x)* sin(theta1 - PI/2) );


		c.x = temppoint.x;
		c.y = temppoint.y;

		m_pVector[0].d = c;

		// ���� ������ = lx - dy;
		for(i = 1; i < (signed)dwVectorLength; i++) 
		{
			switch (m_pVector[i].t)
			{
			case 10: // ĳ������ ��
				p.x += m_pVector[i].d.x; // �ҽ� ���� ��ġ
				p.y += m_pVector[i].d.y; // �ҽ� ���� ��ġ

				// ���� ������ ȸ�� ���� ����
				if (GetCharCenter(i, p) == 0)
				{	// ���� ������ ���� ��� 
					templong = m_pVector[i].d.x;
					m_pVector[i].d.x =  (double(cos(PI/2-theta1)) * double(m_pVector[i].d.x) + double(sin(PI/2-theta1))*double(m_pVector[i].d.y));
					m_pVector[i].d.y = (double(-sin(PI/2-theta1)) * double(templong)+ double(cos(PI/2-theta1))*double(m_pVector[i].d.y));

					c.x  += m_pVector[i].d.x ;
					c.y  += m_pVector[i].d.y ;
					break;
				} 

				l = (xmax - xmin ) - GetCharCenter(i, p); //+ 38;  //(xmax - xmin ) - p.x - tobj->CharSpace/2 ; // l - tobj->CharSpace;
				theta1 = double(l / dRadius + offsettheta);

				// �ʱ� ���� ����
				tempp = c;

				// ���� ���� ��ǥ ���ϱ�
				temppoint.x =  ((pointr + p.y) * cos(theta1));
				temppoint.y = ((pointr + p.y) * sin(theta1));

				temppoint.x =  ( temppoint.x - ( GetCharCenter(i, p) - p.x )*cos(theta1 - PI/2) );
				temppoint.y =  ( temppoint.y - ( GetCharCenter(i, p) - p.x )*sin(theta1 - PI/2) );

				c.x = temppoint.x; //pointr * cos(theta) + tempp.x - c.x;
				c.y = temppoint.y; //pointr * sin(theta) + tempp.y - c.y;

				m_pVector[i].d = c - tempp; // ���� ��ǥ �󿡼� �� ��ǥ ���� ���� ��ǥ ���� ���� ���ϱ�
				

				charcount++;
				break;
			case 18: // ���� ����
				p.x += m_pVector[i].d.x; // �ҽ� ���� ��ġ
				p.y += m_pVector[i].d.y; // �ҽ� ���� ��ġ
				// ���� ����
				lx = ((xmax - xmin ) - p.x);
				theta  = lx / dRadius + offsettheta;

				// ���� ���� ���� 
				temppoint = c;
//				pointr = pointr - charheight - tobj->LineSpace;
				c.x =  ( (pointr + p.y)  * cos(theta) );
				c.y = ( (pointr + p.y) * sin(theta) );
				m_pVector[i].d = c - temppoint;


				// �ʱ� ��ġ�� ���� ���� ����
				tempp =  p;
				i++;
				p.x += m_pVector[i].d.x; // �ҽ� ���� ��ġ
				p.y += m_pVector[i].d.y; // �ҽ� ���� ��ġ

				// ���� ����
				l = ( xmax - xmin ) - GetCharCenter(i, p);
				theta1 = double(l /dRadius + offsettheta);		// �� ���� ȸ���� 

				// �ʱ� ���� ����
				temppoint.x = ( (pointr + p.y) * cos(theta1) );
				temppoint.y = ( (pointr + p.y) * sin(theta1));

				temppoint.x = ( temppoint.x - (GetCharCenter(i, p) - p.x) * cos(theta1 - PI/2));
				temppoint.y =  ( temppoint.y - (GetCharCenter(i, p) - p.x) * sin(theta1 - PI/2));

				tempp = c;
				c = temppoint;

				m_pVector[i].d = c - tempp;
				
				break;
			default: // �⺻ ����
				p.x += m_pVector[i].d.x; // �ҽ� ���� ��ġ
				p.y += m_pVector[i].d.y; // �ҽ� ���� ��ġ

				// ������ŭ ��ȯ 
				templong = m_pVector[i].d.x;
				m_pVector[i].d.x =  int(double(cos(PI/2-theta1)) * double(m_pVector[i].d.x) + double(sin(PI/2-theta1))*double(m_pVector[i].d.y));
				m_pVector[i].d.y = int(double(-sin(PI/2-theta1)) * double(templong)               + double(cos(PI/2-theta1))*double(m_pVector[i].d.y));
				
				c.x += m_pVector[i].d.x;
				c.y += m_pVector[i].d.y;
				break;
			}

		}
		m_pVector[i-1].d.x = 0;
		m_pVector[i-1].d.y = 0;
		// �ۻ����� ũ�⸦ ���Ѵ�
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
	
				if(m_pVector[i].t==18) p.x = 0;
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

	m_dArcRadius= dRadius;
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
	
	int iTotalWidth = GetMaxWidth_LineFeed(m_pVector,dwLength);  //�ۻ��� �ִ���
	
	for ( i=0; i < (signed)dwLength ; i++)
	{
		ixMinT = iyMinT =0;
		ixMaxT = iyMaxT =0;
		iCurrentWidth = 0;
		point= CPoint(0,0);
		j=i;
	
		// �� ���� �ִ�, �ּ� ��ǥ�� ���Ѵ� ���̸� ���Ѵ�
		// ���� ���ڳ� �������� ���϶� ������ ���� ���´�
		for( ; i< (signed)dwLength; i++) 
		{
			if(m_pVector[i].t == 18) 
			// ���� �� �ϴ� ���Ͷ��
				break;
			//if(i >= (signed)dwLength -1) 
			{	// ������ ��ġ�� �������� ���� ��ġ�ų� �Ѿ��
				// j�� ������ ���� ����Ű�� ���� ���ڷ� �Ѿ� ���� 
				
		//		break; 
			}

			ixMinT = ( point.x < ixMinT ) ? point.x : ixMinT;
			iyMinT = ( point.y < iyMinT ) ? point.y : iyMinT;
			ixMaxT = ( point.x > ixMaxT ) ? point.x : ixMaxT;
			iyMaxT = ( point.y > iyMaxT ) ? point.y : iyMaxT;

			point.x += (int)m_pVector[i].d.x; // ��ǥ���� �� ������ x ��ġ 
			point.y += (int)m_pVector[i].d.y; // ��ǥ���� �� ������ y ��ġ

			// ĳ���� ���� �ִ�, �ּ� ��ǥ�� ���Ѵ�
			
			//TRACE(" i, x, y : %d, %d, %d; %d,%d\n",i,m_pVector[i].d.x,m_pVector[i].d.y,m_xmin, m_xmax);
		}
		ixMinT = ( point.x < ixMinT ) ? point.x : ixMinT;
		iyMinT = ( point.y < iyMinT ) ? point.y : iyMinT;
		ixMaxT = ( point.x > ixMaxT ) ? point.x : ixMaxT;
		iyMaxT = ( point.y > iyMaxT ) ? point.y : iyMaxT;
		iCurrentWidth = ixMaxT - ixMinT; // ������ ������ �ִ� �� 
		
		
		switch(m_dwAlignFlag)
		{
		case modeRIGHT:
			// �������̸� ���� ��ġ�� ��ü ������ ��
			// ���� ��ġ = ���� ��ġ - �������� ����
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
		if( m_pVector[i].t == 18) //����Ÿ�� �������� ���� ���๮�ڶ��
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
	
	CDPoint point = CPoint(0,0);
	

	for( i=0 ; i< (int)dwLength; i++ )
	{
	/*		point.x +=(long)pData[i].d.x;
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

UINT CFontLoader::LoadFont(CString strFileName) //��Ʈ�� �ε��Ѵ�.m_pFontHeader,m_pFontData,m_pFontIndex�� ���õ�.
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

	FontFile.ReadHuge(m_pFontData, m_dwFileSize);
	FontFile.Close();

	memcpy(m_pFontHeader, m_pFontData, HEADER_LENGTH);
	memcpy(m_pFontIndex, (m_pFontData +HEADER_LENGTH) , (INDEX_LENGTH*4));

	return R_DEFAULT;
}

UINT CFontLoader::LoadFont(BYTE *pFontData, DWORD dwByte) //ȭ�Ͽ��� ���� �ε����� �ʰ� 
{

	if(pFontData == NULL) return R_FAILED;

	ASSERT(pFontData != NULL);

	m_pFontData = new BYTE[dwByte];
	memcpy(m_pFontData, pFontData, dwByte);

	memcpy(m_pFontHeader, m_pFontData, HEADER_LENGTH);
	memcpy(m_pFontIndex, (m_pFontData +HEADER_LENGTH) , (INDEX_LENGTH*4));

	return R_DEFAULT;

}



Vector *CFontLoader::GetVectorData() // ������ ���͸� �����ش�.
{
	Vector *pVector = new Vector[m_dwVectorSize];
	memcpy( pVector, m_pVector, m_dwVectorSize * sizeof(Vector));
	return pVector;
}

DWORD CFontLoader::GetVectorSize()
{

	return m_dwVectorSize;
}


DWORD CFontLoader::GetTotalLine(CString strData) //strData�ȿ� �ִ� �� ���� ����, ���ڿ����� ���ӵ� ���ʹ� ���� �ʴ´�.
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
	m_dwVectorSize = dwSize;  // �����Ҷ� ��������� ũ�⵵ �����س���.


	pVector = new Vector[dwSize];
	return pVector;
}


DWORD CFontLoader::GetRequireVectorSpace(CString strData) //���� ���ڸ��� ���ͷ� ǥ���ϱ����� ���� ����Ʈ����.
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


DWORD CFontLoader::GetVectorCount(CString strData) //���� �迭 ������ � �ʿ������� ���
{
	DWORD dwTotalSpace,dwLine;

	dwLine = GetTotalLine(strData);

	dwTotalSpace = GetRequireVectorSpace(strData);
	// ������ ������ ������ ���̷� �ٲ۴�
	// ������ ���� + "\n"�� ���� + "\0"�� ���� = ������ ����
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
//�ش� �����¿��� 5����Ʈ�� ������ �����´�.
//������� pen,x��ǥ ,y��ǥ 
		pen = m_pFontData[dwDataOffset ]; // ���� ���´�.

		iX = m_pFontData[dwDataOffset + 2];   //X ��ǥ�� ���´�.
		iX <<= 8;
		iX += m_pFontData[dwDataOffset  + 1];

		iY = m_pFontData[dwDataOffset  + 4];  //Y ��ǥ�� ���´�.
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
	
	for (int i = 0; i < (int)dwNumberofVector; i++)
	{
		GetPositionData(dwDataOffset+dwReadPos,pen,iX,iY);
		m_pVector[pos+i].t = pen | orValue;
		m_pVector[pos+i].d.x = iX;
		m_pVector[pos+i].d.y = iY;
		orValue = 0;
		dwReadPos=dwReadPos + 5; // 5�� ����Ÿ�� �������ִ�.(Font ����) 
	}
	m_pVector[pos + i-1].t |= 0x08; // ������ ���Ϳ� ������ ���̶�� ǥ�� 
	
	return (dwNumberofVector); //��� ���Ͱ� ���Ǿ������� �����Ѵ�.
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
	   GetPositionData(dwDataOffset+i, chPen, iX, iY); //5����Ʈ�� �����´�.
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

// ���� �۾� 11.08 �������!!
void CFontLoader::GetMaxWidthHeightinFont(double &nWidth , double &nHeight)
{
	double iMinX, iMaxX, iMinY, iMaxY;
	GetMinMaxinFont(iMinX, iMaxX, iMinY, iMaxY);
	nWidth = iMaxX - iMinX;      // ���� �ʺ�.
	nHeight = iMaxY - iMinY;     // ���� ����.

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
