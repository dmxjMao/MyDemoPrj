// MyCombo1.cpp : 实现文件
//

#include "stdafx.h"
#include "OwnDraw.h"
#include "MyCombo1.h"
#include "MyCommonDefine.h"

/*遗留问题：
1，根据item字符长度，响应OnDropDown，改变宽度
*/

IMPLEMENT_DYNAMIC(CMyCombo1, CComboBoxEx)

CMyCombo1::CMyCombo1()
{
	//try {
	//	m_regex.assign(
	//		"(?|"
	//		"(fontFaimly):(.*)"
	//		")"
	//		, boost::regex_constants::icase);
	//}
	//catch (boost::regex_error e) {
	//	//theApp.WriteLog
	//}
	//ui默认值
	//m_cfg["fontFaimly"] = "宋体";
}

CMyCombo1::~CMyCombo1()
{
}


BEGIN_MESSAGE_MAP(CMyCombo1, CComboBoxEx)
	ON_WM_PAINT()
	ON_CONTROL_REFLECT(CBN_EDITUPDATE, &CMyCombo1::OnEditUpdate)
END_MESSAGE_MAP()





void CMyCombo1::FillItem(const std::vector<CString>& vecItem)
{
	//设置字体
	Macro_SetFont; //放在OnCreate中最合理

	const int nCnt = vecItem.size() > 10 ? 10 : (int)vecItem.size();

	for (int i = 0; i < nCnt; ++i) {
		AddString(vecItem[i]); //会使用父类的字体
	}

	BOOL b = SetCueBanner(_T("用户名："));
	SetMinVisibleItems(10);//最少显示10个

	//SetCurSel(0);
}

void CMyCombo1::OnPaint()
{
	//BOOL b = SetCueBanner(_T("abc"));
	__super::OnPaint();
}


void CMyCombo1::PreSubclassWindow()
{
	ModifyStyle(CBS_SORT, CBS_AUTOHSCROLL | CBS_DROPDOWN | CBS_HASSTRINGS);
	//EnableWindowTheme(m_hWnd, L"ComboBox", L"Explorer", 0);

	__super::PreSubclassWindow();
}


BOOL CMyCombo1::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		m_bAutoComplete = TRUE;

		int nVirtKey = (int)pMsg->wParam;
		if (nVirtKey == VK_DELETE || nVirtKey == VK_BACK)
			m_bAutoComplete = FALSE;
	}

	return __super::PreTranslateMessage(pMsg);
}


void CMyCombo1::OnEditUpdate()
{
	if (!m_bAutoComplete)
		return;

	CString str;
	GetWindowText(str); //SelectString之后就不是你输入的长度了
	int nLength = str.GetLength();

	//LOWORD：第一个未选择的字符位置 HIWORD选择的结束位置
	DWORD dwCurSel = GetEditSel();
	WORD dStart = LOWORD(dwCurSel);
	WORD dEnd = HIWORD(dwCurSel);

	if (SelectString(-1, str) == CB_ERR) {
		SetWindowText(str);            // No text selected, so restore what 
									   // was there before
		//if (dwCurSel != CB_ERR)
		SetEditSel(dStart, dEnd);    //restore cursor postion
	}

	// Set the text selection as the additional text that we have added
	if (dEnd < nLength /*&& dwCurSel != CB_ERR*/)
		SetEditSel(dStart, dEnd);
	else
		SetEditSel(nLength, -1);
}

BOOL CMyCombo1::PreCreateWindow(CREATESTRUCT& cs)
{
	//Macro_SetFont;还没有dc

	return __super::PreCreateWindow(cs);
}
