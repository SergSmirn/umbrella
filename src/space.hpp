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

  /*void AddAlien(TAlienPtr alien)
  {
    m_alienList.push_back(alien);
  }

  std::list<TAlienPtr> const & GetAlienList()
  {
    return m_alienList;
  }


  std::list<TObstaclePtr> & GetObstaclesList()
  {
    return m_obstacleList;
  }

  void AddObstacle(TObstaclePtr obstacle)
  {
    m_obstacleList.push_back(obstacle);
  }

  */

  void AddShipBullet(TBulletPtr bullet)
  {
    m_shipBulletList.push_back(bullet);
  }

  std::list<TBulletPtr> const & GetShipBulletList()
  {
    return m_shipBulletList;
  }





  TGunPtr & GetShip()
  {
    return m_ship;
  }

  void SetShip(TGunPtr ship)
  {
    m_ship = ship;
  }

  std::vector<Obstacle> & GetObstacle()
  {
    return m_obstacle;
  }

  Obstacle & GetObstacle(int i)
  {
    return m_obstacle[i];
  }

  void SetObstacle(Obstacle obstacle, int i)
  {
    m_obstacle[i] = obstacle;
  }

  std::vector<Alien> & GetAlien()
  {
    return m_alien;
  }

  Alien & GetAlien(int i)
  {
    return m_alien[i];
  }

  void SetAlien(Alien alien, int i)
  {
    m_alien[i] = alien;
  }



private:
  std::vector<Obstacle> m_obstacle;
  std::vector<Alien> m_alien;
  std::list<TBulletPtr> m_shipBulletList;
  TGunPtr m_ship = nullptr;
};
