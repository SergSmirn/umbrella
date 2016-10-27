#pragma once
#include "headerlist.hpp"

class Obstacle : public GameObject
{
public:
  Obstacle() = default;
    
  Obstacle(Point2D const & lbp, Point2D const & rtp, unsigned strength)
   : GameObject(lbp, rtp, "Obstacle")
  {
    if (strength > 50) throw std::invalid_argument("Strenght is less than 50!\n");
    m_strength = strength;
  }

  ~Obstacle() override {}


  unsigned const GetStrength()
  {
    return m_strength;
  }

  void SetStrength(unsigned strength)
  {
    try
    {
      if (strength > 50) throw std::invalid_argument("Strenghth is more than 50!\n");
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

std::ostream & operator << (std::ostream & os,
                            Obstacle & obj)
{
  os << obj.GetName() << " [LeftBotPosition: " << obj.LeftBot()
     << "; Strength: " << obj.GetStrength() << "]";
  return os;
}
