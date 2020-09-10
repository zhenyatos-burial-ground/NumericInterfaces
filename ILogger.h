#ifndef ILOGGER_H
#define ILOGGER_H

#include "../../Util/ReturnCode.h"
#include "../../Util/Export.h"

class DECLSPEC ILogger {
public:
    static ILogger* createLogger(void* client);
    virtual void releaseLogger(void* client)                     = 0;
    virtual void log(char const* message, ReturnCode returnCode) = 0;
    virtual ReturnCode setLogFile(char const* logFileName)       = 0;

    ILogger() = default;
    virtual ~ILogger() = 0;

private:
    ILogger(ILogger const&)            = delete;
    ILogger& operator=(ILogger const&) = delete;
};

#endif /* ILOGGER_H */
