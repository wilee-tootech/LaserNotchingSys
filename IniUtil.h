#include "FieldParameter.h"
#include "./Include//EXTERN/FileMgr.h"
#include "DualScannerParameter.h"

#pragma once
class IniUtil
{
public:
	IniUtil(void);
	~IniUtil(void);
    CFileMgr fileMgr;
    CString LastRecipe;
    CString SiteName;

    CString PATH_BASE;
    CString PATH_INI_SITE;
	CString PATH_INI_ENC;
	CString PATH_INI_WIDTH;

    CString PATH_INI_PATTERN;
    CString PATH_INI_PARAM;
    CString PATH_INI_FIELD;
	CString PATH_INI_RECIPE;

	void LoadOptionsIni(const CString& filePath);
	void SetRecipe(const CString& newRecipe);
	CString ReplacePathVariables(const CString& pathTemplate);

	void LoadStringValueByKey(const CString section, CString Key, CString filePath, CString& data);
	void LoadIntValueByKey(const CString section, CString Key, CString filePath, int& data);
	void LoadDoubleValueByKey(const CString section, CString Key, CString filePath, double& data);
	void LoadFloatValueByKey(const CString section, CString Key, CString filePath, float& data);
	void LoadBoolValueByKey(const CString section, CString Key, CString filePath, BOOL& data);

	void SetStringValue(const CString section, CString Value, CString Key, CString filePath);

	void LoadEncIni(double& data1, double& data2);
	void SaveEncIni(double& data1, double& data2);
	
	void SaveRealWidthIni(double& data);
	void LoadRealWidthIni(double& data);

	void LoadPouchOptionsIni(const CString section, CString filePath, int& modeValue);
    void LoadPouchPatternIni(const CString section, CString filePath, _POCKET_TMP_DATA_& data);
	void SavePouchOptionsIni(const CString section, CString filePath,  int& modeValue);
	void SavePouchPatternIni(const CString section, CString filePath, _POCKET_TMP_DATA_& data);

	void LoadSDIPatternIni(const CString section, CString filePath, _SDI_NOTCH_PATTERN_DATA& data);
	void SaveSDIPatternIni(const CString section, CString filePath, _SDI_NOTCH_PATTERN_DATA& data);

	void LoadParameterIni(const CString section, CString filePath, SingleScannerParameter& modeValue);
    void LoadFieldIni(const CString section, CString filePath, FieldParameter& data);
    void SaveParameterIni(const CString section, CString filePath, SingleScannerParameter& data);
    void SaveFieldIni(const CString section, CString filePath, FieldParameter& data);
};