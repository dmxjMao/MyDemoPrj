

/*笔记*/
msdn 搜索“Using Menus”

用户点击菜单项（ID唯一,resource.h），程序收到WM_COMMAND消息；

分类
1，主菜单（顶层菜单）
2，下拉菜单（子菜单、弹出式菜单）

都有菜单句柄对应 HMENU；

菜单属性
1）显示：文字、图片
2）WM_COMMAND ： id
3）状态：禁用、无效、选中。。。


&、\t、\a文字右对齐；

LoadMenu加载到内存
SetMenu设置菜单

消息
WM_INITMENU wparam=HMENU 主菜单
WM_MENUSELECT 选择菜单项时，文字描述，LOWORD(wparam)：菜单id或句柄，HIWORD（wparam）：MF_GRAYED，msdn
WM_INITMENUPOPUP wparam：句柄，LOWORD（lparam）索引，HIWORD（lparam）：系统菜单为1；
WM_COMMAND wparam 菜单id
WM_SYSCOMMAND 同WM_COMMAND，如果有鼠标产生，则lparam有效，《windows程序设计，P453，加入系统菜单》



OwnDrawDlg.cpp  OnInitDialog设置主菜单


动态创建菜单：COwnDrawDlg::OnContextMenu
1，先创建资源
m_pMenuPop1->LoadMenu(IDM_Pop1);
m_pMenuPop1 = m_pMenuPop1->GetSubMenu(0);   //要这样获取菜单句柄


系统菜单
WS_SYSMENU
菜单id必须小于0xF000, 处理新增id时要把那些系统的发给DefWindowProc；
OwnDrawDlg.cpp OnInitDialog设置系统菜单
OnSysCommand


自绘菜单


其他api
DrawMenuBar 强制重绘菜单
GetMenuItemCount
GetMenuItemID
CheckMenuItem 、EnableMenuItem
GetMenuString、GetMenuState



