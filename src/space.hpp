#pragma once
#include "obstacle.hpp"
#include "alien.hpp"
#include "gameobject.hpp"
#include <list>

class Space : public GameObject
{
public:
  Space() = default;

  Space(Point2D lbp, Point2D rtp)
   : GameObject(lbp, rtp, "Space") {}

  ~Space() override {}

  void AddAlien(TAlienPtr alien)
  {
    m_alienList.push_back(alien);
  }

  void AddShipBullet(TBulletPtr bullet)
  {
    m_shipBulletList.push_back(bullet);
  }

  void AddObstacle(TObstaclePtr obstacle)
  {
    m_obstacleList.push_back(obstacle);
  }

  std::list<TAlienPtr> const & GetAlienList()
  {
    return m_alienList;
  }

  std::list<TBulletPtr> const & GetShipBulletList()
  {
    return m_shipBulletList;
  }

  std::list<TObstaclePtr> & GetObstaclesList()
  {
    return m_obstacleList;
  }

  TGunPtr & GetShip()
  {
    return m_ship;
  }

  void SetShip(TGunPtr ship)
  {
    m_ship = ship;
  }

private:
  std::list<TAlienPtr> m_alienList;
  std::list<TObstaclePtr> m_obstacleList;
  std::list<TBulletPtr> m_shipBulletList;
  TGunPtr m_ship = nullptr;
};
