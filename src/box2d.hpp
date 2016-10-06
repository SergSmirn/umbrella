#pragma once
#include "point2d.hpp"
class Box2D
{
public:
  Box2D() = default;

  Box2D(Box2D const & obj)
    :m_plb(obj.m_plb), m_prt(obj.m_prt)
  {}

  Box2D(Point2D leftp, Point2D rightp)
  {
    if (leftp.x() > rightp.x())
    {
      float swap = rightp.x();
      rightp.x() = leftp.x();
      leftp.x() = swap;
    }
    if (leftp.y() > rightp.y())
    {
      float swap = rightp.y();
      rightp.y() = leftp.y();
      leftp.y() = swap;
    }
    m_plb = leftp;
    m_prt = rightp;
  }

  Box2D(std::initializer_list<Point2D> const & lst)
  {
    Point2D * vals[] = { &m_plb, &m_prt };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
    {
      if (i % 2 == 0) *vals[i] = *it;
      if (i % 2 == 1)
      {
        *vals[i] = *it;
        if (vals[i-1]->x() > vals[i]->x())
        {
          float swap = vals[i-1]->x();
          vals[i-1]->x() = it->x();
          vals[i]->x() = swap;
        }
        if (vals[i-1]->y() > vals[i]->y())
        {
          float swap = vals[i-1]->y();
          vals[i-1]->y() = it->y();
          vals[i]->y() = swap;
        }

      }
    }
  }

  // Проверка пересечения с другим прямоугльником
  bool Intersection (Box2D const & obj)
  {
      return !((m_plb.x() > obj.m_prt.x()) || (m_plb.y() > obj.m_prt.y())
             || (m_prt.x() < obj.m_plb.x()) || (m_prt.y() < obj.m_plb.y()));
  }

  float area() const
  {
      return (m_prt.x() - m_plb.x()) * (m_prt.y() - m_plb.y());
  }

  // Оператор логического равенства.
  bool operator == (Box2D const & obj) const
  {
    return m_plb == obj.m_plb && m_prt == obj.m_prt;
  }

  // Оператор присваивания.
  Box2D & operator = (Box2D const & obj)
  {
    if (this == &obj) return *this;
    m_plb = obj.m_plb;
    m_prt = obj.m_prt;
    return *this;
  }

  // Оператор логического неравенства.
  bool operator != (Box2D const & obj) const
  {
    return !operator == (obj);
  }

  // Оператор меньше.
  bool operator < (Box2D const & obj) const
  {
    return area() < obj.area();

  }

  // Сложение.
  Box2D operator + (Box2D const & obj) const
  {
    return { m_plb + obj.m_plb, m_prt + obj.m_prt };
  }

  // Вычитание.
  Box2D operator - (Box2D const & obj) const
  {
    return { m_plb - obj.m_plb, m_prt - obj.m_prt };
  }

  // Математическое отрицание.
  Box2D operator - () const
  {
    return { -m_plb, -m_prt };
  }

  // Умножение на число.
  Box2D operator * (float scale) const
  {
    return { m_plb, m_prt * scale };
  }

  // Деление на число.
  Box2D operator / (float scale) const
  {
    if (EqualWithEps(scale, 0))
      {
        std::cout << "division by zero is not defined\n";
        return *this;
      }
    return { m_plb, m_prt / scale };;
  }

  Box2D & operator += (Box2D const & obj)
  {
    m_plb += obj.m_plb;
    m_prt += obj.m_prt;
    return *this;
  }

  Box2D & operator -= (Box2D const & obj)
  {
    m_plb -= obj.m_plb;
    m_prt -= obj.m_prt;
    return *this;
  }

  Box2D & operator *= (float scale)
  {
    m_prt *=scale;
    return *this;
  }

  Box2D & operator /= (float scale)
  {
    if (EqualWithEps(scale, 0))
    {
      std::cout << "division by zero is not defined\n";
      return *this;
    }
    m_prt /=scale;
    return *this;
  }

  Box2D MoveX (float x)
  {
    Point2D distance(x,0);
    m_plb+=distance;
    m_prt+=distance;
    return *this;
  }

  Box2D MoveY (float y)
  {
    Point2D distance(0,y);
    m_plb+=distance;
    m_prt+=distance;
    return *this;
  }

  Box2D Move (Point2D distance)
  {
    m_plb+=distance;
    m_prt+=distance;
    return *this;
  }

  Point2D const & LeftBot() const { return m_plb;}
  Point2D const & RightTop() const { return m_prt;}

private:

  bool EqualWithEps(float v1, float v2) const
  {
    return fabs(v1 - v2) < kEps;
  }

  Point2D m_plb{0.0f,0.0f},m_prt{0.0f,0.0f};

};

std::ostream & operator << (std::ostream & os, Box2D const & obj)
{
  os << "Box2D {" << obj.LeftBot() << ", " << obj.RightTop() << "}";
  return os;
}
