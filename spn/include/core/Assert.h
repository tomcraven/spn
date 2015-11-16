#ifndef CORE_ASSERT_H
#define CORE_ASSERT_H

#define ASSERT( x )		\
	if ( !( x ) )		\
	{					\
		CORE_TRAP;		\
	}

#define CORE_TRAP				\
	int* core_trap = 0;			\
	*core_trap = 0;				\

#define VALIDATE_AND_RETURN( x, ret )	\
	if ( !( x ) )						\
	{									\
		CORE_TRAP;						\
		return ret;						\
	}

#define VALIDATE( x ) VALIDATE_AND_RETURN( x, false )

#define CHECK( x ) if ( !( x ) ) return false
#define CHECK_AND_RETURN( x, ret ) if ( !( x ) ) return ret

// Move this to marmalade lib
#define CHECK_S3E_RESULT( x ) if ( ( x ) != S3E_RESULT_SUCCESS ) return false

#endif