#include "bunny/angle.h"

#include <gtest/gtest.h>
#include <span>

template<int left = 0, int right = 0, typename T>
constexpr auto slice(T&& container) {
  if constexpr (right > 0) {
    return std::span(begin(std::forward<T>(container)) + left, begin(std::forward<T>(container)) + right);
  } else {
    return std::span(begin(std::forward<T>(container)) + left, end(std::forward<T>(container)) + right);
  }
}
bunny::bu_vec<bunny::f64> const inputData = {0,
                                             bunny::constants::PI_4,
                                             bunny::constants::PI_2,
                                             bunny::constants::PI_2 + bunny::constants::PI_4,
                                             bunny::constants::PI,
                                             bunny::constants::PI + bunny::constants::PI_4,
                                             bunny::constants::PI + bunny::constants::PI_2,
                                             bunny::constants::PI + bunny::constants::PI_2 + bunny::constants::PI_4,
                                             bunny::constants::PI * 2,
                                             0,
                                             45,
                                             90,
                                             135,
                                             180,
                                             225,
                                             270,
                                             315,
                                             360};
static const auto inputDegrees            = slice<9, -1>(inputData);
static const auto inputRad                = slice<0, 9>(inputData);

static constexpr bunny::f64 f64_accuracy = .0000000000001;
static constexpr bunny::f32 f32_accuracy = .000001;

static constexpr auto PI     = bunny::constants::PI;
static constexpr auto PI_2   = bunny::constants::PI_2;
static constexpr auto PI_4   = bunny::constants::PI_4;
static constexpr auto PI_INV = bunny::constants::PI_INV;

TEST(AngleTest, fromDeg) {
  for (auto const& val : inputDegrees) {
    auto a = bunny::anglef32::from_deg(val);
    EXPECT_FLOAT_EQ(a.deg(), val) << "from degree failed for f32 type angle " << val;
    auto b = bunny::anglef64::from_deg(val);
    EXPECT_DOUBLE_EQ(b.deg(), val) << "from degree failed for f64 type angle " << val;
  }
}
TEST(AngleTest, fromRad) {
  for (auto const& val : inputRad) {
    auto a = bunny::anglef32::from_rad(val);
    EXPECT_FLOAT_EQ(a.rad(), val) << "from rad failed for f32 type angle " << val;
    auto b = bunny::anglef64::from_rad(val);
    EXPECT_DOUBLE_EQ(b.rad(), val) << "from rad failed for f64 type angle " << val;
  }
}
TEST(AngleTest, rad) {
  auto const radLen = inputRad.size();
  for (int i = 0; i < radLen; i++) {
    auto a = bunny::anglef32::from_deg(inputDegrees[i]);
    auto b = bunny::anglef64::from_deg(inputDegrees[i]);
    auto c = bunny::anglef32::from_rad(inputRad[i]);
    auto d = bunny::anglef64::from_rad(inputRad[i]);
    EXPECT_FLOAT_EQ(a.rad(), inputRad[i]) << "rad failed for f32 deg type angle " << inputDegrees[i];
    EXPECT_DOUBLE_EQ(b.rad(), inputRad[i]) << "rad failed for f64 deg type angle " << inputDegrees[i];
    EXPECT_FLOAT_EQ(c.rad(), inputRad[i]) << "rad failed for f32 rad type angle " << inputRad[i];
    EXPECT_DOUBLE_EQ(d.rad(), inputRad[i]) << "rad failed for f64 rad type angle " << inputRad[i];
  }
}
TEST(AngleTest, deg) {
  auto const radLen = inputRad.size();
  for (int i = 0; i < radLen; i++) {
    auto a = bunny::anglef32::from_deg(inputDegrees[i]);
    auto b = bunny::anglef64::from_deg(inputDegrees[i]);
    auto c = bunny::anglef32::from_rad(inputRad[i]);
    auto d = bunny::anglef64::from_rad(inputRad[i]);
    EXPECT_FLOAT_EQ(a.deg(), inputDegrees[i]) << "deg failed for f32 deg type angle " << inputDegrees[i];
    EXPECT_DOUBLE_EQ(b.deg(), inputDegrees[i]) << "deg failed for f64 deg type angle " << inputDegrees[i];
    EXPECT_FLOAT_EQ(c.deg(), inputDegrees[i]) << "deg failed for f32 rad type angle " << inputRad[i];
    EXPECT_DOUBLE_EQ(d.deg(), inputDegrees[i]) << "deg failed for f64 rad type angle " << inputRad[i];
  }
}
TEST(AngleTest, sin) {
  auto const radLen = inputRad.size();
  for (int i = 0; i < radLen; i++) {
    auto f64res = sin(inputRad[i]);
    auto f32res = sinf(inputRad[i]);
    auto a      = bunny::anglef32::from_rad(inputRad[i]);
    auto b      = bunny::anglef64::from_rad(inputRad[i]);
    auto c      = bunny::anglef32::from_deg(inputDegrees[i]);
    auto d      = bunny::anglef64::from_deg(inputDegrees[i]);
    EXPECT_NEAR(a.sin(), f32res, f32_accuracy) << "sin failed for f32 rad type angle " << inputRad[i];
    EXPECT_NEAR(b.sin(), f64res, f64_accuracy) << "sin failed for f64 rad type angle " << inputRad[i];
    EXPECT_NEAR(c.sin(), f32res, f32_accuracy) << "sin failed for f32 deg type angle " << inputDegrees[i];
    EXPECT_NEAR(d.sin(), f64res, f64_accuracy) << "sin failed for f64 deg type angle " << inputDegrees[i];
  }
}
TEST(AngleTest, cos) {
  auto const radLen = inputRad.size();
  for (int i = 0; i < radLen; i++) {
    auto f64res = cos(inputRad[i]);
    auto f32res = cosf(inputRad[i]);
    auto a      = bunny::anglef32::from_rad(inputRad[i]);
    auto b      = bunny::anglef64::from_rad(inputRad[i]);
    auto c      = bunny::anglef32::from_deg(inputDegrees[i]);
    auto d      = bunny::anglef64::from_deg(inputDegrees[i]);
    EXPECT_NEAR(a.cos(), f32res, f32_accuracy) << "cos failed for f32 rad type angle " << inputRad[i];
    EXPECT_NEAR(b.cos(), f64res, f64_accuracy) << "cos failed for f64 rad type angle " << inputRad[i];
    EXPECT_NEAR(c.cos(), f32res, f32_accuracy) << "cos failed for f32 deg type angle " << inputDegrees[i];
    EXPECT_NEAR(d.cos(), f64res, f64_accuracy) << "cos failed for f64 deg type angle " << inputDegrees[i];
  }
}
TEST(AngleTest, tan) {
  auto const radLen = inputRad.size();
  for (int i = 0; i < radLen; i++) {
    auto f64res = tan(inputRad[i]);
    auto f32res = tanf(inputRad[i]);
    auto a      = bunny::anglef32::from_rad(inputRad[i]);
    auto b      = bunny::anglef64::from_rad(inputRad[i]);
    auto c      = bunny::anglef32::from_deg(inputDegrees[i]);
    auto d      = bunny::anglef64::from_deg(inputDegrees[i]);
    EXPECT_NEAR(a.tan(), f32res, f32_accuracy) << "tan failed for f32 rad type angle " << inputRad[i];
    EXPECT_NEAR(b.tan(), f64res, f64_accuracy) << "tan failed for f64 rad type angle " << inputRad[i];
    EXPECT_NEAR(c.tan(), f32res, f32_accuracy) << "tan failed for f32 deg type angle " << inputDegrees[i];
    EXPECT_NEAR(d.tan(), f64res, f64_accuracy) << "tan failed for f64 deg type angle " << inputDegrees[i];
  }
}
TEST(AngleTest, sinh) {
  auto const radLen = inputRad.size();
  for (int i = 0; i < radLen; i++) {
    auto f64res = sinh(inputRad[i]);
    auto f32res = sinhf(inputRad[i]);
    auto a      = bunny::anglef32::from_rad(inputRad[i]);
    auto b      = bunny::anglef64::from_rad(inputRad[i]);
    auto c      = bunny::anglef32::from_deg(inputDegrees[i]);
    auto d      = bunny::anglef64::from_deg(inputDegrees[i]);
    EXPECT_NEAR(a.sinh(), f32res, f32_accuracy) << "sinh failed for f32 rad type angle " << inputRad[i];
    EXPECT_NEAR(b.sinh(), f64res, f64_accuracy) << "sinh failed for f64 rad type angle " << inputRad[i];
    EXPECT_NEAR(c.sinh(), f32res, f32_accuracy) << "sinh failed for f32 deg type angle " << inputDegrees[i];
    EXPECT_NEAR(d.sinh(), f64res, f64_accuracy) << "sinh failed for f64 deg type angle " << inputDegrees[i];
  }
}
TEST(AngleTest, cosh) {
  auto const radLen = inputRad.size();
  for (int i = 0; i < radLen; i++) {
    auto f64res = cosh(inputRad[i]);
    auto f32res = coshf(inputRad[i]);
    auto a      = bunny::anglef32::from_rad(inputRad[i]);
    auto b      = bunny::anglef64::from_rad(inputRad[i]);
    auto c      = bunny::anglef32::from_deg(inputDegrees[i]);
    auto d      = bunny::anglef64::from_deg(inputDegrees[i]);
    EXPECT_NEAR(a.cosh(), f32res, f32_accuracy) << "cosh failed for f32 rad type angle " << inputRad[i];
    EXPECT_NEAR(b.cosh(), f64res, f64_accuracy) << "cosh failed for f64 rad type angle " << inputRad[i];
    EXPECT_NEAR(c.cosh(), f32res, f32_accuracy) << "cosh failed for f32 deg type angle " << inputDegrees[i];
    EXPECT_NEAR(d.cosh(), f64res, f64_accuracy) << "cosh failed for f64 deg type angle " << inputDegrees[i];
  }
}
TEST(AngleTest, tanh) {
  auto const radLen = inputRad.size();
  for (int i = 0; i < radLen; i++) {
    auto f64res = tanh(inputRad[i]);
    auto f32res = tanhf(inputRad[i]);
    auto a      = bunny::anglef32::from_rad(inputRad[i]);
    auto b      = bunny::anglef64::from_rad(inputRad[i]);
    auto c      = bunny::anglef32::from_deg(inputDegrees[i]);
    auto d      = bunny::anglef64::from_deg(inputDegrees[i]);
    EXPECT_NEAR(a.tanh(), f32res, f32_accuracy) << "tanh failed for f32 rad type angle " << inputRad[i];
    EXPECT_NEAR(b.tanh(), f64res, f64_accuracy) << "tanh failed for f64 rad type angle " << inputRad[i];
    EXPECT_NEAR(c.tanh(), f32res, f32_accuracy) << "tanh failed for f32 deg type angle " << inputDegrees[i];
    EXPECT_NEAR(d.tanh(), f64res, f64_accuracy) << "tanh failed for f64 deg type angle " << inputDegrees[i];
  }
}
TEST(AngleTest, asin) {
  auto const radLen = inputRad.size();
  for (int i = 0; i < radLen; i++) {
    auto preA = bunny::anglef32::from_rad(inputRad[i]);
    auto preB = bunny::anglef64::from_rad(inputRad[i]);
    auto a    = bunny::anglef32::asin(preA.sin());
    auto b    = bunny::anglef64::asin(preB.sin());
    EXPECT_NEAR(a.rad(), asinf(preA.sin()), sqrt(f32_accuracy)) << "asin failed for f32 rad type angle " << inputDegrees[i];
    EXPECT_NEAR(b.rad(), asin(preB.sin()), sqrt(f64_accuracy)) << "asin failed for f64 rad type angle " << inputDegrees[i];
  }
}
TEST(AngleTest, acos) {
  auto const radLen = inputRad.size();
  for (int i = 0; i < radLen; i++) {
    auto preA = bunny::anglef32::from_rad(inputRad[i]);
    auto preB = bunny::anglef64::from_rad(inputRad[i]);
    auto a    = bunny::anglef32::acos(preA.cos());
    auto b    = bunny::anglef64::acos(preB.cos());
    EXPECT_NEAR(a.rad(), acosf(preA.cos()), sqrt(f32_accuracy)) << "acos failed for f32 rad type angle " << inputDegrees[i];
    EXPECT_NEAR(b.rad(), acos(preB.cos()), sqrt(f64_accuracy)) << "acos failed for f64 rad type angle " << inputDegrees[i];
  }
}
TEST(AngleTest, atan) {
  auto const radLen = inputRad.size();
  for (int i = 0; i < radLen; i++) {
    auto preA = bunny::anglef32::from_rad(inputRad[i]);
    auto preB = bunny::anglef64::from_rad(inputRad[i]);
    auto a    = bunny::anglef32::atan(preA.tan());
    auto b    = bunny::anglef64::atan(preB.tan());
    EXPECT_NEAR(a.rad(), atanf(preA.tan()), sqrt(f32_accuracy)) << "atan failed for f32 rad type angle " << inputDegrees[i];
    EXPECT_NEAR(b.rad(), atan(preB.tan()), sqrt(f64_accuracy)) << "atan failed for f64 rad type angle " << inputDegrees[i];
  }
}
TEST(AngleTest, asinh) {
  auto const radLen = inputRad.size();
  for (int i = 0; i < radLen; i++) {
    auto preA = bunny::anglef32::from_rad(inputRad[i]);
    auto preB = bunny::anglef64::from_rad(inputRad[i]);
    auto a    = bunny::anglef32::asinh(preA.sinh());
    auto b    = bunny::anglef64::asinh(preB.sinh());
    EXPECT_NEAR(a.rad(), asinhf(preA.sinh()), sqrt(f32_accuracy)) << "asinh failed for f32 rad type angle " << inputDegrees[i];
    EXPECT_NEAR(b.rad(), asinh(preB.sinh()), sqrt(f64_accuracy)) << "asinh failed for f64 rad type angle " << inputDegrees[i];
  }
}
TEST(AngleTest, acosh) {
  auto const radLen = inputRad.size();
  for (int i = 0; i < radLen; i++) {
    auto preA = bunny::anglef32::from_rad(inputRad[i]);
    auto preB = bunny::anglef64::from_rad(inputRad[i]);
    auto a    = bunny::anglef32::acosh(preA.cosh());
    auto b    = bunny::anglef64::acosh(preB.cosh());
    EXPECT_NEAR(a.rad(), acoshf(preA.cosh()), sqrt(f32_accuracy)) << "acosh failed for f32 rad type angle " << inputDegrees[i];
    EXPECT_NEAR(b.rad(), acosh(preB.cosh()), sqrt(f64_accuracy)) << "acosh failed for f64 rad type angle " << inputDegrees[i];
  }
}
TEST(AngleTest, atanh) {
  auto const radLen = inputRad.size();
  for (int i = 0; i < radLen; i++) {
    auto preA = bunny::anglef32::from_rad(inputRad[i]);
    auto preB = bunny::anglef64::from_rad(inputRad[i]);
    auto a    = bunny::anglef32::atanh(preA.tanh());
    auto b    = bunny::anglef64::atanh(preB.tanh());
    EXPECT_NEAR(a.rad(), atanhf(preA.tanh()), sqrt(f32_accuracy)) << "atanh failed for f32 rad type angle " << inputDegrees[i];
    EXPECT_NEAR(b.rad(), atanh(preB.tanh()), sqrt(f64_accuracy)) << "atanh failed for f64 rad type angle " << inputDegrees[i];
  }
}
TEST(AngleTest, atan2) {
  auto preA = bunny::anglef32::from_deg(45);
  auto preB = bunny::anglef64::from_deg(0);
  auto preC = bunny::anglef64::from_deg(-45);
  auto a    = bunny::anglef32::atan2(1., 1.);
  auto b    = bunny::anglef64::atan2(0., 1.);
  auto c    = bunny::anglef64::atan2(-1., 1.);
  EXPECT_NEAR(a.rad(), preA.rad(), f32_accuracy) << "atanh failed for f32 rad type angle";
  EXPECT_NEAR(b.rad(), preB.rad(), f64_accuracy) << "atanh failed for f64 rad type angle";
  EXPECT_NEAR(c.rad(), preC.rad(), f64_accuracy) << "atanh failed for f64 rad type angle";
}
TEST(AngleTest, normalize) {
  auto const radTestData = bunny::bu_vec<bunny::bu_arr<bunny::f64, 3>>{
    {-8 * PI, 0, 0},
    {-4 * PI + PI_4, PI_4, PI_4},
    {-PI, -PI, PI},
    {0, 0, 0},
    {PI_4, PI_4, PI_4},
    {PI, -PI, PI},
    {6 * PI, 0, 0},
    {1453 * PI, PI, PI}};
  auto const degTestData = bunny::bu_vec<bunny::bu_arr<bunny::f64, 3>>{
    {-1080, 2222, 3333},
    {-1380.564, 2222, 3333},
    {-65.3, 2222, 3333},
    {0, 0, 0},
    {49.135, 2222, 3333},
    {194, 2222, 3333},
    {360, 2222, 3333},
    {399, 2222, 3333}};

  for (auto const rad : radTestData) {
    auto a = bunny::anglef32::from_rad(rad[0]);
    auto b = bunny::anglef64::from_rad(rad[0]);
    EXPECT_NEAR(a.normalize(bunny::math::AngleNormalization::ZeroToTwoPi).rad(), rad[1], f32_accuracy);
    EXPECT_NEAR(b.normalize(bunny::math::AngleNormalization::ZeroToTwoPi).rad(), rad[1], f64_accuracy);
    EXPECT_NEAR(a.normalize(bunny::math::AngleNormalization::NegativePiToPi).rad(), rad[2], f32_accuracy);
    EXPECT_NEAR(b.normalize(bunny::math::AngleNormalization::NegativePiToPi).rad(), rad[2], f64_accuracy);
  }
}
