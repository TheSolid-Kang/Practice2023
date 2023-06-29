#pragma once
class CPractice
{
protected:
	virtual void Initialize() noexcept = 0 ;
	virtual int Update() = 0;
	virtual void Render() noexcept = 0;
	virtual void Release() noexcept = 0;

public:
	virtual int Execute();
};

