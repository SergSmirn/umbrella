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
    if (speed > 20) throw std::invalid_argument("Speed is more than 20!\n");
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

std::ostream & operator << (std::ostream & os,
                            Gun & obj)
{
  os << obj.GetName() <<" [LeftBotPosition: " << obj.LeftBot()
     << "; Health: " << obj.GetHealth()
     << "; Rate: " << obj.GetRate()
     << "; Speed: " << obj.GetSpeed() << "]";
  return os;
}
