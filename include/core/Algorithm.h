#ifndef CORE_ALGORITHM_H
#define CORE_ALGORITHM_H

namespace core
{
	class Algorithm
	{
	public:
		template<class T>
		static T max( const T& a, const T& b )
		{
			return ( a > b ) ? a : b;
		}
	};
}

#endif