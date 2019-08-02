#ifndef COLOR_H
# define COLOR_H

# define COLOR(r, g, b)	((((int)r & 0xFF) << 16) | (((int)g & 0xFF) << 8) | ((int)b & 0xFF))

# define RED(c)			(((int)c >> 16) & 0xFF)
# define GREEN(c)		(((int)c >> 8) & 0xFF)
# define BLUE(c)		((int)c & 0xFF)

#endif
