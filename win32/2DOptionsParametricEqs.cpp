// 2DOptionsParametricEqs.cpp : implementation file
//

#include "stdafx.h"
#include "grphcalc.h"
#include "2DOptionsParametricEqs.h"
#include "globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C2DOptionsParametricEqs property page

IMPLEMENT_DYNCREATE(C2DOptionsParametricEqs, CPropertyPage)

C2DOptionsParametricEqs::C2DOptionsParametricEqs() : CPropertyPage(C2DOptionsParametricEqs::IDD)
{
	//{{AFX_DATA_INIT(C2DOptionsParametricEqs)
	m_strX[0] = _T("");
	m_strX[1] = _T("");
	m_strX[2] = _T("");
	m_strX[3] = _T("");
	m_strX[4] = _T("");
	m_strY[0] = _T("");
	m_strY[1] = _T("");
	m_strY[2] = _T("");
	m_strY[3] = _T("");
	m_strY[4] = _T("");
	m_fOn[0]= FALSE;
	m_fOn[1] = FALSE;
	m_fOn[2] = FALSE;
	m_fOn[3] = FALSE;
	m_fOn[4] = FALSE;
	//}}AFX_DATA_INIT

	m_fDirty = false;

	m_ColorButton[0].SetSelectionMode(CP_MODE_BK);
	m_ColorButton[1].SetSelectionMode(CP_MODE_BK);
	m_ColorButton[2].SetSelectionMode(CP_MODE_BK);
	m_ColorButton[3].SetSelectionMode(CP_MODE_BK);
	m_ColorButton[4].SetSelectionMode(CP_MODE_BK);

	m_ColorButton[0].SetBkColour(RGB(128,0,0));
	m_ColorButton[1].SetBkColour(RGB(0,128,0));
	m_ColorButton[2].SetBkColour(RGB(0,0,128));
	m_ColorButton[3].SetBkColour(RGB(128,128,0));
	m_ColorButton[4].SetBkColour(RGB(0,128,128));
}

C2DOptionsParametricEqs::~C2DOptionsParametricEqs()
{
}

void C2DOptionsParametricEqs::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C2DOptionsParametricEqs)
	DDX_Control(pDX, IDC_COLOR_EQ1, m_ColorButton[0]);
	DDX_Control(pDX, IDC_COLOR_EQ2, m_ColorButton[1]);
	DDX_Control(pDX, IDC_COLOR_EQ3, m_ColorButton[2]);
	DDX_Control(pDX, IDC_COLOR_EQ4, m_ColorButton[3]);
	DDX_Control(pDX, IDC_COLOR_EQ5, m_ColorButton[4]);
	DDX_Check(pDX, IDC_ON_EQ1, m_fOn[0]);
	DDX_Check(pDX, IDC_ON_EQ2, m_fOn[1]);
	DDX_Check(pDX, IDC_ON_EQ3, m_fOn[2]);
	DDX_Check(pDX, IDC_ON_EQ4, m_fOn[3]);
	DDX_Check(pDX, IDC_ON_EQ5, m_fOn[4]);
	//}}AFX_DATA_MAP

	// put equations in dialog
	if(!pDX->m_bSaveAndValidate)
		{
		DDX_Text(pDX, IDC_EQX1, m_strX[0]);
		DDX_Text(pDX, IDC_EQX2, m_strX[1]);
		DDX_Text(pDX, IDC_EQX3, m_strX[2]);
		DDX_Text(pDX, IDC_EQX4, m_strX[3]);
		DDX_Text(pDX, IDC_EQX5, m_strX[4]);
		DDX_Text(pDX, IDC_EQY1, m_strY[0]);
		DDX_Text(pDX, IDC_EQY2, m_strY[1]);
		DDX_Text(pDX, IDC_EQY3, m_strY[2]);
		DDX_Text(pDX, IDC_EQY4, m_strY[3]);
		DDX_Text(pDX, IDC_EQY5, m_strY[4]);
		}
	else if(!ValidateEquations())
		pDX->Fail();
}


BEGIN_MESSAGE_MAP(C2DOptionsParametricEqs, CPropertyPage)
	//{{AFX_MSG_MAP(C2DOptionsParametricEqs)
	ON_WM_KILLFOCUS()
	ON_EN_CHANGE(IDC_EQX1, OnValueChanged)
	ON_EN_CHANGE(IDC_EQX2, OnValueChanged)
	ON_EN_CHANGE(IDC_EQX3, OnValueChanged)
	ON_EN_CHANGE(IDC_EQX4, OnValueChanged)
	ON_EN_CHANGE(IDC_EQX5, OnValueChanged)
	ON_EN_CHANGE(IDC_EQY1, OnValueChanged)
	ON_EN_CHANGE(IDC_EQY2, OnValueChanged)
	ON_EN_CHANGE(IDC_EQY3, OnValueChanged)
	ON_EN_CHANGE(IDC_EQY4, OnValueChanged)
	ON_EN_CHANGE(IDC_EQY5, OnValueChanged)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_ON_EQ1, IDC_ON_EQ5, OnEqOnOff)
	ON_COMMAND_RANGE(IDC_COLOR_EQ1, IDC_COLOR_EQ5, OnColorButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C2DOptionsParametricEqs message handlers

struct ParametricEquationCtrls
{
	UINT idOn;
	UINT idX;
	UINT idY;
	UINT idColor;
};

ParametricEquationCtrls g_ParaCtrls[] = {
		{IDC_ON_EQ1, IDC_EQX1, IDC_EQY1, IDC_COLOR_EQ1},
		{IDC_ON_EQ2, IDC_EQX2, IDC_EQY2, IDC_COLOR_EQ2},
		{IDC_ON_EQ3, IDC_EQX3, IDC_EQY3, IDC_COLOR_EQ3},
		{IDC_ON_EQ4, IDC_EQX4, IDC_EQY4, IDC_COLOR_EQ4},
		{IDC_ON_EQ5, IDC_EQX5, IDC_EQY5, IDC_COLOR_EQ5},
		{0, 0, 0, 0}
};

void C2DOptionsParametricEqs::SetDirty() 
{
	m_fDirty = true;
	SetModified(true);
}

BOOL C2DOptionsParametricEqs::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: eqs empty?  if so, turn them off
	
	
	// eqs turned on or off?
	int i=0;
	while(g_ParaCtrls[i].idOn)
		{
		OnEqOnOff(g_ParaCtrls[i].idOn);			
		++i;
		}
	SetDirty();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void C2DOptionsParametricEqs::OnKillFocus(CWnd* pNewWnd) 
{
	CPropertyPage::OnKillFocus(pNewWnd);
}

BOOL C2DOptionsParametricEqs::OnApply() 
{
	if(!m_fDirty)
		return true;
	
	
	CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	pDlg->SendMessage(WM_USER_CHANGE_OBJECT_PROPERTIES, 0, 0);
	m_fDirty = false;
	
	return CPropertyPage::OnApply();
}

bool C2DOptionsParametricEqs::ValidateEquations()
{
	int i=0;
	while(g_ParaCtrls[i].idOn)
		{
		if(!ValidateParametricEquation(i))
			return false;
		++i;
		}
	return true;
}

bool C2DOptionsParametricEqs::ValidateParametricEquation(UINT nIndex)
{
	CString strX, strY;
	
	GetDlgItem(g_ParaCtrls[nIndex].idX)->GetWindowText(strX);
	GetDlgItem(g_ParaCtrls[nIndex].idY)->GetWindowText(strY);

	// if both equations are empty just turn it off and say we were
	// succesful at validating the equations
	if(strX.IsEmpty() && strY.IsEmpty())
		{
		CheckDlgButton(g_ParaCtrls[nIndex].idOn, 0);
		OnEqOnOff(g_ParaCtrls[nIndex].idOn);
		m_fOn[nIndex] = false;
		
		m_strX[nIndex] = strX;
		m_strY[nIndex] = strY;
		return true;
		}

	// make sure both equations are set
	if(strX.IsEmpty() || strY.IsEmpty())
		{
		MessageBox("You must specify x(t) and y(t) for each equation set");
		return false;
		}

	// now check to see if the equations have actualy changed
	if((strX == m_strX[nIndex]) && (strY == m_strY[nIndex])) 
		return true;

	if(strX != m_strX[nIndex]) 
		{
		if(!g_Calculator->IsValid(strX, this->m_hWnd))
			return false;
		}
	m_strX[nIndex] = strX;

	if(strY != m_strY[nIndex]) 
		{
		if(!g_Calculator->IsValid(strY, this->m_hWnd))
			return false;
		}
	m_strY[nIndex] = strY;
	
	return true;
}

void C2DOptionsParametricEqs::OnColorButton(UINT nID)
{
	int nButton = nID - IDC_COLOR_EQ1;
	ASSERT( nButton >= 0 && nButton < 5 );
	m_ColorButton[nButton].OnClicked();
	SetDirty();			
}

void C2DOptionsParametricEqs::OnEqOnOff(UINT nID)
{
	int nButton = nID - IDC_ON_EQ1;
	ASSERT( nButton >= 0 && nButton < 5 );

	int i=0;
	while(g_ParaCtrls[i].idOn)
		{
		if(g_ParaCtrls[i].idOn == nID)
			{
			if(BST_CHECKED == IsDlgButtonChecked(nID)){
				GetDlgItem(g_ParaCtrls[i].idX)->EnableWindow();
				GetDlgItem(g_ParaCtrls[i].idY)->EnableWindow();
				GetDlgItem(g_ParaCtrls[i].idColor)->EnableWindow();
				m_ColorButton[i].Invalidate();
			}
			else{
				GetDlgItem(g_ParaCtrls[i].idX)->EnableWindow(false);
				GetDlgItem(g_ParaCtrls[i].idY)->EnableWindow(false);
				GetDlgItem(g_ParaCtrls[i].idColor)->EnableWindow(false);
				m_ColorButton[i].Invalidate();
			}
			break;
			}
		++i;
		}

	SetDirty();
}

void C2DOptionsParametricEqs::OnValueChanged() 
{	
	SetDirty();	
}
