#include "CPractice_1.h"
#include "CHashMap.h"
#include "Headers.h"
#include "CFileMgr.h"
#include "CINIMgr.h"
#include "StringBuilder.h"

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
				, _T("4. Config 파일 Set, Get")
				, _T("5. ExceptionList 제작")
				, _T("")
				, _T("99. EXIT"));
			std::for_each(titles.cbegin(), titles.cend(), [&](const TString& _title) { std::tcout << _title << std::endl; });
			return nullptr;
		}));
	m_Funcs.emplace(std::make_pair(static_cast<size_t>(FUNC::SET_CONFIG_INI)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			TString exePath = CFileMgr::GetEXEFilePath();
			TString dirPath = exePath + _T("\\Config");
			TString configIniPath = dirPath + _T("\\Config.ini");

			//실행 경로에 File 폴더가 없는 경우 File 폴더 생성
			if (false == std::filesystem::is_directory(dirPath)) {
				CFileMgr::CreateDirectorys(dirPath);
			}

			//File 폴더에 Setting.ini가 없는 경우 Setting.ini파일 생성한 후 내용 채워넣음.
			if (false == std::filesystem::exists(configIniPath)) {
				CINIMgr::WritePrivateProfileString_INI(_T("PATH"), _T("PATH1"), _T("C:\\"), configIniPath);
				CINIMgr::WritePrivateProfileString_INI(_T("PATH"), _T("PATH2"), _T(""), configIniPath);
				CINIMgr::WritePrivateProfileString_INI(_T("PATH"), _T("PATH3"), _T(""), configIniPath);
				CINIMgr::WritePrivateProfileString_INI(_T("PATH"), _T("PATH4"), _T(""), configIniPath);

				CINIMgr::WritePrivateProfileString_INI(_T("SET"), _T("EXTENTION_VOLUME"), _T("5"), configIniPath);
				CINIMgr::WritePrivateProfileString_INI(_T("SET"), _T("MIN_CNT"), _T("100"), configIniPath);
			}

			return nullptr;
		}));
	m_Funcs.emplace(std::make_pair(static_cast<size_t>(FUNC::GET_CONFIG_INI)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			TString exePath = CFileMgr::GetEXEFilePath();
			TString dirPath = exePath + _T("\\Config");
			TString configIniPath = dirPath + _T("\\Config.ini");

			std::map<TString, std::list<TString>> chmapConfig;
			chmapConfig[_T("PATH")].push_back(CINIMgr::GetPrivateProfileString_INI(_T("PATH"), _T("PATH1"), configIniPath));
			chmapConfig[_T("PATH")].push_back(CINIMgr::GetPrivateProfileString_INI(_T("PATH"), _T("PATH2"), configIniPath));
			chmapConfig[_T("PATH")].push_back(CINIMgr::GetPrivateProfileString_INI(_T("PATH"), _T("PATH3"), configIniPath));
			chmapConfig[_T("PATH")].push_back(CINIMgr::GetPrivateProfileString_INI(_T("PATH"), _T("PATH4"), configIniPath));
			chmapConfig[_T("PATH")].remove(_T(""));

			chmapConfig[_T("SET")].push_back(CINIMgr::GetPrivateProfileString_INI(_T("SET"), _T("EXTENTION_VOLUME"), configIniPath));
			chmapConfig[_T("SET")].push_back(CINIMgr::GetPrivateProfileString_INI(_T("SET"), _T("MIN_CNT"), configIniPath));


			return std::make_shared<std::map<TString, std::list<TString>>>(chmapConfig);
		}));
	m_Funcs.emplace(std::make_pair(static_cast<size_t>(FUNC::GET_FILE_LIST)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			TCHAR* fileType = ((TCHAR*)(_p_void));
			TString directoryPath = CFileMgr::GetOpenFolderDialg(_T("C:\\"));
			auto vecFiles = CFileMgr::GetRecursiveFilesInDirectory(directoryPath);

			std::list<TString> listFiles(vecFiles.begin(), vecFiles.end());

			return std::make_shared<std::list<TString>>(listFiles);
		}));
	m_Funcs.emplace(std::make_pair(static_cast<size_t>(FUNC::GET_FILE_LIST2)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			auto chmapConfig = *(std::map<TString, std::list<TString>>*)_p_void;
			auto extentionVolume = stoi(*chmapConfig[_T("SET")].cbegin());
			int minCnt = stoi(*++chmapConfig[_T("SET")].cbegin());

			std::map<TString, std::list<TString*>> chmapPath;

			std::for_each(chmapConfig[_T("PATH")].cbegin()
				, chmapConfig[_T("PATH")].cend(), [&](const TString& _path) {
					//drive 명 틀린 경우 예외처리 필요함.
					auto vecFiles = CFileMgr::GetRecursiveFilesInDirectory(const_cast<TString&>(_path), extentionVolume);
					for (auto _path : vecFiles) {
						chmapPath[CFileMgr::GetExtention(_path)].push_back(&_path);
					}
					StringBuilder strBuil;

					for (auto iter = chmapPath.cbegin(); iter != chmapPath.cend(); ) {
						if (minCnt > (*iter).second.size()) {
							chmapPath.erase(iter++);
							continue;
						}
						else {
							std::tcout << (*iter).first << std::endl;
							//std::tcout << _T("  SIZE: ") << (*iter).second.size() << _T("    ") << (*iter).first << std::endl;
							strBuil.Append_endl((*iter).first);
							++iter;
						}
					}
					TString exePath = CFileMgr::GetEXEFilePath();
					TString dirPath = exePath + _T("\\Result");
					TString configIniPath = dirPath + _T("\\ExceptionList") + _T(".txt");

					//실행 경로에 File 폴더가 없는 경우 File 폴더 생성
					if (false == std::filesystem::is_directory(dirPath)) {
						CFileMgr::CreateDirectorys(dirPath);
					}

					CFileMgr::CreateNewFile(configIniPath);

					strBuil.str();


				});


			int i = 0;
			i = chmapPath.size();

			return nullptr;
		}));
	m_Funcs.emplace(std::make_pair(static_cast<size_t>(FUNC::GET_EXCEPTION_LIST)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			auto chmapConfig = *(std::map<TString, std::list<TString>>*)_p_void;
			auto extentionVolume = stoi(*chmapConfig[_T("SET")].cbegin());
			int minCnt = stoi(*++chmapConfig[_T("SET")].cbegin());

			std::for_each(chmapConfig[_T("PATH")].cbegin()
				, chmapConfig[_T("PATH")].cend(), [&](const TString& _path) {
					//drive 명 틀린 경우 예외처리 필요함.
					TString exePath = CFileMgr::GetEXEFilePath();
					TString dirPath = exePath + _T("\\Result");
					TString filePath = dirPath + _T("\\ExceptionList") + _T(".txt");

					//실행 경로에 File 폴더가 없는 경우 File 폴더 생성
					if (false == std::filesystem::is_directory(dirPath)) {
						CFileMgr::CreateDirectorys(dirPath);
					}
					CFileMgr::WriteExceptionList(_path, filePath, extentionVolume);

					TString data = CFileMgr::ReadData(filePath);

				});

			return nullptr;
		}));

}

void CPractice_1::InitPracticeFunc(void)
{
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::ONE)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			m_Funcs[static_cast<size_t>(FUNC::SET_CONFIG_INI)](nullptr);
			return nullptr;
		}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::TWO)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			m_Funcs[static_cast<size_t>(FUNC::GET_FILE_LIST)](nullptr);
			return nullptr;
		}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::THREE)
		, [&](const void* _p_void) -> std::shared_ptr<void> {

			//TString path = _T("C:\\");

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
			//config 세팅
			m_Funcs[static_cast<size_t>(FUNC::SET_CONFIG_INI)](nullptr);
			auto sharChmapConfig = m_Funcs[static_cast<size_t>(FUNC::GET_CONFIG_INI)](nullptr);
			//config 정보 가져오기
			auto& chmapConfig = *(std::map<TString, std::list<TString>>*)sharChmapConfig.get();
			//config 데이터를 기준으로 
			// 확장자의 글자수가 EXTENTION_VOLUMN 이상이고
			// && 확장자 당 파일의 수가 MIN_CNT 이상인 값 추출
			m_Funcs[static_cast<size_t>(FUNC::GET_FILE_LIST2)](&chmapConfig);





			return nullptr;
		}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::FIVE)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			//config 세팅
			m_Funcs[static_cast<size_t>(FUNC::SET_CONFIG_INI)](nullptr);
			auto sharChmapConfig = m_Funcs[static_cast<size_t>(FUNC::GET_CONFIG_INI)](nullptr);
			//config 정보 가져오기
			auto& chmapConfig = *(std::map<TString, std::list<TString>>*)sharChmapConfig.get();
			//config 데이터를 기준으로 
			// 확장자의 글자수가 EXTENTION_VOLUMN 이상이고
			// && 확장자 당 파일의 수가 MIN_CNT 이상인 값 추출
			m_Funcs[static_cast<size_t>(FUNC::GET_EXCEPTION_LIST)](&chmapConfig);



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


