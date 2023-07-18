#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <tchar.h>
#include <Windows.h>
#include <mutex>
#include <functional>
#include "DEFAULT_MGR.h"
#include "Headers.h"
enum class LOG_LEVEL : int {
    L_ERROR = 1,
    L_WORAN = 2,
    L_INFO = 3,
    L_DEBUG = 4
};
class CLogger {
private:
#if UNICODE 
    using TString = std::wstring;
    using tifstream = std::wifstream;
    using tofstream = std::wofstream;
#define tcout  wcout
#define tcin  wcin
#else
    using TString = std::string;
    using tifstream = std::ifstream;
    using tofstream = std::ofstream;
#define tcout  cout
#define tcin  cin
#endif;

    DECLARE_SINGLETON(CLogger)
private:
    CLogger() : m_logLevel(LOG_LEVEL::L_INFO), m_fileStream(GetEXEFilePath() + _T("\\Log.txt"), std::ios::out), m_logFilePath(GetEXEFilePath() + _T("\\Log.txt")) {}
private:
    LOG_LEVEL m_logLevel;
    tofstream m_fileStream;
    std::mutex m_mutex;
    TString m_logFilePath;

#pragma endregion
private:
    template<typename Func, typename Mutex, typename Ptr, typename Ptr2>
    constexpr decltype(auto) lock_and_call(Func _func, Mutex& _mutex, Ptr _ptr, Ptr2 _ptr2) noexcept;
    void SetLogLvel(LOG_LEVEL _level) {
        m_logLevel = _level;
    }

    TString GetEXEFilePath() {
        TCHAR path[MAX_PATH] = { 0, };
        GetModuleFileName(NULL, path, MAX_PATH);
        TString exe_path = path;
        exe_path = exe_path.substr(0, exe_path.find_last_of(_T("\\/")));
        return exe_path;
    }
    void WriteData(const TString& _filePath, const TString& _saveData) {
        tofstream fout; //������ ���ڿ� ������ �ؽ�Ʈ ����	
        fout.open(_filePath, std::ios_base::out | std::ios_base::app);
        fout << _saveData << std::endl;
        fout.close();
    }

public:
#pragma region Log �Է�(public)
    void Log(const LOG_LEVEL& _level, const TString& _message);
    void LogBegin(const TString& _message);
    void LogEnd(const TString& _message);

#pragma region Log �Է�(private)
    void _Log(const LOG_LEVEL& _level, const TString& _message);
    void Error(const TString& _message);
    void Warn(const TString& _message);
    void Info(const TString& _message);
    void Debug(const TString& _message);
#pragma endregion 



};

template<typename Func, typename Mutex, typename Ptr, typename Ptr2>
inline constexpr decltype(auto) CLogger::lock_and_call(Func _func, Mutex& _mutex, Ptr _ptr, Ptr2 _ptr2) noexcept
{

}
