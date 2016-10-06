#pragma once
#include "point2d.hpp"
#include "box2d.hpp"
#include <cmath>
#include <iostream>

class Ray2D
{
public:
  Ray2D() = default;

  Ray2D(Ray2D const & obj)
    : m_origin(obj.m_origin), m_direction(obj.m_direction)
  {}

  Ray2D(std::initializer_list<Point2D> const & lst)
  {
    Point2D * vals[] = { &m_origin, &m_direction };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
    {
      if (i == 0) *vals[i] = *it;
      if (i == 1)
      {
        *vals[i] = *it;
        *vals[i] = Rationing(*vals[0], *vals [1]);
      }
    }
  }

  Ray2D(Point2D const & orig, Point2D const & dir)
  {
      m_origin = orig;
      m_direction = Rationing(orig, dir);
  }



  //Принадлежность точки четверти  в которой лежит луч
  bool Region (Point2D const & point)
  {
      return (((m_direction.x()-m_origin.x())/(point.x()-m_origin.x()))>=0)
       && (((m_direction.y()-m_origin.y())/(point.y()-m_origin.y()))>=0);
  }

  //Проверка пересечения с прям-ом
  bool Crossing (Box2D const & obj)
  {
    float factorA = m_origin.y()-m_direction.y();
    float factorB = m_direction.x()- m_direction.x();
    float factorC = m_origin.x()*m_direction.y()-m_direction.x()*m_origin.y();
    if (Region(obj.LeftBot()) || Region(obj.RightTop()))
    {
      if (obj.LeftBot().y() <= (-factorA * obj.LeftBot().x() - factorC) / factorB && obj.RightTop().y() >= (-factorA * obj.LeftBot().x() - factorC) / factorB) return true;
      if (obj.LeftBot().y() <= (-factorA * obj.RightTop().x() - factorC) / factorB && obj.RightTop().y() >= (-factorA * obj.RightTop().x() - factorC) / factorB) return true;
      if (obj.LeftBot().x() <= (-factorB * obj.LeftBot().y() - factorC) / factorA && obj.RightTop().x() >= (-factorB * obj.LeftBot().y()-factorC) / factorA) return true;
      if (obj.LeftBot().x() <= (-factorB * obj.RightTop().y()-factorC) / factorA && obj.RightTop().x() >= (-factorB * obj.RightTop().y()-factorC) / factorA) return true;
    }
      return false;
  }

  Point2D const & OriginN () const { return m_origin;}
  Point2D const & DirectionN () const { return m_direction;}

  bool operator == (Ray2D const & obj) const
  {
    return m_origin==obj.OriginN() && m_direction==obj.DirectionN();
  }

  Ray2D MoveX (float x)
  {
    Point2D distance(x,0);
    m_origin+=distance;
    m_direction+=distance;
    return *this;
  }

  Ray2D MoveY (float y)
  {
    Point2D distance(0,y);
    m_origin+=distance;
    m_direction+=distance;
    return *this;
  }

  Ray2D Move (Point2D distance)
  {
    m_origin+=distance;
    m_direction+=distance;
    return *this;
  }

private:

  Point2D Rationing ( Point2D const & orig, Point2D const & dir)
  {
    return orig + (dir - orig) / hypot( (orig.x() - dir.x()), (orig.x() - dir.y()));
  }

  bool EqualWithEps(float v1, float v2) const
  {
    return fabs(v1 - v2) < kEps;
  }

  Point2D m_origin {0.0f,0.0f}, m_direction {0.0f,0.0f};

};

std::ostream & operator << (std::ostream & os, Ray2D const & obj)
{
  os << "Ray2D {" << obj.OriginN() << ", " << obj.DirectionN() << "}";
  return os;
}
