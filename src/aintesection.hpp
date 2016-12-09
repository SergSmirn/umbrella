#pragma once
#include "headerlist.hpp"

Point2D aintesection(std::list<Bullet> &lBullets, std::vector< Obstacle> &vObstacle, std::vector<Alien> &vAlien, Point2D boxAlien)
{
  int aObstacle;
  for (auto bullet : lBullets)
  {
    if (bullet.GetBox().RightTop().GetY() >= 200 & bullet.GetBox().RightTop().GetY() <= 400)
      aObstacle = ((-200 + (int)bullet.GetBox().RightTop().GetY()) / 50 - 1) * 16 + (int)bullet.GetBox().RightTop().GetX() / 50;
    if (bullet.GetBox().Intersection(vObstacle[aObstacle].GetBox()))
      return {bullet.GetBox().RightTop().GetX(), bullet.GetBox().RightTop().GetY()};
  }
  return {0,0};
}
