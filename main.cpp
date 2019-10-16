
/*  test demo
 */

#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <netinet/in.h> /* For htonl and ntohl */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <time.h>
#include <unistd.h>
#include <vector>

#include <nbobservable/nbobservable.hpp>

using namespace std;

static void update(int num) { std::cout << "static function update, Num: " << num << std::endl; }

class TestObserver {
public:
  TestObserver() {}

  ~TestObserver() {}

  void update(int num) { std::cout << "Class function update, Num: " << num << std::endl; }
};

class TestSource : public nbobservable::Observable<void(int)> {
public:
  TestSource() {};
  ~TestSource() {};

  void start() {
    m_pthread =
        std::make_shared<std::thread>(&TestSource::produceCallback, this);
  }

  void stop() {
    exit_ = true;
    m_pthread->join();
  }

private:
  bool exit_ = false;
  std::shared_ptr<std::thread> m_pthread;

  void produceCallback() {
    static int num = 0;

    while (!exit_) {
      notifyObservers(num++);

      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
  }
};

static bool isExit = false;
static void intSigintHandler(int sig) {
  isExit = true;
  std::cout << "user exit!" << std::endl;
}

int main(int argc, char **argv) {
  signal(SIGINT, intSigintHandler);

  std::shared_ptr<TestSource> psource = std::make_shared<TestSource>();
  std::shared_ptr<TestObserver> ptarget = std::make_shared<TestObserver>();

  int con1 = psource->registerObserver(std::bind(&TestObserver::update, ptarget, std::placeholders::_1));
  std::cout << "connected->" << con1 << std::endl;

  int con2 = psource->registerObserver(std::bind(update, std::placeholders::_1));
  std::cout << "connected->" << con2 << std::endl;

  psource->start();
  while (!isExit) {
    // TODO
    usleep(10 * 1000);
  }

  psource->stop();

  // psource->removeObserver(con1);
  // psource->removeObserver(con2);
  psource->clearAllObservers();

  return 0;
}
