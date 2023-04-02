#pragma once
#include "bunny/core/typedefs.h"
namespace Bunny {
  namespace math {
    template<bu_i32 N>
    struct vector;

    namespace vec {
      template<bu_i32 N>
      vector<N> inline normalize(vector<N> const& a);
    }

    template<bu_i32 N>
    struct vector {
     private:
      bu_f32 values[N];

     public:
      bu_f32& operator[](bu_i32 i) {
        return values[i];
      }
      bu_f32 const& operator[](bu_i32 i) const {
        return values[i];
      }

      vector<N>& operator=(const vector<N>& other) = default;
      vector<N>& operator=(vector<N>&& other)      = default;

      // comparison operators for real equality
      bool operator==(vector<N> const& other) const {
        bool b = true;
        for (int i = 0; i < N; i++) { b &= (other[i] == values[i]); }
        return b;
      }
      bool operator!=(vector<N> const& other) const {
        return !((*this) == other);
      }
      const bu_f32* value_ptr() const {
        return values;
      }
      bu_f32* value_ptr() {
        return values;
      }
      // functional operators - memberwise
      vector<N> operator-() const {
        vector<N> res;
        for (int i = 0; i < N; i++) { res[i] = -values[i]; }
        return res;
      }
      vector<N>& operator+=(bu_f32 f) {
        for (int i = 0; i < N; i++) { values[i] += f; }
        return *this;
      }
      vector<N>& operator-=(bu_f32 f) {
        for (int i = 0; i < N; i++) { values[i] -= f; }
        return *this;
      }
      vector<N>& operator*=(bu_f32 f) {
        for (int i = 0; i < N; i++) { values[i] *= f; }
        return *this;
      }
      vector<N>& operator/=(bu_f32 f) {
        for (int i = 0; i < N; i++) { values[i] /= f; }
        return *this;
      }
      friend vector<N> operator+(vector<N> const& a, bu_f32 b) {
        return vector<N>(a) += b;
      }
      friend vector<N> operator+(bu_f32 b, vector<N> const& a) {
        return vector<N>(a) += b;
      }
      friend vector<N> operator-(vector<N> const& a, bu_f32 b) {
        return vector<N>(a) -= b;
      }
      friend vector<N> operator-(bu_f32 b, vector<N> const& a) {
        return vector<N>(a) -= b;
      }
      friend vector<N> operator*(vector<N> const& a, bu_f32 b) {
        return vector<N>(a) *= b;
      }
      friend vector<N> operator*(bu_f32 b, vector<N> const& a) {
        return vector<N>(a) *= b;
      }
      friend vector<N> operator/(vector<N> const& a, bu_f32 b) {
        return vector<N>(a) /= b;
      }
      friend vector<N> operator/(bu_f32 b, vector<N> const& a) {
        return vector<N>(a) /= b;
      }
      vector<N>& operator+=(vector<N> const& other) {
        for (int i = 0; i < N; i++) { values[i] += other[i]; }
        return (*this);
      }
      vector<N>& operator-=(vector<N> const& other) {
        for (int i = 0; i < N; i++) { values[i] -= other[i]; }
        return (*this);
      }
      friend vector<N> operator+(vector<N> const& a, vector<N> const& b) {
        return vector<N>(a) += b;
      }
      friend vector<N> operator-(vector<N> const& a, vector<N> const& b) {
        return vector<N>(a) -= b;
      }
      friend bu_f32* value_ptr(vector<N> const& vec);

      // mathematical operations
      bu_f32 length() const {
        bu_f32 tmp = 0;
        for (int i = 0; i < N; i++) { tmp += values[i] * values[i]; }
        return sqrtf(tmp);
      }

      vector<N> normalized() const {
        return vec::normalize(*this);
      }

      // constructors
      vector<N>() :
          values{0} {};
      vector<N>(bu_f32 v) :
          values{v} {};
      vector<N>(const vector<N>& other) = default;
      vector<N>(vector<N>&& other)      = default;
      ~vector<N>()                      = default;
    };

    template<>
    struct vector<2> {
      union {
        struct {
          bu_f32 x, y;
        };
        bu_f32 values[2];
      };
      bu_f32& operator[](bu_i32 i) {
        return values[i];
      }
      bu_f32 const& operator[](bu_i32 i) const {
        return values[i];
      }

      vector<2>& operator=(const vector<2>& other) = default;
      vector<2>& operator=(vector<2>&& other)      = default;

      // comparison operators for real equality
      bool operator==(vector<2> const& other) const {
        bool b = true;
        for (int i = 0; i < 2; i++) { b &= (other[i] == values[i]); }
        return b;
      }
      bool operator!=(vector<2> const& other) const {
        return !((*this) == other);
      }
      const bu_f32* value_ptr() const {
        return values;
      }
      bu_f32* value_ptr() {
        return values;
      }
      // functional operators - memberwise
      vector<2> operator-() const {
        vector<2> res;
        for (int i = 0; i < 2; i++) { res[i] = -values[i]; }
        return res;
      }
      vector<2>& operator+=(bu_f32 f) {
        for (int i = 0; i < 2; i++) { values[i] += f; }
        return *this;
      }
      vector<2>& operator-=(bu_f32 f) {
        for (int i = 0; i < 2; i++) { values[i] -= f; }
        return *this;
      }
      vector<2>& operator*=(bu_f32 f) {
        for (int i = 0; i < 2; i++) { values[i] *= f; }
        return *this;
      }
      vector<2>& operator/=(bu_f32 f) {
        for (int i = 0; i < 2; i++) { values[i] /= f; }
        return *this;
      }
      friend vector<2> operator+(vector<2> const& a, bu_f32 b) {
        return vector<2>(a) += b;
      }
      friend vector<2> operator+(bu_f32 b, vector<2> const& a) {
        return vector<2>(a) += b;
      }
      friend vector<2> operator-(vector<2> const& a, bu_f32 b) {
        return vector<2>(a) -= b;
      }
      friend vector<2> operator-(bu_f32 b, vector<2> const& a) {
        return vector<2>(a) -= b;
      }
      friend vector<2> operator*(vector<2> const& a, bu_f32 b) {
        return vector<2>(a) *= b;
      }
      friend vector<2> operator*(bu_f32 b, vector<2> const& a) {
        return vector<2>(a) *= b;
      }
      friend vector<2> operator/(vector<2> const& a, bu_f32 b) {
        return vector<2>(a) /= b;
      }
      friend vector<2> operator/(bu_f32 b, vector<2> const& a) {
        return vector<2>(a) /= b;
      }
      vector<2>& operator+=(vector<2> const& other) {
        for (int i = 0; i < 2; i++) { values[i] += other[i]; }
        return (*this);
      }
      vector<2>& operator-=(vector<2> const& other) {
        for (int i = 0; i < 2; i++) { values[i] -= other[i]; }
        return (*this);
      }
      friend vector<2> operator+(vector<2> const& a, vector<2> const& b) {
        return vector<2>(a) += b;
      }
      friend vector<2> operator-(vector<2> const& a, vector<2> const& b) {
        return vector<2>(a) -= b;
      }
      friend bu_f32* value_ptr(vector<2> const& vec);

      // mathematical operations
      bu_f32 length() const {
        bu_f32 tmp = 0;
        for (int i = 0; i < 2; i++) { tmp += values[i] * values[i]; }
        return sqrtf(tmp);
      }

      vector<2> normalized() const {
        return vec::normalize(*this);
      }

      // constructors
      vector() :
          values{0} {};
      vector(bu_f32 v) :
          values{v} {};
      vector(bu_f32 x, bu_f32 y) :
          values{x, y} {}
      vector(const vector<2>& other) = default;
      vector(vector<2>&& other)      = default;

      ~vector() = default;
    };

    template<>
    struct vector<3> {
      union {
        struct {
          bu_f32 x, y, z;
        };
        bu_f32 values[3];
      };
      bu_f32& operator[](bu_i32 i) {
        return values[i];
      }
      bu_f32 const& operator[](bu_i32 i) const {
        return values[i];
      }

      vector<3>& operator=(const vector<3>& other) = default;
      vector<3>& operator=(vector<3>&& other)      = default;

      // comparison operators for real equality
      bool operator==(vector<3> const& other) const {
        bool b = true;
        for (int i = 0; i < 3; i++) { b &= (other[i] == values[i]); }
        return b;
      }
      bool operator!=(vector<3> const& other) const {
        return !((*this) == other);
      }
      const bu_f32* value_ptr() const {
        return values;
      }
      bu_f32* value_ptr() {
        return values;
      }
      // functional operators - memberwise
      vector<3> operator-() const {
        vector<3> res;
        for (int i = 0; i < 3; i++) { res[i] = -values[i]; }
        return res;
      }
      vector<3>& operator+=(bu_f32 f) {
        for (int i = 0; i < 3; i++) { values[i] += f; }
        return *this;
      }
      vector<3>& operator-=(bu_f32 f) {
        for (int i = 0; i < 3; i++) { values[i] -= f; }
        return *this;
      }
      vector<3>& operator*=(bu_f32 f) {
        for (int i = 0; i < 3; i++) { values[i] *= f; }
        return *this;
      }
      vector<3>& operator/=(bu_f32 f) {
        for (int i = 0; i < 3; i++) { values[i] /= f; }
        return *this;
      }
      friend vector<3> operator+(vector<3> const& a, bu_f32 b) {
        return vector<3>(a) += b;
      }
      friend vector<3> operator+(bu_f32 b, vector<3> const& a) {
        return vector<3>(a) += b;
      }
      friend vector<3> operator-(vector<3> const& a, bu_f32 b) {
        return vector<3>(a) -= b;
      }
      friend vector<3> operator-(bu_f32 b, vector<3> const& a) {
        return vector<3>(a) -= b;
      }
      friend vector<3> operator*(vector<3> const& a, bu_f32 b) {
        return vector<3>(a) *= b;
      }
      friend vector<3> operator*(bu_f32 b, vector<3> const& a) {
        return vector<3>(a) *= b;
      }
      friend vector<3> operator/(vector<3> const& a, bu_f32 b) {
        return vector<3>(a) /= b;
      }
      friend vector<3> operator/(bu_f32 b, vector<3> const& a) {
        return vector<3>(a) /= b;
      }
      vector<3>& operator+=(vector<3> const& other) {
        for (int i = 0; i < 3; i++) { values[i] += other[i]; }
        return (*this);
      }
      vector<3>& operator-=(vector<3> const& other) {
        for (int i = 0; i < 3; i++) { values[i] -= other[i]; }
        return (*this);
      }
      friend vector<3> operator+(vector<3> const& a, vector<3> const& b) {
        return vector<3>(a) += b;
      }
      friend vector<3> operator-(vector<3> const& a, vector<3> const& b) {
        return vector<3>(a) -= b;
      }
      friend bu_f32* value_ptr(vector<3> const& vec);

      // mathematical operations
      bu_f32 length() const {
        bu_f32 tmp = 0;
        for (int i = 0; i < 3; i++) { tmp += values[i] * values[i]; }
        return sqrtf(tmp);
      }

      vector<3> normalized() const {
        return vec::normalize(*this);
      }

      // constructors
      vector() :
          values{0} {};
      vector(bu_f32 v) :
          values{v} {};
      vector(bu_f32 a, bu_f32 b, bu_f32 c) :
          values{a, b, c} {}
      vector(const vector<3>& other) = default;
      vector(vector<3>&& other)      = default;
      ~vector()                      = default;
    };

    template<>
    struct vector<4> {
      union {
        struct {
          bu_f32 x, y, z, w;
        };
        bu_f32 values[4];
      };
      bu_f32& operator[](bu_i32 i) {
        return values[i];
      }
      bu_f32 const& operator[](bu_i32 i) const {
        return values[i];
      }

      vector<4>& operator=(const vector<4>& other) = default;
      vector<4>& operator=(vector<4>&& other)      = default;

      // comparison operators for real equality
      bool operator==(vector<4> const& other) const {
        bool b = true;
        for (int i = 0; i < 4; i++) { b &= (other[i] == values[i]); }
        return b;
      }
      bool operator!=(vector<4> const& other) const {
        return !((*this) == other);
      }
      const bu_f32* value_ptr() const {
        return values;
      }
      bu_f32* value_ptr() {
        return values;
      }
      // functional operators - memberwise
      vector<4> operator-() const {
        vector<4> res;
        for (int i = 0; i < 4; i++) { res[i] = -values[i]; }
        return res;
      }
      vector<4>& operator+=(bu_f32 f) {
        for (int i = 0; i < 4; i++) { values[i] += f; }
        return *this;
      }
      vector<4>& operator-=(bu_f32 f) {
        for (int i = 0; i < 4; i++) { values[i] -= f; }
        return *this;
      }
      vector<4>& operator*=(bu_f32 f) {
        for (int i = 0; i < 4; i++) { values[i] *= f; }
        return *this;
      }
      vector<4>& operator/=(bu_f32 f) {
        for (int i = 0; i < 4; i++) { values[i] /= f; }
        return *this;
      }
      friend vector<4> operator+(vector<4> const& a, bu_f32 b) {
        return vector<4>(a) += b;
      }
      friend vector<4> operator+(bu_f32 b, vector<4> const& a) {
        return vector<4>(a) += b;
      }
      friend vector<4> operator-(vector<4> const& a, bu_f32 b) {
        return vector<4>(a) -= b;
      }
      friend vector<4> operator-(bu_f32 b, vector<4> const& a) {
        return vector<4>(a) -= b;
      }
      friend vector<4> operator*(vector<4> const& a, bu_f32 b) {
        return vector<4>(a) *= b;
      }
      friend vector<4> operator*(bu_f32 b, vector<4> const& a) {
        return vector<4>(a) *= b;
      }
      friend vector<4> operator/(vector<4> const& a, bu_f32 b) {
        return vector<4>(a) /= b;
      }
      friend vector<4> operator/(bu_f32 b, vector<4> const& a) {
        return vector<4>(a) /= b;
      }
      vector<4>& operator+=(vector<4> const& other) {
        for (int i = 0; i < 4; i++) { values[i] += other[i]; }
        return (*this);
      }
      vector<4>& operator-=(vector<4> const& other) {
        for (int i = 0; i < 4; i++) { values[i] -= other[i]; }
        return (*this);
      }
      friend vector<4> operator+(vector<4> const& a, vector<4> const& b) {
        return vector<4>(a) += b;
      }
      friend vector<4> operator-(vector<4> const& a, vector<4> const& b) {
        return vector<4>(a) -= b;
      }
      friend bu_f32* value_ptr(vector<4> const& vec);

      // mathematical operations
      bu_f32 length() const {
        bu_f32 tmp = 0;
        for (int i = 0; i < 4; i++) { tmp += values[i] * values[i]; }
        return sqrtf(tmp);
      }

      vector<4> normalized() const {
        return vec::normalize(*this);
      }

      // constructors
      vector() :
          values{0} {};
      vector(bu_f32 v) :
          values{v} {};
      vector(bu_f32 a, bu_f32 b, bu_f32 c, bu_f32 d) :
          values{a, b, c, d} {}
      vector(const vector<4>& other) = default;
      vector(vector<4>&& other)      = default;
      ~vector()                      = default;
    };

    using vec2 = vector<2>;
    using vec3 = vector<3>;
    using vec4 = vector<4>;

    const vec3 x_axis = {1, 0, 0};
    const vec3 y_axis = {0, 1, 0};
    const vec3 z_axis = {0, 0, 1};

    template<bu_i32 N>
    inline std::ostream& operator<<(std::ostream& os, const vector<N>& vec) {
      os << "\t[ " << vec[0];
      for (int i = 1; i < N; i++) { os << " " << vec[i]; }
      os << " ]\n";
      return os;
    }

    template<bu_i32 N>
    inline bu_f32* value_ptr(vector<N> const& vec) {
      return vec.values;
    }

    namespace vec {

      template<bu_i32 N>
      inline bu_f32 dot(vector<N> const& a, vector<N> const& b) {
        bu_f32 res = 0;
        for (int i = 0; i < N; i++) { res += a[i] * b[i]; }
        return res;
      }

      inline vector<3> cross(vector<3> const& a, vector<3> const& b) {
        return {(a[1] * b[2] - a[2] * b[1]), (a[2] * b[0] - a[0] * b[2]), (a[0] * b[1] - a[1] * b[0])};
      }

      template<bu_i32 N>
      inline vector<N> normalize(vector<N> const& a) {
        return a / a.length();
      }

    }  // namespace vec
  }    // namespace math
}  // namespace Bunny
