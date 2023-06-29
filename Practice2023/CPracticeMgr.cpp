#include "CPracticeMgr.h"
#include "CPractice_1.h"

IMPLEMENT_SINGLETON(CPracticeMgr);

CPracticeMgr::CPracticeMgr()
{
	SetPractice();
}

CPracticeMgr::~CPracticeMgr()
{
	if (nullptr != m_pPractice)
		delete m_pPractice;
}

void CPracticeMgr::SetPractice(const int& _practiceNum ) noexcept
{
	if (nullptr != m_pPractice)
		delete m_pPractice;

	switch (_practiceNum) {
	case static_cast<int>(PRACTICE_NUM::PN_1):
		m_pPractice = new CPractice_1();
		break;
	default:
		m_pPractice = new CPractice_1();
		break;
	}
}
