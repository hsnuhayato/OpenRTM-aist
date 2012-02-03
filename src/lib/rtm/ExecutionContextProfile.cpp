// -*- C++ -*-
/*!
 * @file ExecutionContextProfile.cpp
 * @brief ExecutionContextProfile class
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

#include <rtm/ExecutionContextProfile.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>

#define DEEFAULT_PERIOD 0.000001

namespace RTC_impl
{

  /*!
   * @if jp
   * @brief �ǥե���ȥ��󥹥ȥ饯��
   * @else
   * @brief Default constructor
   * @endif
   */
  ExecutionContextProfile::
  ExecutionContextProfile(RTC::ExecutionKind kind)
    : rtclog("periodic_ecprofile"),
      m_period((double)DEEFAULT_PERIOD),
      m_ref(RTC::ExecutionContextService::_nil())
  {
    RTC_TRACE(("ExecutionContextProfile()"));
    RTC_DEBUG(("Actual rate: %d [sec], %d [usec]",
               m_period.sec(), m_period.usec()));
    // profile initialization
    m_profile.kind = RTC::PERIODIC;
    m_profile.rate = 1.0 / m_period;
    m_profile.owner = RTC::RTObject::_nil();
    m_profile.participants.length(0);
    m_profile.properties.length(0);
  }

  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   * @brief Destructor
   * @endif
   */
  ExecutionContextProfile::~ExecutionContextProfile()
  {
    RTC_TRACE(("~ExecutionContextProfile()"));

    // cleanup EC's profile
    m_profile.owner = RTC::RTObject::_nil();
    m_profile.participants.length(0);
    m_profile.properties.length(0);
    m_ref = RTC::ExecutionContextService::_nil();
  }

  /*!
   * @if jp
   * @brief CORBA ���֥������Ȼ��Ȥμ���
   * @else
   * @brief Get the reference to the CORBA object
   * @endif
   */
  void ExecutionContextProfile::
  setObjRef(RTC::ExecutionContextService_ptr ec_ptr)
  {
    RTC_TRACE(("setObjRef()"));
    Guard guard(m_profileMutex);
    m_ref = RTC::ExecutionContextService::_duplicate(ec_ptr);
  }

  /*!
   * @if jp
   * @brief CORBA ���֥������Ȼ��Ȥμ���
   * @else
   * @brief Get the reference to the CORBA object
   * @endif
   */
  RTC::ExecutionContextService_ptr
  ExecutionContextProfile::getObjRef(void) const
  {
    RTC_TRACE(("getObjRef()"));
    Guard guard(m_profileMutex);
    return RTC::ExecutionContextService::_duplicate(m_ref);
  }

  /*!
   * @if jp
   * @brief ExecutionContext �μ¹Լ���(Hz)�����ꤹ��
   * @else
   * @brief Set execution rate(Hz) of ExecutionContext
   * @endif
   */
  RTC::ReturnCode_t ExecutionContextProfile::setRate(double rate)
  {
    RTC_TRACE(("set_rate(%f)", rate));
    if (rate < 0.0) { return RTC::BAD_PARAMETER; }

    Guard guard(m_profileMutex);
    m_profile.rate = rate;
    m_period = coil::TimeValue(1.0/rate);
    return RTC::RTC_OK;
  }
  RTC::ReturnCode_t ExecutionContextProfile::setPeriod(double period)
  {
    RTC_TRACE(("setPeriod(%f [sec])", period));
    if (period < 0.0) { return RTC::BAD_PARAMETER; }

    Guard guard(m_profileMutex);
    m_profile.rate = 1.0 / period;
    m_period = coil::TimeValue(period);
    return RTC::RTC_OK;
  }
  RTC::ReturnCode_t ExecutionContextProfile::setPeriod(coil::TimeValue period)
  {
    RTC_TRACE(("setPeriod(%f [sec])", (double)period));
    if ((double)period < 0.0) { return RTC::BAD_PARAMETER; }

    Guard guard(m_profileMutex);
    m_profile.rate = 1.0 / (double)period;
    m_period = period;
    return RTC::RTC_OK;
  }

  /*!
   * @if jp
   * @brief ExecutionContext �μ¹Լ���(Hz)���������
   * @else
   * @brief Get execution rate(Hz) of ExecutionContext
   * @endif
   */
  CORBA::Double ExecutionContextProfile::getRate() const
  {
    RTC_TRACE(("get_rate()"));
    Guard guard(m_profileMutex);
    return m_profile.rate;
  }

  coil::TimeValue ExecutionContextProfile::getPeriod() const
  {
    RTC_TRACE(("getPeriod()"));
    Guard guard(m_profileMutex);
    return m_period;
  }

  /*!
   * @if jp
   * @brief ExecutionKind ��ʸ���󲽤���
   * @else
   * @brief Converting ExecutionKind enum to string
   * @endif
   */
  const char*
  ExecutionContextProfile::getKindString(RTC::ExecutionKind kind) const
  {
    const char* kinds[] = {"PERIODIC", "EVENT_DRIVEN", "OTHER"};
    if (kind < RTC::PERIODIC || kind > RTC::OTHER)
      {
        return "";
      }
    return kinds[kind];
  }

  /*!
   * @if jp
   * @brief ExecutionKind ���������
   * @else
   * @brief Get the ExecutionKind
   * @endif
   */
  RTC::ReturnCode_t ExecutionContextProfile::setKind(RTC::ExecutionKind kind)
  {
    if (kind < RTC::PERIODIC || kind > RTC::OTHER)
      {
        RTC_ERROR(("Invalid kind is given. %d", kind));
        return RTC::BAD_PARAMETER;
      }
    RTC_TRACE(("setKind(%s)", getKindString(kind)));
    Guard guard(m_profileMutex);
    m_profile.kind = kind;
    return RTC::RTC_OK;
  }

  /*!
   * @if jp
   * @brief ExecutionKind ���������
   * @else
   * @brief Get the ExecutionKind
   * @endif
   */
  RTC::ExecutionKind ExecutionContextProfile::getKind(void) const
  {
    RTC_TRACE(("%s = getKind()", getKindString(m_profile.kind)));
    return m_profile.kind;
  }

  /*!
   * @if jp
   * @brief Owner����ݡ��ͥ�Ȥ򥻥åȤ��롣
   * @else
   * @brief Setting owner component of the execution context
   * @endif
   */
  RTC::ReturnCode_t ExecutionContextProfile::
  setOwner(RTC::LightweightRTObject_ptr comp)
  {
    RTC_TRACE(("setOwner()"));
    if (CORBA::is_nil(comp))
      {
        RTC_ERROR(("nil reference is given."));
        return RTC::BAD_PARAMETER;
      }
    RTC::RTObject_var rtobj;
    rtobj = RTC::RTObject::_narrow(comp);
    if (CORBA::is_nil(rtobj))
      {
        RTC_ERROR(("Narrowing failed."));
        return RTC::RTC_ERROR;
      }
    m_profile.owner = RTC::RTObject::_duplicate(m_profile.owner);
    return RTC::RTC_OK;
  }

  /*!
   * @if jp
   * @brief Owner����ݡ��ͥ�Ȥλ��Ȥ��������
   * @else
   * @brief Getting a reference of the owner component
   * @endif
   */
  const RTC::RTObject_ptr ExecutionContextProfile::getOwner() const
  {
    RTC_TRACE(("getOwner()"));
    return RTC::RTObject::_duplicate(m_profile.owner);
  }

  /*!
   * @if jp
   * @brief RT����ݡ��ͥ�Ȥ��ɲä���
   * @else
   * @brief Add an RT-component
   * @endif
   */
  RTC::ReturnCode_t
  ExecutionContextProfile::addComponent(RTC::LightweightRTObject_ptr comp)
  {
    RTC_TRACE(("addComponent()"));
    if (CORBA::is_nil(comp))
      {
        RTC_ERROR(("A nil reference was given."));
        return RTC::BAD_PARAMETER;
      }
    RTC::RTObject_var rtobj = RTC::RTObject::_narrow(comp);
    if (CORBA::is_nil(rtobj))
      {
        RTC_ERROR(("Narrowing was failed."));
        return RTC::RTC_ERROR;
      }
    CORBA_SeqUtil::push_back(m_profile.participants, rtobj._retn());
    return RTC::RTC_OK;
  }

  /*!
   * @if jp
   * @brief RT����ݡ��ͥ�Ȥ򻲲üԥꥹ�Ȥ���������
   * @else
   * @brief Remove the RT-Component from participant list
   * @endif
   */
  RTC::ReturnCode_t
  ExecutionContextProfile::removeComponent(RTC::LightweightRTObject_ptr comp)
  {
    RTC_TRACE(("removeComponent()"));
    if (CORBA::is_nil(comp))
      {
        RTC_ERROR(("A nil reference was given."));
        return RTC::BAD_PARAMETER;
      }
    RTC::RTObject_var rtobj = RTC::RTObject::_narrow(comp);
    if (CORBA::is_nil(rtobj))
      {
        RTC_ERROR(("Narrowing was failed."));
        return RTC::RTC_ERROR;
      }
    {
      Guard guard(m_profileMutex);
      CORBA::Long index;
      index = CORBA_SeqUtil::find(m_profile.participants,
                                  find_participant(rtobj));
      if (index < 0)
        {
          RTC_ERROR(("The given RTObject does not exist in the EC."));
          return RTC::BAD_PARAMETER;
        }
      CORBA_SeqUtil::erase(m_profile.participants, index);
    }
    return RTC::RTC_OK;
  }

  /*!
   * @if jp
   * @brief ExecutionKind ���������
   * @else
   * @brief Get the ExecutionKind
   * @endif
   */
  const RTC::RTCList& ExecutionContextProfile::getComponentList() const
  {
    RTC_TRACE(("getComponentList(%d)", m_profile.participants.length()));
    return m_profile.participants;
  }

  /*!
   * @if jp
   * @brief Properties�򥻥åȤ���
   * @else
   * @brief Setting Properties
   * @endif
   */
  void ExecutionContextProfile::setProperties(coil::Properties& props)
  {
    RTC_TRACE(("setProperties()"));
    RTC_DEBUG_STR((props));
    Guard guard(m_profileMutex);
    NVUtil::copyFromProperties(m_profile.properties, props);
  }

  /*!
   * @if jp
   * @brief Properties���������
   * @else
   * @brief Setting Properties
   * @endif
   */
  const coil::Properties ExecutionContextProfile::getProperties() const
  {
    RTC_TRACE(("getProperties()"));
    Guard guard(m_profileMutex);
    coil::Properties props;
    NVUtil::copyToProperties(props, m_profile.properties);
    RTC_DEBUG_STR((props));
    return props;
  }

  /*!
   * @if jp
   * @brief ExecutionContextProfile ���������
   * @else
   * @brief Get the ExecutionContextProfile
   * @endif
   */
  RTC::ExecutionContextProfile* ExecutionContextProfile::getProfile()
  {
    RTC_TRACE(("getProfile()"));
    RTC::ExecutionContextProfile_var p;
    {
      Guard guard(m_profileMutex);
      p = new RTC::ExecutionContextProfile(m_profile);
    }
    return p._retn();
  }

  /*!
   * @if jp
   * @brief ExecutionContextProfile ���������
   * @else
   * @brief Get the ExecutionContextProfile
   * @endif
   */
  const RTC::ExecutionContextProfile&
  ExecutionContextProfile::getProfile() const
  {
    RTC_TRACE(("getProfile()"));
    Guard guard(m_profileMutex);
    return m_profile;
  }

  /*!
   * @if jp
   * @brief ExecutionContextProfile����å�����
   * @else
   * @brief Getting a lock of RTC::ExecutionContextProfile
   * @endif
   */
  void ExecutionContextProfile::lock() const
  {
    m_profileMutex.lock();
  }

  /*!
   * @if jp
   * @brief ExecutionContextProfile�򥢥���å�����
   * @else
   * @brief Release a lock of the RTC::ExecutionContextProfile
   * @endif
   */
  void ExecutionContextProfile::unlock() const
  {
    m_profileMutex.unlock();
  }

}; // namespace RTC