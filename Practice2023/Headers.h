#pragma once
#include <Windows.h>

#include <iostream>

#include <string>
#include <tchar.h>

#include <array>
#include <vector>

#include <list>

#include <set>
#include <map>

#include <functional>

#include <algorithm>

#include <type_traits>

#if UNICODE 
using TString = std::wstring;
#define tcout  wcout
#define tcin  wcin
#else
using TString = std::string;
#define tcout  cout
#define tcin  cin
#endif;

#include "CIO.h"
