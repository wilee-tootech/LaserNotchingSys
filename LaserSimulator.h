#pragma once


#include "afxwin.h"
#include <time.h>
#include <list>
#include <vector>
#include "chartdir.h"
#include "ChartViewer.h"
#include <math.h>


// CLaserSimulator 대화 상자입니다.

#define TIMER_DRAW_SIMUL 1
#define FIRST_SHOW_GRAPH 2

enum NotchingState {Flag,Unflag};
enum LaserState { Off,On};

struct Vector2
{
	double x;
	double y;

	Vector2():x(0),y(0){};
	Vector2(double px, double py):x(px),y(py){};


	Vector2 operator= (Vector2 rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}


	Vector2 operator+ (Vector2 rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2 operator- (Vector2 rhs)
	{
		return Vector2(x - rhs.x,y - rhs.y);
	}

	Vector2 operator* (double d)
	{/*
		x *= d;
		y *= d;

		return *this;*/

		return Vector2(x * d, y  *d);
	}


	Vector2 Normalize()
	{
		double c = sqrt(x * x  + y * y);
		if(c == 0.0)
		{
			return Vector2(0,0);
		}

		return Vector2(x/c,y/c);
	}

	Vector2 Move(Vector2 vec)
	{
		x += vec.x;
		y += vec.y;

		return *this;
	}

	double Dot(Vector2 vec)
	{
		return x*vec.x + y*vec.y;
	}

	void SetPos(double dx,double dy)
	{
		x = dx;
		y = dy;
	}

	static double Distance(Vector2 a, Vector2 b)
	{
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}


};

struct PatternData
{
	Vector2 pos;
	double speed;
	bool isWait;
	double encoderAmount;
	NotchingState state;
	LaserState laserState;

	PatternData(Vector2 p,double sp, bool wait,double encoder,NotchingState s,LaserState ls)
	{
		pos = p;
		speed = sp;
		isWait = wait;
		encoderAmount = encoder;
		state = s;
		laserState = ls;
	}

	void setData(Vector2 p,double sp, bool wait,double encoder,NotchingState s,LaserState ls)
	{
		pos = p;
		speed = sp;
		isWait = wait;
		encoderAmount = encoder;
		state = s;
		laserState = ls;
	}




};




class CLaserSimulator : public CDialogEx
{
	DECLARE_DYNAMIC(CLaserSimulator)

public:
	CLaserSimulator(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLaserSimulator();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_LASER_SIMULATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	Vector2 m_vLaserPos;
	Vector2 m_vDir;
	double m_dLaserSize;
	double m_dLaserSpeed;


	int m_nBoundaryWidth;
	int m_nBoundaryHeight;
	int m_nNotchAreaHeight;


	double m_dZoomScale;
	double m_dPoleWidth;
	double m_dPoleHeight;
	clock_t t_LastTime;


	double m_dCenterX;
	double m_dCenterY;
	

	bool isSimulate;
	double m_dEncoder;
	double m_dTotalEncoder;
	double m_speedDiv; // 1 / m_spedDiv의 배속으로 플레이

	double m_dCurrRollSpeed;

	std::list<PatternData> dataList;
	std::list<PatternData>::iterator iter;

	std::list<Vector2> bmwLaserSimulPoints;
	std::vector<double> patternDataX,patternDataY;
	int count;

	bool bRTCIsReady;


	DECLARE_MESSAGE_MAP()
public:
	int m_nFLagRollSpeed;
	int m_nUnflagRollSpeed;
	int m_nFlagToUnflagAcc;
	int m_nUnflagToFlagDec;


	void CalculateLaserPointerPos(double deltaTime);
	void StopLaserSimulation();



	
	void DrawLaserArea(CChartViewer* viewer);
	virtual BOOL OnInitDialog();
//	afx_msg void OnPaint();
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_EVENTSINK_MAP()

	void ClickCtpushSimulstart();
	CChartViewer m_LaserViewer;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void ClickCtpushSimulstop();
	void ClickCtpushSimulGuideOnly();
	bool MakeSimulateDate();
	void MakeRealPatternData();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void FirstShowGrapbh(CChartViewer* viewer);
	double QuadraticFormulaForSimul(double a,double b,double c);
	double CalculateLaserTime(double laserSpeed,double rollSpeed, double x,double y);
};
