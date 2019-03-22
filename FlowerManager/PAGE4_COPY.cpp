/*
PAGE4_COPY.cpp: “文件浏览”复制页
作者：1120151782 王紫薇
*/
//——————————————————————————————————————————————————————————————————————————————————————<王紫薇>
#include "stdafx.h"
#include "FlowerManager.h"
#include "PAGE4_COPY.h"
#include "afxdialogex.h"

// PAGE4_COPY 对话框

IMPLEMENT_DYNAMIC(PAGE4_COPY, CDialogEx)
// 标准构造函数 
PAGE4_COPY::PAGE4_COPY(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE4_COPY, pParent)  //！不可以重定义！
{

}

// 重载构造函数  传入文件路径、文件名
PAGE4_COPY::PAGE4_COPY(CString Dir, CString FileName)
	: CDialogEx(IDD_PAGE4_COPY)
	, m_Source(_T(Dir + FileName))  //源目录
	, m_Dest(_T(""))
	, m_FileName(_T(FileName))
{

}
// 重载构造函数  传入文件夹
PAGE4_COPY::PAGE4_COPY(CString Pack)
	: CDialogEx(IDD_PAGE4_COPY)
	, m_Source(_T(Pack))  //源目录
	, m_Dest(_T(""))
	, m_FileName(_T(""))
{

}

PAGE4_COPY::~PAGE4_COPY()
{
}

void PAGE4_COPY::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COPY_Source, m_Source);    //文件名
	DDX_Text(pDX, IDC_COPY_Dest, m_Dest);	//文件类型
}


BEGIN_MESSAGE_MAP(PAGE4_COPY, CDialogEx)
	ON_BN_CLICKED(IDOK, &PAGE4_COPY::OnBnClickedOk)
END_MESSAGE_MAP()


// PAGE4_COPY 消息处理程序
void PAGE4_COPY::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	CString DestStr;
	GetDlgItemText(IDC_COPY_Dest, DestStr);
	//MessageBox(DestStr);
	if (m_Source.Right(1) == "\\") //文件夹复制
	{
		//MessageBox("Copy Package");
		CopyDirectory(DestStr);
	}
	else
		CopySingleFile(DestStr);   //文件复制
}

void PAGE4_COPY::CopySingleFile(CString Dest)
{
	if (Dest.Right(1) != "\\")
		Dest += "\\";
	CString FullDest = Dest + m_FileName;
	BOOL m = CopyFile(m_Source, FullDest, TRUE);
	if (!m)
		MessageBox((LPCTSTR)"已存在");
	else
	{
		FullDest = "已复制到" + Dest;
		MessageBox(FullDest);
	}
}

void PAGE4_COPY::CopyDirectory(CString Dest) //文件夹复制
{
	//目标地址格式化
	int i;
	for (i = m_Source.GetLength() - 2; i >= 0; i--)
	{
		if (m_Source[i] == '\\') //back to root
			break;
	}
	//D : \ U n i t y \
	//1 2 3 4 5 6 7 8 9
	//lenth=9, i=2, right(6)
	Dest = Dest + m_Source.Right(m_Source.GetLength() - i - 1);

	if (CopyFolder(m_Source, Dest))
	{
		MessageBox("Copy Finished.");
	}
}

BOOL PAGE4_COPY::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  
}

BOOL  PAGE4_COPY::CopyFolder(CString source, CString dest)
{


	/*如果是目录自身复制，直接返回复制成功*/
	if (0 == _tcscmp(source, dest))
	{
		return TRUE;
	}
	if (source.Right(1) != "\\")
		source += "\\";
	if (dest.Right(1) != "\\")
		dest += "\\";

	/*如果目的目录不存在,则创建目录*/
	if (!IsDirectory(dest))
	{
		if (!CreateDirectory(dest, NULL))
		{
			return FALSE;		/*创建目的目录失败*/
		}
	}

	CString strWildcard(source);
	strWildcard += _T("*.*");

	CFileFind finder;
	BOOL fFound = finder.FindFile(strWildcard);

	while (fFound)
	{
		/*查找下一个文件*/
		fFound = finder.FindNextFile();

		/*跳过当前目录“.”和上一级目录“..”*/
		if (finder.IsDots())
		{
			continue;
		}

		/*得到当前要复制的源文件的路径*/
		CString strSrcFile = finder.GetFilePath();

		/*得到要复制的目标文件的路径*/
		CString strDstFile(dest);
		strDstFile += finder.GetFileName();

		/*判断当前文件是否是目录,*/
		/*如果是目录，递归调用复制目录,*/
		/*否则，直接复制文件*/
		if (finder.IsDirectory())
		{
			if (!CopyFolder(strSrcFile, strDstFile))
			{
				finder.Close();
				return FALSE;
			}
		}
		else
		{
			if (!CopyFile(strSrcFile, strDstFile, FALSE))
			{
				finder.Close();
				return FALSE;
			}
		}

	} /*while (fFound)*/

	  /*关闭文件查找*/
	finder.Close();
	return TRUE;
}

/*判断一个路径是否是已存在的目录*/
BOOL  PAGE4_COPY::IsDirectory(LPCTSTR pstrPath)
{
	if (NULL == pstrPath)
	{
		return FALSE;
	}

	/*去除路径末尾的反斜杠*/
	CString strPath = pstrPath;
	if (strPath.Right(1) == _T('\\'))
	{
		strPath.Delete(strPath.GetLength() - 1);
	}

	CFileFind finder;
	BOOL bRet = finder.FindFile(strPath);
	if (!bRet)
	{
		return FALSE;
	}

	/*判断该路径是否是目录*/
	finder.FindNextFile();
	bRet = finder.IsDirectory();
	finder.Close();
	return bRet;
}
//——————————————————————————————————————————————————————————————————————————————————————</王紫薇>