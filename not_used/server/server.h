#include "connect_func.h"

class Server {
 private:
  const char * port_num;

 public:
  Server(const char * myport) : port_num(myport) {}
  void run();
};