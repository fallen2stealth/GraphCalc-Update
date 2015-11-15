// Mode.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "Mode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef MAX_PLACES
#define MAX_PLACES
const int max_places[37] = {0 , 0,52,32,26,22,20,18,17,16,
							15,15,14,14,13,13,13,12,12,12,
							12,11,11,11,11,11,11,10,10,10,
							10,10,10,10,10,10,10};
#endif

extern CCalculator *g_Calculator;
/////////////////////////////////////////////////////////////////////////////
// Mode dialog


Mode::Mode(CWnd* pParent /*=NULL*/)
	: CDialog(Mode::IDD, pParent)
{
	//{{AFX_DATA_INIT(Mode)
	m_TrigUnits = 0;
	m_DecPlaces = 5;
	m_Float = TRUE;
	m_OutputMode = 0;
	m_Base = 10;
	m_IntlMode = -1;
	m_DecimalSeperatorAmount = 2;
	m_DecimalSpaceSeperator = _T(" ");
	m_DecimalSeperator = FALSE;
	m_NumberSpaceSeperator = _T(",");
	m_NumberSeperatorAmount = 2;
	m_NumberSeperator = TRUE;
	//}}AFX_DATA_INIT

	m_Sample = 12345678.1234567;
}

void Mode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Mode)
	DDX_Control(pDX, IDC_DECIMAL_PLACES, m_FloatCtrl);
	DDX_Radio(pDX, IDC_UNITS, m_TrigUnits);
	DDX_Text(pDX, IDC_DECIMAL_PLACES, m_DecPlaces);
	DDX_Check(pDX, IDC_FLOAT, m_Float);
	DDX_Radio(pDX, IDC_SCIENTIFIC, m_OutputMode);
	DDX_Text(pDX, IDC_BASE, m_Base);
	DDV_MinMaxInt(pDX, m_Base, 2, 36);
	DDX_Radio(pDX, IDC_INTLMODE, m_IntlMode);
	DDX_CBIndex(pDX, IDC_DEC_FREQ, m_DecimalSeperatorAmount);
	DDX_Text(pDX, IDC_DEC_CHAR, m_DecimalSpaceSeperator);
	DDV_MaxChars(pDX, m_DecimalSpaceSeperator, 1);
	DDX_Check(pDX, IDC_DEC_SEP, m_DecimalSeperator);
	DDX_Text(pDX, IDC_NUM_CHAR, m_NumberSpaceSeperator);
	DDV_MaxChars(pDX, m_NumberSpaceSeperator, 1);
	DDX_CBIndex(pDX, IDC_NUM_FREQ, m_NumberSeperatorAmount);
	DDX_Check(pDX, IDC_NUM_SEP, m_NumberSeperator);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Mode, CDialog)
	//{{AFX_MSG_MAP(Mode)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_FLOAT, OnFloat)
	ON_EN_CHANGE(IDC_BASE, OnChangeBase)
	ON_BN_CLICKED(IDC_NUM_SEP, OnNumSep)
	ON_BN_CLICKED(IDC_DEC_SEP, OnDecSep)
	ON_EN_CHANGE(IDC_DEC_CHAR, OnChangeDecChar)
	ON_EN_CHANGE(IDC_NUM_CHAR, OnChangeNumChar)
	ON_CBN_SELCHANGE(IDC_NUM_FREQ, OnSelchangeNumFreq)
	ON_CBN_SELCHANGE(IDC_DEC_FREQ, OnSelchangeDecFreq)
	ON_EN_CHANGE(IDC_DECIMAL_PLACES, OnChangeDecimalPlaces)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_INTLMODE, OnIntlmode)
	ON_BN_CLICKED(IDC_SCIENTIFIC, OnScientific)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Mode message handlers


BOOL Mode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// Set Spin control
	CSpinButtonCtrl *pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_DECIMAL_PLACES_SPIN);
	pSpin->SetRange(0, max_places[m_Base]);
	pSpin->SetPos(m_DecPlaces);

	// Disable decimal places if float is checked
	if(BST_CHECKED == IsDlgButtonChecked(IDC_FLOAT))
		m_FloatCtrl.EnableWindow(false);

	// Set Spin control for base
	pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_BASE_SPIN);
	pSpin->SetRange(2, 36);
	pSpin->SetPos(m_Base);

	OnDecSep();
	OnNumSep();
	UpdateSample();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************/
// Mode::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
// Pre: none
// Post: none
// Return Value: none
// Intent: called by framework when the user clicks on the
//		   button to change the number of decimal places
/*********************************************************/
void Mode::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(nSBCode == SB_ENDSCROLL){
		return;
	}

	if((pScrollBar->GetDlgCtrlID() == IDC_DECIMAL_PLACES_SPIN)
		&& (BST_CHECKED != IsDlgButtonChecked(IDC_FLOAT))){
		UpdateData(true);
		m_DecPlaces = nPos;
		UpdateSample();
		UpdateData(false);
	}
	else if(pScrollBar->GetDlgCtrlID() == IDC_BASE_SPIN){
		UpdateData(true);
		m_Base = nPos;
		

		CSpinButtonCtrl *pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_DECIMAL_PLACES_SPIN);
		pSpin->SetRange(0, max_places[m_Base]);

		if(max_places[m_Base] < m_DecPlaces)
			m_DecPlaces = max_places[m_Base];

		UpdateSample();
		UpdateData(false);
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

/*********************************************************/
// Mode::OnFloat() 
// Pre: none
// Post: none
// Return Value: none
// Intent: falled by framework when the user clicks on 
//		   the float button
/*********************************************************/
void Mode::OnFloat() 
{
	if(BST_CHECKED == IsDlgButtonChecked(IDC_FLOAT)){
		m_FloatCtrl.EnableWindow(false);
		g_Calculator->m_Float = true;
	}
	else{
		g_Calculator->m_Float = false;
		m_FloatCtrl.EnableWindow();
	}
	
	UpdateSample();
}

void Mode::OnChangeBase() 
{
	UpdateData(true);
	CSpinButtonCtrl *pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_DECIMAL_PLACES_SPIN);
	pSpin->SetRange(0, max_places[m_Base]);
	
	pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_BASE_SPIN);
	pSpin->SetPos(m_Base);

	UpdateData(false);
}

void Mode::OnNumSep() 
{
	if(BST_CHECKED == IsDlgButtonChecked(IDC_NUM_SEP)){
		CWnd* item = GetDlgItem(IDC_NUM_FREQ);
		item->EnableWindow();
		item =  GetDlgItem(IDC_NUM_CHAR);
		item->EnableWindow();
		item =  GetDlgItem(IDC_NUMC);
		item->EnableWindow();
		item =  GetDlgItem(IDC_NUMF);
		item->EnableWindow();
	}
	else{
		CWnd* item = GetDlgItem(IDC_NUM_FREQ);
		item->EnableWindow(false);
		item =  GetDlgItem(IDC_NUM_CHAR);
		item->EnableWindow(false);
		item =  GetDlgItem(IDC_NUMC);
		item->EnableWindow(false);
		item =  GetDlgItem(IDC_NUMF);
		item->EnableWindow(false);
	}

	UpdateData(true);
	g_Calculator->m_NumberSeperator = (m_NumberSeperator == 1);
	UpdateSample();
	UpdateData(false);
}

void Mode::OnDecSep() 
{
	if(BST_CHECKED == IsDlgButtonChecked(IDC_DEC_SEP))
	{
		CWnd* item =  GetDlgItem(IDC_DEC_FREQ);
		item->EnableWindow();
		item =  GetDlgItem(IDC_DEC_CHAR);
		item->EnableWindow();
		item =  GetDlgItem(IDC_DECC);
		item->EnableWindow();
		item =  GetDlgItem(IDC_DECF);
		item->EnableWindow();
	}
	else
	{
		CWnd* item =  GetDlgItem(IDC_DEC_FREQ);
		item->EnableWindow(false);
		item =  GetDlgItem(IDC_DEC_CHAR);
		item->EnableWindow(false);
		item =  GetDlgItem(IDC_DECC);
		item->EnableWindow(false);
		item =  GetDlgItem(IDC_DECF);
		item->EnableWindow(false);
	}

	UpdateData(true);
	g_Calculator->m_DecimalSeperator = (m_DecimalSeperator == 1);
	UpdateSample();
	UpdateData(false);
}

void Mode::OnChangeDecChar() 
{
	UpdateData(true);

	if(m_DecimalSpaceSeperator.IsEmpty()){
		UpdateData(false);
		return;
	}

	g_Calculator->m_DecimalSpaceSeperator = m_DecimalSpaceSeperator[0];
	UpdateSample();
	UpdateData(false);
}

void Mode::OnChangeNumChar() 
{
	UpdateData(true);

	if(m_NumberSpaceSeperator.IsEmpty()){
		UpdateData(false);
		return;
	}

	g_Calculator->m_NumberSpaceSeperator = m_NumberSpaceSeperator[0];
	UpdateSample();
	UpdateData(false);
}

void Mode::OnSelchangeNumFreq() 
{
	UpdateData(true);
	g_Calculator->m_NumberSeperatorAmount = m_NumberSeperatorAmount + 1;
	UpdateSample();
	UpdateData(false);
}

void Mode::OnSelchangeDecFreq() 
{
	UpdateData(true);
	g_Calculator->m_DecimalSeperatorAmount = m_DecimalSeperatorAmount + 1;
	UpdateSample();
	UpdateData(false);
}

void Mode::UpdateSample()
{
	CString temp; // = m_Sample;
	// chop off extra decimals
	/*if(m_DecPlaces <= 7 && !g_Calculator->m_Float){
		int ln = m_Sample.GetLength();
		int pos = m_Sample.Find(".");
		temp = m_Sample.Left(ln - pos + m_DecPlaces + 1);
	}*/
	
	if(m_OutputMode == 0){
		if(m_DecPlaces <= 7 && !g_Calculator->m_Float)
			temp.Format("%8.*f", m_DecPlaces, m_Sample);
		else
			temp.Format("%8.7f", m_Sample);
	}
	else{
		if(m_DecPlaces <= 7 && !g_Calculator->m_Float)
			temp.Format("%8.*e", m_DecPlaces, m_Sample);
		else
			temp.Format("%8.7e", m_Sample);
	}
	
	temp.TrimLeft();
	temp.TrimRight();

	if(m_IntlMode == 1)
		temp.Replace(".", ",");

	g_Calculator->FormatString(temp);
	SetDlgItemText(IDC_SAMPLE, temp);
}

void Mode::OnChangeDecimalPlaces() 
{
	UpdateData(true);
	UpdateSample();
	UpdateData(false);	
}

void Mode::OnRadio3() 
{
	UpdateData(true);
	g_Calculator->m_IntlMode = (InternationalModeE)m_IntlMode;
	UpdateSample();
	UpdateData(false);	
}

void Mode::OnIntlmode() 
{
	UpdateData(true);
	g_Calculator->m_IntlMode = (InternationalModeE)m_IntlMode;
	UpdateSample();
	UpdateData(false);	
}

void Mode::OnScientific() 
{
	UpdateData(true);
	UpdateSample();
	UpdateData(false);
}

void Mode::OnRadio4() 
{
	UpdateData(true);
	UpdateSample();
	UpdateData(false);
}
