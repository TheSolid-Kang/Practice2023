#pragma once
#include "CPractice.h"
#include <type_traits>
#include <array>
#include "Headers.h"
#include <mutex>
#include <thread>
class CPractice_1 : public CPractice
{
public:
	CPractice_1();
	~CPractice_1();
private:
	enum class PRACTICE_FUNC : size_t { ONE = 1, TWO, THREE, FOUR, FIVE, SIX
		, SEVEN //파일 검출 4차
		, EIGHT //파일 검출 5차
		, NINE //파일 검출 5차
		, TEN //로그 테스트
		, END };
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
		, CREATE_TRACKING_FILE //파일 검출 3차
		, CREATE_TRACKING_FILE2 //파일 검출 4차
		, CREATE_TRACKING_FILE3 //파일 검출 5차
		, COMPARE //속도 비교
		, LOG_TEST //로그 테스트
		, END };
	std::vector<std::thread> threads;
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
	template<typename Func, typename Mutex, typename Ptr, typename Ptr2>
	constexpr decltype(auto) lock_and_call(Func _func, Mutex& _mutex, Ptr _ptr, Ptr2 _ptr2) noexcept
	{
		std::lock_guard<Mutex> mutex_guard(_mutex);//lock_guard의 생성
		return _func(_ptr, _ptr2);//lock_guard의 소멸자 호출
	}
	//ExecuteFx()

};

