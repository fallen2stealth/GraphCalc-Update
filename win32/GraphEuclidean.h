#if !defined(CGRAPHEUCLIDEAN)
#define CGRAPHEUCLIDEAN

#include <afxwin.h>
#include "CCalculator.h"
#include "Structs.h"

#if !defined (DRAWE)
#define DRAWE
enum DrawE {BMP, SCRN, PRINT};
#endif

#if !defined (DISTSTATUSE)
#define DISTSTATUSE
enum DistStatusE {OFF, FIRST, SECOND, DONE};
#endif

#if !defined (GRAPHSTYLE)
#define GRAPHSTYLE
enum ELineStyle {GRAPH_STYLE_LINE, GRAPH_STYLE_POINT};

struct SEquationStyle{
	ELineStyle line;
	int		   size;
};
#endif

#if !defined (LINESTYLE)
#define LINESTYLE
struct SLineStyle{
	COLORREF	color;
	int			size;
	};
#endif

struct SEuclideanGrphRng{
	long double Xmin;
	long double Xmax;
	long double Xscl;
	long double Ymin;
	long double Ymax;
	long double Yscl;
};

#define GRAPH_THRESHOLD		10000

#if !defined (TRACEREDRAWMODE)
#define TRACEREDRAWMODE
enum TraceRedrawMode{TRACE_NONE, TRACE_PAN};
#endif

class CGraphEuclidean : public CObject{
public:
	
	void ValidateRanges();
	CGraphEuclidean();
	~CGraphEuclidean();
	
	void SetLinePrec(int val){ m_LinePrec = val; }
	int GetLinePrec(){ return m_LinePrec; }

	void SetTraceX(long double val){ m_TraceX = val; }
	long double GetTraceX(){ return m_TraceX; }
	void SetTracePixel(int val){ m_TracePixel = val; }
	int GetTracePixel(){ return m_TracePixel; }
	void SetPrevTracePixel(int val){ m_PrevTracePixel = val; }
	int GetPrevTracePixel(){ return m_PrevTracePixel; }

	SEuclideanGrphRng m_EuclideanRange;
	SEuclideanGrphRng m_PrevEuclideanRange;
	
	void SwapPrevCurRanges();
	void SetPreviousRange();
	void StoreCurrentRange();

	void DrawGrid(const SLineStyle &style, bool &grid_on, 
				  const CRect window, CDC *pDC,
				  DrawE destination, double font_size, 
				  COLORREF color, int label_interval=1);

	void DrawAxis(const SLineStyle &style, const CRect window, CDC *pDC);

	void DrawTangentLine(const EquationT &eqT, 
						 const long double &x, 
						 const SEquationStyle &style, 
						 const CRect window, 
						 CCalculator *pCalculator,
						 DrawE destination,
						 CDC *pDC);

	ErrorT DyDx(const CString eq, 
					 CCalculator *pCalculator, 
					 long double x,
					 long double &outAns);

	CString GetTangentEquation(const CString eq, 
							   CCalculator *pCalculator,
							   long double x);	

	void DrawCoordsLabels(const double font_size,
						  const bool coords,
						  const bool labels,
						  const COLORREF color,
						  const CRect window, 
						  DrawE destination,
						  CDC *pDC);
	
	CString GetDyDxStr(const CString eq, long double x);

	CString GetTraceDyDxStr(const CString eq);
	CString GetTraceXStr();
	CString GetTraceYStr(CString eq);

	bool DrawEquation(const EquationT &eqT, 
					  const SEquationStyle &style, 
					  const CRect &window, 
					  CCalculator *pCalculator,
					  CDC *pDC);

	void DrawDistance(DistStatusE distance,
					  const CString &EqOne,
					  const CString &EqTwo,
					  const long double &OneX,
					  const long double &TwoX,
					  const COLORREF bgcolor,
					  const CRect window, 
					  DrawE destination,
					  const SEquationStyle &style, 
					  CCalculator *pCalculator,
					  CDC *pDC);

	void EraseDistance(const CString &EqOne,
					   const CString &EqTwo,
					   const long double &OneX,
					   const long double &TwoX,
					   const COLORREF bgcolor,
					   const CRect window, 
					   const SEquationStyle &style, 
					   CCalculator *pCalculator,
					   CDC *pDC);

	CString GetDistanceStr( const CString &EqOne,
							const CString &EqTwo,
							const long double &OneX,
							const long double &TwoX,
							CCalculator *pCalculator);

	void InitializeTrace(const CRect window);
	CString GetTraceCoordsStr(const CString eq, CCalculator *pCalculator);
	TraceRedrawMode DrawTrace(const CString eq,
							  const CRect window,
							  DrawE destination,
							  CCalculator *pCalculator,
							  CPen *pPen,
							  CDC *pDC);
	
	void ClearPrevTrace(const CString eq,
						CBitmap &bitmap,
						const CRect window,
						CCalculator *pCalculator,
						CDC *pDC);

private:
	void DrawXLabel(long double x, CRect window, CDC *pDC, 
						DrawE destination, double font_size, COLORREF color);
	
	int GetXAxisY(CRect window);
	int GetYAxisX(CRect window);

	bool AutoPan(long double y, CCalculator *pCalculator);

	int GraphToScreenX(const CRect window, long double x, int precision);
	int GraphToScreenY(const CRect window, long double y);

	long double ScreenToGraphX(const CRect window, int x, int precision);


	int			m_LinePrec;

	// variables for tracing
	long double m_TraceX;  // the x value of the tracer.  0 is at the y-axis
	int			m_TracePixel;
	int			m_PrevTracePixel;
};

#endif
