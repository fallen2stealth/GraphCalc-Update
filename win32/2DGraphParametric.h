#if !defined(CGRAPHPARAMETRIC)
#define CGRAPHPARAMETRIC

#include <afxwin.h>
#include "CCalculator.h"
#include "globals.h"
#include "Structs.h"


#if !defined (TRACEREDRAWMODE)
#define TRACEREDRAWMODE
enum TraceRedrawMode{TRACE_NONE, TRACE_PAN};
#endif

class C2DGraphParametric : public CObject{
public:
	// PUBLIC MEMBER VARIABLES
	ParametricEquationT m_Equations[MAX_2D_PARAMETRIC_EQS];

	long double m_Tmin;
	long double m_Tmax;
	long double m_Tstep;
	
	long double m_Xmin;
	long double m_Xmax;
	long double m_Xscl;
	long double m_Ymin;
	long double m_Ymax;
	long double m_Yscl;
	
	long double m_PrevXmin;
	long double m_PrevXmax;
	long double m_PrevXscl;
	long double m_PrevYmin;
	long double m_PrevYmax;
	long double m_PrevYscl;

	
	long double  m_TraceT; 

	// PUBLIC MEMBER FUNCTIONS
	
	C2DGraphParametric();
	~C2DGraphParametric();
	
	void 			SetLinePrec(int val){ m_LinePrec = val; }
	int 			GetLinePrec(){ return m_LinePrec; }

	void 			SwapPrevCurRanges();
	void 			SetPreviousRange();
	void 			StoreCurrentRange();
	void 			ValidateRanges();

	void DrawGrid(const SLineStyle &style, bool &grid_on, 
				   const CRect window, CDC *pDC,
				  DrawE destination, double font_size, 
				  COLORREF color, int label_interval=1);

	void DrawAxis(const SLineStyle &style, const CRect window, CDC *pDC);

	void DrawCoordsLabels(const double font_size,
						  const bool coords,
						  const bool labels,
						  const COLORREF color,
						  const CRect window, 
						  DrawE destination,
						  CDC *pDC);
	
	bool DrawEquation(int nEq, SEquationStyle &style, CRect &window, CDC *pDC);

	
	int GraphToScreenX(const CRect window, long double x);
	int GraphToScreenY(const CRect window, long double y);
	long double ScreenToGraphX(const CRect window, int x);
	long double ScreenToGraphY(const CRect window, int y);

	// tracing functions
	bool InitializeTrace(int &nTraceEq);
	void ClearPrevTrace(UINT nEq,CBitmap &bitmap,CRect window,CDC *pDC);
	TraceRedrawMode DrawTrace(UINT nEq, CRect window,
								DrawE destination, CPen *pPen,
								CDC *pDC);
	void IncreaseTraceT();
	void DecreaseTraceT();
	void NextTraceEq(int direction, int &nTraceEq);
	CString GetTraceCoordsStr(UINT nEq);
	CString GetTraceXStr(CString eq);
	CString GetTraceYStr(CString eq);
	CString GetTraceTStr();
	
	CString GetDyDxStr(UINT nEq, long double t);
	ErrorT DyDx(CString eqX, CString eqY, long double t, long double &outAns);
	CString GetTangentEquation(CString eqX, CString eqY, long double t);
	void DrawTangentLine(int nEq,
						  long double &t, 
						  SEquationStyle &style, 
						  CRect window, 
						  CDC *pDC);
		
	
	/*void 			SetTraceX(long double val){ m_TraceX = val; }
	long double 	GetTraceX(){ return m_TraceX; }
	
		


	
	CString GetTraceXStr();
	CString GetTraceYStr(CString eq);

	void DrawDistance(DistStatusE distance,
					  const CString &EqOne,
					  const CString &EqTwo,
					  const long double &OneX,
					  const long double &TwoX,
					  const COLORREF bgcolor,
					  const CRect window, 
					  DrawE destination,
					  const SEquationStyle &style, 
					  CDC *pDC);

	void EraseDistance(const CString &EqOne,
					   const CString &EqTwo,
					   const long double &OneX,
					   const long double &TwoX,
					   const COLORREF bgcolor,
					   const CRect window, 
					   const SEquationStyle &style, 
					   CDC *pDC);

	CString GetDistanceStr( const CString &EqOne,
							const CString &EqTwo,
							const long double &OneX,
							const long double &TwoX);

	
	
	*/

private:
	int GetXAxisY(CRect window);
	int GetYAxisX(CRect window);

	void DrawXLabel(long double x, CRect window, CDC *pDC, 
						DrawE destination, double font_size, COLORREF color);

	bool AutoPan(long double x, long double y);

	// PRIVATE MEMBER VARIABLES
	int			m_LinePrec;

	long double	m_PrevTraceT;
};

#endif
