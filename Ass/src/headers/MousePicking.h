#include <glm/glm.hpp>

glm::vec3 get_ray_from_mouse(unsigned int WINDOW_WIDTH, 
                            unsigned int WINDOW_HEIGHT,
                            glm::mat4 projection,
                            glm::mat4 view,
                            float xpos, 
                            float ypos)
{
	float x = (2.0f * xpos) / WINDOW_WIDTH - 1.0f;
	float y = 1.0f - (2.0f - ypos) / WINDOW_HEIGHT;
	float z = 1.0f;

	glm::vec3 ray_nds = glm::vec3(x, y, z);
	glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);
	glm::vec4 ray_eye = glm::inverse(projection) * ray_clip;
	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);

	glm::vec4 tmp = glm::inverse(view) * ray_eye;
	glm::vec3 ray_wor = glm::vec3(tmp.x, tmp.y, tmp.z);
	ray_wor = glm::normalize(ray_wor);

	//std::cout << ray_wor.x << ", "
	//	<< ray_wor.y << ", "
	//	<< ray_wor.z << std::endl;

	return ray_wor;
}

bool ray_sphere(glm::vec3 ray_origin_wor,
                glm::vec3 ray_direction_wor,
                glm::vec3 sphere_centre_wor,
                float sphere_radius,
                float* intersection_distance)
{
    glm::vec3 dist_to_sphere = ray_origin_wor - sphere_centre_wor;

    float b = glm::dot(ray_direction_wor, dist_to_sphere);
    float c = glm::dot(dist_to_sphere, dist_to_sphere) - sphere_radius * sphere_radius;
    float b_squared_minus_c = b * b - c;

    // check for "imaginary" answer. == ray completely misses sphere
    if (b_squared_minus_c < 0.0f) return false;

    // check for ray hitting twice (in and out of the sphere)
    if (b_squared_minus_c > 0.0f) {
        // get the 2 intersection distances along ray
        float t_a = -b + sqrt(b_squared_minus_c);
        float t_b = -b - sqrt(b_squared_minus_c);
        *intersection_distance = t_b;
        // if behind viewer, throw one or both away
        if (t_a < 0.0) {
            if (t_b < 0.0) { return false; }
        }
        else if (t_b < 0.0) {
            *intersection_distance = t_a;
        }

        return true;
    }

    // check for ray hitting once (skimming the surface)
    if (b_squared_minus_c == 0.0f) {
        // if behind viewer, throw away
        float t = -b + sqrt(b_squared_minus_c);

        if (t < 0.0f) return false;
        *intersection_distance = t;

        return true;
    }

    // note: could also check if ray origin is inside sphere radius
    return false;
}