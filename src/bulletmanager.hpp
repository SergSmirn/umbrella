#pragma once
#include "headerlist.hpp"

class BulletManager
{
public:
  BulletManager() = default;

  ~BulletManager() {}

  void Shot(TBulletPtr bullet)
  {
    try
    {
      if (m_bulletList[bullet] == 0) throw std::invalid_argument("No bullets!\n");
      m_bulletList[bullet]--;
    }
    catch (std::exception const & ex)
    {
      std::cerr << ex.what();
    }
  }

  std::map<TBulletPtr, unsigned> const & GetBullets()
  {
    return m_bulletList;
  }

  unsigned GetAmmo(TBulletPtr bullet)
  {
    return m_bulletList[bullet];
  }

  void SetAmmo(TBulletPtr bullet, int count)
  {
    try
    {
      if (m_bulletList[bullet]+=count < 0) throw std::invalid_argument("Speed is less than 0!\n");
      m_bulletList[bullet]+=count;
    }
    catch (std::exception const & ex)
    {
      std::cerr << ex.what();
    }
  }

private:
  std::map<TBulletPtr, unsigned> m_bulletList;
};

using TBulletManagerPtr = std::shared_ptr<BulletManager>;
