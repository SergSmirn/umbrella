#include "gtest/gtest.h"
#include "headerlist.hpp"

Point2D c0{ 0, 0 }, c1{ -1, -1 }, c2{ 1, 1 }, c3{ 2, 2};

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
  EXPECT_THROW(Obstacle p1(c1, c2, -10);, std::invalid_argument);
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
  Gun p1(c1, c2, 10, 4, 4);
  Obstacle p2(c2, c3, 5);
  p1.Clash(p2);
  EXPECT_EQ(p1.GetHealth(), 5);
}

//Тесты для пришельца.
TEST(tests, test_alien)
{
  Alien a1 ({1,1}, {2,2}, 30, 5, 3, 3);
  EXPECT_EQ(a1.LeftBot(), Point2D(1,1));
  EXPECT_EQ(a1.RightTop(), Point2D(2,2));
  EXPECT_EQ(a1.GetHealth(), 30);
  EXPECT_EQ(a1.GetSpeed(), 3);
  EXPECT_EQ(a1.GetName(), "Alien");
  EXPECT_EQ(a1.GetType(), 3);
  EXPECT_EQ(a1.GetRate(), 5);
  EXPECT_THROW(Alien a1 ({1,1}, {2,2}, 30, 5, 40, 3), std::invalid_argument);
}
//Тесты для пули.
TEST(tests, test_bullet)
{
  Bullet b1 ({1,1}, {2,2}, 15);
  EXPECT_EQ(b1.LeftBot(), Point2D(1,1));
  EXPECT_EQ(b1.RightTop(), Point2D(2,2));
  EXPECT_EQ(b1.GetName(), "Bullet");
  EXPECT_EQ(b1.GetDamage(), 15);
  b1.SetDamage(20);
  EXPECT_EQ(b1.GetDamage(), 20);
}
//Тесты для менеджера пуль.
TEST(tests, test_bulletmanager)
{
  Bullet b1 ({1,1}, {2,2}, 15);
  BulletManager bm1;
  std::shared_ptr<Bullet> b1_ptr(new Bullet(b1));
  bm1.SetAmmo(b1_ptr, 1);
  EXPECT_EQ(bm1.GetAmmo(b1_ptr), 1);
  bm1.Shot(b1_ptr);
  EXPECT_EQ(bm1.GetAmmo(b1_ptr), 0);
}

//Тесты для игровой сущности.
TEST(test, test_gameentity)
{
  GameEntity ge1 ({1,1}, {2,2}, "Ge1", 30, 5);
  EXPECT_EQ(ge1.LeftBot(), Point2D(1,1));
  EXPECT_EQ(ge1.RightTop(), Point2D(2,2));
  EXPECT_EQ(ge1.GetHealth(), 30);
  EXPECT_EQ(ge1.GetName(), "Ge1");
  EXPECT_EQ(ge1.GetRate(), 5);
  ge1.ReduceHealth(10);
  EXPECT_EQ(ge1.GetHealth(), 20);
  EXPECT_THROW(GameEntity ge ({1,1}, {2,2}, "Ge1", 200, 2), std::invalid_argument);
}

//Тесты для игрового объекта.
TEST(test, test_gameobject)
{
  GameObject go1 ({1,1}, {2,2}, "Go1");
  EXPECT_EQ(go1.GetName(), "Go1");
  EXPECT_EQ(go1.LeftBot(), Point2D(1,1));
  EXPECT_EQ(go1.RightTop(), Point2D(2,2));
}
