#if !defined(AFX_SHADEBUTTON_H__D0B75901_9830_11D1_9C0F_00A0243D1382__INCLUDED_)
#define AFX_SHADEBUTTON_H__D0B75901_9830_11D1_9C0F_00A0243D1382__INCLUDED_

#include "3DGraphOptions.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// CShadeButton.h : header file


/////////////////////////////////////////////////////////////////////////////
// CShadeButton window

//void AFXAPI DDX_ColourPicker(CDataExchange *pDX, int nIDC, COLORREF& crColour);

/////////////////////////////////////////////////////////////////////////////
// CShadeButton window

//#define CP_MODE_TEXT 1  // edit text colour
//#define CP_MODE_BK   2  // edit background colour (default)

class CShadeButton : public CButton
{
// Construction
public:
    CShadeButton();
    DECLARE_DYNCREATE(CShadeButton);

// Attributes
public:
    //COLORREF GetColour();
    //void     SetColour(COLORREF crColour); 

    //void     SetDefaultText(LPCTSTR szDefaultText);
    //void     SetCustomText(LPCTSTR szCustomText);

    //void     SetTrackSelection(BOOL bTracking = TRUE)  { m_bTrackSelection = bTracking; }
    //BOOL     GetTrackSelection()                       { return m_bTrackSelection; }

    //void     SetSelectionMode(UINT nMode)              { m_nSelectionMode = nMode; }
    //UINT     GetSelectionMode()                        { return m_nSelectionMode; };

    //void     SetBkColour(COLORREF crColourBk);
    //COLORREF GetBkColour()                             { return m_crColourBk; }
    
    //void     SetTextColour(COLORREF crColourText);
    //COLORREF GetTextColour()                           { return m_crColourText;}

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CShadeButton)
    public:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CShadeButton();
	BOOL OnClicked();

protected:
    void SetWindowSize();

// protected attributes
protected:
    BOOL     m_bActive;                  // Is the dropdown active?
    //BOOL     m_bTrackSelection;        // track colour changes?
    //COLORREF m_crColourBk;
    //COLORREF m_crColourText;
    //UINT     m_nSelectionMode;
    //CRect    m_ArrowRect;
    //CString  m_strDefaultText;
    //CString  m_strCustomText;

    // Generated message map functions
protected:
    //{{AFX_MSG(CShadeButton)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
private:
	C3DGraphOptions m_3DGraphOptionsDlg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOURPICKER_H__D0B75901_9830_11D1_9C0F_00A0243D1382__INCLUDED_)
