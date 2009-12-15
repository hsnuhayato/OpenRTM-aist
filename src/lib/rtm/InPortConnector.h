// -*- C++ -*-
/*!
 * @file InPortConnector.h
 * @brief InPortConnector base class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_INPORTCONNECTOR_H
#define RTC_INPORTCONNECTOR_H

#include <rtm/ConnectorBase.h>

namespace RTC
{
  /*!
   * @if jp
   * @class InPortConnector
   * @brief InPortConnector 基底クラス
   *
   * InPort の Push/Pull 各種 Connector を派生させるための
   * 基底クラス。
   *
   * @since 1.0.0
   *
   * @else
   * @class InPortConnector
   * @brief IｎPortConnector base class
   *
   * The base class to derive subclasses for InPort's Push/Pull Connectors
   *
   * @since 1.0.0
   *
   * @endif
   */
  class InPortConnector
    : public ConnectorBase
  {
  public:
    DATAPORTSTATUS_ENUM
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    InPortConnector(ConnectorInfo& info,
                    CdrBufferBase* buffer);

    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~InPortConnector();

   /*!
     * @if jp
     * @brief ConnectorInfo 取得
     *
     * Connector ConnectorInfo を取得する
     *
     * @else
     * @brief Getting ConnectorInfo
     *
     * This operation returns ConnectorInfo
     *
     * @endif
     */
    virtual const ConnectorInfo& profile();
    /*!
     * @if jp
     * @brief Connector ID 取得
     *
     * Connector ID を取得する
     *
     * @else
     * @brief Getting Connector ID
     *
     * This operation returns Connector ID
     *
     * @endif
     */
    virtual const char* id();

    /*!
     * @if jp
     * @brief Connector 名取得
     *
     * Connector 名を取得する
     *
     * @else
     * @brief Getting Connector name
     *
     * This operation returns Connector name
     *
     * @endif
     */
    virtual const char* name();

    /*!
     * @if jp
     * @brief 接続解除関数
     *
     * Connector が保持している接続を解除する
     *
     * @else
     * @brief Disconnect connection
     *
     * This operation disconnect this connection
     *
     * @endif
     */
    virtual ReturnCode disconnect() = 0;

    /*!
     * @if jp
     * @brief Buffer を取得する
     *
     * Connector が保持している Buffer を返す
     *
     * @else
     * @brief Getting Buffer
     *
     * This operation returns this connector's buffer
     *
     * @endif
     */
    virtual CdrBufferBase* getBuffer();

    /*!
     * @if jp
     * @brief read 関数
     *
     * Buffer からデータを InPort へ read する関数
     *
     * @else
     * @brief Destructor
     *
     * The read function to read data from buffer to InPort
     *
     * @endif
     */
    virtual ReturnCode read(cdrMemoryStream& data) = 0;

    /*!
     * @if jp
     * @brief endianタイプ設定
     *
     * endianタイプを設定する
     *
     * @else
     * @brief Setting an endian type
     *
     * This operation set this connector's endian type
     *
     * @endif
     */
    virtual void setEndian(const bool endian_type);

    /*!
     * @if jp
     * @brief endian 設定を返す
     *
     * endian 設定のbool値を返す。
     *
     * @return m_littleEndian がlittleの場合true、bigの場合false を返す。
     *
     * @else
     * @brief
     *
     * return it whether endian setting.
     *
     *@return Return true in the case of "little", false in "big" than it.
     *
     * @endif
     */
    virtual bool isLittleEndian();

  protected:
    Logger rtclog;
    ConnectorInfo m_profile;
    CdrBufferBase* m_buffer;
    bool m_littleEndian;
  };
}; // namespace RTC

#endif // RTC_INPORTCONNECTOR_H
