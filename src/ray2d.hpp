#pragma once
#include "point2d.hpp"
#include "box2d.hpp"
#include <cmath>
#include <iostream>

class Ray2d
{
public:
  Ray2d() = default;

  Ray2d(Ray2d const & obj):
  Origin(obj.Origin), Direction(obj.Direction)
  {}

  Ray2d(Point2D Orig, Point2D Dir)
  :Origin(Orig), Direction (Dir)
  {

  }
  //Принадлежность точки четверти  в которой лежит луч
  bool region (Point2D Point)
  {

      if ((((Direction.x()-Origin.x())/(Point.x()-Origin.x()))>=0)
       && (((Direction.y()-Origin.y())/(Point.y()-Origin.y()))>=0)) return 1;
      return 0;;
  }
  //Проверка пересечения с прям-ом
  bool 	crossing (Box2d const & obj)
  {
      factorA=Origin.y()-Direction.y(),
      factorB=Direction.x()- Direction.x(),
      factorC=Origin.x()*Direction.y()-Direction.x()*Origin.y();

      return ((obj.LeftBot().y()<=(-factorA*obj.LeftBot().x()-factorC)/factorB && obj.RightTop().y()>=(-factorA*obj.LeftBot().x()-factorC)/factorB
          || obj.LeftBot().y()<=(-factorA*obj.RightTop().x()-factorC)/factorB && obj.RightTop().y()>=(-factorA*obj.RightTop().x()-factorC)/factorB)
          || (obj.LeftBot().x()<=(-factorB*obj.LeftBot().y()-factorC)/factorA && obj.RightTop().x()>=(-factorB*obj.LeftBot().y()-factorC)/factorA
          || obj.LeftBot().x()<=(-factorB*obj.RightTop().y()-factorC)/factorA && obj.RightTop().x()>=(-factorB*obj.RightTop().y()-factorC)/factorA))
          && (region(obj.LeftBot())||region(obj.RightTop()));
  }


  Ray2d(std::initializer_list<Point2D> const & lst)
  {
    Point2D * vals[] = { &Origin, &Direction};
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }

  Point2D & OriginN () { return Origin;}
  Point2D & DirectionN () { return Direction;}

  Point2D const & OriginN () const { return Origin;}
  Point2D const & DirectionN () const { return Direction;}

  float & A () { return factorA;}
  float & B () { return factorB;}
  float & C () { return factorC;}

  bool operator == (Ray2d const & obj) const
  {
    return Origin==obj.OriginN() && Direction==obj.DirectionN();
  }

  Ray2d moveX (float X)
  {
    Point2D distance(X,0);
    Origin+=distance;
    Direction+=distance;
    return *this;
  }

  Ray2d moveY (float Y)
  {
    Point2D distance(0,Y);
    Origin+=distance;
    Direction+=distance;
    return *this;
  }

  Ray2d move (Point2D distance)
  {
    Origin+=distance;
    Direction+=distance;
    return *this;
  }

  bool EqualWithEps(float v1, float v2) const
  {
    return fabs(v1 - v2) < kEps;
  }
private:
  Point2D Origin{0.0f,0.0f}, Direction{0.0f,0.0f};
  float factorA=0.0f,factorB=0.0f,factorC=0.0f;

};

std::ostream & operator << (std::ostream & os, Ray2d const & obj)
{
  os << "Ray2D {" << obj.OriginN() << ", " << obj.DirectionN() << "}";
  return os;
}
