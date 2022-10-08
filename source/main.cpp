
#include <fstream>
#include "rtweekend.h"

#include "color.h"
#include "hittable.h"
#include "sphere.h"
//include yaml
#include "yaml-cpp/yaml.h"
#include "camera.h"


class RayTracer {
public:
    RayTracer(int width, float aspect_ratio,int max_depth,int samples_per_pixel)
        : width(width),max_depth(max_depth),samples_per_pixel(samples_per_pixel){
        height = static_cast<int>((float)width / aspect_ratio);
    }

    void render(const hittable_list& world){
        std::fstream file_out("image.ppm", std::ios::out);

        camera cam;

        file_out << "P3\n" << width << ' ' << height << "\n255\n";

        for (int j = height-1; j >= 0; --j) {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < width; ++i) {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s) {
                    float u = (float)(i + random_double()) / (float)(width-1);
                    float v = (float)(j + random_double()) / (float)(height-1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color(r, world, max_depth);
                }
                write_color(file_out, pixel_color, samples_per_pixel);
            }
        }

    }

    void calculate_camera_and_viewport(
            float viewport_width,
            float viewport_height,
            float focal_length,
            point3 org
           ){
        this->origin = org;
        horizontal = glm::vec3(viewport_width, 0, 0);
        vertical = glm::vec3(0, viewport_height, 0);
        lower_left_corner = org - horizontal / 2.0f - vertical / 2.0f - glm::vec3(0, 0, focal_length);

    }

    color ray_color(const ray& r, const hittable& world,int depth) { // NOLINT(readability-convert-member-functions-to-static)
        hit_record rec = {};

        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return {0,0,0};

        if (world.hit(r, 0.001f, infinity, rec)) {
            point3 target = rec.p + random_in_hemisphere(rec.normal);
            return 0.5f * ray_color(ray(rec.p, target - rec.p), world, depth-1);
        }
        glm::vec3 unit_direction = glm::normalize(r.direction());
        auto t = 0.5*(unit_direction.y + 1.0);
        return (float)(1.0-t)*color(1.0, 1.0, 1.0) + (float)t*color(0.5, 0.7, 1.0);
    }

private:
    int width;
    int height;
    int max_depth;
    int samples_per_pixel;
    //float aspect_ratio;
    point3 origin = point3(0, 0, 0);
    glm::vec3 horizontal = glm::vec3(4, 0, 0);
    glm::vec3 vertical = glm::vec3(0, 2, 0);
    point3 lower_left_corner = point3(-2, -1, -1);
};


int main() {

    //get yaml node
    YAML::Node input = YAML::LoadFile("input.yaml");
    YAML::Node config = YAML::LoadFile("config.yaml");

    const float aspect_ratio = config["ratio"][0].as<float>() / config["ratio"][1].as<float>();
    const int image_width =  config["image_width"].as<int>();
    const int samples_per_pixel = config["samples_per_pixel"].as<int>();
    const int max_depth = config["max_depth"].as<int>();

    RayTracer tracer(image_width, aspect_ratio,max_depth,samples_per_pixel);

    // World
    hittable_list world;

    //get sphere list
    auto spheres = input["elements"];
    for(auto item : spheres) {

        //parse 3d point
        auto point = item["position"];
        auto position = point.as<std::vector<float>>();
        auto position_glm = glm::vec3(position[0], position[1], position[2]);

        //parse radius
        auto radius = item["radius"].as<float>();
        world.add(make_shared<sphere>(position_glm, radius));
    }

    //camera cam;

    // Camera and viewport
    auto viewport_height = config["camera"]["viewport_height"].as<float>();
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = config["camera"]["focal_length"].as<float>();
    auto origin = point3(
            config["camera"]["origin"][0].as<float>(),
            config["camera"]["origin"][1].as<float>(),
            config["camera"]["origin"][2].as<float>()
    );

    tracer.calculate_camera_and_viewport(viewport_width, viewport_height, focal_length, origin);

    // Render
    tracer.render(world);
}