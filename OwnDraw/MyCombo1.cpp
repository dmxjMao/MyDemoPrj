// MyCombo1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OwnDraw.h"
#include "MyCombo1.h"
#include "MyCommonDefine.h"

/*�������⣺
1������item�ַ����ȣ���ӦOnDropDown���ı���
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
	//uiĬ��ֵ
	//m_cfg["fontFaimly"] = "����";
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
	//��������
	Macro_SetFont; //����OnCreate�������

	const int nCnt = vecItem.size() > 10 ? 10 : (int)vecItem.size();

	for (int i = 0; i < nCnt; ++i) {
		AddString(vecItem[i]); //��ʹ�ø��������
	}

	BOOL b = SetCueBanner(_T("�û�����"));
	SetMinVisibleItems(10);//������ʾ10��

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
	GetWindowText(str); //SelectString֮��Ͳ���������ĳ�����
	int nLength = str.GetLength();

	//LOWORD����һ��δѡ����ַ�λ�� HIWORDѡ��Ľ���λ��
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
	//Macro_SetFont;��û��dc

	return __super::PreCreateWindow(cs);
}
