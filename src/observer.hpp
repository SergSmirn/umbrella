#pragma once
#include <functional>
#include <list>
#include <algorithm>
#include <memory>

using TOnUpdateHandler = std::function<void()>;

class Observer
{
public:
  virtual ~Observer() {}
  virtual void UpdateHandler(TOnUpdateHandler const &) = 0;
  virtual bool operator==(Observer const &) = 0;
  virtual std::size_t Hash() const = 0;
};

using ObserverPtr = std::shared_ptr<Observer>;

class Subject
{
public:
  void RegObserver(ObserverPtr const & subscriber)
  {
    auto it = std::find(m_subscriberList.begin(), m_subscriberList.end(), subscriber);
    if (it == m_subscriberList.end())
      m_subscriberList.push_back(subscriber);
  }

  void UnregObserver(ObserverPtr const & subscriber)
  {
    auto it = std::find(m_subscriberList.begin(), m_subscriberList.end(), subscriber);
    if (it != m_subscriberList.end())
      m_subscriberList.erase(it);
  }

  void SendMessage(TOnUpdateHandler const & message)
  {
    for (auto const & i : m_subscriberList)
      i->UpdateHandler(message);
  }
protected:
  std::list<ObserverPtr> m_subscriberList;
};
