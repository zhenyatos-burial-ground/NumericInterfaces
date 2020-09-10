#ifndef EXPORT_H
#define EXPORT_H

/* Generic helper definitions for shared library support */
#if defined _WIN32 || defined __CYGWIN__
    #define DLL_IMPORT __declspec(dllimport)
    #define DLL_EXPORT __declspec(dllexport)
    #define DLL_LOCAL_VISIBILITY
#else
    #if __GNUC__ >= 4
        #define DLL_IMPORT __attribute__ ((visibility ("default")))
        #define DLL_EXPORT __attribute__ ((visibility ("default")))
        #define DLL_LOCAL_VISIBILITY  __attribute__ ((visibility ("hidden")))
    #else
        #define DLL_IMPORT
        #define DLL_EXPORT
        #define DLL_LOCAL_VISIBILITY
    #endif
#endif

#ifdef BUILD_AS_STATIC
    #define DECLSPEC
#else
    #ifndef DECLSPEC
        #ifdef LIB_IMPORT
            /* Use this library */
            #define DECLSPEC DLL_IMPORT
        #else
            /* Build this library */
            #define DECLSPEC DLL_EXPORT
        #endif
    #endif
#endif

#endif /* EXPORT_H */
