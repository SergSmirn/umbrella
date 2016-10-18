#pragma once
#include "headerlist.hpp"

class Space : public GameObject
{
public:
  Space() = default;

  Space(Point2D lbp, Point2D rtp)
   : GameObject(lbp, rtp, "Space") {}

  ~Space() override {}

  void AddGameObject(TGameObjectConstPtr gameObject)
  {
    m_gameObjectList.push_back(gameObject);
  }

  std::list<TGameObjectConstPtr> const & GetGameObject()
  {
    return m_gameObjectList;
  }

  void ExitCheck()
  {
    for (auto it = m_gameObjectList.begin(); it != m_gameObjectList.end(); )
    {
      if(!(m_box.Box2D::LeftBot() < (*it)->LeftBot() && (*it)->RightTop() < m_box.Box2D::RightTop())) m_gameObjectList.erase(it);
      else ++it;
    }
  }

private:
  std::list<TGameObjectConstPtr> m_gameObjectList;
};
