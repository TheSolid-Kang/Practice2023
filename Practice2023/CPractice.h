#pragma once
#include <iostream>
#include <functional>
#include <map>
#include <type_traits>

class IPractice
{
protected:
	virtual void Initialize(void) noexcept = 0;
	virtual void InitFunc(void) = 0;
	virtual void InitSelectedFunc(void) = 0;
	virtual void Render(void) noexcept = 0;
	virtual void Render(const void* _p_void) = 0;
	virtual int Update(int _event = 0) = 0;
	virtual void Release(void) noexcept = 0;
};

class CPractice : public IPractice
{
public:
	CPractice();
	virtual ~CPractice();

private: 
	enum class PRACTICE_FUNC : size_t { PRINT_TITLE, END };
	enum class FUNC : size_t { PRINT_TITLE, END};
	std::map<FUNC, std::function<std::shared_ptr<void>(const void*)>> m_Funcs;
	std::map<PRACTICE_FUNC, size_t, std::function<std::shared_ptr<void>(const void*)>> m_PracFuncs;

public:
	virtual int Execute();

protected:
	// IPractice을(를) 통해 상속됨
	virtual void Initialize(void) noexcept override;
	virtual void InitFunc(void) override;
	virtual void InitSelectedFunc(void) override;
	virtual void Render(void) noexcept override;
	virtual void Render(const void* _p_void) override;
	virtual int Update(int _event = 0) override;
	virtual void Release(void) noexcept override;

protected:
	template<typename... Args>
	auto BuildArray(Args&&... _args)
		-> std::array<std::common_type_t<Args...>, sizeof ...(_args)>
	{return { std::forward<std::common_type_t<Args...>>((Args&&)_args)... }; }
};

