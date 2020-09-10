#ifndef IPROBLEM_H
#define IPROBLEM_H

#include "../../Util/IBroker.h"
#include "../../Util/Export.h"
#include "../../Util/ReturnCode.h"
#include "../../Logger/include/ILogger.h"
#include "../../Vector/include/IVector.h"
#include "../../Compact/include/ICompact.h"

class DECLSPEC IProblem {
public:
    virtual ReturnCode objectiveFunction(double& res, IVector const* args, IVector const* params = nullptr) = 0;
    virtual ReturnCode setParams(IVector const* params)                                                     = 0;
    virtual bool isValidCompact(ICompact const* compact) const = 0;
    virtual size_t getParamsDim()                        const = 0;
    virtual size_t getArgsDim()                          const = 0;

    IProblem() = default;
    virtual ~IProblem() = 0;

private:
    IProblem(IProblem const& other)             = delete;
    IProblem& operator=(IProblem const& other)  = delete;

};

#endif // IPROBLEM_H