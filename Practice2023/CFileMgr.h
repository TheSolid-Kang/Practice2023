#pragma once
#include <Windows.h>
#include <commdlg.h> //open file dialog
#include <iostream>

#include <string>
#include <tchar.h>

#include <tchar.h>//ExecuteFile () 
#include <stdio.h>//ExecuteFile () 

#include <shlobj_core.h> //open folder dialog
#include <string>
#include <atlcore.h>


#include <fstream>
#include <filesystem>




class CFileMgr {
#if UNICODE 
	using TString = std::wstring;
	using tifstream = std::wifstream;
	using tofstream = std::wofstream;
#define tcout  wcout
#define tcin  wcin
#else
	using TString = std::string;
	using tifstream = std::ifstream;
	using tofstream = std::ofstream;
#define tcout  cout
#define tcin  wcin
#endif;
public:
	static TString GetOpenFileDialg() {
		OPENFILENAME OFN;
		TCHAR filePathName[MAX_PATH] = _T("");
		TCHAR lpstrFile[MAX_PATH] = _T("");
		TCHAR filter[] = _T("��� ����\0*.*\0�ؽ�Ʈ ����\0*.txt\0fbx ����\0*.fbx");
		HWND hWnd = NULL;

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		//OFN.hwndOwner = hWnd;
		OFN.hwndOwner = hWnd;
		OFN.lpstrFilter = filter;
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 100;
		OFN.lpstrInitialDir = _T(".");

		if (GetOpenFileName(&OFN) != 0) {
			wsprintf(filePathName, _T("%s ������ �����Ͻðڽ��ϱ�?"), OFN.lpstrFile);
			MessageBox(hWnd, filePathName, _T("���� ����"), MB_OK);

			TString wstr_result(OFN.lpstrFile); //LPWSTR -> std::wstring

			return wstr_result;//���� ��� ���
		}
		return _T("");
	}
	static void ExecuteFile(const TString& path = GetOpenFileDialg()) {
		HWND hConsole = GetConsoleWindow();
		ShowWindow(hConsole, SW_HIDE);

		SHELLEXECUTEINFO sei;
		ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));

		sei.cbSize = sizeof(SHELLEXECUTEINFO);
		//sei.lpFile =  L"C:\\ManyoneChurch\\msi\\SQLEXPRWT_x64_KOR.exe";
		sei.lpFile = path.c_str();
		sei.lpParameters = _T("");
		sei.nShow = SW_SHOW;
		sei.fMask = SEE_MASK_NOCLOSEPROCESS;
		sei.lpVerb = _T("open");
		DWORD result = ShellExecuteEx(&sei);
		if (sei.hProcess != NULL)
			WaitForSingleObject(sei.hProcess, INFINITE); //���⼭ �ش� ���μ����� ����ɶ����� ����ϰԵ�

		//ShellExecute(NULL, L"open", "C:\\ManyoneChurch\\msi\\sql.bat", NULL, NULL, SW_SHOW);
		//ShellExecute(NULL, _T("open"), path.c_str(), NULL, NULL, SW_SHOW);

	}

	static TString GetOpenFolderDialg(TString _path = (TString)_T("D:\\")) {

		auto BrowseCallbackProc = [](HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData) -> int CALLBACK{
			switch (uMsg)
			{
			case BFFM_INITIALIZED:      // ���� ���� ��ȭ���ڸ� �ʱ�ȭ �� ��, �ʱ� ��� ����
			{
			::SendMessage(hWnd, BFFM_SETSELECTION, TRUE, (LPARAM)lpData);
			}
			break;

			// BROWSEINFO ����ü�� ulFlags ���� BIF_STATUSTEXT �� ������ ��� ȣ��
			// ��, BIF_NEWDIALOGSTYLE �� �����Ǿ� ���� ��� ȣ����� ����
			case BFFM_SELCHANGED:       // ����ڰ� ������ ������ ��� ��ȭ���ڿ� ���õ� ��� ǥ��
			{
			TCHAR szPath[MAX_PATH] = { 0, };

			::SHGetPathFromIDList((LPCITEMIDLIST)lParam, szPath);
			::SendMessage(hWnd, BFFM_SETSTATUSTEXT, 0, (LPARAM)szPath);
			}
			break;

			// BROWSEINFO ����ü�� ulFlags ���� BIF_VALIDATE �� ������ ��� ȣ��
			// BIF_EDITBOX �� ���� ������ ��츸 ȣ���
			case BFFM_VALIDATEFAILED:   // ������ ��Ʈ�ѿ��� ���� �̸��� �߸� �Է��� ��� ȣ��
			{
			::MessageBox(hWnd, _T("�ش� ������ ã�� �� �����ϴ�."), _T("����"),
			MB_ICONERROR | MB_OK);
			}
			break;
			}

			return 0; };

		BROWSEINFO browse_info;
		TCHAR szTemp[MAX_PATH] = _T("");//���� ��ġ
		TCHAR* pRootPath = const_cast<TCHAR*>(_path.c_str());//���� ��ġ
		//const_cast<TCHAR*>(_T("D:\\"));//���� ��ġ
		HWND hWnd = NULL;
		ZeroMemory(&browse_info, sizeof(BROWSEINFO));

		browse_info.hwndOwner = hWnd;
		browse_info.lpszTitle = _T("������ �������ּ���.");
		browse_info.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX
			| BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT | BIF_VALIDATE;
		browse_info.lpfn = BrowseCallbackProc;
		browse_info.lParam = (LPARAM)pRootPath;
		browse_info.pszDisplayName = szTemp;

		LPITEMIDLIST pItemIdList = SHBrowseForFolder(&browse_info);

		if (SHGetPathFromIDList(pItemIdList, szTemp)) {
			MessageBox(hWnd, szTemp, _T("open?"), MB_OK);
			return browse_info.pszDisplayName;//szTemp 
		}

		return _T("");
	}

	static TCHAR* GetFileType(TCHAR* _path)
	{
		static TCHAR buf[MAX_PATH] = _T("");
		bool ret = false;
		TCHAR* ptr = nullptr;
#if UNICODE
		ptr = wcsrchr(_path, _T('.'));
		if (ptr == nullptr)
			return nullptr;
		wcscpy(buf, ptr + 1);//wcscpy �Լ� ����ϱ� ���� C++/��ó����: _CRT_SECURE_NO_WARNINGS �߰���.
#else
		ptr = strrchr(_path, _T('.'));
		if (ptr == nullptr)
			return nullptr;
		strcpy(buf, ptr + 1);
#endif



		return buf;
	}

	static std::vector<TString> getTxtFiles(const TString& dirPath) {
		std::vector<TString> txtFiles;
		TString searchPath = dirPath + _T("\\*.txt");
		WIN32_FIND_DATA fd;
		HANDLE hFind = ::FindFirstFile(searchPath.c_str(), &fd);
		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				txtFiles.push_back(fd.cFileName);
			} while (::FindNextFile(hFind, &fd));
			::FindClose(hFind);
		}
		return txtFiles;
	}
	//0. �������� ��� ���ϱ�
	static TString GetEXEFilePath() {
		//1. �������� ��� ���ϱ� 
		TCHAR path[MAX_PATH] = { 0, };
		GetModuleFileName(NULL, path, MAX_PATH);
		TString exe_path = path;
		exe_path = exe_path.substr(0, exe_path.find_last_of(_T("\\/")));
		return exe_path;
	}
	//1-1. Directory �� ���� ����
	static void CreateNewFile(TString _path) {
		TString file_path = _path;
		tofstream fout = tofstream(file_path);//���� ����_���� ������ ������ ����.

		std::tcout << _T("fout.is_open() == ") << fout.is_open() << std::endl;
		if (true == fout.is_open())
			fout.close();
	}
	//1-2. Directory �� ���� ���� ���ʴ�� ����
	static void CreateDirectorys(const TString& _path) {
		TString path(_path.begin(), _path.end());
		TCHAR arr_dir_name[256] = { 0, };
		TCHAR* ch_ptr_path = const_cast<TCHAR*>(path.c_str());
		TCHAR* ch_ptr_dirname = arr_dir_name;

		while (*ch_ptr_path) {
			if ((_T('\\') == *ch_ptr_path) || (_T('/') == *ch_ptr_path)) {
				if (_T(':') != *(ch_ptr_path - 1))
					CreateDirectory(arr_dir_name, NULL);
			}
			*ch_ptr_dirname++ = *ch_ptr_path++;
			*ch_ptr_dirname = _T('\0');
		}
		CreateDirectory(arr_dir_name, NULL);
	}


	//2-1. Directory �� ���� ��� ���
	static std::vector<TString> GetFilesInDirectory(TString& _path) {
		std::vector<TString> vec_files;
		vec_files.reserve(1024);
		auto iter = std::filesystem::directory_iterator(_path);
		while (true != iter._At_end()) {
#if UNICODE 
			vec_files.emplace_back((*iter++).path().wstring());//std::filesystem::path -> std::string ���� ��ȯ
#else
			vec_files.emplace_back((*iter++).path().string());//std::filesystem::path -> std::string ���� ��ȯ
#endif;
		}
		vec_files.shrink_to_fit();
		return vec_files;
	}
	//2-2. Directory �� ���� ��� ���
	static std::vector<TString> GetRecursiveFilesInDirectory(TString& _path) {
		std::vector<TString> vec_files;
		vec_files.reserve(1024);
		auto iter = std::filesystem::directory_iterator(_path);
		TString str_file_path = _T("");
		while (true != iter._At_end()) {
			try {
				std::filesystem::path file_path = (*iter++).path();
#if UNICODE 
				str_file_path = file_path.wstring();//std::filesystem::path -> std::wstring ���� ��ȯ
#else
				file_path(file_path.string());//std::filesystem::path -> std::string ���� ��ȯ
#endif;
				if (std::filesystem::is_directory(file_path)) {
					auto vec_recursive_file = GetRecursiveFilesInDirectory(str_file_path);
					vec_files.insert(vec_files.end(), vec_recursive_file.begin(), vec_recursive_file.end());
				}
				else
				{
					auto size = file_path.extension().string().size();
					if(size > 4)
						vec_files.emplace_back(str_file_path);
				}
			}
			catch (std::exception _e) {

				std::tcout << _e.what() << _T("\n: ") << str_file_path << _T("\n: ") << std::endl;
			}

		}
		vec_files.shrink_to_fit();
		return vec_files;
	}
	static TString GetExtention(const TString& _path) {
		std::filesystem::path path = _path;
#if UNICODE 
		TString extension = path.extension().wstring();
#else
		TString extension = path.extension().string();
#endif
		return extension;
	}

	static std::list<std::string> GetRecursiveFilesInDirectoryTemp(const std::string& _path) {
		std::list<std::string> vec_files;
		//vec_files.reserve(1024);
		auto iter = std::filesystem::directory_iterator(_path);
		std::string str_file_path = "";
		while (true != iter._At_end()) {
			try {
				std::filesystem::path file_path = (*iter++).path();
				str_file_path = file_path.string();//std::filesystem::path -> std::string ���� ��ȯ

				if (std::filesystem::is_directory(file_path)) {
					auto vec_recursive_file = GetRecursiveFilesInDirectoryTemp(str_file_path);
					vec_files.insert(vec_files.end(), vec_recursive_file.begin(), vec_recursive_file.end());
				}
				else {
					//auto size = file_path.extension().string().size();
					//if(size > 4)
					vec_files.emplace_back(str_file_path);
				}
			}
			catch (std::exception _e) {

				std::cout << _e.what() << "\n: " << str_file_path << "\n" << std::endl;
			}
		}
		//vec_files.shrink_to_fit();
		return vec_files;
	}

};