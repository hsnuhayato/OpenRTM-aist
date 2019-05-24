// -*- C++ -*-
/*!
 * @file Task_posix.h
 * @brief Task class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_TASK_H
#define COIL_TASK_H

#include <thread>

namespace coil
{
  /*!
   * @if jp
   *
   * @class Task
   * @brief Task ���饹
   *
   * @else
   *
   * @class Task
   * @brief Task class
   *
   * @endif
   */
  class Task
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    Task();

    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯��
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~Task();

    /*!
     * @if jp
     *
     * @brief �����������ץ�
     *
     * �����������ץ�
     *
     * @param args ����
     *
     * @else
     *
     * @brief Task open
     *
     * Task open
     *
     * @param args Arguments
     *
     * @endif
     */
    virtual int open(void* args = nullptr);

    /*!
     * @if jp
     *
     * @brief ��������������
     *
     * ��������������
     *
     * @param flags �ե饰
     *
     * @else
     *
     * @brief Task close
     *
     * Task close
     *
     * @param flags Flags
     *
     * @endif
     */
    virtual int close(unsigned long flags = 0);

    /*!
     * @if jp
     *
     * @brief ����åɤ�¹Ԥ���
     *
     * ����åɤ�¹Ԥ���
     *
     * @else
     *
     * @brief Execute thread
     *
     * Execute thread
     *
     * @endif
     */
    virtual int svc();

    /*!
     * @if jp
     *
     * @brief ����åɤ���������
     *
     * ����åɤ���������
     *
     * @else
     *
     * @brief Create a thread
     *
     * Create a thread
     *
     * @endif
     */
    virtual void activate();

    /*!
     * @if jp
     *
     * @brief ����åɽ�λ���Ԥ�
     *
     * ����åɽ�λ���Ԥ�
     *
     * @else
     *
     * @brief Waiting for the thread terminate
     *
     * Waiting for the thread terminate
     *
     * @endif
     */
    virtual int wait();

    /*!
     * @if jp
     *
     * @brief �������¹Ԥ����Ǥ���
     *
     * �������¹Ԥ����Ǥ���
     *
     * @else
     *
     * @brief Suspending the task
     *
     * Suspending the task
     *
     * @endif
     */
    virtual int suspend();

    /*!
     * @if jp
     *
     * @brief ���Ǥ���Ƥ��륿������Ƴ�����
     *
     * ���Ǥ���Ƥ��륿������Ƴ�����
     *
     * @else
     *
     * @brief Resuming the suspended task
     *
     * Resuming the suspended task
     *
     * @endif
     */
    virtual int resume();

    /*!
     * @if jp
     *
     * @brief ���������ꥻ�å�
     *
     * ���������ꥻ�å�
     *
     * @else
     *
     * @brief Reset of task count
     *
     * Reset of task count
     *
     * @endif
     */
    virtual void reset();

    /*!
     * @if jp
     *
     * @brief �������¹Ԥ�λ����
     *
     * �������¹Ԥ�λ����
     *
     * @else
     *
     * @brief Finalizing the task
     *
     * Finalizing the task.
     *
     * @endif
     */
    virtual void finalize();

  private:
    int m_count;
    std::thread m_thread;
  };
} // namespace coil

#endif  // COIL_TASK_H