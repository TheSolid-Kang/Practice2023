#include "Headers.h"
#include "CPracticeMgr.h"
#include "CPractice.h"
#include "CHashMap.h"
#include "CFileMgr.h"
#include "CINIMgr.h"


const int EXIT = 99;
void PrintTitle(void);

int main() {
#if UNICODE
	//SetConsoleOutputCP(65001);
	//std::locale::global(std::locale("kor"));
	std::locale::global(std::locale(".UTF-8"));
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
	std::for_each(list_title.cbegin(), list_title.cend(), [](auto& _title) {std::tcout << _title << std::endl; });
}
