#include "stdafx.h"
#include "IniUtil.h"
#include "FieldParameter.h"
#include "DualScannerParameter.h"
#include "./Include/EXTERN/FileMgr.h"

#include <fstream>
#include <string>
#include <cmath>

IniUtil::IniUtil(void)
	: PATH_BASE(_T("./RECIPE/{LastRecipe}")),
	  PATH_INI_SITE(_T("./RECIPE/Site.ini")),
	  PATH_INI_ENC(_T("./RECIPE/EncoderSaved.ini")),
	  PATH_INI_WIDTH(_T("./RECIPE/RealWidth.ini")),

	  PATH_INI_PATTERN(_T("/SettingPattern.ini")),
	  PATH_INI_PARAM(_T("/SettingParam.ini")),
	  PATH_INI_FIELD(_T("/SettingField.ini")),
	  PATH_INI_RECIPE(_T("./RECIPE/{SiteName}/Recipe.ini"))

{
	LastRecipe = _T("");
	SiteName = _T("");
	LoadOptionsIni(PATH_INI_SITE); // Options.ini에서 SiteName과 LastRecipe를 로드
}

IniUtil::~IniUtil(void) {}

using namespace std;

void IniUtil::LoadOptionsIni(const CString &filePath)
{
	SiteName = fileMgr.ReadString(_T("Settings"), _T("SiteName"), filePath);
	LastRecipe = fileMgr.ReadString(_T("Settings"), _T("LastRecipe"), filePath);
}

void IniUtil::SetRecipe(const CString &newRecipe)
{
	LastRecipe = newRecipe;
	WritePrivateProfileString(_T("Settings"), _T("LastRecipe"), LastRecipe, PATH_INI_SITE);
	SiteName = fileMgr.ReadString(_T("Settings"), _T("SiteName"), PATH_INI_SITE);
}

CString IniUtil::ReplacePathVariables(const CString &pathTemplate)
{
	CString result = pathTemplate;
	result.Replace(_T("{SiteName}"), SiteName);
	result.Replace(_T("{LastRecipe}"), LastRecipe);
	return result;
}

void IniUtil::LoadStringValueByKey(const CString section, CString Key, CString filePath, CString &data)
{
	data = fileMgr.ReadString(section, Key, filePath);
}

void IniUtil::SetStringValue(const CString section, CString Value, CString Key, CString filePath)
{
	fileMgr.WriteString(section, Value, Key, filePath);
}

void IniUtil::LoadIntValueByKey(const CString section, CString Key, CString filePath, int &data)
{
	data = fileMgr.ReadInteger(section, Key, filePath);
}
void IniUtil::LoadDoubleValueByKey(const CString section, CString Key, CString filePath, double &data)
{
	data = fileMgr.ReadDouble(section, Key, filePath);
}
void IniUtil::LoadFloatValueByKey(const CString section, CString Key, CString filePath, float &data)
{
	data = fileMgr.ReadFloat(section, Key, filePath);
}
void IniUtil::LoadBoolValueByKey(const CString section, CString Key, CString filePath, BOOL &data)
{
	data = fileMgr.ReadBool(section, Key, filePath);
}

void IniUtil::LoadPouchOptionsIni(const CString section, CString filePath, int &modeValue)
{
	CString modeString = fileMgr.ReadString(_T("Settings"), _T("Mode"), filePath);

	if (modeString == _T("Anode_A"))
	{
		modeValue = 0;
	}
	else if (modeString == _T("Anode_B"))
	{
		modeValue = 1;
	}
	else if (modeString == _T("Cathode_A"))
	{
		modeValue = 2;
	}
	else if (modeString == _T("Cathode_B"))
	{
		modeValue = 3;
	}
	else
	{
		modeValue = -1;
	}
}

void IniUtil::LoadPouchPatternIni(const CString section, CString filePath, _POCKET_TMP_DATA_ &data)
{
	data.dTotalWidth = fileMgr.ReadDouble(section, _T("TotalWidth"), filePath);
	data.dTotalHeight = fileMgr.ReadDouble(section, _T("TotalHeight"), filePath);
	data.dTabCount = fileMgr.ReadDouble(section, _T("TabCount"), filePath);

	for (size_t i = 0; i < MAX_SPREAD_ROW; i++)
	{
		CString str;
		str.Format(_T("NotchingWidth%d"), i + 1);
		data.dNotchingWidth[i] = fileMgr.ReadDouble(section, str, filePath);
		str.Format(_T("NotchingWidthOffset%d"), i + 1);
		data.dNotchingWidthOffset[i] = fileMgr.ReadDouble(section, str, filePath);
		str.Format(_T("NotchingRealWidth%d"), i + 1);
		data.dNotchingRealWidth[i] = fileMgr.ReadDouble(section, str, filePath);
		str.Format(_T("NotchingAccWidth%d"), i + 1);
		data.dNotchingAccWidth[i] = fileMgr.ReadDouble(section, str, filePath);
		str.Format(_T("NotchingAccOffset%d"), i + 1);
		data.dNotchingAccOffset[i] = fileMgr.ReadDouble(section, str, filePath);
		str.Format(_T("NotchingAccOffset%d"), i + 1);
		data.dNotchingGabWidth[i] = fileMgr.ReadDouble(section, str, filePath);
	}

	data.dNotchingWidthDiff = fileMgr.ReadDouble(section, _T("NotchingWidthDiff"), filePath);

	data.dCuttingWidth = fileMgr.ReadDouble(section, _T("CuttingWidth"), filePath);
	data.dCuttingHeight = fileMgr.ReadDouble(section, _T("CuttingHeight"), filePath);
	data.dCuttingOffset = fileMgr.ReadDouble(section, _T("CuttingOffset"), filePath);
	data.dArcInXPos = fileMgr.ReadDouble(section, _T("ArcPositionInX"), filePath);
	data.dArcInYPos = fileMgr.ReadDouble(section, _T("ArcPositionInY"), filePath);
	data.dArcOutXPos = fileMgr.ReadDouble(section, _T("ArcPositionOutX"), filePath);
	data.dArcOutYPos = fileMgr.ReadDouble(section, _T("ArcPositionOutY"), filePath);
	data.dArcDegree = fileMgr.ReadDouble(section, _T("ArcDegree"), filePath);

	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();

	if (section == _T("Parameter"))
		pFieldParameter->SetPocketPatternParameterData(data);
}

void IniUtil::SavePouchOptionsIni(const CString section, CString filePath, int &modeValue)
{
	if (modeValue == 0)
	{
		fileMgr.WriteString(section, _T("Anode_A"), _T("Mode"), filePath);
	}
	else if (modeValue == 1)
	{
		fileMgr.WriteString(section, _T("Anode_B"), _T("Mode"), filePath);
	}
	else if (modeValue == 2)
	{
		fileMgr.WriteString(section, _T("Cathode_A"), _T("Mode"), filePath);
	}
	else if (modeValue == 3)
	{
		fileMgr.WriteString(section, _T("Cathode_B"), _T("Mode"), filePath);
	}
}

void IniUtil::SavePouchPatternIni(const CString section, CString filePath, _POCKET_TMP_DATA_ &data)
{
	fileMgr.WriteDouble(section, data.dTotalWidth, _T("TotalWidth"), filePath);
	fileMgr.WriteDouble(section, data.dTotalHeight, _T("TotalHeight"), filePath);
	fileMgr.WriteDouble(section, data.dTabCount, _T("TabCount"), filePath);

	for (size_t i = 0; i < MAX_SPREAD_ROW; i++)
	{
		CString str;
		str.Format(_T("NotchingWidth%d"), i + 1);
		fileMgr.WriteDouble(section, data.dNotchingWidth[i], str, filePath);
		str.Format(_T("NotchingWidthOffset%d"), i + 1);
		fileMgr.WriteDouble(section, data.dNotchingWidthOffset[i], str, filePath);
		str.Format(_T("NotchingRealWidth%d"), i + 1);
		fileMgr.WriteDouble(section, data.dNotchingRealWidth[i], str, filePath);
		str.Format(_T("NotchingAccWidth%d"), i + 1);
		fileMgr.WriteDouble(section, data.dNotchingAccWidth[i], str, filePath);
		str.Format(_T("NotchingAccOffset%d"), i + 1);
		fileMgr.WriteDouble(section, data.dNotchingAccOffset[i], str, filePath);
		str.Format(_T("NotchingGabWidth%d"), i + 1);
		fileMgr.WriteDouble(section, data.dNotchingGabWidth[i], str, filePath);
	}

	fileMgr.WriteDouble(section, data.dCuttingWidth, _T("CuttingWidth"), filePath);
	fileMgr.WriteDouble(section, data.dCuttingHeight, _T("CuttingHeight"), filePath);
	fileMgr.WriteDouble(section, data.dCuttingOffset, _T("CuttingOffset"), filePath);
	fileMgr.WriteDouble(section, data.dArcInXPos, _T("ArcPositionInX"), filePath);
	fileMgr.WriteDouble(section, data.dArcInYPos, _T("ArcPositionInY"), filePath);
	fileMgr.WriteDouble(section, data.dArcOutXPos, _T("ArcPositionOutX"), filePath);
	fileMgr.WriteDouble(section, data.dArcOutYPos, _T("ArcPositionOutY"), filePath);
	fileMgr.WriteDouble(section, data.dArcDegree, _T("ArcDegree"), filePath);

	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();

	if (section == _T("Parameter"))
		pFieldParameter->SetPocketPatternParameterData(data);
}

void IniUtil::LoadParameterIni(const CString section, CString filePath, SingleScannerParameter &data)
{
	data.dCuttingOffset = fileMgr.ReadDouble(section, _T("CuttingOffset"), filePath);
	data.EncoderOffset = fileMgr.ReadDouble(section, _T("EncoderOffset"), filePath);
	data.dMinFlagLeng = fileMgr.ReadDouble(section, _T("MinFlagLeng"), filePath);
	data.dNGSensorLeng = fileMgr.ReadDouble(section, _T("NGSensorLeng"), filePath);
	data.cycleOffset = fileMgr.ReadDouble(section, _T("cycleOffset"), filePath);
	data.firstflagLineExt = fileMgr.ReadDouble(section, _T("firstflagLineExt"), filePath);
	data.flagExtSpeed = fileMgr.ReadDouble(section, _T("flagExtSpeed"), filePath);
	data.flagFreq = fileMgr.ReadDouble(section, _T("flagFreq"), filePath);
	data.arcFreq = fileMgr.ReadDouble(section, _T("arcFreq"), filePath);
	data.flagLineExt = fileMgr.ReadDouble(section, _T("flagLineExt"), filePath);
	data.flagLineSpeed = fileMgr.ReadDouble(section, _T("flagLineSpeed"), filePath);
	data.flagOffset = fileMgr.ReadDouble(section, _T("flagOffset"), filePath);
	data.flagPower = fileMgr.ReadDouble(section, _T("flagPower"), filePath);
	data.arcPower = fileMgr.ReadDouble(section, _T("arcPower"), filePath);
	data.flagSpeed = fileMgr.ReadDouble(section, _T("flagSpeed"), filePath);
	data.jumpDelay = fileMgr.ReadDouble(section, _T("jumpDelay"), filePath);
	data.jumpSpeed = fileMgr.ReadDouble(section, _T("jumpSpeed"), filePath);
	data.laserOffDelay = fileMgr.ReadDouble(section, _T("laserOffDelay"), filePath);
	data.laserOnDelay = fileMgr.ReadDouble(section, _T("laserOnDelay"), filePath);
	data.markDelay = fileMgr.ReadDouble(section, _T("markDelay"), filePath);
	data.markSpeed = fileMgr.ReadDouble(section, _T("markSpeed"), filePath);
	data.ngLength = fileMgr.ReadDouble(section, _T("ngLength"), filePath);
	data.nonflagFreq = fileMgr.ReadDouble(section, _T("nonflagFreq"), filePath);
	data.nonflagInoutExtSpeed = fileMgr.ReadDouble(section, _T("nonflagInoutExtSpeed"), filePath);
	data.nonflagInoutSpeed = fileMgr.ReadDouble(section, _T("nonflagInoutSpeed"), filePath);
	data.nonflagLineSpeed = fileMgr.ReadDouble(section, _T("nonflagLineSpeed"), filePath);
	data.nonflagPower = fileMgr.ReadDouble(section, _T("nonflagPower"), filePath);
	data.notchOffset = fileMgr.ReadDouble(section, _T("notchOffset"), filePath);
	data.polygonDelay = fileMgr.ReadDouble(section, _T("polygonDelay"), filePath);
	data.pulsewidth = fileMgr.ReadDouble(section, _T("pulsewidth"), filePath);
	data.startExtLen = fileMgr.ReadDouble(section, _T("startExtLen"), filePath);
	data.xOffset = fileMgr.ReadDouble(section, _T("xOffset"), filePath);
	data.yOffset = fileMgr.ReadDouble(section, _T("yOffset"), filePath);

	data.dPatternShift = fileMgr.ReadDouble(section, _T("PatternShift"), filePath);
	data.dPlcOffset = fileMgr.ReadDouble(section, _T("PlcOffset"), filePath);
}

void IniUtil::LoadFieldIni(const CString section, CString filePath, FieldParameter &data)
{
	data.MmSize = fileMgr.ReadDouble(section, _T("MmSize"), filePath);
	data.FieldSize = fileMgr.ReadDouble(section, _T("FieldSize"), filePath);
	data.Unit = fileMgr.ReadDouble(section, _T("Unit"), filePath);
	data.KX = fileMgr.ReadDouble(section, _T("KX"), filePath);
	data.KY = fileMgr.ReadDouble(section, _T("KY"), filePath);
	data.KX2 = fileMgr.ReadDouble(section, _T("KX2"), filePath);
	data.KY2 = fileMgr.ReadDouble(section, _T("KY2"), filePath);
	data.KX_Notch = fileMgr.ReadDouble(section, _T("KX_Notch"), filePath);
	data.KY_Notch = fileMgr.ReadDouble(section, _T("KY_Notch"), filePath);
	data.KX2_Notch = fileMgr.ReadDouble(section, _T("KX2_Notch"), filePath);
	data.KY2_Notch = fileMgr.ReadDouble(section, _T("KY2_Notch"), filePath);
	data.MaxCuttingSize = fileMgr.ReadDouble(section, _T("MaxCuttingSize"), filePath);
	data.RollSpeed = fileMgr.ReadDouble(section, _T("RollSpeed"), filePath);
	data.SampleSize = fileMgr.ReadDouble(section, _T("SampleSize"), filePath);
	data.RealSize = fileMgr.ReadDouble(section, _T("RealSize"), filePath);
	data.RFieldSize = fileMgr.ReadDouble(section, _T("RFieldSize"), filePath);
	data.MarkingField = fileMgr.ReadDouble(section, _T("MarkingField"), filePath);
	data.CycleOffset = fileMgr.ReadDouble(section, _T("CycleOffset"), filePath);
	data.CycleOffset2 = fileMgr.ReadDouble(section, _T("CycleOffset2"), filePath);
	data.ScannerStartPosX = fileMgr.ReadDouble(section, _T("ScannerStartPosX"), filePath);
	data.ScannerStartPosY = fileMgr.ReadDouble(section, _T("ScannerStartPosY"), filePath);
	data.ModeValue = fileMgr.ReadDouble(section, _T("ModeValue"), filePath);
	data.nPattern = fileMgr.ReadDouble(section, _T("nPattern"), filePath);
	data.nPattern = fileMgr.ReadDouble(section, _T("nPattern"), filePath);
	data.Cutting_set_head1 = fileMgr.ReadDouble(section, _T("Cutting_set_head1"), filePath);
	data.Cutting_act_head1 = fileMgr.ReadDouble(section, _T("Cutting_act_head1"), filePath);
	data.Cutting_set_head2 = fileMgr.ReadDouble(section, _T("Cutting_set_head2"), filePath);
	data.Cutting_act_head2 = fileMgr.ReadDouble(section, _T("Cutting_act_head2"), filePath);
	data.Notching_set_head1 = fileMgr.ReadDouble(section, _T("Notching_set_head1"), filePath);
	data.Notching_act_head1 = fileMgr.ReadDouble(section, _T("Notching_act_head1"), filePath);
	data.Notching_set_head2 = fileMgr.ReadDouble(section, _T("Notching_set_head2"), filePath);
	data.Notching_act_head2 = fileMgr.ReadDouble(section, _T("Notching_act_head2"), filePath);
}

void IniUtil::SaveParameterIni(const CString section, CString filePath, SingleScannerParameter &data)
{
	fileMgr.WriteDouble(section, data.dCuttingOffset, _T("CuttingOffset"), filePath);
	fileMgr.WriteDouble(section, data.EncoderOffset, _T("EncoderOffset"), filePath);
	fileMgr.WriteDouble(section, data.dMinFlagLeng, _T("MinFlagLeng"), filePath);
	fileMgr.WriteDouble(section, data.dNGSensorLeng, _T("NGSensorLeng"), filePath);
	fileMgr.WriteDouble(section, data.cycleOffset, _T("cycleOffset"), filePath);
	fileMgr.WriteDouble(section, data.firstflagLineExt, _T("firstflagLineExt"), filePath);
	fileMgr.WriteDouble(section, data.flagExtSpeed, _T("flagExtSpeed"), filePath);
	fileMgr.WriteDouble(section, data.flagFreq, _T("flagFreq"), filePath);
	fileMgr.WriteDouble(section, data.arcFreq, _T("arcFreq"), filePath);
	fileMgr.WriteDouble(section, data.flagLineExt, _T("flagLineExt"), filePath);
	fileMgr.WriteDouble(section, data.flagLineSpeed, _T("flagLineSpeed"), filePath);
	fileMgr.WriteDouble(section, data.flagOffset, _T("flagOffset"), filePath);
	fileMgr.WriteDouble(section, data.flagPower, _T("flagPower"), filePath);
	fileMgr.WriteDouble(section, data.arcPower, _T("arcPower"), filePath);
	fileMgr.WriteDouble(section, data.flagSpeed, _T("flagSpeed"), filePath);
	fileMgr.WriteDouble(section, data.jumpDelay, _T("jumpDelay"), filePath);
	fileMgr.WriteDouble(section, data.jumpSpeed, _T("jumpSpeed"), filePath);
	fileMgr.WriteDouble(section, data.laserOffDelay, _T("laserOffDelay"), filePath);
	fileMgr.WriteDouble(section, data.laserOnDelay, _T("laserOnDelay"), filePath);
	fileMgr.WriteDouble(section, data.markDelay, _T("markDelay"), filePath);
	fileMgr.WriteDouble(section, data.markSpeed, _T("markSpeed"), filePath);
	fileMgr.WriteDouble(section, data.ngLength, _T("ngLength"), filePath);
	fileMgr.WriteDouble(section, data.nonflagFreq, _T("nonflagFreq"), filePath);
	fileMgr.WriteDouble(section, data.nonflagInoutExtSpeed, _T("nonflagInoutExtSpeed"), filePath);
	fileMgr.WriteDouble(section, data.nonflagInoutSpeed, _T("nonflagInoutSpeed"), filePath);
	fileMgr.WriteDouble(section, data.nonflagLineSpeed, _T("nonflagLineSpeed"), filePath);
	fileMgr.WriteDouble(section, data.nonflagPower, _T("nonflagPower"), filePath);
	fileMgr.WriteDouble(section, data.notchOffset, _T("notchOffset"), filePath);
	fileMgr.WriteDouble(section, data.polygonDelay, _T("polygonDelay"), filePath);
	fileMgr.WriteDouble(section, data.pulsewidth, _T("pulsewidth"), filePath);
	fileMgr.WriteDouble(section, data.startExtLen, _T("startExtLen"), filePath);
	fileMgr.WriteDouble(section, data.xOffset, _T("xOffset"), filePath);
	fileMgr.WriteDouble(section, data.yOffset, _T("yOffset"), filePath);

	fileMgr.WriteDouble(section, data.dPatternShift, _T("PatternShift"), filePath);
	fileMgr.WriteDouble(section, data.dPlcOffset, _T("PlcOffset"), filePath);
}

void IniUtil::SaveEncIni(double &data1, double &data2)
{
	fileMgr.WriteDouble(_T("ENC"), data1, _T("HEAD1"), PATH_INI_ENC);
	fileMgr.WriteDouble(_T("ENC"), data2, _T("HEAD2"), PATH_INI_ENC);
}

void IniUtil::LoadEncIni(double &data1, double &data2)
{
	data1 = fileMgr.ReadDouble(_T("ENC"), _T("HEAD1"), PATH_INI_ENC);
	data2 = fileMgr.ReadDouble(_T("ENC"), _T("HEAD2"), PATH_INI_ENC);
}

void IniUtil::SaveRealWidthIni(double &data)
{
	fileMgr.WriteDouble(_T("RealWidth"), data, _T("RealWidth"), PATH_INI_WIDTH);
}

void IniUtil::LoadRealWidthIni(double &data)
{
	data = fileMgr.ReadDouble(_T("RealWidth"), _T("RealWidth"), PATH_INI_WIDTH);
}

void IniUtil::SaveFieldIni(const CString section, CString filePath, FieldParameter &data)
{
	fileMgr.WriteDouble(section, data.MmSize, _T("MmSize"), filePath);
	fileMgr.WriteDouble(section, data.FieldSize, _T("FieldSize"), filePath);
	fileMgr.WriteDouble(section, data.Unit, _T("Unit"), filePath);
	fileMgr.WriteDouble(section, data.KX, _T("KX"), filePath);
	fileMgr.WriteDouble(section, data.KY, _T("KY"), filePath);
	fileMgr.WriteDouble(section, data.KX2, _T("KX2"), filePath);
	fileMgr.WriteDouble(section, data.KY2, _T("KY2"), filePath);
	fileMgr.WriteDouble(section, data.KX_Notch, _T("KX_Notch"), filePath);
	fileMgr.WriteDouble(section, data.KY_Notch, _T("KY_Notch"), filePath);
	fileMgr.WriteDouble(section, data.KX2_Notch, _T("KX2_Notch"), filePath);
	fileMgr.WriteDouble(section, data.KY2_Notch, _T("KY2_Notch"), filePath);
	fileMgr.WriteDouble(section, data.MaxCuttingSize, _T("MaxCuttingSize"), filePath);
	fileMgr.WriteDouble(section, data.RollSpeed, _T("RollSpeed"), filePath);
	fileMgr.WriteDouble(section, data.SampleSize, _T("SampleSize"), filePath);
	fileMgr.WriteDouble(section, data.RealSize, _T("RealSize"), filePath);
	fileMgr.WriteDouble(section, data.RFieldSize, _T("RFieldSize"), filePath);
	fileMgr.WriteDouble(section, data.MarkingField, _T("MarkingField"), filePath);
	fileMgr.WriteDouble(section, data.CycleOffset, _T("CycleOffset"), filePath);
	fileMgr.WriteDouble(section, data.CycleOffset2, _T("CycleOffset2"), filePath);
	fileMgr.WriteDouble(section, data.ScannerStartPosX, _T("ScannerStartPosX"), filePath);
	fileMgr.WriteDouble(section, data.ScannerStartPosY, _T("ScannerStartPosY"), filePath);
	fileMgr.WriteInteger(section, data.ModeValue, _T("ModeValue"), filePath);
	fileMgr.WriteInteger(section, data.nPattern, _T("nPattern"), filePath);
	fileMgr.WriteDouble(section, data.Cutting_set_head1, _T("Cutting_set_head1"), filePath);
	fileMgr.WriteDouble(section, data.Cutting_act_head1, _T("Cutting_act_head1"), filePath);
	fileMgr.WriteDouble(section, data.Cutting_set_head2, _T("Cutting_set_head2"), filePath);
	fileMgr.WriteDouble(section, data.Cutting_act_head2, _T("Cutting_act_head2"), filePath);
	fileMgr.WriteDouble(section, data.Notching_set_head1, _T("Notching_set_head1"), filePath);
	fileMgr.WriteDouble(section, data.Notching_act_head1, _T("Notching_act_head1"), filePath);
	fileMgr.WriteDouble(section, data.Notching_set_head2, _T("Notching_set_head2"), filePath);
	fileMgr.WriteDouble(section, data.Notching_act_head2, _T("Notching_act_head2"), filePath);
}

void IniUtil::LoadSDIPatternIni(const CString section, CString filePath, _SDI_NOTCH_PATTERN_DATA &data)
{
	data.bFlip = fileMgr.ReadBool(section, _T("Flip"), filePath);
	data.nCuttingMode = fileMgr.ReadInteger(section, _T("CuttingMode"), filePath);
	data.dCuttingTotalWidth = fileMgr.ReadDouble(section, _T("CuttingTotalWidth"), filePath);
	data.dNochingWidth = fileMgr.ReadDouble(section, _T("NochingWidth"), filePath);
	data.dNochingHeight = fileMgr.ReadDouble(section, _T("NochingHeight"), filePath);
	data.dCuttingHeight = fileMgr.ReadDouble(section, _T("CuttingHeight"), filePath);
	data.dCuttingTabWidth1 = fileMgr.ReadDouble(section, _T("CuttingTabWidth1"), filePath);
	data.dCuttingTabWidth2 = fileMgr.ReadDouble(section, _T("CuttingTabWidth2"), filePath);
	data.dCuttingTabWidth3 = fileMgr.ReadDouble(section, _T("CuttingTabWidth3"), filePath);
	data.dCuttingTabWidth4 = fileMgr.ReadDouble(section, _T("CuttingTabWidth4"), filePath);
	data.dCuttingTabWidth5 = fileMgr.ReadDouble(section, _T("CuttingTabWidth5"), filePath);
	data.dCuttingTabWidth6 = fileMgr.ReadDouble(section, _T("CuttingTabWidth6"), filePath);

	data.dCuttingCount1 = fileMgr.ReadDouble(section, _T("CuttingCount1"), filePath);
	data.dCuttingCount2 = fileMgr.ReadDouble(section, _T("CuttingCount2"), filePath);
	data.dCuttingCount3 = fileMgr.ReadDouble(section, _T("CuttingCount3"), filePath);
	data.dCuttingCount4 = fileMgr.ReadDouble(section, _T("CuttingCount4"), filePath);
	data.dCuttingCount5 = fileMgr.ReadDouble(section, _T("CuttingCount5"), filePath);
	data.dCuttingCount6 = fileMgr.ReadDouble(section, _T("CuttingCount6"), filePath);

	data.dCuttingAngle = fileMgr.ReadDouble(section, _T("CuttingAngle"), filePath);
	data.dNochingAngle = fileMgr.ReadDouble(section, _T("NochingAngle"), filePath);
	data.dNochingOutPosWidth = fileMgr.ReadDouble(section, _T("NochingOutPosWidth"), filePath);
}

void IniUtil::SaveSDIPatternIni(const CString section, CString filePath, _SDI_NOTCH_PATTERN_DATA &data)
{
	fileMgr.WriteBool(section, data.bFlip, _T("Flip"), filePath);
	fileMgr.WriteInteger(section, data.nCuttingMode, _T("CuttingMode"), filePath);
	fileMgr.WriteDouble(section, data.dCuttingTotalWidth, _T("CuttingTotalWidth"), filePath);
	fileMgr.WriteDouble(section, data.dNochingWidth, _T("NochingWidth"), filePath);
	fileMgr.WriteDouble(section, data.dNochingHeight, _T("NochingHeight"), filePath);
	fileMgr.WriteDouble(section, data.dCuttingHeight, _T("CuttingHeight"), filePath);

	fileMgr.WriteDouble(section, data.dCuttingTabWidth1, _T("CuttingTabWidth1"), filePath);
	fileMgr.WriteDouble(section, data.dCuttingTabWidth2, _T("CuttingTabWidth2"), filePath);
	fileMgr.WriteDouble(section, data.dCuttingTabWidth3, _T("CuttingTabWidth3"), filePath);
	fileMgr.WriteDouble(section, data.dCuttingTabWidth4, _T("CuttingTabWidth4"), filePath);
	fileMgr.WriteDouble(section, data.dCuttingTabWidth5, _T("CuttingTabWidth5"), filePath);
	fileMgr.WriteDouble(section, data.dCuttingTabWidth6, _T("CuttingTabWidth6"), filePath);

	fileMgr.WriteDouble(section, data.dCuttingCount1, _T("CuttingCount1"), filePath);
	fileMgr.WriteDouble(section, data.dCuttingCount2, _T("CuttingCount2"), filePath);
	fileMgr.WriteDouble(section, data.dCuttingCount3, _T("CuttingCount3"), filePath);
	fileMgr.WriteDouble(section, data.dCuttingCount4, _T("CuttingCount4"), filePath);
	fileMgr.WriteDouble(section, data.dCuttingCount5, _T("CuttingCount5"), filePath);
	fileMgr.WriteDouble(section, data.dCuttingCount6, _T("CuttingCount6"), filePath);

	fileMgr.WriteDouble(section, data.dCuttingAngle, _T("CuttingAngle"), filePath);
	fileMgr.WriteDouble(section, data.dNochingAngle, _T("NochingAngle"), filePath);
	fileMgr.WriteDouble(section, data.dNochingOutPosWidth, _T("NochingOutPosWidth"), filePath);
}