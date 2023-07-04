#include "CPractice_1.h"
#include "CHashMap.h"
#include "Headers.h"

CPractice_1::CPractice_1()
{
	Initialize();
}

CPractice_1::~CPractice_1()
{
}

void CPractice_1::Initialize(void) noexcept
{
	InitFunc();
	InitPracticeFunc();
}

void CPractice_1::InitFunc(void)
{
	m_Funcs.emplace(std::make_pair(static_cast<size_t>(FUNC::PRINT_TITLE)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			auto titles = BuildArray(_T("0. ")
				, _T("")
				, _T("")
				, _T("")
				, _T("") );
			return nullptr;
		}));
}

void CPractice_1::InitPracticeFunc(void)
{
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::ONE)
		, [&](const void* _p_void) -> std::shared_ptr<void>{


		return nullptr;
	}));
}

void CPractice_1::Render(void) noexcept
{
}

void CPractice_1::Render(const void* _p_void)
{
}

int CPractice_1::Update(int _event)
{
	return 0;
}

void CPractice_1::Release(void) noexcept
{
}


