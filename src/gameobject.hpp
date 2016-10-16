#pragma once
#include "headerlist.hpp"


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

  std::string const & GetName() const
  {
    return m_name;
  }

protected:
  std::string m_name;
};

using TGameObjectPtr = std::shared_ptr<GameObject>;
using TGameObjectConstPtr = std::shared_ptr<GameObject const>;
