#pragma once
#include "box2d.hpp"

class GameObject : public Box2D
{
public:
  GameObject() = default;

  GameObject(Point2D const & lbp, Point2D const & rtp, std::string const & name)
   : Box2D(lbp, rtp)
  {
    m_name = name;
  }

  ~GameObject() override {}

/*
  GameEntity(std::initializer_list<unsigned> const & lst)
   : Box2D(lst)
  {
    unsigned * vals[] = { &m_health };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }
*/

  std::string const & GetName() const
  {
    return m_name;
  }

protected:
  std::string m_name;
};

using TGameObjectPtr = std::shared_ptr<GameObject>;
using TGameObjectConstPtr = std::shared_ptr<GameObject const>;
