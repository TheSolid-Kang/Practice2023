#include "CPractice.h"

CPractice::CPractice()
{
	Initialize();
}

CPractice::~CPractice()
{
	Release();
}

int CPractice::Execute()
{
	Render();
	int result = Update();

	Release();
	return result;
}

void CPractice::Initialize(void) noexcept
{
	InitFunc();
	InitSelectedFunc();
}

void CPractice::InitFunc(void)
{

}

void CPractice::InitSelectedFunc(void)
{
}

void CPractice::Render(void) noexcept
{
}

void CPractice::Render(const void* _p_void)
{
}

int CPractice::Update(int _event)
{
	return 0;
}

void CPractice::Release() noexcept
{
	if (NULL != m_Funcs.size()) {
		m_Funcs.clear();
	}
}