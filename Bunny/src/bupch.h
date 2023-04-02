#pragma once
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#ifdef BU_PLATFORM_WINDOWS
  #ifdef _WIN32
    #ifndef NOMINMAX
      #define NOMINMAX  // prevent windows redefining min/max
    #endif
  #endif
  #include <Windows.h>
#endif
