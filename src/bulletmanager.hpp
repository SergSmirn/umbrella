#pragma once
#include <list>
#include "bullet.hpp"

class BulletManager : public Bullet
{
public:
  BulletManager() = default;

  ~BulletManager() override {}

  void Shot()
  {
    if (not m_bulletList.empty())
    {
      m_bulletList.pop_front();
    }
  }

  std::list<TBulletPtr> GetBullets()
  {
    return m_bulletList;
  }

  void SetAmmo(unsigned count)
  {
    if (count > 0)
    {
      m_bulletList = std::list<TBulletPtr>(count, TBulletPtr(new Bullet()));
    }
  }

private:
  std::list<TBulletPtr> m_bulletList;
};
