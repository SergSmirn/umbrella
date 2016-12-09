#pragma once
#include "headerlist.hpp"
#include "obstacle.hpp"

void IniObsatacle (std::vector< Obstacle> &vObstacle)
{
    Obstacle ob;

    for (int i = 0; i < 64; i++)
    {
      vObstacle.push_back(ob);
      vObstacle[i].SetCoordinateY(i/16);
      vObstacle[i].SetCoordinates({(float)(i/16),(float)((i+1)%16 + 1)}, (float) 40);
      vObstacle[i].SetCoordinateX((i+1)%16 + 1);
      if (rand () % 4 == 1)
        vObstacle[i].SetIni(true);//SetIni(true);
    }
    //for (vector<int>::iterator it = vObstacle.begin() ; it!=vObstacle.end() ; ++it)
}
