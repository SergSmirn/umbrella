#pragma once
#include "headerlist.hpp"
class GameObject
{
public:
  GameObject() = default;

  GameObject(Point2D const & lbp, Point2D const & rtp, std::string const & name)
  {
    m_box.Order(lbp,rtp);
    m_name = name;
  }

  virtual ~GameObject() {}

  bool operator == (GameObject const & obj) const
  {
    return m_box == obj.GetBox() && m_name == obj.GetName();
  }

  std::string const & GetName() const
  {
    return m_name;
  }

  Box2D const & GetBox() const { return m_box;}

  bool Intersection(GameObject const & go)
  {
    return m_box.Intersection(go.GetBox());
  }

  GameObject & MoveX (float x)
  {
    m_box.MoveX(x);
    return *this;
  }

  GameObject & MoveY (float y)
  {
    m_box.MoveY(y);
    return *this;
  }

  GameObject & Move (Point2D distance)
  {
    m_box.Move(distance);
    return *this;
  }

  Point2D const & LeftBot() const { return m_box.LeftBot();}
  Point2D const & RightTop() const { return m_box.RightTop();}

protected:
  Box2D m_box;
  std::string m_name;
};

using TGameObjectPtr = std::shared_ptr<GameObject>;
using TGameObjectConstPtr = std::shared_ptr<GameObject const>;
