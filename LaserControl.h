// LaserControl.h: interface for the CLaserControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LASERCONTROL_H__1F97C0A4_0F90_4E96_8195_15895DA6433D__INCLUDED_)
#define AFX_LASERCONTROL_H__1F97C0A4_0F90_4E96_8195_15895DA6433D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Communicate.h"

class CLaserControl
{
public:
	CLaserControl();
	virtual ~CLaserControl();
	
	virtual void SetShutter(BOOL m_shutter);
	virtual BOOL GetShutter();

	/* �ڵ� On/Off ���� Method�� ���� ����ϴ� Concrete Class�� �������̵� */
	virtual UINT AutoOn(); /* AutoOnOff �κ��� �׻� �ٲ� �� ����, ��ӹ޴� �ֵ� ���� ��ü��Ű�� */
	virtual UINT AutoOff();
	virtual UINT ShutterOn()=0;
	virtual UINT ShutterOff()=0;
	virtual UINT CurrentControl(double dCurrent)=0;
	virtual double GetCurrent()=0;
	virtual int	 GetMode();
	virtual char *GetStatus()=0;
	virtual int	 GetOnStatus();
	virtual void SetIsReceived(int iReceived);
	virtual void SetIsBreak(int iBreak);
	virtual void SetIsProceedOn(BOOL bIsProceedOn);
	virtual char *GetReceivedCurrent();
	virtual char *GetTemperature();
	virtual char *GetLampCurrent();
	virtual char *GetInterLockMessage();
	virtual BOOL GetIsAutoOn();
	virtual BOOL GetIsConnect();
	virtual BOOL GetIsProceedOn();
	virtual UINT ChangeMode(int modeNumber);
	virtual BOOL SetConfigComPort(int Boaud, int Parity, int stopbit);

	
	
	/* Power ��, ���� ���� Method�� ���⼭ ���� */
	virtual UINT PowerMeasurement(CCommunicate *pComm, BOOL m_flag);
	virtual UINT PowerAdjustment(CCommunicate *pComm,BOOL m_flag);	
//	virtual UINT PowerMeasurementEnd(CCommunicate *pComm);
	virtual void    SetAperture(double dAperture); /* Aperture�� user�� �Է��ϵ��� ���� �����ϱ� */
	virtual double  GetAperture();
	virtual void    SetDate(CString strDate); /* Date�� user�� �Է��ϵ��� ���� �����ϱ� */
	virtual CString GetDate();
	virtual void	SetPMUShutter(BOOL bIsPMUShutterOn);
	virtual BOOL	GetPMUShutter();
	virtual BOOL	GetAutoPowerAdjustment();
	virtual void	SetAutoPowerAdjustment(BOOL bIsAutoPowerAdjutment);
	virtual void    SetSetPower(double dSetPower);
	virtual double  GetSetPower();
	virtual void    SetMeasuredPower(double dMeasuredPower);
	virtual double  GetMeasuredPower();

	/* Laser Control ���� ������ �����ع����� */
	virtual void UnSerialize(char *pstrSerial);
	virtual char *Serialize(DWORD &dwLength);

	/* Instance ���� */
	static CLaserControl *GetInstance(CLaserControl *pLaserControl);
	static CLaserControl *GetInstance();

	enum VariableLaserControlID {
		ID_SET_POWER = 10000,
		ID_MEASURED_POWER = 10001,
		ID_APERTURE = 10002,
		ID_CURRENT = 10003,
		ID_DATE = 10004
	};

protected:
	int		m_iMode;
	BOOL	m_bMainPower;
	BOOL	m_bIsShutterOn;
	BOOL	m_bIsPMUShutterOn;
	BOOL	m_bIsAutoPowerAdjutment;
	double	m_dSetPower;
	double  m_dMeasuredPower;
	double  m_dAperture;
	double	m_dCurrent;
	CString m_strDate;

private:
	static CLaserControl *m_pLaserControl; // ������ instance

	/* �� Util */
	void SetDelayTime(unsigned int iSecond);
};

#endif // !defined(AFX_LASERCONTROL_H__1F97C0A4_0F90_4E96_8195_15895DA6433D__INCLUDED_)
