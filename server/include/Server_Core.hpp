#ifndef SERVER_CORE
#define SERVER_CORE

#include <string>

class Server_Core{
        int port_number = 54000;
        std::string address ="0.0.0.0";

        public:
           Server_Core();
           Server_Core(int port, std::string address);
           int threadDispatch();
           void run();
           void idiotic_respond();
           friend std::ostream& operator<< (std::ostream& os, Server_Core& s);
};

#endif
