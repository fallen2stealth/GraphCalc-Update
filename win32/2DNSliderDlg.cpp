// 2DNSliderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "2DNSliderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C2DNSliderDlg dialog


C2DNSliderDlg::C2DNSliderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(C2DNSliderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(C2DNSliderDlg)
	m_dMin = 1.0;
	m_dMax = 10.0;
	m_dStep = 1.0;
	m_cMilliseconds = 100;
	//}}AFX_DATA_INIT

	Assert(pParent);
	m_pParent = pParent;
	m_positionRect.left = m_positionRect.top = m_positionRect.right = m_positionRect.bottom = -1;
	m_fTimer = false;
	m_fForwardAnimate = true;
	
	CWnd *pMainWnd = NULL;
	pMainWnd = FromHandle(ghDlg);
	if(pMainWnd)
		pMainWnd->GetWindowRect(m_positionRect);
}


void C2DNSliderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C2DNSliderDlg)
	DDX_Text(pDX, IDC_N_MIN, m_dMin);
	DDX_Text(pDX, IDC_N_MAX, m_dMax);
	DDX_Text(pDX, IDC_N_STEP, m_dStep);
	DDX_Text(pDX, IDC_MILLISECONDS, m_cMilliseconds);
	DDV_MinMaxUInt(pDX, m_cMilliseconds, 1, 100000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C2DNSliderDlg, CDialog)
	//{{AFX_MSG_MAP(C2DNSliderDlg)
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_EN_CHANGE(IDC_N_MIN, OnChangeNMin)
	ON_EN_CHANGE(IDC_N_MAX, OnChangeNMax)
	ON_EN_CHANGE(IDC_N_STEP, OnChangeNStep)
	ON_WM_CLOSE()
	ON_EN_KILLFOCUS(IDC_N_MAX, OnKillfocusNMax)
	ON_EN_KILLFOCUS(IDC_N_MIN, OnKillfocusNMin)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ANIMATE, OnAnimate)
	ON_WM_WINDOWPOSCHANGING()
	ON_EN_CHANGE(IDC_MILLISECONDS, OnChangeMilliseconds)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C2DNSliderDlg message handlers

/*void C2DNSliderDlg::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
 if (lpwndpos->cx == 0)
 if (lpwndpos->cy == 0) // is init time
 {
  lpwndpos->x = m_positionRect.left;
  lpwndpos->y = m_positionRect.top; 
 }
 CDialog::OnWindowPosChanging(lpwndpos);
} */

void C2DNSliderDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(pScrollBar->GetDlgCtrlID() == IDC_N_SPIN){
		CSliderCtrl* pSlide = (CSliderCtrl*) pScrollBar;
		SetSliderValue(m_dMin + (m_dStep * double(pSlide->GetPos())));

		CString str;
		str.Format("n = %f", m_dMin + (m_dStep * double(pSlide->GetPos())));
		long double ans;
		g_Calculator->Compute(str, ans, this->m_hWnd);

		CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
		pDlg->SendMessage(WM_2DGRAPH_N_SLIDER_UPDATE, 0, 0);
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void C2DNSliderDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonDown(nFlags, point);

	// fake windows into thinking your clicking on the caption, does not
	// maximize on double click
	PostMessage( WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM( point.x, point.y));
}

BOOL C2DNSliderDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	long double n;
	g_Calculator->Compute("n", n, this->m_hWnd);

	if(n < m_dMin)
		{
		UpdateData(true);
		m_dMin = n - g_Calculator->abs(n/2.0);
		UpdateData(false);
		}
	else if(n > m_dMax)
		{
		UpdateData(true);
		m_dMax = n + g_Calculator->abs(n/2.0);
		UpdateData(false);
		}
	
	CSliderCtrl *pSlide = (CSliderCtrl*) GetDlgItem(IDC_N_SPIN);
	pSlide->SetPos((n-m_dMin)/m_dStep);
	SetSliderValue(n);
	SetSliderRange();

	if(m_positionRect.left != -1)
		SetWindowPos(NULL, m_positionRect.left, m_positionRect.top, NULL, NULL, SWP_NOSIZE | 
				 SWP_NOZORDER | SWP_SHOWWINDOW);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void C2DNSliderDlg::SetSliderValue(double val)
{
	CString str;
	str.Format("%f", val);
	ConvertCleanupFormatAnswer(str);
	SetDlgItemText(IDC_N, "n = " + str);
}

void C2DNSliderDlg::OnChangeNMin() 
{
}

void C2DNSliderDlg::OnChangeNMax() 
{	
}

void C2DNSliderDlg::OnChangeNStep() 
{
	CString val;
	long double ans;
	GetDlgItemText(IDC_N_STEP, val);

	if(val == "")
		return;
	
	if(!g_Calculator->IsValid(val))
		{
		MessageBox("Please enter a valid step greater than 0", "Invalid Step", MB_ICONEXCLAMATION);
		GetDlgItem(IDC_N_STEP)->SetFocus();
		return;
		}
	g_Calculator->Compute(val, ans, this->m_hWnd);
	if(ans <= 0)
		{
		if(ans < 0)
			MessageBox("Please enter a valid step greater than 0", "Invalid Step", MB_ICONEXCLAMATION);

		GetDlgItem(IDC_N_STEP)->SetFocus();
		return;
		}
	
	UpdateSliderCtrl();
}

bool C2DNSliderDlg::ValidateStep()
{
	if(g_Calculator->divisible(m_dStep, m_dMax - m_dMin))
		{
		MessageBox("The range must be divisible by the step!", "Invalid Step", MB_ICONEXCLAMATION);
		GetDlgItem(IDC_N_STEP)->SetFocus();
		return false;
		}
	return true;
}

void C2DNSliderDlg::UpdateSliderCtrl()
{
	CSliderCtrl* pSlide = (CSliderCtrl*) GetDlgItem(IDC_N_SPIN);
	double n = m_dMin + (m_dStep * double(pSlide->GetPos())), newN;

	UpdateData();

	if(m_dMax <= m_dMin)
		{
		MessageBox("n max must be less that n min", "Invalid Range", MB_ICONEXCLAMATION);
		return;
		}

	if(n < m_dMin)
		{
		newN = m_dMin;
		
		CString str;
		str.Format("n = %d", m_dMin);

		long double ans;
		g_Calculator->Compute(str, ans, this->m_hWnd);

		CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
		pDlg->SendMessage(WM_2DGRAPH_N_SLIDER_UPDATE, 0, 0);
		}
	else if(m_dMax < n)
		{
		newN = m_dMax;
		
		CString str;
		str.Format("n = %d", m_dMax);

		long double ans;
		g_Calculator->Compute(str, ans, this->m_hWnd);

		CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
		pDlg->SendMessage(WM_2DGRAPH_N_SLIDER_UPDATE, 0, 0);
		}
	else
		newN = n;

	SetSliderRange();

	// now fix the slider position
	pSlide->SetPos((newN-m_dMin)/m_dStep);
	SetSliderValue(newN);
}

void C2DNSliderDlg::SetSliderRange()
{
	CSliderCtrl* pSlide = (CSliderCtrl*) GetDlgItem(IDC_N_SPIN);
	pSlide->SetRange(0, (m_dMax - m_dMin) * (1.0/m_dStep), true);
}

long double C2DNSliderDlg::GetFieldValue(UINT nID)
{
	CString val;
	GetDlgItemText(nID, val);

	long double ans=0;
	ErrorT error = g_Calculator->Compute(val, ans, this->m_hWnd);

	if(SUCCESSFULL != error)
		{
		Assert(SUCCESSFULL == error);
		MessageBox("Error getting fields value!");
		}
	return ans;
}

void C2DNSliderDlg::PostNcDestroy() 
{
	if(m_pParent->m_hWnd)
		m_pParent->SendMessage(WM_2DGRAPH_N_SLIDER_CLOSING, 0, 0);
	
	CDialog::PostNcDestroy();

	delete this; // for modeless dialog only
}

void C2DNSliderDlg::OnClose() 
{
	if(this->m_hWnd)
		DestroyWindow();
}

void C2DNSliderDlg::OnKillfocusNMax() 
{
	CString val;
	GetDlgItemText(IDC_N_MAX, val);

	if(!g_Calculator->IsValid(val))
		return;
	
	UpdateSliderCtrl();
}

void C2DNSliderDlg::OnKillfocusNMin() 
{
	CString val;
	GetDlgItemText(IDC_N_MIN, val);

	if(!g_Calculator->IsValid(val))
		return;
	
	UpdateSliderCtrl();
}

void C2DNSliderDlg::OnTimer(UINT nIDEvent) 
{
	CSliderCtrl* pSlide = (CSliderCtrl*) GetDlgItem(IDC_N_SPIN);
	double n = m_dMin + (m_dStep * double(pSlide->GetPos()));

	if(m_fForwardAnimate)
		{
		if(n >= m_dMax)
			{
			m_fForwardAnimate = false;
			n -= m_dStep;
			}
		else
			{
			n += m_dStep;		
			if(n > m_dMax)
				{
				n -= (2*m_dStep);
				m_fForwardAnimate = false;
				}
			}
			
		}
	else
		{
		if(n <= m_dMin)
			{
			m_fForwardAnimate = true;
			n += m_dStep;
			}
		else
			{
			n -= m_dStep;		
			if(n < m_dMin)
				{
				n += (2*m_dStep);
				m_fForwardAnimate = true;
				}
			}
		}
	
	CString str;
	str.Format("n = %f", n);
	long double ans;
	g_Calculator->Compute(str, ans, this->m_hWnd);

	CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	pDlg->SendMessage(WM_2DGRAPH_N_SLIDER_UPDATE, 0, 0);

	int newPos;
	if(m_fForwardAnimate)
		newPos = pSlide->GetPos() + 1;
	else
		newPos = pSlide->GetPos() - 1;
	
	pSlide->SetPos(newPos);
	SetSliderValue(n);
	
	CDialog::OnTimer(nIDEvent);
}

void C2DNSliderDlg::OnAnimate() 
{
	if(m_fTimer)
		{
		m_fTimer = false;
		KillTimer(0);
		SetDlgItemText(IDC_ANIMATE, "Animate");
		}
	else
		{
		m_fTimer = true;
		if(UpdateData())
			{
			m_fForwardAnimate = true;
			SetDlgItemText(IDC_ANIMATE, "Stop");
			SetTimer(0, m_cMilliseconds, NULL);
			}
		}	
}

void C2DNSliderDlg::OnChangeMilliseconds() 
{
	CString val;
	long double dVal;
	GetDlgItemText(IDC_MILLISECONDS, val);

	if(!g_Calculator->IsValid(val))
		return;

	g_Calculator->Compute(val, dVal, this->m_hWnd);
	if(dVal < 1)
		return;

	UpdateData();
	SetTimer(0, m_cMilliseconds, NULL);
}
