#pragma once
#include "CPractice.h"
#include <type_traits>
#include <array>
#include "Headers.h"

class CPractice_1 : public CPractice
{
public:
	CPractice_1();
	~CPractice_1();
private:
	enum class PRACTICE_FUNC : size_t { ONE = 1, TWO, THREE, FOUR, FIVE, END };
	enum class FUNC : size_t { PRINT_TITLE, SET_CONFIG_INI, GET_CONFIG_INI, GET_FILE_LIST, GET_FILE_LIST2
								, GET_EXCEPTION_LIST, END };

protected:
	// IPractice을(를) 통해 상속됨
	virtual void Initialize(void) noexcept override;
	virtual void InitFunc(void) override;
	virtual void InitPracticeFunc(void) override;
	virtual void Render(void) noexcept override;
	virtual void Render(const void* _p_void) override;
	virtual int Update(int _event = 0) override;
	virtual void Release(void) noexcept override;
	
private:
	std::vector<TString> Split(const TString& str, TCHAR _delimiter)
	{
		std::vector<TString> vec_result;
		vec_result.reserve(1024);
		tistringstream iss(str);
		TString str_buffer;

		while (std::getline(iss, str_buffer, _delimiter))
			vec_result.push_back(str_buffer);

		return vec_result;
	}
	TString ToLower(TString& _str) {

		for (TCHAR& _ch : _str) {
			if ('A' <= _ch && 'Z' >= _ch) {
				_ch |= 32;
			}
		}
		return _str;
	}

	TString ToUpper(TString& _str) {

		for (TCHAR& _ch : _str) {
			if ('a' <= _ch && 'z' >= _ch) {
				_ch -= 32;
			}
		}
		return _str;
	}



};

