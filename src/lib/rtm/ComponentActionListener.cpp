﻿// -*- C++ -*-
/*!
 * @file ComponentActionListener.cpp
 * @brief Component action listener class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2011
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <rtm/ComponentActionListener.h>

namespace RTC
{

  //============================================================
  /*!
   * @if jp
   * @class PostComponentActionListener クラス
   * @else
   * @class PostComponentActionListener class
   * @endif
   */
  PostComponentActionListener::~PostComponentActionListener() {}

  /*!
   * @if jp
   * @class PreComponentActionListener クラス
   * @else
   * @class PreComponentActionListener class
   * @endif
   */
  PreComponentActionListener::~PreComponentActionListener() {}

  /*!
   * @if jp
   * @class PortActionListener クラス
   * @else
   * @class PortActionListener class
   * @endif
   */
  PortActionListener::~PortActionListener() {}

  /*!
   * @if jp
   * @class ExecutionContextActionListener クラス
   * @else
   * @class ExecutionContextActionListener class
   * @endif
   */
  ExecutionContextActionListener::~ExecutionContextActionListener() {}





  //============================================================
  /*!
   * @if jp
   * @class PreComponentActionListener ホルダクラス
   * @else
   * @class PreComponentActionListener holder class
   * @endif
   */
  PreComponentActionListenerHolder::PreComponentActionListenerHolder()
  {
  }


  PreComponentActionListenerHolder::~PreComponentActionListenerHolder()
  {
    std::lock_guard<coil::Mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        if (listener.second)
          {
            delete listener.first;
          }
      }
  }


  void PreComponentActionListenerHolder::
  addListener(PreComponentActionListener* listener,
              bool autoclean)
  {
    std::lock_guard<coil::Mutex> guard(m_mutex);
    m_listeners.emplace_back(listener, autoclean);
  }


  void PreComponentActionListenerHolder::
  removeListener(PreComponentActionListener* listener)
  {
    std::lock_guard<coil::Mutex> guard(m_mutex);
    std::vector<Entry>::iterator it(m_listeners.begin());

    for (; it != m_listeners.end(); ++it)
      {
        if (it->first == listener)
          {
            if (it->second)
              {
                delete it->first;
              }
            m_listeners.erase(it);
            return;
          }
      }

  }


  void PreComponentActionListenerHolder::notify(UniqueId ec_id)
  {
    std::lock_guard<coil::Mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        listener.first->operator()(ec_id);
      }
  }

  //============================================================
  /*!
   * @if jp
   * @class PostComponentActionListener ホルダクラス
   * @else
   * @class PostComponentActionListener holder class
   * @endif
   */
  PostComponentActionListenerHolder::PostComponentActionListenerHolder()
  {
  }


  PostComponentActionListenerHolder::~PostComponentActionListenerHolder()
  {
    std::lock_guard<coil::Mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        if (listener.second)
          {
            delete listener.first;
          }
      }
  }


  void PostComponentActionListenerHolder::
  addListener(PostComponentActionListener* listener, bool autoclean)
  {
    std::lock_guard<coil::Mutex> guard(m_mutex);
    m_listeners.emplace_back(listener, autoclean);
  }


  void PostComponentActionListenerHolder::
  removeListener(PostComponentActionListener* listener)
  {
    std::lock_guard<coil::Mutex> guard(m_mutex);
    std::vector<Entry>::iterator it(m_listeners.begin());
    for (; it != m_listeners.end(); ++it)
      {
        if ((*it).first == listener)
          {
            if ((*it).second)
              {
                delete (*it).first;
              }
            m_listeners.erase(it);
            return;
          }
      }

  }


  void PostComponentActionListenerHolder::notify(UniqueId ec_id,
                                                 ReturnCode_t ret)
  {
    std::lock_guard<coil::Mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        listener.first->operator()(ec_id, ret);
      }
  }


  /*!
   * @if jp
   * @class PortActionListener ホルダクラス
   * @else
   * @class PortActionListener holder class
   * @endif
   */
  PortActionListenerHolder::PortActionListenerHolder()
  {
  }


  PortActionListenerHolder::~PortActionListenerHolder()
  {
    std::lock_guard<coil::Mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        if (listener.second)
          {
            delete listener.first;
          }
      }
  }


  void PortActionListenerHolder::addListener(PortActionListener* listener,
                                             bool autoclean)
  {
    std::lock_guard<coil::Mutex> guard(m_mutex);
    m_listeners.emplace_back(listener, autoclean);
  }


  void PortActionListenerHolder::removeListener(PortActionListener* listener)
  {
    std::lock_guard<coil::Mutex> guard(m_mutex);
    std::vector<Entry>::iterator it(m_listeners.begin());

    for (; it != m_listeners.end(); ++it)
      {
        if ((*it).first == listener)
          {
            if ((*it).second)
              {
                delete (*it).first;
              }
            m_listeners.erase(it);
            return;
          }
      }

  }


  void PortActionListenerHolder::notify(const RTC::PortProfile& pprofile)
  {
    std::lock_guard<coil::Mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        listener.first->operator()(pprofile);
      }
  }



  /*!
   * @if jp
   * @class ExecutionContextActionListener ホルダクラス
   * @else
   * @class ExecutionContextActionListener holder class
   * @endif
   */
  ExecutionContextActionListenerHolder::ExecutionContextActionListenerHolder()
  {
  }


  ExecutionContextActionListenerHolder::~ExecutionContextActionListenerHolder()
  {
    std::lock_guard<coil::Mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        if (listener.second)
          {
            delete listener.first;
          }
      }
  }


  void ExecutionContextActionListenerHolder::
  addListener(ExecutionContextActionListener* listener,
              bool autoclean)
  {
    std::lock_guard<coil::Mutex> guard(m_mutex);
    m_listeners.emplace_back(listener, autoclean);
  }


  void ExecutionContextActionListenerHolder::
  removeListener(ExecutionContextActionListener* listener)
  {
    std::lock_guard<coil::Mutex> guard(m_mutex);
    std::vector<Entry>::iterator it(m_listeners.begin());

    for (; it != m_listeners.end(); ++it)
      {
        if ((*it).first == listener)
          {
            if ((*it).second)
              {
                delete (*it).first;
              }
            m_listeners.erase(it);
            return;
          }
      }

  }


  void ExecutionContextActionListenerHolder::notify(UniqueId ec_id)
  {
    std::lock_guard<coil::Mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        listener.first->operator()(ec_id);
      }
  }

  /*!
   * @if jp
   * @class ComponentActionListeners
   * @else
   * @class ComponentActionListeners class
   * @endif
   */

    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
  ComponentActionListeners::ComponentActionListeners()
    {
    }
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
  ComponentActionListeners::~ComponentActionListeners()
    {
    }
} // namespace RTC

