#include "Common.h"
#ifndef API_H
#define API_H
class ApiSetup
{
public:
    static void initRoutingConfig();

private:
    static void getStatus();
    static void handleNotFound();
    static void prepareHeader();
};
#endif
