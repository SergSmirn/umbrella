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
      if (m_bulletList[bullet] != 0)
      m_bulletList[bullet]--;
    }
    catch (std::exception const & ex)
    {
      std::cerr << ex.what();
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
    if (count <= 200)
      m_bulletList[bullet] = count;
  }

  void AddAmmo(TBulletPtr bullet, unsigned count)
  {
    if (m_bulletList[bullet] + count > 200)
      m_bulletList[bullet] = 200;
    else m_bulletList[bullet]+=count;
  }

private:
  std::map<TBulletPtr, unsigned> m_bulletList;
};

using TBulletManagerPtr = std::shared_ptr<BulletManager>;

std::ostream & operator << (std::ostream & os,
                           BulletManager const & obj)
{
  os << "BulletManager [";
  auto bullets = obj.GetBullets();
  for (auto it = bullets.begin(); it != bullets.end(); ++it)
    {
      os << *(it->first);
      os << " - Count: " << it->second;
    }
  os << "]";
  return os;
}
