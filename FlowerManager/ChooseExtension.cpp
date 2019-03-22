/*
ChooseExtension.cpp: “文件清理”选择文件类型页
作者：1120151775 罗薇
*/
//——————————————————————————————————————————————————————————————————————————————————————<罗薇>
#include "stdafx.h"
#include "FlowerManager.h"
#include "ChooseExtension.h"
#include "afxdialogex.h"
#include "PAGE5.h"

// ChooseExtension 对话框

IMPLEMENT_DYNAMIC(ChooseExtension, CDialogEx)

ChooseExtension::ChooseExtension(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHOOSE_EXTENDED, pParent)
{
}

ChooseExtension::~ChooseExtension()
{
}

void ChooseExtension::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EXTENSION, m_list_extension);
}

BEGIN_MESSAGE_MAP(ChooseExtension, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_EXTENSION, &ChooseExtension::OnLvnItemchangedListExtension)
	ON_BN_CLICKED(IDC_BUTTON_EXTENSION_OK, &ChooseExtension::OnBnClickedButtonExtensionOk)
	ON_BN_CLICKED(IDC_CHECK_CHOOSE_ALL_EXT, &ChooseExtension::OnBnClickedCheckChooseAllExt)
END_MESSAGE_MAP()

// ChooseExtension 消息处理程序

BOOL ChooseExtension::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_list_extension.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_list_extension.InsertColumn(0, "文件类型", NULL, 200, 50);
	m_list_extension.InsertColumn(1, "描述", NULL, 200, 50);
	AddItem("*.syd", "临时文件");
	AddItem("*.~*", "临时文件");
	AddItem("~*.*", "临时文件");
	AddItem("*.---", "临时文件");
	AddItem("*.^*", "临时文件");
	AddItem("*.??~", "临时文件");
	AddItem("*.??$", "临时文件");
	AddItem("*.tmp", "临时文件");
	AddItem("*._mp", "临时文件");
	AddItem("*.spc", "WordPerfect临时文件");
	AddItem("*.cdr_", "Corel DRAW临时文件");
	AddItem("*.#Res", "Mac Photoshop临时文件");
	AddItem("*.%%%", "安装的临时文件");
	AddItem("*.@@@", "安装的临时文件");
	AddItem("*.$$$", "安装的临时文件");
	AddItem("mscreate.dir", "安装的临时文件");
	AddItem("*.chk", "丢失簇的恢复文件");
	AddItem("chklist.*", "丢失簇的恢复文件");
	AddItem("*.gid", "帮助与支持的临时文件");
	AddItem("*.fts", "帮助与支持的临时文件");
	AddItem("*.ftg", "帮助与支持的临时文件");
	AddItem("*.ms", "微软产品备份文件");
	AddItem("*.old", "备份文件");
	AddItem("*.bak", "备份文件");
	AddItem("*.prv", "备份文件");
	AddItem("*.wbk", "Word的备份文件");
	AddItem("*.xlk", "Excel的备份文件");
	AddItem("*.pch", "预编译头文件");
	AddItem("*.dmp", "内存转储文件");
	AddItem("*.diz", "zip文档说明文件");
	AddItem("Thumbs.db", "图片预览缩略图文件");
	AddItem("*.err", "错误日志文件");
	AddItem("*.log.txt", "错误日志文件");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void ChooseExtension::AddItem(TCHAR* FileType, TCHAR* FileDescription)
{
	int nItemNum = m_list_extension.GetItemCount();
	m_list_extension.InsertItem(nItemNum, FileType);
	m_list_extension.SetItemText(nItemNum, 1, FileDescription);
	m_list_extension.SetCheck(nItemNum, extState[nItemNum]);
}


void ChooseExtension::OnLvnItemchangedListExtension(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	*pResult = 0;
}

//点击确认时将页面中list的checkbox状态写入extState[i]，然后关闭窗口
//用于父页面和子页面的参数传递
void ChooseExtension::OnBnClickedButtonExtensionOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//string str = "";

	for (int i = 0; i<m_list_extension.GetItemCount(); i++)
	{
		if (m_list_extension.GetCheck(i))
		{
			extState[i] = TRUE;
			//str += "1";
		}
		else
		{
			extState[i] = FALSE;
			//str += "0";
		}
	}

	OnCancel();
}

//全选按钮
void ChooseExtension::OnBnClickedCheckChooseAllExt()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_CHOOSE_ALL_EXT);
	int state = pBtn->GetCheck();
	if (state == 0)
	{
		for (int i = 0; i<m_list_extension.GetItemCount(); i++)
		{
			m_list_extension.SetCheck(i, false);
		}
	}
	else
	{
		for (int i = 0; i<m_list_extension.GetItemCount(); i++)
		{
			m_list_extension.SetCheck(i, true);
		}
	}
}
//——————————————————————————————————————————————————————————————————————————————————————</罗薇>