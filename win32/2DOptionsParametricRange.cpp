// 2DOptionsParametricRange.cpp : implementation file
//

#include "stdafx.h"
#include "grphcalc.h"
#include "2DOptionsParametricRange.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct SControlValues{
	UINT nID;
	CString *strVal;
	long double *dVal;
};

SControlValues ParametricRangeCtrls[] = {
		{IDC_XMAX, 0, 0},
		{IDC_XMIN, 0, 0},
		{IDC_XINT, 0, 0},
		{IDC_YMAX, 0, 0},
		{IDC_YMIN, 0, 0},
		{IDC_YINT, 0, 0},
		{IDC_TMAX, 0, 0},
		{IDC_TMIN, 0, 0},
		{IDC_TSTEP, 0, 0},
		{0,0}
};


/////////////////////////////////////////////////////////////////////////////
// C2DOptionsParametricRange property page

IMPLEMENT_DYNCREATE(C2DOptionsParametricRange, CPropertyPage)

C2DOptionsParametricRange::C2DOptionsParametricRange() : CPropertyPage(C2DOptionsParametricRange::IDD)
{
	//{{AFX_DATA_INIT(C2DOptionsParametricRange)
	m_strTmax = _T("10");
	m_strTmin = _T("0");
	m_strTstep = _T("0.1");
	m_strXscl = _T("1");
	m_strXmax = _T("10");
	m_strXmin = _T("-10");
	m_strYscl = _T("1");
	m_strYmax = _T("10");
	m_strYmin = _T("-10");
	//}}AFX_DATA_INIT
	
	m_fDirty = false;

	ParametricRangeCtrls[0].strVal = &m_strXmax;
	ParametricRangeCtrls[1].strVal = &m_strXmin;
	ParametricRangeCtrls[2].strVal = &m_strXscl;
	ParametricRangeCtrls[3].strVal = &m_strYmax;
	ParametricRangeCtrls[4].strVal = &m_strYmin;
	ParametricRangeCtrls[5].strVal = &m_strYscl;
	ParametricRangeCtrls[6].strVal = &m_strTmax;
	ParametricRangeCtrls[7].strVal = &m_strTmin;
	ParametricRangeCtrls[8].strVal = &m_strTstep;
	
	ParametricRangeCtrls[0].dVal = &m_dXmax;
	ParametricRangeCtrls[1].dVal = &m_dXmin;
	ParametricRangeCtrls[2].dVal = &m_dXscl;
	ParametricRangeCtrls[3].dVal = &m_dYmax;
	ParametricRangeCtrls[4].dVal = &m_dYmin;
	ParametricRangeCtrls[5].dVal = &m_dYscl;
	ParametricRangeCtrls[6].dVal = &m_dTmax;
	ParametricRangeCtrls[7].dVal = &m_dTmin;
	ParametricRangeCtrls[8].dVal = &m_dTstep;
}

C2DOptionsParametricRange::~C2DOptionsParametricRange()
{
}

void C2DOptionsParametricRange::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C2DOptionsParametricRange)
	//}}AFX_DATA_MAP
	if(!pDX->m_bSaveAndValidate)
		{
		DDX_Text(pDX, IDC_TMAX, m_strTmax);
		DDX_Text(pDX, IDC_TMIN, m_strTmin);
		DDX_Text(pDX, IDC_TSTEP, m_strTstep);
		DDX_Text(pDX, IDC_XINT, m_strXscl);
		DDX_Text(pDX, IDC_XMAX, m_strXmax);
		DDX_Text(pDX, IDC_XMIN, m_strXmin);
		DDX_Text(pDX, IDC_YINT, m_strYscl);
		DDX_Text(pDX, IDC_YMAX, m_strYmax);
		DDX_Text(pDX, IDC_YMIN, m_strYmin);
		}
	else if(!ValidateFieldValues() || !ValidateRanges())
		pDX->Fail();
}


BEGIN_MESSAGE_MAP(C2DOptionsParametricRange, CPropertyPage)
	//{{AFX_MSG_MAP(C2DOptionsParametricRange)
	ON_EN_CHANGE(IDC_TMAX, SetDirty)
	ON_EN_CHANGE(IDC_TMIN, SetDirty)
	ON_EN_CHANGE(IDC_TSTEP, SetDirty)
	ON_EN_CHANGE(IDC_XINT, SetDirty)
	ON_EN_CHANGE(IDC_XMAX, SetDirty)
	ON_EN_CHANGE(IDC_XMIN, SetDirty)
	ON_EN_CHANGE(IDC_YINT, SetDirty)
	ON_EN_CHANGE(IDC_YMAX, SetDirty)
	ON_EN_CHANGE(IDC_YMIN, SetDirty)
	ON_EN_KILLFOCUS(IDC_TMAX, OnKillfocusTmax)
	ON_EN_KILLFOCUS(IDC_TMIN, OnKillfocusTmin)
	ON_EN_KILLFOCUS(IDC_TSTEP, OnKillfocusTstep)
	ON_EN_KILLFOCUS(IDC_XINT, OnKillfocusXint)
	ON_EN_KILLFOCUS(IDC_XMAX, OnKillfocusXmax)
	ON_EN_KILLFOCUS(IDC_XMIN, OnKillfocusXmin)
	ON_EN_KILLFOCUS(IDC_YINT, OnKillfocusYint)
	ON_EN_KILLFOCUS(IDC_YMAX, OnKillfocusYmax)
	ON_EN_KILLFOCUS(IDC_YMIN, OnKillfocusYmin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C2DOptionsParametricRange message handlers

void C2DOptionsParametricRange::SetDirty() 
{
	m_fDirty = true;
	SetModified(true);
}

BOOL C2DOptionsParametricRange::OnApply() 
{
	if(!m_fDirty)
		return true;

	CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	pDlg->SendMessage(WM_USER_CHANGE_OBJECT_PROPERTIES, 0, 0);
	m_fDirty = false;
	return CPropertyPage::OnApply();
}

BOOL C2DOptionsParametricRange::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


long double C2DOptionsParametricRange::GetFieldValue(UINT nID)
{
	int i=0;
	while(ParametricRangeCtrls[i].nID)
		{
		if(ParametricRangeCtrls[i].nID == nID)
			return *ParametricRangeCtrls[i].dVal;
		++i;
		}

	return 0.0;
}

bool C2DOptionsParametricRange::ValidateRanges()
{
	// validate x range
	if(GetFieldValue(IDC_XMAX) <= GetFieldValue(IDC_XMIN))
		{
		MessageBox("x max must be greater than x min.");
		return false;
		}

	if(GetFieldValue(IDC_XINT) <= 0)
		{
		MessageBox("x scl must be greater than 0.");
		return false;
		}

	// validate y range
	if(GetFieldValue(IDC_YMAX) <= GetFieldValue(IDC_YMIN))
		{
		MessageBox("y max must be greater than y min.");
		return false;
		}

	if(GetFieldValue(IDC_YINT) <= 0)
		{
		MessageBox("y scl must be greater than 0.");
		return false;
		}
	
	// validate t range
	if(GetFieldValue(IDC_TMAX) <= GetFieldValue(IDC_TMIN))
		{
		MessageBox("t max must be greater than t min.");
		return false;
		}

	if(GetFieldValue(IDC_TSTEP) <= 0)
		{
		MessageBox("t step must be greater than 0.");
		return false;
		}
	
	return true;
}

bool C2DOptionsParametricRange::ValidateFieldValues()
{
	int i=0;
	while(ParametricRangeCtrls[i].nID)
		{
		if(!ValidateField(ParametricRangeCtrls[i].nID))
			return false;
		++i;
		}
	return true;
}

bool C2DOptionsParametricRange::ValidateField(UINT nID)
{
	CString strFieldValue;
	long double dValue;
	
	GetDlgItem(nID)->GetWindowText(strFieldValue);

	// field must not be empty
	if(strFieldValue.IsEmpty())
		{
		MessageBox("Field value must not be empty");
		GetDlgItem(nID)->SetFocus();
		return false;
		}

	// check to see if value actualy changed
	int i=0;
	while(ParametricRangeCtrls[i].nID)
		{
		if(ParametricRangeCtrls[i].nID == nID)
			if(*ParametricRangeCtrls[i].strVal == strFieldValue)
				return true;
		++i;
		}

	// now compute the value
	if(g_Calculator->Compute(strFieldValue, dValue, this->m_hWnd) != SUCCESSFULL)
		{
		// error should be displayed by Compute call
		GetDlgItem(nID)->SetFocus();
		return false;
		}

	// convert and set new value in window
	g_Calculator->DecimalToStringSci(strFieldValue, dValue);
	GetDlgItem(nID)->SetWindowText(strFieldValue);

	// save field value
	i=0;
	while(ParametricRangeCtrls[i].nID)
		{
		if(ParametricRangeCtrls[i].nID == nID)
			{
			*ParametricRangeCtrls[i].strVal = strFieldValue;
			*ParametricRangeCtrls[i].dVal = dValue;
			}
		++i;
		}
	
	return true;
}

void C2DOptionsParametricRange::OnKillfocusTmax() { ValidateField(IDC_TMAX); }
void C2DOptionsParametricRange::OnKillfocusTmin()  { ValidateField(IDC_TMIN); }
void C2DOptionsParametricRange::OnKillfocusTstep()  { ValidateField(IDC_TSTEP); }
void C2DOptionsParametricRange::OnKillfocusXint()  { ValidateField(IDC_XINT); }
void C2DOptionsParametricRange::OnKillfocusXmax()  { ValidateField(IDC_XMAX); }
void C2DOptionsParametricRange::OnKillfocusXmin()  { ValidateField(IDC_XMIN); }
void C2DOptionsParametricRange::OnKillfocusYint()  { ValidateField(IDC_YINT); }
void C2DOptionsParametricRange::OnKillfocusYmax()  { ValidateField(IDC_YMAX); }
void C2DOptionsParametricRange::OnKillfocusYmin()  { ValidateField(IDC_YMIN); }
