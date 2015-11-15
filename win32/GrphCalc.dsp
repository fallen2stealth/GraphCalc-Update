# Microsoft Developer Studio Project File - Name="GrphCalc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GrphCalc - Win32 GraphCalc Light Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GrphCalc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GrphCalc.mak" CFG="GrphCalc - Win32 GraphCalc Light Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GrphCalc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GrphCalc - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "GrphCalc - Win32 GraphCalc Light Release" (based on "Win32 (x86) Application")
!MESSAGE "GrphCalc - Win32 GraphCalc Light Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/GraphCalc", BAAAAAAA"
# PROP Scc_LocalPath "Desktop"
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GrphCalc - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release\IntermediateFiles"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Release/Browse/GrphCalc.bsc"
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 htmlhelp.lib winmm.lib opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /pdb:none /machine:I386
# SUBTRACT LINK32 /verbose /debug /force

!ELSEIF  "$(CFG)" == "GrphCalc - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug\IntermediateFiles"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Fr"Browse/" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /WX
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Debug/Browse/GrphCalc.bsc"
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 htmlhelp.lib winmm.lib opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "GrphCalc - Win32 GraphCalc Light Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "GrphCalc___Win32_GraphCalc_Light_Release"
# PROP BASE Intermediate_Dir "GrphCalc___Win32_GraphCalc_Light_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseLight"
# PROP Intermediate_Dir "ReleaseLight\IntermediateFiles"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "GRAPHCALC_LIGHT" /Yu"stdafx.h" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /GX /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "GRAPHCALC_LIGHT" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "GRAPHCALC_LIGHT" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o"Release/Browse/GrphCalc.bsc"
# ADD BSC32 /nologo /o"ReleaseLight/Browse/GrphCalc.bsc"
LINK32=link.exe
# ADD BASE LINK32 htmlhelp.lib winmm.lib opengl32.lib glu32.lib glaux.lib gdi32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 htmlhelp.lib winmm.lib opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /pdb:none /machine:I386
# SUBTRACT LINK32 /debug
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Processesing post_build.bat
PostBuild_Cmds=c:\GraphCalc\Project\ReleaseLight\post_build.bat
# End Special Build Tool

!ELSEIF  "$(CFG)" == "GrphCalc - Win32 GraphCalc Light Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GrphCalc___Win32_GraphCalc_Light_Debug"
# PROP BASE Intermediate_Dir "GrphCalc___Win32_GraphCalc_Light_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugLight\IntermediateFiles"
# PROP Intermediate_Dir "DebugLight\IntermediateFiles"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "GRAPHCALC_LIGHT" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "GRAPHCALC_LIGHT" /D "_AFXDLL" /Fr"Browse/" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "GRAPHCALC_LIGHT" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o"Debug/Browse/GrphCalc.bsc"
# ADD BSC32 /nologo /o"DebugLight/Browse/GrphCalc.bsc"
LINK32=link.exe
# ADD BASE LINK32 htmlhelp.lib winmm.lib opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 htmlhelp.lib winmm.lib opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /debug /machine:I386 /out:"DebugLight/GrphCalc.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "GrphCalc - Win32 Release"
# Name "GrphCalc - Win32 Debug"
# Name "GrphCalc - Win32 GraphCalc Light Release"
# Name "GrphCalc - Win32 GraphCalc Light Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\2DCreateAnimationScriptDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\2DEqIntersectionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\2DEquationInterceptsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\2DEvaluateParametricDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\2DGraphParametric.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\2DMinMaxDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\2DNSliderDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\2DOptionsMode.cpp
# End Source File
# Begin Source File

SOURCE=.\2DOptionsParametricEqs.cpp
# End Source File
# Begin Source File

SOURCE=.\2DOptionsParametricRange.cpp
# End Source File
# Begin Source File

SOURCE=.\2DTableViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\3DGOAxes.cpp
# End Source File
# Begin Source File

SOURCE=.\3DGOEquations.cpp
# End Source File
# Begin Source File

SOURCE=.\3DGORangeAxisWire.cpp
# End Source File
# Begin Source File

SOURCE=.\3DGORenderMode.cpp
# End Source File
# Begin Source File

SOURCE=.\3DGOTickMarks.cpp
# End Source File
# Begin Source File

SOURCE=.\3DGraph.cpp
# End Source File
# Begin Source File

SOURCE=.\3DGraphEvaluateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\3DGraphOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\ButtonShade.cpp
# End Source File
# Begin Source File

SOURCE=.\CalculatorView.cpp
# End Source File
# Begin Source File

SOURCE=.\CatalogDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CCalculator.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\CGCCommand.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\CJComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientCapture.cpp
# End Source File
# Begin Source File

SOURCE=.\Color.cpp
# End Source File
# Begin Source File

SOURCE=.\ColourPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\ColourPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandData.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\CommandDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CPrintGraph.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\DistanceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EquationSolverDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EvaluateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FindAreaDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FlatEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\FlatEditEq.cpp
# End Source File
# Begin Source File

SOURCE=.\globals.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\GraphEuclidean.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\GraphOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphOptionsOne.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphOptionsPolar.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphOptionsTwo.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphOptionsZero.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphPolar.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\GraphTabNameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphView.cpp
# End Source File
# Begin Source File

SOURCE=.\GrphCalc.cpp
# End Source File
# Begin Source File

SOURCE=.\GrphCalc.rc
# End Source File
# Begin Source File

SOURCE=.\GrphCalcDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\Mode.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputView.cpp
# End Source File
# Begin Source File

SOURCE=.\Print.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PromptValDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SaveScriptDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsIO.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TangentDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Tfxdatatip.cpp
# End Source File
# Begin Source File

SOURCE=.\Wave.cpp

!IF  "$(CFG)" == "GrphCalc - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "GrphCalc - Win32 Debug"

# ADD CPP /ZI /D "NDEBUG" /Yu"stdafx.h"
# SUBTRACT CPP /O<none> /D "_DEBUG" /D "_MBCS"

!ELSEIF  "$(CFG)" == "GrphCalc - Win32 GraphCalc Light Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "GrphCalc - Win32 GraphCalc Light Debug"

# ADD BASE CPP /ZI /D "NDEBUG" /Yu"stdafx.h"
# SUBTRACT BASE CPP /O<none> /D "_DEBUG" /D "_MBCS"
# ADD CPP /ZI /D "NDEBUG" /Yu"stdafx.h"
# SUBTRACT CPP /O<none> /D "_DEBUG" /D "_MBCS"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\2DCreateAnimationScriptDlg.h
# End Source File
# Begin Source File

SOURCE=.\2DEqIntersectionDlg.h
# End Source File
# Begin Source File

SOURCE=.\2DEquationInterceptsDlg.h
# End Source File
# Begin Source File

SOURCE=.\2DEvaluateParametricDlg.h
# End Source File
# Begin Source File

SOURCE=.\2DGraphParametric.h
# End Source File
# Begin Source File

SOURCE=.\2DInfoBar.h
# End Source File
# Begin Source File

SOURCE=.\2DMinMaxDlg.h
# End Source File
# Begin Source File

SOURCE=.\2DNSliderDlg.h
# End Source File
# Begin Source File

SOURCE=.\2DOptionsMode.h
# End Source File
# Begin Source File

SOURCE=.\2DOptionsParametricEqs.h
# End Source File
# Begin Source File

SOURCE=.\2DOptionsParametricRange.h
# End Source File
# Begin Source File

SOURCE=.\2DTableViewDlg.h
# End Source File
# Begin Source File

SOURCE=.\3DGOAxes.h
# End Source File
# Begin Source File

SOURCE=.\3DGOEquations.h
# End Source File
# Begin Source File

SOURCE=.\3DGORangeAxisWire.h
# End Source File
# Begin Source File

SOURCE=.\3DGORenderMode.h
# End Source File
# Begin Source File

SOURCE=.\3DGOTickMarks.h
# End Source File
# Begin Source File

SOURCE=.\3DGraph.h
# End Source File
# Begin Source File

SOURCE=.\3DGraphEvaluateDlg.h
# End Source File
# Begin Source File

SOURCE=.\3DGraphOptions.h
# End Source File
# Begin Source File

SOURCE=.\3DMenus.h
# End Source File
# Begin Source File

SOURCE=.\Bitmap.h
# End Source File
# Begin Source File

SOURCE=.\Buttons.h
# End Source File
# Begin Source File

SOURCE=.\ButtonShade.h
# End Source File
# Begin Source File

SOURCE=.\CalculatorView.h
# End Source File
# Begin Source File

SOURCE=.\CatalogDlg.h
# End Source File
# Begin Source File

SOURCE=.\CCalculator.h
# End Source File
# Begin Source File

SOURCE=.\CGCCommand.h
# End Source File
# Begin Source File

SOURCE=.\CJComboBox.h
# End Source File
# Begin Source File

SOURCE=.\ClientCapture.h
# End Source File
# Begin Source File

SOURCE=.\Color.h
# End Source File
# Begin Source File

SOURCE=.\ColourPicker.h
# End Source File
# Begin Source File

SOURCE=.\ColourPopup.h
# End Source File
# Begin Source File

SOURCE=.\CommandData.h
# End Source File
# Begin Source File

SOURCE=.\CommandDlg.h
# End Source File
# Begin Source File

SOURCE=.\ContextMenus.h
# End Source File
# Begin Source File

SOURCE=.\CPrintGraph.h
# End Source File
# Begin Source File

SOURCE=.\DistanceDlg.h
# End Source File
# Begin Source File

SOURCE=.\DrawGraph.h
# End Source File
# Begin Source File

SOURCE=.\EquationSolverDlg.h
# End Source File
# Begin Source File

SOURCE=.\EvaluateDlg.h
# End Source File
# Begin Source File

SOURCE=.\FindAreaDlg.h
# End Source File
# Begin Source File

SOURCE=.\FlatEdit.h
# End Source File
# Begin Source File

SOURCE=.\FlatEditEq.h
# End Source File
# Begin Source File

SOURCE=.\GraphEuclidean.h
# End Source File
# Begin Source File

SOURCE=.\GraphOptions.h
# End Source File
# Begin Source File

SOURCE=.\GraphOptionsOne.h
# End Source File
# Begin Source File

SOURCE=.\GraphOptionsPolar.h
# End Source File
# Begin Source File

SOURCE=.\GraphOptionsTwo.h
# End Source File
# Begin Source File

SOURCE=.\GraphOptionsZero.h
# End Source File
# Begin Source File

SOURCE=.\GraphPolar.h
# End Source File
# Begin Source File

SOURCE=.\GraphTabNameDlg.h
# End Source File
# Begin Source File

SOURCE=.\GraphView.h
# End Source File
# Begin Source File

SOURCE=.\GrphCalc.h
# End Source File
# Begin Source File

SOURCE=.\GrphCalcDlg.h
# End Source File
# Begin Source File

SOURCE=.\GrphCalcInclude.h
# End Source File
# Begin Source File

SOURCE=.\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\Menus.h
# End Source File
# Begin Source File

SOURCE=.\MenuUpdates.h
# End Source File
# Begin Source File

SOURCE=.\Mode.h
# End Source File
# Begin Source File

SOURCE=.\Mouse.h
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\OutputView.h
# End Source File
# Begin Source File

SOURCE=.\Print.h
# End Source File
# Begin Source File

SOURCE=.\ProgDlg.h
# End Source File
# Begin Source File

SOURCE=.\PromptValDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "GrphCalc - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=GrphCalc
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GrphCalc - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=GrphCalc
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GrphCalc - Win32 GraphCalc Light Release"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=GrphCalc
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GrphCalc - Win32 GraphCalc Light Debug"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=GrphCalc
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SaveScriptDlg.h
# End Source File
# Begin Source File

SOURCE=.\SettingsIO.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Structs.h
# End Source File
# Begin Source File

SOURCE=.\TangentDlg.h
# End Source File
# Begin Source File

SOURCE=.\Tfxdatatip.h
# End Source File
# Begin Source File

SOURCE=.\Wave.h
# End Source File
# Begin Source File

SOURCE=.\Zoom.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\toolbars\2dgraph.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\bmp0d1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\copy.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cur00003.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00007.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor3.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor4.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor5.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor6.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor7.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor8.cur
# End Source File
# Begin Source File

SOURCE=.\res\cut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GrphCalc.rc2
# End Source File
# Begin Source File

SOURCE=.\GrphCalc.rgs
# End Source File
# Begin Source File

SOURCE=.\res\H_arrow.cur
# End Source File
# Begin Source File

SOURCE=.\res\H_move.cur
# End Source File
# Begin Source File

SOURCE=".\Buttons\Letters\Hex - A - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Letters\Hex - A - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Letters\Hex - B - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Letters\Hex - B - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Letters\Hex - C - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Letters\Hex - C - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Letters\Hex - D - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Letters\Hex - D - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Letters\Hex - E - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Letters\Hex - E - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Letters\Hex - F - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Letters\Hex - F - Up.bmp"
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D0.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D1.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D10.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D11.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D12.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D13.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D14.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D15.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D16.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D17.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D18.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D19.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D2.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D20.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D21.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D22.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D23.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D24.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D25.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D26.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D27.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D28.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D29.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D3.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D30.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D31.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D32.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D32_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D33.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D34.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D4.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D5.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D6.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D7.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D8.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_D9.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U0.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U1.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U10.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U11.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U12.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U13.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U14.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U15.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U16.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U17.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U18.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U19.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U2.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U20.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U21.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U22.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U23.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U24.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U25.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U26.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U27.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U28.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U29.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U3.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U30.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U31.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U32.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U32_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U33.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U34.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U4.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U5.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U6.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U7.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U8.bmp
# End Source File
# Begin Source File

SOURCE=.\Buttons\IDB_U9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\beta\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo.bmp
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - abs - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - abs - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - ceil - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - ceil - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - fib - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - fib - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - floor - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - floor - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - fPart - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - fPart - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - GCD - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - GCD - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - int - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - int - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - iPart - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - iPart - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - LCM - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - LCM - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - max - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - max - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - min - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - min - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - mod - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - mod - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - percentage - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - percentage - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - Round - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Math\Math - Round - Up.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\open.bmp
# End Source File
# Begin Source File

SOURCE=.\res\paste.bmp
# End Source File
# Begin Source File

SOURCE=".\Buttons\Prob\Prob - fRand - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Prob\Prob - fRand - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Prob\Prob - iRand - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Prob\Prob - iRand - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Prob\Prob - nCr - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Prob\Prob - nCr - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Prob\Prob - NFac - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Prob\Prob - NFac - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Prob\Prob - nPr - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Prob\Prob - nPr - Up.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\save.bmp
# End Source File
# Begin Source File

SOURCE=".\Buttons\Stats\Stats - mean - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Stats\Stats - mean - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Stats\Stats - median - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Stats\Stats - median - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Stats\Stats - mode - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Stats\Stats - mode - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Stats\Stats - stdev - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Stats\Stats - stdev - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Stats\Stats - var - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Stats\Stats - var - Up.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\tab_img.bmp
# End Source File
# Begin Source File

SOURCE=".\Buttons\Test\Test - EQ - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Test\Test - EQ - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Test\Test - GT - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Test\Test - GT - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Test\Test - GTE - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Test\Test - GTE - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Test\Test - LT - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Test\Test - LT - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Test\Test - LTE - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Test\Test - LTE - Up.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Test\Test - NE - Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\Buttons\Test\Test - NE - Up.bmp"
# End Source File
# Begin Source File

SOURCE=.\Buttons\toolbar1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\graphcalc.ini
# End Source File
# Begin Source File

SOURCE=.\Read.txt
# End Source File
# End Target
# End Project
# Section GrphCalc : {00692A14-0000-0000-0F00-0F0048080000}
# 	1:12:IDR_GRPHCALC:103
# End Section
