#include "Headers.h"
#include "CPracticeMgr.h"
#include "CPractice.h"
#include "CHashMap.h"

int main() {

	auto pInstance = CPracticeMgr::GetInstance();
	auto pPractice = (*pInstance).GetPractice();

	//(*pPractice).Execute();
	CHashMap<TString, TString> map;
	map.Put(_T("하나"), _T("1"));
	map.Put(_T("둘"), _T("2"));
	map.Put(_T("셋"), _T("3"));

	std::tcout << map.Get(_T("하나")) << std::endl;
	std::tcout << map.Get(_T("둘")) << std::endl;
	std::tcout << map.Get(_T("셋")) << std::endl;

	return NULL;
}