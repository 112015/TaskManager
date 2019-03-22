/*
PAGE3.cpp: “网络”页
作者：1120151769 侯思凡
*/
//——————————————————————————————————————————————————————————————————————————————————————<侯思凡>

#include "stdafx.h"
#include "FlowerManager.h"
#include "PAGE3.h"
#include "afxdialogex.h"


// PAGE3 对话框

IMPLEMENT_DYNAMIC(PAGE3, CDialogEx)

PAGE3::PAGE3(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE3, pParent)
{

}

PAGE3::~PAGE3()
{

}

void PAGE3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREENET, m_TreeNet);
	DDX_Control(pDX, IDC_LISTNET, m_ListNet);
}


BEGIN_MESSAGE_MAP(PAGE3, CDialogEx)
	ON_NOTIFY(TVN_GETINFOTIP, IDC_TREENET, &PAGE3::OnTvnGetInfoTipTreenet)			//鼠标滑过节点，提示其子节点数
	ON_BN_CLICKED(IDC_BUTTONNet, &PAGE3::OnBnClickedButtonnet)						//刷新页面
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREENET, &PAGE3::OnTvnSelchangedTreenet)			//提示您选中的节点
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTNET, &PAGE3::OnLvnColumnclickListnet)		//排序
END_MESSAGE_MAP()


// PAGE3 消息处理程序


BOOL PAGE3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	HTREEITEM hRoot;										//树的根
	hRoot = m_TreeNet.InsertItem(_T("整个网络"), 0, 0);		//根节点名

	LPNETRESOURCE Ipnr = NULL;								//网络资源

	//List写上各属性名称
	//m_ListNet.InsertColumn(0, "编号", NULL, 50, 50);		//没多大意义，我不用了
	m_ListNet.InsertColumn(0, "远程网络名称", NULL, 150, 50);
	m_ListNet.InsertColumn(1, "资源类型", NULL, 100, 50);
	m_ListNet.InsertColumn(2, "网络浏览用户界面中网络对象的显示选项", NULL, 180, 50);
	m_ListNet.InsertColumn(3, "如何使用的一组位标志", NULL, 80, 50);
	m_ListNet.InsertColumn(4, "本地设备名称", NULL, 150, 50);
	m_ListNet.InsertColumn(5, "枚举范围", NULL, 150, 50);
	m_ListNet.InsertColumn(6, "评论", NULL, 100, 50);
	m_ListNet.InsertColumn(7, "提供者", NULL, 100, 50);

	//递归整个网络
	TreeProc(hRoot, Ipnr, 1);

	//展开第一层节点——好看一点儿，哈哈哈
	m_TreeNet.Expand(hRoot, TVE_EXPAND);					

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void PAGE3::TreeProc(HTREEITEM hRoot, LPNETRESOURCE lpnr, int depth) 
{
	DWORD dwResult, dwResultEnum;
	HANDLE hEnum;
	DWORD cbBuffer = 16384;			// 16K 是个合适的大小
	DWORD cEntries = -1;			// 枚举所有可能的条目
	LPNETRESOURCE lpnrLocal;		// 指向枚举的结构体
	DWORD i;
	HTREEITEM hsubRoot;				//新节点也可能是他儿子的“根”哦

	//调用WNetOpenEnum函数来开始枚举
	dwResult = WNetOpenEnum(
		RESOURCE_GLOBALNET,			// 所有的网络资源
		RESOURCETYPE_ANY,			// 所有的资源
		0,							// 枚举所有资源
		lpnr,						// 第一次用NULL
		&hEnum);					// 资源的句柄

	//严谨吗，我跟微软学的
	if (dwResult != NO_ERROR)
	{
		return;
	}

	// 调用GlobalAlloc函数来分配资源
	lpnrLocal = (LPNETRESOURCE)GlobalAlloc(GPTR, cbBuffer);
	if (lpnrLocal == NULL) 
	{
		// NetErrorHandler(hwnd, dwResult, (LPSTR)"WNetOpenEnum");
		//MessageBox("资源分配失败！");
		return;
	}

	//这是一个枚举的循环
	do {
		// 初始化缓冲区
		ZeroMemory(lpnrLocal, cbBuffer);

		// 调用WNetEnumResource函数来继续枚举
		dwResultEnum = WNetEnumResource(
			hEnum,				// 资源的句柄
			&cEntries,			// -1
			lpnrLocal,			// LPNETRESOURCE
			&cbBuffer);			// 缓冲区大小

		// 如果调用成功，循环
		if (dwResultEnum == NO_ERROR) 
		{
			m_TreeNet.SetItemData(hRoot, cEntries);						//给节点写入他有几个儿子，一切以服务用户为重：软工老师说用户是傻子
			for (i = 0; i < cEntries; i++) 
			{
				// 给咱们的树增孙添子
				hsubRoot = IntsertNode(hRoot, &lpnrLocal[i], depth);

				//List同步插入一条资源记录
				DisplayStruct(i, &lpnrLocal[i]);

				// 如果NETRESOURCE结构体代表一个容器，递归地调用此函数：因为他有儿子呀
				if (RESOURCEUSAGE_CONTAINER == (lpnrLocal[i].dwUsage& RESOURCEUSAGE_CONTAINER)) 
				{
					//更深一层递归啊
					TreeProc(hsubRoot, &lpnrLocal[i], ++depth);
					depth--;		//回到这一层
				}
			}//for——我是不是贼机智，这样就能看出这个大括号是谁的了
		}//if
		 // 错误
		else if (dwResultEnum != ERROR_NO_MORE_ITEMS) 
		{
			//      NetErrorHandler(hwnd, dwResultEnum, (LPSTR)"WNetEnumResource");
			break;
		}
	} while (dwResultEnum != ERROR_NO_MORE_ITEMS);

	// 调用GlobalFree函数释放内存
	GlobalFree((HGLOBAL)lpnrLocal);

	// 调用WNetCloseEnum函数结束枚举
	dwResult = WNetCloseEnum(hEnum);

	if (dwResult != NO_ERROR) 
	{
		// 错误
		//    NetErrorHandler(hwnd, dwResult, (LPSTR)"WNetCloseEnum");
		return;
	}
}

/*向树中插入一个节点，返回新的节点哦，可能他将来也是个爸爸*/
HTREEITEM PAGE3::IntsertNode(HTREEITEM hRoot, LPNETRESOURCE lpnrLocal, int depth)
{
	HTREEITEM hSubRoot;
	hSubRoot= m_TreeNet.InsertItem(lpnrLocal->lpRemoteName, depth, depth, hRoot);
	return hSubRoot;
}

/*用于将网络的详细信息写入List中呈现给用户*/
void PAGE3::DisplayStruct(int i, LPNETRESOURCE lpnrLocal) 
{
	//各变量的声明
	TCHAR* Num = new TCHAR[MAX_PATH];
	TCHAR* Scope = new TCHAR[MAX_PATH];
	TCHAR* Type = new TCHAR[MAX_PATH];
	TCHAR* DisplayType = new TCHAR[MAX_PATH];
	TCHAR* Usage = new TCHAR[MAX_PATH];
	TCHAR* Localname = new TCHAR[MAX_PATH];
	TCHAR* Remotename = new TCHAR[MAX_PATH];
	TCHAR* Comment = new TCHAR[MAX_PATH];
	TCHAR* Provider = new TCHAR[MAX_PATH];

	//编号
	sprintf(Num, "%d", i);

	//枚举范围
	switch (lpnrLocal->dwScope)
	{
	case(RESOURCE_CONNECTED):
		sprintf(Scope, "枚举当前连接的资源");
		break;
	case(RESOURCE_GLOBALNET):
		sprintf(Scope, "枚举网络上的所有资源");
		break;
	case(RESOURCE_REMEMBERED):
		sprintf(Scope, "枚举记忆（永久）连接");
		break;
	default:
		sprintf(Scope, "未知 %d", lpnrLocal->dwScope);
		break;
	}

	//资源类型
	switch (lpnrLocal->dwType) 
	{
	case(RESOURCETYPE_ANY):
		sprintf(Type, "所有资源");
		break;
	case(RESOURCETYPE_DISK):
		sprintf(Type, "磁盘资源");
	case(RESOURCETYPE_PRINT):
		sprintf(Type, "打印资源");
		break;
	default:
		sprintf(Type, "未知 %d", lpnrLocal->dwType);
		break;
	}

	//网络浏览用户界面中网络对象的显示选项
	switch (lpnrLocal->dwDisplayType) 
	{
	case (RESOURCEDISPLAYTYPE_GENERIC):
		sprintf(DisplayType, "用于显示对象的方法并不重要");
		break;
	case (RESOURCEDISPLAYTYPE_DOMAIN):
		sprintf(DisplayType, "该对象应显示为一个域");
		break;
	case (RESOURCEDISPLAYTYPE_SERVER):
		sprintf(DisplayType, "该对象应显示为服务器");
		break;
	case (RESOURCEDISPLAYTYPE_SHARE):
		sprintf(DisplayType, "该对象应显示为共享");
		break;
	case (RESOURCEDISPLAYTYPE_FILE):
		sprintf(DisplayType, "该对象应该显示为一个文件");
		break;
	case (RESOURCEDISPLAYTYPE_GROUP):
		sprintf(DisplayType, "该对象应该作为一个组显示");
		break;
	case (RESOURCEDISPLAYTYPE_NETWORK):
		sprintf(DisplayType, "该对象应显示为网络");
		break;
	case(RESOURCEDISPLAYTYPE_ROOT):
		sprintf(DisplayType, "该对象应该显示为整个网络的逻辑根");
		break;
	case(RESOURCEDISPLAYTYPE_SHAREADMIN):
		sprintf(DisplayType, "该对象应显示为管理共享");
		break;
	case(RESOURCEDISPLAYTYPE_DIRECTORY):
		sprintf(DisplayType, "该对象应显示为一个目录");
		break;
	case(RESOURCEDISPLAYTYPE_TREE):
		sprintf(DisplayType, "该对象应该显示为一棵树");
		break;
	case(RESOURCEDISPLAYTYPE_NDSCONTAINER):
		sprintf(DisplayType, "该对象应显示为Netware目录服务容器");
		break;
	default:
		sprintf(DisplayType, "未知 %d", lpnrLocal->dwDisplayType);
		break;
	}

	//描述资源如何使用的一组位标志
	switch (lpnrLocal->dwUsage)
	{
	case(RESOURCEUSAGE_CONNECTABLE):
		sprintf(Usage, "可连接的资源");
		break;
	case(RESOURCEUSAGE_CONTAINER):
		sprintf(Usage, "容器资源");
		break;
	case(RESOURCEUSAGE_NOLOCALDEVICE):
		sprintf(Usage, "非本地设备");
		break;
	case(RESOURCEUSAGE_SIBLING):
		sprintf(Usage, "兄弟姐妹");//windows不使用这个值
		break;
	case(RESOURCEUSAGE_ATTACHED):
		sprintf(Usage, "必须连接");
		break;
	default:
		sprintf(Usage, "未知 %d", lpnrLocal->dwUsage);
		break;
	}
	//这是一段被抛弃的代码，此代码由微软官网提供，但作者查询到微软对dwUsage的更全面的解释，故使用上面的代码
	//if (lpnrLocal->dwUsage & RESOURCEUSAGE_CONNECTABLE) {
	//	sprintf(Usage, "0x%x = connectable",lpnrLocal->dwUsage);
	//}
	//else {
	//	sprintf(Usage, "0x%x = container", lpnrLocal->dwUsage);
	//}

	//本地设备名称
	/*如果dwScope成员等于RESOURCE_CONNECTED或RESOURCE_REMEMBERED，
	则此成员是指向指定本地设备名称的空终止字符串的指针。
	如果连接不使用设备，则该成员为NULL。*/
	sprintf(Localname, "%s", lpnrLocal->lpLocalName);

	//远程设备名称
	/*如果条目是网络资源，则该成员是指向指定远程网络名称的空终止字符串的指针。
	如果项是当前或永久连接，lpRemoteName成员指向与名称相关的网络名称指向的lpLocalName成员。
	该字符串的长度可以是MAX_PATH个字符，并且必须遵循网络提供者的命名约定。*/
	sprintf(Remotename, "%s", lpnrLocal->lpRemoteName);

	//指向包含由网络提供者提供的注释的NULL终止字符串的指针。
	sprintf(Comment, "%s", lpnrLocal->lpComment);

	//提供者
	/*指向包含拥有资源的提供程序名称的NULL终止字符串的指针。如果提供者名称未知，此成员可以为NULL*/
	sprintf(Provider, "%s", lpnrLocal->lpProvider);

	//填入一条记录
	AddItem(Num, Remotename, Type, DisplayType, Usage, Localname, Scope, Comment, Provider);
}

/*向List中添加一条资源的记录*/
void PAGE3::AddItem(TCHAR* num, TCHAR* remotename, TCHAR* type, TCHAR* displaytype, TCHAR* usage, TCHAR* localname, TCHAR* scope, TCHAR* comment, TCHAR* provider)
{
	int nItemNum;
	nItemNum = m_ListNet.GetItemCount();
	//名字我就不写了，在上面的函数里写清楚了的
	m_ListNet.InsertItem(nItemNum, remotename);
	m_ListNet.SetItemText(nItemNum, 1, type);
	m_ListNet.SetItemText(nItemNum, 2, displaytype);
	m_ListNet.SetItemText(nItemNum, 3, usage);
	m_ListNet.SetItemText(nItemNum, 4, localname);
	m_ListNet.SetItemText(nItemNum, 5, scope);
	m_ListNet.SetItemText(nItemNum, 6, comment);
	m_ListNet.SetItemText(nItemNum, 7, provider);
	//m_ListNet.SetItemText(nItemNum, 8, provider);
}

/*鼠标划过根节点外的某个树节点时，提示节点的子节点有几个——我是不是贼体贴*/
void PAGE3::OnTvnGetInfoTipTreenet(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVGETINFOTIP pGetInfoTip = reinterpret_cast<LPNMTVGETINFOTIP>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	NMTVGETINFOTIP* pTVTipInfo = (NMTVGETINFOTIP*)pNMHDR;   // 将传入的pNMHDR转换为NMTVGETINFOTIP指针类型   
	HTREEITEM hRoot = m_TreeNet.GetRootItem();				// 获取树的根节点   
	CString strText;										// 每个树节点的提示信息   

	if (pTVTipInfo->hItem == hRoot) {
		// 如果鼠标划过的节点是根节点，则提示信息为。。。还是不用特殊化了，提示吧
		//strText = _T("");
		strText.Format(_T("%d"), pTVTipInfo->lParam);
	}
	else {
		// 如果鼠标划过的节点不是根节点，则将该节点的附加32位数据格式化为字符串,是不是和上面一样，哈白白加了四行代码
		strText.Format(_T("%d"), pTVTipInfo->lParam);
	}

	// 将strText字符串拷贝到pTVTipInfo结构体变量的pszText成员中，这样就能显示内容为strText的提示信息   
	strcpy(pTVTipInfo->pszText, strText);
	*pResult = 0;
}

/*提示选中的节点——我说了我很体贴的*/
void PAGE3::OnTvnSelchangedTreenet(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CString strText; // 树节点的标签文本字符串   

	// 获取当前选中节点的句柄   
	HTREEITEM hItem = m_TreeNet.GetSelectedItem();

	// 获取选中节点的标签文本字符串   
	strText = m_TreeNet.GetItemText(hItem);

	// 将字符串显示到编辑框中   
	SetDlgItemText(IDC_EDITNET, strText);
}

/*刷新按钮*/
void PAGE3::OnBnClickedButtonnet()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TreeNet.DeleteAllItems();							//清空树当前所有节点
	HTREEITEM hRoot;									//重新声明一个根
	hRoot = m_TreeNet.InsertItem(_T("整个网络"), 0, 0);//这是祖宗呗

	LPNETRESOURCE Ipnr = NULL;

	m_ListNet.DeleteAllItems();

	TreeProc(hRoot, Ipnr, 1);

	//展开我的根~~~
	m_TreeNet.Expand(hRoot, TVE_EXPAND);
}

//比较函数，用于list根据某一列排序——抱歉我实在忍不住排序
int CALLBACK PAGE3::MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	UNREFERENCED_PARAMETER(lParamSort);
	// 从参数中提取所需比较lc的两行数据
	int row1 = (int)lParam1;
	int row2 = (int)lParam2;
	CListCtrl* lc = (CListCtrl*)lParamSort;
	CString lp1 = lc->GetItemText(row1, sort_column);
	CString lp2 = lc->GetItemText(row2, sort_column);

	//按照整数排序
	//if (sort_column == 0)
	//{
	//	if (method)
	//		return atoi(lp1) - atoi(lp2);
	//	else
	//		return atoi(lp2) - atoi(lp1);
	//}
	//按照字符串排序
	//else
	{
		if (method)
			return lp1.CompareNoCase(lp2);
		else
			return lp2.CompareNoCase(lp1);
	}
	return 0;
}


void PAGE3::OnLvnColumnclickListnet(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	sort_column = pNMLV->iSubItem;	//点击的列
	int count = m_ListNet.GetItemCount();	//list的行数
	for (int i = 0; i < count; i++)
	{
		//每行的比较关键字，此处为列序号（点击的列号），比较函数的第一二个参数
		m_ListNet.SetItemData(i, i);
	}
	method = !method;		//下一次点击改变排序顺序
							//对list排序
	m_ListNet.SortItems(
		MyCompareProc,			//比较函数
		(LPARAM)&m_ListNet);	//比较函数的第三个参数
	*pResult = 0;
}
//——————————————————————————————————————————————————————————————————————————————————————</侯思凡>