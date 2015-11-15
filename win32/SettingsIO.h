#if !defined(CSEETINGSIO)
#define CSEETINGSIO

#include "stdafx.h"
#include "CCalculator.h"
#include <afxtempl.h>

class CSettingsIO : public CObject{	
public:
	CSettingsIO(CCalculator *pCalc);

	void WriteColorSetting(CString section, CString var, COLORREF val);
	void WriteSetting(CString section, CString var, long double val);
	void WriteSetting(CString section, CString var, CString val);
	void WriteSetting(CString section, CString var, int value);
	void WriteSettingColorT(CString section, CString var, ColorT value);
	void WriteSettingS3DEquation(CString section, CString var, S3DEquation value, CString eq);
	void WriteLogFont(CString section, CString var, LOGFONT value);
	void WriteCharFormat(CString section, CString var, CHARFORMAT value);

	COLORREF	ParseRGB(CString var);
	int			ReadSettingInt(CString section, CString var, int def);
	bool		ReadSettingBool(CString section, CString var, int def);
	CString		ReadSettingString(CString section, CString var, CString def);
	COLORREF	ReadSettingCOLORREF(CString section, CString var, CString def);
	long double ReadSettingLDouble(CString section, CString var, CString def);
	ColorT		ReadSettingColorT(CString section, CString var, SRGBString def);
	S3DEquation ReadSettingS3DEquation(CString section, CString var, SRGBString def_c1, SRGBString def_c2, SRGBString def_c3, SRGBString def_c4);
	LOGFONT 	ReadLogFont(CString section, CString var, LOGFONT def);
	CHARFORMAT ReadCharFormat(CString section, CString var, CHARFORMAT value);

private:
	CWinApp *m_pApp;
	CCalculator *m_pCalc;
};

#endif
