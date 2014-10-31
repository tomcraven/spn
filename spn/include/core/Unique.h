#ifndef CORE_UNIQUE_H
#define CORE_UNIQUE_H

#define ___UNIQUE_NAME( a, b ) a##b
#define __UNIQUE_NAME( a, b ) ___UNIQUE_NAME( a, b )
#define UNIQUE_NAME( a ) __UNIQUE_NAME( a, __LINE__ )

#endif