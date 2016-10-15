#pragma once
#include "gameentity.hpp"

class Gun: public GameEntity
{
public:
  Gun() = default;


  Gun(Point2D const & lbp, Point2D const & rtp,
      unsigned health, unsigned rate, unsigned speed)
   : GameEntity(lbp, rtp, "Gun", rate, health)
  {
    m_speed = speed;
  }

  ~Gun() override {}

private:
  unsigned m_speed = 0;
};
