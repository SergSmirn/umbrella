#include "gtest/gtest.h"
#include "observer.hpp"

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
