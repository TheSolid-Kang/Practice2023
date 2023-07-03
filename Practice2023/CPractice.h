#pragma once
#include <map>
#include <functional>
#include <iostream>

class CPractice
{
protected:
	std::map<size_t, std::function<std::shared_ptr<void>(const void*)>> m_map_func;

protected:
	virtual void Initialize() noexcept = 0 ;
	virtual int Update() = 0;
	virtual void Render() noexcept = 0;
	virtual void Release() noexcept = 0;

public:
	virtual int Execute();
};

