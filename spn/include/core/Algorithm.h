#ifndef CORE_ALGORITHM_H
#define CORE_ALGORITHM_H

namespace core
{
	namespace algorithm
	{
		template< class T >
		T max( const T& a, const T& b )
		{
			return ( a > b ) ? a : b;
		}

		template< class T >
		T min( const T& a, const T& b )
		{
			return ( a < b ) ? a : b;
		}

		template< class T >
		T clamp( const T& val, const T& low, const T& high )
		{
			return min( high, max( low, val ) );
		}
	};
}

#endif