#include "CPractice_1.h"
#include "CHashMap.h"
#include "Headers.h"
#include "CFileMgr.h"
#include "CINIMgr.h"
#include "StringBuilder.h"
#include "StringEditor.h"
#include <chrono>
#include "CLogger.h"

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
			auto titles = BuildArray(_T("1. ")
				, _T("99. EXIT"));
			std::for_each(titles.cbegin(), titles.cend(), [&](const TString& _title) { std::tcout << _title << std::endl; });
			return nullptr;
		}));
}

void CPractice_1::InitPracticeFunc(void)
{
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::ONE)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			return nullptr;
		}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::TWO)
		, [&](const void* _p_void) -> std::shared_ptr<void> {

			return nullptr;
		}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::THREE)
		, [&](const void* _p_void) -> std::shared_ptr<void> {

			return nullptr;
		}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::FOUR)
		, [&](const void* _p_void) -> std::shared_ptr<void> {

			return nullptr;
		}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::FIVE)
		, [&](const void* _p_void) -> std::shared_ptr<void> {

			return nullptr;
		}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::SIX)
		, [&](const void* _p_void) -> std::shared_ptr<void> {

			return nullptr;
		}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::SEVEN)
		, [&](const void* _p_void) -> std::shared_ptr<void> {


			return nullptr;
		}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::EIGHT)
		, [&](const void* _p_void) -> std::shared_ptr<void> {

			return nullptr;
		}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::NINE)
		, [&](const void* _p_void) -> std::shared_ptr<void> {

			return nullptr;
		}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::TEN)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			return nullptr;
		}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::ELEVEN)
		, [&](const void* _p_void) -> std::shared_ptr<void> {

			return nullptr;
		}));

}

void CPractice_1::Render(void) noexcept
{
	m_Funcs[static_cast<size_t>(FUNC::PRINT_TITLE)](nullptr);
}

void CPractice_1::Render(const void* _p_void)
{
}

int CPractice_1::Update(int _event)
{
	switch (CIO::ask_and_return_integer())
	{
	case static_cast<size_t>(PRACTICE_FUNC::ONE):
		m_PracFuncs[static_cast<size_t>(PRACTICE_FUNC::ONE)](nullptr);
		break;
	case static_cast<size_t>(PRACTICE_FUNC::TWO):
		m_PracFuncs[static_cast<size_t>(PRACTICE_FUNC::TWO)](nullptr);
		break;
	case static_cast<size_t>(PRACTICE_FUNC::THREE):
		m_PracFuncs[static_cast<size_t>(PRACTICE_FUNC::THREE)](nullptr);
		break;
	case static_cast<size_t>(PRACTICE_FUNC::FOUR):
		m_PracFuncs[static_cast<size_t>(PRACTICE_FUNC::FOUR)](nullptr);
		break;
	case static_cast<size_t>(PRACTICE_FUNC::FIVE):
		m_PracFuncs[static_cast<size_t>(PRACTICE_FUNC::FIVE)](nullptr);
		break;
	case static_cast<size_t>(PRACTICE_FUNC::SIX):
		m_PracFuncs[static_cast<size_t>(PRACTICE_FUNC::SIX)](nullptr);
		break;
	case static_cast<size_t>(PRACTICE_FUNC::SEVEN):
		m_PracFuncs[static_cast<size_t>(PRACTICE_FUNC::SEVEN)](nullptr);
		break;
	case static_cast<size_t>(PRACTICE_FUNC::EIGHT):
		m_PracFuncs[static_cast<size_t>(PRACTICE_FUNC::EIGHT)](nullptr);
		break;
	case static_cast<size_t>(PRACTICE_FUNC::NINE):
		m_PracFuncs[static_cast<size_t>(PRACTICE_FUNC::NINE)](nullptr);
		break;
	case static_cast<size_t>(PRACTICE_FUNC::TEN):
		m_PracFuncs[static_cast<size_t>(PRACTICE_FUNC::TEN)](nullptr);
		break;
	case static_cast<size_t>(PRACTICE_FUNC::ELEVEN):
		m_PracFuncs[static_cast<size_t>(PRACTICE_FUNC::ELEVEN)](nullptr);
		break;

	default:
		break;
	}

	return 0;
}

void CPractice_1::Release(void) noexcept
{
}


