

/*�ʼ�*/
msdn ������Using Menus��

�û�����˵��IDΨһ,resource.h���������յ�WM_COMMAND��Ϣ��

����
1�����˵�������˵���
2�������˵����Ӳ˵�������ʽ�˵���

���в˵������Ӧ HMENU��

�˵�����
1����ʾ�����֡�ͼƬ
2��WM_COMMAND �� id
3��״̬�����á���Ч��ѡ�С�����


&��\t��\a�����Ҷ��룻

LoadMenu���ص��ڴ�
SetMenu���ò˵�

��Ϣ
WM_INITMENU wparam=HMENU ���˵�
WM_MENUSELECT ѡ��˵���ʱ������������LOWORD(wparam)���˵�id������HIWORD��wparam����MF_GRAYED��msdn
WM_INITMENUPOPUP wparam�������LOWORD��lparam��������HIWORD��lparam����ϵͳ�˵�Ϊ1��
WM_COMMAND wparam �˵�id
WM_SYSCOMMAND ͬWM_COMMAND�����������������lparam��Ч����windows������ƣ�P453������ϵͳ�˵���



OwnDrawDlg.cpp  OnInitDialog�������˵�


��̬�����˵���COwnDrawDlg::OnContextMenu
1���ȴ�����Դ
m_pMenuPop1->LoadMenu(IDM_Pop1);
m_pMenuPop1 = m_pMenuPop1->GetSubMenu(0);   //Ҫ������ȡ�˵����


ϵͳ�˵�
WS_SYSMENU
�˵�id����С��0xF000, ��������idʱҪ����Щϵͳ�ķ���DefWindowProc��
OwnDrawDlg.cpp OnInitDialog����ϵͳ�˵�
OnSysCommand


�Ի�˵�


����api
DrawMenuBar ǿ���ػ�˵�
GetMenuItemCount
GetMenuItemID
CheckMenuItem ��EnableMenuItem
GetMenuString��GetMenuState



