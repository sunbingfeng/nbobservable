/**
 * Author: Bill(cocobill1987ATgmail.com)
 * Description: An easy to use observable module implemented in CPP
 * License: see the LICENSE.txt file
 */
#ifndef NB_OBSERVABLE_
#define NB_OBSERVABLE_

#include <boost/signals2/signal.hpp>

#include <functional>
#include <unordered_map>

namespace nbobservable {

template <class T> class Observable {
public:
  typedef typename boost::signals2::signal<T> t_signal_type;
  typedef typename t_signal_type::slot_type t_slot_type;

  Observable(){};
  ~Observable(){};

public:
  /**
   * Register an observer
   *
   * @param[in]  slot  observer slot
   *
   * @return     connection handler
   */
  int registerObserver(const t_slot_type &slot) {
    static int handler = -1;
    int current = ++handler;
    m_connections[current] = m_signal.connect(slot);
    return current;
  }

  /**
   * Remove an observer
   *
   * @param[in]  handler  The handler related to the connection
   */
  void removeObserver(int handler) {
    if (m_connections.count(handler)) {
      m_connections[handler].disconnect();
      m_connections.erase(handler);
    }
  }

  /**
   * @brief      Remove all slot connections
   */
  void clearAllObservers()
  {
    m_signal.disconnect_all_slots();
  }

  /**
   * Notify all the registered observers when a change happens
   */
  template <typename... Args> void notifyObservers(Args... args) {
    m_signal(std::forward<Args>(args)...);
  }

private:
  t_signal_type m_signal;
  std::unordered_map<int, boost::signals2::connection> m_connections;
};
} // namespace nbobservable

#endif // NB_OBSERVABLE_