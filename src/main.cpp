#include <iostream>
#include "point2d.hpp"
#include "box2d.hpp"
#include "ray2d.hpp"

using namespace std;

int main()
{
  Point2D c1{-1,-1}, c2{1,1}, c3{1,1}, c4{4,2}, origin{0,0}, dir{2,2};
  Box2d b1(c1,c2), b2(c3,c4);
  Ray2d r1(origin,dir);
  bool eq, eq2;
  eq=b1.intersection(b2);
  eq2=r1.crossing(b1);
  cout<<eq2<<endl;
  return 0;
}

