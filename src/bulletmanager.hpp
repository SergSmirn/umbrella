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
      throw;
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

  void SetAmmo(TBulletPtr bullet, unsigned count)
  {
    m_bulletList[bullet]+=count;
  }

private:
  std::map<TBulletPtr, unsigned> m_bulletList;
};

using TBulletManagerPtr = std::shared_ptr<BulletManager>;
