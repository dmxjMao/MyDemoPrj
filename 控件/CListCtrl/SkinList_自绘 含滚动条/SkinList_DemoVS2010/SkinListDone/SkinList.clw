; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SkinList.h"

ClassCount=8
Class1=CSkinListApp
Class2=CSkinListDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX (English (U.S.))
Resource2=IDR_MAINFRAME
Class5=CSkinScrollbar
Class4=CSkinListCtrl
Class6=CSkinHeaderCtrl
Resource3=IDD_ABOUTBOX
Resource4=IDD_SKINLIST_DIALOG (English (U.S.))
Class7=CSkinHorizontalScrollbar
Class8=CSkinVerticleScrollbar
Resource5=IDD_SKINLIST_DIALOG

[CLS:CSkinListApp]
Type=0
HeaderFile=SkinList.h
ImplementationFile=SkinList.cpp
Filter=N

[CLS:CSkinListDlg]
Type=0
HeaderFile=SkinListDlg.h
ImplementationFile=SkinListDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CSkinListDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=SkinListDlg.h
ImplementationFile=SkinListDlg.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SKINLIST_DIALOG]
Type=1
Class=CSkinListDlg
ControlCount=1
Control1=IDC_SKIN_LIST,SysListView32,1342242817

[CLS:CSkinListCtrl]
Type=0
HeaderFile=SkinListCtrl.h
ImplementationFile=SkinListCtrl.cpp
BaseClass=CListCtrl
Filter=W
VirtualFilter=FWC
LastObject=CSkinListCtrl

[CLS:CSkinScrollbar]
Type=0
HeaderFile=SkinScrollbar.h
ImplementationFile=SkinScrollbar.cpp
BaseClass=CStatic
Filter=W
LastObject=CSkinScrollbar
VirtualFilter=WC

[CLS:CSkinHeaderCtrl]
Type=0
HeaderFile=SkinHeaderCtrl.h
ImplementationFile=SkinHeaderCtrl.cpp
BaseClass=CHeaderCtrl
Filter=W
VirtualFilter=JWC
LastObject=CSkinHeaderCtrl

[DLG:IDD_SKINLIST_DIALOG (English (U.S.))]
Type=1
Class=CSkinListDlg
ControlCount=1
Control1=IDC_SKIN_LIST,SysListView32,1342242817

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CSkinHorizontalScrollbar]
Type=0
HeaderFile=SkinHorizontalScrollbar.h
ImplementationFile=SkinHorizontalScrollbar.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=CSkinHorizontalScrollbar

[CLS:CSkinVerticleScrollbar]
Type=0
HeaderFile=SkinVerticleScrollbar.h
ImplementationFile=SkinVerticleScrollbar.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=CSkinVerticleScrollbar

