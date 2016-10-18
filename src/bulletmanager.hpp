#pragma once
#include "headerlist.hpp"

class BulletManager
{
public:
  BulletManager() = default;

  ~BulletManager() {}

  void Shot(TBulletPtr bullet)
  {
    if (m_bulletList[bullet]!=0)
    {
      m_bulletList[bullet]--;
    }
  }

  std::map<TBulletPtr, unsigned> const & GetBullets() const
  {
    return m_bulletList;
  }

  unsigned GetAmmo(TBulletPtr bullet)
  {
    return m_bulletList[bullet];
  }

  void SetAmmo(TBulletPtr bullet, unsigned count)
  {
    m_bulletList[bullet]+=count;
  }

private:
  std::map<TBulletPtr, unsigned> m_bulletList;
};
