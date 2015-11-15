// OutputView.cpp : implementation file
//

#include "stdafx.h"
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <afxtempl.h>
#include <fstream.h>
#include "GrphCalc.h"
#include "OutputView.h"
#include "GrphCalcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OutputView property page

IMPLEMENT_DYNCREATE(OutputView, CPropertyPage)

OutputView::OutputView() : CPropertyPage(OutputView::IDD)
{
	//{{AFX_DATA_INIT(OutputView)
	//}}AFX_DATA_INIT

	m_LongOutput = false;
	m_fOutputWindow = true;

	m_AnswerFont.cbSize = sizeof(CHARFORMAT);
	m_AnswerFont.dwMask = CFM_BOLD | CFM_UNDERLINE | CFM_ITALIC | CFM_STRIKEOUT | 
		CFM_COLOR | CFM_FACE | CFM_SIZE | CFM_CHARSET;
	m_AnswerFont.dwEffects = (0);
	m_AnswerFont.crTextColor = 0x00000080;
	strcpy(m_AnswerFont.szFaceName, "Arial");
	m_AnswerFont.yHeight = 175;
	//m_AnswerFont.yHeight = 300;
	m_AnswerFont.yOffset = 40;

	m_LongOutputFont.cbSize = sizeof(CHARFORMAT);
	m_LongOutputFont.dwMask = CFM_BOLD | CFM_UNDERLINE | CFM_ITALIC | CFM_STRIKEOUT | 
		CFM_COLOR | CFM_FACE | CFM_SIZE | CFM_CHARSET;
	m_LongOutputFont.dwEffects = (0);
	m_LongOutputFont.crTextColor = 0x00008000;
	strcpy(m_LongOutputFont.szFaceName, "Arial");
	m_LongOutputFont.yHeight = 135;
	m_LongOutputFont.yOffset = 40;

	m_BaseFont.cbSize = sizeof(CHARFORMAT);
	m_BaseFont.dwMask = CFM_BOLD | CFM_UNDERLINE | CFM_ITALIC | CFM_STRIKEOUT | 
		CFM_COLOR | CFM_FACE | CFM_SIZE | CFM_CHARSET | CFM_OFFSET;
	m_BaseFont.dwEffects = (0);
	m_BaseFont.crTextColor = 0x00800000;
	strcpy(m_BaseFont.szFaceName, "Arial");
	m_BaseFont.yHeight = 135;
	m_BaseFont.yOffset = -40;

	m_ExpressionFont.cbSize = sizeof(CHARFORMAT);
	m_ExpressionFont.dwMask = CFM_BOLD | CFM_UNDERLINE | CFM_ITALIC | CFM_STRIKEOUT | 
		CFM_COLOR | CFM_FACE | CFM_SIZE | CFM_CHARSET;
	m_ExpressionFont.dwEffects = (0);
	m_ExpressionFont.crTextColor = 0x00800000;
	strcpy(m_ExpressionFont.szFaceName, "Arial");
	m_ExpressionFont.yHeight = 175;
	//m_ExpressionFont.yHeight = 250;
	m_ExpressionFont.yOffset = 40;

	m_TotalCharacters = 0;
}

OutputView::~OutputView()
{
}

void OutputView::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(OutputView)
	DDX_Control(pDX, IDC_OUTPUT, m_Result);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(OutputView, CPropertyPage)
	//{{AFX_MSG_MAP(OutputView)
	ON_WM_SHOWWINDOW()
	ON_WM_KILLFOCUS()
	ON_NOTIFY(NM_KILLFOCUS, IDC_OUTPUT, OnKillfocusOutput)
	ON_WM_CAPTURECHANGED()
	ON_WM_SIZE()
	ON_NOTIFY(EN_KILLFOCUS, IDC_OUTPUT, OnKillfocusOutput)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OutputView message handlers

/*********************************************************/
// OutputView::OnEnter(CString Formula, CCalculator &Calculator, 
//					   CComboBox *FormulaCtrl)
// Pre: the window has been initialzed
// Post: Formula is evaluated and the answer is appended
//		 to the output
// Return Value:
// Intent: to evaluate Formula and add the answer and Formula
//		   to the output window
/*********************************************************/
void OutputView::OnEnter(CString Formula, CCalculator &Calculator, CComboBox *FormulaCtrl)
{	
	#ifdef TEST_MODE
	::ofstream ofile;
	ofile.open("C:\\GC Test Results.txt", ios::app, filebuf::openprot);
	#endif

	CString ans;
	CHARRANGE chrang;
	long double answer;

	if(Calculator.Compute(Formula, answer, this->m_hWnd) != SUCCESSFULL){
		// set the selection to nothing
		chrang.cpMax = m_Result.GetTextLength();
		chrang.cpMin = m_Result.GetTextLength();
		m_Result.SetSel(chrang);

		#ifdef TEST_MODE
		ofile.write("error in expression\n", 20);
		ofile.close();
		#endif

		return;
	}

	if(!m_fOutputWindow)
		return;
	
	// ADD FORMULA TO FORMULA DROPDOWN LIST
	if(FormulaCtrl->FindStringExact(-1, Formula) == CB_ERR){
			CArray<CString, CString> list;
			
			list.Add(Formula);
			
			for(int i(0); i < FormulaCtrl->GetCount(); ++i){
				CString temp;
				FormulaCtrl->GetLBText(i, temp);
				list.Add(temp);	
			}

			FormulaCtrl->ResetContent();
			
			for(int j(0); j < list.GetSize(); ++j)
				FormulaCtrl->AddString(list[j]);
	}
	///////////////////////////////////////

	// if answer is to big or too small we need ot go to scientific notation
	// or if the user is in scientific mode
	if(((answer > 99999999999999) || (answer < -99999999999999)
		|| ((answer < 0.0000000000001) && (answer > 0))
		|| ((answer > -0.0000000000001) && (answer < 0)) 
		|| ((Calculator.m_base == 10) && (Calculator.m_Normal))) && answer != 0.0){
		
		CString str;

		if(((answer < 0.0000000000001) && (answer > 0))
		|| ((answer > -0.0000000000001) && (answer < 0))
		|| (answer > 99999999999999) || (answer < -99999999999999))
			str.Format("%e", answer);
		else
			Calculator.DecimalToString(str, answer);

		Calculator.SetPrevAnswerStr(str);

		// because the output will be in base 10 regardless
		if(Calculator.m_base != 10){
			Calculator.m_ShowBase = true;
			Calculator.m_ConvertToBase = 10;
		}
		
		if(-HUGE_VAL == answer || HUGE_VAL == answer)
			ans = "overflow";
		else if(Calculator.m_Float)
			ans.Format("%e",answer);
		else
			ans.Format("%.*e", Calculator.m_DecimalPlaces, answer);
	}
	// if we are in floating mode go here
	else if(Calculator.m_Float){
		if(Calculator.DecimalToString(ans, answer) != SUCCESSFULL)
			return;

		Calculator.SetPrevAnswerStr(ans);
	}
	else{
		if(Calculator.DecimalToString(ans, answer) != SUCCESSFULL)
			return;

		Calculator.SetPrevAnswerStr(ans);

		if(ans != "overflow"){
			int  dec = ans.Find(".");
			if(dec == -1){
				ans += ".";
				dec = ans.Find(".");
			} else {
				ans = ans.Left(ans.Find('.') + Calculator.m_DecimalPlaces + 1);
			}

			CString right = ans.Right(ans.GetLength() - dec);
	
			while(right.GetLength() <= Calculator.m_DecimalPlaces){
				ans += "0";
				dec = ans.Find(".");
				right = ans.Right(ans.GetLength() - dec);
			}
		}
	}

	Calculator.FormatString(ans);

	if(!Calculator.m_ShowBase)
		ans += '\n';

	#ifdef TEST_MODE
	if(Calculator.m_ShowBase)
		ans += '\n';
	ofile.write(ans.GetBuffer(0), ans.GetLength());
	ofile.close();
	#endif

	Formula += "\n";
	
	CString long_output, base;

	if(m_LongOutput){
		long_output = Calculator.m_LongOutput;

		for(int i(0); i <= (ans.GetLength() * 2); ++i)
			long_output += "-";
		long_output += "\n";
	}
	
	if(Calculator.m_ShowBase)
	{
		base.Format("%d\n", Calculator.m_ConvertToBase);
		Calculator.m_ShowBase = false;
	}

	AddEntry(Formula, long_output, ans, base);
}

void OutputView::AddEntry(CString heading, CString body)
{
	heading += "\n";
	if(!body.IsEmpty())
		body += "\n";

	AddEntry(heading, "", body, "");
}
void OutputView::AddEntry(CString input, CString long_output, CString answer, CString base)
{
	if(!m_fOutputWindow)
		return;

	HaltRedraw();
	
	AddInputString(input);
	AddDetailedOutputString(long_output);
	AddAnswerString(answer);
	AddBaseString(base);

	// scroll down
	int count(0);
	if(!long_output.IsEmpty()){
		
		for(int i(0); i < long_output.GetLength(); ++i){
			if(long_output[i] == '\n')
				++count;
		}
	}

	::PostMessage(m_Result.m_hWnd, EM_SETSEL, -1, MAKELONG(-1, 0));
	::PostMessage(m_Result.m_hWnd, EM_SCROLLCARET,0,0);

	InvalidateRedraw()
}


/*********************************************************/
// OutputView::ClearOutput()
// Pre: none
// Post: output is cleared
// Return Value: none
// Intent: to clear the output window of all text
/*********************************************************/
void OutputView::ClearOutput()
{
	CHARRANGE chrang;
	chrang.cpMax = m_Result.GetTextLength();
	chrang.cpMin = 0;
	m_Result.SetSel(chrang);
	m_Result.SetReadOnly(false);
	m_Result.Cut();
	m_Result.SetReadOnly(true);

	m_Answers.RemoveAll();
	m_Bases.RemoveAll();
	m_Expressions.RemoveAll();
	m_LongOutputs.RemoveAll();

	m_TotalCharacters = 0;
}

void OutputView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	
	// set the selection to nothing
	CHARRANGE chrang;
	chrang.cpMax = m_Result.GetTextLength();
	chrang.cpMin = m_Result.GetTextLength();
	m_Result.SetSel(chrang);	
}

void OutputView::OnKillFocus(CWnd* pNewWnd) 
{
	CPropertyPage::OnKillFocus(pNewWnd);
	
	// set the selection to nothing
	CHARRANGE chrang;
	chrang.cpMax = m_Result.GetTextLength();
	chrang.cpMin = m_Result.GetTextLength();
	m_Result.SetSel(chrang);
}

void OutputView::OnKillfocusOutput(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// set the selection to nothing
	CHARRANGE chrang;
	chrang.cpMax = m_Result.GetTextLength();
	chrang.cpMin = m_Result.GetTextLength();
	m_Result.SetSel(chrang);
	
	*pResult = 0;
}

void OutputView::OnCaptureChanged(CWnd *pWnd) 
{
	// set the selection to nothing
	CHARRANGE chrang;
	chrang.cpMax = m_Result.GetTextLength();
	chrang.cpMin = m_Result.GetTextLength();
	m_Result.SetSel(chrang);
	
	CPropertyPage::OnCaptureChanged(pWnd);
}
/*********************************************************/
// OutputView::PreTranslateMessage(MSG* pMsg) 
// Pre: none
// Post: none
// Return Value: handled by parent function
// Intent: to capture the user right clicking on the output
//		   window.  all other messages are forwarded off for
//		   normal handling
/*********************************************************/
BOOL OutputView::PreTranslateMessage(MSG* pMsg) 
{	
	return CPropertyPage::PreTranslateMessage(pMsg);
}

void OutputView::Print()
{

	CDC             dc;
    CPrintDialog    printDlg(FALSE);
    CRect           r;
    //int             nHeight;
    
    // ask the user to select a printer
    if (printDlg.DoModal() == IDCANCEL)
        return;
    
    // Attach a printer DC
    dc.Attach(printDlg.GetPrinterDC());
    dc.m_bPrinting = TRUE;

    dc.SetMapMode(MM_TEXT);
        
    // Initialise print document details
    DOCINFO di;
    ::ZeroMemory (&di, sizeof (DOCINFO));
    di.cbSize = sizeof (DOCINFO);
    // application title appears in the spooler view
    di.lpszDocName = "GraphCalc Output Window";
    
    // Begin a new print job
    BOOL bPrintingOK = dc.StartDoc( &di );
        
    // Get the printing extents and store in the m_rectDraw field of a 
    // CPrintInfo object
    int w = dc.GetDeviceCaps(HORZRES);
    int h = dc.GetDeviceCaps(VERTRES);

	double w_margin_inches(0.5), h_margin_inches(0.5);
	w_margin_inches -= 0.125;  // because of built in margin when printing
	h_margin_inches -= 0.125;  // because of built in margin when printing

	int w_margin_pixels(dc.GetDeviceCaps(LOGPIXELSX) * w_margin_inches);
	int h_margin_pixels(dc.GetDeviceCaps(LOGPIXELSY) * h_margin_inches);
    m_Info.m_rectDraw.SetRect(w_margin_pixels, h_margin_pixels, w - w_margin_pixels, h - h_margin_pixels);
        
	int maxx(0), start(0);
	m_Info.m_nCurPage = 0;

	while(maxx < m_Expressions.GetSize()){

		dc.StartPage();
        ++m_Info.m_nCurPage;

		r = m_Info.m_rectDraw;	
		r.bottom = r.top;
        
		start = maxx;
		maxx = FindMaxPageEntry(start, r, m_Info.m_rectDraw.right, dc);

		if(maxx < start)
			maxx = start;

		for(int i(start); i <= maxx; ++i){

			PrintExpression(dc, r, m_Expressions[i].Left(m_Expressions[i].GetLength() - 1));
			r.right = m_Info.m_rectDraw.right;
			
			if(!m_LongOutputs[i].IsEmpty()){
				PrintLongOutput(dc, r, m_LongOutputs[i].Left(m_LongOutputs[i].GetLength() - 1));
				r.right = m_Info.m_rectDraw.right;
			}

			PrintAnswer(dc, r, i, m_Info.m_rectDraw.right);
			r.right = m_Info.m_rectDraw.right;
        }
        
        bPrintingOK = (dc.EndPage() > 0);
		++maxx;
    }
    
	//////////////////////////////////////////////////////
    // end a print job
    if (bPrintingOK)
        dc.EndDoc();
    else
        dc.AbortDoc();
    
    dc.Detach();
}

void OutputView::SetPrintRectangle(CDC &dc, CRect &r, CString str)
{
	// calc how big string block is		
	r.top = r.bottom = r.top + dc.DrawText(str, -1, r, 
		DT_CALCRECT|DT_WORDBREAK|DT_NOCLIP|DT_EXPANDTABS);
}

int OutputView::FindMaxPageEntry(int start, CRect r, int right, CDC &dc)
{
	int i(start);
	while ((r.bottom < m_Info.m_rectDraw.bottom) && (i < m_Expressions.GetSize()))
    {
		PrintString(dc, r, m_Expressions[i].Left(m_Expressions[i].GetLength() - 1), GetPrintLogFont(EXPRESSION, dc), RGB(7,40,74), DT_LEFT, 0);
		r.right = right;
		PrintString(dc, r, m_LongOutputs[i].Left(m_LongOutputs[i].GetLength() - 1), GetPrintLogFont(LONG_OUTPUT, dc), RGB(0,128,0), DT_RIGHT, 0);
		r.right = right;
		PrintString(dc, r, m_Answers[i], GetPrintLogFont(ANSWER, dc), RGB(88,0,0), DT_RIGHT, 0);
		r.right = right;

		if(r.bottom >= m_Info.m_rectDraw.bottom)
			return (i - 1);
		else if((m_Expressions.GetSize() - 1) == i)
			return i;

		++i;
	}
	return 0;
}

LOGFONT OutputView::GetPrintLogFont(EOutputEntry entry, CDC &dc)
{
	LOGFONT LogFont;
    
	switch(entry){
	case EXPRESSION: 
		LogFont = m_LFExpressionFont;
		LogFont.lfWidth = 0;
		LogFont.lfHeight = -MulDiv(abs(LogFont.lfHeight), GetDeviceCaps(dc, LOGPIXELSY), 72);
		return LogFont;
	case ANSWER: 
		LogFont = m_LFAnswerFont;
		LogFont.lfWidth = 0;
		LogFont.lfHeight = -MulDiv(abs(LogFont.lfHeight), GetDeviceCaps(dc, LOGPIXELSY), 72);
		return LogFont;
	case LONG_OUTPUT:
		LogFont = m_LFLongOutputFont;
		LogFont.lfWidth = 0;
		LogFont.lfHeight = -MulDiv(abs(LogFont.lfHeight), GetDeviceCaps(dc, LOGPIXELSY), 72);
	case BASE:
		LogFont = m_LFBaseFont;
		LogFont.lfWidth = 0;
		LogFont.lfHeight = -MulDiv(abs(LogFont.lfHeight), GetDeviceCaps(dc, LOGPIXELSY), 72);
	} 

	switch(entry){
	case EXPRESSION: LogFont.lfHeight = -MulDiv(10, GetDeviceCaps(dc, LOGPIXELSY), 72); break;
	case LONG_OUTPUT: LogFont.lfHeight = -MulDiv(8, GetDeviceCaps(dc, LOGPIXELSY), 72); break;
	case ANSWER: LogFont.lfHeight = -MulDiv(10, GetDeviceCaps(dc, LOGPIXELSY), 72); break;
	case BASE: LogFont.lfHeight = -MulDiv(7, GetDeviceCaps(dc, LOGPIXELSY), 72); break;
	}
    LogFont.lfWidth = 0;
    LogFont.lfEscapement = 0;
    LogFont.lfOrientation = 0;
	switch(entry){
	case EXPRESSION: LogFont.lfWeight = 0; break;
	case LONG_OUTPUT: LogFont.lfWeight = 0; break;
	case ANSWER: LogFont.lfWeight = FW_BOLD; break;
	case BASE: LogFont.lfWeight = 0; break;
	}    
    LogFont.lfItalic = false;
    LogFont.lfUnderline = 0;
    LogFont.lfStrikeOut = 0;
    LogFont.lfCharSet = ANSI_CHARSET;
    LogFont.lfOutPrecision = OUT_TT_PRECIS;
    LogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    LogFont.lfQuality = DEFAULT_QUALITY;
    LogFont.lfPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
    lstrcpy (LogFont.lfFaceName, "Arial");
 
	return LogFont;
}

void OutputView::PrintString(CDC &dc, CRect &r, CString str, LOGFONT lgfont, COLORREF color, UINT align, UINT print_mode){

	CFont	aFont, *oldFont;
	aFont.CreateFontIndirect ( &lgfont );
	oldFont = dc.SelectObject( &aFont ); 
	dc.SetBkMode(OPAQUE);  
	dc.SetTextColor(color);

	CString nstr, temp;

	while(!str.IsEmpty()){
		int count(0), width(0);
		char cur(str[0]);
		str.Delete(0,1);

		CRect b = r;
		CString st = cur;
		dc.DrawText(st, -1, b, DT_CALCRECT|DT_WORDBREAK|DT_NOCLIP|DT_EXPANDTABS|DT_RIGHT);	
		width = b.Width();
		
		if(!(cur == '-' && str[0] == '-')){
			while((cur != '\n') && !str.IsEmpty() && width <= r.Width()){
				temp += cur;
				++count;
				cur = str[0];
				str.Delete(0,1);

				b = r;
				st = temp + cur;
				dc.DrawText(st, -1, b, DT_CALCRECT|DT_WORDBREAK|DT_NOCLIP|DT_EXPANDTABS|DT_RIGHT);	
				width = b.Width();
			}
		}
		else{
			temp = cur + str;
			str.Empty();
		}

		CString pre_str;

		if(cur == '\n'){
			pre_str = temp + cur;
			temp.Empty();
		}
		else if(width > r.Width()){
			
			if(str.IsEmpty())
				temp += cur;

			int j(count-1);
			while((j >= 0) && (temp[j] != '+') && (temp[j] != '*') && (temp[j] != '/') && (temp[j] != '-')) --j;

			if(j < 0){
				pre_str = temp + "\n";
				temp.Empty();
			}
			else{
				pre_str = temp.Left(j + 1) + "\n";
				temp.Delete(0, j+1);
			}
		}
		else{
			if(str.IsEmpty())
				temp += cur;

			pre_str = temp + "\n";
			temp.Empty();
		}
		
		if(print_mode == 1){
			CRect t(r);
			t.bottom = t.top + dc.DrawText(nstr + pre_str, -1, t, DT_CALCRECT|DT_WORDBREAK|DT_EXPANDTABS|align);
			if(t.bottom >= m_Info.m_rectDraw.bottom){
				nstr = nstr.Left(nstr.GetLength() - 1);					
				
				dc.DrawText(nstr, -1, r, DT_WORDBREAK|DT_NOCLIP|DT_EXPANDTABS|align);
				
				r.top = r.bottom = r.top + dc.DrawText(nstr, -1, r, DT_CALCRECT|DT_WORDBREAK|DT_EXPANDTABS|align);
				
				dc.EndPage();
				dc.StartPage();
				++m_Info.m_nCurPage;				
				r = m_Info.m_rectDraw;	
				r.bottom = r.top;				
				nstr = pre_str;
			}
			else
				nstr += pre_str;
		}
		else
			nstr += pre_str;
	}
	str = nstr.Left(nstr.GetLength() - 1);	

	if(print_mode == 1)
		dc.DrawText(str, -1, r, DT_WORDBREAK|DT_NOCLIP|DT_EXPANDTABS|align);

	r.top = r.bottom = r.top + dc.DrawText(str, -1, r, DT_CALCRECT|DT_WORDBREAK|DT_EXPANDTABS|align);

    dc.SelectObject(oldFont);
    aFont.DeleteObject();
}

void OutputView::PrintExpression(CDC &dc, CRect &r, CString str)
{	
	PrintString(dc, r, str, GetPrintLogFont(EXPRESSION, dc), RGB(7,40,74), DT_LEFT, 1);
}

void OutputView::PrintLongOutput(CDC &dc, CRect &r, CString str)
{
	PrintString(dc, r, str, GetPrintLogFont(LONG_OUTPUT, dc), RGB(0,128,0), DT_RIGHT, 1);
}

void OutputView::PrintAnswer(CDC &dc, CRect &r, UINT i, UINT right)
{	
	if(m_Bases[i].IsEmpty()){
		PrintString(dc, r, m_Answers[i], GetPrintLogFont(ANSWER, dc), RGB(88,0,0), DT_RIGHT, 1);
	}
	else{
		//// figure out where to draw answer and base		
		CRect b = r;
		
		LOGFONT LogFont;    
		LogFont = GetPrintLogFont(BASE, dc);
		CFont	aFont, *oldFont;
		aFont.CreateFontIndirect ( &LogFont );
		oldFont = dc.SelectObject( &aFont );  
		dc.DrawText(m_Bases[i].Left(m_Bases[i].GetLength() - 1), -1, b, 
			DT_CALCRECT|DT_WORDBREAK|DT_NOCLIP|DT_EXPANDTABS|DT_RIGHT);			
		dc.SelectObject(oldFont);
		aFont.DeleteObject();
		
		int w(b.Width());
		r.right -= w;
		
		b.left = r.right;
		b.right = b.left + w;
		
		PrintString(dc, r, m_Answers[i], GetPrintLogFont(ANSWER, dc), RGB(88,0,0), DT_RIGHT, 1);
		
		b.top = r.top - 60;
		b.bottom = r.bottom - 60;

		PrintBase(dc, b, m_Bases[i].Left(m_Bases[i].GetLength() - 1));
	}
}

void OutputView::PrintBase(CDC &dc, CRect &r, CString str)
{
	LOGFONT LogFont;    
    LogFont = GetPrintLogFont(BASE, dc);
    CFont	aFont, *oldFont;
    dc.SetBkMode(OPAQUE);
    aFont.CreateFontIndirect ( &LogFont );
    oldFont = dc.SelectObject( &aFont );  

	dc.SetTextColor(RGB(0,0,88));

	dc.DrawText(str, -1, r, DT_WORDBREAK|DT_NOCLIP|DT_EXPANDTABS|DT_RIGHT);
	
    dc.SelectObject(oldFont);
    aFont.DeleteObject();
}

void OutputView::DisplayString(CString str, CHARFORMAT font, UINT align){
	CHARRANGE chrang;
	PARAFORMAT para;
	
	chrang.cpMax = m_Result.GetTextLength();
	chrang.cpMin = chrang.cpMax;
	
	m_Result.SetSel(chrang);
	m_Result.ReplaceSel(str.GetBuffer(0));

	m_TotalCharacters += str.GetLength();
	
	if(str[str.GetLength() - 1] == '\n')
		chrang.cpMax = m_TotalCharacters - 1;
	else
		chrang.cpMax = m_TotalCharacters;
	
	chrang.cpMin = m_TotalCharacters - str.GetLength();

	if(chrang.cpMin < 0)
		chrang.cpMin = 0;

	m_Result.SetSel(chrang);
	
	para.dwMask = PFM_ALIGNMENT;
	para.wAlignment = align;
	
	m_Result.SetParaFormat(para);
	m_Result.SetSelectionCharFormat(font);
}

void OutputView::AddInputString(CString str)
{
	if(!str.IsEmpty())
	{
		DisplayString(str, m_ExpressionFont, PFA_LEFT);
	}
	m_Expressions.Add(str);
}

void OutputView::AddDetailedOutputString(CString str)
{
	if(!str.IsEmpty()){
		DisplayString(str, m_LongOutputFont, PFA_RIGHT);
	}
	m_LongOutputs.Add(str);
}

void OutputView::AddAnswerString(CString str)
{
	if(!str.IsEmpty())
	{
		DisplayString(str, m_AnswerFont, PFA_RIGHT);
	}
	m_Answers.Add(str);
}

void OutputView::AddBaseString(CString str)
{
	if(!str.IsEmpty())
	{
		DisplayString(str, m_BaseFont, PFA_RIGHT);
	}
	m_Bases.Add(str);
}

void OutputView::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);

	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_OUTPUT);
    if(pWnd != NULL){
		pWnd->SetWindowPos(this, 0, 0, cx, cy, SWP_NOOWNERZORDER | SWP_NOZORDER);
	}
}

void OutputView::SaveOutput()
{
	::ofstream outfile;
	char pound = '#';
	char new_line = '\n';

	chdir(g_strApplicationDirectory);
	outfile.open("output_history.dat");
	
	for(int i(0); i < m_Expressions.GetSize(); ++i){
		
		outfile.write(&pound, 1);
		outfile.write(&new_line, 1);
		outfile.write(m_Expressions[i].GetBuffer(m_Expressions[i].GetLength()), m_Expressions[i].GetLength());
		if(m_Expressions[i].IsEmpty() || m_Expressions[i][m_Expressions[i].GetLength() - 1] != '\n')
			outfile.write(&new_line, 1);

		outfile.write(&pound, 1);
		outfile.write(&new_line, 1);
		outfile.write(m_LongOutputs[i].GetBuffer(m_LongOutputs[i].GetLength()), m_LongOutputs[i].GetLength());
		if(m_LongOutputs[i].IsEmpty() || m_LongOutputs[i][m_LongOutputs[i].GetLength() - 1] != '\n')
			outfile.write(&new_line, 1);
		
		outfile.write(&pound, 1);
		outfile.write(&new_line, 1);
		outfile.write(m_Answers[i].GetBuffer(m_Answers[i].GetLength()), m_Answers[i].GetLength());
		
		if(m_Answers[i].IsEmpty() || m_Answers[i][m_Answers[i].GetLength() - 1] != '\n')
			outfile.write(&new_line, 1);

		outfile.write(&pound, 1);
		outfile.write(&new_line, 1);
		outfile.write(m_Bases[i].GetBuffer(m_Bases[i].GetLength()), m_Bases[i].GetLength());

		outfile.write(&new_line, 1);
	}
	
	outfile.close();
}

void OutputView::LoadOutput()
{
	::ifstream infile;
	infile.open("output_history.dat", ios::nocreate);
	
	if(infile.rdstate() == ios::failbit){
		//AfxMessageBox("Error opening output_history.dat", MB_OK | MB_ICONEXCLAMATION, 0);
		return;
	}

	CString value, input, long_output, ans;
	bool done(false);
	int part(0);  // 0 - input, 1 - long output, 2 - answer, 3 - base
	char *line = new char[1000];
	
	infile.getline(line, 1000, '\n');
	value = (LPCTSTR)line;
	value.TrimLeft();
	value.TrimRight();

	if(value.IsEmpty() || value[0] != '#'){
		infile.close();
		delete line;
		return;
	}

	while(!infile.eof()){

		input = long_output = ans = "";
		part = 0;
		done = false;
		
		while(part < 4 && !infile.eof()){
			infile.getline(line, 1000, '\n');
			value = (LPCTSTR)line;
			value.TrimLeft();
			value.TrimRight();
			
			if(!value.IsEmpty() && value[0] == '#')
				++part;
			else{
				switch(part){
				case 0:
					input = value + "\n";
					break;
				case 1:
					if(!value.IsEmpty())
						long_output += value + "\n";
					break;
				case 2:
					ans = value;
					break;
				case 3:
					if(!input.IsEmpty() && !ans.IsEmpty() && !done){
						done = true;
						if(value.IsEmpty())
							ans += "\n";
						else if(value[value.GetLength() - 1] != '\n')
							value += "\n";
						
						AddEntry(input, long_output, ans, value);
					}
					break;
				}
			}
		}
	}

	delete line;
	infile.close();
}

BOOL OutputView::OnSetActive() 
{
	CGrphCalcDlg* pDlg = (CGrphCalcDlg*)STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	pDlg->SetMenu(&m_MenuOutput);
	pDlg->PostMessage(WM_SETFULLWINDOW, 0, 0);

	/* NEEDED BECAUSE GOING INTO GRAPH OPTIONS MOVES
	   AND CHANGES THE SIZE OF THE WINDOW FOR SOME ODD REASON
	*/
	CCalculatorView *pWnd = (CCalculatorView*)GetParent();
	MoveWindow(&pWnd->m_PageRect); 
	// END POSITIONING OF WINDOW

	// move cursor to bottom
	CHARRANGE chrang;
	chrang.cpMax = 0;
	chrang.cpMin = m_Result.GetTextLength();
	m_Result.SetSel(chrang);

	::PostMessage(m_Result.m_hWnd, EM_SETSEL, -1, MAKELONG(-1, 0));
	::PostMessage(m_Result.m_hWnd, EM_SCROLLCARET,0,0);
	// end move to bottom

	return CPropertyPage::OnSetActive();
}

BOOL OutputView::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();	

	CMenu PopUpView;
	PopUpView.LoadMenu(IDR_VIEW);
	
	m_MenuOutput.LoadMenu(IDR_MENU);
	CGrphCalcDlg* pDlg = (CGrphCalcDlg*)STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	pDlg->AddScriptLibraryMenu(m_MenuOutput, 3);

	m_MenuOutput.InsertMenu(5, MF_BYPOSITION|MF_POPUP|MF_ENABLED, (UINT)PopUpView.m_hMenu, "View");
	PopUpView.Detach();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void OutputView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	/* NEEDED BECAUSE GOING INTO GRAPH OPTIONS MOVES
	   AND CHANGES THE SIZE OF THE WINDOW FOR SOME ODD REASON
	*/
	//CCalculatorView *pWnd = (CCalculatorView*)GetParent();
	//MoveWindow(&pWnd->m_PageRect); 
	// END POSITIONING OF WINDOW	
	// Do not call CPropertyPage::OnPaint() for painting messages
}


static DWORD CALLBACK StreamOutCtrl (DWORD dwCookie, LPBYTE pbBuff,
                                     LONG cb, LONG* pcb)
{
  CFile *pstr = (CFile*)dwCookie;

  pstr->Write(pbBuff, cb);
  *pcb = cb;

  return 0;
}

void OutputView::SaveOutputToFile(CString strFile)
	{
	CFile sf(strFile, CFile::modeWrite | CFile::modeCreate);

	EDITSTREAM es;
	es.dwCookie = (DWORD)&sf;
	es.dwError = 0;
	es.pfnCallback = StreamOutCtrl;
 
	m_Result.StreamOut(SF_RTF , es);

	}
