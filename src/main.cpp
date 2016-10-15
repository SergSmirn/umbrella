#include <iostream>
#include "point2d.hpp"
#include "box2d.hpp"
#include "ray2d.hpp"
#include "obstacle.hpp"
#include "space.hpp"
#include "gameobject.hpp"

using namespace std;

int main()
{
  Point2D c1{-1,-1}, c2{1,1}, c3{1,1}, c4{4,2}, origin{0,1}, dir{1,1};
  Ray2D r1 {origin};
  bool eq, eq2;
  cout << r1 << endl;
  return 0;
}
