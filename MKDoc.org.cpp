// MKDoc.cpp : implementation of the CMKDoc class
//

#include "stdafx.h"
#include "MainFrm.h"

#include "MK.h"
#include "MKDoc.h"
#include "MKView.h"

#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMKDoc

IMPLEMENT_DYNCREATE(CMKDoc, CDocument)

BEGIN_MESSAGE_MAP(CMKDoc, CDocument)
	//{{AFX_MSG_MAP(CMKDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMKDoc construction/destruction

CMKDoc::CMKDoc()
{
	// TODO: add one-time construction code here
    TRACE("Called CMKCoc::CMKDoc() \n");
}

CMKDoc::~CMKDoc()
{
	for(int i=0;i<MAXOBJ;i++) {
		if(long(MKOBJ[i].hpgl_data)>long(0)) {
			delete [] MKOBJ[i].hpgl_data;
			MKOBJ[i].hpgl_data = NULL;
		}
	}
}

BOOL CMKDoc::OnNewDocument()
{
	int i;
	int Wx = (::GetSystemMetrics(SM_CXFULLSCREEN) -325 )/2; 
	int Wy = ::GetSystemMetrics(SM_CYFULLSCREEN) / 2 ; 
	m_sizeDoc=CSize(Wx,Wy);
	if (!CDocument::OnNewDocument())
		return FALSE;
	CMKView *pView;
	POSITION pd;
	pd=GetFirstViewPosition();
	pView=(CMKView*)GetNextView(pd);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	pView->SELECTED_OBJ = -1;
	pView->ScreenZoom   = float(.1);
	pView->ScreenOffset = CPoint(Wx, Wy);
	pView->m_nPressed = 0;	
	Unit = 0;

	InitErrorMessage();
	
	for(i=0;i<MAXOBJ;i++) {
		if(long(MKOBJ[i].hpgl_data)>long(0)) {
			delete [] MKOBJ[i].hpgl_data;
			MKOBJ[i].hpgl_data = NULL;
		}
		MKOBJ[i].type=(i+1)%2;

		MKOBJ[i].DontCare=0;
		MKOBJ[i].High=0;
		MKOBJ[i].Low=0;
		MKOBJ[i].MaxChar=256;
		MKOBJ[i].Align=MIDDLE;
		MKOBJ[i].ObjStr.Format("O\n%dTEST\n23",i);
		MKOBJ[i].Width = float(100+i*10);
		MKOBJ[i].Height= float(100+i*10);
		if(i>0) MKOBJ[i].X = Wx-MKOBJ[i].Width+50*i;
		else	MKOBJ[i].X = 0;//Wx-MKOBJ[i].Width;

		MKOBJ[i].Y = float(i);// + MKOBJ[i].Height;

		MKOBJ[i].DataName.Format("String of DataName of OBJ #%d",i);

		MKOBJ[i].Xmag = 1.0;
		MKOBJ[i].Ymag = 1.0;
		MKOBJ[i].fxratio = 1.0; // Field Ratio of X-Axis
		MKOBJ[i].fyratio = 1.0; // Fiels Ratio of Y-Axis
		MKOBJ[i].Angle   = 0;
		MKOBJ[i].Inclinde= 0;
		MKOBJ[i].RadialFlag = 0;
		MKOBJ[i].Radius  = 0; 
		MKOBJ[i].Stangle = 0; 
		MKOBJ[i].vrbfnt  = 1;
		MKOBJ[i].fntsize = 0;
		MKOBJ[i].wf      = 0; // width factor
		MKOBJ[i].LineSpace = 1;
		MKOBJ[i].CharSpace = 1;
		MKOBJ[i].Scribe    = 1;
		MKOBJ[i].number    = i;
		MKOBJ[i].f_w= 1;
		MKOBJ[i].fname.Format("font\\intl240p.fnt");
		MKOBJ[i].nhpd  = 0; // number of hpgl data list
		MKOBJ[i].mark  = 1;
		MKOBJ[i].stv   = 1;
		MKOBJ[i].edv   = 1;

/*
		MKOBJ[i].hpgl_data = new Vector[10]; // hpgl data list
		MKOBJ[i].hpgl_data[0].t = 02;
		MKOBJ[i].hpgl_data[0].d.x = 300+i*50;
		MKOBJ[i].hpgl_data[0].d.y = 100;
		for(int k=1;k<4;k++) {
			MKOBJ[i].hpgl_data[k].t = 04;
			MKOBJ[i].hpgl_data[k].d.x  = 5;
			MKOBJ[i].hpgl_data[k].d.y  = 5;
		}
		for(    k=4;k<7;k++) {
			MKOBJ[i].hpgl_data[k].t = 04;
			MKOBJ[i].hpgl_data[k].d.x  = 5;
			MKOBJ[i].hpgl_data[k].d.y  =-5;
		}
		for(    k=7;k<10;k++) {
			MKOBJ[i].hpgl_data[k].t = 04;
			MKOBJ[i].hpgl_data[k].d.x  =-5;
			MKOBJ[i].hpgl_data[k].d.y  = 0;
		}
*/
		MKOBJ[i].hpgl_data=NULL;
		if(MKOBJ[i].type==STEXT) OnLoadFont(&MKOBJ[i]);
	}
	return TRUE;
}

void CMKDoc::OnLoadFont(defobj * tobj) 
{
	CFile f;
	CFileException e;
	CString str;
	int charspace = 150;
	int linespace = 150;
	unsigned long i,j,t,it;
//	int j,k;
	int HeaderLEN=102;
	int IndexLEN=256*2;
	int  m_xmin,  m_xmax,  m_ymin,  m_ymax;
	int    xmin,    xmax,    ymin,    ymax;
	int subxmin, subxmax, subymin, subymax;
	int ifsize;
	CPoint p,c;	

	DWORD FileSize;
	BYTE  * pdata;
	BYTE  * pheader = new BYTE [HeaderLEN];
	DWORD * pindex  = new DWORD[IndexLEN];
	CString fname;
	

	fname.Format("%s",tobj->fname);
	if( !f.Open( fname, CFile::modeRead, &e )){
		#ifdef _DEBUG
			afxDump << "File could not be opened " << e.m_cause << "\n";
		#endif
	}

	FileSize = f.GetLength();
	pdata = new BYTE[FileSize];
	f.ReadHuge(pdata, FileSize);
	f.Close();
	memcpy(pheader,&pdata[0],HeaderLEN-1);
	memcpy(pindex,&pdata[HeaderLEN],(IndexLEN*4));
	memcpy(&tobj->fts,(void *)&pdata[8],2);
///////////////////////// Vector set
	char *chs = new char[255];
	int d_length=0;
	int idx,no,strl,newline;
	short bt2;
	unsigned char func;
	int check=1;
	int ttotwidth, tcurwidth, tprewidth, ttmpwidth;
//	double tmptheta, dtheta, r, PI, ppx, ppy, dx;
//	long prei;
//	PI = 3.1415926535;

	ifsize = (int) (((float)pdata[100])*35.3) ;
	str.Format(" %d ",ifsize);

	sprintf(chs,"%s",tobj->ObjStr);
	strl = strlen(chs);
	newline = 0;
	for( i=0;i<unsigned long(strl);i++) {
		if((chs[i]=='\n')||(chs[i]=='\r')) {newline++; continue;}
		idx = pindex[int(chs[i])*2];
		no  = pindex[int(chs[i])*2+1];
		d_length+=no;
	}
	d_length=d_length/5 + newline;
	if(tobj->hpgl_data!=NULL){
		delete [] tobj->hpgl_data ;
		tobj->hpgl_data=NULL;
	}
	tobj->hpgl_data = NULL;

	tobj->hpgl_data = new Vector[d_length];
	tobj->nhpd = d_length;
	t=0;
//	tmptheta = dtheta = 0; prei = 0;
//	tmptheta = PI / 2 ;
//		p = CPoint(0,0);	
//		c = CPoint(0,0);
	newline = 0;
	for(i=0;i<unsigned long(strl);i++) {
		if(t>=d_length) 
		{
			AfxMessageBox("Error : Array excess denied...!",MB_OK,0);
			break;
		}
		if(chs[i]==NULL) continue;
		if((chs[i]=='\n')||(chs[i]=='\r')) { newline=1; continue; }
		idx = pindex[int(chs[i])*2];
		no  = pindex[int(chs[i])*2+1];
		subxmin = 32766; subymin = 32766;
		subxmax =-32766; subymax =-32766;
		it = t;
		p = CPoint(0,0);	
		c = CPoint(0,0);
		for(j=0;j<no;) {
			func = pdata[idx+j];
			if( newline ) { tobj->hpgl_data[t].t = (func|0x10);  newline = 0; } // newline
			else			 tobj->hpgl_data[t].t = func;
			
			bt2  = pdata[idx+j+2];
			bt2<<= 8;
			bt2 += pdata[idx+j+1];
			tobj->hpgl_data[t].d.x = bt2 ;

			bt2  = pdata[idx+j+4];
			bt2<<= 8;
			bt2 += pdata[idx+j+3];
			tobj->hpgl_data[t].d.y = bt2 ;
/// 1st step for trim out area space
			p.x += tobj->hpgl_data[t].d.x;
			p.y += tobj->hpgl_data[t].d.y;
			if((tobj->hpgl_data[t].t==04)||(tobj->hpgl_data[t].t==20)) {
				subxmin = ( p.x < subxmin ) ? p.x : subxmin;
				subxmax = ( p.x > subxmax ) ? p.x : subxmax;
				subymin = ( p.y < subymin ) ? p.y : subymin;
				subymax = ( p.y > subymax ) ? p.y : subymax;
			}
/// end of 1st step .....
			j+=5;
			t++;
		}
		tobj->hpgl_data[t-1].t |= 0x08;  // endofchar bx1000

		c = CPoint(0,0);	
		for(j=it;j<t;j++){
			c.x += tobj->hpgl_data[j].d.x;
			c.y += tobj->hpgl_data[j].d.y;
		}
//////////////////////////////////////////////////////////////
		if(tobj->vrbfnt) 
		{
		// if set horizontal same distance array mode //450
			tobj->hpgl_data[it ].d.x -= subxmin ;
			tobj->hpgl_data[t-1].d.x -= (c.x - subxmax) ;
//			if(i!=0)
			tobj->hpgl_data[it ].d.x += (450 - (subxmax - subxmin)) / 2;
//			if(i<long(strl-1))
			tobj->hpgl_data[t-1].d.x += (450 - (subxmax - subxmin)) / 2;

		} else {
		// if not set horizontal same distance array mode
			tobj->hpgl_data[it ].d.x -= subxmin;
			tobj->hpgl_data[t-1].d.x -= (c.x - subxmax);
		}
		TRACE(" subxmin, subxmax = %d, %d \n",int(subxmin), int(subxmax));
//////////////////////////////////////////////////////////////
		TRACE(" t : %d ", tobj->hpgl_data[it].t);
		if(tobj->hpgl_data[it].t&0x10) {         
//			if(check)
//			tobj->hpgl_data[it-1].d.x -= charspace;
			for(j=t;j>it;j--) {
				tobj->hpgl_data[j].t   = tobj->hpgl_data[j-1].t;
				tobj->hpgl_data[j].d.x = tobj->hpgl_data[j-1].d.x;
				tobj->hpgl_data[j].d.y = tobj->hpgl_data[j-1].d.y;
			}
			//tobj->hpgl_data[it].t = 18;
			func = tobj->hpgl_data[it+1].t;
			tobj->hpgl_data[it+1].t = func&(~0x10) ;
			TRACE(" [it+1].t : %d \n", tobj->hpgl_data[it+1].t);
			tobj->hpgl_data[it].d.x = 0;
			tobj->hpgl_data[it].d.y -= (linespace+subymax);
//			tobj->chrHeight = subymax;
//			tobj->chrWidth  = submax-submin ;
			t++;
		}
		//else if( (i!=0) && (i<long(strl)) ) 
//			tobj->hpgl_data[it ].d.x += charspace;
	}
	tobj->nhpd = t;
/*
	if(tobj->RadialFlag) {
		p = CPoint(0,0);	
		c = CPoint(0,0);	
		r  = tobj->Radius;
		for(i=0;i<tobj->nhpd;i++){
			if( (i==0) || (tobj->hpgl_data[i].t==03) ) {
				dx = 450;
				dtheta = dx / r;
				tmptheta -= dtheta;
				ppx = r*sin(tmptheta);
				ppy = r*cos(tmptheta);
				tobj->hpgl_data[i].d.x += - c.x + ppx;
				tobj->hpgl_data[i].d.y += - c.y + ppy;
				p = c;
			}
			c.x += tobj->hpgl_data[i].d.x;
			c.y += tobj->hpgl_data[i].d.y;
		}
	}
*/

	newline = 0;
	for(i=0;i<tobj->nhpd;i++) 
		if(tobj->hpgl_data[i].t == 18) {newline=1; break;}
/*		p.x += tobj->hpgl_data[i].d.x;
		p.y += tobj->hpgl_data[i].d.y;
		xmin = ( p.x < xmin ) ? p.x : xmin;
		ymin = ( p.y < ymin ) ? p.y : ymin;
		xmax = ( p.x > xmax ) ? p.x : xmax;
		ymax = ( p.y > ymax ) ? p.y : ymax;
	}

*/	if(newline) i = i;
	else        i = 0;

	p = CPoint(0,0);	
	xmin = 32766; ymin = 32766;
	xmax =-32766; ymax =-32766;
	for(;i<tobj->nhpd;i++){
//		if(i>=tobj->nhpd) break;
		p.x += tobj->hpgl_data[i].d.x;
		p.y += tobj->hpgl_data[i].d.y;
		xmin = ( p.x < xmin ) ? p.x : xmin;
		ymin = ( p.y < ymin ) ? p.y : ymin;
		xmax = ( p.x > xmax ) ? p.x : xmax;
		ymax = ( p.y > ymax ) ? p.y : ymax;
//		if(tobj->hpgl_data[i].t==18) p.x =(xmax-xmin);  
	}
	tobj->hpgl_data[0].d.y+=(ymax-ymin)+linespace;
/*
	p = CPoint(0,0);	
	xmin = 32766; ymin = 32766;
	xmax =-32766; ymax =-32766;
	for(i=0;i<tobj->nhpd;i++){
		p.x += tobj->hpgl_data[i].d.x;
		p.y += tobj->hpgl_data[i].d.y;
		xmin = ( p.x < xmin ) ? p.x : xmin;
		ymin = ( p.y < ymin ) ? p.y : ymin;
		xmax = ( p.x > xmax ) ? p.x : xmax;
		ymax = ( p.y > ymax ) ? p.y : ymax;
		if(tobj->hpgl_data[i].t==18) p.x = (xmax-xmin);  
	}
	ttotwidth = m_xmax - m_xmin;

	tprewidth = 0;
	p = CPoint(0,0);	
	xmin = 32766; ymin = 32766;
	xmax =-32766; ymax =-32766;
	newline=1;
	for(i=0;i<tobj->nhpd;i++) {
		if((tobj->hpgl_data[i].t==18)||newline) {
			c = CPoint(0,0);
			m_xmin = m_ymin = 32766;
			m_xmax = m_ymax =-32766;
			tcurwidth = 0;
			if(newline) j=i;
			else        j=i+1;
			for(;j<tobj->nhpd;j++) {
				if( (tobj->hpgl_data[j].t==18) || (j>=tobj->nhpd) ) break;
				c.x += tobj->hpgl_data[j].d.x;
				c.y += tobj->hpgl_data[j].d.y;
				m_xmin = ( c.x < m_xmin ) ? c.x : m_xmin;
				m_ymin = ( c.y < m_ymin ) ? c.y : m_ymin;
				m_xmax = ( c.x > m_xmax ) ? c.x : m_xmax;
				m_ymax = ( c.y > m_ymax ) ? c.y : m_ymax;
				tcurwidth = m_xmax - m_xmin;
			}
			switch(tobj->Align){
			case RIGHT :
				tobj->hpgl_data[i].d.x-= tprewidth;
				tobj->hpgl_data[i].d.x+= ttotwidth;
				tobj->hpgl_data[i].d.x-= tcurwidth;
				break;
			case MIDDLE :
				if(newline) {
					tobj->hpgl_data[i].d.x-= tprewidth;
					tobj->hpgl_data[i].d.x+= ttotwidth/2;
					tobj->hpgl_data[i].d.x+= tcurwidth/2;
					ttmpwidth = ttotwidth/2 + tcurwidth/2 - tprewidth;
				} else {
					tobj->hpgl_data[i].d.x-=ttmpwidth;
					tobj->hpgl_data[i].d.x-=tprewidth;
//					tobj->hpgl_data[i].d.x-= ttotwidth/2;
//					tobj->hpgl_data[i].d.x-= tcurwidth/2;
				}
				break;
			case LEFT :
			default   :
				tobj->hpgl_data[i].d.x-= tprewidth;
			}
			p    = CPoint(0,0);
			xmin = 32766;
			xmax =-32766;
			newline = 0;
		}
		p.x += tobj->hpgl_data[i].d.x;
		p.y += tobj->hpgl_data[i].d.y;
		xmin = ( p.x < xmin ) ? p.x : xmin;
		ymin = ( p.y < ymin ) ? p.y : ymin;
		xmax = ( p.x > xmax ) ? p.x : xmax;
		ymax = ( p.y > ymax ) ? p.y : ymax;
		tprewidth = xmax - xmin;
	}
*/
	p = CPoint(0,0);	
	xmin = 32766; ymin = 32766;
	xmax =-32766; ymax =-32766;
	for(i=0;i<tobj->nhpd;i++) {
		p.x += tobj->hpgl_data[i].d.x;
		p.y += tobj->hpgl_data[i].d.y;
		if(tobj->hpgl_data[i].t==18) p.x = 0;  
		xmin = ( p.x < xmin ) ? p.x : xmin;
		ymin = ( p.y < ymin ) ? p.y : ymin;
		xmax = ( p.x > xmax ) ? p.x : xmax;
		ymax = ( p.y > ymax ) ? p.y : ymax;
	}
	tobj->Width = float(xmax - xmin);
	tobj->Height= float(ymax - ymin);
//	tobj->chrHeight = tobj->Height;
//	tobj->chrWidth  = tobj->Width / strl;
//	tobj->hpgl_data[0].d.y-=ymin;
//////////////////////////
	delete [] pdata;
	delete [] pheader;
	delete [] pindex;
	delete [] chs;
	pdata  = NULL;
	pheader = NULL;
	pindex = NULL;
	chs = NULL;
}

void CMKDoc::SetScreenSize(int width, int height){
	m_sizeDevice = CSize(width,height);
};
CSize CMKDoc::GetScreenSize(){
	return m_sizeDevice;
};

/////////////////////////////////////////////////////////////////////////////
// CMKDoc serialization

void CMKDoc::Serialize(CArchive& ar)
{
//	m_stringArray.Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << MKOBJ[0].DataName;
	}
	else
	{
		// TODO: add loading code here
		ar >> MKOBJ[0].DataName;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMKDoc diagnostics

#ifdef _DEBUG
void CMKDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMKDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMKDoc commands

void CMKDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
}

void CMKDoc::InitErrorMessage() 
{
	for(int i=0;i<10;i++)
		Error[i] = 	" Select OBJECT ";
}
