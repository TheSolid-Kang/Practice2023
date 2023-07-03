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
	enum class FUNC {ONE, TWO, THREE};

private:
	// CPractice을(를) 통해 상속됨
	virtual void Initialize() noexcept override;
	virtual int Update() override;
	virtual void Render() noexcept override;
	virtual void Release() noexcept override;

private:
	template<typename ...Args>
	auto _BuildArray(Args&&... _args)
		-> std::array<std::common_type_t<Args...>, sizeof ...(_args)>
	{ return { std::forward<std::common_type_t<Args...>>((Args&&)_args)... }; }




};

