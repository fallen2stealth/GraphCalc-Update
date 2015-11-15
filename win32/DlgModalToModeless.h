
#ifndef _DLGMODALTOMODELESS_H_
#define _DLGMODALTOMODELESS_H_

/////////////////////////////////////////////////////////////////////////////
// CDlgModalToModeless thread
//#include "Mode.h"

class CDlgModalToModeless : public CWinThread
{
	DECLARE_DYNCREATE(CDlgModalToModeless)

public:
	CDlgModalToModeless();
	void DoDialog(CDialog *pDlg);

protected:
	// Internal functions
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// Internal Data
	CDialog *m_pDlg;

	// Generated message map functions
	//{{AFX_MSG(CDlgModalToModeless)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // _PSEDLGMODALTOMODELESS_H_