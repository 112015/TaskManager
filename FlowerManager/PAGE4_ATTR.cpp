/*
PAGE4_ATTR.cpp: ���ļ����������ҳ
���ߣ�1120151782 ����ޱ
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<����ޱ>

#include "stdafx.h"
#include "FlowerManager.h"
#include "PAGE4_ATTR.h"
#include "afxdialogex.h"



// PAGE4_ATTR �Ի���

IMPLEMENT_DYNAMIC(PAGE4_ATTR, CDialogEx)

PAGE4_ATTR::PAGE4_ATTR(CWnd* pParent /*=NULL*/)  //��׼���캯��
	: CDialogEx(IDD_PAGE4_ATTR, pParent)
{

}
//���ع��캯��
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
	DDX_Text(pDX, IDC_EDIT_FileName, m_StrFileName);    //�ļ���
	DDX_Text(pDX, IDC_EDIT_Type, m_StrType);	//�ļ�����
	DDX_Text(pDX, IDC_EDIT_Path, m_StrPath);	//λ��
	DDX_Text(pDX, IDC_EDIT_Size, m_StrSize);   //��С
	DDX_Text(pDX, IDC_EDIT_CreateTime, m_StrCreatTime);//����ʱ��
	DDX_Text(pDX, IDC_EDIT_ViewTime, m_StrViewTime); //������
	DDX_Text(pDX, IDC_EDIT_ModifyTime, m_StrModifyTime);//�޸�ʱ��
	DDX_Text(pDX, IDC_EDIT_Read, m_StrRead);   //�ɼ���

}


BEGIN_MESSAGE_MAP(PAGE4_ATTR, CDialogEx)
	ON_BN_CLICKED(IDOK, &PAGE4_ATTR::OnBnClickedOk)
END_MESSAGE_MAP()


// PAGE4_ATTR ��Ϣ�������


void PAGE4_ATTR::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD Attr = GetFileAttributes(m_StrPath);
	Attr = Attr &~FILE_ATTRIBUTE_READONLY &~FILE_ATTRIBUTE_HIDDEN;

	CDialogEx::OnOK();
}


BOOL PAGE4_ATTR::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//��ȡ�ļ���Ϣ
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
		m_StrCreatTime.Format(FileStatus.m_ctime.Format("%Y��%m��%d��  %H:%M:%S"));
		m_StrModifyTime.Format(FileStatus.m_mtime.Format("%Y��%m��%d��  %H:%M:%S"));
		m_StrViewTime.Format(FileStatus.m_atime.Format("%Y��%m��%d��  %H:%M:%S"));

		//�ļ��ߴ�;
		if (FileStatus.m_size / 1024 <1)
			m_StrSize.Format("%d Byte", FileStatus.m_size);
		else if (FileStatus.m_size / 1024 / 1024 < 1)
			m_StrSize.Format("%d KB", FileStatus.m_size / 1024);
		else if (FileStatus.m_size / 1024 / 1024 / 1024 < 1)
			m_StrSize.Format("%d MB", FileStatus.m_size / 1024 / 1024);
		else if (FileStatus.m_size / 1024 / 1024 / 1024 / 1024< 1)
			m_StrSize.Format("%d GB", FileStatus.m_size / 1024 / 1024 / 1024);

		//�ļ�����;
		if ((FileStatus.m_attribute & CFile::readOnly) == CFile::readOnly)
		{
			m_StrRead = ((LPCTSTR)"ֻ��");
		}
		else if ((FileStatus.m_attribute & CFile::hidden) == CFile::hidden)
		{
			m_StrRead = "����";
		}
		else
			m_StrRead = "��д";

		//��ȡ�ļ�����;
		SHFILEINFO FileInfo = {};
		SHGetFileInfo(m_StrPath, 0, &FileInfo, sizeof(SHFILEINFO), SHGFI_TYPENAME);
		m_StrType = FileInfo.szTypeName;
		UpdateData(FALSE);
	}

	else
	{
		MessageBox("��Ȩ�޷���");
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</����ޱ>