
/*********************************************************/
// CGrphCalcDlg::UpdateMenu(CMenu* pMenu)
// Pre: none
// Post: menu is updated
// Return Value: none
// Intent: to update the menu item(s)
//		   this function is needed to update menu items
//		   because it is not automatically done in dialog
//		   based apps
/*********************************************************/
void CGrphCalcDlg::UpdateMenu(CMenu* pMenu)
{
	CCmdUI cmdUI;
	for (UINT n = 0; n < pMenu->GetMenuItemCount(); ++n)
	{
	    CMenu* pSubMenu = pMenu->GetSubMenu(n);
	    if (pSubMenu == NULL)
	    {
			cmdUI.m_nIndexMax = pMenu->GetMenuItemCount();
			for (UINT i = 0; i < cmdUI.m_nIndexMax;++i)
			{
			    cmdUI.m_nIndex = i;
				cmdUI.m_nID = pMenu->GetMenuItemID(i);
				cmdUI.m_pMenu = pMenu;
				cmdUI.DoUpdate(this, FALSE);
			}
	    }
	}
}

void CGrphCalcDlg::OnUpdateFileLoadsettingsfile(CCmdUI* pCmdUI) 
{
	if(!m_OpenBmp.loaded){
		m_OpenBmp.loaded = true;
		//pCmdUI->m_pMenu->SetMenuItemBitmaps(ID_FILE_LOADSETTINGSFILE, MF_BYCOMMAND, &m_OpenBmp.bmp, &m_OpenBmp.bmp);
	}
}

void CGrphCalcDlg::OnUpdateFileOptionsSavesettingsnow(CCmdUI* pCmdUI) 
{
	if(!m_SaveBmp.loaded){
		m_SaveBmp.loaded = true;
		//pCmdUI->m_pMenu->SetMenuItemBitmaps(ID_FILE_OPTIONS_SAVESETTINGSNOW, MF_BYCOMMAND, &m_SaveBmp.bmp, &m_SaveBmp.bmp);
	}
}

void CGrphCalcDlg::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
#ifdef GRAPHCALC_LIGHT
	if(GetActiveGraphTabIndex() >= 0)
		{
		pCmdUI->Enable(false);
		return;
		}
#endif

	if(!m_CutBmp.loaded){
		m_CutBmp.loaded = true;
		pCmdUI->m_pMenu->SetMenuItemBitmaps(ID_EDIT_CUT, MF_BYCOMMAND, &m_CutBmp.bmp, &m_CutBmp.bmp);
	}
}

void CGrphCalcDlg::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	if(m_view.GetActivePage() == &m_OutputV)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);

	if(!m_CopyBmp.loaded){
		m_CopyBmp.loaded = true;
		pCmdUI->m_pMenu->SetMenuItemBitmaps(ID_EDIT_COPY, MF_BYCOMMAND, &m_CopyBmp.bmp, &m_CopyBmp.bmp);
	}
}

void CGrphCalcDlg::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_view.GetActivePage() == &m_OutputV)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);

	if(!m_PasteBmp.loaded){
		m_PasteBmp.loaded = true;
		pCmdUI->m_pMenu->SetMenuItemBitmaps(ID_EDIT_PASTE, MF_BYCOMMAND, &m_PasteBmp.bmp, &m_PasteBmp.bmp);
	}
}

/*********************************************************/
// CGrphCalcDlg::OnUpdateAltMenu(CCmdUI* pCmdUI)
// Pre: none
// Post: none
// Return Value: none
// Intent: updates menu items
/*********************************************************/
void CGrphCalcDlg::OnUpdateAltMenu(CCmdUI* pCmdUI)
{
	switch(pCmdUI->m_nID){
	case ID_PALETES_PROB: 
		if(m_CurrentPalete == PROB) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_PALETES_MATH:
		if(m_CurrentPalete == MATH) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_PALETES_TEST:
		if(m_CurrentPalete == TEST) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_PALETES_STATS:
		if(m_CurrentPalete == STATS) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_PALETES_LETTERS:
		if(m_CurrentPalete == LETTERS) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_PALETES_NONE:
		if(m_CurrentPalete == NONE) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	}
}

void CGrphCalcDlg::OnUpdate3DAutoRotate(CCmdUI* pCmdUI)
{
#ifndef GRAPHCALC_LIGHT
	switch(pCmdUI->m_nID){
	case ID_3DGRAPH_AUTOROTATE_ALLAXIS: 
		if(m_3DGraphView->IsAllAutoRotate())pCmdUI->SetCheck(true);
		else								pCmdUI->SetCheck(false);
		break;
	case ID_3DGRAPH_AUTOROTATE_XAXIS: 
		if(m_3DGraphView->IsXAutoRotate())	pCmdUI->SetCheck(true);
		else								pCmdUI->SetCheck(false);
		break;
	case ID_3DGRAPH_AUTOROTATE_YAXIS: 
		if(m_3DGraphView->IsYAutoRotate())	pCmdUI->SetCheck(true);
		else								pCmdUI->SetCheck(false);
		break;
	case ID_3DGRAPH_AUTOROTATE_ZAXIS: 
		if(m_3DGraphView->IsZAutoRotate())	pCmdUI->SetCheck(true);
		else								pCmdUI->SetCheck(false);
		break;
	}
#endif
}

/*********************************************************/
// CGrphCalcDlg::OnUpdateBaseMenu(CCmdUI* pCmdUI)
// Pre: none
// Post: none
// Return Value: none
// Intent: updates menu items
/*********************************************************/
void CGrphCalcDlg::OnUpdateBaseMenu(CCmdUI* pCmdUI)
{
	switch(pCmdUI->m_nID){
	case ID_BASE_2: 
		if(m_Calculator.m_base == 2) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_3: 
		if(m_Calculator.m_base == 3) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_4: 
		if(m_Calculator.m_base == 4) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_5: 
		if(m_Calculator.m_base == 5) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_6: 
		if(m_Calculator.m_base == 6) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_7: 
		if(m_Calculator.m_base == 7) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_8: 
		if(m_Calculator.m_base == 8) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_9: 
		if(m_Calculator.m_base == 9) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_10: 
		if(m_Calculator.m_base == 10) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_11: 
		if(m_Calculator.m_base == 11) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_12: 
		if(m_Calculator.m_base == 12) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_13: 
		if(m_Calculator.m_base == 13) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_14: 
		if(m_Calculator.m_base == 14) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_15: 
		if(m_Calculator.m_base == 15) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_16: 
		if(m_Calculator.m_base == 16) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_17: 
		if(m_Calculator.m_base == 17) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_18: 
		if(m_Calculator.m_base == 18) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_19: 
		if(m_Calculator.m_base == 19) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_20: 
		if(m_Calculator.m_base == 20) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_21: 
		if(m_Calculator.m_base == 21) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_22: 
		if(m_Calculator.m_base == 22) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_23: 
		if(m_Calculator.m_base == 23) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_24: 
		if(m_Calculator.m_base == 24) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_25: 
		if(m_Calculator.m_base == 25) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_26: 
		if(m_Calculator.m_base == 26) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_27: 
		if(m_Calculator.m_base == 27) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_28: 
		if(m_Calculator.m_base == 28) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_29: 
		if(m_Calculator.m_base == 29) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_30: 
		if(m_Calculator.m_base == 30) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_31: 
		if(m_Calculator.m_base == 31) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_32: 
		if(m_Calculator.m_base == 32) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_33: 
		if(m_Calculator.m_base == 33) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_34: 
		if(m_Calculator.m_base == 34) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_35: 
		if(m_Calculator.m_base == 35) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	case ID_BASE_36: 
		if(m_Calculator.m_base == 36) 
			pCmdUI->SetCheck(true);
		else
			pCmdUI->SetCheck(false);
		break;
	}
}
/*********************************************************/
// CGrphCalcDlg::OnUpdateFileOptionsTooltips(CCmdUI* pCmdUI)
// Pre: none
// Post: menu is updated
// Return Value: none
// Intent: to update the menu item(s)
/*********************************************************/
void CGrphCalcDlg::OnUpdateFileOptionsTooltips(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_ToolTips.IsOn());
}
/*********************************************************/
// CGrphCalcDlg::OnUpdateOptionsSoundEffects(CCmdUI* pCmdUI)
// Pre: none
// Post: menu is updated
// Return Value: none
// Intent: to update the menu item(s)
/*********************************************************/
void CGrphCalcDlg::OnUpdateOptionsSoundEffects(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_SndEffects);
}
/*********************************************************/
// CGrphCalcDlg::OnUpdateGraphFindarea(CCmdUI* pCmdUI) 
// Pre: none
// Post: menu is updated
// Return Value: none
// Intent: to update the menu item(s)
/*********************************************************/
void CGrphCalcDlg::OnUpdateGraphFindarea(CCmdUI* pCmdUI) 
{
	for(int i = 0; i < MAXTABS; ++i){
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			
			if(m_GraphViewList[i].m_Mode == POLAR || m_GraphViewList[i].m_Mode == PARAMETRIC)
				pCmdUI->Enable(false);
			else
				pCmdUI->Enable(true);
			
			pCmdUI->SetCheck(m_GraphViewList[i].m_FindArea);
			break;
		}
	}
}

void CGrphCalcDlg::OnUpdate2dgraphAnalysisIntercepts(CCmdUI* pCmdUI) 
{

#ifdef GRAPHCALC_LIGHT
	pCmdUI->Enable(false);
	return;
#endif

	int i = GetActiveGraphTabIndex();
	if(i >= 0)
	{
		if(m_GraphViewList[i].m_Mode == POLAR || m_GraphViewList[i].m_Mode == PARAMETRIC)
			pCmdUI->Enable(false);
		else
			pCmdUI->Enable(true);
	}
}

void CGrphCalcDlg::OnUpdate2dgraphAnalysisIntersectionof2equations(CCmdUI* pCmdUI) 
{

#ifdef GRAPHCALC_LIGHT
	pCmdUI->Enable(false);
	return;
#endif

	int i = GetActiveGraphTabIndex();
	if(i >= 0)
	{
		if(m_GraphViewList[i].m_Mode == POLAR || m_GraphViewList[i].m_Mode == PARAMETRIC)
			pCmdUI->Enable(false);
		else
			pCmdUI->Enable(true);
	}
}

void CGrphCalcDlg::OnUpdateAnalysisEqMinmax(CCmdUI* pCmdUI) 
{

#ifdef GRAPHCALC_LIGHT
	pCmdUI->Enable(false);
	return;
#endif

	int i = GetActiveGraphTabIndex();
	if(i >= 0)
	{
		if(m_GraphViewList[i].m_Mode == POLAR || m_GraphViewList[i].m_Mode == PARAMETRIC)
			pCmdUI->Enable(false);
		else
			pCmdUI->Enable(true);
	}
}

void CGrphCalcDlg::OnUpdate2dgraphAnalysisTable(CCmdUI* pCmdUI) 
{
#ifdef GRAPHCALC_LIGHT
	pCmdUI->Enable(false);
	return;
#endif

	int i = GetActiveGraphTabIndex();
	if(i >= 0)
	{
		if(m_GraphViewList[i].m_Mode == PARAMETRIC)
			pCmdUI->Enable(false);
		else
			pCmdUI->Enable(true);
	}

}

void CGrphCalcDlg::OnUpdateFileOptionsDisaplaydetailedoutput(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_OutputV.m_LongOutput);
}

/*********************************************************/
// CGrphCalcDlg::OnUpdateGraphGraphtrace(CCmdUI* pCmdUI) 
// Pre: none
// Post: menu is updated
// Return Value: none
// Intent: to update the menu item(s)
/*********************************************************/
void CGrphCalcDlg::OnUpdateGraphGraphtrace(CCmdUI* pCmdUI) 
{
	int i = GetActiveGraphTabIndex();
	if(i != -1)
		pCmdUI->SetCheck(m_GraphViewList[i].m_Trace);		
}

void CGrphCalcDlg::OnUpdateGraphDistance(CCmdUI* pCmdUI) 
{
	int i = GetActiveGraphTabIndex();
	if(i != -1){
		if(m_GraphViewList[i].IsDistanceOn())
			pCmdUI->SetCheck(1);
		else
			pCmdUI->SetCheck(0);
	}
}


void CGrphCalcDlg::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
#ifndef GRAPHCALC_LIGHT
	if(m_view.GetActivePage() == &m_OutputV){
		pCmdUI->Enable(true);
		pCmdUI->SetText("Print Output... \tCtrl+P");
	}
	else if(GetActiveGraphTabIndex() != -1){
		pCmdUI->Enable(true);
		pCmdUI->SetText("Print 2D Graph... \tCtrl+P");
	}
	else if(Is3DGraphActive()){
		pCmdUI->Enable(true);
		pCmdUI->SetText("Print 3D Graph... \tCtrl+P");
	}
	else
#endif
		pCmdUI->Enable(false);
}

void CGrphCalcDlg::OnUpdate2DGraphCopy(CCmdUI* pCmdUI) 
{
#ifdef GRAPHCALC_LIGHT
	pCmdUI->Enable(false);
#endif
}

void CGrphCalcDlg::OnUpdate2DGraphSaveAsBitmap(CCmdUI* pCmdUI) 
{
#ifdef GRAPHCALC_LIGHT
	pCmdUI->Enable(false);
#endif
}

void CGrphCalcDlg::OnUpdate2DGraphPrint(CCmdUI* pCmdUI) 
{
#ifdef GRAPHCALC_LIGHT
	pCmdUI->Enable(false);
#endif	
}

void CGrphCalcDlg::OnUpdateFileEquationsolver(CCmdUI* pCmdUI) 
{
#ifdef GRAPHCALC_LIGHT
	pCmdUI->Enable(false);
#endif	
}

void CGrphCalcDlg::OnUpdateFileRunscript(CCmdUI* pCmdUI) 
{
#ifdef GRAPHCALC_LIGHT
	pCmdUI->Enable(false);
#endif	
}

void CGrphCalcDlg::OnUpdateFileSavescript(CCmdUI* pCmdUI) 
{
#ifdef GRAPHCALC_LIGHT
	pCmdUI->Enable(false);
#endif	
}

/*********************************************************/
// CGrphCalcDlg::OnUpdateViewFullscreen(CCmdUI* pCmdUI) 
// Pre: none
// Post: menu is updated
// Return Value: none
// Intent: to update the menu item(s)
/*********************************************************/
void CGrphCalcDlg::OnUpdateViewFullscreen(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_FullScreen);

#ifndef GRAPH2D_INFOBAR
	pCmdUI->Enable(false);
#endif	
}

void CGrphCalcDlg::OnUpdateOptionsAlwaysontop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_AlwaysOnTop);
}

void CGrphCalcDlg::OnUpdateFileOptionsSavesettingsonexit(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_SaveSettings);	
}

void CGrphCalcDlg::OnUpdate2DGraphIInfobar(CCmdUI* pCmdUI) 
{
	int i = GetActiveGraphTabIndex();
	if(i >= 0)
	{
	#ifndef GRAPH2D_INFOBAR
		pCmdUI->Enable(false);
		pCmdUI->SetCheck(false);
	#else
		pCmdUI->SetCheck(m_GraphViewList[i].m_fInfoBar);
	#endif
	}
}



void CGrphCalcDlg::OnUpdate2DGraphToolbar(CCmdUI* pCmdUI) 
{
	int i = GetActiveGraphTabIndex();
	if(i >= 0)
		pCmdUI->SetCheck(m_GraphViewList[i].m_fToolbarOn);
}

void CGrphCalcDlg::OnUpdate2DGraphAnimationScript(CCmdUI* pCmdUI) 
{
	int i = GetActiveGraphTabIndex();
	if(i >= 0)
		{
			pCmdUI->Enable(m_GraphViewList[i].m_fNSliderOn);
		}
}


void CGrphCalcDlg::OnUpdate2DGraphNSlider(CCmdUI* pCmdUI) 
{
	int i = GetActiveGraphTabIndex();
	if(i >= 0)
		{
		#ifdef GRAPHCALC_LIGHT
			pCmdUI->Enable(false);
		#else	
			pCmdUI->SetCheck(m_GraphViewList[i].m_fNSliderOn);
		#endif
		}
}
