/*
PAGE4_COPY.h: ���ļ����������ҳͷ�ļ�
���ߣ�1120151782 ����ޱ
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<����ޱ>
#pragma once


// PAGE4_COPY �Ի���

class PAGE4_COPY : public CDialogEx
{
	DECLARE_DYNAMIC(PAGE4_COPY)

public:

	PAGE4_COPY(CWnd* pParent = NULL);   	// ��׼���캯�� 
	PAGE4_COPY(CString Dir, CString FileName);  	// �ļ����ƹ��캯��
	PAGE4_COPY(CString Pack);	//�ļ��и��ƹ��캯��
	
	virtual ~PAGE4_COPY();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE4_COPY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CString m_Source;
	CString m_Dest;   //��Edit��õ�Ŀ��·��
	CString m_FileName;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void CopySingleFile(CString DestStr);
	void CopyDirectory(CString DestStr);
	virtual BOOL OnInitDialog();
	BOOL IsDirectory(LPCTSTR pstrPath);
	BOOL CopyFolder(CString strSrcFolder, CString strDstFolder);
};
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</����ޱ>