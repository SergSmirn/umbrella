#pragma once
#include "headerlist.hpp"

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

  unsigned GetHealth()
  {
    return m_health;
  }

  unsigned GetRate()
  {
    return m_rate;
  }

  GameEntity ReduceHealth(unsigned damage)
  {
    if (m_health > damage)
    m_health -= damage;
    else m_health = 0;
    return *this;
  }

  void SetBulletManager(TBulletManagerPtr bulletManager)
  {
    m_bulletManager = bulletManager;
  }

  BulletManager & GetBulletManager()
  {
    return *m_bulletManager;
  }

protected:
  unsigned m_health = 0;
  unsigned m_rate = 0;
  TBulletManagerPtr m_bulletManager;
};
