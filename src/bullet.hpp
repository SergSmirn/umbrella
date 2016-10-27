#pragma once
#include "headerlist.hpp"

class Bullet: public GameObject
{
public:
  Bullet() = default;
  
  Bullet(Point2D const & lbp, Point2D const & rtp, unsigned damage)
    : GameObject(lbp, rtp, "Bullet")
  {
    m_damage = damage;
  }

  ~Bullet() override {}

  unsigned GetDamage() const
  {
     return m_damage;
  }

  void SetDamage(unsigned damage)
  {
    try
    {
      if (damage > 50) throw std::invalid_argument("Damage is more than 50!\n");
      m_damage = damage;
    }
    catch (std::exception const & ex)
    {
      std::cerr << ex.what();
    }
  }

private:
  unsigned m_damage = 0;
};

using TBulletPtr = std::shared_ptr<Bullet>;

std::ostream & operator << (std::ostream & os,
                            Bullet const & obj)
{
  os << " " << obj.GetName() << " [LeftBotPosition: " << obj.LeftBot()
     << "; Damage: " << obj.GetDamage() << "]";
  return os;
}
