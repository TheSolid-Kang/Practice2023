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
	enum class PRACTICE_FUNC : size_t { ONE = 1, TWO, THREE, FOUR, FIVE, SIX, END };
	enum class FUNC : size_t { PRINT_TITLE //제목 출력
		, SET_CONFIG_INI //Cofig.ini 파일 세팅
		, SET_CONFIG_INI2 //Cofig.ini 파일 세팅2
		, GET_CONFIG_INI //Cofig.ini 데이터 std::map<TSting, std::list<TString>> 으로 반환
		, GET_CONFIG_INI2//Cofig.ini 데이터 std::map<TSting, std::map<TString, TString>> 으로 반환
		, GET_FILE_LIST //파일 검출 1차
		, GET_FILE_LIST2 //파일 검출 2차
		, CREATE_EXCEPSION_LIST //Exception
		, GET_EXCEPTION_LIST
		, GET_SEARCH_PATHS
		, CREATE_TRACKING_FILE
		, END };

protected:
	// IPractice을(를) 통해 상속됨
	virtual void Initialize(void) noexcept override;
	virtual void InitFunc(void) override;
	virtual void InitPracticeFunc(void) override;
	virtual void Render(void) noexcept override;
	virtual void Render(const void* _p_void) override;
	virtual int Update(int _event = 0) override;
	virtual void Release(void) noexcept override;
	



};

