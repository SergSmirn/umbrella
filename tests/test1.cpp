#include "gtest/gtest.h"
#include "headerlist.hpp"

Point2D c0{ 0, 0 }, c1{ -1, -1 }, c2{ 1, 1 }, c3{ 2, 2 }, c4{ 5, 5 }, c5{ -3, -3 },
        c6{ 10, 10 }, c7{ 6, 6 }, c8{ 1, 0 }, c9{ 5, 0 }, c10{ 4, 4 };

// Тесты для космоса.
TEST(prog_test, test_space_construction)
{
  // Тест на создание объекта по умолчанию.
  Space p1;
  EXPECT_EQ(p1.LeftBot(), c0);
  EXPECT_EQ(p1.RightTop(), c0);

  // Тест на создание объекта с параметрами.
  Space p2(c1, c2);
  EXPECT_EQ(p2.LeftBot(), c1);
  EXPECT_EQ(p2.RightTop(), c2);
  EXPECT_EQ(p2.GetName(), "Space");
}

TEST(test, test_space_add_gameobject)
{
  // Тест на создание объекта в космосе.
  Space p1(c1, c2);
  GameObject p2;
  p1.AddGameObject(TGameObjectConstPtr(new GameObject(p2)));
  EXPECT_EQ(*(p1.GetGameObject().back()), p2);
}

// Тесты для препятствия.
TEST(prog_test, test_obstacle_construction)
{
  // Тест на создание объекта по умолчанию.
  Obstacle p1;
  EXPECT_EQ(p1.LeftBot(), c0);
  EXPECT_EQ(p1.RightTop(), c0);

  // Тест на создание объекта с параметрами.
  Obstacle p2(c1, c2, 5);
  EXPECT_EQ(p2.LeftBot(), c1);
  EXPECT_EQ(p2.RightTop(), c2);
  EXPECT_EQ(p2.GetName(), "Obstacle");
  EXPECT_EQ(p2.GetStrength(), 5);
}

TEST(prog_test, test_obstacle_stregth)
{
  Obstacle p(c1, c2, 10);
  EXPECT_EQ(p.GetStrength(), 10);
  p.ReduceStrength(5);
  EXPECT_EQ(p.GetStrength(), 5);
  p.SetStrength(7);
  EXPECT_EQ(p.GetStrength(), 7);
}

// Тесты для пушки.
TEST(prog_test, test_gun_construction)
{
  // Тест на создание объекта по умолчанию.
  Gun p1;
  EXPECT_EQ(p1.LeftBot(), c0);
  EXPECT_EQ(p1.RightTop(), c0);

  // Тест на создание объекта с параметрами.
  Gun p2(c1, c2, 5, 5, 5);
  EXPECT_EQ(p2.LeftBot(), c1);
  EXPECT_EQ(p2.RightTop(), c2);
  EXPECT_EQ(p2.GetName(), "Gun");
  EXPECT_EQ(p2.GetHealth(), 5);
  EXPECT_EQ(p2.GetRate(), 5);
  EXPECT_EQ(p2.GetSpeed(), 5);
}

TEST(prog_test, test_clash)
{
  Gun p1(c1, c2, 10, 10, 10);
  Obstacle p2(c2, c3, 5);
  p1.Clash(p2);
  EXPECT_EQ(p1.GetHealth(), 5);
}
