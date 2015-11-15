#include "SettingsIO.h"
#include "Color.h"

CSettingsIO::CSettingsIO(CCalculator *pCalc){
	m_pCalc = pCalc;
	m_pApp = AfxGetApp();
}

void CSettingsIO::WriteSettingColorT(CString section, CString var, ColorT val)
{
	WriteSetting(section, var+".red", long double(val.red));
	WriteSetting(section, var+".green", long double(val.green));
	WriteSetting(section, var+".blue", long double(val.blue));
}

void CSettingsIO::WriteSettingS3DEquation(CString section, CString var, S3DEquation val, CString eq)
{
	WriteSetting(section, var+".wire", val.wires);
	WriteSetting(section, var+".on", val.on);
	WriteSetting(section, var+".color.type", val.color.type);
	WriteSettingColorT(section, var+".color1", val.color.color1);
	WriteSettingColorT(section, var+".color2", val.color.color2);
	WriteSettingColorT(section, var+".color3", val.color.color3);
	WriteSettingColorT(section, var+".color4", val.color.color4);
	WriteSetting(section, var+".eq", eq);
}

void CSettingsIO::WriteSetting(CString section, CString var, int value)
{
	m_pApp->WriteProfileInt(section, var, value);
}

void CSettingsIO::WriteSetting(CString section, CString var, long double val)
{
	CString value, line;
	m_pCalc->DecimalToString(value, val);
	
	m_pApp->WriteProfileString(section, var, value);
}

void CSettingsIO::WriteSetting(CString section, CString var, CString val)
{
	m_pApp->WriteProfileString(section, var, val);
}

void CSettingsIO::WriteColorSetting(CString section, CString var, COLORREF val)
{
	CColor col(val);

	CString r, g, b;
	m_pCalc->DecimalToString(r, col.GetRed());
	m_pCalc->DecimalToString(g, col.GetGreen());
	m_pCalc->DecimalToString(b, col.GetBlue());
	m_pApp->WriteProfileString(section, var, r + "," + g + "," + b);
}

void CSettingsIO::WriteLogFont(CString section, CString var, LOGFONT value)
{
	m_pApp->WriteProfileInt(section, var + ".lfHeight", value.lfHeight);
	m_pApp->WriteProfileInt(section, var + ".lfWidth", value.lfWidth);
	m_pApp->WriteProfileInt(section, var + ".lfEscapement", value.lfEscapement);
	m_pApp->WriteProfileInt(section, var + ".lfOrientation", value.lfOrientation);
	m_pApp->WriteProfileInt(section, var + ".lfWeight", value.lfWeight);
	m_pApp->WriteProfileInt(section, var + ".lfItalic", value.lfItalic);
	m_pApp->WriteProfileInt(section, var + ".lfUnderline", value.lfUnderline);
	m_pApp->WriteProfileInt(section, var + ".lfStrikeOut", value.lfStrikeOut);
	m_pApp->WriteProfileInt(section, var + ".lfCharSet", value.lfCharSet);
	m_pApp->WriteProfileInt(section, var + ".lfOutPrecision", value.lfOutPrecision);
	m_pApp->WriteProfileInt(section, var + ".lfClipPrecision", value.lfClipPrecision);
	m_pApp->WriteProfileInt(section, var + ".lfQuality", value.lfQuality);
	m_pApp->WriteProfileInt(section, var + ".lfPitchAndFamily", value.lfPitchAndFamily);
	m_pApp->WriteProfileString(section, var + ".lfFaceName", value.lfFaceName);
 }

LOGFONT CSettingsIO::ReadLogFont(CString section, CString var, LOGFONT def)
{
	LOGFONT lf;
	
	lf.lfHeight 		= m_pApp->GetProfileInt(section, var + ".lfHeight", def.lfHeight);
	lf.lfWidth 			= m_pApp->GetProfileInt(section, var + ".lfWidth", def.lfWidth);
	lf.lfEscapement 	= m_pApp->GetProfileInt(section, var + ".lfEscapement", def.lfEscapement);
	lf.lfOrientation 	= m_pApp->GetProfileInt(section, var + ".lfOrientation", def.lfOrientation);
	lf.lfWeight 		= m_pApp->GetProfileInt(section, var + ".lfWeight", def.lfWeight);
	lf.lfItalic 		= m_pApp->GetProfileInt(section, var + ".lfItalic", def.lfItalic);
	lf.lfUnderline 		= m_pApp->GetProfileInt(section, var + ".lfUnderline", def.lfUnderline);
	lf.lfStrikeOut 		= m_pApp->GetProfileInt(section, var + ".lfStrikeOut", def.lfStrikeOut);
	lf.lfCharSet 		= m_pApp->GetProfileInt(section, var + ".lfCharSet", def.lfCharSet);
	lf.lfOutPrecision 	= m_pApp->GetProfileInt(section, var + ".lfOutPrecision", def.lfOutPrecision);
	lf.lfClipPrecision 	= m_pApp->GetProfileInt(section, var + ".lfClipPrecision", def.lfClipPrecision);
	lf.lfQuality 		= m_pApp->GetProfileInt(section, var + ".lfQuality", def.lfQuality);
	lf.lfPitchAndFamily     = m_pApp->GetProfileInt(section, var + ".lfPitchAndFamily", def.lfPitchAndFamily);
	strcpy(lf.lfFaceName, m_pApp->GetProfileString(section, var + ".lfFaceName", def.lfFaceName));
	

	/*(for(int i=0; i < strFace.GetLength(); ++i)
 		lf.lfFaceName[i] = strFace[i];
	lf.lfFaceName[i] = 0x00;*/

	return lf;
}

void CSettingsIO::WriteCharFormat(CString section, CString var, CHARFORMAT value)
{
	m_pApp->WriteProfileInt(section, var + ".cf.dwMask", value.dwMask);
	m_pApp->WriteProfileInt(section, var + ".cf.dwEffects", value.dwEffects);
	m_pApp->WriteProfileInt(section, var + ".cf.yHeight", value.yHeight);
	m_pApp->WriteProfileInt(section, var + ".cf.yOffset", value.yOffset);
	m_pApp->WriteProfileInt(section, var + ".cf.crTextColor", value.crTextColor);
	m_pApp->WriteProfileInt(section, var + ".cf.bCharSet", value.bCharSet);
	m_pApp->WriteProfileInt(section, var + ".cf.bPitchAndFamily", value.bPitchAndFamily);
	m_pApp->WriteProfileString(section, var + ".cf.szFaceName", value.szFaceName);
}

CHARFORMAT CSettingsIO::ReadCharFormat(CString section, CString var, CHARFORMAT value)
{
	CHARFORMAT cf;
	
	cf.dwMask		= m_pApp->GetProfileInt(section, var + ".cf.dwMask", value.dwMask);
	cf.dwEffects	= m_pApp->GetProfileInt(section, var + ".cf.dwEffects", value.dwEffects);
	cf.yHeight		= m_pApp->GetProfileInt(section, var + ".cf.yHeight", value.yHeight);
	cf.yOffset		= m_pApp->GetProfileInt(section, var + ".cf.yOffset", value.yOffset);
	cf.crTextColor	= m_pApp->GetProfileInt(section, var + ".cf.crTextColor", value.crTextColor);
	cf.bCharSet		= m_pApp->GetProfileInt(section, var + ".cf.bCharSet", value.bCharSet);
	cf.bPitchAndFamily = m_pApp->GetProfileInt(section, var + ".cf.bPitchAndFamily", value.bPitchAndFamily);
	strcpy(cf.szFaceName, m_pApp->GetProfileString(section, var + ".cf.szFaceName", value.szFaceName));

	return cf;
}
int	CSettingsIO::ReadSettingInt(CString section, CString var, int def){
	return m_pApp->GetProfileInt(section, var, def);
}

bool CSettingsIO::ReadSettingBool(CString section, CString var, int def){
	return (m_pApp->GetProfileInt(section, var, def) == 1);
}

CString	CSettingsIO::ReadSettingString(CString section, CString var, CString def){
	return m_pApp->GetProfileString(section, var, def);
}

long double CSettingsIO::ReadSettingLDouble(CString section, CString var, CString def){
	long double ans;
	m_pCalc->StringToDecimal(m_pApp->GetProfileString(section, var, def), 10, ans);
	return ans;
}

ColorT	CSettingsIO::ReadSettingColorT(CString section, CString var, SRGBString def){
	ColorT clr;
	clr.red =	ReadSettingLDouble(section, var+".red", def.r);
	clr.green = ReadSettingLDouble(section, var+".green", def.g);
	clr.blue =	ReadSettingLDouble(section, var+".blue", def.b);
	return clr;
}

S3DEquation CSettingsIO::ReadSettingS3DEquation(CString section, CString var, SRGBString def_c1, SRGBString def_c2, SRGBString def_c3, SRGBString def_c4){
	S3DEquation val;

	val.wires = (WiresE)ReadSettingInt(section, var+".wire", CW);
	val.on = ReadSettingBool(section, var+".on", 0);
	val.color.type = (ShadingTypeE)ReadSettingInt(section, var+".color.type", 0);
	val.color.color1 = ReadSettingColorT(section, var+".color1", def_c1);
	val.color.color2 = ReadSettingColorT(section, var+".color2", def_c2);
	val.color.color3 = ReadSettingColorT(section, var+".color3", def_c3);
	val.color.color4 = ReadSettingColorT(section, var+".color4", def_c4);

	val.eq = ReadSettingString(section, var+".eq", "");

	return val;
}

COLORREF CSettingsIO::ReadSettingCOLORREF(CString section, CString var, CString def){
	return ParseRGB(m_pApp->GetProfileString(section, var, def));
}

COLORREF CSettingsIO::ParseRGB(CString var)
{
	CString r,g,b;
	r = var.Left(var.Find(","));
	CString right = var.Right(var.GetLength() - 1 - var.Find(","));
	g = right.Left(right.Find(","));
	b = right.Right(right.GetLength() - 1 - right.Find(","));

	long double rr, gg, bb;
	m_pCalc->StringToDecimal(r, 10, rr);
	m_pCalc->StringToDecimal(g, 10, gg); 
	m_pCalc->StringToDecimal(b, 10, bb);

	return RGB(int(rr), int(gg), int(bb));
}
