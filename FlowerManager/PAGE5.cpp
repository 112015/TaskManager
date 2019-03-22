/*
PAGE5.cpp: “文件清理”页
作者：1120151764 陈牧乔
	 1120151775 罗薇
*/
//——————————————————————————————————————————————————————————————————————————————————————<陈牧乔>
#include "stdafx.h"
#include "FlowerManager.h"
#include "PAGE5.h"
#include "afxdialogex.h"
#include "ChooseExtension.h"
#include <regex>  
#include <string>  
#include <vector>  
#include <iostream>  

int sort_column_p5; // 记录点击的列
bool method_p5 = false; // 记录比较方法

const int BUFSIZE = 4096;

//要匹配文件类型的正则表达式
char* reg[33] = {
	".*\\.syd", ".*\\.~.*", "~.*\\..*", ".*\\.---", ".*\\.\\^.*",
	".*\\.\\?\\?~",  ".*\\.\\?\\?\\$", ".*\\.tmp", ".*\\._mp", ".*\\.spc",
	".*\\.cdr_", ".*\\.#Res", ".*\\.%%%", ".*\\.@@@", ".*\\.\\$\\$\\$",
	"mscreate\\.dir", ".*\\.chk", "chklist\\..*", ".*\\.gid", ".*\\.fts",
	".*\\.ftg", ".*\\.ms", ".*\\.old", ".*\\.bak", ".*\\.prv",
	".*\\.wpk", ".*\\.xlk", ".*\\.pch", ".*\\.dmp", ".*\\.diz",
	"Thumbs\\.db", ".*\\.err", ".*log\\.txt"
};
//——————————————————————————————————————————————————————————————————————————————————————</陈牧乔>
//——————————————————————————————————————————————————————————————————————————————————————<罗薇>
struct ext
{
	string name;
	string description;
	BOOL state;
};
ext extend[33];
//——————————————————————————————————————————————————————————————————————————————————————</罗薇>
//——————————————————————————————————————————————————————————————————————————————————————<陈牧乔>
// PAGE5 对话框

IMPLEMENT_DYNAMIC(PAGE5, CDialogEx)

PAGE5::PAGE5(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE5, pParent)
{

}

PAGE5::~PAGE5()
{
}

void PAGE5::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILEROUTE, m_edit_fileroute);
	DDX_Control(pDX, IDC_LIST_PAGE5, m_list_page5);
//——————————————————————————————————————————————————————————————————————————————————————</陈牧乔>
//——————————————————————————————————————————————————————————————————————————————————————<罗薇>
	DDX_Control(pDX, IDC_EDIT_FILETYPE, m_edit_filetype);
}
//——————————————————————————————————————————————————————————————————————————————————————</罗薇>
//——————————————————————————————————————————————————————————————————————————————————————<陈牧乔>
BEGIN_MESSAGE_MAP(PAGE5, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FILEROUTE, &PAGE5::OnBnClickedButtonFileroute)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &PAGE5::OnBnClickedButtonSearch)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_PAGE5, &PAGE5::OnLvnColumnclickListPage5)
//——————————————————————————————————————————————————————————————————————————————————————</陈牧乔>
//——————————————————————————————————————————————————————————————————————————————————————<罗薇>
	ON_BN_CLICKED(IDC_BUTTON_FILETYPE, &PAGE5::OnBnClickedButtonFiletype)
	ON_BN_CLICKED(IDC_CHECK_CHOOSEALL_PAGE5, &PAGE5::OnBnClickedCheckChooseallPage5)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &PAGE5::OnBnClickedButtonClean)
END_MESSAGE_MAP()
//——————————————————————————————————————————————————————————————————————————————————————</罗薇>

// PAGE5 消息处理程序
//——————————————————————————————————————————————————————————————————————————————————————<陈牧乔>
//通过CFolderPickerDialog获得文件路径
void PAGE5::OnBnClickedButtonFileroute()
{
	// TODO: 在此添加控件通知处理程序代码
	CFolderPickerDialog fd(
		NULL,	//初始文件夹
		0,		//允许您自定义对话框中的一个或多个标志的组合
		this,	//指向对话框对象的父窗口或所有者窗口的指针
		0);		//OPENFILENAME 结构的大小

	if (fd.DoModal() == IDOK)
	{
		CString des;	//返回的路径字符串
		des = fd.GetPathName();
		SetDlgItemText(IDC_EDIT_FILEROUTE, des);	//将字符串填入edit框
													//MessageBox(des);
	}
}
//——————————————————————————————————————————————————————————————————————————————————————</陈牧乔>
//——————————————————————————————————————————————————————————————————————————————————————<罗薇>
void insertExtend(int number, string name, string description, BOOL state)
{
	extend[number].name = name;
	extend[number].description = description;
	extend[number].state = state;
}

void initExtend()
{
	insertExtend(0, "*.syd", "临时文件", false);
	insertExtend(1, "*.~*", "临时文件", false);
	insertExtend(2, "~*.*", "临时文件", false);
	insertExtend(3, "*.---", "临时文件", false);
	insertExtend(4, "*.^*", "临时文件", false);
	insertExtend(5, "*.??~", "临时文件", false);
	insertExtend(6, "*.??$", "临时文件", false);
	insertExtend(7, "*.tmp", "临时文件", false);
	insertExtend(8, "*._mp", "临时文件", false);
	insertExtend(9, "*.spc", "WordPerfect临时文件", false);
	insertExtend(10, "*.cdr_", "Corel DRAW临时文件", false);
	insertExtend(11, "*.#Res", "Mac Photoshop临时文件", false);
	insertExtend(12, "*.%%%", "安装的临时文件", false);
	insertExtend(13, "*.@@@", "安装的临时文件", false);
	insertExtend(14, "*.$$$", "安装的临时文件", false);
	insertExtend(15, "mscreate.dir", "安装的临时文件", false);
	insertExtend(16, "*.chk", "丢失簇的恢复文件", false);
	insertExtend(17, "chklist.*", "丢失簇的恢复文件", false);
	insertExtend(18, "*.gid", "帮助与支持的临时文件", false);
	insertExtend(19, "*.fts", "帮助与支持的临时文件", false);
	insertExtend(20, "*.ftg", "帮助与支持的临时文件", false);
	insertExtend(21, "*.ms", "微软产品备份文件", false);
	insertExtend(22, "*.old", "备份文件", false);
	insertExtend(23, "*.bak", "备份文件", false);
	insertExtend(24, "*.prv", "备份文件", false);
	insertExtend(25, "*.wbk", "Word的备份文件", false);
	insertExtend(26, "*.xlk", "Excel的备份文件", false);
	insertExtend(27, "*.pch", "预编译头文件", false);
	insertExtend(28, "*.dmp", "内存转储文件", false);
	insertExtend(29, "*.diz", "zip文档说明文件", false);
	insertExtend(30, "Thumbs.db", "图片预览缩略图文件", false);
	insertExtend(31, "*.err", "错误日志文件", false);
	insertExtend(32, "*.log.txt", "错误日志文件", false);
}


BOOL PAGE5::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	initExtend();

	m_list_page5.SetExtendedStyle(
		LVS_EX_GRIDLINES |			//绘制表格
		LVS_EX_FULLROWSELECT |		//选中为一整行
		LVS_EX_CHECKBOXES);			//每行前设置checkbox
	m_list_page5.InsertColumn(0, "文件路径", NULL, 250, 50);
	m_list_page5.InsertColumn(1, "文件类型", NULL, 100, 50);
	m_list_page5.InsertColumn(2, "文件描述", NULL, 150, 50);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void PAGE5::OnBnClickedButtonFiletype()
{
	// TODO: 在此添加控件通知处理程序代码
	ChooseExtension* CXdlg;
	CXdlg = new ChooseExtension(this);

	for (int i = 0; i < 33; i++)
	{
		CXdlg->extState[i] = extend[i].state;
	}

	CXdlg->DoModal();

	string str = "";
	for (int i = 0; i < 33; i++)
	{
		extend[i].state = CXdlg->extState[i];
		if (extend[i].state)
		{
			str += "\"";
			str += extend[i].name;
			str += "\" ";
		}
	}

	TCHAR *extstring = new TCHAR[500];
	_stprintf_s(extstring, 500, "%s", str.c_str());
	SetDlgItemText(IDC_EDIT_FILETYPE, extstring);	//将字符串填入edit框
}
//——————————————————————————————————————————————————————————————————————————————————————</罗薇>
//——————————————————————————————————————————————————————————————————————————————————————<陈牧乔>
//判断是否为需要的类型的文件
int isWantedFileType(char* filename)
{
	for (int i = 0; i < 33; i++)
	{
		//对于每个用户选择的要清理的文件类型
		if (extend[i].state)
		{
			std::string pattern{ reg[i] };
			std::regex re(pattern);		//正则表达式
			std::string str = filename;	//待匹配的文件名
			bool ret = std::regex_match(str, re);	//返回匹配结果
			if (ret)	//如果匹配到当前文件类型
			{
				return i;
			}
		}
	}
	return -1;
}

//判断是否为目录
static BOOL IsChildDir(WIN32_FIND_DATA *lpFindData)
{
	return (
		((lpFindData->dwFileAttributes &
			FILE_ATTRIBUTE_DIRECTORY) != 0) &&	//文件属性不为目录
			(lstrcmp(lpFindData->cFileName, __TEXT(".")) != 0) &&	//长文件名不当前目录
		(lstrcmp(lpFindData->cFileName, __TEXT("..")) != 0));	//长文件名不是上一目录
}

//遍历路径指定文件夹
void PAGE5::searchFile(char * sourceFile)
{
	WIN32_FIND_DATA FindFileData;
	char src[BUFSIZE];	//保存源文件地址
	lstrcpy(src, sourceFile);	//将当前源文件根地址复制到源文件地址中
	lstrcat(src, "\\*");	//源地址追加\*，查找目录下所有文件
	HANDLE hFind = FindFirstFile(src,	//查找第一个文件
		&FindFileData);
	if (hFind != INVALID_HANDLE_VALUE)	//找到了文件
	{
		//循环查找下一文件，直到找完
		while (FindNextFile(hFind, &FindFileData) != 0)
		{
			//将源地址中的\*去除，回退到上一文件夹
			memset(src, 0, sizeof(src));	//源地址清零
			lstrcpy(src, sourceFile);
			lstrcat(src, "\\");
			//在源地址和目标地址后面追加找到的文件名
			lstrcat(src, FindFileData.cFileName);
			if (IsChildDir(&FindFileData))	//如果找到子目录
			{
				searchFile(src);	//进入子目录递归查找复制
			}
			else	//如果找到的是文件
			{
				//判断是否为要清理的文件类型，返回类型编号
				int num = isWantedFileType(FindFileData.cFileName);
				if (num != -1)
				{
					//获得列表的总行数
					int nItemNum = m_list_page5.GetItemCount();

					//设置文件类型和文件描述字符串，并进行格式转换
					TCHAR *type = new TCHAR[MAX_PATH];
					_stprintf_s(type, MAX_PATH, "%s", extend[num].name.c_str());
					TCHAR *description = new TCHAR[MAX_PATH];
					_stprintf_s(description, MAX_PATH, "%s", extend[num].description.c_str());

					//列表中添加行
					m_list_page5.InsertItem(nItemNum, src);
					m_list_page5.SetItemText(nItemNum, 1, type);
					m_list_page5.SetItemText(nItemNum, 2, description);
				}
			}
			//源地址和目标地址均回退到上一文件夹
			lstrcpy(src, sourceFile);
			lstrcat(src, "\\");
		}
	}
}

//扫描按钮
void PAGE5::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list_page5.DeleteAllItems();	//清空列表
	CString csX;
	m_edit_fileroute.GetWindowText(csX);	//获得文件路径
	char* sourceFile = (char*)csX.GetBuffer(0);	//格式转换
												//进行文件扫描
	searchFile(sourceFile);

	MessageBox(		//弹出提示框
		_T("扫描完成！"),	//文字内容
		_T("提示"),		//顶部文字
		MB_ICONASTERISK);	//提示图标
	return;
}
//——————————————————————————————————————————————————————————————————————————————————————</陈牧乔>
//——————————————————————————————————————————————————————————————————————————————————————<罗薇>
//全选checkbox的操作
void PAGE5::OnBnClickedCheckChooseallPage5()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_CHOOSEALL_PAGE5);
	int state = pBtn->GetCheck();
	if (state == 0)
	{
		for (int i = 0; i<m_list_page5.GetItemCount(); i++)
		{
			m_list_page5.SetCheck(i, false);
		}
	}
	else
	{
		for (int i = 0; i<m_list_page5.GetItemCount(); i++)
		{
			m_list_page5.SetCheck(i, true);
		}
	}
}

//清理文件按钮
void PAGE5::OnBnClickedButtonClean()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_list_page5.GetItemCount() == 0)
	{
		MessageBox(		//弹出提示框
			_T("没有可清理文件！"),	//文字内容
			_T("提示"),		//顶部文字
			MB_ICONASTERISK);	//提示图标
		return;
	}

	int cnt = 0;	//选中清理文件数

	for (int i = m_list_page5.GetItemCount() - 1; i >= 0; i--)
	{
		if (m_list_page5.GetCheck(i) == TRUE)
		{
			cnt++;
			char FileName[260];
			memset(FileName, 0, 260);
			m_list_page5.GetItemText(i, 0, FileName, 259);
			DeleteFile(FileName);
			m_list_page5.DeleteItem(i);
		}
	}

	if (cnt == 0)	//未勾选清理行
	{
		MessageBox(		//弹出提示框
			_T("请选择清理项！"),	//文字内容
			_T("提示"),		//顶部文字
			MB_ICONASTERISK);	//提示图标
		return;
	}

	string str = "清理完成！\n共清理 ";
	str += to_string(cnt);
	str += " 项文件";

	MessageBox(		//弹出提示框
		_T(str.c_str()),	//文字内容
		_T("提示"),		//顶部文字
		MB_ICONASTERISK);	//提示图标
}
//——————————————————————————————————————————————————————————————————————————————————————</罗薇>
//——————————————————————————————————————————————————————————————————————————————————————<陈牧乔>
//比较函数，用于list根据某一列排序
int CALLBACK PAGE5::MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	UNREFERENCED_PARAMETER(lParamSort);
	// 从参数中提取所需比较lc的两行数据
	int row1 = (int)lParam1;
	int row2 = (int)lParam2;
	CListCtrl* lc = (CListCtrl*)lParamSort;
	CString lp1 = lc->GetItemText(row1, sort_column_p5);
	CString lp2 = lc->GetItemText(row2, sort_column_p5);

	//按照字符串排序
	//正序或反序排序
	if (method_p5)
		return lp1.CompareNoCase(lp2);
	else
		return lp2.CompareNoCase(lp1);
	return 0;
}

//点击list的某列列头，根据这列排序
void PAGE5::OnLvnColumnclickListPage5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	sort_column_p5 = pNMLV->iSubItem;	//点击的列
	int count = m_list_page5.GetItemCount();	//list的行数
	for (int i = 0; i < count; i++)
	{
		//每行的比较关键字，此处为列序号（点击的列号），比较函数的第一二个参数
		m_list_page5.SetItemData(i, i);
	}
	method_p5 = !method_p5;		//下一次点击改变排序顺序
								//对list排序
	m_list_page5.SortItems(
		MyCompareProc,			//比较函数
		(LPARAM)&m_list_page5);	//比较函数的第三个参数
	*pResult = 0;
}
//——————————————————————————————————————————————————————————————————————————————————————</陈牧乔>