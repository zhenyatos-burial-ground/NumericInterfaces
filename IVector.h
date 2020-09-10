#ifndef IVECTOR_H
#define IVECTOR_H

#include "../../Logger/include/ILogger.h"
#include "../../Util/ReturnCode.h"
#include "../../Util/Export.h"
#include <cstddef> // size_t

class DECLSPEC IVector {
public:
	enum class Norm {
		NORM_1,
		NORM_2,
		NORM_INF
	};

	static IVector* createVector(size_t dim, double* data, ILogger* logger = nullptr);
	static IVector* add(IVector const* addend1, IVector const* addend2, ILogger* logger = nullptr);
	static IVector* sub(IVector const* minuend, IVector const* subtrahend, ILogger* logger = nullptr);
	static IVector* mul(IVector const* multiplier, double scale, ILogger* logger = nullptr);
	static double mul(IVector const* multiplier1, IVector const* multiplier2, ILogger* logger = nullptr);
	static ReturnCode equals(IVector const* v1, IVector const* v2, Norm norm, double tolerance, bool& result, ILogger* logger = nullptr);

	virtual IVector* clone()                                const = 0;
	virtual ReturnCode setCoord(size_t index, double value) const = 0;
	virtual double getCoord(size_t index)                   const = 0;
	virtual double norm(Norm norm)                          const = 0;
	virtual size_t getDim()                                 const = 0;

	IVector() = default;
	virtual ~IVector() = 0;

private:
	IVector(IVector const&)			   = delete;
	IVector& operator=(IVector const&) = delete;
};

#endif /* IVECTOR_H */
