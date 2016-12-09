#pragma once
#include "headerlist.hpp"
#include "alien.hpp"

void IniAlien (std::vector<Alien> &vAlien)
{
    Alien alien;

    for (int i = 0; i < 55; i++)
    {
      vAlien.push_back(alien);
      vAlien[i].SetCoordinateY(i/11);
      vAlien[i].SetCoordinateX((i+1)%11 + 1);
      if (i < 22)
        vAlien[i].SetType(1);
      else if (i >= 44)
        vAlien[i].SetType(2);
      else
        vAlien[i].SetType(3);
    }
    //for (vector<int>::iterator it = vObstacle.begin() ; it!=vObstacle.end() ; ++it)
}
