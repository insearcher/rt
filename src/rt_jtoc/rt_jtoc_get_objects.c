#include "rt.h"
#include "rt_jtoc.h"
#include "rt_raycast.h"

int 		rt_jtoc_compare_str_with_texture_name(t_obj_texture *texture, char *str)
{
	int i;
	int cache_counter;

	i = -1;
	cache_counter = texture->textures_count;
	while (++i < cache_counter)
		if ((ft_strstr(texture->textures_path[i], str)))
			return (i);
	return (-2);
}
int 		rt_jtoc_get_object_texture(t_object *obj, t_obj_texture *texture, t_jnode *n)
{
	t_jnode	*tmp;
	int 	id;
	char 	*str;

	if (!(tmp = jtoc_node_get_by_path(n, "texture"))
		|| tmp->type != string)
		return (rt_jtoc_sdl_log_error("TEXTURE ERROR OR TEXTURE IS MISSING", -1));
	str = jtoc_get_string(tmp);
	if (!(ft_strcmp(str, "none")))
		id = -1;
	else
		id = rt_jtoc_compare_str_with_texture_name(texture, str);
	if (id == -2)
		return (rt_jtoc_sdl_log_error("TEXTURE NAME ERROR OR TEXTURE NAME IS MISSING", -1));
	obj->material.texture_id = id;
	return (FUNCTION_SUCCESS);
}

int	rt_jtoc_get_object_type(t_object *obj, t_jnode *n)
{
	char	*str;
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "type")) || tmp->type != string)
		return (rt_jtoc_sdl_log_error("TYPE ERROR OR TYPE IS MISSING", -1));
	str = jtoc_get_string(tmp);
	obj->type = 0;
	obj->type = ft_strcmp(str, "sphere") ? obj->type : o_sphere;
	obj->type = ft_strcmp(str, "box") ? obj->type : o_box;
	obj->type = ft_strcmp(str, "round_box") ? obj->type : o_round_box;
	obj->type = ft_strcmp(str, "torus") ? obj->type : o_torus;
	obj->type = ft_strcmp(str, "capped_torus") ? obj->type : o_capped_torus;
	obj->type = ft_strcmp(str, "link") ? obj->type : o_link;
	obj->type = ft_strcmp(str, "cylinder") ? obj->type : o_cylinder;
	obj->type = ft_strcmp(str, "cone") ? obj->type : o_cone;
	obj->type = ft_strcmp(str, "plane") ? obj->type : o_plane;
	obj->type = ft_strcmp(str, "octahedron") ? obj->type : o_octahedron;
	obj->type = ft_strcmp(str, "mandelbulb") ? obj->type : o_mandelbulb;
	obj->type = ft_strcmp(str, "mandelbox") ? obj->type : o_mandelbox;
	obj->type = ft_strcmp(str, "menger_sponge") ? obj->type : o_menger_sponge;
	if (obj->type == 0)
		return (FUNCTION_FAILURE);
	return (FUNCTION_SUCCESS);
}

int	rt_jtoc_get_object_layer(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;
	char	*str;


	if (!(tmp = jtoc_node_get_by_path(n, "layer")) || tmp->type != string)
		return (rt_jtoc_sdl_log_error("LAYER ERROR OR LAYER IS MISSING", -1));
	str = jtoc_get_string(tmp);
	obj->layer = 0;
	obj->layer |= ft_strcmp(str, "default_layer") ? DEFAULT_LAYER : obj->layer;
	obj->layer |= ft_strcmp(str, "ignore_raycast_layer") ? IGNORE_RAYCAST_LAYER : obj->layer;
	if (obj->layer == 0)
		obj->layer = DEFAULT_LAYER;
	return (FUNCTION_SUCCESS);
}

int	rt_jtoc_check_and_get_id_for_object(t_scene *scene, t_jnode *n, t_object *object)
{
	t_jnode		*tmp;
	cl_uint		id;

	if (!(tmp = jtoc_node_get_by_path(n, "id")) || tmp->type != integer)
		return (rt_jtoc_sdl_log_error("ID ERROR", -1));
		id = jtoc_get_int(tmp);
		if (id <= 0)
			return (FUNCTION_FAILURE);
		if (scene->camera.transform.id == (cl_uint)id)
			return (rt_jtoc_sdl_log_error("THAT ID ALREADY EXISTS IN CAMERA", id));
		if (rt_find_light_by_id(scene->lights, id))
			return (rt_jtoc_sdl_log_error("THAT ID ALREADY EXISTS IN LIGHTS", id));
		if (rt_find_object_by_id(scene->objects, id))
			return (rt_jtoc_sdl_log_error("THAT ID ALREADY EXISTS IN OBJECTS", id));
	object->transform.id = id;
	return (FUNCTION_SUCCESS);
}

int rt_jtoc_get_type_name(int type, int id, char *str)
{
	char *tmp_id;
	char tmp_str[15];

	ft_bzero(tmp_str, 15);
	tmp_id = ft_itoa(id);
	if (type == o_sphere)
		ft_strcat(ft_strcat(str,"Sphere"), tmp_id);
	else if (type == o_box)
		ft_strcat(ft_strcat(str,"Box"), tmp_id);
	else if (type == o_round_box)
		ft_strcat(ft_strcat(str,"Round Box"), tmp_id);
	else if (type == o_torus)
		ft_strcat(ft_strcat(str,"Torus"), tmp_id);
	else if (type == o_capped_torus)
		ft_strcat(ft_strcat(str,"Capped Torus"), tmp_id);
	else if (type == o_link)
		ft_strcat(ft_strcat(str,"Link"), tmp_id);
	else if (type == o_cylinder)
		ft_strcat(ft_strcat(str,"Cylinder"), tmp_id);
	else if (type == o_cone)
		ft_strcat(ft_strcat(str,"Cone"), tmp_id);
	else if (type == o_plane)
		ft_strcat(ft_strcat(str,"Plane"), tmp_id);
	else if (type == o_octahedron)
		ft_strcat(ft_strcat(str, "Octahedron"), tmp_id);
	else if (type == o_mandelbulb)
		ft_strcat(ft_strcat(str,"Mandelbulb"), tmp_id);
	else if (type == o_mandelbox)
		ft_strcat(ft_strcat(str,"Mandelbox"), tmp_id);
	else if (type == o_menger_sponge)
		ft_strcat(ft_strcat(str,"Menger Sponge"), tmp_id);
	free(tmp_id);
	return (FUNCTION_SUCCESS);
}

//int rt_jtoc_get_type_name(int type, int id, char *str) юзать если объявлять str на стеке
//{
//	char *tmp_id;
//	char tmp_str[30];
//
//	ft_bzero(tmp_str, 30);
//	tmp_id = ft_itoa(id);
//	if (type == o_sphere)
//		ft_strcat(str, ft_strcat(ft_strcat(tmp_str,"Sphere"), tmp_id));
//	else if (type == o_box)
//		ft_strcat(str, ft_strcat(ft_strcat(tmp_str,"Box"), tmp_id));
//	else if (type == o_round_box)
//		ft_strcat(str, ft_strcat(ft_strcat(tmp_str,"Round Box"), tmp_id));
//	else if (type == o_torus)
//		ft_strcat(str, ft_strcat(ft_strcat(tmp_str,"Torus"), tmp_id));
//	else if (type == o_capped_torus)
//		ft_strcat(str, ft_strcat(ft_strcat(tmp_str,"Capped Torus"), tmp_id));
//	else if (type == o_link)
//		ft_strcat(str, ft_strcat(ft_strcat(tmp_str,"Link"), tmp_id));
//	else if (type == o_cylinder)
//		ft_strcat(str, ft_strcat(ft_strcat(tmp_str,"Cylinder"), tmp_id));
//	else if (type == o_cone)
//		ft_strcat(str, ft_strcat(ft_strcat(tmp_str,"Cone"), tmp_id));
//	else if (type == o_plane)
//		ft_strcat(str, ft_strcat(ft_strcat(tmp_str,"Plane"), tmp_id));
//	else if (type == o_mandelbulb)
//		ft_strcat(str, ft_strcat(ft_strcat(tmp_str,"Mandelbulb"), tmp_id));
//	else if (type == o_mandelbox)
//		ft_strcat(str, ft_strcat(ft_strcat(tmp_str,"Mandelbox"), tmp_id));
//	free(tmp_id);
//	return (FUNCTION_SUCCESS);
//}


int	rt_jtoc_compare_name(t_object *obj, int i, char str[1000][15], int name)
{
	int		tmp;
	tmp = i;
	while (tmp > 0)
	{
		if (ft_strcmp(obj->local_name, str[tmp - 1]) == 0)
			break;
		else
			tmp--;
	}
	if (tmp == 0)
		return (FUNCTION_SUCCESS);
	else
	{
		ft_bzero(str[i], 15);
		rt_jtoc_get_type_name(obj->type, name, str[i]);
		obj->local_name = str[i];
		name++;
		rt_jtoc_compare_name(obj, i, str, name);
	}
	return (FUNCTION_SUCCESS);
}

int rt_jtoc_get_object_name(t_object *obj, t_jnode *n)
{
	t_jnode		*tmp;
	char		*str;
	int			name;
	static int	i = 0;
	static char tmp_str[1000][15];

	if (!(str = (char *)ft_x_memalloc(sizeof(char) * 16)))
		return (FUNCTION_FAILURE);
	name = 0;
	if ((tmp = jtoc_node_get_by_path(n, "name")) && tmp->type == string)
	{
		ft_strncpy(str, jtoc_get_string(tmp), 15);
		obj->local_name = str;
	}
	else
	{
		rt_jtoc_get_type_name(obj->type, name, str);
		obj->local_name = str;
	}
	ft_strcpy(tmp_str[i], str);
	rt_jtoc_compare_name(obj, i, tmp_str, name);

	obj->local_name = tmp_str[i];
	i++;
	free(str);
	return (FUNCTION_SUCCESS);
}

int rt_jtoc_get_object(t_object *obj, t_jnode *n, t_scene *scene, t_obj_texture *texture)
{
	t_jnode	*tmp;
	int		err;

	ft_bzero(obj, sizeof(t_object));
	if (rt_jtoc_get_object_type(obj, n))
		return (rt_jtoc_sdl_log_error("NOT VALID TYPE", -1));
	if (rt_jtoc_get_object_layer(obj, n))
		return (rt_jtoc_sdl_log_error("NOT VALID LAYER", -1));
	if (rt_jtoc_get_object_texture(obj, texture , n))
		return(rt_jtoc_sdl_log_error("NOT VALID TEXTURE", -1));
	if (rt_jtoc_get_transform(&obj->transform, n))
		return (rt_jtoc_sdl_log_error("TRANSFORM ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "color")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("COLOR TYPE ERROR OR COLOR IS MISSING", -1));
	if (rt_jtoc_get_float4(&obj->material.color, tmp))
		return (rt_jtoc_sdl_log_error("COLOR ERROR", -1));
	if (rt_jtoc_check_and_get_id_for_object(scene, n, obj))
		return (rt_jtoc_sdl_log_error("ID ERROR", -1));
	rt_jtoc_get_object_name(obj, n);

	err = 0;
	err = obj->type == o_sphere ? rt_jtoc_get_sphere(obj, n) : err;
	err = obj->type == o_box ? rt_jtoc_get_box(obj, n) : err;
	err = obj->type == o_round_box ? rt_jtoc_get_round_box(obj, n) : err;
	err = obj->type == o_torus ? rt_jtoc_get_torus(obj, n) : err;
	err = obj->type == o_plane ? rt_jtoc_get_plane(obj, n) : err;
	err = obj->type == o_cone ? rt_jtoc_get_cone(obj, n) : err;
	err = obj->type == o_cylinder ? rt_jtoc_get_cylinder(obj, n) : err;
	err = obj->type == o_link ? rt_jtoc_get_link(obj, n) : err;
	err = obj->type == o_octahedron ? rt_jtoc_get_octahedron(obj, n) : err;
	err = obj->type == o_mandelbulb ? rt_jtoc_get_mandelbulb(obj, n) : err;
	err = obj->type == o_mandelbox ? rt_jtoc_get_mandelbox(obj, n) : err;
	err = obj->type == o_menger_sponge ? rt_jtoc_get_menger_sponge(obj, n) : err;
	if (err != 0)
		return (FUNCTION_FAILURE);

	return (FUNCTION_SUCCESS);
}

int rt_jtoc_get_objects(t_scene *scene, t_jnode *n, t_obj_texture *texture)
{
	t_jnode		*tmp;
	t_object	obj;
	uint		c;
	int			i;

	c = 0;
	if (rt_jtoc_get_objects_num_in_arr(&c, n) ||
		!(scene->objects = vec_init(c, sizeof(t_object))))
		return (FUNCTION_FAILURE);
	if (c >= 1000)
		return (rt_jtoc_sdl_log_error("OBJECT OVER 1000", -1));
	tmp = n->down;
	i = 0;
	while (tmp)
	{
		if (tmp->type != object)
			return (rt_jtoc_sdl_log_error("OBJECT TYPE ERROR", i));
		if (rt_jtoc_get_object(&obj, tmp, scene, texture))
			return (rt_jtoc_sdl_log_error("OBJECT DATA ERROR", i));
		vec_push_back(scene->objects, &obj);
		SDL_Log("%s", obj.local_name);
		i++;
		tmp = tmp->right;
	}
	return (FUNCTION_SUCCESS);
}
