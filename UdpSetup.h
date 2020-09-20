#include "Common.h"
#ifndef UDP_H
#define UDP_H
class UdpSetup
{
public:
    static void init();
    static void listen();
    static void broadcast();
};
#endif
