#ifndef ISOLVER_H
#define ISOLVER_H

#include "../../Util/IBroker.h"
#include "../../Util/Export.h"
#include "../../Util/ReturnCode.h"
#include "../../Logger/include/ILogger.h"
#include "../../Vector/include/IVector.h"
#include "../../Compact/include/ICompact.h"
#include "../../Problem/include/IProblem.h"
#include <string>  // string

class DECLSPEC ISolver {
public:
    // params - container used by solver that may contain e.g.
    // step vector of compact iterator, initial point, etc.
    // in our case it will be interpreted as steps for iterator
    // since our implementation of solver is in essence a brute
    // force solution search algorithm in specified area,
    // so the method of setting parameters with std::string
    // will not be used and may be implemented as dummy.
    // NOTE: set problem at first, then all the other stuff
    virtual ReturnCode setParams(std::string const& params)             = 0;
    virtual ReturnCode setParams(IVector const* params)                 = 0;
    virtual ReturnCode setProblemParams(IVector const* problemParams)   = 0;
    virtual ReturnCode setCompact(ICompact const* compact)              = 0;
    virtual ReturnCode setProblem(IProblem* problem)                    = 0;
    virtual ReturnCode solve()                                          = 0;
    virtual ReturnCode getSolution(IVector*& dst)                 const = 0;
    virtual size_t getParamsDim()                                 const = 0;

    ISolver() = default;
    virtual ~ISolver() = 0;

private:
    ISolver(const ISolver& other)            = delete;
    ISolver& operator=(const ISolver& other) = delete;
};


#endif // ISOLVER_H