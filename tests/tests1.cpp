#include "gtest/gtest.h"
#include "headerlist.hpp"


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
}

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

TEST(tests, test_bulletmanager)
{
  Bullet b1 ({1,1}, {2,2}, 15);
  BulletManager bm1;
  std::shared_ptr<Bullet> b1_ptr(new Bullet(b1));
  bm1.SetAmmo(b1_ptr, 5);
  EXPECT_EQ(bm1.GetAmmo(b1_ptr), 5);
  bm1.Shot(b1_ptr);
  EXPECT_EQ(bm1.GetAmmo(b1_ptr), 4);
}

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
}

TEST(test, test_gameobject)
{
  GameObject go1 ({1,1}, {2,2}, "Go1");
  EXPECT_EQ(go1.GetName(), "Go1");
  EXPECT_EQ(go1.LeftBot(), Point2D(1,1));
  EXPECT_EQ(go1.RightTop(), Point2D(2,2));
}
