#ifndef ICOMPACT_H
#define ICOMPACT_H

#include <cstddef> // size_t
#include <vector>  // vector
#include "../../Logger/include/ILogger.h"
#include "../../Vector/include/IVector.h"
#include "../../Util/ReturnCode.h"
#include "../../Util/Export.h"

class DECLSPEC ICompact {
public:
    class Iterator {
    public:
        virtual IVector* getPoint() const = 0;
        // change order of step
        virtual ReturnCode setDirection(std::vector<size_t> const& direction) = 0;
        // adds step to current value in Iterator
        virtual ReturnCode doStep() = 0;

        Iterator() = default;
        virtual ~Iterator() = 0;

    private:
        Iterator(Iterator const&)            = delete;
        Iterator& operator=(Iterator const&) = delete;
    };

    static ICompact* createCompact(IVector const* begin, IVector const* end, double tolerance, ILogger* logger = nullptr);
    static ICompact* _union(ICompact const* comp1, ICompact const* comp2, double tolerance, ILogger* logger = nullptr);
    static ICompact* convex(ICompact const* comp1, ICompact const* comp2, double tolerance, ILogger* logger = nullptr);
    static ICompact* intersection(ICompact const* comp1, ICompact const* comp2, double tolerance, ILogger* logger = nullptr);

    virtual Iterator* begin(IVector const* step) = 0;
    virtual Iterator* end(IVector const* step)   = 0;

    virtual ICompact* clone()                                         const = 0;
    virtual IVector* getBegin()                                       const = 0;
    virtual IVector* getEnd()                                         const = 0;
    virtual ReturnCode contains(IVector const* vec, bool& result)     const = 0;
    virtual ReturnCode isSubset(ICompact const* comp, bool& result)   const = 0;
    virtual ReturnCode intersects(ICompact const* comp, bool& result) const = 0;
    virtual size_t getDim()                                           const = 0;

    ICompact() = default;
    virtual ~ICompact() = 0;

private:
    ICompact(ICompact const&)            = delete;
    ICompact& operator=(ICompact const&) = delete;
};

#endif /* ICOMPACT_H */
