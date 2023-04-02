#pragma once

#include "angle.h"
#include "bunny/core/typedefs.h"
#include "vector.h"

namespace Bunny {
  namespace math {
    template<bu_i32 M, bu_i32 N>
    struct matrix;

    namespace mat {
      template<bu_i32 M, bu_i32 N, bu_i32 O>
      inline matrix<M, O> mult(matrix<M, N> const& a, matrix<N, O> const& b);
      template<bu_i32 M, bu_i32 N>
      vector<M> inline mult(matrix<M, N> const& a, vector<N> const& b);
      template<bu_i32 M, bu_i32 N>
      matrix<N, M> inline transpose(matrix<M, N> const& a);
    }  // namespace mat

    template<bu_i32 M, bu_i32 N>
    struct matrix {
     private:
      union {
        vector<M> columns[N];
        bu_f32 values[M * N];
      };

     public:
      vector<M>& operator[](bu_i32 i) {
        return columns[i];
      }
      vector<M> const& operator[](bu_i32 i) const {
        return columns[i];
      }

      matrix<M, N>& operator=(matrix<M, N> const& other) = default;
      matrix<M, N>& operator=(matrix<M, N>&& other)      = default;

      bool operator==(matrix<M, N> const& other) {
        bool b = true;
        for (int i = 0; i < N; i++) {
          b &= (columns[i] == other[i]);
        }
        return b;
      }
      bool operator!=(matrix<M, N> const& other) {
        return !((*this) == other);
      }

      matrix<M, N> operator-() const {
        matrix<M, N> o = *this;
        for (int i = 0; i < N; i++) {
          o[i] = -o[i];
        }
        return o;
      }
      matrix<M, N>& operator+=(bu_f32 f) {
        for (int i = 0; i < N; i++) {
          columns[i] += f;
        }
        return *this;
      }
      matrix<M, N>& operator-=(bu_f32 f) {
        for (int i = 0; i < N; i++) {
          columns[i] -= f;
        }
        return *this;
      }
      matrix<M, N>& operator*=(bu_f32 f) {
        for (int i = 0; i < N; i++) {
          columns[i] *= f;
        }
        return *this;
      }
      matrix<M, N>& operator/=(bu_f32 f) {
        for (int i = 0; i < N; i++) {
          columns[i] /= f;
        }
        return *this;
      }

      friend matrix<M, N> operator+(matrix<M, N> const& a, bu_f32 b) {
        return matrix<M, N>(a) += b;
      }
      friend matrix<M, N> operator+(bu_f32 b, matrix<M, N> const& a) {
        return matrix<M, N>(a) += b;
      }
      friend matrix<M, N> operator-(matrix<M, N> const& a, bu_f32 b) {
        return matrix<M, N>(a) -= b;
      }
      friend matrix<M, N> operator-(bu_f32 b, matrix<M, N> const& a) {
        return matrix<M, N>(a) -= b;
      }
      friend matrix<M, N> operator*(matrix<M, N> const& a, bu_f32 b) {
        return matrix<M, N>(a) *= b;
      }
      friend matrix<M, N> operator*(bu_f32 b, matrix<M, N> const& a) {
        return matrix<M, N>(a) *= b;
      }
      friend matrix<M, N> operator/(matrix<M, N> const& a, bu_f32 b) {
        return matrix<M, N>(a) /= b;
      }
      friend matrix<M, N> operator/(bu_f32 b, matrix<M, N> const& a) {
        return matrix<M, N>(a) /= b;
      }

      matrix<M, N>& operator+=(matrix<M, N> const& other) {
        for (int i = 0; i < N; i++) {
          columns[i] += other[i];
        }
        return *this;
      }
      matrix<M, N>& operator-=(matrix<M, N> const& other) {
        for (int i = 0; i < N; i++) {
          columns[i] -= other[i];
        }
        return *this;
      }

      friend matrix<M, N> operator+(matrix<M, N> const& a, matrix<M, N> const& b) {
        return matrix<M, N>(a) += b;
      }
      friend matrix<M, N> operator-(matrix<M, N> const& a, matrix<M, N> const& b) {
        return matrix<M, N>(a) -= b;
      }
      template<bu_i32 O>
      matrix<M, O>& operator*=(matrix<N, O> const& other) {
        return ((*this) = mat::mult(*this, other));
      }
      template<bu_i32 O>
      friend matrix<M, O> operator*(matrix<M, N> const& a, matrix<N, O> const& b) {
        return mat::mult(a, b);
      }
      friend vector<M> operator*(matrix<M, N> const& a, vector<N> const& b) {
        return mat::mult(a, b);
      }

      const bu_f32* value_ptr() const {
        return values;
      };

      matrix<N, M> T() {
        return mat::transpose(*this);
      }

      matrix<M, N>() :
          columns{0} {}

      // TODO test
      matrix<M, N>(const bu_f32 (&vectors)[N * M]) :
          columns{} {
        for (int i = 0; i < N; i++) {
          for (int j = 0; j < M; j++) {
            rows[j][i] = vectors[i * N + j];
          }
        }
      }
      explicit matrix<M, N>(bu_f32 v) :
          columns{0} {
        static_assert(N == M, "Only for square matrices");

        for (int i = 0; i < M; i++) {
          columns[i][i] = v;
        }
      }
      matrix<M, N>(matrix<M, N> const& other) = default;
      matrix<M, N>(matrix<M, N>&& other)      = default;

      ~matrix<M, N>() = default;
    };

    template<>
    struct matrix<4, 4> {
     private:
      union {
        vector<4> columns[4];
        bu_f32 values[16];
      };

     public:
      vector<4>& operator[](bu_i32 i) {
        return columns[i];
      }
      vector<4> const& operator[](bu_i32 i) const {
        return columns[i];
      }

      matrix<4, 4>& operator=(matrix<4, 4> const& other) = default;
      matrix<4, 4>& operator=(matrix<4, 4>&& other)      = default;

      bool operator==(matrix<4, 4> const& other) {
        bool b = true;
        for (int i = 0; i < 4; i++) {
          b &= (columns[i] == other[i]);
        }
        return b;
      }
      bool operator!=(matrix<4, 4> const& other) {
        return !((*this) == other);
      }

      matrix<4, 4> operator-() const {
        matrix<4, 4> o = *this;
        for (int i = 0; i < 4; i++) {
          o[i] = -o[i];
        }
        return o;
      }
      matrix<4, 4>& operator+=(bu_f32 f) {
        for (int i = 0; i < 4; i++) {
          columns[i] += f;
        }
        return *this;
      }
      matrix<4, 4>& operator-=(bu_f32 f) {
        for (int i = 0; i < 4; i++) {
          columns[i] -= f;
        }
        return *this;
      }
      matrix<4, 4>& operator*=(bu_f32 f) {
        for (int i = 0; i < 4; i++) {
          columns[i] *= f;
        }
        return *this;
      }
      matrix<4, 4>& operator/=(bu_f32 f) {
        for (int i = 0; i < 4; i++) {
          columns[i] /= f;
        }
        return *this;
      }

      friend matrix<4, 4> operator+(matrix<4, 4> const& a, bu_f32 b) {
        return matrix<4, 4>(a) += b;
      }
      friend matrix<4, 4> operator+(bu_f32 b, matrix<4, 4> const& a) {
        return matrix<4, 4>(a) += b;
      }
      friend matrix<4, 4> operator-(matrix<4, 4> const& a, bu_f32 b) {
        return matrix<4, 4>(a) -= b;
      }
      friend matrix<4, 4> operator-(bu_f32 b, matrix<4, 4> const& a) {
        return matrix<4, 4>(a) -= b;
      }
      friend matrix<4, 4> operator*(matrix<4, 4> const& a, bu_f32 b) {
        return matrix<4, 4>(a) *= b;
      }
      friend matrix<4, 4> operator*(bu_f32 b, matrix<4, 4> const& a) {
        return matrix<4, 4>(a) *= b;
      }
      friend matrix<4, 4> operator/(matrix<4, 4> const& a, bu_f32 b) {
        return matrix<4, 4>(a) /= b;
      }
      friend matrix<4, 4> operator/(bu_f32 b, matrix<4, 4> const& a) {
        return matrix<4, 4>(a) /= b;
      }

      matrix<4, 4>& operator+=(matrix<4, 4> const& other) {
        for (int i = 0; i < 4; i++) {
          columns[i] += other[i];
        }
        return *this;
      }
      matrix<4, 4>& operator-=(matrix<4, 4> const& other) {
        for (int i = 0; i < 4; i++) {
          columns[i] -= other[i];
        }
        return *this;
      }

      friend matrix<4, 4> operator+(matrix<4, 4> const& a, matrix<4, 4> const& b) {
        return matrix<4, 4>(a) += b;
      }
      friend matrix<4, 4> operator-(matrix<4, 4> const& a, matrix<4, 4> const& b) {
        return matrix<4, 4>(a) -= b;
      }
      template<bu_i32 O>
      matrix<4, O>& operator*=(matrix<4, O> const& other) {
        return ((*this) = mat::mult(*this, other));
      }
      template<bu_i32 O>
      friend matrix<4, O> operator*(matrix<4, 4> const& a, matrix<4, O> const& b) {
        return mat::mult(a, b);
      }
      friend vector<4> operator*(matrix<4, 4> const& a, vector<4> const& b) {
        return mat::mult(a, b);
      }

      const bu_f32* value_ptr() const {
        return values;
      };

      matrix<4, 4> T() {
        return mat::transpose(*this);
      }

      matrix() :
          values{0} {}

      matrix(const bu_f32 (&vectors)[4 * 4]) :
          columns{} {
        for (int i = 0; i < 4; i++) {
          for (int j = 0; j < 4; j++) {
            columns[j][i] = vectors[i * 4 + j];
          }
        }
      }
      explicit matrix(bu_f32 v) :
          values{v, 0, 0, 0, 0, v, 0, 0, 0, 0, v, 0, 0, 0, 0, v} {
      }
      matrix(matrix<4, 4> const& other) = default;
      matrix(matrix<4, 4>&& other)      = default;
      matrix(bu_f32 a00, bu_f32 a10, bu_f32 a20, bu_f32 a30, bu_f32 a01, bu_f32 a11, bu_f32 a21, bu_f32 a31, bu_f32 a02, bu_f32 a12, bu_f32 a22, bu_f32 a32, bu_f32 a03, bu_f32 a13, bu_f32 a23, bu_f32 a33) :
          values{a00, a01, a02, a03, a10, a11, a12, a13, a20, a21, a22, a23, a30, a31, a32, a33} {
      }
      ~matrix() = default;
    };

    template<bu_i32 N, bu_i32 M>
    inline std::ostream& operator<<(std::ostream& os, const matrix<N, M>& mat) {
      for (int i = 0; i < N; i++) {
        os << mat[i];
      }
      return os;
    }
  }  // namespace math
}  // namespace Bunny

// free standing functions
namespace Bunny {
  namespace math {

    namespace mat {
      template<bu_i32 M, bu_i32 N>
      matrix<N, M> inline transpose(matrix<M, N> const& a) {

        matrix<N, M> res;
        for (int i = 0; i < M; i++) {
          for (int j = 0; j < N; j++) {
            res[j][i] = a[i][j];
          }
        }
        return res;
      }

      template<bu_i32 M, bu_i32 N, bu_i32 O>
      inline matrix<M, O> mult(matrix<M, N> const& a, matrix<N, O> const& b) {
        matrix<M, O> result;
        for (int i = 0; i < O; i++) {
          for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
              result[i][j] += a[k][j] * b[i][k];
            }
          }
        }
        return result;
      }

      template<bu_i32 M, bu_i32 N>
      inline vector<M> mult(matrix<M, N> const& a, vector<N> const& b) {
        vector<M> result;
        for (int j = 0; j < M; j++) {
          for (int k = 0; k < N; k++) {
            result[j] += a[k][j] * b[k];
          }
        }
        return result;
      }

      inline matrix<4, 4> identity() {
        return matrix<4, 4>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
      }

      inline matrix<4, 4> translation(vector<3> const& v) {
        return matrix<4, 4>(
          1,
          0,
          0,
          v[0],
          0,
          1,
          0,
          v[1],
          0,
          0,
          1,
          v[2],
          0,
          0,
          0,
          1);
      }
      inline matrix<4, 4> translation(bu_f32 x, bu_f32 y, bu_f32 z) {
        return matrix<4, 4>(
          1,
          0,
          0,
          x,
          0,
          1,
          0,
          y,
          0,
          0,
          1,
          z,
          0,
          0,
          0,
          1);
      }
      inline matrix<4, 4> scaling(vector<3> const& v) {
        return matrix<4, 4>(
          v[0],
          0,
          0,
          0,
          0,
          v[1],
          0,
          0,
          0,
          0,
          v[2],
          0,
          0,
          0,
          0,
          1);
      }
      inline matrix<4, 4> scaling(bu_f32 x, bu_f32 y, bu_f32 z) {
        return matrix<4, 4>(
          x,
          0,
          0,
          0,
          0,
          y,
          0,
          0,
          0,
          0,
          z,
          0,
          0,
          0,
          0,
          1);
      }
      inline matrix<4, 4> scaling2d(vector<2> const& v) {
        return matrix<4, 4>(
          v[0],
          0,
          0,
          0,
          0,
          v[1],
          0,
          0,
          0,
          0,
          1,
          0,
          0,
          0,
          0,
          1);
      }
      inline matrix<4, 4> scaling2d(bu_f32 x, bu_f32 y) {
        return matrix<4, 4>(
          x,
          0,
          0,
          0,
          0,
          y,
          0,
          0,
          0,
          0,
          1,
          0,
          0,
          0,
          0,
          1);
      }
      inline matrix<4, 4> rotation(vector<3> const& axis, angle angle) {
        vector<3> norm = axis.normalized();
        float c = angle.cos(), cm = 1 - c,
              s = angle.sin(),
              x = norm[0], y = norm[1], z = norm[2],
              xy = norm[0] * norm[1], xz = norm[0] * norm[2], yz = norm[1] * norm[2];
        return matrix<4, 4>(
          c + x * x * cm,
          xy * cm - z * s,
          xz * cm + y * s,
          0,
          xy * cm + z * s,
          c + y * y * cm,
          yz * cm - x * s,
          0,
          xz * cm - y * s,
          yz * cm + x * s,
          c + z * z * cm,
          0,
          0,
          0,
          0,
          1);
      }

      inline matrix<4, 4> rotation2d(angle angle) {
        float c = angle.cos(),
              s = angle.sin();
        return matrix<4, 4>(
          c,
          -s,
          0,
          0,
          s,
          c,
          0,
          0,
          0,
          0,
          1,
          0,
          0,
          0,
          0,
          1);
      }

      inline matrix<4, 4> ortho(bu_f32 left, bu_f32 right, bu_f32 bottom, bu_f32 top, bu_f32 zNear, bu_f32 zFar) {
        return matrix<4, 4>(
          2.0f / (right - left),
          0,
          0,
          -(right + left) / (right - left),
          0,
          2.0f / (top - bottom),
          0,
          -(top + bottom) / (top - bottom),
          0,
          0,
          -2.0f / (zFar - zNear),
          -(zFar + zNear) / (zFar - zNear),
          0,
          0,
          0,
          1);
      }

      inline matrix<4, 4> perspective(bu_f32 fovy, bu_f32 aspect, bu_f32 zNear, bu_f32 zFar) {
        bu_f32 tanHalfFovy = std::tan(fovy / 2.0f);

        return matrix<4, 4>(
          1.0f / (aspect * tanHalfFovy),
          0,
          0,
          0,
          0,
          1.0f / tanHalfFovy,
          0,
          0,
          0,
          0,
          -(zFar * zNear) / (zFar - zNear),
          -(2.0f * zFar * zNear) / (zFar - zNear),
          0,
          0,
          -1.0f,
          0);
      }

      inline bu_f32 det(matrix<4, 4> const& a) {
        return a[1 - 1][1 - 1] * (a[2 - 1][2 - 1] * a[3 - 1][3 - 1] * a[4 - 1][4 - 1] + a[3 - 1][2 - 1] * a[4 - 1][3 - 1] * a[2 - 1][4 - 1] + a[4 - 1][2 - 1] * a[2 - 1][3 - 1] * a[3 - 1][4 - 1] - a[4 - 1][2 - 1] * a[3 - 1][3 - 1] * a[2 - 1][4 - 1] - a[3 - 1][2 - 1] * a[2 - 1][3 - 1] * a[4 - 1][4 - 1] - a[2 - 1][2 - 1] * a[4 - 1][3 - 1] * a[3 - 1][4 - 1]) - a[1 - 1][2 - 1] * (a[2 - 1][1 - 1] * a[3 - 1][3 - 1] * a[4 - 1][4 - 1] + a[3 - 1][1 - 1] * a[4 - 1][3 - 1] * a[2 - 1][4 - 1] + a[4 - 1][1 - 1] * a[2 - 1][3 - 1] * a[3 - 1][4 - 1] - a[4 - 1][1 - 1] * a[3 - 1][3 - 1] * a[2 - 1][4 - 1] - a[3 - 1][1 - 1] * a[2 - 1][3 - 1] * a[4 - 1][4 - 1] - a[2 - 1][1 - 1] * a[4 - 1][3 - 1] * a[3 - 1][4 - 1]) + a[1 - 1][3 - 1] * (a[2 - 1][1 - 1] * a[3 - 1][2 - 1] * a[4 - 1][4 - 1] + a[3 - 1][1 - 1] * a[4 - 1][2 - 1] * a[2 - 1][4 - 1] + a[4 - 1][1 - 1] * a[2 - 1][2 - 1] * a[3 - 1][4 - 1] - a[4 - 1][1 - 1] * a[3 - 1][2 - 1] * a[2 - 1][4 - 1] - a[3 - 1][1 - 1] * a[2 - 1][2 - 1] * a[4 - 1][4 - 1] - a[2 - 1][1 - 1] * a[4 - 1][2 - 1] * a[3 - 1][4 - 1]) - a[1 - 1][4 - 1] * (a[2 - 1][1 - 1] * a[3 - 1][2 - 1] * a[4 - 1][3 - 1] + a[3 - 1][1 - 1] * a[4 - 1][2 - 1] * a[2 - 1][3 - 1] + a[4 - 1][1 - 1] * a[2 - 1][2 - 1] * a[3 - 1][3 - 1] - a[4 - 1][1 - 1] * a[3 - 1][2 - 1] * a[2 - 1][3 - 1] - a[3 - 1][1 - 1] * a[2 - 1][2 - 1] * a[4 - 1][3 - 1] - a[2 - 1][1 - 1] * a[4 - 1][2 - 1] * a[3 - 1][3 - 1]);
      }

      inline matrix<4, 4> inverse(matrix<4, 4> const& m) {
        bu_f32 A2323 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
        bu_f32 A1323 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
        bu_f32 A1223 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
        bu_f32 A0323 = m[0][2] * m[3][3] - m[3][2] * m[0][3];
        bu_f32 A0223 = m[0][2] * m[2][3] - m[2][2] * m[0][3];
        bu_f32 A0123 = m[0][2] * m[1][3] - m[1][2] * m[0][3];
        bu_f32 A2313 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
        bu_f32 A1313 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
        bu_f32 A1213 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
        bu_f32 A2312 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
        bu_f32 A1312 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
        bu_f32 A1212 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
        bu_f32 A0313 = m[0][1] * m[3][3] - m[3][1] * m[0][3];
        bu_f32 A0213 = m[0][1] * m[2][3] - m[2][1] * m[0][3];
        bu_f32 A0312 = m[0][1] * m[3][2] - m[3][1] * m[0][2];
        bu_f32 A0212 = m[0][1] * m[2][2] - m[2][1] * m[0][2];
        bu_f32 A0113 = m[0][1] * m[1][3] - m[1][1] * m[0][3];
        bu_f32 A0112 = m[0][1] * m[1][2] - m[1][1] * m[0][2];

        bu_f32 det = m[0][0] * (m[1][1] * A2323 - m[2][1] * A1323 + m[3][1] * A1223) - m[1][0] * (m[0][1] * A2323 - m[2][1] * A0323 + m[3][1] * A0223) + m[2][0] * (m[0][1] * A1323 - m[1][1] * A0323 + m[3][1] * A0123) - m[3][0] * (m[0][1] * A1223 - m[1][1] * A0223 + m[2][1] * A0123);
        det        = 1 / det;

        matrix<4, 4> res;
        res[0][0] = det * (m[1][1] * A2323 - m[2][1] * A1323 + m[3][1] * A1223);
        res[1][0] = det * -(m[1][0] * A2323 - m[2][0] * A1323 + m[3][0] * A1223);
        res[2][0] = det * (m[1][0] * A2313 - m[2][0] * A1313 + m[3][0] * A1213);
        res[3][0] = det * -(m[1][0] * A2312 - m[2][0] * A1312 + m[3][0] * A1212);
        res[0][1] = det * -(m[0][1] * A2323 - m[2][1] * A0323 + m[3][1] * A0223);
        res[1][1] = det * (m[0][0] * A2323 - m[2][0] * A0323 + m[3][0] * A0223);
        res[2][1] = det * -(m[0][0] * A2313 - m[2][0] * A0313 + m[3][0] * A0213);
        res[3][1] = det * (m[0][0] * A2312 - m[2][0] * A0312 + m[3][0] * A0212);
        res[0][2] = det * (m[0][1] * A1323 - m[1][1] * A0323 + m[3][1] * A0123);
        res[1][2] = det * -(m[0][0] * A1323 - m[1][0] * A0323 + m[3][0] * A0123);
        res[2][2] = det * (m[0][0] * A1313 - m[1][0] * A0313 + m[3][0] * A0113);
        res[3][2] = det * -(m[0][0] * A1312 - m[1][0] * A0312 + m[3][0] * A0112);
        res[0][3] = det * -(m[0][1] * A1223 - m[1][1] * A0223 + m[2][1] * A0123);
        res[1][3] = det * (m[0][0] * A1223 - m[1][0] * A0223 + m[2][0] * A0123);
        res[2][3] = det * -(m[0][0] * A1213 - m[1][0] * A0213 + m[2][0] * A0113);
        res[3][3] = det * (m[0][0] * A1212 - m[1][0] * A0212 + m[2][0] * A0112);

        return res;
      }

    }  // namespace mat
    using mat4 = matrix<4, 4>;
  }  // namespace math
}  // namespace Bunny
//
// namespace Bunny
//{
//	namespace math2
//	{
//		template <bu_i32 N>
//		using vector = math::vector<N>;
//		using angle = math::angle;
//
//
//		template <bu_i32 N, bu_i32 M>
//		struct matrix;
//
//		namespace mat
//		{
//			template <bu_i32 N, bu_i32 M, bu_i32 O> inline matrix<N, O> mult(matrix<N, M> const& a, matrix<M, O> const& b);
//			template <bu_i32 N, bu_i32 M> vector<N> inline mult(matrix<N, M> const& a, vector<M> const& b);
//			template <bu_i32 N, bu_i32 M> matrix<M, N> inline transpose(matrix<N, M> const& a);
//		}
//
//
//		template <bu_i32 N, bu_i32 M>
//		struct matrix
//		{
//		private:
//			union
//			{
//				vector<M> rows[N];
//				bu_f32 values[M * N];
//			};
//
//		public:
//			vector<M>& operator[](bu_i32 i) { return rows[i]; }
//			vector<M> const& operator[](bu_i32 i) const { return rows[i]; }
//
//			matrix<N, M>& operator=(matrix<N, M> const& other) = default;
//			matrix<N, M>& operator=(matrix<N, M>&& other) = default;
//
//			bool operator==(matrix<N, M> const& other)
//			{
//				bool b = true;
//				for (int i = 0; i < N; i++)
//				{
//					b &= (rows[i] == other[i]);
//				}
//				return b;
//			}
//			bool operator!=(matrix<N, M> const& other)
//			{
//				return !((*this) == other);
//			}
//
//			matrix<N, M> operator-() const
//			{
//				matrix<N, M> o = *this;
//				for (int i = 0; i < N; i++)
//				{
//					o[i] = -o[i];
//				}
//				return o;
//			}
//			matrix<N, M>& operator+=(bu_f32 f)
//			{
//				for (int i = 0; i < N; i++)
//				{
//					rows[i] += f;
//				}
//				return *this;
//			}
//			matrix<N, M>& operator-=(bu_f32 f)
//			{
//				for (int i = 0; i < N; i++)
//				{
//					rows[i] -= f;
//				}
//				return *this;
//			}
//			matrix<N, M>& operator*=(bu_f32 f)
//			{
//				for (int i = 0; i < N; i++)
//				{
//					rows[i] *= f;
//				}
//				return *this;
//			}
//			matrix<N, M>& operator/=(bu_f32 f)
//			{
//				for (int i = 0; i < N; i++)
//				{
//					rows[i] /= f;
//				}
//				return *this;
//			}
//
//			friend matrix<N, M> operator+(matrix<N, M> const& a, bu_f32 b) { return matrix<N, M>(a) += b; }
//			friend matrix<N, M> operator+(bu_f32 b, matrix<N, M> const& a) { return matrix<N, M>(a) += b; }
//			friend matrix<N, M> operator-(matrix<N, M> const& a, bu_f32 b) { return matrix<N, M>(a) -= b; }
//			friend matrix<N, M> operator-(bu_f32 b, matrix<N, M> const& a) { return matrix<N, M>(a) -= b; }
//			friend matrix<N, M> operator*(matrix<N, M> const& a, bu_f32 b) { return matrix<N, M>(a) *= b; }
//			friend matrix<N, M> operator*(bu_f32 b, matrix<N, M> const& a) { return matrix<N, M>(a) *= b; }
//			friend matrix<N, M> operator/(matrix<N, M> const& a, bu_f32 b) { return matrix<N, M>(a) /= b; }
//			friend matrix<N, M> operator/(bu_f32 b, matrix<N, M> const& a) { return matrix<N, M>(a) /= b; }
//
//			matrix<N, M>& operator+=(matrix<N, M> const& other)
//			{
//				for (int i = 0; i < N; i++)
//				{
//					rows[i] += other[i];
//				}
//				return *this;
//			}
//			matrix<N, M>& operator-=(matrix<N, M> const& other)
//			{
//				for (int i = 0; i < N; i++)
//				{
//					rows[i] -= other[i];
//				}
//				return *this;
//			}
//
//			friend matrix<N, M> operator+(matrix<N, M> const& a, matrix<N, M> const& b) { return matrix<N, M>(a) += b; }
//			friend matrix<N, M> operator-(matrix<N, M> const& a, matrix<N, M> const& b) { return matrix<N, M>(a) -= b; }
//			template <bu_i32 O> matrix<N, O>& operator*=(matrix<M, O> const& other) { return ((*this) = mat::mult(*this, other)); }
//			template <bu_i32 O> friend matrix<N, O> operator*(matrix<N, M> const& a, matrix<M, O> const& b) { return mat::mult(a, b); }
//			friend vector<M> operator*(matrix<N, M> const& a, vector<M> const& b) { return mat::mult(a, b); }
//
//			const bu_f32* value_ptr() const
//			{
//				return values;
//			};
//
//			matrix<M, N> T() { return mat::transpose(*this); }
//
//			matrix<N, M>() : values{ 0 } {}
//
//			matrix<N, M>(const bu_f32(&vectors)[N * M]) : rows{}
//			{
//				for (int i = 0; i < N; i++)
//				{
//					for (int j = 0; j < M; j++)
//					{
//						rows[i][j] = vectors[i * M + j];
//					}
//				}
//			}
//			explicit matrix<N, M>(bu_f32 v) : rows{ 0 }
//			{
//				static_assert(N == M, "Only for square matrices");
//
//				for (int i = 0; i < M; i++)
//				{
//					rows[i][i] = v;
//				}
//
//			}
//			matrix<N, M>(matrix<N, M> const& other) = default;
//			matrix<N, M>(matrix<N, M>&& other) = default;
//
//			~matrix<N, M>() = default;
//		};
//
//
//		template <>
//		struct matrix<4, 4>
//		{
//		private:
//			union
//			{
//				vector<4> rows[4];
//				bu_f32 values[16];
//			};
//
//		public:
//			vector<4>& operator[](bu_i32 i) { return rows[i]; }
//			vector<4> const& operator[](bu_i32 i) const { return rows[i]; }
//
//			matrix<4, 4>& operator=(matrix<4, 4> const& other) = default;
//			matrix<4, 4>& operator=(matrix<4, 4>&& other) = default;
//
//			bool operator==(matrix<4, 4> const& other)
//			{
//				bool b = true;
//				for (int i = 0; i < 4; i++)
//				{
//					b &= (rows[i] == other[i]);
//				}
//				return b;
//			}
//			bool operator!=(matrix<4, 4> const& other)
//			{
//				return !((*this) == other);
//			}
//
//			matrix<4, 4> operator-() const
//			{
//				matrix<4, 4> o = *this;
//				for (int i = 0; i < 4; i++)
//				{
//					o[i] = -o[i];
//				}
//				return o;
//			}
//			matrix<4, 4>& operator+=(bu_f32 f)
//			{
//				for (int i = 0; i < 4; i++)
//				{
//					rows[i] += f;
//				}
//				return *this;
//			}
//			matrix<4, 4>& operator-=(bu_f32 f)
//			{
//				for (int i = 0; i < 4; i++)
//				{
//					rows[i] -= f;
//				}
//				return *this;
//			}
//			matrix<4, 4>& operator*=(bu_f32 f)
//			{
//				for (int i = 0; i < 4; i++)
//				{
//					rows[i] *= f;
//				}
//				return *this;
//			}
//			matrix<4, 4>& operator/=(bu_f32 f)
//			{
//				for (int i = 0; i < 4; i++)
//				{
//					rows[i] /= f;
//				}
//				return *this;
//			}
//
//			friend matrix<4, 4> operator+(matrix<4, 4> const& a, bu_f32 b) { return matrix<4, 4>(a) += b; }
//			friend matrix<4, 4> operator+(bu_f32 b, matrix<4, 4> const& a) { return matrix<4, 4>(a) += b; }
//			friend matrix<4, 4> operator-(matrix<4, 4> const& a, bu_f32 b) { return matrix<4, 4>(a) -= b; }
//			friend matrix<4, 4> operator-(bu_f32 b, matrix<4, 4> const& a) { return matrix<4, 4>(a) -= b; }
//			friend matrix<4, 4> operator*(matrix<4, 4> const& a, bu_f32 b) { return matrix<4, 4>(a) *= b; }
//			friend matrix<4, 4> operator*(bu_f32 b, matrix<4, 4> const& a) { return matrix<4, 4>(a) *= b; }
//			friend matrix<4, 4> operator/(matrix<4, 4> const& a, bu_f32 b) { return matrix<4, 4>(a) /= b; }
//			friend matrix<4, 4> operator/(bu_f32 b, matrix<4, 4> const& a) { return matrix<4, 4>(a) /= b; }
//
//			matrix<4, 4>& operator+=(matrix<4, 4> const& other)
//			{
//				for (int i = 0; i < 4; i++)
//				{
//					rows[i] += other[i];
//				}
//				return *this;
//			}
//			matrix<4, 4>& operator-=(matrix<4, 4> const& other)
//			{
//				for (int i = 0; i < 4; i++)
//				{
//					rows[i] -= other[i];
//				}
//				return *this;
//			}
//
//			friend matrix<4, 4> operator+(matrix<4, 4> const& a, matrix<4, 4> const& b) { return matrix<4, 4>(a) += b; }
//			friend matrix<4, 4> operator-(matrix<4, 4> const& a, matrix<4, 4> const& b) { return matrix<4, 4>(a) -= b; }
//			template <bu_i32 O> matrix<4, O>& operator*=(matrix<4, O> const& other) { return ((*this) = mat::mult(*this, other)); }
//			template <bu_i32 O> friend matrix<4, O> operator*(matrix<4, 4> const& a, matrix<4, O> const& b) { return mat::mult(a, b); }
//			friend vector<4> operator*(matrix<4, 4> const& a, vector<4> const& b) { return mat::mult(a, b); }
//
//			const bu_f32* value_ptr() const
//			{
//				return values;
//			};
//
//			matrix<4, 4> T() { return mat::transpose(*this); }
//
//			matrix() : values{ 0 } {}
//
//			matrix(const bu_f32(&vectors)[4 * 4]) : rows{}
//			{
//				for (int i = 0; i < 4; i++)
//				{
//					for (int j = 0; j < 4; j++)
//					{
//						rows[i][j] = vectors[i * 4 + j];
//					}
//				}
//			}
//			explicit matrix(bu_f32 v) : values{ v, 0, 0, 0,
//												0, v, 0, 0,
//												0, 0, v, 0,
//												0, 0, 0, v }
//			{}
//			matrix(matrix<4, 4> const& other) = default;
//			matrix(matrix<4, 4>&& other) = default;
//			matrix(bu_f32 a00, bu_f32 a01, bu_f32 a02, bu_f32 a03,
//				   bu_f32 a10, bu_f32 a11, bu_f32 a12, bu_f32 a13,
//				   bu_f32 a20, bu_f32 a21, bu_f32 a22, bu_f32 a23,
//				   bu_f32 a30, bu_f32 a31, bu_f32 a32, bu_f32 a33) : values{ a00, a01, a02, a03, a10, a11, a12, a13, a20, a21, a22, a23, a30, a31, a32, a33 }
//			{}
//			~matrix() = default;
//		};
//
//
//
//		template <bu_i32 N, bu_i32 M>
//		inline std::ostream& operator<<(std::ostream& os, const matrix<N, M>& mat)
//		{
//			for (int i = 0; i < N; i++)
//			{
//				os << mat[i];
//			}
//			return os;
//		}
//	}
//}
//
//// free standing functions
// namespace Bunny
//{
//	namespace math2
//	{
//
//		namespace mat
//		{
//			template <bu_i32 N, bu_i32 M> matrix<M, N> inline transpose(matrix<N, M> const& a)
//			{
//
//				matrix<M, N> res;
//				for (int i = 0; i < N; i++)
//				{
//					for (int j = 0; j < M; j++)
//					{
//						res[j][i] = a[i][j];
//					}
//				}
//				return res;
//			}
//
//			template <bu_i32 N, bu_i32 M, bu_i32 O>
//			inline matrix<N, O> mult(matrix<N, M> const& a, matrix<M, O> const& b)
//			{
//				matrix<N, O> result;
//				for (int i = 0; i < N; i++)
//				{
//					for (int j = 0; j < O; j++)
//					{
//						for (int k = 0; k < M; k++)
//						{
//							result[i][j] += (a[i][k] * b[k][j]);
//						}
//					}
//				}
//				return result;
//			}
//
//			template <bu_i32 N, bu_i32 M> inline  vector<N> mult(matrix<N, M> const& a, vector<M> const& b)
//			{
//				vector<N> result;
//				for (int i = 0; i < N; i++)
//				{
//					result[i] = 0;
//					for (int k = 0; k < M; k++)
//					{
//						result[i] += a[i][k] * b[k];
//					}
//				}
//				return result;
//			}
//
//			inline matrix<4, 4> identity() { return { {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1} }; }
//
//			inline matrix<4, 4> translation(vector<3> const& v)
//			{
//				return
//				{
//					{
//						1, 0, 0, v[0],
//						0, 1, 0, v[1],
//						0, 0, 1, v[2],
//						0, 0, 0, 1
//					}
//				};
//			}
//			inline matrix<4, 4> scaling(vector<3> const& v)
//			{
//				return
//				{
//					{
//						v[0], 0, 0, 0,
//						0, v[1], 0, 0,
//						0, 0, v[2], 0,
//						0, 0, 0, 1
//					}
//				};
//			}
//			inline matrix<4, 4> scaling(vector<2> const& v)
//			{
//				return
//				{
//					{
//						v[0], 0, 0, 0,
//						0, v[1], 0, 0,
//						0, 0, 1, 0,
//						0, 0, 0, 1
//					}
//				};
//			}
//			inline matrix<4, 4> rotation(vector<3> const& axis, angle angle)
//			{
//				vector<3> norm = axis.normalized();
//				float c = angle.cos(), cm = 1 - c,
//					s = angle.sin(),
//					x = norm[0], y = norm[1], z = norm[2],
//					xy = norm[0] * norm[1], xz = norm[0] * norm[2], yz = norm[1] * norm[2];
//				return
//				{
//					{
//						c + x * x * cm,			xy * cm - z * s,			xz * cm + y * s,			0,
//						xy * cm + z * s,		c + y * y * cm,				yz * cm - x * s,				0,
//						xz * cm - y * s,		yz * cm + x * s,			c + z * z * cm,					0,
//						0,					0,						0,							1
//					}
//				};
//			}
//
//			inline matrix<4, 4> rotation2d(angle angle)
//			{
//				float c = angle.cos(),
//					s = angle.sin();
//				return
//				{
//					{
//						c,-s, 0, 0,
//						s, c, 0, 0,
//						0, 0, 1, 0,
//						0, 0, 0, 1
//					}
//				};
//			}
//
//			inline matrix<4, 4> ortho(bu_f32 left, bu_f32 right, bu_f32 bottom, bu_f32 top, bu_f32 zNear, bu_f32 zFar)
//			{
//				//matrix<4, 4> Result(identity());
//				//Result[0][0] = 2.0f / (right - left);
//				//Result[1][1] = 2.0f / (top - bottom);
//				//Result[2][2] = -2.0f / (zFar - zNear);
//				//Result[0][3] = -(right + left) / (right - left);
//				//Result[1][3] = -(top + bottom) / (top - bottom);
//				//Result[2][3] = -(zFar + zNear) / (zFar - zNear);
//				return
//				{
//					{
//						2.0f / (right - left), 0, 0,  -(right + left) / (right - left),
//						0, 2.0f / (top - bottom), 0, -(top + bottom) / (top - bottom),
//						0, 0, -2.0f / (zFar - zNear), -(zFar + zNear) / (zFar - zNear),
//						0, 0, 0, 1
//					}
//				};
//			}
//
//			inline bu_f32 det(matrix<4, 4> const& a)
//			{
//				return
//					a[1 - 1][1 - 1] * (a[2 - 1][2 - 1] * a[3 - 1][3 - 1] * a[4 - 1][4 - 1] + a[2 - 1][3 - 1] * a[3 - 1][4 - 1] * a[4 - 1][2 - 1] + a[2 - 1][4 - 1] * a[3 - 1][2 - 1] * a[4 - 1][3 - 1] - a[2 - 1][4 - 1] * a[3 - 1][3 - 1] * a[4 - 1][2 - 1] - a[2 - 1][3 - 1] * a[3 - 1][2 - 1] * a[4 - 1][4 - 1] - a[2 - 1][2 - 1] * a[3 - 1][4 - 1] * a[4 - 1][3 - 1])
//					- a[2 - 1][1 - 1] * (a[1 - 1][2 - 1] * a[3 - 1][3 - 1] * a[4 - 1][4 - 1] + a[1 - 1][3 - 1] * a[3 - 1][4 - 1] * a[4 - 1][2 - 1] + a[1 - 1][4 - 1] * a[3 - 1][2 - 1] * a[4 - 1][3 - 1] - a[1 - 1][4 - 1] * a[3 - 1][3 - 1] * a[4 - 1][2 - 1] - a[1 - 1][3 - 1] * a[3 - 1][2 - 1] * a[4 - 1][4 - 1] - a[1 - 1][2 - 1] * a[3 - 1][4 - 1] * a[4 - 1][3 - 1])
//					+ a[3 - 1][1 - 1] * (a[1 - 1][2 - 1] * a[2 - 1][3 - 1] * a[4 - 1][4 - 1] + a[1 - 1][3 - 1] * a[2 - 1][4 - 1] * a[4 - 1][2 - 1] + a[1 - 1][4 - 1] * a[2 - 1][2 - 1] * a[4 - 1][3 - 1] - a[1 - 1][4 - 1] * a[2 - 1][3 - 1] * a[4 - 1][2 - 1] - a[1 - 1][3 - 1] * a[2 - 1][2 - 1] * a[4 - 1][4 - 1] - a[1 - 1][2 - 1] * a[2 - 1][4 - 1] * a[4 - 1][3 - 1])
//					- a[4 - 1][1 - 1] * (a[1 - 1][2 - 1] * a[2 - 1][3 - 1] * a[3 - 1][4 - 1] + a[1 - 1][3 - 1] * a[2 - 1][4 - 1] * a[3 - 1][2 - 1] + a[1 - 1][4 - 1] * a[2 - 1][2 - 1] * a[3 - 1][3 - 1] - a[1 - 1][4 - 1] * a[2 - 1][3 - 1] * a[3 - 1][2 - 1] - a[1 - 1][3 - 1] * a[2 - 1][2 - 1] * a[3 - 1][4 - 1] - a[1 - 1][2 - 1] * a[2 - 1][4 - 1] * a[3 - 1][3 - 1]);
//			}
//
//			inline matrix<4, 4> inverse(matrix<4, 4> const& m)
//			{
//				bu_f32 A2323 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
//				bu_f32 A1323 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
//				bu_f32 A1223 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
//				bu_f32 A0323 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
//				bu_f32 A0223 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
//				bu_f32 A0123 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
//				bu_f32 A2313 = m[1][2] * m[3][3] - m[1][3] * m[3][2];
//				bu_f32 A1313 = m[1][1] * m[3][3] - m[1][3] * m[3][1];
//				bu_f32 A1213 = m[1][1] * m[3][2] - m[1][2] * m[3][1];
//				bu_f32 A2312 = m[1][2] * m[2][3] - m[1][3] * m[2][2];
//				bu_f32 A1312 = m[1][1] * m[2][3] - m[1][3] * m[2][1];
//				bu_f32 A1212 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
//				bu_f32 A0313 = m[1][0] * m[3][3] - m[1][3] * m[3][0];
//				bu_f32 A0213 = m[1][0] * m[3][2] - m[1][2] * m[3][0];
//				bu_f32 A0312 = m[1][0] * m[2][3] - m[1][3] * m[2][0];
//				bu_f32 A0212 = m[1][0] * m[2][2] - m[1][2] * m[2][0];
//				bu_f32 A0113 = m[1][0] * m[3][1] - m[1][1] * m[3][0];
//				bu_f32 A0112 = m[1][0] * m[2][1] - m[1][1] * m[2][0];
//
//				bu_f32 det = m[0][0] * (m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223)
//					- m[0][1] * (m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223)
//					+ m[0][2] * (m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123)
//					- m[0][3] * (m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123);
//				det = 1 / det;
//
//				matrix<4, 4> res;
//				res[0][0] = det * (m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223);
//				res[0][1] = det * -(m[0][1] * A2323 - m[0][2] * A1323 + m[0][3] * A1223);
//				res[0][2] = det * (m[0][1] * A2313 - m[0][2] * A1313 + m[0][3] * A1213);
//				res[0][3] = det * -(m[0][1] * A2312 - m[0][2] * A1312 + m[0][3] * A1212);
//				res[1][0] = det * -(m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223);
//				res[1][1] = det * (m[0][0] * A2323 - m[0][2] * A0323 + m[0][3] * A0223);
//				res[1][2] = det * -(m[0][0] * A2313 - m[0][2] * A0313 + m[0][3] * A0213);
//				res[1][3] = det * (m[0][0] * A2312 - m[0][2] * A0312 + m[0][3] * A0212);
//				res[2][0] = det * (m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123);
//				res[2][1] = det * -(m[0][0] * A1323 - m[0][1] * A0323 + m[0][3] * A0123);
//				res[2][2] = det * (m[0][0] * A1313 - m[0][1] * A0313 + m[0][3] * A0113);
//				res[2][3] = det * -(m[0][0] * A1312 - m[0][1] * A0312 + m[0][3] * A0112);
//				res[3][0] = det * -(m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123);
//				res[3][1] = det * (m[0][0] * A1223 - m[0][1] * A0223 + m[0][2] * A0123);
//				res[3][2] = det * -(m[0][0] * A1213 - m[0][1] * A0213 + m[0][2] * A0113);
//				res[3][3] = det * (m[0][0] * A1212 - m[0][1] * A0212 + m[0][2] * A0112);
//				return res;
//			}
//
//		}
//		using mat4 = matrix<4, 4>;
//	}
// }
//
//// // ASM IMPLEMENTATION NO BIT FASTER REEEEEEEEEEE
//			//matrix<2, 2, bu_f32> mult_sse(matrix<2, 2, bu_f32> const& a, matrix<2, 2, bu_f32> const& b)
//			//{
//			//	matrix<2, 2, bu_f32> result;
//			//	bu_f32 tmp1[4] = { a[0][0], a[0][0], a[1][0], a[1][0] };
//			//	bu_f32 tmp2[4] = { b[0][0], b[0][1], b[0][0], b[0][1] };
//			//	bu_f32 tmp3[4] = { a[0][1], a[0][1], a[1][1], a[1][1] };
//			//	bu_f32 tmp4[4] = { b[1][0], b[1][1], b[1][0], b[1][1] };
//			//	__asm
//			//	{
//			//		movups xmm0, [tmp1]
//			//		movups xmm1, [tmp2]
//			//		mulps xmm0, xmm1
//			//		movups xmm1, [tmp3]
//			//		movups xmm2, [tmp4]
//			//		mulps xmm1, xmm2
//			//		addps xmm0, xmm1
//			//		movups [result], xmm0
//			//	}
//			//	return result;
//			//}
//
///// THIS SHIT WAS OLD HARD CODED STUFF IN THE PROCESS OF BEING CONVERTED TO TEMPLATES
///// OBSOLETE, LEFT FOR REFERENCE
//
//
//		//template <typename vT>
//		//struct matrix<2, 2, vT>
//		//{
//		//	union
//		//	{
//		//		vector<2, vT> rows[2];
//		//		struct
//		//		{
//		//			vT
//		//				x11, x12,
//		//				x21, x22;
//		//		};
//		//	};
//		//	vector<2, vT>& operator[](bu_i32 i) { return rows[i]; }
//		//	const vector<2, vT>& operator[](bu_i32 i) const { return rows[i]; }
//		//	matrix<2, 2, vT>& operator=(matrix<2, 2, vT> const& other) = default;
//		//	matrix<2, 2, vT>& operator=(matrix<2, 2, vT>&& other) = default;
//		//	bool operator==(matrix<2, 2, vT> const& other) const { return rows[0] == other.rows[0] && rows[1] == other.rows[1]; }
//		//	bool operator!=(matrix<2, 2, vT> const& other) const { return !((*this) == other); }
//		//	matrix<2, 2, vT> operator-() const { return { -x11, -x12, -x21, -x22 }; }
//		//	matrix<2, 2, vT>& operator+=(vT f) { rows[0] += f; rows[1] += f; return *this; }
//		//	matrix<2, 2, vT>& operator-=(vT f) { rows[0] -= f; rows[1] -= f; return *this; }
//		//	matrix<2, 2, vT>& operator*=(vT f) { rows[0] *= f; rows[1] *= f; return *this; }
//		//	matrix<2, 2, vT>& operator/=(vT f) { rows[0] /= f; rows[1] /= f; return *this; }
//		//	friend matrix<2, 2, vT> operator+(matrix<2, 2, vT> const& a, vT b) { return matrix<2, 2, vT>(a) += b; }
//		//	friend matrix<2, 2, vT> operator+(vT b, matrix<2, 2, vT> const& a) { return matrix<2, 2, vT>(a) += b; }
//		//	friend matrix<2, 2, vT> operator-(matrix<2, 2, vT> const& a, vT b) { return matrix<2, 2, vT>(a) -= b; }
//		//	friend matrix<2, 2, vT> operator-(vT b, matrix<2, 2, vT> const& a) { return matrix<2, 2, vT>(a) -= b; }
//		//	friend matrix<2, 2, vT> operator*(matrix<2, 2, vT> const& a, vT b) { return matrix<2, 2, vT>(a) *= b; }
//		//	friend matrix<2, 2, vT> operator*(vT b, matrix<2, 2, vT> const& a) { return matrix<2, 2, vT>(a) *= b; }
//		//	friend matrix<2, 2, vT> operator/(matrix<2, 2, vT> const& a, vT b) { return matrix<2, 2, vT>(a) /= b; }
//		//	friend matrix<2, 2, vT> operator/(vT b, matrix<2, 2, vT> const& a) { return matrix<2, 2, vT>(a) /= b; }
//		//	matrix<2, 2, vT>& operator+=(matrix<2, 2, vT> const& other) { rows[0] += other.rows[0]; rows[1] += other.rows[1]; return *this; }
//		//	matrix<2, 2, vT>& operator-=(matrix<2, 2, vT> const& other) { rows[0] -= other.rows[0]; rows[1] -= other.rows[1]; return *this; }
//		//	friend matrix<2, 2, vT> operator+(matrix<2, 2, vT> const& a, matrix<2, 2, vT> const& b) { return matrix<2, 2, vT>(a) += b; }
//		//	friend matrix<2, 2, vT> operator-(matrix<2, 2, vT> const& a, matrix<2, 2, vT> const& b) { return matrix<2, 2, vT>(a) -= b; }
//		//	matrix<2, 2, vT>& operator*=(matrix<2, 2, vT> const& other)
//		//	{
//		//		//bu_f32 t11 = this->x11, t12 = this->x12,
//		//		//	t21 = this->x21, t22 = this->x22;
//		//		//bu_f32 o11 = other.x11, o12 = other.x12,
//		//		//	o21 = other.x21, o22 = other.x22;
//		//		//x11 = t11 * o11 + t12 * o21;
//		//		//x12 = t11 * o12 + t12 * o22;
//		//		//x21 = t21 * o11 + t22 * o21;
//		//		//x22 = t21 * o12 + t22 * o22;
//		//		//return *this;
//		//		(*this) = mat::mult(*this, other);
//		//	}
//		//	friend matrix<2, 2, vT> operator*(matrix<2, 2, vT> const& a, matrix<2, 2, vT> const& b) { return mat::mult(a, b); }
//		//	friend vector<2, vT> operator*(matrix<2, 2, vT> const& a, vector<2, vT> const& b) { return mat::mult(a, b); }
//		//	matrix<2, 2, vT> T() { return mat::transpose(*this); }
//		//	matrix<2, 2, vT>() = default;
//		//	matrix<2, 2, vT>(vT v11, vT v12, vT v21, vT v22) : rows{ {v11,v12},{v21, v22} } {}
//		//	explicit matrix<2, 2, vT>(vT v) : rows{ {v, v}, {v, v} } {};
//		//	matrix<2, 2, vT>(const matrix<2, 2, vT>& other) = default;
//		//	matrix<2, 2, vT>(matrix<2, 2, vT>&& other) = default;
//		//	~matrix<2, 2, vT>() = default;
//		//};
//
//		//template <typename vT>
//		//struct matrix<3, 3, vT>
//		//{
//		//	union
//		//	{
//		//		vector<3, vT> rows[3];
//		//		struct
//		//		{
//		//			bu_f32
//		//				x11, x12, x13,
//		//				x21, x22, x23,
//		//				x31, x32, x33;
//		//		};
//		//	};
//		//	matrix<3, 3, vT>& operator[](bu_i32 i) { return rows[i]; }
//		//	matrix<3, 3, vT> const& operator[](bu_i32 i) const { return rows[i]; }
//		//	matrix<3, 3, vT>& operator=(matrix<3, 3, vT> const& other) = default;
//		//	matrix<3, 3, vT>& operator=(matrix<3, 3, vT>&& other) = default;
//		//	bool operator==(matrix<3, 3, vT> const& other) const { return rows[0] == other.rows[0] && rows[1] == other.rows[1] && rows[2] == other.rows[2]; }
//		//	bool operator!=(matrix<3, 3, vT> const& other) const { return !((*this) == other); }
//		//	matrix<3, 3, vT> operator-() const { return { -x11, -x12, -x13, -x21, -x22, -x23, -x31, -x32, -x33 }; }
//		//	matrix<3, 3, vT>& operator+=(bu_f32 f) { rows[0] += f; rows[1] += f; rows[2] += f; return *this; }
//		//	matrix<3, 3, vT>& operator-=(bu_f32 f) { rows[0] -= f; rows[1] -= f; rows[2] -= f; return *this; }
//		//	matrix<3, 3, vT>& operator*=(bu_f32 f) { rows[0] *= f; rows[1] *= f; rows[2] *= f; return *this; }
//		//	matrix<3, 3, vT>& operator/=(bu_f32 f) { rows[0] /= f; rows[1] /= f; rows[2] /= f; return *this; }
//		//	friend matrix<3, 3, vT> operator+(matrix<3, 3, vT> const& a, bu_f32 b) { return mat3(a) += b; }
//		//	friend matrix<3, 3, vT> operator+(bu_f32 b, matrix<3, 3, vT> const& a) { return mat3(a) += b; }
//		//	friend matrix<3, 3, vT> operator-(matrix<3, 3, vT> const& a, bu_f32 b) { return mat3(a) -= b; }
//		//	friend matrix<3, 3, vT> operator-(bu_f32 b, matrix<3, 3, vT> const& a) { return mat3(a) -= b; }
//		//	friend matrix<3, 3, vT> operator*(matrix<3, 3, vT> const& a, bu_f32 b) { return mat3(a) *= b; }
//		//	friend matrix<3, 3, vT> operator*(bu_f32 b, matrix<3, 3, vT> const& a) { return mat3(a) *= b; }
//		//	friend matrix<3, 3, vT> operator/(matrix<3, 3, vT> const& a, bu_f32 b) { return mat3(a) /= b; }
//		//	friend matrix<3, 3, vT> operator/(bu_f32 b, matrix<3, 3, vT> const& a) { return mat3(a) /= b; }
//		//	matrix<3, 3, vT>& operator+=(matrix<3, 3, vT> const& other) { rows[0] += other.rows[0]; rows[1] += other.rows[1]; rows[2] += other.rows[2]; return *this; }
//		//	matrix<3, 3, vT>& operator-=(matrix<3, 3, vT> const& other) { rows[0] -= other.rows[0]; rows[1] -= other.rows[1]; rows[2] -= other.rows[2]; return *this; }
//		//	friend matrix<3, 3, vT> operator+(matrix<3, 3, vT> const& a, matrix<3, 3, vT> const& b) { return mat3(a) += b; }
//		//	friend matrix<3, 3, vT> operator-(matrix<3, 3, vT> const& a, matrix<3, 3, vT> const& b) { return mat3(a) -= b; }
//		//	matrix<3, 3, vT>& operator*=(matrix<3, 3, vT> const& other)
//		//	{
//		//		bu_f32
//		//			t11 = this->x11, t12 = this->x12, t13 = this->x13,
//		//			t21 = this->x21, t22 = this->x22, t23 = this->x23,
//		//			t31 = this->x31, t32 = this->x32, t33 = this->x33;
//		//		bu_f32
//		//			o11 = other.x11, o12 = other.x12, o13 = other.x13,
//		//			o21 = other.x21, o22 = other.x22, o23 = other.x23,
//		//			o31 = other.x31, o32 = other.x32, o33 = other.x33;
//		//		x11 = t11 * o11 + t12 * o21 + t13 * o31;
//		//		x12 = t11 * o12 + t12 * o22 + t13 * o32;
//		//		x13 = t11 * o13 + t12 * o23 + t13 * o33;
//		//		x21 = t21 * o11 + t22 * o21 + t23 * o31;
//		//		x22 = t21 * o12 + t22 * o22 + t23 * o32;
//		//		x23 = t21 * o13 + t22 * o23 + t23 * o33;
//		//		x31 = t31 * o11 + t32 * o21 + t33 * o31;
//		//		x32 = t31 * o12 + t32 * o22 + t33 * o32;
//		//		x33 = t31 * o13 + t32 * o23 + t33 * o33;
//		//		return *this;
//		//	}
//		//	friend matrix<3, 3, vT> operator*(matrix<3, 3, vT> const& a, mat3 const& b) { return mat3(a) *= b; }
//		//	matrix<3, 3, vT>() = default;
//		//	matrix<3, 3, vT>(bu_f32 v11, bu_f32 v12, bu_f32 v13, bu_f32 v21, bu_f32 v22, bu_f32 v23, bu_f32 v31, bu_f32 v32, bu_f32 v33)
//		//		:rows{ {v11, v12, v13}, {v21, v22, v23}, {v31, v32, v33} }
//		//	{}
//		//	explicit matrix<3, 3, vT>(bu_f32 v) : rows{ vec3(v), vec3(v), vec3(v) } {};
//		//	matrix<3, 3, vT>(const matrix<3, 3, vT>& other) = default;
//		//	matrix<3, 3, vT>(matrix<3, 3, vT>&& other) = default;
//		//	~matrix<3, 3, vT>() = default;
//		//};
//
//		//	struct mat4
//		//	{
//		//		union
//		//		{
//		//			vec4 rows[4];
//		//			struct
//		//			{
//		//				bu_f32
//		//					x11, x12, x13, x14,
//		//					x21, x22, x23, x24,
//		//					x31, x32, x33, x34,
//		//					x41, x42, x43, x44;
//		//			};
//		//		};
//		//		vec4& operator[](bu_i32 i) { return rows[i]; }
//		//		vec4 const& operator[](bu_i32 i) const { return rows[i]; }
//		//		mat4& operator=(mat4 const& other) = default;
//		//		mat4& operator=(mat4&& other) = default;
//		//		bool operator==(mat4 const& other) const { return rows[0] == other.rows[0] && rows[1] == other.rows[1] && rows[2] == other.rows[2] && rows[3] == other.rows[3]; }
//		//		bool operator!=(mat4 const& other) const { return !((*this) == other); }
//		//		mat4 operator-() const { return { -x11, -x12, -x13, -x14, -x21, -x22, -x23, -x24, -x31, -x32, -x33, -x34, -x41, -x42, -x43, -x44 }; }
//		//		mat4& operator+=(bu_f32 f) { rows[0] += f; rows[1] += f; rows[2] += f; rows[3] += f; return *this; }
//		//		mat4& operator-=(bu_f32 f) { rows[0] -= f; rows[1] -= f; rows[2] -= f; rows[3] -= f; return *this; }
//		//		mat4& operator*=(bu_f32 f) { rows[0] *= f; rows[1] *= f; rows[2] *= f; rows[3] *= f; return *this; }
//		//		mat4& operator/=(bu_f32 f) { rows[0] /= f; rows[1] /= f; rows[2] /= f; rows[3] /= f; return *this; }
//		//		friend mat4 operator+(mat4 const& a, bu_f32 b) { return mat4(a) += b; }
//		//		friend mat4 operator+(bu_f32 b, mat4 const& a) { return mat4(a) += b; }
//		//		friend mat4 operator-(mat4 const& a, bu_f32 b) { return mat4(a) -= b; }
//		//		friend mat4 operator-(bu_f32 b, mat4 const& a) { return mat4(a) -= b; }
//		//		friend mat4 operator*(mat4 const& a, bu_f32 b) { return mat4(a) *= b; }
//		//		friend mat4 operator*(bu_f32 b, mat4 const& a) { return mat4(a) *= b; }
//		//		friend mat4 operator/(mat4 const& a, bu_f32 b) { return mat4(a) /= b; }
//		//		friend mat4 operator/(bu_f32 b, mat4 const& a) { return mat4(a) /= b; }
//		//		mat4& operator+=(mat4 const& other) { rows[0] += other.rows[0]; rows[1] += other.rows[1]; rows[2] += other.rows[2]; rows[3] += other.rows[3]; return *this; }
//		//		mat4& operator-=(mat4 const& other) { rows[0] -= other.rows[0]; rows[1] -= other.rows[1]; rows[2] -= other.rows[2]; rows[3] -= other.rows[3]; return *this; }
//		//		friend mat4 operator+(mat4 const& a, mat4 const& b) { return mat4(a) += b; }
//		//		friend mat4 operator-(mat4 const& a, mat4 const& b) { return mat4(a) -= b; }
//		//		mat4& operator*=(mat4 const& other)
//		//		{
//		//			bu_f32
//		//				t11 = this->x11, t12 = this->x12, t13 = this->x13, t14 = this->x14,
//		//				t21 = this->x21, t22 = this->x22, t23 = this->x23, t24 = this->x24,
//		//				t31 = this->x31, t32 = this->x32, t33 = this->x33, t34 = this->x34,
//		//				t41 = this->x41, t42 = this->x42, t43 = this->x43, t44 = this->x44;
//		//			bu_f32
//		//				o11 = other.x11, o12 = other.x12, o13 = other.x13, o14 = other.x14,
//		//				o21 = other.x21, o22 = other.x22, o23 = other.x23, o24 = other.x24,
//		//				o31 = other.x31, o32 = other.x32, o33 = other.x33, o34 = other.x34,
//		//				o41 = other.x41, o42 = other.x42, o43 = other.x43, o44 = other.x44;
//		//			x11 = t11 * o11 + t12 * o21 + t13 * o31 + t14 * o41;
//		//			x12 = t11 * o12 + t12 * o22 + t13 * o32 + t14 * o42;
//		//			x13 = t11 * o13 + t12 * o23 + t13 * o33 + t14 * o43;
//		//			x14 = t11 * o14 + t12 * o24 + t13 * o34 + t14 * o44;
//		//			x21 = t21 * o11 + t22 * o21 + t23 * o31 + t24 * o41;
//		//			x22 = t21 * o12 + t22 * o22 + t23 * o32 + t24 * o42;
//		//			x23 = t21 * o13 + t22 * o23 + t23 * o33 + t24 * o43;
//		//			x24 = t21 * o14 + t22 * o24 + t23 * o34 + t24 * o44;
//		//			x31 = t31 * o11 + t32 * o21 + t33 * o31 + t34 * o41;
//		//			x32 = t31 * o12 + t32 * o22 + t33 * o32 + t34 * o42;
//		//			x33 = t31 * o13 + t32 * o23 + t33 * o33 + t34 * o43;
//		//			x34 = t31 * o14 + t32 * o24 + t33 * o34 + t34 * o44;
//		//			x41 = t41 * o11 + t42 * o21 + t43 * o31 + t44 * o41;
//		//			x42 = t41 * o12 + t42 * o22 + t43 * o32 + t44 * o42;
//		//			x43 = t41 * o13 + t42 * o23 + t43 * o33 + t44 * o43;
//		//			x44 = t41 * o14 + t42 * o24 + t43 * o34 + t44 * o44
//		//				;
//		//			return *this;
//		//		}
//		//		friend mat4 operator*(mat4 const& a, mat4 const& b) { return mat4(a) *= b; }
//		//		mat4() = default;
//		//		mat4(bu_f32 v11, bu_f32 v12, bu_f32 v13, bu_f32 v14, bu_f32 v21, bu_f32 v22, bu_f32 v23, bu_f32 v24, bu_f32 v31, bu_f32 v32, bu_f32 v33, bu_f32 v34, bu_f32 v41, bu_f32 v42, bu_f32 v43, bu_f32 v44)
//		//			:rows{ {v11, v12, v13, v14}, {v21, v22, v23, v24}, {v31, v32, v33, v34} ,{v41, v42, v43, v44} }
//		//		{}
//		//		explicit mat4(bu_f32 v) : rows{ vec4(v), vec4(v), vec4(v), vec4(v)} {};
//		//		mat4(const mat4& other) = default;
//		//		mat4(mat4&& other) = default;
//		//		~mat4() = default;
//		//	};
//
//
//
//
// // ASM IMPLEMENTATION NO BIT FASTER REEEEEEEEEEE
// matrix<2, 2, bu_f32> mult_sse(matrix<2, 2, bu_f32> const& a, matrix<2, 2, bu_f32> const& b)
//{
//	matrix<2, 2, bu_f32> result;
//	bu_f32 tmp1[4] = { a[0][0], a[0][0], a[1][0], a[1][0] };
//	bu_f32 tmp2[4] = { b[0][0], b[0][1], b[0][0], b[0][1] };
//	bu_f32 tmp3[4] = { a[0][1], a[0][1], a[1][1], a[1][1] };
//	bu_f32 tmp4[4] = { b[1][0], b[1][1], b[1][0], b[1][1] };
//	__asm
//	{
//		movups xmm0, [tmp1]
//		movups xmm1, [tmp2]
//		mulps xmm0, xmm1
//		movups xmm1, [tmp3]
//		movups xmm2, [tmp4]
//		mulps xmm1, xmm2
//		addps xmm0, xmm1
//		movups [result], xmm0
//	}
//	return result;
//}
// THIS SHIT WAS OLD HARD CODED STUFF IN THE PROCESS OF BEING CONVERTED TO TEMPLATES
// OBSOLETE, LEFT FOR REFERENCE
// template <typename vT>
// struct matrix<2, 2, vT>
//{
//	union
//	{
//		vector<2, vT> rows[2];
//		struct
//		{
//			vT
//				x11, x12,
//				x21, x22;
//		};
//	};
//	vector<2, vT>& operator[](bu_i32 i) { return rows[i]; }
//	const vector<2, vT>& operator[](bu_i32 i) const { return rows[i]; }
//	matrix<2, 2, vT>& operator=(matrix<2, 2, vT> const& other) = default;
//	matrix<2, 2, vT>& operator=(matrix<2, 2, vT>&& other) = default;
//	bool operator==(matrix<2, 2, vT> const& other) const { return rows[0] == other.rows[0] && rows[1] == other.rows[1]; }
//	bool operator!=(matrix<2, 2, vT> const& other) const { return !((*this) == other); }
//	matrix<2, 2, vT> operator-() const { return { -x11, -x12, -x21, -x22 }; }
//	matrix<2, 2, vT>& operator+=(vT f) { rows[0] += f; rows[1] += f; return *this; }
//	matrix<2, 2, vT>& operator-=(vT f) { rows[0] -= f; rows[1] -= f; return *this; }
//	matrix<2, 2, vT>& operator*=(vT f) { rows[0] *= f; rows[1] *= f; return *this; }
//	matrix<2, 2, vT>& operator/=(vT f) { rows[0] /= f; rows[1] /= f; return *this; }
//	friend matrix<2, 2, vT> operator+(matrix<2, 2, vT> const& a, vT b) { return matrix<2, 2, vT>(a) += b; }
//	friend matrix<2, 2, vT> operator+(vT b, matrix<2, 2, vT> const& a) { return matrix<2, 2, vT>(a) += b; }
//	friend matrix<2, 2, vT> operator-(matrix<2, 2, vT> const& a, vT b) { return matrix<2, 2, vT>(a) -= b; }
//	friend matrix<2, 2, vT> operator-(vT b, matrix<2, 2, vT> const& a) { return matrix<2, 2, vT>(a) -= b; }
//	friend matrix<2, 2, vT> operator*(matrix<2, 2, vT> const& a, vT b) { return matrix<2, 2, vT>(a) *= b; }
//	friend matrix<2, 2, vT> operator*(vT b, matrix<2, 2, vT> const& a) { return matrix<2, 2, vT>(a) *= b; }
//	friend matrix<2, 2, vT> operator/(matrix<2, 2, vT> const& a, vT b) { return matrix<2, 2, vT>(a) /= b; }
//	friend matrix<2, 2, vT> operator/(vT b, matrix<2, 2, vT> const& a) { return matrix<2, 2, vT>(a) /= b; }
//	matrix<2, 2, vT>& operator+=(matrix<2, 2, vT> const& other) { rows[0] += other.rows[0]; rows[1] += other.rows[1]; return *this; }
//	matrix<2, 2, vT>& operator-=(matrix<2, 2, vT> const& other) { rows[0] -= other.rows[0]; rows[1] -= other.rows[1]; return *this; }
//	friend matrix<2, 2, vT> operator+(matrix<2, 2, vT> const& a, matrix<2, 2, vT> const& b) { return matrix<2, 2, vT>(a) += b; }
//	friend matrix<2, 2, vT> operator-(matrix<2, 2, vT> const& a, matrix<2, 2, vT> const& b) { return matrix<2, 2, vT>(a) -= b; }
//	matrix<2, 2, vT>& operator*=(matrix<2, 2, vT> const& other)
//	{
//		//bu_f32 t11 = this->x11, t12 = this->x12,
//		//	t21 = this->x21, t22 = this->x22;
//		//bu_f32 o11 = other.x11, o12 = other.x12,
//		//	o21 = other.x21, o22 = other.x22;
//		//x11 = t11 * o11 + t12 * o21;
//		//x12 = t11 * o12 + t12 * o22;
//		//x21 = t21 * o11 + t22 * o21;
//		//x22 = t21 * o12 + t22 * o22;
//		//return *this;
//		(*this) = mat::mult(*this, other);
//	}
//	friend matrix<2, 2, vT> operator*(matrix<2, 2, vT> const& a, matrix<2, 2, vT> const& b) { return mat::mult(a, b); }
//	friend vector<2, vT> operator*(matrix<2, 2, vT> const& a, vector<2, vT> const& b) { return mat::mult(a, b); }
//	matrix<2, 2, vT> T() { return mat::transpose(*this); }
//	matrix<2, 2, vT>() = default;
//	matrix<2, 2, vT>(vT v11, vT v12, vT v21, vT v22) : rows{ {v11,v12},{v21, v22} } {}
//	explicit matrix<2, 2, vT>(vT v) : rows{ {v, v}, {v, v} } {};
//	matrix<2, 2, vT>(const matrix<2, 2, vT>& other) = default;
//	matrix<2, 2, vT>(matrix<2, 2, vT>&& other) = default;
//	~matrix<2, 2, vT>() = default;
//};
// template <typename vT>
// struct matrix<3, 3, vT>
//{
//	union
//	{
//		vector<3, vT> rows[3];
//		struct
//		{
//			bu_f32
//				x11, x12, x13,
//				x21, x22, x23,
//				x31, x32, x33;
//		};
//	};
//	matrix<3, 3, vT>& operator[](bu_i32 i) { return rows[i]; }
//	matrix<3, 3, vT> const& operator[](bu_i32 i) const { return rows[i]; }
//	matrix<3, 3, vT>& operator=(matrix<3, 3, vT> const& other) = default;
//	matrix<3, 3, vT>& operator=(matrix<3, 3, vT>&& other) = default;
//	bool operator==(matrix<3, 3, vT> const& other) const { return rows[0] == other.rows[0] && rows[1] == other.rows[1] && rows[2] == other.rows[2]; }
//	bool operator!=(matrix<3, 3, vT> const& other) const { return !((*this) == other); }
//	matrix<3, 3, vT> operator-() const { return { -x11, -x12, -x13, -x21, -x22, -x23, -x31, -x32, -x33 }; }
//	matrix<3, 3, vT>& operator+=(bu_f32 f) { rows[0] += f; rows[1] += f; rows[2] += f; return *this; }
//	matrix<3, 3, vT>& operator-=(bu_f32 f) { rows[0] -= f; rows[1] -= f; rows[2] -= f; return *this; }
//	matrix<3, 3, vT>& operator*=(bu_f32 f) { rows[0] *= f; rows[1] *= f; rows[2] *= f; return *this; }
//	matrix<3, 3, vT>& operator/=(bu_f32 f) { rows[0] /= f; rows[1] /= f; rows[2] /= f; return *this; }
//	friend matrix<3, 3, vT> operator+(matrix<3, 3, vT> const& a, bu_f32 b) { return mat3(a) += b; }
//	friend matrix<3, 3, vT> operator+(bu_f32 b, matrix<3, 3, vT> const& a) { return mat3(a) += b; }
//	friend matrix<3, 3, vT> operator-(matrix<3, 3, vT> const& a, bu_f32 b) { return mat3(a) -= b; }
//	friend matrix<3, 3, vT> operator-(bu_f32 b, matrix<3, 3, vT> const& a) { return mat3(a) -= b; }
//	friend matrix<3, 3, vT> operator*(matrix<3, 3, vT> const& a, bu_f32 b) { return mat3(a) *= b; }
//	friend matrix<3, 3, vT> operator*(bu_f32 b, matrix<3, 3, vT> const& a) { return mat3(a) *= b; }
//	friend matrix<3, 3, vT> operator/(matrix<3, 3, vT> const& a, bu_f32 b) { return mat3(a) /= b; }
//	friend matrix<3, 3, vT> operator/(bu_f32 b, matrix<3, 3, vT> const& a) { return mat3(a) /= b; }
//	matrix<3, 3, vT>& operator+=(matrix<3, 3, vT> const& other) { rows[0] += other.rows[0]; rows[1] += other.rows[1]; rows[2] += other.rows[2]; return *this; }
//	matrix<3, 3, vT>& operator-=(matrix<3, 3, vT> const& other) { rows[0] -= other.rows[0]; rows[1] -= other.rows[1]; rows[2] -= other.rows[2]; return *this; }
//	friend matrix<3, 3, vT> operator+(matrix<3, 3, vT> const& a, matrix<3, 3, vT> const& b) { return mat3(a) += b; }
//	friend matrix<3, 3, vT> operator-(matrix<3, 3, vT> const& a, matrix<3, 3, vT> const& b) { return mat3(a) -= b; }
//	matrix<3, 3, vT>& operator*=(matrix<3, 3, vT> const& other)
//	{
//		bu_f32
//			t11 = this->x11, t12 = this->x12, t13 = this->x13,
//			t21 = this->x21, t22 = this->x22, t23 = this->x23,
//			t31 = this->x31, t32 = this->x32, t33 = this->x33;
//		bu_f32
//			o11 = other.x11, o12 = other.x12, o13 = other.x13,
//			o21 = other.x21, o22 = other.x22, o23 = other.x23,
//			o31 = other.x31, o32 = other.x32, o33 = other.x33;
//		x11 = t11 * o11 + t12 * o21 + t13 * o31;
//		x12 = t11 * o12 + t12 * o22 + t13 * o32;
//		x13 = t11 * o13 + t12 * o23 + t13 * o33;
//		x21 = t21 * o11 + t22 * o21 + t23 * o31;
//		x22 = t21 * o12 + t22 * o22 + t23 * o32;
//		x23 = t21 * o13 + t22 * o23 + t23 * o33;
//		x31 = t31 * o11 + t32 * o21 + t33 * o31;
//		x32 = t31 * o12 + t32 * o22 + t33 * o32;
//		x33 = t31 * o13 + t32 * o23 + t33 * o33;
//		return *this;
//	}
//	friend matrix<3, 3, vT> operator*(matrix<3, 3, vT> const& a, mat3 const& b) { return mat3(a) *= b; }
//	matrix<3, 3, vT>() = default;
//	matrix<3, 3, vT>(bu_f32 v11, bu_f32 v12, bu_f32 v13, bu_f32 v21, bu_f32 v22, bu_f32 v23, bu_f32 v31, bu_f32 v32, bu_f32 v33)
//		:rows{ {v11, v12, v13}, {v21, v22, v23}, {v31, v32, v33} }
//	{}
//	explicit matrix<3, 3, vT>(bu_f32 v) : rows{ vec3(v), vec3(v), vec3(v) } {};
//	matrix<3, 3, vT>(const matrix<3, 3, vT>& other) = default;
//	matrix<3, 3, vT>(matrix<3, 3, vT>&& other) = default;
//	~matrix<3, 3, vT>() = default;
//};
//	struct mat4
//	{
//		union
//		{
//			vec4 rows[4];
//			struct
//			{
//				bu_f32
//					x11, x12, x13, x14,
//					x21, x22, x23, x24,
//					x31, x32, x33, x34,
//					x41, x42, x43, x44;
//			};
//		};
//		vec4& operator[](bu_i32 i) { return rows[i]; }
//		vec4 const& operator[](bu_i32 i) const { return rows[i]; }
//		mat4& operator=(mat4 const& other) = default;
//		mat4& operator=(mat4&& other) = default;
//		bool operator==(mat4 const& other) const { return rows[0] == other.rows[0] && rows[1] == other.rows[1] && rows[2] == other.rows[2] && rows[3] == other.rows[3]; }
//		bool operator!=(mat4 const& other) const { return !((*this) == other); }
//		mat4 operator-() const { return { -x11, -x12, -x13, -x14, -x21, -x22, -x23, -x24, -x31, -x32, -x33, -x34, -x41, -x42, -x43, -x44 }; }
//		mat4& operator+=(bu_f32 f) { rows[0] += f; rows[1] += f; rows[2] += f; rows[3] += f; return *this; }
//		mat4& operator-=(bu_f32 f) { rows[0] -= f; rows[1] -= f; rows[2] -= f; rows[3] -= f; return *this; }
//		mat4& operator*=(bu_f32 f) { rows[0] *= f; rows[1] *= f; rows[2] *= f; rows[3] *= f; return *this; }
//		mat4& operator/=(bu_f32 f) { rows[0] /= f; rows[1] /= f; rows[2] /= f; rows[3] /= f; return *this; }
//		friend mat4 operator+(mat4 const& a, bu_f32 b) { return mat4(a) += b; }
//		friend mat4 operator+(bu_f32 b, mat4 const& a) { return mat4(a) += b; }
//		friend mat4 operator-(mat4 const& a, bu_f32 b) { return mat4(a) -= b; }
//		friend mat4 operator-(bu_f32 b, mat4 const& a) { return mat4(a) -= b; }
//		friend mat4 operator*(mat4 const& a, bu_f32 b) { return mat4(a) *= b; }
//		friend mat4 operator*(bu_f32 b, mat4 const& a) { return mat4(a) *= b; }
//		friend mat4 operator/(mat4 const& a, bu_f32 b) { return mat4(a) /= b; }
//		friend mat4 operator/(bu_f32 b, mat4 const& a) { return mat4(a) /= b; }
//		mat4& operator+=(mat4 const& other) { rows[0] += other.rows[0]; rows[1] += other.rows[1]; rows[2] += other.rows[2]; rows[3] += other.rows[3]; return *this; }
//		mat4& operator-=(mat4 const& other) { rows[0] -= other.rows[0]; rows[1] -= other.rows[1]; rows[2] -= other.rows[2]; rows[3] -= other.rows[3]; return *this; }
//		friend mat4 operator+(mat4 const& a, mat4 const& b) { return mat4(a) += b; }
//		friend mat4 operator-(mat4 const& a, mat4 const& b) { return mat4(a) -= b; }
//		mat4& operator*=(mat4 const& other)
//		{
//			bu_f32
//				t11 = this->x11, t12 = this->x12, t13 = this->x13, t14 = this->x14,
//				t21 = this->x21, t22 = this->x22, t23 = this->x23, t24 = this->x24,
//				t31 = this->x31, t32 = this->x32, t33 = this->x33, t34 = this->x34,
//				t41 = this->x41, t42 = this->x42, t43 = this->x43, t44 = this->x44;
//			bu_f32
//				o11 = other.x11, o12 = other.x12, o13 = other.x13, o14 = other.x14,
//				o21 = other.x21, o22 = other.x22, o23 = other.x23, o24 = other.x24,
//				o31 = other.x31, o32 = other.x32, o33 = other.x33, o34 = other.x34,
//				o41 = other.x41, o42 = other.x42, o43 = other.x43, o44 = other.x44;
//			x11 = t11 * o11 + t12 * o21 + t13 * o31 + t14 * o41;
//			x12 = t11 * o12 + t12 * o22 + t13 * o32 + t14 * o42;
//			x13 = t11 * o13 + t12 * o23 + t13 * o33 + t14 * o43;
//			x14 = t11 * o14 + t12 * o24 + t13 * o34 + t14 * o44;
//			x21 = t21 * o11 + t22 * o21 + t23 * o31 + t24 * o41;
//			x22 = t21 * o12 + t22 * o22 + t23 * o32 + t24 * o42;
//			x23 = t21 * o13 + t22 * o23 + t23 * o33 + t24 * o43;
//			x24 = t21 * o14 + t22 * o24 + t23 * o34 + t24 * o44;
//			x31 = t31 * o11 + t32 * o21 + t33 * o31 + t34 * o41;
//			x32 = t31 * o12 + t32 * o22 + t33 * o32 + t34 * o42;
//			x33 = t31 * o13 + t32 * o23 + t33 * o33 + t34 * o43;
//			x34 = t31 * o14 + t32 * o24 + t33 * o34 + t34 * o44;
//			x41 = t41 * o11 + t42 * o21 + t43 * o31 + t44 * o41;
//			x42 = t41 * o12 + t42 * o22 + t43 * o32 + t44 * o42;
//			x43 = t41 * o13 + t42 * o23 + t43 * o33 + t44 * o43;
//			x44 = t41 * o14 + t42 * o24 + t43 * o34 + t44 * o44
//				;
//			return *this;
//		}
//		friend mat4 operator*(mat4 const& a, mat4 const& b) { return mat4(a) *= b; }
//		mat4() = default;
//		mat4(bu_f32 v11, bu_f32 v12, bu_f32 v13, bu_f32 v14, bu_f32 v21, bu_f32 v22, bu_f32 v23, bu_f32 v24, bu_f32 v31, bu_f32 v32, bu_f32 v33, bu_f32 v34, bu_f32 v41, bu_f32 v42, bu_f32 v43, bu_f32 v44)
//			:rows{ {v11, v12, v13, v14}, {v21, v22, v23, v24}, {v31, v32, v33, v34} ,{v41, v42, v43, v44} }
//		{}
//		explicit mat4(bu_f32 v) : rows{ vec4(v), vec4(v), vec4(v), vec4(v)} {};
//		mat4(const mat4& other) = default;
//		mat4(mat4&& other) = default;
//		~mat4() = default;
//	};
