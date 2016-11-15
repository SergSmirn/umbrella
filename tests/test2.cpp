#include "gtest/gtest.h"
#include "headerlist.hpp"

#include <sstream>
#include <iostream>

std::stringstream cout;

class BulletObserver : public Observer
{
  std::string m_state;
public:
  BulletObserver(std::string state) : m_state(state) {}
  void UpdateHandler(TOnUpdateHandler const & message) override
  {
    cout << "BulletObserver " << m_state << "; ";
    message();
  }

  std::size_t Hash() const override
  {
    return std::hash<std::string>()(m_state);
  }
  bool operator==(Observer const & a) override
  {
    return (Hash() == a.Hash());
  }
};


TEST(Observer_test, bulletobserver)
{
  BulletObserver l1("1");
  BulletObserver l2("2");
  BulletObserver l3("1");

  EXPECT_EQ(l1 == l2, false);
  EXPECT_EQ(l1 == l3, true);
}

TEST(Observer_test, subject)
{
  auto l1 = std::make_shared<BulletObserver>("1");
  auto l2 = std::make_shared<BulletObserver>("2");
  Subject sub;
  sub.RegObserver(l1);
  sub.RegObserver(l1);
  sub.RegObserver(l2);
  sub.SendMessage([]() {cout << "Hello! ";});
  sub.UnregObserver(l1);
  sub.UnregObserver(l2);
  sub.UnregObserver(l2);

  EXPECT_EQ(cout.str(), "BulletObserver 1; Hello! BulletObserver 2; Hello! ");
}

TEST(factory_test, construction)
{
  Factory factory;
  auto bullet = factory.Create<Bullet>(Point2D(1.0f, 1.0f), Point2D(1.1f, 1.1f), 15);
  EXPECT_EQ(bullet->GetName(),"Bullet");
  EXPECT_EQ(bullet->GetDamage(),15);
  EXPECT_EQ(bullet->LeftBot(),Point2D(1.0f, 1.0f));
  EXPECT_EQ(bullet->RightTop(),Point2D(1.1f, 1.1f));

  auto bulletManager = factory.Create<BulletManager>();
  EXPECT_EQ(bulletManager->GetBullets().empty(),true);

  auto alien1 = factory.Create<Alien>(Point2D(1.0f, 1.0f), Point2D(2.0f, 2.0f), 90, 5, 15, 2);
  EXPECT_EQ(alien1->GetName(),"Alien");
  EXPECT_EQ(alien1->LeftBot(),Point2D(1.0f, 1.0f));
  EXPECT_EQ(alien1->RightTop(),Point2D(2.0f, 2.0f));
  EXPECT_EQ(alien1->GetHealth(),90);
  EXPECT_EQ(alien1->GetRate(),5);
  EXPECT_EQ(alien1->GetSpeed(),15);
  EXPECT_EQ(alien1->GetType(),2);

  auto gun1 = factory.Create<Gun>(Point2D(1.0f, 1.0f), Point2D(3.0f, 3.0f), 100, 5, 10);
  EXPECT_EQ(gun1->GetName(),"Gun");
  EXPECT_EQ(gun1->LeftBot(),Point2D(1.0f, 1.0f));
  EXPECT_EQ(gun1->RightTop(),Point2D(3.0f, 3.0f));
  EXPECT_EQ(gun1->GetHealth(),100);
  EXPECT_EQ(gun1->GetRate(),5);
  EXPECT_EQ(gun1->GetSpeed(),10);

  auto obstacle1 = factory.Create<Obstacle>(Point2D(1.0f, 1.0f), Point2D(3.0f, 3.0f), 45);
  EXPECT_EQ(obstacle1->GetName(),"Obstacle");
  EXPECT_EQ(obstacle1->LeftBot(),Point2D(1.0f, 1.0f));
  EXPECT_EQ(obstacle1->RightTop(),Point2D(3.0f, 3.0f));
  EXPECT_EQ(obstacle1->GetStrength(),45);
}
