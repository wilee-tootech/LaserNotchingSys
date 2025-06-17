#pragma once

struct SingleScannerParameter
{                                      //����
	double flagSpeed;                  // mm/s // Ŀ�ý��ǵ� �ʱⰪ
	double flagExtSpeed;               // mm/s
	double flagLineSpeed;               // mm/s

	double nonflagLineSpeed;           // mm/s
	double nonflagLineExtSpeed;		   // mm/s
	double nonflagInoutSpeed;		   // mm/s
	double nonflagInoutExtSpeed;	   // mm/s
	double jumpSpeed;                  // mm/s

	double laserOnDelay;			   // us
	double laserOffDelay;              // us
	double markDelay;                  // us
	double markSpeed;
	double jumpDelay;                  // us
	double polygonDelay;			   // us

	double firstflagLineExt;			//mm
	double flagLineExt;					//mm
	double cycleOffset;				//mm
	//double nonflagOffsetR;			//mm
	double startExtLen;				//mm

	double flagPower;
	double nonflagPower;
	double arcPower;

	double flagFreq;
	double nonflagFreq;
	double arcFreq;

	double pulsewidth;

	double flagOffset; // 240502 jyh
	
	double xOffset;
	double yOffset;

	double EncoderOffset;

	double notchOffset;

	double ngLength;

	double dCuttingOffset;

	double dMinFlagLeng;
	double dNGSensorLeng; // ������ ������ ������ ������� ���̰Ÿ�

	double dACSensorLeng;

	double dPatternShift; // 1ȸ ������ ���� ������ ���ܺ���ġ ���� ��

	double dPlcOffset;

	 // ��� ���� �ʱ�ȭ
	void clear()
	{
		flagSpeed = 0;flagExtSpeed=0;flagLineSpeed=0;nonflagLineExtSpeed = 0;nonflagInoutSpeed=0;nonflagInoutExtSpeed=0;jumpSpeed=0;markSpeed=0;
		polygonDelay=0;firstflagLineExt = 0;flagLineExt = 0; cycleOffset=0;startExtLen=0;flagPower=0;nonflagPower=0;arcPower=0;flagFreq=0;nonflagFreq=0;arcFreq=0;pulsewidth=0; flagOffset=0;
		xOffset = 0; yOffset = 0; EncoderOffset = 0; notchOffset = 0; ngLength = 0; dCuttingOffset = 1.5; dMinFlagLeng = 0; dNGSensorLeng = 0;dACSensorLeng=0; dPlcOffset=0;// �⺻��
	}
};




class CDualScannerParameter
{
public:
	CDualScannerParameter(void);
	~CDualScannerParameter(void);





	static CDualScannerParameter* m_instance;

	static CDualScannerParameter* GetInstance();


	void SetData(SingleScannerParameter HEAD2,SingleScannerParameter HEAD1);
	void LoadData(CString fileName);
	void SaveData(CString fileName);
	void SaveIniData();


	SingleScannerParameter GetHEAD2Parameter();
	SingleScannerParameter GetHEAD1Parameter();

private:
	SingleScannerParameter m_HEAD2ScannerParameter;
	SingleScannerParameter m_HEAD1ScannerParameter;

	

};

