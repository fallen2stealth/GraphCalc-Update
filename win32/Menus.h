void CGrphCalcDlg::OnOptionsProgramoptions() 
{
	COptionsDlg ops;

	ops.m_bDetailedOutput = m_OutputV.m_LongOutput;
	ops.m_bSaveExprHistory = m_bSaveExprHistory;
	ops.m_bSaveOutputHistory = m_bSaveOutputHistory;
	ops.m_bSaveSettings = m_SaveSettings;
	ops.m_bSoundEffects = m_SndEffects;
	ops.m_bStartupScript = m_bStartupScript;
	ops.m_bTooltips = m_ToolTips.IsOn();
	ops.m_sScriptFile = m_sScriptFile;
	ops.m_sSettingsFile = m_SettingsFile;
	ops.m_bCommandErrors = m_bShowCommandErrors;
	ops.m_bDispScriptProgressDlg = m_fShowScriptProgressDlg;
	
	if(ops.DoModal() == IDOK){
		m_OutputV.m_LongOutput = (ops.m_bDetailedOutput == 1);
		m_bSaveExprHistory = (ops.m_bSaveExprHistory == 1);
		m_bSaveOutputHistory = (ops.m_bSaveOutputHistory == 1);
		m_SaveSettings = (ops.m_bSaveSettings == 1);
		m_SndEffects = (ops.m_bSoundEffects == 1);
		m_bStartupScript = (ops.m_bStartupScript == 1);
		m_ToolTips.On((ops.m_bTooltips == 1));
		m_sScriptFile = ops.m_sScriptFile;
		m_SettingsFile = ops.m_sSettingsFile;
		m_bShowCommandErrors = (ops.m_bCommandErrors == 1);
		m_fShowScriptProgressDlg = (ops.m_bDispScriptProgressDlg == 1);
	}
}

void CGrphCalcDlg::OnFileSaveScript() 
{
	CSaveScriptDlg sdlg;	
	sdlg.m_pFormulaCtrl = &m_FormulaCtrl;
	sdlg.DoModal();
}

/*********************************************************/
// CGrphCalcDlg::OnContextMenu(CWnd* pWnd, CPoint point)
// Pre: none none
// Post: none none
// Return Value: none none
// Intent: to handle menu call to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if(m_FullScreen)
		return;

	int i, j;

	ScreenToClient(&point);

	if(ButtonDetect(point, i, j))
		OnContextMenuSubmit(i, j, point);
}

////////////////////////////////////////////////////////////////
//////////// FILE MENU ///////////
//////////////////////////////////

/*********************************************************/
// CGrphCalcDlg::OnOptionsMode()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnOptionsMode() 
{
	m_FormulaCtrl.SetFocus();

	Mode ModeOptionsDlg;

	ModeOptionsDlg.m_TrigUnits 	= m_Calculator.m_trig_state;
	ModeOptionsDlg.m_DecPlaces 	= m_Calculator.m_DecimalPlaces;
	ModeOptionsDlg.m_Float 		= m_Calculator.m_Float;
	ModeOptionsDlg.m_OutputMode  = m_Calculator.m_Normal;
	ModeOptionsDlg.m_IntlMode 	= m_Calculator.m_IntlMode;
	ModeOptionsDlg.m_Base 		= m_Calculator.m_base;
	ModeOptionsDlg.m_DecimalSeperatorAmount 	= m_Calculator.m_DecimalSeperatorAmount - 1;
	ModeOptionsDlg.m_DecimalSeperator 			= m_Calculator.m_DecimalSeperator;
	ModeOptionsDlg.m_DecimalSpaceSeperator.Format("%c", m_Calculator.m_DecimalSpaceSeperator);
	ModeOptionsDlg.m_NumberSeperatorAmount 		= m_Calculator.m_NumberSeperatorAmount - 1;
	ModeOptionsDlg.m_NumberSeperator 			= m_Calculator.m_NumberSeperator;
	ModeOptionsDlg.m_NumberSpaceSeperator.Format("%c", m_Calculator.m_NumberSpaceSeperator);

	if(ModeOptionsDlg.DoModal() == IDOK){
		m_Calculator.m_trig_state 	= (TrigE)ModeOptionsDlg.m_TrigUnits;
		m_Calculator.m_base 		= ModeOptionsDlg.m_Base;
		m_Calculator.m_DecimalPlaces  = ModeOptionsDlg.m_DecPlaces;
		m_Calculator.m_Float 		= (ModeOptionsDlg.m_Float == 1);
		m_Calculator.m_Normal 		= (ModeOptionsDlg.m_OutputMode == 1);
		m_Calculator.m_IntlMode 	= (InternationalModeE)ModeOptionsDlg.m_IntlMode;
		
		m_Calculator.m_DecimalSeperatorAmount = ModeOptionsDlg.m_DecimalSeperatorAmount + 1;
		m_Calculator.m_DecimalSeperator 	= (ModeOptionsDlg.m_DecimalSeperator == 1);
		m_Calculator.m_DecimalSpaceSeperator  = ModeOptionsDlg.m_DecimalSpaceSeperator[0];
		m_Calculator.m_NumberSeperatorAmount = ModeOptionsDlg.m_NumberSeperatorAmount + 1;
		m_Calculator.m_NumberSeperator 	    = (ModeOptionsDlg.m_NumberSeperator == 1);
		m_Calculator.m_NumberSpaceSeperator  = ModeOptionsDlg.m_NumberSpaceSeperator[0];
		
		m_Buttons[2][6].up.DeleteObject();
		m_Buttons[2][6].down.DeleteObject();

		if(m_Calculator.m_IntlMode == US){
			m_Buttons[2][6].up.LoadBitmap(IDB_32U);
			m_Buttons[2][6].down.LoadBitmap(IDB_32D);
		}
		else if(m_Calculator.m_IntlMode == EUROPEAN){
			m_Buttons[2][6].up.LoadBitmap(IDB_32U_2);
			m_Buttons[2][6].down.LoadBitmap(IDB_32D_2);
		}

		Invalidate();
		
		for(int i = 0; i < MAXTABS; ++i){
			if(m_view.GetActivePage() == &m_GraphViewList[i]){
				m_GraphViewList[i].m_Redraw = true;
				m_GraphViewList[i].Invalidate();
				return;
			}
		}
		
#ifndef GRAPHCALC_LIGHT
		m_3DGraphView->ReCompute();
#endif
	}
}

/*********************************************************/
// CGrphCalcDlg::OnFileCatalog()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnFileCatalog() 
{
	CCatalogDlg dlg;	
    
	m_FormulaCtrl.SetFocus();
	
	int pos_start, pos_end;
	DWORD span = m_FormulaCtrl.GetEditSel();
	pos_start = span & 0xFF;
	pos_end = (span>>16);
    
	if(IDOK == dlg.DoModal()){
		m_FormulaCtrl.SetEditSel(pos_end, pos_end);
		FormulaInsertion(dlg.m_Operator);
	}
}



void CGrphCalcDlg::OnInsertCommand() 
{
	CCommandDlg dlg;

	m_FormulaCtrl.SetFocus();
	
	int pos_start, pos_end;
	DWORD span = m_FormulaCtrl.GetEditSel();
	pos_start = span & 0xFF;
	pos_end = (span>>16);

	if(IDOK == dlg.DoModal()){
		m_FormulaCtrl.SetEditSel(pos_end, pos_end);
		FormulaInsertion("[" + dlg.m_sCommand + "]");
	}
}


void CGrphCalcDlg::OnFileOptionsSavesettingsnow() 
{
	WriteSettings(m_SettingsFile);	
}

void CGrphCalcDlg::OnFileOptionsSavesettingsonexit() 
{
	if(m_SaveSettings)
		m_SaveSettings = false;
	else
		m_SaveSettings = true;
}

void CGrphCalcDlg::OnFileOptionsDisaplaydetailedoutput() 
{
	if(m_OutputV.m_LongOutput)
		m_OutputV.m_LongOutput = false;
	else
		m_OutputV.m_LongOutput = true;
}



/*********************************************************/
// CGrphCalcDlg::OnOptionsSoundEffects()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnOptionsSoundEffects() 
{
	if(m_SndEffects)
		m_SndEffects = false;
	else
		m_SndEffects = true;
}

/*********************************************************/
// CGrphCalcDlg::OnFileOptionsTooltips()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnFileOptionsTooltips() 
{
	if(m_ToolTips.IsOn())
		m_ToolTips.On(false);
	else
		m_ToolTips.On(true);
}
/*********************************************************/
// CGrphCalcDlg::OnFileOptionsAnswer()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnFileOptionsAnswer() 
{
	CFontDialog *fontDlg = new CFontDialog(&m_OutputV.m_LFAnswerFont, CF_BOTH | CF_EFFECTS | CF_FORCEFONTEXIST | CF_SCALABLEONLY | CF_SCREENFONTS, NULL, this);
	fontDlg->m_cf.rgbColors = m_OutputV.m_AnswerFont.crTextColor;
	fontDlg->m_cf.iPointSize = m_OutputV.m_LFAnswerFont.lfHeight;
	if(fontDlg->DoModal() == IDOK){
		fontDlg->GetCurrentFont(&m_OutputV.m_LFAnswerFont);
		fontDlg->GetCharFormat(m_OutputV.m_AnswerFont);
		m_fSaveFont = true;
	}
	delete fontDlg;
}
void CGrphCalcDlg::OnFileOptionsExpression() 
{
	CFontDialog *fontDlg = new CFontDialog(&m_OutputV.m_LFExpressionFont, CF_BOTH | CF_EFFECTS | CF_FORCEFONTEXIST | CF_SCALABLEONLY | CF_SCREENFONTS, NULL, this);
	fontDlg->m_cf.rgbColors = m_OutputV.m_ExpressionFont.crTextColor;
	fontDlg->m_cf.iPointSize = m_OutputV.m_LFExpressionFont.lfHeight;
	if(fontDlg->DoModal() == IDOK){
		fontDlg->GetCurrentFont(&m_OutputV.m_LFExpressionFont);
		fontDlg->GetCharFormat(m_OutputV.m_ExpressionFont);
		m_fSaveFont = true;
	}
	delete fontDlg;
}

void CGrphCalcDlg::OnOptionsOutputfontsettingsDetailedoutput() 
{
	CFontDialog *fontDlg = new CFontDialog(&m_OutputV.m_LFLongOutputFont, CF_BOTH | CF_EFFECTS | CF_FORCEFONTEXIST | CF_SCALABLEONLY | CF_SCREENFONTS, NULL, this);
	fontDlg->m_cf.rgbColors = m_OutputV.m_LongOutputFont.crTextColor;
	fontDlg->m_cf.iPointSize = m_OutputV.m_LFLongOutputFont.lfHeight;
	if(fontDlg->DoModal() == IDOK){
		fontDlg->GetCurrentFont(&m_OutputV.m_LFLongOutputFont);
		fontDlg->GetCharFormat(m_OutputV.m_LongOutputFont);
		m_fSaveFont = true;
	}
	delete fontDlg;
}

void CGrphCalcDlg::OnOptionsOutputfontsettingsBase() 
{
	CFontDialog *fontDlg = new CFontDialog(&m_OutputV.m_LFBaseFont, CF_BOTH | CF_EFFECTS | CF_FORCEFONTEXIST | CF_SCALABLEONLY | CF_SCREENFONTS, NULL, this);
	fontDlg->m_cf.rgbColors = m_OutputV.m_BaseFont.crTextColor;
	fontDlg->m_cf.iPointSize = m_OutputV.m_LFBaseFont.lfHeight;
	if(fontDlg->DoModal() == IDOK){
		fontDlg->GetCurrentFont(&m_OutputV.m_LFBaseFont);
		fontDlg->GetCharFormat(m_OutputV.m_BaseFont);
		m_OutputV.m_BaseFont.yOffset = -40;
		m_OutputV.m_BaseFont.dwMask |= CFM_OFFSET;
		m_fSaveFont = true;
	}
	delete fontDlg;
}
////////////////////////////////////////////////////////////////
//////////// EDIT MENU ///////////
//////////////////////////////////
/*********************************************************/
// CGrphCalcDlg::OnEditCopy() 
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnEditCopy() 
{ 
	int i;
	if((i=GetActiveGraphTabIndex()) != -1){
		m_GraphViewList[i].OnCopyGraph();
		return;
	}

#ifndef GRAPHCALC_LIGHT
	if(Is3DGraphActive()){
		m_3DGraphView->CopyGraph();
		return;
	}
#endif

	int pos_start, pos_end;
	DWORD span = m_FormulaCtrl.GetEditSel();
	pos_start = span & 0xFF;
	pos_end = (span & 0xFFFF0000)>>10;
	
	if(pos_start == pos_end)
		{
		m_OutputV.m_Result.Copy();
		return;
		}
	else
		{
		m_FormulaCtrl.Copy();
		}

	
}
/*********************************************************/
// CGrphCalcDlg::OnEditCut() 
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnEditCut() { m_FormulaCtrl.Cut(); }
/*********************************************************/
// CGrphCalcDlg::OnEditPaste()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnEditPaste() { m_FormulaCtrl.Paste(); }

////////////////////////////////////////////////////////////////
//////////// GRAPH MENU /////////
//////////////////////////////////
/*********************************************************/
// CGrphCalcDlg::OnGraphAddGraphTab()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnGraphAddGraphTab() 
{
	// search for free graph
	for(int i = 0; i < MAXTABS; ++i)
		if(!m_ActiveGraphView[i]){
			break;
		}

	if(i == MAXTABS){
		MessageBox("You have reached your maximum of 4 graph tabs","Maximum Number of Graphs", MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
		return;
	}
	AddGraphTab(i);
}
void CGrphCalcDlg::AddGraphTab(int i)
{
	if(m_ActiveGraphView[i])
		return;

	m_ActiveGraphView[i] = true;
	m_view.AddPage(&m_GraphViewList[i]);

	if(m_TotalGraphViews != 0){
		m_GraphViewList[i].m_graph_width = m_view.m_PageRect.right - m_view.m_PageRect.left - (2*h_space);
		m_GraphViewList[i].m_graph_height = m_view.m_PageRect.bottom - m_view.m_PageRect.top - (2*v_space);
	}

	++m_TotalGraphViews;

	if(m_view.initialzed){
		// update pics on tabs
		CTabCtrl* pTab = m_view.GetTabControl();
		TC_ITEM tcItem;
		tcItem.mask = TCIF_IMAGE;
		tcItem.iImage = 1;
		pTab->SetItem(m_view.GetPageIndex(&m_GraphViewList[i]) , &tcItem );

		CString tempS;
		tempS.Format("Graph %d", i+1);
		tcItem.mask = TCIF_TEXT;
		tcItem.pszText = tempS.GetBuffer(0);
		pTab->SetItem(m_view.GetPageIndex(&m_GraphViewList[i]) , &tcItem );
	}
}

/*********************************************************/
// CGrphCalcDlg::OnGraphRemovegraphtab()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnGraphRemovegraphtab() 
{
	if(Is3DGraphActive() || m_view.GetActivePage() == &m_OutputV)
		return;

	if(m_TotalGraphViews == 1){
		MessageBox("You must have at least 1 graph tab","No Graph Tabs", MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
		return;
	}
	
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_ActiveGraphView[i] = false;
			break;
		}

	// clear graph equations
	for(int j = 0; j < 10; ++j){
		m_GraphViewList[i].m_Equations[j].eq = "";
		m_GraphViewList[i].m_astrEquationsRaw[i] = "";
		m_GraphViewList[i].m_Equations[j].disp = false;
	}

	--m_TotalGraphViews;
	m_view.RemovePage(&m_GraphViewList[i]);
}
/*********************************************************/
// CGrphCalcDlg::OnGraphGraphtrace()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnGraphGraphtrace() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			if(m_Trace){
				m_Trace = false;
			}
			else{
				m_Trace = true;
			}			

			m_GraphViewList[i].OnMenuGraphTrace();
			break;
		}
}

/*********************************************************/
// CGrphCalcDlg::OnGraphZoomInX()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnGraphZoomInX() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnGraphZoomInX();
			break;
		}
}

void CGrphCalcDlg::OnGraphDistance() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnGraphDistance();
			break;
		}
}

/*********************************************************/
// CGrphCalcDlg::OnGraphZoomInY()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnGraphZoomInY() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnGraphZoomInY();
			break;
		}
}
/*********************************************************/
// CGrphCalcDlg::OnGraphZoomDecimal()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnGraphZoomDecimal() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnGraphZoomDecimal();
			break;
		}
}
/*********************************************************/
// CGrphCalcDlg::OnGraphZoomStandard()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnGraphZoomStandard() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnGraphZoomStandard();
			break;
		}
}
/*********************************************************/
// CGrphCalcDlg::OnGraphZoomTrig() 
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnGraphZoomTrig() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnGraphZoomTrig();
			break;
		}
}
/*********************************************************/
// CGrphCalcDlg::OnGraphZoomOutX()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnGraphZoomOutX() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnGraphZoomOutX();
			break;
		}
}
/*********************************************************/
// CGrphCalcDlg::OnGraphZoomOutY()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnGraphZoomOutY() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnGraphZoomOutY();
			break;
		}
}
/*********************************************************/
// CGrphCalcDlg::OnGraphZoomInteger() 
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnGraphZoomInteger() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnGraphZoomInteger();
			break;
		}
}
/*********************************************************/
// CGrphCalcDlg::OnGraphZoomFit()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnGraphZoomFit() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnGraphZoomFit();
			break;
		}
}
/*********************************************************/
// CGrphCalcDlg::OnGraphFindArea() 
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnGraphFindArea() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnGraphFindArea();
			break;
		}
}

void CGrphCalcDlg::OnGraphEvaluate() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnGraphEvaluate();
			break;
		}
}
/*********************************************************/
// CGrphCalcDlg::OnGraphZoomPreviousRange() 
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnGraphZoomPreviousRange() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnGraphZoomPreviousRange();
			break;
		}
	
}

/*********************************************************/
// CGrphCalcDlg::OnGraphRenametab()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnGraphRenametab() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i])
			break;

	if(i == MAXTABS)
		return;

	CGraphTabNameDlg name_dlg;

	if(name_dlg.DoModal() == IDOK){
		CTabCtrl* pTab = m_view.GetTabControl();
		TC_ITEM tcItem;
		tcItem.mask = TCIF_TEXT;
		tcItem.pszText = name_dlg.m_Name.GetBuffer(0);
		pTab->SetItem(m_view.GetPageIndex(&m_GraphViewList[i]) , &tcItem );
	}
}
/*********************************************************/
// CGrphCalcDlg::OnViewFullscreen() 
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnViewFullscreen() 
{
	if(m_FullScreen){
		m_FormulaCtrl.ShowWindow(SW_SHOW);
		m_FullScreen = false;
	}
	else{
		m_FormulaCtrl.ShowWindow(SW_HIDE);
		m_FullScreen = true;
	}

	CRect client_r;
	GetClientRect(&client_r);
	ResizeTabs(CSize(client_r.right, client_r.bottom));
}

/*********************************************************/
// CGrphCalcDlg::OnSetFullWindow() 
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnSetFullWindow(WPARAM wParam, LPARAM lParam) 
{
	if(!wParam){
		m_FormulaCtrl.ShowWindow(SW_SHOW);
		m_FullScreen = false;
	}
	else{
		m_FormulaCtrl.ShowWindow(SW_HIDE);
		m_FullScreen = true;
	}

	CRect client_r;
	GetClientRect(&client_r);
	ResizeTabs(CSize(client_r.right, client_r.bottom));
}


/*********************************************************/
// CGrphCalcDlg::OnOptionsGraph()
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnOptionsGraph(UINT id) 
{
	int i = GetActiveGraphTabIndex();
	if(i != -1){		
		switch(id){
		case ID_GRAPH_EQUATIONS:
			m_GraphViewList[i].Options(1);
			break;
		case ID_GRAPH_RANGEPRECISION:
			m_GraphViewList[i].Options(2);
			break;
		case ID_GRAPH_DISPLAY:
			m_GraphViewList[i].Options(3);
			break;
		default:
			m_GraphViewList[i].Options(0);
			break;
		}
		m_view.SetActivePage(&m_GraphViewList[i]);
		m_GraphViewList[i].SetFocus();
	}
}

void CGrphCalcDlg::OnCtrlG() 
{
	int i = GetActiveGraphTabIndex();
	if(i != -1){	
		m_GraphViewList[i].Options(0);
		m_view.SetActivePage(&m_GraphViewList[i]);
		m_GraphViewList[i].SetFocus();
	}
#ifndef GRAPHCALC_LIGHT
	if(Is3DGraphActive())
		m_3DGraphView->Options(0);
#endif
}

/*********************************************************/
// CGrphCalcDlg::OnGraphZoomInXY() 
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnGraphZoomInXY() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnGraphZoomInXY();
			break;
		}
}
/*********************************************************/
// CGrphCalcDlg::OnGraphZoomOutXY() 
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle menu call
/*********************************************************/
void CGrphCalcDlg::OnGraphZoomOutXY() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnGraphZoomOutXY();
			break;
		}
}

void CGrphCalcDlg::OnGraphTangentline() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnTangentLine();
			break;
		}
}

void CGrphCalcDlg::OnGraphCopygraph() 
{
	if(GetActiveGraphTabIndex() != -1)
		m_GraphViewList[GetActiveGraphTabIndex()].OnCopyGraph();
#ifndef GRAPHCALC_LIGHT
	if(Is3DGraphActive())
		m_3DGraphView->CopyGraph();
#endif
		
}

void CGrphCalcDlg::OnFilePrint() 
{
	if(m_view.GetActivePage() == &m_OutputV)
		m_OutputV.Print();
	else if(GetActiveGraphTabIndex() != -1)
		OnGraphPrint();
	else if(Is3DGraphActive())
		On3DCommand(ID_3DGRAPH_PRINT);
	
}

void CGrphCalcDlg::OnGraphPrint() 
{
	for(int i = 0; i < MAXTABS; ++i){
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnGraphPrint();
			break;
		}
	}
}


void CGrphCalcDlg::OnGraphCleartangentlines() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].OnClearTangentLines();
			break;
		}
}

void CGrphCalcDlg::OnGraphSaveAsBitmap() 
{
	int i = GetActiveGraphTabIndex();
	if(i != -1){	
		m_GraphViewList[i].OnSaveAsBitmap();
		m_view.SetActivePage(&m_GraphViewList[i]);
		m_GraphViewList[i].SetFocus();
	}	
}

void CGrphCalcDlg::OnFileEquationSolver() 
{
	CEquationSolverDlg dlg;
	dlg.DoModal();
}

void CGrphCalcDlg::OnAnalysisEqMinmax() 
{
	int i = GetActiveGraphTabIndex();
	if(i != -1){	
		m_GraphViewList[i].OnCalculateMinMax();
	}
}

void CGrphCalcDlg::On2DGraphAnalysisTable() 
{
	int i = GetActiveGraphTabIndex();
	if(i != -1){	
		m_GraphViewList[i].OnAnalysisTable();
	}
}

void CGrphCalcDlg::On2DGraphAnalysisNslider() 
{
	int i = GetActiveGraphTabIndex();
	if(i != -1){	
		m_GraphViewList[i].OnAnalysisNslider();
	}
}

void CGrphCalcDlg::On2DGraphAnalysisIntersectionof2equations() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].On2DGraphAnalysisIntersectionof2equations();
			break;
		}
}

void CGrphCalcDlg::On2DGraphAnalysisIntercepts() 
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].On2DGraphAnalysisIntercepts();
			break;
		}
}

void CGrphCalcDlg::OnFileSaveOutput() 
{
	static char BASED_CODE szFilter[] = "Rich Text File(*.rtf)|*.rtf||";	

	CFileDialog *fileDlg = new CFileDialog(false, 
										   "rtf",
										    NULL,
											OFN_ENABLESIZING 
											| OFN_CREATEPROMPT
											| OFN_HIDEREADONLY 
											| OFN_OVERWRITEPROMPT,
											szFilter,
											this);

	if(fileDlg->DoModal() == IDOK)
		m_OutputV.SaveOutputToFile(fileDlg->GetPathName());

	delete fileDlg;	
}

void CGrphCalcDlg::On2DGraphInfobar() 
{
	int i = GetActiveGraphTabIndex();
	if(i != -1){	
		m_GraphViewList[i].SetRedraw(false);
		m_GraphViewList[i].ShowInfoBar(!m_GraphViewList[i].m_fInfoBar);
		m_GraphViewList[i].SetRedraw(true);

		
		if(m_GraphViewList[i].m_fInfoBar)
			{
			m_GraphViewList[i].m_graph_width -= BUTTON_PALLETE_WIDTH;
			m_GraphViewList[i].RePaintNow();

			CRect client;
			m_GraphViewList[i].GetClientRect(client);	
			m_GraphViewList[i].InvalidateRect(CRect(client.right-BUTTON_PALLETE_WIDTH, 0, client.right, client.bottom), true);
			}
		else
			{
			m_GraphViewList[i].m_graph_width += BUTTON_PALLETE_WIDTH;
			m_GraphViewList[i].RePaintNow();
			}
		
	}
}

void CGrphCalcDlg::On2DGraphToolbar() 
{
	int i = GetActiveGraphTabIndex();
	if(i != -1)
		m_GraphViewList[i].OnToolbar();
}

void CGrphCalcDlg::On2DGraphAnimationScript() 
{
	int i = GetActiveGraphTabIndex();
	if(i != -1)
		m_GraphViewList[i].OnCreateAnimationScript();
}

