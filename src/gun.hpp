#pragma once
#include "headerlist.hpp"

class Gun: public GameEntity
{
public:
  Gun() = default;


  Gun(Point2D const & lbp, Point2D const & rtp,
      unsigned health, unsigned rate, unsigned speed)
   : GameEntity(lbp, rtp, "Gun", health, rate)
  {
    m_speed = speed;
  }

  ~Gun() override {}

  unsigned GetSpeed()
  {
    return m_speed;
  }

  Gun Clash(Obstacle const & obj)
  {
    if (Intersection(*this, obj)) ReduceHealth(5);
    return *this;
  }

private:
  unsigned m_speed = 0;
};
