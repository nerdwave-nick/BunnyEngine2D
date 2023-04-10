#pragma once

#include "bunny/typedefs.h"

#include <array>
#include <initializer_list>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

namespace bunny {
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

  template<typename T, u32 N>
  using bu_arr = std::array<T, N>;

  template<class Key, class T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>, class Allocator = std::allocator<std::pair<const Key, T>>>
  using bu_dict = std::unordered_map<Key, T, Hash, KeyEqual, Allocator>;

  template<typename T>
  using bu_init_list = std::initializer_list<T>;

  template<typename T1, typename T2>
  using bu_pair = std::pair<T1, T2>;

  // using bu_vec2 = math::vector<2>;
  // using bu_vec3 = math::vector<3>;
  // using bu_vec4 = math::vector<4>;
  // using bu_mat2 = math::matrix<2, 2>;
  // using bu_mat3 = math::matrix<3, 3>;
  // using bu_mat4 = math::matrix<4, 4>;

}  // namespace bunny
