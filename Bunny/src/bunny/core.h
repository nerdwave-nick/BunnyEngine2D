#pragma once

// Platform detection
#ifdef _WIN32
  // Windows x64/x86 */
  #ifdef _WIN64
    // Windows x64
    #define BU_PLATFORM_WINDOWS
  #else
    // Windows x86
    #error "x86 Builds are not supported!"
  #endif
#elif defined(__APPLE__) || defined(__MACH__)
  #include <TargetConditionals.h>
  // TARGET_OS_MAC exists on all the platforms
  // check all of them in this order
  #if TARGET_IPHONE_SIMULATOR == 1
    #error "IOS simulator is not supported!"
  #elif TARGET_OS_IPHONE == 1
    #define BU_PLATFORM_IOS
    #error "IOS is not supported!"
  #elif TARGET_OS_MAC == 1
    #define BU_PLATFORM_MACOS
    #error "MacOS is not supported!"
  #else
    #error "Unknown Apple platform!"
  #endif
// check __ANDROID__ before __linux__
// since android is based on the linux kernel
#elif defined(__ANDROID__)
  #define BU_PLATFORM_ANDROID
  #error "Android is not supported!"
#elif defined(__linux__)
  #define BU_PLATFORM_LINUX
  #error "Linux is not supported!"
#else
  // Unknown compiler/platform */
  #error "Unknown platform!"
#endif
// End of platform detection


// DLL support
#ifdef BU_PLATFORM_WINDOWS
  #if BU_DYNAMIC_LINK
    #ifdef BU_BUILD_DLL
      #define BUNNY_API __declspec(dllexport)
    #else
      #define BUNNY_API __declspec(dllimport)
    #endif
  #else
    #define BUNNY_API
  #endif
#else
  #error "Bunny only supports Windows!"
#endif
// End of DLL support

#ifdef BU_DEBUG
  #define BU_ENABLE_ASSERTS
#endif

#ifdef BU_ENABLE_ASSERTS
  #define BU_ASSERT(x, ...)                                        \
    {                                                              \
      if (!(x)) {                                                  \
        ::Bunny::Log::Error("Assertion Failed: {0}", __VA_ARGS__); \
        __debugbreak();                                            \
      }                                                            \
    }
  #define BU_CORE_ASSERT(x, ...)                                         \
    {                                                                    \
      if (!(x)) {                                                        \
        ::Bunny::Log::Core::Error("Assertion Failed: {0}", __VA_ARGS__); \
        __debugbreak();                                                  \
      }                                                                  \
    }
  #define BU_CORE_ASSERT_MESSAGE(m, x, ...)                              \
    {                                                                    \
      if (!(x)) {                                                        \
        ::Bunny::Log::Core::Error("Assertion Failed: {0}", __VA_ARGS__); \
        __debugbreak();                                                  \
      } else {                                                           \
        ::Bunny::Log::Core::Info(m);                                     \
      }                                                                  \
    }
#else
  #define BU_ASSERT(x, ...)
  #define BU_CORE_ASSERT(x, ...)
#endif

#define BIT(x)                     (1 << x)

#define BU_BIND_EVENT_FN(fn)       std::bind(&fn, this, std::placeholders::_1)
#define BU_AUTO_DISPATCH(Cl, type) dispatcher.Dispatch<type##Event>(BU_BIND_EVENT_FN(Cl::On##type))

// #include "bunny/core/entry-point.h"
#include "bunny/core/input.h"
#include "bunny/core/key-codes.h"
#include "bunny/core/mouse-button-codes.h"
#include "bunny/core/random.h"
#include "bunny/core/time.h"
#include "bunny/core/typedefs.h"
#include "bunny/core/types.h"
