#pragma once
#include "gameobject.hpp"
#include "bulletmanager.hpp"

class GameEntity : public GameObject
{
public:
  GameEntity() = default;

  GameEntity(Point2D const & lbp, Point2D const & rtp,
             std::string const & name, unsigned health, unsigned rate)
   : GameObject(lbp, rtp, name)
  {
    m_health = health;
    m_rate = rate;
  }

  ~GameEntity() override {}

/*
  GameEntity(std::initializer_list<unsigned> const & lst)
   : Box2D(lst)
  {
    unsigned * vals[] = { &m_health };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }
*/
  unsigned GetHealth()
  {
    return m_health;
  }

  GameEntity ReduceHealth(unsigned damage)
  {
    if (m_health > damage)
    m_health -= damage;
    else m_health = 0;
    return *this;
  }

  void SetBulletManager(BulletManager const & bulletmanager)
  {
    m_bulletManager = bulletmanager;
  }

  BulletManager const & GetBulletManager() const
  {
    return m_bulletManager;
  }

protected:
  unsigned m_health = 0;
  unsigned m_rate = 0;
  BulletManager m_bulletManager;
};
