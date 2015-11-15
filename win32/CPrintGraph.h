#if !defined(CPRINTGRAPH)
#define CPRINTGRAPH

#include "resource.h"		// main symbols
#include "Print.h"			// Added by ClassView
#include "CCalculator.h"	// Added by ClassView
#include "Structs.h"


struct SGraphPrintLegend{
	S3DEquation threed;
	EquationT	twod;
	short		type; // 2 is 2D, 3 is 3D
};

class CPrintGraph{
public:
	void BeginPrinting();
	void EndPrinting();
	void InitializePrinting();

	CDC m_DC;
	bool DisplayOptions();

	CPrintGraph(int width, int height, CCalculator *pCalc, CArray<SGraphPrintLegend, SGraphPrintLegend> *Equations);

	int GetGraphWidth(){ return m_PrintOptions.m_graph_width; }
	int GetGraphHeight(){ return m_PrintOptions.m_graph_height; }


	
private:
	void Draw3DSwatch(CRect rect, S3DEquation eq);
	void Draw3DColor(CRect rect, S3DEquation eq);
	void Draw3DGrid(CRect rect);

	CArray<SGraphPrintLegend, SGraphPrintLegend> *m_Equations;
	void DrawTitle();
	void CalcGraphPosition();
	void DrawEquationList();
	void DrawEquationLegend(CRect eq_rect);
	void SetGraphSize();

	CPoint		m_GraphOrigin;
	CPoint		m_MaxSize;
	BOOL		m_bPrintingOK;
	CCalculator *m_pCalculator;
	CPrint		m_PrintOptions;
	CPrintInfo  m_Info;
};

#endif // !defined(CPRINTGRAPH)