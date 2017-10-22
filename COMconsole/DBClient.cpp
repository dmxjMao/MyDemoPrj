//#include "stdafx.h"
//#include <iostream>
//
//#include "..\interface\DBSRV.H"
//
//
//using namespace std;
//
//
//int main()
//{
//	HRESULT hRes = CoInitialize(0);
//
//	IUnknown *m_pDB; // pointer to database object
//	IClassFactory *pDBFactory = NULL;
//
//	hRes = CoGetClassObject(CLSID_DBSAMPLE, CLSCTX_SERVER, NULL, IID_IClassFactory, (void**)&pDBFactory);
//	if (FAILED(hRes)) {
//		CString csError;
//		csError.Format(_T("Error %x obtaining class factory for DB Object!"), hRes);
//		AfxMessageBox(csError);
//		return FALSE;
//	}
//
//	hRes = pDBFactory->CreateInstance(NULL, IID_IUnknown, (void**)&m_pDB);
//	if (FAILED(hRes)) {
//		CString csError;
//		csError.Format(_T("Error %x creating DB Object!"), hRes);
//		AfxMessageBox(csError);
//		return FALSE;
//	}
//
//	pDBFactory->Release(); // do not need the factory anymore
//
//
//
//	CString m_csData; // last data read from database
//	int m_nCount;			// number of writes to database
//	short m_nTable;		// number of last table created
//
//	// 初始化数据成员变量
//	m_csData = "No data yet!";
//	m_nCount = 0;
//	m_nTable = -1;
//
//
//	CoUninitialize();
//
//	return 0;
//}