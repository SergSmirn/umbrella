#pragma once
#include "point2d.hpp"
class Box2d
{
public:
  Box2d() = default;

  Box2d(Box2d const & obj):
  p_l_b(obj.p_l_b), p_r_t(obj.p_r_t)
  {}

  Box2d(Point2D leftp, Point2D rightp)
  :p_l_b(leftp), p_r_t(rightp)
  {}

  Box2d(std::initializer_list<Point2D> const & lst)
  {
    Point2D * vals[] = { &p_l_b, &p_r_t };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }

  // Проверка пересечения с другим прямоугльником
  bool intersection (Box2d const & obj)
  {

      return ((p_l_b.x()<=obj.p_l_b.x() && obj.p_l_b.x()<=p_r_t.x())
              || (obj.p_l_b.x()<=p_l_b.x() && p_l_b.x()<=obj.p_r_t.x()))
              &&((p_l_b.y()<=obj.p_l_b.y() && obj.p_l_b.y()<=p_r_t.y())
              || (obj.p_l_b.y()<=p_l_b.y() && p_l_b.y()<=obj.p_r_t.y()));

  }


  float area() const
  {
      return (p_r_t.x()-p_l_b.x())*(p_r_t.y()-p_l_b.y());
  }

  // Оператор логического равенства.
  bool operator == (Box2d const & obj) const
  {
    return p_l_b==obj.p_l_b && p_r_t==obj.p_r_t;
  }

  // Оператор присваивания.
  Box2d & operator = (Box2d const & obj)
  {
    if (this == &obj) return *this;
    p_l_b = obj.p_l_b;
    p_r_t = obj.p_r_t;
    return *this;
  }

  // Оператор логического неравенства.
  bool operator != (Box2d const & obj) const
  {
    return !operator==(obj);
  }

  // Оператор меньше.
  bool operator < (Box2d const & obj) const
  {
    if (area() < obj.area()) return 1;
    return 0;

  }

  // Сложение.
  Box2d operator + (Box2d const & obj) const
  {
    return { p_l_b + obj.p_l_b, p_r_t + obj.p_r_t };
  }

  // Вычитание.
  Box2d operator - (Box2d const & obj) const
  {
    return { p_l_b - obj.p_l_b, p_r_t - obj.p_r_t };
  }


  // Математическое отрицание.
  Box2d operator - () const
  {
    return { -p_l_b, -p_r_t };
  }

  // Умножение на число.
  Box2d operator * (float scale) const
  {
    return {p_l_b, p_r_t * scale };
  }

  // Деление на число.
  Box2d operator / (float scale) const
  {
    //TODO: обработать деление на 0.
    return {p_l_b, p_r_t / scale };;
  }

  Box2d & operator += (Box2d const & obj)
  {
    p_l_b += obj.p_l_b;
    p_r_t += obj.p_r_t;
    return *this;
  }

  Box2d & operator -= (Box2d const & obj)
  {
    p_l_b -= obj.p_l_b;
    p_r_t -= obj.p_r_t;
    return *this;
  }

  Box2d & operator *= (float scale)
  {
    p_r_t *=scale;
    return *this;
  }

  bool EqualWithEps(float v1, float v2) const
  {
    return fabs(v1 - v2) < kEps;
  }

  Box2d & operator /= (float scale)
  {
      if (EqualWithEps(scale, 0))
      {
        std::cout<<"division by zero is not defined\n";
        return *this;
      }
      p_r_t /=scale;
      return *this;
  }

  Box2d moveX (float X)
  {
    Point2D distance(X,0);
    p_l_b+=distance;
    p_r_t+=distance;
    return *this;
  }

  Box2d moveY (float Y)
  {
    Point2D distance(0,Y);
    p_l_b+=distance;
    p_r_t+=distance;
    return *this;
  }

  Box2d move (Point2D distance)
  {

    p_l_b+=distance;
    p_r_t+=distance;
    return *this;
  }

  Point2D & LeftBot() { return p_l_b;}
  Point2D & RightTop() { return p_r_t;}

  Point2D const & LeftBot() const { return p_l_b;}
  Point2D const & RightTop() const { return p_r_t;}


private:
  Point2D p_l_b{0.0f,0.0f},p_r_t{0.0f,0.0f};

};

std::ostream & operator << (std::ostream & os, Box2d const & obj)
{
  os << "Box2D {" << obj.LeftBot() << ", " << obj.RightTop() << "}";
  return os;
}
