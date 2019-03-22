/*
PAGE4_COPY.cpp: ���ļ����������ҳ
���ߣ�1120151782 ����ޱ
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<����ޱ>
#include "stdafx.h"
#include "FlowerManager.h"
#include "PAGE4_COPY.h"
#include "afxdialogex.h"

// PAGE4_COPY �Ի���

IMPLEMENT_DYNAMIC(PAGE4_COPY, CDialogEx)
// ��׼���캯�� 
PAGE4_COPY::PAGE4_COPY(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE4_COPY, pParent)  //���������ض��壡
{

}

// ���ع��캯��  �����ļ�·�����ļ���
PAGE4_COPY::PAGE4_COPY(CString Dir, CString FileName)
	: CDialogEx(IDD_PAGE4_COPY)
	, m_Source(_T(Dir + FileName))  //ԴĿ¼
	, m_Dest(_T(""))
	, m_FileName(_T(FileName))
{

}
// ���ع��캯��  �����ļ���
PAGE4_COPY::PAGE4_COPY(CString Pack)
	: CDialogEx(IDD_PAGE4_COPY)
	, m_Source(_T(Pack))  //ԴĿ¼
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
	DDX_Text(pDX, IDC_COPY_Source, m_Source);    //�ļ���
	DDX_Text(pDX, IDC_COPY_Dest, m_Dest);	//�ļ�����
}


BEGIN_MESSAGE_MAP(PAGE4_COPY, CDialogEx)
	ON_BN_CLICKED(IDOK, &PAGE4_COPY::OnBnClickedOk)
END_MESSAGE_MAP()


// PAGE4_COPY ��Ϣ�������
void PAGE4_COPY::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
	CString DestStr;
	GetDlgItemText(IDC_COPY_Dest, DestStr);
	//MessageBox(DestStr);
	if (m_Source.Right(1) == "\\") //�ļ��и���
	{
		//MessageBox("Copy Package");
		CopyDirectory(DestStr);
	}
	else
		CopySingleFile(DestStr);   //�ļ�����
}

void PAGE4_COPY::CopySingleFile(CString Dest)
{
	if (Dest.Right(1) != "\\")
		Dest += "\\";
	CString FullDest = Dest + m_FileName;
	BOOL m = CopyFile(m_Source, FullDest, TRUE);
	if (!m)
		MessageBox((LPCTSTR)"�Ѵ���");
	else
	{
		FullDest = "�Ѹ��Ƶ�" + Dest;
		MessageBox(FullDest);
	}
}

void PAGE4_COPY::CopyDirectory(CString Dest) //�ļ��и���
{
	//Ŀ���ַ��ʽ��
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  
}

BOOL  PAGE4_COPY::CopyFolder(CString source, CString dest)
{


	/*�����Ŀ¼�����ƣ�ֱ�ӷ��ظ��Ƴɹ�*/
	if (0 == _tcscmp(source, dest))
	{
		return TRUE;
	}
	if (source.Right(1) != "\\")
		source += "\\";
	if (dest.Right(1) != "\\")
		dest += "\\";

	/*���Ŀ��Ŀ¼������,�򴴽�Ŀ¼*/
	if (!IsDirectory(dest))
	{
		if (!CreateDirectory(dest, NULL))
		{
			return FALSE;		/*����Ŀ��Ŀ¼ʧ��*/
		}
	}

	CString strWildcard(source);
	strWildcard += _T("*.*");

	CFileFind finder;
	BOOL fFound = finder.FindFile(strWildcard);

	while (fFound)
	{
		/*������һ���ļ�*/
		fFound = finder.FindNextFile();

		/*������ǰĿ¼��.������һ��Ŀ¼��..��*/
		if (finder.IsDots())
		{
			continue;
		}

		/*�õ���ǰҪ���Ƶ�Դ�ļ���·��*/
		CString strSrcFile = finder.GetFilePath();

		/*�õ�Ҫ���Ƶ�Ŀ���ļ���·��*/
		CString strDstFile(dest);
		strDstFile += finder.GetFileName();

		/*�жϵ�ǰ�ļ��Ƿ���Ŀ¼,*/
		/*�����Ŀ¼���ݹ���ø���Ŀ¼,*/
		/*����ֱ�Ӹ����ļ�*/
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

	  /*�ر��ļ�����*/
	finder.Close();
	return TRUE;
}

/*�ж�һ��·���Ƿ����Ѵ��ڵ�Ŀ¼*/
BOOL  PAGE4_COPY::IsDirectory(LPCTSTR pstrPath)
{
	if (NULL == pstrPath)
	{
		return FALSE;
	}

	/*ȥ��·��ĩβ�ķ�б��*/
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

	/*�жϸ�·���Ƿ���Ŀ¼*/
	finder.FindNextFile();
	bRet = finder.IsDirectory();
	finder.Close();
	return bRet;
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</����ޱ>