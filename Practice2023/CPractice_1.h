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
		, SEVEN, EIGHT, NINE, TEN, ELEVEN, END };
	enum class FUNC : size_t { PRINT_TITLE //제목 출력

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
	
private:
	template<typename Func, typename Mutex, typename Ptr, typename Ptr2>
	constexpr decltype(auto) lock_and_call(Func _func, Mutex& _mutex, Ptr _ptr, Ptr2 _ptr2) noexcept
	{
		std::lock_guard<Mutex> mutex_guard(_mutex);//lock_guard의 생성
		return _func(_ptr, _ptr2);//lock_guard의 소멸자 호출
	}

};

