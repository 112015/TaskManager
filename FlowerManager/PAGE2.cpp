/*
PAGE2.cpp: “性能”页
作者：1120151769 侯思凡
*/
//——————————————————————————————————————————————————————————————————————————————————————<侯思凡>

#include "stdafx.h"
#include "FlowerManager.h"
#include "PAGE2.h"
#include "afxdialogex.h"


// PAGE2 对话框


IMPLEMENT_DYNAMIC(PAGE2, CDialogEx)

PAGE2::PAGE2(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE2, pParent)
{

}

PAGE2::~PAGE2()
{
}

void PAGE2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTPER, m_ListPer);
	DDX_Control(pDX, IDC_LISTPOWER, m_ListPower);
}


BEGIN_MESSAGE_MAP(PAGE2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONPER1, &PAGE2::OnBnClickedButtonper1)						//刷新
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTPER, &PAGE2::OnLvnColumnclickListper)			//排系统
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTPOWER, &PAGE2::OnLvnColumnclickListpower)		//排电源
END_MESSAGE_MAP()


// PAGE2 消息处理程序


BOOL PAGE2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	method1 = FALSE;
	method2 = FALSE;

	//系统信息
	m_ListPer.InsertColumn(0, "名称", NULL, 250, 50);
	m_ListPer.InsertColumn(1, "值", NULL, 250, 50);

	//电源信息
	m_ListPower.InsertColumn(0, "名称", NULL, 250, 50);
	m_ListPower.InsertColumn(1, "值", NULL, 280, 50);

	ListProc();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

/*获取系统和电池的性能信息*/
void PAGE2::ListProc() 
{

	//系统性能信息
	PERFORMANCE_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));
	pi.cb = sizeof(pi);
	GetPerformanceInfo(&pi, sizeof(pi));

	//用于规范字符形式
	TCHAR* sz = new TCHAR[MAX_PATH];

	StrFormatByteSize(pi.cb, sz, MAX_PATH);
	AddItem(0, "PERFORMANCE_INFORMATION大小", sz);

	//提交页面
	sprintf(sz, "%d 页", pi.CommitTotal);
	AddItem(0, "当前提交的页面总数", sz);
	sprintf(sz, "%d 页", pi.CommitLimit);
	AddItem(0, "当前可提交的最大页面数", sz);
	sprintf(sz, "%d 页", pi.CommitPeak);
	AddItem(0, "历史提交页面峰值", sz);

	//物理内存
	sprintf(sz, "%d 页", pi.PhysicalTotal);
	AddItem(0, "按页分配的总物理内存", sz);
	sprintf(sz, "%d 页", pi.PhysicalAvailable);
	AddItem(0, "当前可用的物理内存", sz);

	//Cache
	sprintf(sz, "%d 页", pi.SystemCache);
	AddItem(0, "Cache的容量", sz);

	//Kernel
	sprintf(sz, "%d 页", pi.KernelTotal);
	AddItem(0, "内存总量", sz);
	sprintf(sz, "%d 页", pi.KernelPaged);
	AddItem(0, "分页池大小", sz);
	sprintf(sz, "%d 页", pi.KernelNonpaged);
	AddItem(0, "非分页池大小", sz);

	//页的大小
	StrFormatByteSize(pi.PageSize, sz, MAX_PATH);
	AddItem(0, "页的大小", sz);

	//句柄
	sprintf(sz, "%d", pi.HandleCount);
	AddItem(0, "打开的句柄个数", sz);

	//进程
	sprintf(sz, "%d", pi.ProcessCount);
	AddItem(0, "进程个数", sz);

	//线程
	sprintf(sz, "%d", pi.ThreadCount);
	AddItem(0, "线程个数", sz);

	//电源性能信息
	//包含有关系统电源状态的信息
	SYSTEM_POWER_STATUS power;					
	ZeroMemory(&pi, sizeof(power));

	if (GetSystemPowerStatus(&power)) 
	{
		//交流电源状态
		switch (power.ACLineStatus) 
		{
		case 0:
			sprintf(sz, "离线");
			break;
		case 1:
			sprintf(sz, "线上");
			break;
		case 255:
			sprintf(sz, "未知状态");
			break;
		}
		AddItem(1, "交流电流源状态", sz);

		//电池充电状态
		switch (power.BatteryFlag) 
		{
		case 1:
			sprintf(sz, "高：容量大于66%");
			break;
		case 2:
			sprintf(sz, "低：容量少于33%");
			break;
		case 4:
			sprintf(sz, "亏电严重：容量少于5%");
			break;
		case 8:
			sprintf(sz, "充电中");
			break;
		case 125:
			sprintf(sz, "无系统电池");
			break;
		case 255:
			sprintf(sz, "未知状态：无法获取充电状态");
			break;
		}
		AddItem(1, "电池充电状态", sz);

		//剩余电量充足的百分比，该成员可以是0到100之间的一个值，或者是状态未知的值
		sprintf(sz, "%d%%", power.BatteryLifePercent);
		AddItem(1, "剩余电量百分比", sz);

		//剩余电池寿命的秒数，如果剩余秒数未知或设备连接到交流电源，则为-1
		if (power.BatteryLifeTime == -1)
			sprintf(sz, "剩余秒数未知/设备连接到交流电源");
		else
			sprintf(sz, "%d 秒", power.BatteryLifeTime);
		AddItem(1, "剩余电池寿命", sz);

		//完全充电时的电池寿命秒数，如果完整电池寿命未知或设备连接到交流电源，则为-1
		if (power.BatteryFullLifeTime = -1)
			sprintf(sz, "完整电池寿命未知/设备连接到交流电源");
		else
			sprintf(sz, "%d 秒", power.BatteryFullLifeTime);
		AddItem(1, "完全充电时的电池寿命", sz);
	}
	else 
	{
		GetLastError();
	}
}

/*向List中写入性能值*/
void PAGE2::AddItem(bool flag, TCHAR* name, TCHAR* value) 
{
	int nItemNum;
	switch (flag) 
	{
		//写系统性能
	case 0:
		nItemNum = m_ListPer.GetItemCount();
		m_ListPer.InsertItem(nItemNum, name);
		m_ListPer.SetItemText(nItemNum, 1, value);
		break;
		//写电池性能
	case 1:
		nItemNum = m_ListPower.GetItemCount();
		m_ListPower.InsertItem(nItemNum, name);
		m_ListPower.SetItemText(nItemNum, 1, value);
		break;
	}
}

//刷新
void PAGE2::OnBnClickedButtonper1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ListPer.DeleteAllItems();		//清空系统性能List内容
	m_ListPower.DeleteAllItems();	//清空电池性能List内容
	ListProc();						//重新写入内容
}

//比较函数，用于系统list根据某一列排序
int CALLBACK PAGE2::MyCompareProc1(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	UNREFERENCED_PARAMETER(lParamSort);
	// 从参数中提取所需比较lc的两行数据
	int row1 = (int)lParam1;
	int row2 = (int)lParam2;
	CListCtrl* lc = (CListCtrl*)lParamSort;
	CString lp1 = lc->GetItemText(row1, sort_column1);
	CString lp2 = lc->GetItemText(row2, sort_column1);

	//按照整数排序(有点不规范，因为未考虑单位，我就试试这功能)
	if (sort_column1 == 1)
	{
		if (method1)
			return atoi(lp1) - atoi(lp2);
		else
			return atoi(lp2) - atoi(lp1);
	}
	//否则按照字符串排序
	else
	{
		if (method1)
			return lp1.CompareNoCase(lp2);
		else
			return lp2.CompareNoCase(lp1);
	}
	return 0;
}

//比较函数，用于电源页list根据某一列排序
int CALLBACK PAGE2::MyCompareProc2(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	UNREFERENCED_PARAMETER(lParamSort);
	// 从参数中提取所需比较lc的两行数据
	int row1 = (int)lParam1;
	int row2 = (int)lParam2;
	CListCtrl* lc = (CListCtrl*)lParamSort;
	CString lp1 = lc->GetItemText(row1, sort_column2);
	CString lp2 = lc->GetItemText(row2, sort_column2);

	//按照字符串排序
	{
		if (method2)
			return lp1.CompareNoCase(lp2);
		else
			return lp2.CompareNoCase(lp1);
	}
	return 0;
}

//响应系统list排序
void PAGE2::OnLvnColumnclickListper(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码
	sort_column1 = pNMLV->iSubItem;				//点击的列索引
	int count = m_ListPer.GetItemCount();		//list的行数
	for (int i = 0; i < count; i++)
	{
		//每行的比较关键字，此处为列序号（点击的列号），比较函数的第一二个参数
		m_ListPer.SetItemData(i, i);
	}
	method1 = !method1;						//下一次点击改变排序顺序
	//对list排序
	m_ListPer.SortItems(
		MyCompareProc1,						//比较函数
		(LPARAM)&m_ListPer);				//比较函数的第三个参数

	*pResult = 0;
}

//响应电源性能list排序
void PAGE2::OnLvnColumnclickListpower(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码
	sort_column2 = pNMLV->iSubItem;				//点击的列
	int count = m_ListPower.GetItemCount();		//list的行数
	for (int i = 0; i < count; i++)
	{
		//每行的比较关键字，此处为列序号（点击的列号），比较函数的第一二个参数
		m_ListPower.SetItemData(i, i);
	}
	method2 = !method2;						//下一次点击改变排序顺序
	//对list排序
	m_ListPower.SortItems(
		MyCompareProc2,						//比较函数
		(LPARAM)&m_ListPower);				//比较函数的第三个参数

	*pResult = 0;
}
//——————————————————————————————————————————————————————————————————————————————————————</侯思凡>