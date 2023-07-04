#include "CPractice.h"
#include "Headers.h"
#if _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

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
	system("pause");
	system("cls");
	Initialize();
	Render();
	int result = Update();

	Release();
	auto memory_info = _CrtDumpMemoryLeaks();
	std::tcout << _T("Memory: ") << memory_info << std::endl;
	return result;
}

void CPractice::Initialize(void) noexcept
{
	InitFunc();
	InitPracticeFunc();
}

void CPractice::InitFunc(void)
{

}

void CPractice::InitPracticeFunc(void)
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