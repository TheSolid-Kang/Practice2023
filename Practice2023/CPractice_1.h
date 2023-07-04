#pragma once
#include "CPractice.h"
#include <type_traits>
#include <array>

class CPractice_1 : public CPractice
{
public:
	CPractice_1();
	~CPractice_1();
private:
	enum class PRACTICE_FUNC : size_t { ONE = 1, TWO, THREE, FOUR, FIVE, END };
	enum class FUNC : size_t { PRINT_TITLE, SET_FILE_INI, GET_FILE_LIST, END };

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

