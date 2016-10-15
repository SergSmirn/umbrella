#pragma once
#include "gameentity.hpp"

class Obstacle : public GameObject
{
public:
  Obstacle() = default;
    
  Obstacle(Point2D const & lbp, Point2D const & rtp, unsigned strength)
   : GameObject(lbp, rtp, "Obstacle")
  {
    m_strength = strength;
  }

  ~Obstacle() override {}

/*
  Obstacle(std::initializer_list<unsigned> const & lst)
   : Box2D(lst)
  {
    unsigned * vals[] = { &m_strength };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }
*/
  unsigned const GetStrength()
  {
    return m_strength;
  }

  void SetHealth(unsigned strength)
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
  unsigned m_strength = 0;
};

std::ostream & operator << (std::ostream & os, Obstacle & obj)
{
  os << "Obstacle {" << obj.LeftBot() << ", " << obj.RightTop() << ", " << obj.GetStrength() << "}";
  return os;
}
