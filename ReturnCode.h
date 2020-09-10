#ifndef RETURN_CODE_H
#define RETURN_CODE_H

enum class ReturnCode {
    RC_SUCCESS        = 0,
    RC_NO_MEM         = 1,
    RC_NULL_PTR       = 2,
    RC_ZERO_DIM       = 3,
    RC_WRONG_DIM      = 4,
    RC_NAN            = 5,
    RC_OUT_OF_BOUNDS  = 6,
    RC_OPEN_FILE      = 7,
    RC_ELEM_NOT_FOUND = 8,
    RC_INVALID_PARAMS = 9,
    RC_INIT_REQUIRED  = 10,
    RC_UNKNOWN        = 11
};

#endif /* RETURN_CODE_H */
