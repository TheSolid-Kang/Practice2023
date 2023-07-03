#include "CPractice_1.h"
#include "CHashMap.h"

CPractice_1::CPractice_1()
{
}

CPractice_1::~CPractice_1()
{
	Release();
}

void CPractice_1::Initialize() noexcept
{

}

int CPractice_1::Update()
{

	return 0;
}

void CPractice_1::Render() noexcept
{

}

void CPractice_1::Release() noexcept
{
	m_map_func.clear();
}
