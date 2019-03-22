/*
PAGE4_ATTR.cpp: “文件浏览”属性页
作者：1120151782 王紫薇
*/
//——————————————————————————————————————————————————————————————————————————————————————<王紫薇>

#include "stdafx.h"
#include "FlowerManager.h"
#include "PAGE4_ATTR.h"
#include "afxdialogex.h"



// PAGE4_ATTR 对话框

IMPLEMENT_DYNAMIC(PAGE4_ATTR, CDialogEx)

PAGE4_ATTR::PAGE4_ATTR(CWnd* pParent /*=NULL*/)  //标准构造函数
	: CDialogEx(IDD_PAGE4_ATTR, pParent)
{

}
//重载构造函数
PAGE4_ATTR::PAGE4_ATTR(CString  Path)
	: CDialogEx(IDD_PAGE4_ATTR)
	, m_StrFileName(_T(""))
	, m_StrType(_T(""))
	, m_StrPath(Path)
	, m_StrSize(_T(""))
	, m_StrCreatTime(_T(""))
	, m_StrViewTime(_T(""))
	, m_StrModifyTime(_T(""))
	, m_StrRead(_T(""))
{

}

PAGE4_ATTR::~PAGE4_ATTR()
{
}

void PAGE4_ATTR::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FileName, m_StrFileName);    //文件名
	DDX_Text(pDX, IDC_EDIT_Type, m_StrType);	//文件类型
	DDX_Text(pDX, IDC_EDIT_Path, m_StrPath);	//位置
	DDX_Text(pDX, IDC_EDIT_Size, m_StrSize);   //大小
	DDX_Text(pDX, IDC_EDIT_CreateTime, m_StrCreatTime);//创建时间
	DDX_Text(pDX, IDC_EDIT_ViewTime, m_StrViewTime); //最后访问
	DDX_Text(pDX, IDC_EDIT_ModifyTime, m_StrModifyTime);//修改时间
	DDX_Text(pDX, IDC_EDIT_Read, m_StrRead);   //可见性

}


BEGIN_MESSAGE_MAP(PAGE4_ATTR, CDialogEx)
	ON_BN_CLICKED(IDOK, &PAGE4_ATTR::OnBnClickedOk)
END_MESSAGE_MAP()


// PAGE4_ATTR 消息处理程序


void PAGE4_ATTR::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD Attr = GetFileAttributes(m_StrPath);
	Attr = Attr &~FILE_ATTRIBUTE_READONLY &~FILE_ATTRIBUTE_HIDDEN;

	CDialogEx::OnOK();
}


BOOL PAGE4_ATTR::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//获取文件信息
	CFileStatus FileStatus;
	if (CFile::GetStatus(m_StrPath, FileStatus))
	{
		/*
		struct CFileStatus
		{
			CTime m_ctime;          // creation date/time of file
			CTime m_mtime;          // last modification date/time of file
			CTime m_atime;          // last access date/time of file
			ULONGLONG m_size;       // logical size of file in bytes
			DWORD m_attribute;      // logical OR of CFile::Attribute enum values
			TCHAR m_szFullName[_MAX_PATH]; // absolute path name

			#ifdef _DEBUG
			void Dump(CDumpContext& dc) const;
			#endif
		};
		*/
		m_StrFileName = FileStatus.m_szFullName;
		m_StrCreatTime.Format(FileStatus.m_ctime.Format("%Y年%m月%d日  %H:%M:%S"));
		m_StrModifyTime.Format(FileStatus.m_mtime.Format("%Y年%m月%d日  %H:%M:%S"));
		m_StrViewTime.Format(FileStatus.m_atime.Format("%Y年%m月%d日  %H:%M:%S"));

		//文件尺寸;
		if (FileStatus.m_size / 1024 <1)
			m_StrSize.Format("%d Byte", FileStatus.m_size);
		else if (FileStatus.m_size / 1024 / 1024 < 1)
			m_StrSize.Format("%d KB", FileStatus.m_size / 1024);
		else if (FileStatus.m_size / 1024 / 1024 / 1024 < 1)
			m_StrSize.Format("%d MB", FileStatus.m_size / 1024 / 1024);
		else if (FileStatus.m_size / 1024 / 1024 / 1024 / 1024< 1)
			m_StrSize.Format("%d GB", FileStatus.m_size / 1024 / 1024 / 1024);

		//文件属性;
		if ((FileStatus.m_attribute & CFile::readOnly) == CFile::readOnly)
		{
			m_StrRead = ((LPCTSTR)"只读");
		}
		else if ((FileStatus.m_attribute & CFile::hidden) == CFile::hidden)
		{
			m_StrRead = "隐藏";
		}
		else
			m_StrRead = "读写";

		//获取文件类型;
		SHFILEINFO FileInfo = {};
		SHGetFileInfo(m_StrPath, 0, &FileInfo, sizeof(SHFILEINFO), SHGFI_TYPENAME);
		m_StrType = FileInfo.szTypeName;
		UpdateData(FALSE);
	}

	else
	{
		MessageBox("无权限访问");
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
//——————————————————————————————————————————————————————————————————————————————————————</王紫薇>