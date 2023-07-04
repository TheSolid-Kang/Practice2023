#include "CPractice_1.h"
#include "CHashMap.h"
#include "Headers.h"
#include "CFileMgr.h"
#include "CINIMgr.h"

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
			auto titles = BuildArray(_T("1. config 파일 세팅")
				, _T("2. 파일 다이어로그 사용")
				, _T("3. vector 형식으로 모두 메모리에 올림.")
				, _T("")
				, _T("")
				, _T("")
				, _T("99. EXIT") );
			std::for_each(titles.cbegin(), titles.cend(), [&](const TString& _title) { std::tcout << _title << std::endl; });
			return nullptr;
		}));

	m_Funcs.emplace(std::make_pair(static_cast<size_t>(FUNC::SET_FILE_INI), [&](const void* _p_void) -> std::shared_ptr<void> {
		TString exePath = CFileMgr::GetEXEFilePath();
		TString dirPath = exePath + _T("\\Config");
		TString settingIniPath = dirPath + _T("\\Setting.ini");
		//실행 경로에 File 폴더가 없는 경우 File 폴더 생성
		if (false == std::filesystem::is_directory(dirPath))
			CFileMgr::CreateDirectorys(dirPath);

		//File 폴더에 Setting.ini가 없는 경우 Setting.ini파일 생성한 후 내용 채워넣음.
		if (false == std::filesystem::exists(settingIniPath))
		{
			CINIMgr::WritePrivateProfileString_INI(_T("SET"), _T("FILE_TYPE"), _T(".md"), settingIniPath);
			CINIMgr::WritePrivateProfileString_INI(_T("SET"), _T("ARR_KEYWORD"), _T("검색어"), settingIniPath);
		}
		auto temp = CINIMgr::GetPrivateProfileString_INI(_T("SET"), _T("SEARCH_KEYWORD"), settingIniPath);

		return nullptr; }));
	m_Funcs.emplace(std::make_pair(static_cast<size_t>(FUNC::GET_FILE_LIST), [&](const void* _p_void) -> std::shared_ptr<void> {
		TCHAR* fileType = ((TCHAR*)(_p_void));
		TString directoryPath = CFileMgr::GetOpenFolderDialg(_T("C:\\"));
		auto vecFiles = CFileMgr::GetRecursiveFilesInDirectory(directoryPath);

		std::list<TString> listFiles(vecFiles.begin(), vecFiles.end());

		return std::make_shared<std::list<TString>>(listFiles); }));


}

void CPractice_1::InitPracticeFunc(void)
{
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::ONE)
		, [&](const void* _p_void) -> std::shared_ptr<void>{
			m_Funcs[static_cast<size_t>(FUNC::SET_FILE_INI)](nullptr);
		return nullptr;
	}));	
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::TWO)
		, [&](const void* _p_void) -> std::shared_ptr<void>{
			m_Funcs[static_cast<size_t>(FUNC::GET_FILE_LIST)](nullptr);
		return nullptr;
	}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::THREE)
		, [&](const void* _p_void) -> std::shared_ptr<void> {

			//TString path = _T("C:\\");

//std::string path = "C:\\MinGW\\";
//TString path = _T("C:\\TAEKYUNG\\Dev\\CPP");
			TString path = _T("C:\\");
			auto lists = CFileMgr::GetRecursiveFilesInDirectory(path);
			std::map<TString, std::list<TString>> map;
			std::for_each(lists.begin(), lists.end()
				, [&](const TString& _path) {
					TString extension = CFileMgr::GetExtention(_path);
					map[extension].emplace_back(_path);
				}
			);




			lists.clear();
			map.clear();

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

	default:
		break;
	}

	return 0;
}

void CPractice_1::Release(void) noexcept
{
}


