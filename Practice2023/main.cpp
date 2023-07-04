#include "Headers.h"
#include "CPracticeMgr.h"
#include "CPractice.h"
#include "CHashMap.h"
#include "CFileMgr.h"
#include "CINIMgr.h"

int main() {

	auto pInstance = CPracticeMgr::GetInstance();
	auto pPractice = (*pInstance).GetPractice();

	//TString path = _T("C:\\");

	//std::string path = "C:\\MinGW\\";
	//TString path = _T("C:\\TAEKYUNG\\Dev\\CPP");
	TString path = _T("C:\\");
	auto lists = CFileMgr::GetRecursiveFilesInDirectory(path);
	std::map<TString, std::list<TString>> map;
	std::for_each(lists.begin(), lists.end()
		, [&](const TString& _path) {
			TString extension = CFileMgr::GetExtention(_path);//path.extension().wstring();

			//map.emplace(extension, map[extension]);
			map[extension].emplace_back(_path);
		}
	);

	lists.clear();
	map.clear();

	return NULL;
}