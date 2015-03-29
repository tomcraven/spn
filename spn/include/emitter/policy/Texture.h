#ifndef EMITTER_POLICY_TEXTURE_H
#define EMITTER_POLICY_TEXTURE_H

namespace emitter
{
	namespace policy
	{
		class Texture
		{
		public:
			virtual const char* getTexturePath() = 0;
		};

		namespace texture
		{
			class Path : public Texture
			{
			public:
				Path( const char* inPath ) : path( inPath )
				{
				}

			public:
				virtual const char* getTexturePath()
				{
					return path;
				}

			private:
				const char* path;
			};
		}
	}
}

#endif