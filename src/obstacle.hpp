#pragma once
#include "headerlist.hpp"

class Obstacle : public GameObject
{
public:
  Obstacle() = default;
    
  Obstacle(Point2D const & lbp, Point2D const & rtp, int strength)
   : GameObject(lbp, rtp, "Obstacle")
  {
    m_strength = strength;
  }

  ~Obstacle() override {}


  unsigned const GetStrength()
  {
    return m_strength;
  }

  void SetStrength(unsigned strength)
  {
    m_strength = strength;
  }

  Obstacle ReduceStrength(unsigned damage)
  {
    if (m_strength > damage)
    m_strength -= damage;
    else m_strength = 0;
    return *this;
  }

private:
  int m_strength = 0;
};

std::ostream & operator << (std::ostream & os, Obstacle & obj)
{
  os << "Obstacle {" << obj.LeftBot() << ", " << obj.RightTop() << ", " << obj.GetStrength() << "}";
  return os;
}
