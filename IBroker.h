#ifndef IBROKER_H
#define IBROKER_H

#include "Export.h"

class DECLSPEC IBroker {
public:
    enum class BrokerType {
        BT_PROBLEM,
        BT_SOLVER
    };

    virtual void release()                                = 0;
    virtual bool canCastTo(BrokerType type)         const = 0;
    virtual void* getInterfaceImpl(BrokerType type) const = 0;

    IBroker() = default;
    virtual ~IBroker() {};

private:
    IBroker(IBroker const& other)               = delete;
    IBroker& operator=(IBroker const& other)    = delete;
};

#endif /* IBROKER_H */
