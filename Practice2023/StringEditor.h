#pragma once
#include <iostream>
#include <string>
#include <tchar.h>
#include <vector>
#include <Windows.h>
#include <sstream>


class StringEditor {
#define DEFAULT_CAP 2048
#if UNICODE 
	using TString = std::wstring;
	using tifstream = std::wifstream;
	using tofstream = std::wofstream;
	using tistringstream = std::wistringstream;
#define tcout  wcout
#define tcin  wcin
#else
	using TString = std::string;
	using tifstream = std::ifstream;
	using tofstream = std::ofstream;
	using tistringstream = std::istringstream;
#define tcout  cout
#define tcin  cin
#endif;

public:
	static std::vector<TString> Split(const TString& str, TCHAR _delimiter)
	{
		std::vector<TString> vec_result;
		vec_result.reserve(1024);
		tistringstream iss(str);
		TString str_buffer;

		while (std::getline(iss, str_buffer, _delimiter))
			vec_result.push_back(str_buffer);
		vec_result.shrink_to_fit();
		return vec_result;
	}
	static TString ToLower(TString& _str) {

		for (TCHAR& _ch : _str) {
			if ('A' <= _ch && 'Z' >= _ch) {
				_ch |= 32;
			}
		}
		return _str;
	}

	static TString ToUpper(TString& _str) {

		for (TCHAR& _ch : _str) {
			if ('a' <= _ch && 'z' >= _ch) {
				_ch -= 32;
			}
		}
		return _str;
	}
};