#pragma once
#include <memory>

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

#define BIT(x) (1 << x)

// #define BU_AUTO_DISPATCH(Cl, type) dispatcher.Dispatch<type##Event>(BU_BIND_EVENT_FN(Cl::On##type))
#define BU_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#include "bunny/core/typedefs.h"
#include "bunny/math/math.h"

#include <array>
#include <initializer_list>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>
namespace Bunny {
  /// STD TYPE ABSTRACTION ///
  template<typename T>
  using Scope = std::unique_ptr<T>;
  template<typename T, typename... Args>
  constexpr Scope<T> CreateScope(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
  }
  template<typename T>
  using Ref = std::shared_ptr<T>;
  template<typename T, typename... Args>
  constexpr Ref<T> CreateRef(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }

  using bu_str      = std::string;
  using bu_str_view = std::string_view;
  using bu_sstream  = std::stringstream;

  template<typename T>
  using bu_vec = std::vector<T>;

  template<typename T>
  using bu_deque = std::deque<T>;

  template<typename T, class Container = bu_deque<T>>
  using bu_stack = std::stack<T, Container>;

  template<typename T, bu_u32 N>
  using bu_arr = std::array<T, N>;

  template<class Key, class T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>, class Allocator = std::allocator<std::pair<const Key, T>>>
  using bu_dict = std::unordered_map<Key, T, Hash, KeyEqual, Allocator>;

  template<typename T>
  using bu_init_list = std::initializer_list<T>;

  template<typename T1, typename T2>
  using bu_pair = std::pair<T1, T2>;

  using bu_vec2 = math::vector<2>;
  using bu_vec3 = math::vector<3>;
  using bu_vec4 = math::vector<4>;
  using bu_mat2 = math::matrix<2, 2>;
  using bu_mat3 = math::matrix<3, 3>;
  using bu_mat4 = math::matrix<4, 4>;

}  // namespace Bunny

// #include "bunny/core/Timestep.h"