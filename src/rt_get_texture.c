
#include "rt.h"
#define STB_IMAGE_IMPLEMENTATION
# include "stb_image.h"


int		*get_texture(t_rt_main *rt)
{
	int 			*texture;
	unsigned char	*tex_data;
	int 			x;
	int 			y;
	int 			bpp;

	if (!(tex_data = stbi_load("./texture.png", &rt->texture.w,
							   &rt->texture.h, &bpp, 4)))
		return (NULL);
	rt->texture.texture_size.x = rt->texture.w;
	rt->texture.texture_size.y = rt->texture.h;
	if (!(texture = (int *)ft_memalloc(sizeof(int) * rt->texture.h * rt->texture.w + 1)))
		return (NULL);
	y = -1;
	while (++y < rt->texture.h)
	{
		x = -1;
		while (++x < rt->texture.w)
			texture[x + y * rt->texture.w] = *((int *)tex_data + x + y * rt->texture.w);
	}
	return (texture);
}