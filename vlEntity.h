// vlEntity.h: interface for the CvlEntity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VLENTITY_H__F44648AD_6457_11D6_8794_00C026664D59__INCLUDED_)
#define AFX_VLENTITY_H__F44648AD_6457_11D6_8794_00C026664D59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CvlEntity  
{
public:
	CvlEntity();
	CvlEntity(int nIndex);
	virtual ~CvlEntity();

public:
	int		m_iType;		//Entity Type, Line, Poly Line, Rectangle...
	int		m_hID;			//Graphic Object Identifier, Read Only
	int		m_iKey;			//Graphic Object Key, R/W
	int		m_iLayer;		//Layer Index of graphic object
	int		m_iStLine;		//Line Style Index
	int		m_iPage;		//Page Index of graphic object
    int		m_iLevel;
	int		m_iIndex;		//object's index
	
	int		m_iColor;		//Object color, if not by layer
	int		m_iFillColor;	//Object filling color, if not by layer
	int		m_iNoGrips;		//Number of grips in the entity

	double	m_dLineWidth;	//line width (if not by layer)
	double	m_dWidth;		//width of entity 
	double	m_dHeight;		//Height of entity 
	double	m_dLength;		//Entity's length or perimeter
	double	m_dArea;		//entity's area. for closed entities & open polylines have this value also
	
	double	m_dExtLeft;		//left extent of entity limits, Read Only
	double	m_dExtBottom;	//bottom extent of entity limits, Read Only
	double	m_dExtRight;	//right extent of entity limits, Read Only
	double	m_dExtTop;		//top extent of entity limits, Read Only
	
	BOOL	m_bSelect;		//entity's selection flag 
	BOOL	m_bVisible;		//entity's visibablity flag on screen 
	BOOL	m_bInBlock;		//is entity part of a block  definition
	BOOL	m_bDeleted;		//flag, entity is deleted
	BOOL	m_bFilled;		//Entity with filling”  for closed entities only
	BOOL	m_bBorder;		//Draw border”  for filled entities only
	BOOL	m_bOwnColor;	//flag, Entity has own color? not by layer.
	BOOL	m_bOwnFillColor;//flag, Entity has own filling color? not by layer 
	BOOL	m_bOwnLineWidth;//flag, Entity has own line width”  not by layer.
	BOOL	m_bMultiLine;	//flag "line style is multiline"

	void*	m_pExtObject;	//pointer to external object

public:
	void	Select(bool bSel);
	void	GetBasic();
	void	UpdateData(bool bSaveAndValidate);

	static CvlEntity* GetEntity(int nIndex);

public:

	virtual void Erase();
	virtual void Explode(int nLevel);
	virtual void Move(VLPOINT dOffset);
	void GetOuterRect(double* pdLeft, double* pdTop, double* pdRight, double* pdBottom);

	virtual void AddToCanvas() = 0;
	virtual bool Offset(double dSize) = 0;
	virtual bool Resize(VLPOINT dOrigin, double dRatioX, double dRatioY) = 0;
	virtual bool GetCenter(VLPOINT* pdCenter) = 0;

public:

	virtual const CvlEntity& operator = (const CvlEntity& Src);
};


class CvlPoint : public CvlEntity
{
public:

	CvlPoint();
	CvlPoint(int nIndex);
	~CvlPoint();


public:
	VLPOINT	m_dCoord;		//coordinate of point
	int		m_iStPoint;		//point type
	int		m_iGroup;		//point group
	char*	m_pszTxt;		//point text
	int		m_iLenTxt;		//text length (symbols)
	VLPOINT	m_dTxtOffset;	// point text offset
	double	m_dTxtAngle;	// point text angle
	double	m_dBlockAngle;	// rotation angle of block insertion
	BOOL	m_bFixed;		// flag, non-movable point

public:
	void UpdateData(bool bSaveAndValidate);
	virtual const	CvlPoint& operator = (const CvlPoint& Src);
	virtual void	AddToCanvas();
	virtual bool	Offset(double /*dSize*/){return true;}
	virtual bool	Resize(VLPOINT dOrigin, double dRatioX, double dRatioY);
	virtual bool	GetCenter(VLPOINT* pdCenter);
};

class CvlLine : public CvlEntity
{
	
public:
	CvlLine();
	CvlLine(int nIndex);

public:
	VLPOINT	m_dLine1;
	VLPOINT	m_dLine2;
	int		m_iArrow1;
	int		m_iArrow2;

public:
	void	MovePt2(double dX, double dY);
	void	MovePt1(double dX, double dY);
	void	UpdateData(bool bSaveAndValidate);
	virtual const	CvlLine& operator = (const CvlLine& Src);
	virtual void	AddToCanvas();
	virtual bool	Offset(double dSize);
	virtual bool	Resize(VLPOINT dOrigin, double dRatioX, double dRatioY);
	virtual bool	GetCenter(VLPOINT* pdCenter);

public:

	// µÎ Á÷¼±°£ÀÇ ±³Á¡ÁÂÇ¥
	static bool CalcIntersectPt(VLPOINT PtSrc1, VLPOINT PtSrc2, 
								VLPOINT PtDst1, VLPOINT PtDst2, 
								VLPOINT* pPtIntercept,
								bool	bLimit);

	// Á÷¼±°ú Á¡ÀÇ Á÷±³ÁÂÇ¥.
	static bool CalcIntersectPt(VLPOINT PtSrc1, VLPOINT PtSrc2, 
								VLPOINT PtDst,
								VLPOINT* pPtIntercept,
								bool	bLimit);
};

class CvlPoly : public CvlEntity
{	
public:
	CvlPoly();
	CvlPoly(int nIndex);

	~CvlPoly();
	
	void UpdateData(bool bSaveAndValidate);
	virtual const CvlPoly& CvlPoly::operator = (const CvlPoly& Src);
	virtual void AddToCanvas();
	virtual bool Offset(double dSize);
	virtual bool Resize(VLPOINT dOrigin, double dRatioX, double dRatioY);
	virtual bool GetCenter(VLPOINT* pdCenter);

	void	InsertVertex(int nIndex, VLPOINT Pt);
	bool	GetCOG(VLPOINT* pdCenter);

public:	
	
	BOOL		m_bClosed;
	int			m_iStSmooth;
	
	int			m_iArrow1;
	int			m_iArrow2;
	double		m_dVerRadius;
	int			m_iNoVer;
	int			m_iCurrVer;
	VLPOINT		m_dCurrVerCoord;	// coordinate of current vertex      	
	double		m_dCurrVerRadius;
	double		m_dCoeffBulge;		// bulge coefficient of current segment (for smooth=VL_POLY_BULGE) 
	BOOL		m_bCurrVerOn;		// VD_POLY_VER_ON    

	VLPOINT*	m_pdVert;
	
//	VL_POLY_LINE	

	// VD_POLY_GETVERS   vertexes array °¡ ¹»±î¿ä...
	// VD_POLY_SETVERS
	// VD_POLY_VER_INS
	// VD_POLY_VER_DEL
	// VD_POLY_VER_DATA  
	// VD_POLY_CUSTDATA  
protected:
	static bool FindLineEq(VLPOINT Pt1, VLPOINT Pt2, VLPOINT PtCenter, double dSize, double* pDstDelta, double* pDstSlice);
	static bool FindCoordDist(VLPOINT PtSrc1, VLPOINT PtSrc2, double Dist, VLPOINT *pPtDst);
	static bool FindCoordAngle(VLPOINT PtSrc1, VLPOINT PtSrc2, VLPOINT PtSrc3, /*VLPOINT PtCenter,*/ CRgn* pRgn, double Dist, VLPOINT *pPtDst);
};

class CvlRect : public CvlEntity
{
public:
	CvlRect();
	CvlRect(int nIndex);

public:
	VLPOINT	m_dCoord;
//	double	m_dWidth;
//	double	m_dHeight;
	double	m_dAngle;
	double	m_dRadius;

public:	
	void	UpdateData(bool bSaveAndValidate);
	virtual void	AddToCanvas();
	virtual bool	Offset(double dSize);	
	virtual bool	Resize(VLPOINT dOrigin, double dRatioX, double dRatioY);
	virtual bool	GetCenter(VLPOINT* pdCenter);

	virtual const	CvlRect& operator = (const CvlRect& Src);
};


class CvlCircle : public CvlEntity
{
public:

	CvlCircle();
	CvlCircle(int nIndex);
	~CvlCircle();

public:


	VLPOINT	m_dCoord;
	double	m_dRadius;

public:
	void	UpdateData(bool bSaveAndValidate);
	virtual const	CvlCircle& operator = (const CvlCircle& Src);
	virtual void	AddToCanvas();
	virtual bool	Offset(double dSize);
	virtual bool	Resize(VLPOINT dOrigin, double dRatioX, double dRatioY);
	virtual bool	GetCenter(VLPOINT* pdCenter);	
	virtual void	GetRect(double* pdLeft, double* pdTop, double* pdRight, double* pdBottom);
};


class CvlArc : public CvlEntity
{
public:
	CvlArc();
	CvlArc(int nIndex);
	~CvlArc();

public:

	VLPOINT	m_dCoordCenter;		//VD_ARC_X          VD_ARC_Y          
	VLPOINT	m_dCoordStart;		//VD_ARC_XS         VD_ARC_YS         
	VLPOINT	m_dCoordEnd;		//VD_ARC_XE         VD_ARC_YE   

	double	m_dRadius;			//VD_ARC_R          
	double	m_dStart;			//VD_ARC_START      
	double	m_dEnd;				//VD_ARC_END        
	int		m_iStArrow1;		//VD_ARC_ARROW1     
	int		m_iStArrow2;		//VD_ARC_ARROW2     
	double	m_dRadiusHorz;		//VD_ARC_RH 
	double	m_dRadiusVert;		//VD_ARC_RV         
	double	m_dAngleStart;		//VD_ARC_ANG0       
	double	m_dAngleInclude;	//VD_ARC_ANGARC     
	double	m_dAngleRotation;	//VD_ARC_ANGROT     
	BOOL	m_bIsSectorMode;	//VD_ARC_SECTOR     
	BOOL	m_bIsChordMode;		//VD_ARC_CHORD      

public:	
	void	UpdateData(bool bSaveAndValidate);
	virtual const	CvlArc& operator = (const CvlArc& Src);
	virtual void	AddToCanvas();
	virtual bool	Offset(double dSize);
	virtual bool	Resize(VLPOINT dOrigin, double dRatioX, double dRatioY);
	virtual bool	GetCenter(VLPOINT* pdCenter);
};

class CvlEllipse : public CvlEntity
{
public:
	CvlEllipse();
	CvlEllipse(int nIndex);
	~CvlEllipse();

public:

	VLPOINT m_dCoord;		//VD_ELLIPSE_X     VD_ELLIPSE_Y     
	double	m_dRadiusHorz;		//VD_ELLIPSE_RH    
	double	m_dRadiusVert;		//VD_ELLIPSE_RV    
	double	m_dAngle;			//VD_ELLIPSE_ANGLE 

public:
	void	UpdateData(bool bSaveAndValidate);

	virtual const	CvlEllipse& operator = (const CvlEllipse& Src);
	virtual void	AddToCanvas();
	virtual bool	Offset(double dSize);
	virtual bool	Resize(VLPOINT dOrigin, double dRatioX, double dRatioY);
	virtual bool	GetCenter(VLPOINT* pdCenter);
};


class CvlText : public CvlEntity
{
public:
	CvlText();
	CvlText(int nIndex);
	~CvlText();
public:

	VLPOINT m_dCoord;			
	char*	m_pszTxt;			
	int		m_iLength;			
	int		m_iStyle;			
	double	m_dHeight;			
	double	m_dWidthScale;		
	int		m_iAlign;			
	double	m_dAngleRotation;	
	double	m_dAngleOblique;	
	double	m_dIntervalHorz;	
	double	m_dIntervalVert;	
	BOOL	m_bIsPath;			
	BOOL	m_bIsStrikeOut;		
	BOOL	m_bIsUnderLine;		
	int		m_iNoLines;			
	int		m_iPathCurve;		
	VLPOINT	m_dCurveOrg;		    
	BOOL	m_bIsBackwardCurve;	
	BOOL	m_bIsAbsAngle;		
	
public:
	void	UpdateData(bool bSaveAndValidate);
	virtual const	CvlText& CvlText::operator = (const CvlText& Src);
	virtual void	AddToCanvas();
	virtual bool	Offset(double dSize);
	virtual bool	Resize(VLPOINT dOrigin, double dRatioX, double dRatioY);
	virtual bool	GetCenter(VLPOINT* pdCenter);
};

//Hatch
class CvlHatch : public CvlEntity
{
public:
	CvlHatch();
	CvlHatch(int nIndex);
	~CvlHatch();

public:
	int		m_iStyle; // index of hatch style
	double	m_dScale;// hatch's scale
	double	m_dAngle;// hatch's angle

public:
	void	UpdateData(bool bSaveAndValidate);
	virtual const	CvlHatch& CvlHatch::operator = (const CvlHatch& Src);
	virtual void	AddToCanvas();
	virtual bool	Offset(double dSize);
	virtual bool	Resize(VLPOINT dOrigin, double dRatioX, double dRatioY);
	virtual bool	GetCenter(VLPOINT* pdCenter);
};

//Block(VL_ENT_INSBLOCK)

class CvlBlock : public CvlEntity
{
public:
	CvlBlock();
	CvlBlock(int nIndex);
	~CvlBlock();

public:

	char	m_pszName[32];			//VD_BLOCK_NAME       
	double	m_dBlockWidth;		//VD_BLOCK_WIDTH      (RO)
	double	m_dBlockHeight;		//VD_BLOCK_HEIGHT     (RO)
	
	VLPOINT	m_dBlockBase;		//VD_BLOCK_XBASE      , VD_BLOCK_YBASE      
	VLPOINT	m_dPtInsertion;		//VD_INSBLK_X,Y
	int		m_iIndexBlockDef;	//VD_INSBLK_BLOCK   index of block definition 
	double	m_dAngle;			//VD_INSBLK_ANGLE   rotation angle
	double	m_dScaleX;			//VD_INSBLK_SCALEX  
	double	m_dScaleY;			//VD_INSBLK_SCALEY  	
	double	m_dScale;			//VD_INSBLK_SCALE   	

public:
	void UpdateData(bool bSaveAndValidate);
	virtual const CvlBlock& CvlBlock::operator = (const CvlBlock& Src);
	virtual void AddToCanvas();
	virtual bool Offset(double dSize);
	virtual bool Resize(VLPOINT dOrigin, double dRatioX, double dRatioY);
	virtual bool GetCenter(VLPOINT* pdCenter);
};



class CvlDim : public CvlEntity
{
public:
	int		m_iStyle;					//VD_DIM_STYLE   // dimension style
	int		m_iDimType;					//VD_DIM_TYPE	// RO dimension type 
	BOOL	m_bStatic;					//VD_DIM_STATIC  // flag "static value"
	char	m_szStaticValue[MAX_PATH];	//VD_DIM_VALUE   // value (if static)
	VLPOINT	m_dText;					//VD_DIM_XTEXT   VD_DIM_YTEXT // text point

public:
	CvlDim();
	CvlDim(int iIndex);
	~CvlDim();

public:
	void UpdateData(bool bSaveAndValidate);
	virtual const CvlDim& CvlDim::operator = (const CvlDim& Src);

	virtual void AddToCanvas();
};

// VL_ENT_DIMLIN
class CvlDimLinear : public CvlDim
{
public:
	VLPOINT	m_dPt1;		//VD_DIM_L_X1 VD_DIM_L_Y1      // first point//
	VLPOINT	m_dPt2;		//VD_DIM_L_X2 VD_DIM_L_Y2      // second point
	double	m_dOffset;	//VD_DIM_L_OFFSET  // offset of dim. line parallel offset of dimension line to line x1,y1,x2,y2
	VLPOINT	m_dPos;		//double VD_DIM_L_XLINE   VD_DIM_L_YLINE   // horizontal position of dimension line

public:

	CvlDimLinear();
	CvlDimLinear(int iIndex);
	~CvlDimLinear();

public:
	void	UpdateData(bool bSaveAndValidate);
	virtual const	CvlDimLinear& CvlDimLinear::operator = (const CvlDimLinear& Src);
	virtual void	AddToCanvas();

	virtual bool	Offset(double /*dSize*/){return true;}
	virtual bool	Resize(VLPOINT /*dOrigin*/, double /*dRatioX*/, double /*dRatioY*/){return true;}
	virtual bool	GetCenter(VLPOINT* /*pdCenter*/){return true;}

};

// VL_ENT_DIMANG
class CvlDimAngula : public CvlDim
{
public:

	VLPOINT	m_dPtCenter;	// VD_DIM_A_XCEN     VD_DIM_A_YCEN  // center point
	VLPOINT	m_dPt1;			// VD_DIM_A_X1       VD_DIM_A_Y1	// first point
	VLPOINT	m_dPt2;			// VD_DIM_A_X2       VD_DIM_A_Y2	// second point
	double	m_dRadius;		// VD_DIM_A_RADIUS   // radius for dimension arc

public:

	CvlDimAngula();
	CvlDimAngula(int iIndex);
	~CvlDimAngula();

public:
	void	UpdateData(bool bSaveAndValidate);
	virtual const	CvlDimAngula& CvlDimAngula::operator = (const CvlDimAngula& Src);
	virtual void	AddToCanvas();
	virtual bool	Offset(double /*dSize*/){return true;}
	virtual bool	Resize(VLPOINT /*dOrigin*/, double /*dRatioX*/, double /*dRatioY*/){return true;}
	virtual bool	GetCenter(VLPOINT* /*pdCenter*/){return true;}

};

// VL_ENT_DIMRAD
class CvlDimRadial : public CvlDim
{
public:

	VLPOINT	m_dPtCenter;	// VD_DIM_R_XCEN    VD_DIM_R_YCEN    // center point
	VLPOINT	m_dPtRadial;	// VD_DIM_R_XRAD       VD_DIM_R_YRAD // radial point
	double	m_dOffset;		// VD_DIM_R_OFFSET   // offset of dim line start

public:

	CvlDimRadial();
	CvlDimRadial(int iIndex);
	~CvlDimRadial();

public:
	void	UpdateData(bool bSaveAndValidate);
	virtual const	CvlDimRadial& CvlDimRadial::operator = (const CvlDimRadial& Src);
	virtual void	AddToCanvas();
	virtual bool	Offset(double /*dSize*/){return true;}
	virtual bool	Resize(VLPOINT /*dOrigin*/, double /*dRatioX*/, double /*dRatioY*/){return true;}
	virtual bool	GetCenter(VLPOINT* /*pdCenter*/){return true;}

};


// VL_ENT_DIMDIAM
class CvlDimDiameter : public CvlDim
{
public:
	VLPOINT		m_dPtCenter;	// VD_DIM_D_XCEN     VD_DIM_D_YCEN     // center point
	VLPOINT		m_dPtRadial;	// VD_DIM_D_XRAD     VD_DIM_D_YRAD     // radial point

public:

	CvlDimDiameter();
	CvlDimDiameter(int iIndex);
	~CvlDimDiameter();

public:
	void	UpdateData(bool bSaveAndValidate);
	virtual const	CvlDimDiameter& CvlDimDiameter::operator = (const CvlDimDiameter& Src);
	virtual void	AddToCanvas();
	virtual bool	Offset(double /*dSize*/){return true;}
	virtual bool	Resize(VLPOINT /*dOrigin*/, double /*dRatioX*/, double /*dRatioY*/){return true;}
	virtual bool	GetCenter(VLPOINT* /*pdCenter*/){return true;}

};


class CvlDimOrdinate : public CvlDim
{
public:

	VLPOINT	m_dPtOrdinate;	// VD_DIM_O_X  , VD_DIM_O_Y  // ordinate point
	BOOL	m_bShowOrdinateY;//VD_DIM_O_ORDY     // flag "Show Y ordinate"

public:

	CvlDimOrdinate();
	CvlDimOrdinate(int iIndex);
	~CvlDimOrdinate();

public:
	void	UpdateData(bool bSaveAndValidate);
	virtual const	CvlDimOrdinate& CvlDimOrdinate::operator = (const CvlDimOrdinate& Src);
	virtual void	AddToCanvas();

	virtual bool	Offset(double /*dSize*/){return true;}
	virtual bool	Resize(VLPOINT /*dOrigin*/, double /*dRatioX*/, double /*dRatioY*/){return true;}
	virtual bool	GetCenter(VLPOINT* /*pdCenter*/){return true;}

	
	
};

#endif // !defined(AFX_VLENTITY_H__F44648AD_6457_11D6_8794_00C026664D59__INCLUDED_)


