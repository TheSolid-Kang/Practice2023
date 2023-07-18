#include "CLogger.h"
#include <chrono>

IMPLEMENT_SINGLETON(CLogger)

void CLogger::Log(const LOG_LEVEL& _level, const TString& _message) 
{
    std::chrono::system_clock::time_point beginPoint;
    beginPoint = std::chrono::system_clock::now();
    std::time_t begin_time = std::chrono::system_clock::to_time_t(beginPoint);

    TString strBeginTime;
#if UNICODE
    std::string str = std::ctime(&begin_time);
    strBeginTime.assign(str.begin(), str.end());
#else
    strBeginTime = std::ctime(&begin_time);
#endif;
    size_t index = strBeginTime.find(_T("\n"));
    if (index) {
        strBeginTime = _T(" [") + strBeginTime;
        strBeginTime.erase(index);
        strBeginTime += _T("] ");
    }

    _Log(_level, strBeginTime  + _message);
    //lock_and_call(_Log, m_mutex, _level, strBeginTime + _message);
}

void CLogger::LogBegin(const TString& _message)
{
	LOG_LEVEL logLevel = LOG_LEVEL::L_INFO;
	Log(logLevel, (_T(" (BEGIN) ") + _message));
}

void CLogger::LogEnd(const TString& _message)
{
	Log(LOG_LEVEL::L_INFO, (_T(" (END) ") + _message));
}

void CLogger::_Log(const LOG_LEVEL& _level, const TString& _message)
{
    SetLogLvel(_level);
    switch (_level)
    {
    case LOG_LEVEL::L_ERROR:
        Error(_message);
        break;
    case LOG_LEVEL::L_WORAN:
        Warn(_message);
        break;
    case LOG_LEVEL::L_INFO:
        Info(_message);
        break;
    case LOG_LEVEL::L_DEBUG:
        Debug(_message);
        break;
    }
}

void CLogger::Error(const TString& _message)
{
    if (m_logLevel >= LOG_LEVEL::L_ERROR) {
        TString msg = _T("[ERROR]: ") + _message;
        std::tcout << msg << std::endl;
        WriteData(m_logFilePath, msg);
    }
}

void CLogger::Warn(const TString& _message)
{
    if (m_logLevel >= LOG_LEVEL::L_WORAN) {
        TString msg = _T("[WARNING]: ") + _message;
        std::tcout << msg << std::endl;
        WriteData(m_logFilePath, msg);
    }
}

void CLogger::Info(const TString& _message)
{
    if (m_logLevel >= LOG_LEVEL::L_INFO) {
        TString msg = _T("[INFO]: ") + _message;
        std::tcout << msg << std::endl;
        WriteData(m_logFilePath, msg);
    }
}

void CLogger::Debug(const TString& _message)
{
    if (m_logLevel >= LOG_LEVEL::L_DEBUG) {
        TString msg = _T("[DEBUG]: ") + _message;
        std::tcout << msg << std::endl;
        WriteData(m_logFilePath, msg);
    }
}
