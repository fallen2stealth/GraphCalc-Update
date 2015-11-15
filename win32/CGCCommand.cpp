#include "CGCCommand.h"
#include "GrphCalcDlg.h"
#include "PromptValDlg.h"

extern CCalculator *g_Calculator;

bool IsScriptCommand(CString command, CString condition, CString error, bool errors/*false*/)
{
	if(command.Find(condition) == 0)
		if(command.ReverseFind(')') == command.GetLength() - 1)
			return true;
		else if(errors)
			{
			CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
			pDlg->MessageBox(error,"Script Error", MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
			}
	return false;
}


bool IsIfCommand(CString command, bool errors/*false*/)
{
	// format is as follows
	// If(expression)
	return IsScriptCommand(command, "If(", "Warning: Missing ) in If statement!", errors);
}

bool IsElseIfCommand(CString command, bool errors/*false*/)
{
	// format is as follows
	// ElseIf(expression)
	return IsScriptCommand(command, "ElseIf(", "Warning: Missing ) in ElseIf statement!", errors);
}

bool IsWhileCommand(CString command, bool errors/*false*/)
{
	// format is as follows
	// While(expression)
	return IsScriptCommand(command, "While(", "Warning: Missing ) in While statement!", errors);
}

CString GetIfCondition(CString command)
{
	// ONLY CALL THIS WITH A VALID IF
	command.Delete(0,3);
	// be nice and allow them to miss the last )
	if(command.ReverseFind(')') == command.GetLength() - 1)
		command.Delete(command.GetLength() - 1,1);
	return command;
}

CString GetElseIfCondition(CString command)
{
	// ONLY CALL THIS WITH A VALID ELSEIF
	command.Delete(0,7);
	// be nice and allow them to miss the last )
	if(command.ReverseFind(')') == command.GetLength() - 1)
		command.Delete(command.GetLength() - 1,1);
	return command;
}

CString GetWhileCondition(CString command)
{
	// ONLY CALL THIS WITH A VALID WHILE
	command.Delete(0,6);
	// be nice and allow them to miss the last )
	if(command.ReverseFind(')') == command.GetLength() - 1)
		command.Delete(command.GetLength() - 1,1);
	return command;
}

CGCCommand::CGCCommand()
{
	InitializeCommands();
}

CGCCommand::~CGCCommand()
{
	m_pCalculator = 0;
	m_Parameters.RemoveAll();
}

void CGCCommand::SetControls(CCalculator *pCalc)
{
	m_pCalculator = pCalc;
}

bool CGCCommand::GetComment(CString command, CString &comment)
{
	m_eError = SUCCESS;
	m_sCommandAndArgs = command;

	command.TrimLeft('[');
	command.TrimRight(']');

	m_Command.Empty();
	m_Parameters.RemoveAll();
	m_StringParams.RemoveAll();
	m_NumberParams.RemoveAll();
	m_BoolParams.RemoveAll();

	if(!ExtractValidateCommand(command))
		return false;

	if(m_Command != "Comment")
		return false;
	
	if(!ParseParameters(command))
		return false;
	if(!ValidateParameters())
		return false;

	comment = m_StringParams[0];
	return true;
}

bool CGCCommand::ParseCommand(CString command)
{
	m_eError = SUCCESS;
	m_sCommandAndArgs = command;

	command.TrimLeft('[');
	command.TrimRight(']');

	m_Command.Empty();
	m_Parameters.RemoveAll();
	m_StringParams.RemoveAll();
	m_NumberParams.RemoveAll();
	m_BoolParams.RemoveAll();

	if(!ExtractValidateCommand(command))
		return false;
	if(!ParseParameters(command))
		return false;
	if(!ValidateParameters())
		return false;

	return true;
}

bool CGCCommand::ExecuteCommand(CString command)
{
	m_eError = SUCCESS;
	m_sCommandAndArgs = command;

	command.TrimLeft('[');
	command.TrimRight(']');

	m_Command.Empty();
	m_Parameters.RemoveAll();
	m_StringParams.RemoveAll();
	m_NumberParams.RemoveAll();
	m_BoolParams.RemoveAll();

	if(!ExtractValidateCommand(command))
		return false;
	if(!ParseParameters(command))
		return false;
	if(!ValidateParameters())
		return false;

	return PerformCommand();
}

bool CGCCommand::ExtractValidateCommand(CString &command)
{
	// extract command
	int eq_pos(command.Find("="));
	if(eq_pos == -1){
		m_Command = command;
		command.Empty();
	}
	else{
		m_Command = command.Left(eq_pos);
		command.Delete(0, eq_pos+1);
	}

	// validate command now
	for(int i(0); i <= m_NumberCommands; ++i){
		if(m_aCommands[i].name == m_Command){
			m_CommandIndex = i;
			return true;	
		}
	}

	m_eError = UNKOWN_COMMAND;

	return false;
}

bool CGCCommand::ParseParameters(CString &command)
{
	CString param;
	
	while(!command.IsEmpty()){
		
		if(command[0] != '"'){
			int col_pos(command.Find(":"));
			if(col_pos == -1){
				param = command;
				command.Empty();
			}
			else{
				param = command.Left(col_pos);
				command.Delete(0, col_pos+1);
			}

			if(param[param.GetLength() - 1] == '"'){
				m_eError = UNMATCHED_QUOTE;
				return false; // error, there needs to be a matching "
			}
		}
		else{
			command.Delete(0,1);
			int quote_pos(command.Find("\""));

			if(quote_pos == -1){
				m_eError = UNMATCHED_QUOTE;
				return false; // error, there needs to be a matching "
			}
			else{
				param = command.Left(quote_pos);
				command.Delete(0, quote_pos+1);
			}

		}
		m_Parameters.Add(param);
	}
	
	return true;
}

bool CGCCommand::ValidateParameters()
{
	if(m_Parameters.GetSize() > m_aCommands[m_CommandIndex].params.GetSize()){
		m_eError = TOO_MANY_ARGS;
		return false;
	}
	if(m_Parameters.GetSize() < m_aCommands[m_CommandIndex].GetRequiredArguments()){
		m_eError = TOO_FEW_ARGS;
		return false;
	}

	for(int i(0); i < m_Parameters.GetSize(); ++i){
		switch(m_aCommands[m_CommandIndex].params[i].type){
		case PARAM_STRING:
			{
				m_StringParams.Add(m_Parameters[i]);
				break;
			}
		case PARAM_NUMBER:
			{
				long double ans;
				if(!m_pCalculator->IsValid(m_Parameters[i])){
					m_eError = INVALID_NUMBER;
					return false;
				}

				if(m_pCalculator->Compute(m_Parameters[i], ans, 0) != SUCCESSFULL){
					m_eError = INVALID_NUMBER;
					return false;
				}
				
				m_NumberParams.Add(ans);
				break;
			}
		case PARAM_BOOL:
			{
				if(m_Parameters[i] == "on" || m_Parameters[i] == "yes")
					m_BoolParams.Add(true);
				else if(m_Parameters[i] == "off" || m_Parameters[i] == "no")
					m_BoolParams.Add(false);
				else{
					long double ans;
					
					if(!m_pCalculator->IsValid(m_Parameters[i])){
						m_eError = INVALID_NUMBER;
						return false;
					}
					
					if(m_pCalculator->Compute(m_Parameters[i], ans, 0) != SUCCESSFULL){
						m_eError = INVALID_NUMBER;
						return false;
					}
					
					if(ans > 0)
						m_BoolParams.Add(true);
					else
						m_BoolParams.Add(false);
				}
				break;
			}
		}
	}
	
	return true;
}

bool CGCCommand::PerformCommand()
{
	CGrphCalcDlg* pDlg = (CGrphCalcDlg*)STATIC_DOWNCAST(CDialog, AfxGetMainWnd());

	if(m_Command[0] == '2' && m_Command[1] == 'D'){
		if(pDlg->GetActiveGraphTabIndex() == -1){
			m_eError = NOT_ON_2D;
			return false;
		}
		
		return Perform2DCommand();
	}
#ifndef GRAPHCALC_LIGHT
	else if(m_Command[0] == '3' && m_Command[1] == 'D'){
		if(!pDlg->Is3DGraphActive()){
			m_eError = NOT_ON_3D;
			return false;
		}
	
		return Perform3DCommand();
	}
#endif
	else
		return PerformProgramCommand();
}

bool CGCCommand::PerformProgramCommand()
{
	CGrphCalcDlg* pDlg = (CGrphCalcDlg*)STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	WPARAM wpar;

	/////////////////////////////////////
	// SCRIPT
	if(m_Command == "Message")	pDlg->MessageBox(m_StringParams[0], "Script Message", MB_ICONINFORMATION | MB_OK);
	else if(m_Command == "DispVal")
		if(m_StringParams.GetSize() != 0)
			DispVal(m_NumberParams[0], m_StringParams[0]);
		else
			DispVal(m_NumberParams[0]);
	else if(m_Command == "PromptVal")
		if(m_StringParams.GetSize() == 2)
			PromptVal(m_StringParams[0], m_StringParams[1]);
		else
			PromptVal(m_StringParams[0]);
	else if(m_Command == "OutputWindow")	pDlg->m_OutputV.m_fOutputWindow = m_BoolParams[0];

	/////////////////////////////////////
	// FILE
#ifndef GRAPHCALC_LIGHT
	else if(m_Command == "Print"){			pDlg->SendMessage(WM_COMMAND, ID_FILE_PRINT, 0);	}
#endif
	else if(m_Command == "Save"){			pDlg->SendMessage(WM_COMMAND, ID_FILE_OPTIONS_SAVESETTINGSNOW, 0);}
	else if(m_Command == "SaveAs"){			pDlg->WriteSettings(m_Parameters[0]); }
	else if(m_Command == "LoadSettings"){	pDlg->ReadSettings(m_Parameters[0]); }
	else if(m_Command == "SaveOutput"){		pDlg->m_OutputV.SaveOutputToFile(m_StringParams[0]); }

	/////////////////////////////////////
	// OPTIONS
	else if(m_Command == "Sound"){				pDlg->SetSndEffects(m_BoolParams[0]); }
	else if(m_Command == "DetailedOutput"){		pDlg->SetDetailedOutput(m_BoolParams[0]); }
	else if(m_Command == "SaveSettingsExit"){	pDlg->SetSaveSettings(m_BoolParams[0]); }
	else if(m_Command == "SettingsFile"){		pDlg->SetSettingsFile(m_StringParams[0]); }
	else if(m_Command == "StartupScriptOn"){	pDlg->SetStartUpScript(m_BoolParams[0]); }
	else if(m_Command == "StartupScriptFile"){	pDlg->SetStartUpScriptFile(m_StringParams[0]); }
	else if(m_Command == "SaveExpressionHistory"){	pDlg->SetSaveExpression(m_BoolParams[0]); }
	else if(m_Command == "SaveOutputWindow"){	pDlg->SetSaveOutput(m_BoolParams[0]); }
	else if(m_Command == "ShowCommandErrors"){	pDlg->SetShowCommandErrors(m_BoolParams[0]); }
	

	/////////////////////////////////////
	// MODE	
	else if(m_Command == "NumberSeperator"){		m_pCalculator->m_NumberSeperator = m_BoolParams[0]; }
	else if(m_Command == "NumberSeperatorChar"){	m_pCalculator->m_NumberSpaceSeperator = m_StringParams[0][0]; }
	else if(m_Command == "NumberSeperatorFreq"){	m_pCalculator->m_NumberSeperatorAmount = m_NumberParams[0]; }
	else if(m_Command == "DecimalSeperator"){		m_pCalculator->m_DecimalSeperator = m_BoolParams[0]; }
	else if(m_Command == "DecimalSeperatorChar"){	m_pCalculator->m_DecimalSpaceSeperator = m_StringParams[0][0]; }
	else if(m_Command == "DecimalSeperatorFreq"){	m_pCalculator->m_DecimalSeperatorAmount = m_NumberParams[0]; }
	else if(m_Command == "DecimalPlaces"){			m_pCalculator->m_DecimalPlaces = m_NumberParams[0]; }
	else if(m_Command == "Float"){					m_pCalculator->m_Float = m_BoolParams[0]; }
	else if(m_Command == "AngleUnit"){				m_pCalculator->SetTrigState(m_StringParams[0]); }
	else if(m_Command == "Scientific"){				m_pCalculator->SetNormal(m_BoolParams[0]); }
	else if(m_Command == "IntlMode"){				m_pCalculator->SetIntlMode(m_StringParams[0]); }
	else if(m_Command == "Base"){ 
		if(m_NumberParams[0] < 2 || m_NumberParams[0] > 36)
			m_pCalculator->m_base = 10;
		else
			m_pCalculator->m_base = m_NumberParams[0];
	}

	/////////////////////////////////////
	// VIEW
	else if(m_Command == "Palette"){ 
		if(m_StringParams[0] == "probability")	wpar = ID_PALETES_PROB;
		else if(m_StringParams[0] == "math")	wpar = ID_PALETES_MATH;
		else if(m_StringParams[0] == "stats")	wpar = ID_PALETES_STATS;
		else if(m_StringParams[0] == "test")	wpar = ID_PALETES_TEST;
		else if(m_StringParams[0] == "hex")	wpar = ID_PALETES_LETTERS;
		else if(m_StringParams[0] == "none")	wpar = ID_PALETES_NONE;
		else{
			m_eError = UNKNOWN_ARG_VAL;
			return false;
		}

		pDlg->SendMessage(WM_COMMAND, wpar, 0);
	}
	else if(m_Command == "Tooltips"){		pDlg->SetTooltips(m_BoolParams[0]); }
	else if(m_Command == "Tab"){			pDlg->SetTab(m_StringParams[0]); }
	else if(m_Command == "AlwaysOnTop"){	pDlg->SetAlwaysOnTop(m_BoolParams[0]); }
	else if(m_Command == "FullWindow"){		pDlg->SetFullScreen(m_BoolParams[0]); }


	/////////////////////////////////////
	// MISC
	else if(m_Command == "ClearCharacter"){		pDlg->SendMessage(WM_COMMAND, ID_CLEAR_1, 0);	}
	else if(m_Command == "ClearExpression"){	pDlg->SendMessage(WM_COMMAND, ID_CLEAR_2, 0);	}
	else if(m_Command == "ClearOutput"){		pDlg->SendMessage(WM_COMMAND, ID_CLEAR_4, 0);	}
	else if(m_Command == "ClearHistory"){		pDlg->SendMessage(WM_COMMAND, ID_CLEAR_5, 0);	}
	else if(m_Command == "ClearGraph"){			pDlg->SendMessage(WM_COMMAND, ID_CLEAR_3, 0);	}
	else if(m_Command == "ClearAll"){			pDlg->SendMessage(WM_COMMAND, ID_CLEAR_ALL, 0);	}
	else if(m_Command == "Help"){				pDlg->SendMessage(WM_COMMAND, ID_HELP, 0);		}
	else if(m_Command == "About"){				pDlg->SendMessage(WM_COMMAND, ID_APP_ABOUT, 0);	}
	else if(m_Command == "RunScript"){			pDlg->RunScript(m_StringParams[0]); }
	else if(m_Command == "ExitScript"){			pDlg->SendMessage(WM_COMMAND, ID_QUIT_SCRIPT, 0); }
	else if(m_Command == "Comment"){			pDlg->m_OutputV.AddEntry(m_StringParams[0]); }
	else if(m_Command == "Solve"){
		if(m_StringParams.GetSize() == 2)
			pDlg->Solve(m_StringParams[0], m_NumberParams[0], m_StringParams[1]);
		else
			pDlg->Solve(m_StringParams[0], m_NumberParams[0]);
		}
	else{
		m_eError = UNKOWN_COMMAND;
		return false;
	}

	pDlg = 0;
	return true;
}

bool CGCCommand::Perform2DCommand()
{
	CGrphCalcDlg* pDlg = (CGrphCalcDlg*)STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	int tab = pDlg->GetActiveGraphTabIndex();

	/////////////////////////////////////
	// EQUATIONS
	if(m_Command == "2DEq"){				pDlg->SetEquation(m_NumberParams[0] - 1, m_StringParams[0]); }
	else if(m_Command == "2DEqOn"){			pDlg->SetEquationState(m_NumberParams[0] - 1, m_BoolParams[0]); }
	else if(m_Command == "2DEqColor"){		pDlg->SetEquationColor(m_NumberParams[0] - 1, m_StringParams[0]); }
	else if(m_Command == "2DEqAllOn"){		pDlg->m_GraphViewList[tab].SetAllEquationState(m_BoolParams[0]); }
	else if(m_Command == "2DEqAllEmpty"){	pDlg->m_GraphViewList[tab].EmptyAllEquations();}

	/////////////////////////////////////
	// RANGE & PRECISION
	else if(m_Command == "2DXmin"){			pDlg->SetGraphNumber(m_Command, m_NumberParams[0]); }
	else if(m_Command == "2DXmax"){			pDlg->SetGraphNumber(m_Command, m_NumberParams[0]); }
	else if(m_Command == "2DXint"){			pDlg->SetGraphNumber(m_Command, m_NumberParams[0]); }
	else if(m_Command == "2DYmin"){			pDlg->SetGraphNumber(m_Command, m_NumberParams[0]); }
	else if(m_Command == "2DYmax"){			pDlg->SetGraphNumber(m_Command, m_NumberParams[0]); }
	else if(m_Command == "2DYint"){			pDlg->SetGraphNumber(m_Command, m_NumberParams[0]); }
	else if(m_Command == "2DAreaPrecision"){pDlg->SetGraphNumber(m_Command, m_NumberParams[0]); }
	else if(m_Command == "2DFixedGrid"){	pDlg->SetGraphBool(m_Command, m_BoolParams[0]); }
	
	else if(m_Command == "2DPolarXmin" || m_Command == "2DPolarXmax" ||
		    m_Command == "2DPolarYmin" || m_Command == "2DPolarYmax" ||
		    m_Command == "2DPolarThetaMin" || m_Command == "2DPolarThetaMax" ||
		    m_Command == "2DPolarThetaStep" || m_Command == "2DPolarGridAngle" ||
			m_Command == "2DPolarGridSpace")
		pDlg->SetGraphNumber(m_Command, m_NumberParams[0]); 

	/////////////////////////////////////
	// DISPLAY
	else if(m_Command == "2DBackgroundColor"){	pDlg->SetGraphString(m_Command, m_StringParams[0]); }
	else if(m_Command == "2DAxisColor"){		pDlg->SetGraphString(m_Command, m_StringParams[0]); }
	else if(m_Command == "2DGridColor"){		pDlg->SetGraphString(m_Command, m_StringParams[0]); }
	else if(m_Command == "2DCoordinatesColor"){ pDlg->SetGraphString(m_Command, m_StringParams[0]); }
	else if(m_Command == "2DOtherText"){		pDlg->SetGraphString(m_Command, m_StringParams[0]); }
	else if(m_Command == "2DAreaColor"){		pDlg->SetGraphString(m_Command, m_StringParams[0]); }
	
	else if(m_Command == "2DLabels"){			pDlg->SetGraphBool(m_Command, m_BoolParams[0]); }
	else if(m_Command == "2DAxis"){				pDlg->SetGraphBool(m_Command, m_BoolParams[0]); }
	else if(m_Command == "2DGrid"){				pDlg->SetGraphBool(m_Command, m_BoolParams[0]); }
	else if(m_Command == "2DCoordinatesPos"){	pDlg->SetGraphBool(m_Command, m_BoolParams[0]); }

	else if(m_Command == "2DAxisSize"){			pDlg->SetGraphNumber(m_Command, m_NumberParams[0]); }
	else if(m_Command == "2DGridSize"){			pDlg->SetGraphNumber(m_Command, m_NumberParams[0]); }
	else if(m_Command == "2DLineSize"){			pDlg->SetGraphNumber(m_Command, m_NumberParams[0]); }
	else if(m_Command == "2DZoomDecimalPrec"){	pDlg->SetGraphNumber(m_Command, m_NumberParams[0]); }
	
	else if(m_Command == "2DPlotStyle"){		pDlg->SetGraphString(m_Command, m_StringParams[0]); }
	else if(m_Command == "2DLineResolution"){	pDlg->SetGraphNumber(m_Command, m_NumberParams[0]); }
	else if(m_Command == "2DZoomFactor"){		pDlg->SetGraphNumber(m_Command, m_NumberParams[0]); }
	else if(m_Command == "2DFontSize"){			pDlg->SetGraphNumber(m_Command, m_NumberParams[0]); }

	/////////////////////////////////////
	// MENU COMMANDS
	else if(m_Command == "2DRecomputeAll"){		pDlg->m_GraphViewList[tab].RePaintNow(); }
	GraphCalcFull(else if(m_Command == "2DCopyGraph"){		pDlg->m_GraphViewList[tab].DoCopy(); })
	else if(m_Command == "2DZoomOutX"){			pDlg->SendMessage(WM_COMMAND, ID_GRAPH_ZOOM_OUT_X, 0); }
	else if(m_Command == "2DZoomOutY"){			pDlg->SendMessage(WM_COMMAND, ID_GRAPH_ZOOM_OUT_Y, 0); }
	else if(m_Command == "2DZoomOutXY"){		pDlg->SendMessage(WM_COMMAND, ID_GRAPH_ZOOM_OUT_XY, 0); }
	else if(m_Command == "2DZoomInX"){			pDlg->SendMessage(WM_COMMAND, ID_GRAPH_ZOOM_IN_X, 0); }
	else if(m_Command == "2DZoomInY"){			pDlg->SendMessage(WM_COMMAND, ID_GRAPH_ZOOM_IN_Y, 0); }
	else if(m_Command == "2DZoomInXY"){			pDlg->SendMessage(WM_COMMAND, ID_GRAPH_ZOOM_IN_XY, 0); }
	else if(m_Command == "2DZoomStandard"){		pDlg->SendMessage(WM_COMMAND, ID_GRAPH_ZOOM_STANDARD, 0); }
	else if(m_Command == "2DZoomDecimalPrec"){	pDlg->SendMessage(WM_COMMAND, ID_GRAPH_ZOOM_DECIMAL, 0); }
	else if(m_Command == "2DZoomTrig"){			pDlg->SendMessage(WM_COMMAND, ID_GRAPH_ZOOM_TRIG, 0); }
	else if(m_Command == "2DZoomInteger"){		pDlg->SendMessage(WM_COMMAND, ID_GRAPH_ZOOM_INTEGER, 0); }
	else if(m_Command == "2DZoomFit"){			pDlg->SendMessage(WM_COMMAND, ID_GRAPH_ZOOM_FIT, 0); }
	else if(m_Command == "2DPreviousRange"){	pDlg->SendMessage(WM_COMMAND, ID_GRAPH_ZOOM_PREVIOUSRANGE, 0); }

	else if(m_Command == "2DTrace"){ pDlg->m_GraphViewList[tab].SetTraceState(m_BoolParams[0]); }
	else if(m_Command == "2DFindAreaOff")
			pDlg->m_GraphViewList[tab].FindAreaOff();
	else if(m_Command == "2DFindArea"){ 
		if(m_NumberParams.GetSize() == 3)
			pDlg->FindGraphArea(m_BoolParams[0], m_NumberParams[2] - 1, -1, m_NumberParams[0], m_NumberParams[1]); 
		else if(m_NumberParams.GetSize() == 4)
			pDlg->FindGraphArea(m_BoolParams[0], m_NumberParams[2] - 1, m_NumberParams[3] - 1, m_NumberParams[0], m_NumberParams[1]);
	}
	else if(m_Command == "2DEvaluate"){ pDlg->Evaluate2DEquation(m_NumberParams[0], m_NumberParams[1]); } 
	else if(m_Command == "2DTangentLine"){ pDlg->GraphTangentLine(m_NumberParams[0]-1, m_NumberParams[1]); } 
	else if(m_Command == "2DClearTangentLines"){ pDlg->m_GraphViewList[tab].OnClearTangentLines(); }
	else if(m_Command == "2DAddGraphTab"){ pDlg->SendMessage(WM_COMMAND, ID_GRAPH_ADDGRAPHTAB, 0); }
	else if(m_Command == "2DRenameTab"){ pDlg->RenameGraphTab(m_StringParams[0]); }
	else if(m_Command == "2DDistanceOff")
		pDlg->m_GraphViewList[tab].m_Distance = OFF;
	else if(m_Command == "2DDistance"){ 
		if(m_NumberParams.GetSize() == 3)
			pDlg->FindGraphDistance(m_NumberParams[2] - 1, m_NumberParams[2] - 1, m_NumberParams[0], m_NumberParams[1]); 
		else if(m_NumberParams.GetSize() == 4)
			pDlg->FindGraphDistance(m_NumberParams[2] - 1, m_NumberParams[3] - 1, m_NumberParams[0], m_NumberParams[1]);
	}

	else if(m_Command == "2DRemoveGraphTab"){ pDlg->RemoveGraphTab(m_StringParams[0]); }
	else if(m_Command == "2DSaveBitmap")	  pDlg->m_GraphViewList[tab].SaveBitmap(m_StringParams[0]);
	else if(m_Command == "2DGraphMode"){
		m_StringParams[0].MakeLower();

		if(m_StringParams[0] == "euclidean") pDlg->m_GraphViewList[tab].m_Mode = EUCLIDEAN;
		else if(m_StringParams[0] == "polar") pDlg->m_GraphViewList[tab].m_Mode = POLAR;
		else{
			m_eError = UNKNOWN_ARG_VAL;
			return false;
		}
	}
	else if(m_Command == "2DEqIntersection"){ pDlg->Graph2DEqIntersection(int(m_NumberParams[0]-1), int(m_NumberParams[1]-1), m_NumberParams[2]); }
	else if(m_Command == "2DXIntercept"){ pDlg->Graph2DXIntercept(int(m_NumberParams[0]-1), m_NumberParams[1]); }
	else if(m_Command == "2DYIntercept"){ pDlg->Graph2DYIntercept(int(m_NumberParams[0]-1)); }
	else if(m_Command == "2DStationaryPoint"){ pDlg->Graph2DStationaryPoint(int(m_NumberParams[0]-1), m_NumberParams[1], m_NumberParams[2]); }
	else if(m_Command == "2DDyDx"){ pDlg->Graph2DDyDx(int(m_NumberParams[0]-1), m_NumberParams[1]); }
	else{
		m_eError = UNKOWN_COMMAND;
		return false;
	}

	if(m_Command != "2DCopyGraph"
	&& m_Command != "2DSaveBitmap"
	&& m_Command != "2DRecomputeAll")
		pDlg->m_GraphViewList[tab].RePaintNow();
	return true;
}

#ifndef GRAPHCALC_LIGHT
bool CGCCommand::Perform3DCommand()
{
	CGrphCalcDlg* pDlg = (CGrphCalcDlg*)STATIC_DOWNCAST(CDialog, AfxGetMainWnd());

	if(m_Command == "3DWireResolution")			pDlg->m_3DGraphView->SetWireResolution(m_NumberParams[0]); 
	else if(m_Command == "3DGridLineWidth")		pDlg->m_3DGraphView->SetGridlineWidth(m_NumberParams[0]);
	else if(m_Command == "3DXAxisOrigin")		pDlg->m_3DGraphView->SetOriginX(m_NumberParams[0]);
	else if(m_Command == "3DYAxisOrigin")		pDlg->m_3DGraphView->SetOriginY(m_NumberParams[0]);
	else if(m_Command == "3DZAxisOrigin")		pDlg->m_3DGraphView->SetOriginZ(m_NumberParams[0]);
	else if(m_Command == "3DXTickInterval")		pDlg->m_3DGraphView->SetTickXInterval(m_NumberParams[0]);
	else if(m_Command == "3DYTickInterval")		pDlg->m_3DGraphView->SetTickYInterval(m_NumberParams[0]);
	else if(m_Command == "3DZTickInterval")		pDlg->m_3DGraphView->SetTickZInterval(m_NumberParams[0]);
	else if(m_Command == "3DTickWidth")			pDlg->m_3DGraphView->SetTickWidth(m_NumberParams[0]);
	else if(m_Command == "3DTickLength")		pDlg->m_3DGraphView->SetTickLength(m_NumberParams[0]);
	else if(m_Command == "3DXintervals")		pDlg->m_3DGraphView->SetXInterval(m_NumberParams[0]);
	else if(m_Command == "3DYintervals")		pDlg->m_3DGraphView->SetYInterval(m_NumberParams[0]);
	else if(m_Command == "3DXmin")				pDlg->m_3DGraphView->SetXmin(m_NumberParams[0]);
	else if(m_Command == "3DXmax")				pDlg->m_3DGraphView->SetXmax(m_NumberParams[0]);
	else if(m_Command == "3DYmin")				pDlg->m_3DGraphView->SetYmin(m_NumberParams[0]);
	else if(m_Command == "3DYmax")				pDlg->m_3DGraphView->SetYmax(m_NumberParams[0]);

	else if(m_Command == "3DBackgroundColor")	pDlg->m_3DGraphView->SetBGColor(ColorLookupColorT(m_StringParams[0]));
	else if(m_Command == "3DXAxisColor")		pDlg->m_3DGraphView->SetXColor(ColorLookupColorT(m_StringParams[0]));
	else if(m_Command == "3DYAxisColor")		pDlg->m_3DGraphView->SetYColor(ColorLookupColorT(m_StringParams[0]));
	else if(m_Command == "3DZAxisColor")		pDlg->m_3DGraphView->SetZColor(ColorLookupColorT(m_StringParams[0]));
	else if(m_Command == "3DXTickColor")		pDlg->m_3DGraphView->SetTickXColor(ColorLookupColorT(m_StringParams[0]));
	else if(m_Command == "3DYTickColor")		pDlg->m_3DGraphView->SetTickYColor(ColorLookupColorT(m_StringParams[0]));
	else if(m_Command == "3DZTickColor")		pDlg->m_3DGraphView->SetTickZColor(ColorLookupColorT(m_StringParams[0]));

	else if(m_Command == "3DAxesOn")			pDlg->m_3DGraphView->SetAxesOn(m_BoolParams[0]);
	else if(m_Command == "3DAxesLabelsOn")		pDlg->m_3DGraphView->SetAxesLabelsOn(m_BoolParams[0]);
	else if(m_Command == "3DTickMarksOn")		pDlg->m_3DGraphView->SetTicksOn(m_BoolParams[0]);
	else if(m_Command == "3DCustomTickColor")	pDlg->m_3DGraphView->SetTickCustomColor(m_BoolParams[0]);

	else if(m_Command == "3DEq")				pDlg->m_3DGraphView->SetEquationRawString(m_NumberParams[0], m_StringParams[0]);
	else if(m_Command == "3DEqWireMode"){
		m_StringParams[0].MakeLower();
		if(m_StringParams[0] == "w")
			pDlg->m_3DGraphView->SetEquationWireMode(m_NumberParams[0], W);
		else if(m_StringParams[0] == "c")
			pDlg->m_3DGraphView->SetEquationWireMode(m_NumberParams[0], C);
		else if(m_StringParams[0] == "cww")
			pDlg->m_3DGraphView->SetEquationWireMode(m_NumberParams[0], CW);
		else if(m_StringParams[0] == "cw")
			pDlg->m_3DGraphView->SetEquationWireMode(m_NumberParams[0], CW);
		else{
			m_eError = UNKNOWN_ARG_VAL;
			return false;
		}
	}
	else if(m_Command == "3DEqShadeMode"){
		m_StringParams[0].MakeLower();
		if(m_StringParams[0] == "xypos")
			pDlg->m_3DGraphView->SetEquationShadeMode(m_NumberParams[0], FOUR_COLOR);
		else if(m_StringParams[0] == "elevation")
			pDlg->m_3DGraphView->SetEquationShadeMode(m_NumberParams[0], TWO_COLOR);
		else{
			m_eError = UNKNOWN_ARG_VAL;
			return false;
		}
	}
	else if(m_Command == "3DEqColorXmaxYmax")	pDlg->m_3DGraphView->SetEquationColorXmaxYmax(m_NumberParams[0], ColorLookupColorT(m_StringParams[0]));
	else if(m_Command == "3DEqColorXmaxYmin")	pDlg->m_3DGraphView->SetEquationColorXmaxYmin(m_NumberParams[0], ColorLookupColorT(m_StringParams[0]));
	else if(m_Command == "3DEqColorXminYmin")	pDlg->m_3DGraphView->SetEquationColorXminYmin(m_NumberParams[0], ColorLookupColorT(m_StringParams[0]));
	else if(m_Command == "3DEqColorXminYmax")	pDlg->m_3DGraphView->SetEquationColorXminYmax(m_NumberParams[0], ColorLookupColorT(m_StringParams[0]));
	else if(m_Command == "3DEqOn")				pDlg->m_3DGraphView->SetEquationOn(m_NumberParams[0], m_BoolParams[0]);
	else if(m_Command == "3DEqAllOn")
		{
		for(int i=0; i < MAX_3D_EQS; ++i)
			pDlg->m_3DGraphView->m_3DEquations[i].on = m_BoolParams[0];
		}
	else if(m_Command == "3DEqAllEmpty")
		{
		for(int i=0; i < MAX_3D_EQS; ++i)
			{
			pDlg->m_3DGraphView->m_3DEquations[i].on = false;
			pDlg->m_3DGraphView->m_3DEquations[i].eq = "";
			}
		pDlg->m_3DGraphView->ExpandEquations();
		}
	
	else if(m_Command == "3DRecomputeAll")		pDlg->m_3DGraphView->ReCompute();
	else if(m_Command == "3DCopyGraph")			pDlg->m_3DGraphView->CopyGraph();
	else if(m_Command == "3DZoomOut")			pDlg->m_3DGraphView->ZoomOutZ(false);
	else if(m_Command == "3DZoomIn")			pDlg->m_3DGraphView->ZoomInZ(false);
	else if(m_Command == "3DReCenterView")		pDlg->m_3DGraphView->CenterView();
	else if(m_Command == "3DSaveBitmap")		pDlg->m_3DGraphView->SaveBitmap(m_StringParams[0]);
	else if(m_Command == "3DExportDXF")			pDlg->m_3DGraphView->ExportDXF(m_StringParams[0]);
	
	else if(m_Command == "3DRotateXIncrease"){
		if(m_NumberParams.GetSize() == 1)
			pDlg->m_3DGraphView->RotateXIncrease(m_NumberParams[0]);
		else
			pDlg->m_3DGraphView->RotateXIncrease();
	}
	else if(m_Command == "3DRotateYIncrease"){
		if(m_NumberParams.GetSize() == 1)
			pDlg->m_3DGraphView->RotateYIncrease(m_NumberParams[0]);
		else
			pDlg->m_3DGraphView->RotateYIncrease();
	}
	else if(m_Command == "3DRotateZIncrease"){
		if(m_NumberParams.GetSize() == 1)
			pDlg->m_3DGraphView->RotateZIncrease(m_NumberParams[0]);
		else
			pDlg->m_3DGraphView->RotateZIncrease();
	}else if(m_Command == "3DRotateXDecrease"){
		if(m_NumberParams.GetSize() == 1)
			pDlg->m_3DGraphView->RotateXDecrease(m_NumberParams[0]);
		else
			pDlg->m_3DGraphView->RotateXDecrease();
	}
	else if(m_Command == "3DRotateYDecrease"){
		if(m_NumberParams.GetSize() == 1)
			pDlg->m_3DGraphView->RotateYDecrease(m_NumberParams[0]);
		else
			pDlg->m_3DGraphView->RotateYDecrease();
	}
	else if(m_Command == "3DRotateZDecrease"){
		if(m_NumberParams.GetSize() == 1)
			pDlg->m_3DGraphView->RotateZDecrease(m_NumberParams[0]);
		else
			pDlg->m_3DGraphView->RotateZDecrease();
	}
	else if(m_Command == "3DGraphMode"){
		if(m_StringParams[0] == "euclidean")
			pDlg->m_3DGraphView->SetGraphModePolar(false);
		else if(m_StringParams[0] == "polar")
			pDlg->m_3DGraphView->SetGraphModePolar(true);
		else{
			m_eError = UNKNOWN_ARG_VAL;
			return false;
		}
	}
	else if(m_Command == "3DEvaluate"){ pDlg->Evaluate3DEquation(m_NumberParams[0], m_NumberParams[1], m_NumberParams[2]); } 
	else if(m_Command == "3DAutoRotate"){ pDlg->PostMessage(WM_COMMAND, ID_3DGRAPH_AUTOROTATE_ALLAXIS, 0); } 
	else if(m_Command == "3DAutoRotateX"){ pDlg->PostMessage(WM_COMMAND, ID_3DGRAPH_AUTOROTATE_XAXIS, 0); } 
	else if(m_Command == "3DAutoRotateY"){ pDlg->PostMessage(WM_COMMAND, ID_3DGRAPH_AUTOROTATE_YAXIS, 0); } 
	else if(m_Command == "3DAutoRotateZ"){ pDlg->PostMessage(WM_COMMAND, ID_3DGRAPH_AUTOROTATE_ZAXIS, 0); } 
	else if(m_Command == "3DAutoRotateIncreaseSpeed"){ pDlg->PostMessage(WM_COMMAND, ID_3DGRAPH_AUTOROTATE_INCREASESPEED, 0); } 
	else if(m_Command == "3DAutoRotateDecreaseSpeed"){ pDlg->PostMessage(WM_COMMAND, ID_3DGRAPH_AUTOROTATE_DECREASESPEED, 0); } 
	else{
		m_eError = UNKOWN_COMMAND;
		return false;
	}

	pDlg->m_3DGraphView->Paint();

	return true;
}
#endif

SCommandParam CGCCommand::NewParam(ParamTypeE type, bool required)
{
	SCommandParam nparam;
	nparam.required = required;
	nparam.type = type;

	return nparam;
}

SCommandParam CGCCommand::NewParam(ParamTypeE type)
{
	SCommandParam nparam;
	nparam.required = true;
	nparam.type = type;

	return nparam;
}

void CGCCommand::InitializeCommands()
{
	int i(0);

	/////////////////////////////////////
	// SCRIPT
	m_aCommands[i].name = "Message";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "DispVal";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_STRING, false));
	m_aCommands[++i].name = "PromptVal";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[i].params.Add(NewParam(PARAM_STRING, false));
	m_aCommands[++i].name = "OutputWindow";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	

	/////////////////////////////////////
	// FILE
	m_aCommands[++i].name = "Print";
	m_aCommands[++i].name = "Save";
	m_aCommands[++i].name = "SaveAs";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "LoadSettings";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));	
	m_aCommands[++i].name = "SaveOutput";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));	

	/////////////////////////////////////
	// OPTIONS
	m_aCommands[++i].name = "Sound";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "DetailedOutput";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "SaveSettingsExit";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));

	m_aCommands[++i].name = "SettingsFile";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "StartupScriptOn";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "StartupScriptFile";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "SaveExpressionHistory";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "SaveOutputWindow";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "ShowCommandErrors";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	
	/////////////////////////////////////
	// MODE	
	m_aCommands[++i].name = "NumberSeperator";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "NumberSeperatorChar";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "NumberSeperatorFreq";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "DecimalSeperator";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "DecimalSeperatorChar";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "DecimalSeperatorFreq";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "DecimalPlaces";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "Float";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "AngleUnit";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "Scientific";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "IntlMode";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "Base";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	
	/////////////////////////////////////
	// VIEW
	m_aCommands[++i].name = "Palette";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "Tooltips";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "Tab";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "AlwaysOnTop";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "FullWindow";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));

	/////////////////////////////////////
	// MISC
	m_aCommands[++i].name = "ClearCharacter";
	m_aCommands[++i].name = "ClearExpression";
	m_aCommands[++i].name = "ClearOutput";
	m_aCommands[++i].name = "ClearHistory";
	m_aCommands[++i].name = "ClearGraph";
	m_aCommands[++i].name = "ClearAll";
	m_aCommands[++i].name = "Help";
	m_aCommands[++i].name = "About";
	m_aCommands[++i].name = "ExitScript";

	m_aCommands[++i].name = "RunScript";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "Comment";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "Solve";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_STRING, false));


	/////////////////////////////////////
	/////////////////////////////////////
	// 2D Graphing

	/////////////////////////////////////
	// EQUATIONS
	m_aCommands[++i].name = "2DGraphMode";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));

	m_aCommands[++i].name = "2DEq";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "2DEqOn";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "2DEqColor";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));	
	m_aCommands[++i].name = "2DEqAllOn";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "2DEqAllEmpty";

	/////////////////////////////////////
	// RANGE & PRECISION
	m_aCommands[++i].name = "2DXmin";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DXmax";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DXint";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DYmin";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DYmax";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DYint";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DAreaPrecision";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DFixedGrid";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	
	m_aCommands[++i].name = "2DPolarThetaMin";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DPolarThetaMax";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DPolarThetaStep";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DPolarGridAngle";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DPolarGridSpace";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DPolarXmax";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DPolarXmin";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DPolarYmin";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DPolarYmax";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));

	/////////////////////////////////////
	// DISPLAY
	m_aCommands[++i].name = "2DBackgroundColor";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "2DAxisColor";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "2DGridColor";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "2DCoordinatesColor";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "2DOtherText";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "2DAreaColor";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));

	m_aCommands[++i].name = "2DLabels";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "2DAxis";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "2DGrid";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "2DCoordinatesPos";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));

	m_aCommands[++i].name = "2DAxisSize";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DGridSize";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DLineSize";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DZoomDecimalPrec";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));

	m_aCommands[++i].name = "2DPlotStyle";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "2DLineResolution";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DZoomFactor";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DFontSize";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	
	

	/////////////////////////////////////
	// MENU COMMANDS
	m_aCommands[++i].name = "2DRecomputeAll";
	m_aCommands[++i].name = "2DCopyGraph";
	m_aCommands[++i].name = "2DZoomOutX";
	m_aCommands[++i].name = "2DZoomOutY";
	m_aCommands[++i].name = "2DZoomOutXY";
	m_aCommands[++i].name = "2DZoomInX";
	m_aCommands[++i].name = "2DZoomInY";
	m_aCommands[++i].name = "2DZoomInXY";
	m_aCommands[++i].name = "2DZoomStandard";
	m_aCommands[++i].name = "2DZoomDecimalPrec";
	m_aCommands[++i].name = "2DZoomTrig";
	m_aCommands[++i].name = "2DZoomInteger";
	m_aCommands[++i].name = "2DZoomFit";
	m_aCommands[++i].name = "2DPreviousRange";
	m_aCommands[++i].name = "2DTrace";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "2DFindAreaOff";
	m_aCommands[++i].name = "2DFindArea";		
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER, false));
	m_aCommands[++i].name = "2DEvaluate";		
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DTangentLine";		
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DClearTangentLines";
	m_aCommands[++i].name = "2DDistanceOff";	
	m_aCommands[++i].name = "2DDistance";		
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER, false));
	m_aCommands[++i].name = "2DAddGraphTab";
	m_aCommands[++i].name = "2DRenameTab";	
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "2DRemoveGraphTab";	
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "2DSaveBitmap";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "2DEqIntersection";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DXIntercept";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DYIntercept";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DStationaryPoint";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[++i].name = "2DDyDx";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));

	/////////////////////////////////////
	/////////////////////////////////////
	// 3D Graphing

	/////////////////////////////////////
	// MISC, WIREFRAME, AXES OPTIONS
	m_aCommands[++i].name = "3DBackgroundColor";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));	
	m_aCommands[++i].name = "3DEvaluate";		
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));

	m_aCommands[++i].name = "3DWireResolution";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));	
	m_aCommands[++i].name = "3DGridLineWidth";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));	
	m_aCommands[++i].name = "3DAxesOn";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));		
	m_aCommands[++i].name = "3DAxesLabelsOn";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "3DXAxisColor";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "3DYAxisColor";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "3DZAxisColor";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));	
	m_aCommands[++i].name = "3DXAxisOrigin";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));	
	m_aCommands[++i].name = "3DYAxisOrigin";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));	
	m_aCommands[++i].name = "3DZAxisOrigin";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));

	/////////////////////////////////////
	// TICK MARKS		
	m_aCommands[++i].name = "3DTickMarksOn";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));	
	m_aCommands[++i].name = "3DCustomTickColor";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "3DXTickInterval";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));	
	m_aCommands[++i].name = "3DYTickInterval";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));	
	m_aCommands[++i].name = "3DZTickInterval";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));	
	m_aCommands[++i].name = "3DXTickColor";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "3DYTickColor";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "3DZTickColor";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));	
	m_aCommands[++i].name = "3DTickWidth";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));	
	m_aCommands[++i].name = "3DTickLength";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	
	/////////////////////////////////////
	// RANGE & PRECISION
		
	m_aCommands[++i].name = "3DXintervals";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));	
	m_aCommands[++i].name = "3DYintervals";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));	
	m_aCommands[++i].name = "3DXmin";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));	
	m_aCommands[++i].name = "3DXmax";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));	
	m_aCommands[++i].name = "3DYmin";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));	
	m_aCommands[++i].name = "3DYmax";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));

	/////////////////////////////////////
	// EQUATIONS	
	m_aCommands[++i].name = "3DGraphMode";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));

	m_aCommands[++i].name = "3DEq";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "3DEqWireMode";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "3DEqShadeMode";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "3DEqColorXmaxYmax";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "3DEqColorXmaxYmin";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "3DEqColorXminYmin";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "3DEqColorXminYmax";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "3DEqOn";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "3DEqAllOn";
	m_aCommands[i].params.Add(NewParam(PARAM_BOOL));
	m_aCommands[++i].name = "3DEqAllEmpty";

	/////////////////////////////////////
	// 3D MENU COMMANDS
	m_aCommands[++i].name = "3DRecomputeAll";
	m_aCommands[++i].name = "3DCopyGraph";
	m_aCommands[++i].name = "3DReCenterView";
	m_aCommands[++i].name = "3DSaveBitmap";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "3DExportDXF";
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[++i].name = "3DEvaluate";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER));
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));
	m_aCommands[i].params.Add(NewParam(PARAM_STRING));

	/////////////////////////////////////
	// 3D VIEW
	m_aCommands[++i].name = "3DZoomIn";
	m_aCommands[++i].name = "3DZoomOut";
	m_aCommands[++i].name = "3DRotateXIncrease";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER, false));
	m_aCommands[++i].name = "3DRotateYIncrease";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER, false));
	m_aCommands[++i].name = "3DRotateZIncrease";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER, false));
	m_aCommands[++i].name = "3DRotateXDecrease";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER, false));
	m_aCommands[++i].name = "3DRotateYDecrease";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER, false));
	m_aCommands[++i].name = "3DRotateZDecrease";
	m_aCommands[i].params.Add(NewParam(PARAM_NUMBER, false));

	/////////////////////////////////////
	// Auto rotating
	m_aCommands[++i].name = "3DAutoRotate";
	m_aCommands[++i].name = "3DAutoRotateX";
	m_aCommands[++i].name = "3DAutoRotateY";
	m_aCommands[++i].name = "3DAutoRotateZ";
	m_aCommands[++i].name = "3DAutoRotateIncreaseSpeed";
	m_aCommands[++i].name = "3DAutoRotateDecreaseSpeed";

	m_NumberCommands = i;

	ASSERT(MAX_NUMBER_COMMANDS>=m_NumberCommands);

	/*
	m_aCommands[++i].name = "";
	m_aCommands[i].params.Add(PARAM_STRING);	
	m_aCommands[++i].name = "";
	m_aCommands[i].params.Add(PARAM_NUMBER);	
	m_aCommands[++i].name = "";
	m_aCommands[i].params.Add(PARAM_BOOL);	
	*/

}


COLORREF CGCCommand::ColorLookupCOLORREF(CString color)
{
	color.MakeLower();
	
	if(color == "black")					return RGB(0x00, 0x00, 0x00);
    else if(color == "brown")				return RGB(0xA5, 0x2A, 0x00);
    else if(color == "dark olive green")	return RGB(0x00, 0x40, 0x40);
    else if(color == "dark green")			return RGB(0x00, 0x55, 0x00);
    else if(color == "dark teal")			return RGB(0x00, 0x00, 0x5E);
    else if(color == "dark blue")			return RGB(0x00, 0x00, 0x8B);
    else if(color == "indigo")				return RGB(0x4B, 0x00, 0x82);
    else if(color == "dark grey")			return RGB(0x28, 0x28, 0x28);

    else if(color == "dark red")			return RGB(0x8B, 0x00, 0x00);
    else if(color == "orange")				return RGB(0xFF, 0x68, 0x20);
    else if(color == "dark yellow")			return RGB(0x8B, 0x8B, 0x00);
    else if(color == "green")				return RGB(0x00, 0x93, 0x00);
    else if(color == "teal")				return RGB(0x38, 0x8E, 0x8E);
    else if(color == "blue")				return RGB(0x00, 0x00, 0xFF);
    else if(color == "blue-grey")			return RGB(0x7B, 0x7B, 0xC0);
    else if(color == "grey-40")				return RGB(0x66, 0x66, 0x66);

    else if(color == "red")					return RGB(0xFF, 0x00, 0x00);
    else if(color == "light orange")		return RGB(0xFF, 0xAD, 0x5B);
    else if(color == "lime")				return RGB(0x32, 0xCD, 0x32);
    else if(color == "sea green")			return RGB(0x3C, 0xB3, 0x71);
    else if(color == "aqua")				return RGB(0x7F, 0xFF, 0xD4);
    else if(color == "light blue")			return RGB(0x7D, 0x9E, 0xC0);
    else if(color == "violet")				return RGB(0x80, 0x00, 0x80);
    else if(color == "grey-50")				return RGB(0x7F, 0x7F, 0x7F);

    else if(color == "pink")				return RGB(0xFF, 0xC0, 0xCB);
    else if(color == "gold")				return RGB(0xFF, 0xD7, 0x00);
    else if(color == "yellow")				return RGB(0xFF, 0xFF, 0x00);
    else if(color == "bright green")		return RGB(0x00, 0xFF, 0x00);
    else if(color == "turquoise")			return RGB(0x40, 0xE0, 0xD0);
    else if(color == "skyblue")				return RGB(0xC0, 0xFF, 0xFF);
    else if(color == "plum")				return RGB(0x48, 0x00, 0x48);
    else if(color == "light grey")			return RGB(0xC0, 0xC0, 0xC0);

    else if(color == "rose")				return RGB(0xFF, 0xE4, 0xE1);
    else if(color == "tan")					return RGB(0xD2, 0xB4, 0x8C);
    else if(color == "light yellow")		return RGB(0xFF, 0xFF, 0xE0);
    else if(color == "pale green ")			return RGB(0x98, 0xFB, 0x98);
    else if(color == "pale turquoise")		return RGB(0xAF, 0xEE, 0xEE);
    else if(color == "pale blue")			return RGB(0x68, 0x83, 0x8B);
    else if(color == "lavender")			return RGB(0xE6, 0xE6, 0xFA);
    else if(color == "white")				return RGB(0xFF, 0xFF, 0xFF);

	return RGB(0,0,0);
}

#ifndef GRAPHCALC_LIGHT
ColorT CGCCommand::ColorLookupColorT(CString color)
{
	ColorT color_typed;
	
	CGrphCalcDlg* pDlg = (CGrphCalcDlg*)STATIC_DOWNCAST(CDialog, AfxGetMainWnd());

	color_typed.red = pDlg->m_3DGraphView->GetRed(ColorLookupCOLORREF(color));
	color_typed.green = pDlg->m_3DGraphView->GetGreen(ColorLookupCOLORREF(color));
	color_typed.blue = pDlg->m_3DGraphView->GetBlue(ColorLookupCOLORREF(color));

	return color_typed;
}
#endif

void CGCCommand::HandleError(HWND window)
{
	CString message;
	switch(m_eError){
	case UNKOWN_COMMAND:	message = "Unknown command"; break;
	case FORMAT_ERROR:		message = "Invalid command format"; break;
	case UNMATCHED_QUOTE:	message = "Unmatched quote"; break;
	case INVALID_NUMBER:	message = "Error parsing number"; break;
	case TOO_MANY_ARGS:		message = "Too many arguments to command"; break;
	case TOO_FEW_ARGS:		message = "Missing arguments to command"; break;
	case UNKNOWN_ARG_VAL:	message = "Unknown argument value"; break;
	case NOT_ON_3D:			message = "Not on 3D Graph. Command ignored"; break;
	case NOT_ON_2D:			message = "Not on 2D Graph. Command ignored"; break;
	}

	MessageBox(window, ("ERROR: " + message + "\nCOMMAND ENTERED: " + m_sCommandAndArgs),"Command Error", 
		MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
}

void CGCCommand::DispVal(long double val, CString msg /*value*/)
{
	CString strVal;

	g_Calculator->DecimalToStringSci(strVal, val);

	CGrphCalcDlg* pDlg = (CGrphCalcDlg*)STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	pDlg->MessageBox(msg + " = " +  strVal, "Script Message", MB_ICONINFORMATION | MB_OK);
}

void CGCCommand::PromptVal(CString var, CString msg /*Please enter a value*/)
{
	CPromptValDlg dlg;
	dlg.m_msg = msg;
	dlg.m_var = var;
	if(dlg.DoModal() == IDOK)
		{
		CGrphCalcDlg* pDlg = (CGrphCalcDlg*)STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
		pDlg->EvaluateFormula(var+"=("+dlg.m_strValue+")", false);
		}
	
}
