#pragma once
#include "bunny/types.h"
namespace bunny {
  class ToDebugString {
   public:
    virtual bu_str to_debug_string() const;
  };
}  // namespace bunny

inline std::ostream& operator<<(std::ostream& os, const bunny::ToDebugString& str_rep) {
  os << str_rep.to_debug_string();
  return os;
}