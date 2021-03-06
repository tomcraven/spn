#ifndef CORE_ASSERT_H
#define CORE_ASSERT_H

#define ASSERT( x )		\
	if ( !( x ) )		\
	{					\
		CORE_TRAP;		\
	}

#ifdef DEBUG
# define CORE_TRAP				\
	int* core_trap = 0;			\
	*core_trap = 0;
#else
# define CORE_TRAP 0;
#endif

#define VALIDATE_AND_RETURN( x, ret )	\
	if ( !( x ) )						\
	{									\
		CORE_TRAP;						\
		return ret;						\
	}

#define VALIDATE( x ) VALIDATE_AND_RETURN( x, false )

#define CHECK( x ) if ( !( x ) ) return false
#define CHECK_AND_RETURN( x, ret ) if ( !( x ) ) return ret

#endif
