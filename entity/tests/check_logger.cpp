#include "entity/logger.h"

int main(int /* argc */, char ** /* argv */)
{
    using namespace entity;
    Logger& logger = Logger::getInstance();
    logger.setLevel(ERROR);
    // logger.setLevel(DEBUG);
    logger.log(DEBUG, "DEBUG");
    logger.log(INFO, "INFO");
    logger.log(NOTICE, "NOTICE");
    logger.log(WARNING, "WARNING");
    //logger.log(ERROR, "ERROR");
    //logger.log(CRITICAL, "CRITICAL");
    return 0;
}

