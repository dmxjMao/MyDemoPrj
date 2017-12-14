
// algorithm.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "algorithm.h"
#include "algorithmDlg.h"

#include <list>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CalgorithmApp

BEGIN_MESSAGE_MAP(CalgorithmApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


CalgorithmApp::CalgorithmApp()
{
}

CalgorithmApp theApp;

// CalgorithmApp 初始化
struct st {
	int a;
	st(int _a) : a(_a) {}
};
bool cmp(const st& t1, const st& t2) {
	return t1.a > t2.a;
}
struct cmp2 {
	bool operator()(const st& t1, const st& t2) {
		return t1.a > t2.a;
	}
};

BOOL CalgorithmApp::InitInstance()
{
	CWinApp::InitInstance();

	list<st> li = { st(1),st(2),st(3),st(4) };
	li.sort(cmp2());

	CalgorithmDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	UNUSED(nResponse);
	
	return FALSE;
}

