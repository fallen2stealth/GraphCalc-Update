// CommandDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "CommandDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommandDlg dialog


CCommandDlg::CCommandDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommandDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommandDlg)
	m_sCommand = _T("");
	//}}AFX_DATA_INIT
}


void CCommandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommandDlg)
	DDX_Control(pDX, IDC_COMMANDS, m_CommandCtrl);
	DDX_LBString(pDX, IDC_COMMANDS, m_sCommand);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommandDlg, CDialog)
	//{{AFX_MSG_MAP(CCommandDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommandDlg message handlers

#define AddCommand(strCommand) \
	m_CommandCtrl.AddString(strCommand)

BOOL CCommandDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	AddCommand("Print");
	AddCommand("Save");
	AddCommand("Save=a");
	AddCommand("SaveAs=a");
	AddCommand("LoadSettings=a");
	AddCommand("SaveOutput=a");

	AddCommand("Sound=a");
	AddCommand("DetailOutput=a");
	AddCommand("SaveSettingsExit=a");
	AddCommand("SettingsFile=a");
	AddCommand("StartupScriptOn=a");
	AddCommand("StartupScriptFile=a");
	AddCommand("SaveExpressionHistory=a");
	AddCommand("SaveOutputWindow=a");
	AddCommand("ShowCommandErrors=a");

	AddCommand("NumberSeperator=a");
	AddCommand("NumberSeperatorChar=a");
	AddCommand("NumberSeperatorFreq=a");
	AddCommand("DecimalSeperator=a");
	AddCommand("DecimalSeperatorChar=a");
	AddCommand("DecimalSeperatorFreq=a");
	AddCommand("DecimalPlaces=a");
	AddCommand("Float=a");
	AddCommand("AngleUnit=a");
	AddCommand("Scientific=a");
	AddCommand("IntlMode=a");
	AddCommand("Base=a");

	AddCommand("Palette=a");
	AddCommand("Tooltips=a");
	AddCommand("Tab=a");
	AddCommand("AlwaysOnTop=a");
	AddCommand("FullWindow=a");

	AddCommand("ClearCharacter");
	AddCommand("ClearExpression");
	AddCommand("ClearOutput");
	AddCommand("ClearHistory");
	AddCommand("ClearGraph");
	AddCommand("ClearAll");
	AddCommand("Help");
	AddCommand("About");
	AddCommand("ExitScript");

	AddCommand("RunScript=a");
	AddCommand("Comment=a");
	AddCommand("Solve=a:b");
	AddCommand("Solve=a:b:c");

	AddCommand("2DGraphMode=a");
	AddCommand("2DEq=a:b");
	AddCommand("2DEqOn=a:b");
	AddCommand("2DEqColor=a:b");
	AddCommand("2DEqAllOn=a");
	AddCommand("2DEqAllEmpty");

	AddCommand("2DXmin=a");
	AddCommand("2DXmax=a");
	AddCommand("2DXint=a");
	AddCommand("2DYmin=a");
	AddCommand("2DYmax=a");
	AddCommand("2DYint=a");
	AddCommand("2DAreaPrecision=a");
	AddCommand("2DFixedGrid=a");
	
	AddCommand("2DPolarGridAngle=a");
	AddCommand("2DPolarGridSpace=a");
	AddCommand("2DPolarThetaMin=a");
	AddCommand("2DPolarThetaMax=a");
	AddCommand("2DPolarThetaStep=a");
	AddCommand("2DPolarXmin=a");
	AddCommand("2DPolarXmax=a");
	AddCommand("2DPolarYmin=a");
	AddCommand("2DPolarYmax=a");

	AddCommand("2DBackgroundColor=a");
	AddCommand("2DAxisColor=a");
	AddCommand("2DGridColor=a");
	AddCommand("2DCoordinatesColor=a");
	AddCommand("2DOtherTextColor=a");
	AddCommand("2DAreaColor=a");
	AddCommand("2DLabels=a");
	AddCommand("2DAxis=a");
	AddCommand("2DGrid=a");
	AddCommand("2DCoordinatesPos=a");
	AddCommand("2DAxisSize=a");
	AddCommand("2DGridSize=a");
	AddCommand("2DLineSize=a");
	AddCommand("2DZoomDecimalPrec=a");
	AddCommand("2DPlotStyle=a");
	AddCommand("2DLineResolution=a");
	AddCommand("2DZoomFactor=a");

	AddCommand("2DCopyGraph");
	AddCommand("2DZoomOutX");
	AddCommand("2DZoomOutY");
	AddCommand("2DZoomOutXY");
	AddCommand("2DZoomInX");
	AddCommand("2DZoomInY");
	AddCommand("2DZoomInXY");
	AddCommand("2DZoomStandard");
	AddCommand("2DZoomDecimalPrec");
	AddCommand("2DZoomTrig");
	AddCommand("2DZoomInteger");
	AddCommand("2DZoomFit");
	AddCommand("2DPreviousRange");
	AddCommand("2DTrace");
	AddCommand("2DFindAreaOff");
	AddCommand("2DFindArea=a:b:c");
	AddCommand("2DFindArea=a:b:c:d");
	AddCommand("2DEvaluate=a:b");
	AddCommand("2DTangentLine=a:b");
	AddCommand("2DClearTangentLines");
	AddCommand("2DDistanceOff");
	AddCommand("2DDistance=a:b:c");
	AddCommand("2DDistance=a:b:c:d");
	AddCommand("2DAddGraphTab");
	AddCommand("2DRenameTab=a");
	AddCommand("2DRemoveGraphTab=a");
	AddCommand("2DSaveBitmap=a");
	AddCommand("2DEqIntersection=a:b:c");
	AddCommand("2DXIntercept=a:b");
	AddCommand("2DYIntercept=a");
	AddCommand("2DStationaryPoint=a:b:c");
	AddCommand("2DDyDx=a:b");
	AddCommand("2DFontSize=a");

	
	AddCommand("3DBackgroundColor=a");
	
	AddCommand("3DWireResolution=a");
	AddCommand("3DWireWidth=a");
	AddCommand("3DAxesOn=a");
	AddCommand("3DAxesLabelsOn=a");
	AddCommand("3DXAxisColor=a");
	AddCommand("3DYAxisColor=a");
	AddCommand("3DZAxisColor=a");
	AddCommand("3DXAxisOrigin=a");
	AddCommand("3DYAxisOrigin=a");
	AddCommand("3DZAxisOrigin=a");

	AddCommand("3DTickMarksOn=a");
	AddCommand("3DCustomTickColor=a");
	AddCommand("3DXTickInterval=a");
	AddCommand("3DYTickInterval=a");
	AddCommand("3DZTickInterval=a");
	AddCommand("3DXTickColor=a");
	AddCommand("3DYTickColor=a");
	AddCommand("3DZTickColor=a");
	AddCommand("3DTickWidth=a");
	AddCommand("3DTickLength=a");

	AddCommand("3DXintervals=a");
	AddCommand("3DYintervals=a");
	AddCommand("3DXmin=a");
	AddCommand("3DXmax=a");
	AddCommand("3DYmin=a");
	AddCommand("3DYmax=a");

	AddCommand("3DGraphMode=a");
	AddCommand("3DEq=a:b");
	AddCommand("3DEqWireMode=a:b");
	AddCommand("3DEqShadeMode=a:b");
	AddCommand("3DEqColorXmaxYmax=a:b");
	AddCommand("3DEqColorXmaxYmin=a:b");
	AddCommand("3DEqColorXminYmin=a:b");
	AddCommand("3DEqColorXminYmax=a:b");
	AddCommand("3DEqOn=a:b");
	AddCommand("3DEqAllOn=a");
	AddCommand("3DEqAllEmpty");
	
	AddCommand("3DRecomputeAll");
	AddCommand("3DCopyGraph");
	AddCommand("3DZoomIn");
	AddCommand("3DZoomOut");
	AddCommand("3DReCenterView");
	AddCommand("3DSaveBitmap=a");
	AddCommand("3DExportDXF=a");
	
	AddCommand("3DZoomIn");
	AddCommand("3DZoomOut");
	AddCommand("3DRotateXIncrease");
	AddCommand("3DRotateXIncrease=a");
	AddCommand("3DRotateYIncrease");
	AddCommand("3DRotateYIncrease=a");
	AddCommand("3DRotateZIncrease");
	AddCommand("3DRotateZIncrease=a");
	AddCommand("3DRotateXDecrease");
	AddCommand("3DRotateXDecrease=a");
	AddCommand("3DRotateYDecrease");
	AddCommand("3DRotateYDecrease=a");
	AddCommand("3DRotateZDecrease");
	AddCommand("3DRotateZDecrease=a");
	
	AddCommand("3DAutoRotate");
	AddCommand("3DAutoRotateX");
	AddCommand("3DAutoRotateY");
	AddCommand("3DAutoRotateZ");
	AddCommand("3DAutoRotateIncreaseSpeed");
	AddCommand("3DAutoRotateDecreaseSpeed");

	//AddCommand("");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
