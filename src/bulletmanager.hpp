#pragma once
#include "headerlist.hpp"

class BulletManager : public Bullet
{
public:
  BulletManager() = default;

  ~BulletManager() override {}

  void Shot(TBulletPtr bullet)
  {
    if (m_bulletList[bullet]!=0)
    {
      m_bulletList[bullet]-=1;
    }
  }

  std::map<TBulletPtr, unsigned> GetBullets()
  {
    return m_bulletList;
  }

  void SetAmmo(TBulletPtr bullet, unsigned count)
  {
    m_bulletList[bullet]+=count;
  }

private:
  std::map<TBulletPtr, unsigned> m_bulletList;
};
