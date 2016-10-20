#pragma once
#include "headerlist.hpp"

class Obstacle : public GameObject
{
public:
  Obstacle() = default;
    
  Obstacle(Point2D const & lbp, Point2D const & rtp, int strength)
   : GameObject(lbp, rtp, "Obstacle")
  {
    if (strength < 0) throw std::invalid_argument("Strenght is less than 0!\n");
    m_strength = strength;
  }

  ~Obstacle() override {}


  unsigned const GetStrength()
  {
    return m_strength;
  }

  void SetStrength(int strength)
  {
    try
    {
      if (strength < 0) throw std::invalid_argument("Strenghth is less than 0!\n");
      m_strength = strength;
    }
    catch (std::exception const & ex)
    {
      std::cerr << ex.what();
    }
  }

  Obstacle ReduceStrength(unsigned damage)
  {
    if (m_strength > damage)
    m_strength -= damage;
    else m_strength = 0;
    return *this;
  }

private:
  unsigned m_strength = 0;
};

std::ostream & operator << (std::ostream & os, Obstacle & obj)
{
  os << "Obstacle {" << obj.LeftBot() << ", " << obj.RightTop() << ", " << obj.GetStrength() << "}";
  return os;
}
