#pragma once
#include "headerlist.hpp"

class Bullet: public GameObject
{
public:
  Bullet() = default;
  
  Bullet(Point2D const & lbp, Point2D const & rtp, unsigned damage)
    : GameObject(lbp, rtp, "Bullet")
  {
    m_damage = damage;
  }

  ~Bullet() override {}

  unsigned GetDamage() const
  {
     return m_damage;
  }

  void SetDamage(uint const & damage)
  {
    m_damage = damage;
  }

private:
  unsigned m_damage = 0;
};

using TBulletPtr = std::shared_ptr<Bullet>;
