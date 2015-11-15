// 3DGOEquations.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "3DGOEquations.h"
#include "CCalculator.h"
#include "3DGraphOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool *Changed3DEquation;
extern CCalculator *g_Calculator;
extern bool IsEquation(CString equation, char variable);

void AFXAPI DDV_3DEquation( CDataExchange* pDX, int nIDC, CString& value, int mode, int enabled)
{
	// from dialog to class ?
	if( pDX->m_bSaveAndValidate)
	{
		int eq(-1);

		switch(nIDC){
		case IDC_3D_EQ:  eq = 0; break;
		case IDC_3D_EQ2: eq = 1; break;
		case IDC_3D_EQ3: eq = 2; break;
		case IDC_3D_EQ4: eq = 3; break;
		case IDC_3D_EQ5: eq = 4; break;
		case IDC_3D_EQ6: eq = 5; break;
		default: return;
		}

		if(!Changed3DEquation[eq])
			return;

		CString Val;				
		pDX->m_pDlgWnd->GetDlgItem(nIDC)->GetWindowText(Val);	

		if(Val.IsEmpty()){
			value = Val;
			Changed3DEquation[eq] = false;
			return;
		}
				
		if(g_Calculator->IsValid(Val, pDX->m_pDlgWnd->m_hWnd)){
			value = Val;
			if(enabled)
			{
				switch(mode)
				{
				case POLAR:
					{
						if(IsEquation(Val, 'x') || IsEquation(Val, 'y'))
							{
							pDX->m_pDlgWnd->MessageBox("The variables 'x' and 'y' can not be used in polar mode.");
							goto Error;
							}
						break;
					}
				case EUCLIDEAN:
					{
						if(IsEquation(Val, 't') || IsEquation(Val, 'r'))
							{
							pDX->m_pDlgWnd->MessageBox("The variables 't' and 'r' can not be used in euclidean mode.");
							goto Error;
							}
						break;
					}
				}
			}
			Changed3DEquation[eq] = false;
			return;
		}
		else
			{
			pDX->m_pDlgWnd->MessageBox("Invalid Equation!");
			goto Error;
			}
		
		Error:
			pDX->PrepareEditCtrl(nIDC);
			pDX->Fail();
	}	
}

/////////////////////////////////////////////////////////////////////////////
// C3DGOEquations property page

IMPLEMENT_DYNCREATE(C3DGOEquations, CPropertyPage)

C3DGOEquations::C3DGOEquations() : CPropertyPage(C3DGOEquations::IDD)
{
	//{{AFX_DATA_INIT(C3DGOEquations)
	m_Eq = _T("");
	m_Eq2 = _T("");
	m_Eq3 = _T("");
	m_Eq4 = _T("");
	m_Eq5 = _T("");
	m_Eq6 = _T("");
	m_Eq_On = FALSE;
	m_Eq2_On = FALSE;
	m_Eq3_On = FALSE;
	m_Eq4_On = FALSE;
	m_Eq5_On = FALSE;
	m_Eq6_On = FALSE;
	m_Mode = 0;
	//}}AFX_DATA_INIT

	Changed3DEquation = new bool[6];

	for(int i(0); i <= 5; ++i)
		Changed3DEquation[i] = false;
}

C3DGOEquations::~C3DGOEquations()
{
}

void C3DGOEquations::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C3DGOEquations)
	DDX_Radio(pDX, IDC_MODE, m_Mode);
	DDX_Check(pDX, IDC_3D_EQ_ON, m_Eq_On);
	DDX_Check(pDX, IDC_3D_EQ_ON2, m_Eq2_On);
	DDX_Check(pDX, IDC_3D_EQ_ON3, m_Eq3_On);
	DDX_Check(pDX, IDC_3D_EQ_ON4, m_Eq4_On);
	DDX_Check(pDX, IDC_3D_EQ_ON5, m_Eq5_On);
	DDX_Check(pDX, IDC_3D_EQ_ON6, m_Eq6_On);
	DDX_Text(pDX, IDC_3D_EQ, m_Eq);
	DDV_3DEquation(pDX, IDC_3D_EQ, m_Eq, m_Mode, m_Eq_On);
	DDX_Text(pDX, IDC_3D_EQ2, m_Eq2);
	DDV_3DEquation(pDX, IDC_3D_EQ2, m_Eq2, m_Mode, m_Eq2_On);
	DDX_Text(pDX, IDC_3D_EQ3, m_Eq3);
	DDV_3DEquation(pDX, IDC_3D_EQ3, m_Eq3, m_Mode, m_Eq3_On);
	DDX_Text(pDX, IDC_3D_EQ4, m_Eq4);
	DDV_3DEquation(pDX, IDC_3D_EQ4, m_Eq4, m_Mode, m_Eq4_On);
	DDX_Text(pDX, IDC_3D_EQ5, m_Eq5);
	DDV_3DEquation(pDX, IDC_3D_EQ5, m_Eq5, m_Mode, m_Eq5_On);
	DDX_Text(pDX, IDC_3D_EQ6, m_Eq6);
	DDV_3DEquation(pDX, IDC_3D_EQ6, m_Eq6, m_Mode, m_Eq6_On);
	DDX_Control(pDX, IDC_EQ_SHADING, m_EqRenderButton);
	DDX_Control(pDX, IDC_EQ_SHADING2, m_Eq2RenderButton);
	DDX_Control(pDX, IDC_EQ_SHADING3, m_Eq3RenderButton);
	DDX_Control(pDX, IDC_EQ_SHADING4, m_Eq4RenderButton);
	DDX_Control(pDX, IDC_EQ_SHADING5, m_Eq5RenderButton);
	DDX_Control(pDX, IDC_EQ_SHADING6, m_Eq6RenderButton);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C3DGOEquations, CPropertyPage)
	//{{AFX_MSG_MAP(C3DGOEquations)
	ON_BN_CLICKED(IDC_EQ_SHADING, OnEqShading)
	ON_BN_CLICKED(IDC_EQ_SHADING2, OnEqShading2)
	ON_BN_CLICKED(IDC_EQ_SHADING3, OnEqShading3)
	ON_BN_CLICKED(IDC_EQ_SHADING4, OnEqShading4)
	ON_BN_CLICKED(IDC_EQ_SHADING5, OnEqShading5)
	ON_BN_CLICKED(IDC_EQ_SHADING6, OnEqShading6)
	ON_BN_CLICKED(IDC_3D_EQ_ON, On3dEqOn)
	ON_BN_CLICKED(IDC_3D_EQ_ON2, On3dEqOn2)
	ON_BN_CLICKED(IDC_3D_EQ_ON3, On3dEqOn3)
	ON_BN_CLICKED(IDC_3D_EQ_ON4, On3dEqOn4)
	ON_BN_CLICKED(IDC_3D_EQ_ON5, On3dEqOn5)
	ON_BN_CLICKED(IDC_3D_EQ_ON6, On3dEqOn6)
	ON_EN_CHANGE(IDC_3D_EQ, OnChange3dEq)
	ON_EN_CHANGE(IDC_3D_EQ2, OnChange3dEq2)
	ON_EN_CHANGE(IDC_3D_EQ3, OnChange3dEq3)
	ON_EN_CHANGE(IDC_3D_EQ4, OnChange3dEq4)
	ON_EN_CHANGE(IDC_3D_EQ5, OnChange3dEq5)
	ON_EN_CHANGE(IDC_3D_EQ6, OnChange3dEq6)
	ON_EN_KILLFOCUS(IDC_3D_EQ, OnKillfocus3dEq)
	ON_EN_KILLFOCUS(IDC_3D_EQ2, OnKillfocus3dEq2)
	ON_EN_KILLFOCUS(IDC_3D_EQ3, OnKillfocus3dEq3)
	ON_EN_KILLFOCUS(IDC_3D_EQ4, OnKillfocus3dEq4)
	ON_EN_KILLFOCUS(IDC_3D_EQ5, OnKillfocus3dEq5)
	ON_EN_KILLFOCUS(IDC_3D_EQ6, OnKillfocus3dEq6)
	ON_BN_CLICKED(IDC_MODE, OnClickedMode)
	ON_BN_CLICKED(IDC_MODE2, OnClickedMode)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_3D_EQ, IDC_3D_EQ6, UpdateEqStatus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DGOEquations message handlers

BOOL C3DGOEquations::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	UpdateEqStatus(IDC_3D_EQ);
	UpdateEqStatus(IDC_3D_EQ2);
	UpdateEqStatus(IDC_3D_EQ3);
	UpdateEqStatus(IDC_3D_EQ4);
	UpdateEqStatus(IDC_3D_EQ5);
	UpdateEqStatus(IDC_3D_EQ6);


	UpdateEqType();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void C3DGOEquations::UpdateEqStatus(UINT nID)
{
	//UpdateData();
	
	switch(nID){
	case IDC_3D_EQ: AlterEqStatus(IDC_3D_EQ_ON, IDC_3D_EQ, IDC_EQ_SHADING); break;
	case IDC_3D_EQ2: AlterEqStatus(IDC_3D_EQ_ON2, IDC_3D_EQ2, IDC_EQ_SHADING2); break;
	case IDC_3D_EQ3: AlterEqStatus(IDC_3D_EQ_ON3, IDC_3D_EQ3, IDC_EQ_SHADING3); break;
	case IDC_3D_EQ4: AlterEqStatus(IDC_3D_EQ_ON4, IDC_3D_EQ4, IDC_EQ_SHADING4); break;
	case IDC_3D_EQ5: AlterEqStatus(IDC_3D_EQ_ON5, IDC_3D_EQ5, IDC_EQ_SHADING5); break;
	case IDC_3D_EQ6: AlterEqStatus(IDC_3D_EQ_ON6, IDC_3D_EQ6, IDC_EQ_SHADING6); break;
	}
}

int C3DGOEquations::EqIDtoNum(UINT id)
{
	switch(id){
	case IDC_3D_EQ: return 1;
	case IDC_3D_EQ2: return 2;
	case IDC_3D_EQ3: return 3;
	case IDC_3D_EQ4: return 4;
	case IDC_3D_EQ5: return 5;
	case IDC_3D_EQ6: return 6;
	}
	return -1;
}

void C3DGOEquations::AlterEqStatus(UINT on, UINT eq, UINT eq_shade)
{
	CWnd *pshade;
	CEdit *peq;
	
	peq = (CEdit*)GetDlgItem(eq);
	pshade = GetDlgItem(eq_shade);

	if(BST_CHECKED == IsDlgButtonChecked(on)){
		peq->EnableWindow();		
		pshade->EnableWindow();
		Changed3DEquation[EqIDtoNum(on) - 1] = true;
	}
	else{
		peq->EnableWindow(false);
		pshade->EnableWindow(false);
	}

}

void C3DGOEquations::ClearEmptyEq(UINT eq, UINT eq_on)
{
	CString Val;
	GetDlgItem(eq)->GetWindowText(Val);

	if(Val.IsEmpty()) 
		CheckDlgButton(eq_on, 0); 
}

void C3DGOEquations::On3dEqOn() {
	UpdateData();
	UpdateEqStatus(IDC_3D_EQ); 
	SetModified(true);
}
void C3DGOEquations::On3dEqOn2() { 
	UpdateData();
	UpdateEqStatus(IDC_3D_EQ2); 
	SetModified(true);
}
void C3DGOEquations::On3dEqOn3() { 
	UpdateData();
	UpdateEqStatus(IDC_3D_EQ3); 
	SetModified(true);
}
void C3DGOEquations::On3dEqOn4() { 
	UpdateData();
	UpdateEqStatus(IDC_3D_EQ4); 
	SetModified(true);
}
void C3DGOEquations::On3dEqOn5() { 
	UpdateData();
	UpdateEqStatus(IDC_3D_EQ5); 
	SetModified(true);
}
void C3DGOEquations::On3dEqOn6() { 
	UpdateData();
	UpdateEqStatus(IDC_3D_EQ6); 
	SetModified(true);
}

void C3DGOEquations::OnKillfocus3dEq()  { ClearEmptyEq(IDC_3D_EQ, IDC_3D_EQ_ON);	UpdateEqStatus(IDC_3D_EQ);	}
void C3DGOEquations::OnKillfocus3dEq2() { ClearEmptyEq(IDC_3D_EQ2, IDC_3D_EQ_ON2);	UpdateEqStatus(IDC_3D_EQ2); }
void C3DGOEquations::OnKillfocus3dEq3() { ClearEmptyEq(IDC_3D_EQ3, IDC_3D_EQ_ON3);	UpdateEqStatus(IDC_3D_EQ3); }
void C3DGOEquations::OnKillfocus3dEq4() { ClearEmptyEq(IDC_3D_EQ4, IDC_3D_EQ_ON4);	UpdateEqStatus(IDC_3D_EQ4); }
void C3DGOEquations::OnKillfocus3dEq5() { ClearEmptyEq(IDC_3D_EQ5, IDC_3D_EQ_ON5);	UpdateEqStatus(IDC_3D_EQ5); }
void C3DGOEquations::OnKillfocus3dEq6() { ClearEmptyEq(IDC_3D_EQ6, IDC_3D_EQ_ON6);	UpdateEqStatus(IDC_3D_EQ6); }

void C3DGOEquations::OnEqShading() {  
	m_EqRenderButton.m_3DRenderDlg.m_Mode = m_Mode; 
	if(m_EqRenderButton.OnClicked()) SetModified(true); 
}
void C3DGOEquations::OnEqShading2() { 
	m_Eq2RenderButton.m_3DRenderDlg.m_Mode = m_Mode; 
	if(m_Eq2RenderButton.OnClicked()) SetModified(true); 
}
void C3DGOEquations::OnEqShading3() { 
	m_Eq3RenderButton.m_3DRenderDlg.m_Mode = m_Mode; 
	if(m_Eq3RenderButton.OnClicked()) SetModified(true); 
}
void C3DGOEquations::OnEqShading4() { 
	m_Eq4RenderButton.m_3DRenderDlg.m_Mode = m_Mode; 
	if(m_Eq4RenderButton.OnClicked()) SetModified(true); 
}
void C3DGOEquations::OnEqShading5() { 
	m_Eq5RenderButton.m_3DRenderDlg.m_Mode = m_Mode; 
	if(m_Eq5RenderButton.OnClicked()) SetModified(true); 
}
void C3DGOEquations::OnEqShading6() { 
	m_Eq6RenderButton.m_3DRenderDlg.m_Mode = m_Mode; 
	if(m_Eq6RenderButton.OnClicked()) SetModified(true); 
}

void C3DGOEquations::OnChange3dEq()  { Changed3DEquation[0] = true; SetModified(true);}
void C3DGOEquations::OnChange3dEq2() { Changed3DEquation[1] = true;  SetModified(true);}
void C3DGOEquations::OnChange3dEq3() { Changed3DEquation[2] = true;  SetModified(true);}
void C3DGOEquations::OnChange3dEq4() { Changed3DEquation[3] = true;  SetModified(true);}
void C3DGOEquations::OnChange3dEq5() { Changed3DEquation[4] = true;  SetModified(true);}
void C3DGOEquations::OnChange3dEq6() { Changed3DEquation[5] = true;  SetModified(true);}

BOOL C3DGOEquations::OnKillActive() 
{
	OnKillfocus3dEq();		
	OnKillfocus3dEq2();
	OnKillfocus3dEq3();
	OnKillfocus3dEq4();
	OnKillfocus3dEq5();
	OnKillfocus3dEq6();
	return CPropertyPage::OnKillActive();
}

BOOL C3DGOEquations::OnApply() 
{
	UpdateData();

	for(int i(0); i <= 5; ++i){
		if(Changed3DEquation[i])
			return false;
	}

	CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	pDlg->SendMessage(WM_3DOPTIONS_CHANGE, 0, 0);

	m_EqRenderButton.ClearModified();
	m_Eq2RenderButton.ClearModified();
	m_Eq3RenderButton.ClearModified();
	m_Eq4RenderButton.ClearModified();
	m_Eq5RenderButton.ClearModified();
	m_Eq6RenderButton.ClearModified();
	
	return CPropertyPage::OnApply();
}

void C3DGOEquations::OnClickedMode() { 
	SetModified(true);
	UpdateEqType();
	for(int i(0); i <= 5; ++i){
		if(IsFunctionEnabled(i+1))
			Changed3DEquation[i] = true;
	}
}

bool C3DGOEquations::IsFunctionEnabled(int eq)
{
	switch(eq)
	{
	case 1: return (BST_CHECKED == IsDlgButtonChecked(IDC_3D_EQ_ON));
	case 2: return (BST_CHECKED == IsDlgButtonChecked(IDC_3D_EQ_ON2));
 	case 3: return (BST_CHECKED == IsDlgButtonChecked(IDC_3D_EQ_ON3));
	case 4: return (BST_CHECKED == IsDlgButtonChecked(IDC_3D_EQ_ON4));
	case 5: return (BST_CHECKED == IsDlgButtonChecked(IDC_3D_EQ_ON5));
	case 6: return (BST_CHECKED == IsDlgButtonChecked(IDC_3D_EQ_ON6));
	}
	return false;	
}

void C3DGOEquations::UpdateEqType()
{
	UpdateData();
	switch(m_Mode){
	case 0:
		{
			GetDlgItem(IDC_3D_EQ_ON)->SetWindowText("z1(x,y) = ");
			GetDlgItem(IDC_3D_EQ_ON2)->SetWindowText("z2(x,y) = ");
			GetDlgItem(IDC_3D_EQ_ON3)->SetWindowText("z3(x,y) = ");
			GetDlgItem(IDC_3D_EQ_ON4)->SetWindowText("z4(x,y) = ");
			GetDlgItem(IDC_3D_EQ_ON5)->SetWindowText("z5(x,y) = ");
			GetDlgItem(IDC_3D_EQ_ON6)->SetWindowText("z6(x,y) = ");
			break;
		}
	case 1:
		{
			GetDlgItem(IDC_3D_EQ_ON)->SetWindowText("z1(r,t) = ");
			GetDlgItem(IDC_3D_EQ_ON2)->SetWindowText("z2(r,t) = ");
			GetDlgItem(IDC_3D_EQ_ON3)->SetWindowText("z3(r,t) = ");
			GetDlgItem(IDC_3D_EQ_ON4)->SetWindowText("z4(r,t) = ");
			GetDlgItem(IDC_3D_EQ_ON5)->SetWindowText("z5(r,t) = ");
			GetDlgItem(IDC_3D_EQ_ON6)->SetWindowText("z6(r,t) = ");
			break;
		}
	}

	C3DGraphOptions *pWnd = (C3DGraphOptions*)GetParent();
	pWnd->UpdateGraphMode(m_Mode);
}

void C3DGOEquations::OnOK() 
{
	
	CPropertyPage::OnOK();
}
