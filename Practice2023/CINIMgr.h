#pragma once
#include <iostream>
#include <string>
#include <tchar.h>
#include <Windows.h>
#include <atlconv.h>
#include <filesystem>
#if UNICODE 
using TString = std::wstring;
#else
using TString = std::string;
#endif;

#define DEF_CAP 2048

class CINIMgr {
public:
	static TString GetDefaultConfigPath() {
		//1. �������� ��� ���ϱ� 
		TCHAR path[MAX_PATH] = { 0, };
		GetModuleFileName(NULL, path, MAX_PATH);
		TString exe_path = path;
		exe_path = exe_path.substr(0, exe_path.find_last_of(_T("\\/")));

		//221123 ����: ��ɿ��� | ��� ini ������ config ���� �ȿ��� �����Ǳ⿡ ����
		exe_path += _T("\\configINI");//������
		if (false == std::filesystem::exists(exe_path)) //������ ���ٸ� �����.
			std::filesystem::create_directory(exe_path);
		exe_path += _T("\\config.ini");//ini ���� ��

		return exe_path;
	}
	static void WritePrivateProfileString_INI(TString _section, TString _key, TString _value, TString _path = GetDefaultConfigPath()) {
		WritePrivateProfileString(_section.c_str(), _key.c_str(), _value.c_str(), _path.c_str());
	}
	static TString GetPrivateProfileString_INI(TString _section, TString _key, TString _path = GetDefaultConfigPath()) {
		TCHAR szBuffer[DEF_CAP] = { NULL , };
		GetPrivateProfileString(_section.c_str(), _key.c_str(), _T("0"), szBuffer, 1024, _path.c_str());
		TString wstr(szBuffer);
		return wstr;
	}

};