#pragma once
#include "Headers.h"
#include "DEFAULT_MGR.h"
#include "Enum.h"


class CPractice;
class CPracticeMgr
{
private:
	CPracticeMgr();	
	~CPracticeMgr();
	DECLARE_SINGLETON(CPracticeMgr);

private:
	CPractice* m_pPractice;

public:
	void SetPractice(const int& _practiceNum = static_cast<int>(PRACTICE_NUM::PN_1)) noexcept;
	CPractice* GetPractice(void) { return m_pPractice; };



};

