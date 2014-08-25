#ifndef CORE_ASSERT_H
#define CORE_ASSERT_H

#define CHECK( x ) if ( !( x ) ) return false
#define CHECK_AND_RETURN( x, ret ) if ( !( x ) ) return ret
#define CHECK_S3E_RESULT( x ) if ( ( x ) != S3E_RESULT_SUCCESS ) return false

#endif