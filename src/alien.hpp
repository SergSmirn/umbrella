#pragma once
#include "headerlist.hpp"

class Alien : public GameEntity
{
public:
  Alien() = default;

  Alien(Point2D const & lbp, Point2D const & rtp,
       int health, int rate, int speed, int type)
    : GameEntity(lbp, rtp, "Alien", health, rate)
  {
    if (speed < 0) throw std::invalid_argument("Speed is less than 0!\n");
    if (type < 0) throw std::invalid_argument("Type is less than 0!\n");
    m_speed = speed;
    m_type = type;
  }

  ~Alien() override {}

  unsigned GetSpeed()
  {
    return m_speed;
  }

  void SetSpeed(int speed)
  {
    try
    {
      if (speed < 0) throw std::invalid_argument("Speed is less than 0!\n");
      m_speed = speed;
    }
    catch (std::exception const & ex)
    {
      std::cerr << ex.what();
    }
  }

  unsigned GetType()
  {
    return m_type;
  }

  void SetType(int type)
  {
    try
    {
      if (type < 0) throw std::invalid_argument("Type is less than 0!\n");
      m_type = type;
    }
    catch (std::exception const & ex)
    {
      std::cerr << ex.what();
    }
  }

private:
  unsigned m_speed = 0;
  unsigned m_type = 0;
};
