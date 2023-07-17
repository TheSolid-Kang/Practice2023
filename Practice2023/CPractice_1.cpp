#include "CPractice_1.h"
#include "CHashMap.h"
#include "Headers.h"
#include "CFileMgr.h"
#include "CINIMgr.h"
#include "StringBuilder.h"
#include "StringEditor.h"
#include <chrono>

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
				, _T("6. 파일 검출 3차")
				, _T("7. 파일 검출 4차")
				, _T("8. 파일 검출 5차")
				, _T("9. 파일검출 비교(3차, 4차, 5차)")
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

				CINIMgr::WritePrivateProfileString_INI(_T("SET"), _T("EXTENSION_VOLUME"), _T("5"), configIniPath);
				CINIMgr::WritePrivateProfileString_INI(_T("SET"), _T("MIN_CNT"), _T("100"), configIniPath);
			}

			return nullptr;
		}));	
	m_Funcs.emplace(std::make_pair(static_cast<size_t>(FUNC::SET_CONFIG_INI2)
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
				CINIMgr::WritePrivateProfileString_INI(_T("PATH"), _T("SEARCH_DIRECTORY"), dirPath + _T("\\SearchPath.txt"), configIniPath);
				CINIMgr::WritePrivateProfileString_INI(_T("PATH"), _T("EXCEPTION_FILE_LIST"), dirPath + _T("\\ExceptionList.txt"), configIniPath);

				CINIMgr::WritePrivateProfileString_INI(_T("SET"), _T("EXTENSION_VOLUME"), _T("5"), configIniPath);
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

			chmapConfig[_T("SET")].push_back(CINIMgr::GetPrivateProfileString_INI(_T("SET"), _T("EXTENSION_VOLUME"), configIniPath));
			chmapConfig[_T("SET")].push_back(CINIMgr::GetPrivateProfileString_INI(_T("SET"), _T("MIN_CNT"), configIniPath));


			return std::make_shared<std::map<TString, std::list<TString>>>(chmapConfig);
		}));
	m_Funcs.emplace(std::make_pair(static_cast<size_t>(FUNC::GET_CONFIG_INI2)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			TString exePath = CFileMgr::GetEXEFilePath();
			TString dirPath = exePath + _T("\\Config");
			TString configIniPath = dirPath + _T("\\Config.ini");

			std::map<TString, std::map<TString, TString>> chmapConfig;
			chmapConfig[_T("PATH")][_T("SEARCH_DIRECTORY")] = CINIMgr::GetPrivateProfileString_INI(_T("PATH"), _T("SEARCH_DIRECTORY"), configIniPath);
			chmapConfig[_T("PATH")][_T("EXCEPTION_FILE_LIST")] = CINIMgr::GetPrivateProfileString_INI(_T("PATH"), _T("EXCEPTION_FILE_LIST"), configIniPath);
			
			chmapConfig[_T("SET")][_T("EXTENSION_VOLUME")] = CINIMgr::GetPrivateProfileString_INI(_T("SET"), _T("EXTENSION_VOLUME"), configIniPath);
			chmapConfig[_T("SET")][_T("MIN_CNT")] = CINIMgr::GetPrivateProfileString_INI(_T("SET"), _T("MIN_CNT"), configIniPath);


			return std::make_shared<std::map<TString, std::map<TString, TString>>>(chmapConfig);
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


			size_t i = 0;
			i = chmapPath.size();

			return nullptr;
		}));
	m_Funcs.emplace(std::make_pair(static_cast<size_t>(FUNC::CREATE_EXCEPSION_LIST)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			auto chmapConfig = *(std::map<TString, std::list<TString>>*)_p_void;
			auto extentionVolume = stoi(*chmapConfig[_T("SET")].cbegin());
			int minCnt = stoi(*++chmapConfig[_T("SET")].cbegin());

			TString exePath = CFileMgr::GetEXEFilePath();
			TString dirPath = exePath + _T("\\Result");
			std::set<TString> sets;

			std::map<TString, int> mapSplits;
			std::for_each(chmapConfig[_T("PATH")].cbegin()
				, chmapConfig[_T("PATH")].cend(), [&](const TString& _path) {
					//drive 명 틀린 경우 예외처리 필요함.
					TString exceptionListPath = dirPath + _T("\\ExceptionList.txt");
					CFileMgr::CreateNewFile(exceptionListPath);

					//실행 경로에 File 폴더가 없는 경우 File 폴더 생성
					if (false == std::filesystem::is_directory(dirPath)) {
						CFileMgr::CreateDirectorys(dirPath);
					}
					CFileMgr::WriteExtensionList(_path, exceptionListPath, extentionVolume);

					TString data = CFileMgr::ReadData(exceptionListPath);
					auto splits = StringEditor::Split(data, '\n');

					for (const TString& _extention : splits) {
						mapSplits[_extention]++;
					}

				});

			for (auto& _pair : mapSplits) {
				if (_pair.second > minCnt) {
					//std::tcout << _T("    SIZE: ") << _pair.second << _T("    FILE: ") << _pair.first << _T("   ") << std::endl;;
					//std::tcout << _pair.first << std::endl;;
					TString str = _pair.first;
					std::tcout << StringEditor::ToUpper(str) << std::endl;
					sets.insert(StringEditor::ToUpper(str));
				}
			}
			StringBuilder strBuild;
			TString exceptionListPath2 = dirPath + _T("\\ExceptionList2.txt");
			CFileMgr::CreateNewFile(exceptionListPath2);
			for (const TString& _extention : sets) {
				strBuild.Append_endl(_extention);
			}

			CFileMgr::WriteData(exceptionListPath2, strBuild.str());
			return nullptr;
		}));

	m_Funcs.emplace(std::make_pair(static_cast<size_t>(FUNC::GET_EXCEPTION_LIST)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			auto chmapConfig = *(std::map<TString, std::map<TString, TString>>*)_p_void;
			TString SearchDirectoryFilePath = chmapConfig[_T("PATH")][_T("SEARCH_DIRECTORY")];
			TString ExceptionListFilePath = chmapConfig[_T("PATH")][_T("EXCEPTION_FILE_LIST")];
			int extentionVolume = std::stoi(chmapConfig[_T("SET")][_T("EXTENSION_VOLUME")]);
			int minCnt = std::stoi(chmapConfig[_T("SET")][_T("MIN_CNT")]);

			std::shared_ptr<std::map<TCHAR, std::vector<TString>>> shar_chmapExceptionList;
			shar_chmapExceptionList = std::make_shared<std::map<TCHAR, std::vector<TString>>>();
			
			auto vec = StringEditor::Split(CFileMgr::ReadData(ExceptionListFilePath), '\n');
			for (size_t i = 0; i < vec.size(); ++i) {
				if (vec[i].size() > 1) { //글자수(extentionVolume) 이하의 확장자는 목록에서 제외한다. 
					(*shar_chmapExceptionList)[vec[i][1]].emplace_back(vec[i]);
				}
			}

			

			return shar_chmapExceptionList;
		}));
	m_Funcs.emplace(std::make_pair(static_cast<size_t>(FUNC::GET_SEARCH_PATHS)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			auto chmapConfig = *(std::map<TString, std::map<TString, TString>>*)_p_void;
			TString SearchDirectoryFilePath = chmapConfig[_T("PATH")][_T("SEARCH_DIRECTORY")];
			TString ExceptionListFilePath = chmapConfig[_T("PATH")][_T("EXCEPTION_FILE_LIST")];
			auto extentionVolume = std::stoi(chmapConfig[_T("SET")][_T("EXTENSION_VOLUME")]);
			int minCnt = std::stoi(chmapConfig[_T("SET")][_T("MIN_CNT")]);

			std::shared_ptr<std::vector<TString>> shar_vecSearchPathList;
			shar_vecSearchPathList = std::make_shared<std::vector<TString>>();

			auto vec = StringEditor::Split(CFileMgr::ReadData(SearchDirectoryFilePath), '\n');
			for (size_t i = 0; i < vec.size(); ++i) {
					(*shar_vecSearchPathList).emplace_back(vec[i]);
			}

			return shar_vecSearchPathList;
		}));
	m_Funcs.emplace(std::make_pair(static_cast<size_t>(FUNC::CREATE_TRACKING_FILE)
		, [&](const void* _p_void) -> std::shared_ptr<void> {

			//실행 속도 확인 함수 추가 예정
			auto chmapConfig = *(std::map<TString, std::map<TString, TString>>*)_p_void;
			TString SearchDirectoryFilePath = chmapConfig[_T("PATH")][_T("SEARCH_DIRECTORY")];
			TString ExceptionListFilePath = chmapConfig[_T("PATH")][_T("EXCEPTION_FILE_LIST")];
			auto extentionVolume = std::stoi(chmapConfig[_T("SET")][_T("EXTENSION_VOLUME")]);
			int minCnt = std::stoi(chmapConfig[_T("SET")][_T("MIN_CNT")]);

			//예외목록 
			auto shar_chmapExceptionList = m_Funcs[static_cast<size_t>(FUNC::GET_EXCEPTION_LIST)](&chmapConfig);
			auto& chmapExceptionList = *(std::map<TCHAR, std::vector<TString>>*)shar_chmapExceptionList.get();

			//검색파일 경로
			auto shar_vecSearchPathList = m_Funcs[static_cast<size_t>(FUNC::GET_SEARCH_PATHS)](&chmapConfig);
			auto& vecSearchPathList = *(std::vector<TString>*)shar_vecSearchPathList.get();
			//검색 결과 Result.txt 파일에 넣기
			TString resultFilePath = CFileMgr::GetEXEFilePath() + _T("\\Result\\Result.txt");
			CFileMgr::CreateNewFile(resultFilePath);
			std::for_each(vecSearchPathList.begin(), vecSearchPathList.end()
				, [&](TString& _searchPath) {
					auto vec = CFileMgr::GetRecursiveFilesInDirectory(_searchPath, extentionVolume, chmapExceptionList);
					for (auto iter = vec.begin(); iter != vec.end();) {
						CFileMgr::WriteData(resultFilePath, (*iter++));
					}
					vec.clear();
				});

			//1. Result.txt 파일 내에 있는 전체 파일Path 읽고, Vector에 담기 
			TString data = CFileMgr::ReadData(resultFilePath);
			std::vector<TString> paths = StringEditor::Split(data, '\n');
			std::map<TString, std::vector<const TString*> > chmapExtensions;
			for (const TString& _path : paths) {
				chmapExtensions[CFileMgr::GetExtention(_path)].emplace_back(&_path);
			}

			//2. 특정 파일 확장자가 minCnt개 이상 존재할 경우,  SendMail.txt 파일에 기록
			// minCnt 이하로 존재할 경우 함수 return
			for (auto iter = chmapExtensions.cbegin(); iter != chmapExtensions.cend(); ) {
				if (minCnt > (*iter).second.size() ) {
					chmapExtensions.erase(iter++); //삭제
				}
				else {
					++iter;
				}
			}
			if (chmapExtensions.size() == 0) {// minCnt 보다 많은 확장자가 없다면 return
				return nullptr;
			}
			/*
			SendMail.txt 양식
			이메일 타이틀: 랜섬웨어 발견! 
			의심 확장자 명: 
			FilePath목록 : 
			PATH1
			PATH2
			*/
			StringBuilder strBuil;
			TString sendMailPath = CFileMgr::GetEXEFilePath() + _T("\\Result\\SendMail.txt");
			CFileMgr::CreateNewFile(sendMailPath);
			int extensionCnt = 1;
			strBuil.Append(_T("의심 확장자 개수: ") + StringEditor::ToString(chmapExtensions.size()));
			for (std::pair<TString, std::vector<const TString*>> _pair : chmapExtensions) {
				strBuil.Append_endl(_T("\n\n\n"));
				strBuil.Append_endl(StringEditor::ToString(extensionCnt++) + _T(".의심 확장자 명: ") + _pair.first);
				strBuil.Append_endl(_T("파일 경로 목록"));
				std::vector<const TString*> filePaths = _pair.second;
				for (const TString* _filePath : filePaths) {
					strBuil.Append_endl(*_filePath);
				}
			}
			CFileMgr::WriteData(sendMailPath, strBuil.str());
			

			//추가 함수 로직
			//이후 다른 로직으로 C# SMTP 콘솔 프로그램 실행
			//SendMail.txt 메일 발송


			return nullptr;
		}));
	m_Funcs.emplace(std::make_pair(static_cast<size_t>(FUNC::CREATE_TRACKING_FILE2)
		, [&](const void* _p_void) -> std::shared_ptr<void> {

			//실행 속도 확인 함수 추가 예정
			auto chmapConfig = *(std::map<TString, std::map<TString, TString>>*)_p_void;
			TString SearchDirectoryFilePath = chmapConfig[_T("PATH")][_T("SEARCH_DIRECTORY")];
			TString ExceptionListFilePath = chmapConfig[_T("PATH")][_T("EXCEPTION_FILE_LIST")];
			auto extentionVolume = std::stoi(chmapConfig[_T("SET")][_T("EXTENSION_VOLUME")]);
			int minCnt = std::stoi(chmapConfig[_T("SET")][_T("MIN_CNT")]);

			//예외목록 
			auto shar_chmapExceptionList = m_Funcs[static_cast<size_t>(FUNC::GET_EXCEPTION_LIST)](&chmapConfig);
			auto& chmapExceptionList = *(std::map<TCHAR, std::vector<TString>>*)shar_chmapExceptionList.get();

			//검색파일 경로
			auto shar_vecSearchPathList = m_Funcs[static_cast<size_t>(FUNC::GET_SEARCH_PATHS)](&chmapConfig);
			auto& vecSearchPathList = *(std::vector<TString>*)shar_vecSearchPathList.get();
			std::mutex mux;
			

			//-> [&](TString& _searchPath, std::map<TCHAR, std::vector<TString>>& _chmapExceptionList, int _extentionVolume) { };

			//검색 결과 Result.txt 파일에 넣기
			TString resultFilePath = CFileMgr::GetEXEFilePath() + _T("\\Result\\Result.txt");
			CFileMgr::CreateNewFile(resultFilePath);

			auto ExecuteFx = [&](TString& _searchPath){
				auto vec = CFileMgr::GetRecursiveFilesInDirectory(_searchPath, extentionVolume, chmapExceptionList);

				for (auto iter = vec.begin(); iter != vec.end();) {
					//lock 적용
					lock_and_call(CFileMgr::WriteData, mux, resultFilePath, (*iter++));
					//CFileMgr::WriteData(resultFilePath, (*iter++));
				}
				vec.clear();
			};
			std::for_each(vecSearchPathList.begin(), vecSearchPathList.end()
				, [&](TString& _searchPath) {
					//ExecuteFx(_searchPath, chmapExceptionList, extentionVolume, resultFilePath, mux);
					//auto thread2 = new std::thread(ExecuteFx, _searchPath);
					//threads.push_back(thread);
					/*
					auto vec = CFileMgr::GetRecursiveFilesInDirectory(_searchPath, extentionVolume, chmapExceptionList);
					for (auto iter = vec.begin(); iter != vec.end();) {
						//lock 적용
						lock_and_call(CFileMgr::WriteData, mux, resultFilePath, (*iter++));
						//CFileMgr::WriteData(resultFilePath, (*iter++));
					}
					vec.clear();
					*/
					//(*thread).detach();
					threads.push_back(std::thread([&]() {
						//TString _resultFilePath = CFileMgr::GetEXEFilePath() + _T("\\Result\\Result.txt");
						auto vec = CFileMgr::GetRecursiveFilesInDirectory(_searchPath, extentionVolume, chmapExceptionList);

						for (auto iter = vec.begin(); iter != vec.end();) {
							//lock 적용
							lock_and_call(CFileMgr::WriteData, mux, resultFilePath, (*iter++));
							//CFileMgr::WriteData(resultFilePath, (*iter++));
						}
						vec.clear();
						}));
				});

			for (size_t i = 0; i < threads.size(); ++i) {
				if (true == threads[i].joinable()) {
					threads[i].join();
				}
				//(*_thread).joinable();
			}






			//1. Result.txt 파일 내에 있는 전체 파일Path 읽고, Vector에 담기 
			TString data = CFileMgr::ReadData(resultFilePath);
			std::vector<TString> paths = StringEditor::Split(data, '\n');
			std::map<TString, std::vector<const TString*> > chmapExtensions;
			for (const TString& _path : paths) {
				chmapExtensions[CFileMgr::GetExtention(_path)].emplace_back(&_path);
			}

			//2. 특정 파일 확장자가 minCnt개 이상 존재할 경우,  SendMail.txt 파일에 기록
			// minCnt 이하로 존재할 경우 함수 return
			for (auto iter = chmapExtensions.cbegin(); iter != chmapExtensions.cend(); ) {
				if (minCnt > (*iter).second.size() ) {
					chmapExtensions.erase(iter++); //삭제
				}
				else {
					++iter;
				}
			}
			if (chmapExtensions.size() == 0) {// minCnt 보다 많은 확장자가 없다면 return
				return nullptr;
			}
			/*
			SendMail.txt 양식
			이메일 타이틀: 랜섬웨어 발견! 
			의심 확장자 명: 
			FilePath목록 : 
			PATH1
			PATH2
			*/
			StringBuilder strBuil;
			TString sendMailPath = CFileMgr::GetEXEFilePath() + _T("\\Result\\SendMail.txt");
			CFileMgr::CreateNewFile(sendMailPath);
			int extensionCnt = 1;
			strBuil.Append(_T("의심 확장자 개수: ") + StringEditor::ToString(chmapExtensions.size()));
			for (std::pair<TString, std::vector<const TString*>> _pair : chmapExtensions) {
				strBuil.Append_endl(_T("\n\n\n"));
				strBuil.Append_endl(StringEditor::ToString(extensionCnt++) + _T(".의심 확장자 명: ") + _pair.first);
				strBuil.Append_endl(_T("파일 경로 목록"));
				std::vector<const TString*> filePaths = _pair.second;
				for (const TString* _filePath : filePaths) {
					strBuil.Append_endl(*_filePath);
				}
			}
			CFileMgr::WriteData(sendMailPath, strBuil.str());
			

			//추가 함수 로직
			//이후 다른 로직으로 C# SMTP 콘솔 프로그램 실행
			//SendMail.txt 메일 발송
			//auto sendExePath = _T("C:\\TAEKYUNG\\Dev\\Git\\RansomewareTracker\\RansomewareTrackerSMTPSender\\RansomewareTrackerSMTPSender\\bin\\Release\\net6.0\\RansomewareTrackerSMTPSender.exe");
			auto sendExePath = CFileMgr::GetEXEFilePath() + _T("\\SMTPSender\\RansomewareTrackerSMTPSender.exe");
			//CFileMgr::ExecuteFile(sendExePath);


			return nullptr;
		}));
	m_Funcs.emplace(std::make_pair(static_cast<size_t>(FUNC::CREATE_TRACKING_FILE3)
		, [&](const void* _p_void) -> std::shared_ptr<void> {

			//실행 속도 확인 함수 추가 예정
			auto chmapConfig = *(std::map<TString, std::map<TString, TString>>*)_p_void;
			TString SearchDirectoryFilePath = chmapConfig[_T("PATH")][_T("SEARCH_DIRECTORY")];
			TString ExceptionListFilePath = chmapConfig[_T("PATH")][_T("EXCEPTION_FILE_LIST")];
			auto extentionVolume = std::stoi(chmapConfig[_T("SET")][_T("EXTENSION_VOLUME")]);
			int minCnt = std::stoi(chmapConfig[_T("SET")][_T("MIN_CNT")]);

			//예외목록 
			auto shar_chmapExceptionList = m_Funcs[static_cast<size_t>(FUNC::GET_EXCEPTION_LIST)](&chmapConfig);
			auto& chmapExceptionList = *(std::map<TCHAR, std::vector<TString>>*)shar_chmapExceptionList.get();

			//검색파일 경로
			auto shar_vecSearchPathList = m_Funcs[static_cast<size_t>(FUNC::GET_SEARCH_PATHS)](&chmapConfig);
			auto& vecSearchPathList = *(std::vector<TString>*)shar_vecSearchPathList.get();
			std::mutex mux;
			
			//검색 결과 Result.txt 파일에 넣기
			TString resultFilePath = CFileMgr::GetEXEFilePath() + _T("\\Result\\Result.txt");
			CFileMgr::CreateNewFile(resultFilePath);

			std::for_each(vecSearchPathList.begin(), vecSearchPathList.end()
				, [&](TString& _searchPath) {

					threads.push_back(std::thread([&]() {
						//TString _resultFilePath = CFileMgr::GetEXEFilePath() + _T("\\Result\\Result.txt");
						auto vec = CFileMgr::GetRecursiveFilesInDirectory(std::move(_searchPath), extentionVolume, std::move(chmapExceptionList));

						for (auto iter = vec.begin(); iter != vec.end();) {
							//lock 적용
							lock_and_call(CFileMgr::WriteData, mux, resultFilePath, (*iter++));
							//CFileMgr::WriteData(resultFilePath, (*iter++));
						}
						vec.clear();
						}));
				});

			for (size_t i = 0; i < threads.size(); ++i) {
				if (true == threads[i].joinable()) {
					threads[i].join();
				}
			}



			//1. Result.txt 파일 내에 있는 전체 파일Path 읽고, Vector에 담기 
			TString data = CFileMgr::ReadData(resultFilePath);
			std::vector<TString> paths = StringEditor::Split(data, '\n');
			std::map<TString, std::vector<const TString*> > chmapExtensions;
			for (const TString& _path : paths) {
				chmapExtensions[CFileMgr::GetExtention(_path)].emplace_back(&_path);
			}

			//2. 특정 파일 확장자가 minCnt개 이상 존재할 경우,  SendMail.txt 파일에 기록
			// minCnt 이하로 존재할 경우 함수 return
			for (auto iter = chmapExtensions.cbegin(); iter != chmapExtensions.cend(); ) {
				if (minCnt > (*iter).second.size() ) {
					chmapExtensions.erase(iter++); //삭제
				}
				else {
					++iter;
				}
			}
			if (chmapExtensions.size() == 0) {// minCnt 보다 많은 확장자가 없다면 return
				return nullptr;
			}
			/*
			SendMail.txt 양식
			이메일 타이틀: 랜섬웨어 발견! 
			의심 확장자 명: 
			FilePath목록 : 
			PATH1
			PATH2
			*/
			StringBuilder strBuil;
			TString sendMailPath = CFileMgr::GetEXEFilePath() + _T("\\Result\\SendMail.txt");
			CFileMgr::CreateNewFile(sendMailPath);
			int extensionCnt = 1;
			strBuil.Append(_T("의심 확장자 개수: ") + StringEditor::ToString(chmapExtensions.size()));
			for (std::pair<TString, std::vector<const TString*>> _pair : chmapExtensions) {
				strBuil.Append_endl(_T("\n\n\n"));
				strBuil.Append_endl(StringEditor::ToString(extensionCnt++) + _T(".의심 확장자 명: ") + _pair.first);
				strBuil.Append_endl(_T("파일 경로 목록"));
				std::vector<const TString*> filePaths = _pair.second;
				for (const TString* _filePath : filePaths) {
					strBuil.Append_endl(*_filePath);
				}
			}
			CFileMgr::WriteData(sendMailPath, strBuil.str());
			

			//추가 함수 로직
			//이후 다른 로직으로 C# SMTP 콘솔 프로그램 실행
			//SendMail.txt 메일 발송
			//auto sendExePath = _T("C:\\TAEKYUNG\\Dev\\Git\\RansomewareTracker\\RansomewareTrackerSMTPSender\\RansomewareTrackerSMTPSender\\bin\\Release\\net6.0\\RansomewareTrackerSMTPSender.exe");
			auto sendExePath = CFileMgr::GetEXEFilePath() + _T("\\SMTPSender\\RansomewareTrackerSMTPSender.exe");
			//CFileMgr::ExecuteFile(sendExePath);


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
			m_Funcs[static_cast<size_t>(FUNC::CREATE_EXCEPSION_LIST)](&chmapConfig);



			return nullptr;
		}));	
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::SIX)
		, [&](const void* _p_void) -> std::shared_ptr<void> {

			std::chrono::system_clock::time_point m_begin;
			std::string m_begin_time;
			double m_elapsed_time;
			std::chrono::system_clock::time_point m_end;
			std::string m_end_time;

			m_begin = std::chrono::system_clock::now();
			std::time_t begin_time = std::chrono::system_clock::to_time_t(m_begin);
			m_begin_time = std::ctime(&begin_time);

			m_Funcs[static_cast<size_t>(FUNC::SET_CONFIG_INI2)](nullptr);
			//config 설정 값 가져오기
			auto sharChmapConfig = m_Funcs[static_cast<size_t>(FUNC::GET_CONFIG_INI2)](nullptr);
			//config 정보 가져오기
			auto& chmapConfig = *(std::map<TString, std::map<TString, TString>>*)sharChmapConfig.get();
			//config 데이터를 기준으로 
			// 확장자의 글자수가 EXTENTION_VOLUMN 이상이고
			// && 확장자 당 파일의 수가 MIN_CNT 이상인 값 추출
			auto shar_chmapExceptionList = m_Funcs[static_cast<size_t>(FUNC::GET_EXCEPTION_LIST)](&chmapConfig);
			auto& chmapExceptionList = *(std::map<TCHAR, std::vector<TString>>*)shar_chmapExceptionList.get();
			m_Funcs[static_cast<size_t>(FUNC::CREATE_TRACKING_FILE)](&chmapConfig);

			m_end = std::chrono::system_clock::now();
			std::time_t end_time = std::chrono::system_clock::to_time_t(m_end);
			m_end_time = std::ctime(&end_time);
			m_elapsed_time = std::chrono::duration<double>(m_end - m_begin).count();

			std::tcout << _T("6번: 실행시간: ") << m_elapsed_time << std::endl;
			return nullptr;
		}));	
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::SEVEN)
		, [&](const void* _p_void) -> std::shared_ptr<void> {

			std::chrono::system_clock::time_point m_begin;
			std::string m_begin_time;
			double m_elapsed_time;
			std::chrono::system_clock::time_point m_end;
			std::string m_end_time;

			m_begin = std::chrono::system_clock::now();
			std::time_t begin_time = std::chrono::system_clock::to_time_t(m_begin);
			m_begin_time = std::ctime(&begin_time);



			m_Funcs[static_cast<size_t>(FUNC::SET_CONFIG_INI2)](nullptr);
			//config 설정 값 가져오기
			auto sharChmapConfig = m_Funcs[static_cast<size_t>(FUNC::GET_CONFIG_INI2)](nullptr);
			//config 정보 가져오기
			auto& chmapConfig = *(std::map<TString, std::map<TString, TString>>*)sharChmapConfig.get();
			//config 데이터를 기준으로 
			// 확장자의 글자수가 EXTENTION_VOLUMN 이상이고
			// && 확장자 당 파일의 수가 MIN_CNT 이상인 값 추출
			auto shar_chmapExceptionList = m_Funcs[static_cast<size_t>(FUNC::GET_EXCEPTION_LIST)](&chmapConfig);
			auto& chmapExceptionList = *(std::map<TCHAR, std::vector<TString>>*)shar_chmapExceptionList.get();
			m_Funcs[static_cast<size_t>(FUNC::CREATE_TRACKING_FILE2)](&chmapConfig);



			m_end = std::chrono::system_clock::now();
			std::time_t end_time = std::chrono::system_clock::to_time_t(m_end);
			m_end_time = std::ctime(&end_time);
			m_elapsed_time = std::chrono::duration<double>(m_end - m_begin).count();

			std::tcout << _T("7번: 실행시간: ") << m_elapsed_time << std::endl;
			return nullptr;
		}));	
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::EIGHT)
		, [&](const void* _p_void) -> std::shared_ptr<void> {

			std::chrono::system_clock::time_point m_begin;
			std::string m_begin_time;
			double m_elapsed_time;
			std::chrono::system_clock::time_point m_end;
			std::string m_end_time;

			m_begin = std::chrono::system_clock::now();
			std::time_t begin_time = std::chrono::system_clock::to_time_t(m_begin);
			m_begin_time = std::ctime(&begin_time);



			m_Funcs[static_cast<size_t>(FUNC::SET_CONFIG_INI2)](nullptr);
			//config 설정 값 가져오기
			auto sharChmapConfig = m_Funcs[static_cast<size_t>(FUNC::GET_CONFIG_INI2)](nullptr);
			//config 정보 가져오기
			auto& chmapConfig = *(std::map<TString, std::map<TString, TString>>*)sharChmapConfig.get();
			//config 데이터를 기준으로 
			// 확장자의 글자수가 EXTENTION_VOLUMN 이상이고
			// && 확장자 당 파일의 수가 MIN_CNT 이상인 값 추출
			auto shar_chmapExceptionList = m_Funcs[static_cast<size_t>(FUNC::GET_EXCEPTION_LIST)](&chmapConfig);
			auto& chmapExceptionList = *(std::map<TCHAR, std::vector<TString>>*)shar_chmapExceptionList.get();
			m_Funcs[static_cast<size_t>(FUNC::CREATE_TRACKING_FILE3)](&chmapConfig);



			m_end = std::chrono::system_clock::now();
			std::time_t end_time = std::chrono::system_clock::to_time_t(m_end);
			m_end_time = std::ctime(&end_time);
			m_elapsed_time = std::chrono::duration<double>(m_end - m_begin).count();

			std::tcout << _T("8번: 실행시간: ") << m_elapsed_time << std::endl;
			return nullptr;
		}));	
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::NINE)
		, [&](const void* _p_void) -> std::shared_ptr<void> {


			std::thread th1(m_PracFuncs[static_cast<size_t>(PRACTICE_FUNC::SIX)], nullptr);
			std::thread th2(m_PracFuncs[static_cast<size_t>(PRACTICE_FUNC::SEVEN)], nullptr);
			std::thread th3(m_PracFuncs[static_cast<size_t>(PRACTICE_FUNC::EIGHT)],nullptr);

			th1.join();
			th2.join();
			th3.join();
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

	default:
		break;
	}

	return 0;
}

void CPractice_1::Release(void) noexcept
{
}


