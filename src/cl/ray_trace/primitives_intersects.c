int torus_intersect(float3 orig, float3 dir, __global t_object *obj, float *t0)
{
	int i;
	float3 current_position = (float3) 0;
	float distance_to_closest = 0.f;
	float2 q = (float2) 0;
	float3 vec = (float3) 0;
	float3 p = (float3) 0, n1 = (float3) 0;

	i = 0;
	int j = 1;
	while (i < 4096)
	{
		current_position = orig + (*t0) * dir;
		p = current_position - obj->center;
		n1 = dot(p, obj->vector) * obj->vector;
		vec = p - n1;
		q = (float2)(length(vec) - obj->radius, length(n1));
		if ((j == 1) && ((length(q) - obj->param) < -1e-5f))
			j = -1;
		distance_to_closest = fabs(length(q) - obj->param);
		if ((*t0) > 10000.f)
			return (0);
		if (distance_to_closest < 1e-3f)
			return (j);
		(*t0) +=
				distance_to_closest;
		i++;
	}
	return 0;
}

int hyper_intersect(float3 orig, float3 dir, __global t_object *p, float *t0)
{
	float a;
	float b;
	float c;
	float t1;
	float t2;
	float3 x;

	x = orig - p->center;
//p->vector = fast_normalize(p->vector);
	a = dot(dir, dir) - dot(dir, p->vector) * dot(dir, p->vector);
	b = 2.f * (dot(dir, x) - dot(dir, p->vector) * (dot(x, p->vector) + 2.f * p->param));
	c = dot(x, x) - dot(x, p->vector) * (dot(x, p->vector) + 4.f * p->param);
	if (
			b * b
			- 4.f *
			  a * c <
			-1e-5)
		return 0;
	if (
			fabs(b
				 * b - 4.f *
					   a * c
			) < 1e-5)
	{
		*
				t0 = -b / (a * 2.f);
		return 1;
	}
	t1 = (-b + sqrt(b * b - 4.f * a * c)) / (2.f * a);
	t2 = (-b - sqrt(b * b - 4.f * a * c)) / (2.f * a);
	*
			t0 = min(t1, t2);
	if (*t0 > 1e-3)
	{
		return 1;
	}
	*
			t0 = max(t1, t2);
	if (*t0 > 1e-5)
	{
		return 2;
	}
	return 0;
}

int sphere_intersect(float3 orig, float3 dir, __global t_object *obj, float *t0)
{
	float3 l;
	float tca;
	float d2;
	float thc;

	l = obj->center - orig;
	tca = dot(l, dir);
	d2 = dot(l, l) - tca * tca;
	if (d2 > obj->radius * s->radius)
		return (0);
	thc = sqrt(s->radius * s->radius - d2);
	*
			t0 = tca - thc;
	if (*t0 > 1e-5f)
		return (1);
	*
			t0 = tca + thc;
	if (*t0 > 1e-5f)
		return (2);
	return (0);
}

int plane_intersect(float3 orig, float3 dir, __global t_object *p, float *t0)
{
	float a = 0;

//p->vector = fast_normalize(p->vector);
	dir = fast_normalize(dir);
	a = dot(dir, p->vector);
	if (
			fabs(a)
			< 1e-6)
		return (0);
	*
			t0 = (p->param - dot(orig, p->vector)) / a;
	if ((*t0) < 0)
		return (0);
	return (1);
}

int cyl_intersect(float3 orig, float3 dir, __global t_object *p, float *t0)
{
	float b;
	float3 s;
	float3 q;
	float c;
	float d;

	s = dir - p->vector * dot(dir, p->vector);
	q = orig - p->center;
	q = q - p->vector * dot(q, p->vector);
	b = 2 * dot(s, q);
	c = dot(q, q) - p->radius * p->radius;
	d = b * b - 4 * dot(s, s) * c;
	if (
			fabs(d)
			< 1e-6)
		return (0);
	if (d < 0)
		return (0);
	*
			t0 = ((-1) * b - sqrt(d)) / (2 * dot(s, s));
	if (*t0 > 0)
		return (1);
	*
			t0 = (-b + sqrt(d)) / (2 * dot(s, s));
	if (*t0 > 0)
		return (2);
	return (0);
}

int cone_intersect(float3 orig, float3 dir, __global t_object *p, float *t0)
{
	float t1;
	float t2;
	float a;
	float b;
	float c;
	float3 s;
	float3 q;

	s = dir - p->vector * dot(dir, p->vector);
	q = orig - p->center - p->vector * dot((orig - p->center), p->vector);
	a = cos(p->param) * cos(p->param) * dot(s, s) -
		sin(p->param) * sin(p->param) * dot(dir, p->vector) * dot(dir, p->vector);
	b = 2 * cos(p->param) * cos(p->param) * dot(s, q) -
		2 * sin(p->param) * sin(p->param) * dot(dir, p->vector) * dot(orig - p->center, p->vector);
	c = cos(p->param) * cos(p->param) * dot(q, q) -
		sin(p->param) * sin(p->param) * dot(orig - p->center, p->vector) * dot(orig - p->center, p->vector);
	if (b * b - 4 * a * c < 0)
		return (0);
	t1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	t2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
	if (fabs(t1 - t2) < 1e-6)
		return (0);
	*t0 = min(t1, t2);
	if (*t0 > 0)
	{
		if (acos(fabs(dot(dir, p->vector))) > p->param)
			return (1);
		return (2);
	}
	*t0 = max(t1, t2);
	if (*t0 > 0)
	{
		if (acos(fabs(dot(dir, p->vector))) > p->param)
			return (2);
		return (1);
	}
	return (0);
}
