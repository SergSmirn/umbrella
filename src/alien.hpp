#pragma once
#include "headerlist.hpp"

class Alien : public GameEntity
{
public:
  Alien() = default;

  Alien(Point2D const & lbp, Point2D const & rtp,
       unsigned rate, unsigned health, unsigned speed, unsigned type)
    : GameEntity(lbp, rtp, "Alien", rate, health)
  {
    m_speed = speed;
    m_type = type;
  }

  ~Alien() override {}

  unsigned  GetSpeed()
  {
    return m_speed;
  }

  void SetSpeed(unsigned speed)
  {
    m_speed = speed;
  }

  unsigned  GetType()
  {
    return m_type;
  }

  void SetType(unsigned type)
  {
    m_speed = type;
  }

private:
  unsigned m_speed = 0;
  unsigned m_type = 0;
};
