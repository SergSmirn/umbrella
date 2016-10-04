
#include "gtest/gtest.h"
#include "point2d.hpp"
#include "box2d.hpp"
#include "ray2d.hpp"
#include <sstream>
#include <unordered_set>

Point2D c0{0,0}, c1{-1,-1}, c2{1,1}, c3{2,2}, c4{5,5}, c5{-3,-3}, c6{10,10}, c7{6,6};

// Тесты для прямоугольника.
TEST(rayandbox_test, test_box_construction)
{
  // Тест на создание объекта по умолчанию.
  Box2d p1;
  EXPECT_EQ(p1.LeftBot(), c0);
  EXPECT_EQ(p1.RightTop(), c0);

  // Тест на создание объекта с параметрами.
  Box2d p2 = { c1, c2 };
  EXPECT_EQ(p2.LeftBot(), c1);
  EXPECT_EQ(p2.RightTop(), c2);

  // Тест на создание копии объекта.
  Box2d p3 = p2;
  EXPECT_EQ(p3, p2);
}

TEST(rayandbox_test, test_box_initializer_list)
{
  Box2d p1 = { c2, c3, c4 };
  EXPECT_EQ(p1.LeftBot(), c2);
  EXPECT_EQ(p1.RightTop(), c3);

  Box2d p2 = { c2 };
  EXPECT_EQ(p2.LeftBot(), c2);
  EXPECT_EQ(p2.RightTop(), c0);
}

TEST(rayandbox_test, test_box_assignment)
{
  Box2d p1;
  p1 = { c1, c2 };
  EXPECT_EQ(p1, Box2d(c1, c2));
}

TEST(rayandbox_test, test_box_equality)
{
  Box2d p1 = { c1, c2 };
  Box2d p2 = { c1, c2 };
  Box2d p3 = { c3, c4 };
  Box2d p4 = { c2, c4 };

  EXPECT_EQ(p1, p2);
  EXPECT_NE(p1, p3);
  EXPECT_LT(p1, p3);
  EXPECT_LT(p1, p4);
}

TEST(rayandbox_test, test_box_calculus)
{
  Box2d p1 = { c1, c2 };
  Box2d p2 = { c3, c0 };

  EXPECT_EQ(p1 + p2, Box2d(c2, c2));
  EXPECT_EQ(p1 - p2, Box2d(c5, c2));
}

TEST(rayandbox_test, test_box_extension)
{
  Box2d p1 = { c2, c4 };

  EXPECT_EQ(p1 * 2, Box2d(c2, c6));
}

TEST(rayandbox_test, test_box_move)
{
  Box2d p1 = { c2, c4 };
  Box2d p2 = { c3, c7 };
  EXPECT_EQ(p1.move(c2), p2);
}

TEST(rayandbox_test, test_box_intersection)
{
  Box2d p1 = { c1, c2 };
  Box2d p2 = { c0, c3 };

  EXPECT_EQ(p1.intersection(p2), 1);
}

// Тесты для луча.
TEST(rayandbox_test, test_ray_construction)
{
  // Тест на создание объекта по умолчанию.
  Ray2d p1;
  EXPECT_EQ(p1.OriginN(), c0);
  EXPECT_EQ(p1.DirectionN(), c0);

  // Тест на создание объекта с параметрами.
  Ray2d p2 = { c1, c2 };
  EXPECT_EQ(p2.OriginN(), c1);
  EXPECT_EQ(p2.DirectionN(), c2);

  // Тест на создание копии объекта.
  Ray2d p3 = p2;
  EXPECT_EQ(p3, p2);
}

TEST(rayandbox_test, test_ray_initializer_list)
{
  Ray2d p1 = { c2, c3, c4 };
  EXPECT_EQ(p1.OriginN(), c2);
  EXPECT_EQ(p1.DirectionN(), c3);

  Ray2d p2 = { c2 };
  EXPECT_EQ(p2.OriginN(), c2);
  EXPECT_EQ(p2.DirectionN(), c0);
}

TEST(rayandbox_test, test_ray_assignment)
{
  Ray2d p1;
  p1 = { c1, c2 };
  EXPECT_EQ(p1, Ray2d(c1, c2));
}

TEST(rayandbox_test, test_ray_move)
{
  Ray2d p1 = { c0, c4 };
  Ray2d p2 = { c2, c7 };

  EXPECT_EQ(p1.move(c2), p2);
}

TEST(rayandbox_test, test_ray_crossing)
{
  Box2d p1 = { c1, c2 };
  Ray2d p2 = { c0, c4 };

  EXPECT_EQ(p2.crossing(p1), 1);
}
