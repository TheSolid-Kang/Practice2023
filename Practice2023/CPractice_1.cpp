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
				, _T("2. ConnectionString 확인")
				, _T("3. 입고번호 별 SP 호출 쿼리 작성")
				, _T("4. 폴더 내 파일 사이즈 확인")
				, _T("5. 폴더 내 파일명 목록 작성")
				, _T("99. EXIT"));
			std::for_each(titles.cbegin(), titles.cend(), [&](const TString& _title) { std::tcout << _title << std::endl; });
			return nullptr;
		}));
}

void CPractice_1::InitPracticeFunc(void)
{
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::ONE)
		, [&](const void* _p_void) -> std::shared_ptr<void> {

			int n3 = 3;
			int r2;
			r2 = !n3;
			std::tcout << r2 << std::endl;



			auto path = CFileMgr::GetOpenFileDialg();
			auto content = CFileMgr::ReadData(path);
			auto vec = StringEditor::Split(content, '\n');
			vec.erase(remove(vec.begin(), vec.end(), _T("\r")), vec.end());
			std::tcout << vec.size() << std::endl;
			vec.shrink_to_fit();
			StringBuilder strBuil;
			auto iter = vec.begin();
			while (iter != vec.end()) {
				TString str = (*iter++);
				size_t space_idx = str.find_first_of(_T(" "));
				size_t colon_idx = str.find_first_of(_T(":"));
				size_t testament_idx;
				for (size_t i = 0; i < str.size(); ++i) {
					if (str[i] >= 49 && str[i] <= 58) {
						testament_idx = i;
						break;
					}
				}

				TString Testament, Chapter, Verse, Descript;
				Testament = str.substr(0, testament_idx);
				Chapter = str.substr(testament_idx, colon_idx  - testament_idx);
				Verse = str.substr(colon_idx + 1, space_idx  - colon_idx);
				Descript = str.substr(space_idx + 1, str.size() - space_idx - 2) ; //\r 없애기 위해 -2 함.

				strBuil.Append(_T("INSERT INTO _TFBible(Testament, Chapter, Verse, Descript) VALUES("));
				strBuil.Append(_T("'") + Testament + _T("'"));
				strBuil.Append(_T(",") + Chapter);
				strBuil.Append(_T(",") + Verse);
				strBuil.Append(_T(",'") + Descript + _T("'"));
				strBuil.Append_endl(_T(");"));
			}
			CFileMgr::WriteData(CFileMgr::GetEXEFilePath() + _T("/BibleInsertQuery.txt"), strBuil.str());
			std::tcout << strBuil.str() << std::endl;

			return nullptr;
		}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::TWO)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			TString filePath = CFileMgr::GetOpenFileDialg();
			auto vec = StringEditor::Split( CFileMgr::ReadData(filePath), _T('\n'));
			std::map<TString, int> map;
			std::for_each(vec.begin(), vec.end(), [&](TString _str) {
				//if (TString::npos != _str.find(_T("==note:"))) 
				if (TString::npos != _str.find(_T("Stack == 2"))) 
					map[_str]++;
				});
			for (auto pair : map) {
				std::tcout << _T("  Cnt:") << pair.second << _T("   ConnectionString: ")  << pair.first << std::endl;
			}

			return nullptr;
		}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::THREE)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			TString strIncomeNum = CFileMgr::ReadData(_T("C:\\TAEKYUNG\\2024\\01\\240110\\입고번호 목록.txt"));
			std::vector<TString> incomeNums = StringEditor::Split(strIncomeNum, '\n');
			incomeNums.erase(remove(incomeNums.begin(), incomeNums.end(), _T("\r")), incomeNums.end());

			TString front = _T("EXEC yw_SWHIncomeInspectionQuery @xmlDocument = N'<ROOT>\n");
			front += _T("<DataBlock1>\n");
			front += _T("	<WorkingTag>U</WorkingTag>\n");
			front += _T("	<IDX_NO>1</IDX_NO>\n");
			front += _T("	<Status>0</Status>\n");
			front += _T("	<DataSeq>1</DataSeq>\n");
			front += _T("	<Selected>1</Selected>\n");
			front += _T("	<TABLE_NAME>DataBlock1</TABLE_NAME>\n");
			front += _T("	<IsChangedMst>1</IsChangedMst>\n");
			front += _T("	<INCOME_NO>");

			TString back = _T("</INCOME_NO> </DataBlock1> </ROOT>'");
			back += _T(", @xmlFlags = 2, @ServiceSeq = 68020190, @WorkingTag = N'', @CompanySeq = 1, @LanguageSeq = 1, @UserSeq = 9669, @PgmSeq = 68020148");

			std::for_each(incomeNums.begin(), incomeNums.end(), [&](TString& _incomeNum) { _incomeNum = (front + _incomeNum + back); });

			return nullptr;
		}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::FOUR)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			TString exePath = CFileMgr::GetEXEFilePath();
			TString dirPath = exePath + _T("\\Config");
			TString configIniPath = dirPath + _T("\\Config.ini");

			auto filePath = CINIMgr::GetPrivateProfileString_INI(_T("PATH"), _T("SEARCH_DIR_PATH"), configIniPath);
			std::vector<CFileMgr::TString> files = CFileMgr::GetRecursiveFilesInDirectory(filePath);

			__int64 totSize = 0;
			for (auto& file : files)
			{
				__int64 fileSize = CFileMgr::GetFileSize(file);
				if (fileSize > 0)
					totSize += CFileMgr::GetFileSize(file);
				else
					std::tcout << file << _T(" == 0") << std::endl;

			}

			StringBuilder strBuil;
			strBuil.Append(_T("전체 바이트 사이즈: "));
			strBuil.Append_endl(StringEditor::ToString(totSize));
			strBuil.Append(_T("전체 파일 개수: "));
			strBuil.Append_endl(StringEditor::ToString(files.size()));

			CFileMgr::WriteData(exePath + _T("\\SaveData.txt"), strBuil.str());

			return nullptr;
		}));
	m_PracFuncs.emplace(std::make_pair(static_cast<size_t>(PRACTICE_FUNC::FIVE)
		, [&](const void* _p_void) -> std::shared_ptr<void> {
			TString exePath = CFileMgr::GetEXEFilePath();
			TString dirPath = exePath + _T("\\Config");
			TString configIniPath = dirPath + _T("\\Config.ini");
			TString fileNameList = exePath + _T("\\FileNameList.txt");

			auto filePath = CINIMgr::GetPrivateProfileString_INI(_T("PATH"), _T("SEARCH_DIR_PATH"), configIniPath);
			std::vector<CFileMgr::TString> files = CFileMgr::GetRecursiveFilesInDirectory(filePath);

			for (auto& _file : files)
			{
				CFileMgr::WriteData(fileNameList, _file);
			}
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


