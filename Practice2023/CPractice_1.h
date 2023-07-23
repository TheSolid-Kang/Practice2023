#pragma once
#include "CPractice.h"
#include <type_traits>
#include <array>
#include "Headers.h"
#include <mutex>
#include <thread>
class CPractice_1 : public CPractice
{
#if UNICODE 
	using TString = std::wstring;
	using tifstream = std::wifstream;
	using tofstream = std::wofstream;
	using tistringstream = std::wistringstream;
	using tstring_view = std::wstring_view;
	using tstringstream = std::wstringstream;
#define tcout  wcout
#define tcin  wcin
#else
	using TString = std::string;
	using tifstream = std::ifstream;
	using tofstream = std::ofstream;
	using tistringstream = std::istringstream;
	using tstring_view = std::string_view;
	using tstringstream = std::stringstream;
#define tcout  cout
#define tcin  cin
#endif;
public:
	CPractice_1();
	~CPractice_1();
private:
	enum class PRACTICE_FUNC : size_t { ONE = 1, TWO, THREE, FOUR, FIVE, SIX
		, SEVEN //파일 검출 4차
		, EIGHT //파일 검출 5차
		, NINE //파일 검출 5차
		, TEN //로그 테스트
		, ELEVEN // 
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



		, SET_CONFIG
		, SET_EXCEPTION_LIST
		, SET_SEARCH_PATHS
		, CREATE_RESULT_FILE
		, CREATE_SEND_FILE
		, SEND_MAIL
		, WRITE_EXECUTE_RECORD
		, END };
	std::vector<std::thread> threads;
	
	

	//config
	TString m_exceptionListFIilePath;
	TString m_searchFilePath;
	TString m_resultFilePath;
	TString m_SendMailFilePath;
	TString m_ExcuteRecordFilePath;
	TString m_SMTPSendExePath;
	int m_exceptionVolume = 5;
	int m_minCnt = 100;

	std::vector<std::thread> m_vecThreads;
	std::map<TCHAR, std::vector<TString>> m_champExceptionList;
	std::map<TString, std::vector<const TString*>> m_chmapExtensions;
	std::vector<TString> m_vecSearchPathList;
	std::set<TString> m_setResults;
	TString m_result;
	TString m_sendMail;
	TString m_executeRecord;



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

