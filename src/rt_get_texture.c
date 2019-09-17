
#include "rt.h"
#define STB_IMAGE_IMPLEMENTATION
# include "stb_image.h"


void 	find_textures_size(t_rt_main *rt, int number_of_texture)
{
	char			*texture[number_of_texture];
	unsigned char	*tex_data;
	int 			bpp;
	int 			texture_w;
	int 			texture_h;
	int				i;

	i = -1;
	texture[0] = "./textures/test.jpg";
	texture[1] = "./textures/texture.png";
	texture[2] = "./textures/brick.jpg";
	texture[3] = "./textures/marble.png";
	while (++i < number_of_texture)
	{
		if (!(tex_data = stbi_load(texture[i], &texture_w,
								   &texture_h, &bpp, 4)))
			return ;
		rt->texture.texture_size += (texture_w * texture_h);
		free(tex_data);
	}
}

void		get_texture(t_rt_main *rt, char *texturename, int number_of_texture)
{
	char 			*texture[number_of_texture];
	unsigned char	*tex_data;
	int 			x;
	int 			y;
	int 			bpp;
	int 			i;

	texture[0] = texturename;
	texture[1] = "./textures/texture.png";
	texture[2] = "./textures/brick.jpg";
	texture[3] = "./textures/marble.png";
	i = -1;
	while (++i < number_of_texture)
	{
		if (!(tex_data = stbi_load(texture[i], &rt->texture.w,
								   &rt->texture.h, &bpp, 4)))
			return;
		y = -1;
		while (++y < rt->texture.h)
		{
			x = -1;
			while (++x < rt->texture.w)
				rt->texture.texture[(x + i * 1024) + (y + i * 1023) * (rt->texture.w)] =
						*((int *) tex_data + x + y * rt->texture.w);
		}
		free(tex_data);
	}
}