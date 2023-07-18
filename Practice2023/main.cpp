#include "Headers.h"
#include "CPracticeMgr.h"
#include "CPractice.h"
#include "CHashMap.h"
#include "CFileMgr.h"
#include "CINIMgr.h"


const int EXIT = 99;
HANDLE hMutex = NULL;
bool IsRun(); 
void PrintTitle(void);

int main() {
	//::ReleaseMutex(hMutex);
	if (true == IsRun()) {//프로그램 실행중인 경우 종료
		return NULL;
	}

#if UNICODE
	//SetConsoleOutputCP(65001);
	//std::locale::global(std::locale("kor"));
	//std::locale::global(std::locale(".UTF-8"));
#else
	SetConsoleOutputCP(949);
	//std::locale::global(std::locale());
#endif

	auto& rInstance = *CPracticeMgr::GetInstance();

	do {
		PrintTitle();
		int num = CIO::ask_and_return_integer();
		if (EXIT == num)
			break;
		rInstance.SetPractice(num);
	} while (rInstance.Execute() != -1);
	return NULL;
}


void PrintTitle(void)
{
	std::list<TString> list_title;


	list_title.emplace_back(_T(""));
	list_title.emplace_back(_T("1. Practice: 랜섬웨어 검출 프로그램"));
	list_title.emplace_back(_T("2. Practice: "));
	list_title.emplace_back(_T(""));
	list_title.emplace_back(_T(""));
	list_title.emplace_back(_T("99.EXIT"));


	system("pause");
	system("cls");
	std::for_each(list_title.cbegin(), list_title.cend(), [](const TString& _title) {std::tcout << _title << std::endl; });
}

bool IsRun()
{
	TString ProgMutex = CFileMgr::GetEXEFilePath();
	hMutex = ::CreateMutex(NULL, FALSE, _T("Practice2023"));
	if (NULL == hMutex) {
		::MessageBox(NULL, _T("뮤텍스 생성 실패"), _T("알림"), MB_OK);
		return false;
	}

	if (ERROR_ALREADY_EXISTS == ::GetLastError()) {
		::MessageBox(NULL, _T("이미 실행중입니다."), _T("알림"), MB_OK);
		::CloseHandle(hMutex);
		hMutex = INVALID_HANDLE_VALUE;
		::ReleaseMutex(hMutex);

		return true;
	}
	else {
		return false;
	}
}
