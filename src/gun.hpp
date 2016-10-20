#pragma once
#include "headerlist.hpp"

class Gun: public GameEntity
{
public:
  Gun() = default;


  Gun(Point2D const & lbp, Point2D const & rtp,
      int health, int rate, int speed)
   : GameEntity(lbp, rtp, "Gun", health, rate)
  {
    if (speed < 0) throw std::invalid_argument("Speed is less than 0!\n");
    m_speed = speed;
  }

  ~Gun() override {}

  unsigned GetSpeed()
  {
    return m_speed;
  }

  Gun Clash(Obstacle const & obj)
  {
    if (this->Intersection(obj)) ReduceHealth(5);
    return *this;
  }

private:
  unsigned m_speed = 0;
};
