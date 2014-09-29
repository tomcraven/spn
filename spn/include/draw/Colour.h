#ifndef DRAW_COLOUR_H
#define DRAW_COLOUR_H

namespace draw
{
	namespace colour
	{
		const uint32_t kDefault = 0xFFFFFFFF;

		const uint32_t kLightBlue = 0xFFF8DEAF;
		
		uint32_t colourFromRGBA( uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF )
		{
			return ( ( uint32_t )r ) |
                ( ( uint32_t )g << 8 ) |
                ( ( uint32_t )b << 16) |
                ( ( uint32_t )a << 24 );
		}

		void rgbaFromColour( uint32_t colour, uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& a )
		{
			r = colour & 0xFF;
			g = ( colour >> 8 ) & 0xFF;
			b = ( colour >> 16 ) & 0xFF;
			a = ( colour >> 24 ) & 0xFF;
		}
	}
}

#endif