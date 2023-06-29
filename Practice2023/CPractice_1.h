#pragma once
#include "CPractice.h"
class CPractice_1 : public CPractice
{
public:
	CPractice_1() {

	}
	~CPractice_1() {
		Release();
	}
private:
	// CPractice을(를) 통해 상속됨
	virtual void Initialize() noexcept override;
	virtual int Update() override;
	virtual void Render() noexcept override;
	virtual void Release() noexcept override;

public:





};

