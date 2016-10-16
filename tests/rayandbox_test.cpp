#include "gtest/gtest.h"
#include "headerlist.hpp"

Point2D c0{ 0, 0 }, c1{ -1, -1 }, c2{ 1, 1 }, c3{ 2, 2 }, c4{ 5, 5 }, c5{ -3, -3 },
        c6{ 10, 10 }, c7{ 6, 6 }, c8{ 1, 0 }, c9{ 5, 0 }, c10{ 4, 4 };

// Тесты для прямоугольника.
TEST(rayandbox_test, test_box_construction)
{
  // Тест на создание объекта по умолчанию.
  Box2D p1;
  EXPECT_EQ(p1.LeftBot(), c0);
  EXPECT_EQ(p1.RightTop(), c0);

  // Тест на создание объекта с параметрами.
  Box2D p2 = { c1, c2 };
  EXPECT_EQ(p2.LeftBot(), c1);
  EXPECT_EQ(p2.RightTop(), c2);

  //  Тест на создание объекта с неверными параметрами.
  Box2D p3( c2, c1 );
  EXPECT_EQ(p3.LeftBot(), c1);
  EXPECT_EQ(p3.RightTop(), c2);

  // Тест на создание копии объекта.
  Box2D p4 = p2;
  EXPECT_EQ(p4, p2);
}

TEST(rayandbox_test, test_box_initializer_list)
{
  Box2D p1 = { c2, c3, c4 };
  EXPECT_EQ(p1.LeftBot(), c2);
  EXPECT_EQ(p1.RightTop(), c3);

  Box2D p2 = { c2 };
  EXPECT_EQ(p2.LeftBot(), c0);
  EXPECT_EQ(p2.RightTop(), c2);
}

TEST(rayandbox_test, test_box_assignment)
{
  Box2D p1;
  p1 = { c1, c2 };
  EXPECT_EQ(p1, Box2D(c1, c2));
}

TEST(rayandbox_test, test_box_equality)
{
  Box2D p1 = { c1, c2 };
  Box2D p2 = { c1, c2 };
  Box2D p3 = { c3, c4 };
  Box2D p4 = { c2, c4 };

  EXPECT_EQ(p1, p2);
  EXPECT_NE(p1, p3);
  EXPECT_LT(p1, p3);
  EXPECT_LT(p1, p4);
}

TEST(rayandbox_test, test_box_calculus)
{
  Box2D p1 = { c1, c2 };
  Box2D p2 = { c0, c10 };

  EXPECT_EQ(p1 + p2, Box2D(c1, c4));
  EXPECT_EQ(p1 - p2, Box2D(c1, c5));
}

TEST(rayandbox_test, test_box_extension)
{
  Box2D p1 = { c2, c4 };

  EXPECT_EQ(p1 * 2, Box2D(c2, c6));
}

TEST(rayandbox_test, test_box_move)
{
  Box2D p1 = { c2, c4 };
  Box2D p2 = { c3, c7 };
  EXPECT_EQ(p1.Move(c2), p2);
}

TEST(rayandbox_test, test_box_intersection)
{
  Box2D p1 = { c1, c2 };
  Box2D p2 = { c0, c3 };

  EXPECT_EQ(p1.Intersection(p2), 1);
}

TEST(rayandbox_test, test_box_output)
{
  std::stringstream s;
  s << Box2D(c0, c2);
  EXPECT_EQ(s.str(), "Box2D {(0, 0), (1, 1)}");
}

//Тесты на перемещение
TEST(rayandbox_test, test_box_move_hw2)
{
  Box2D p1(c5, c6);
  Box2D p2(std::move(p1));
  EXPECT_EQ(p2, Box2D(c5, c6));
}

TEST(rayandbox_test, test_box_move_operator)
{
  Box2D p1(c5, c6);
  Box2D p2 = std::move(p1);
  EXPECT_EQ(p2, Box2D(c5, c6));
}

// Тесты для луча.
TEST(rayandbox_test, test_ray_construction)
{
  // Тест на создание объекта по умолчанию.
  Ray2D p1;
  EXPECT_EQ(p1.OriginN(), c0);
  EXPECT_EQ(p1.DirectionN(), c0);

  // Тест на создание объекта с параметрами.
  Ray2D p2 = { c0, c9 };
  EXPECT_EQ(p2.OriginN(), c0);
  EXPECT_EQ(p2.DirectionN(), c8);

  // Тест на создание копии объекта.
  Ray2D p3 = p2;
  EXPECT_EQ(p3, p2);
}

TEST(rayandbox_test, test_ray_initializer_list)
{
  Ray2D p1 = { c0, c9, c4 };
  EXPECT_EQ(p1.OriginN(), c0);
  EXPECT_EQ(p1.DirectionN(), c8);

  Ray2D p2 = { c8 };
  EXPECT_EQ(p2.OriginN(), c8);
  EXPECT_EQ(p2.DirectionN(), c0);
}

TEST(rayandbox_test, test_ray_assignment)
{
  Ray2D p1 = { c3, c5 };
  EXPECT_EQ(p1, Ray2D(c3, c5));
}

TEST(rayandbox_test, test_ray_move)
{
  Ray2D p1 = { c0, c4 };
  Ray2D p2 = { c2, c4 };

  EXPECT_EQ(p1.Move(c2), p2);
}

TEST(rayandbox_test, test_ray_crossing)
{
  Box2D p1 = { c1, c2 };
  Ray2D p2 = { c0, c4 };

  EXPECT_EQ(p2.Crossing(p1), 1);
}

TEST(rayandbox_test, test_ray_output)
{
  std::stringstream s;
  s << Ray2D(c0, c8);
  EXPECT_EQ(s.str(), "Ray2D {(0, 0), (1, 0)}");
}

//Тест на перемещение
TEST(rayandbox_test, test_ray_move_hw2)
{
  Ray2D p1(c5, c6);
  Ray2D p2(std::move(p1));
  EXPECT_EQ(p2, Ray2D(c5, c6));
}

TEST(rayandbox_test, test_ray_move_operator)
{
  Ray2D p1(c5, c6);
  Ray2D p2 = std::move(p1);
  EXPECT_EQ(p2, Ray2D(c5, c6));
}
