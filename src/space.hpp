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

  void ExitCheck(GameObject obj)
  {
    if (!(m_plb < obj.LeftBot() && obj.RightTop() < m_prt))
            obj.GameObject::~GameObject();
  }

private:
  std::list<TGameObjectConstPtr> m_gameObjectList;
};
