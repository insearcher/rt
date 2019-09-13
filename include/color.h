#ifndef COLOR_H
# define COLOR_H

# ifndef OPENCL___
#  define COLOR(r, g, b)	((((int)r & 0xFF) << 16) | (((int)g & 0xFF) << 8) | ((int)b & 0xFF))
#  define RED(c)			(((int)c >> 16) & 0xFF)
#  define GREEN(c)			(((int)c >> 8) & 0xFF)
#  define BLUE(c)			((int)c & 0xFF)
# else
#  define COLOR(r, g, b)	bit_insert(bit_insert((int)r, 8, 0, (int)g, 0, 0), 0, 8, (int)b, 0, 0)
#  define RED(c)			bit_extract((int)c, 16, 0xFF)
#  define GREEN(c)			bit_extract((int)c, 8, 0xFF)
#  define BLUE(c)			bit_extract((int)c, 0, 0xFF)
# endif

#endif
