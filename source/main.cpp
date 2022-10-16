
#include <fstream>
#include <chrono>
#include "utils.h"

#include "color.h"
#include "hittable.h"
#include "sphere.h"
//include yaml
#include "yaml-cpp/yaml.h"
#include "camera.h"
#include "box.h"
#include "aarect.h"

hittable_list loadSceneFromFile(const std::string& filename) {
    YAML::Node config = YAML::LoadFile(filename + ".yaml");

    hittable_list objects;

    for (auto object : config["objects"]) {
        auto type = object["type"].as<std::string>();

        if(type == "sphere") {
            auto center_v = object["center"].as<std::vector<float>>();
            auto radius = object["radius"].as<float>();
            objects.add(std::make_shared<sphere>(point3(center_v[0], center_v[1], center_v[2]), radius));
        } else if(type == "box") {
            auto size = object["size"].as<std::vector<float>>();
            objects.add(std::make_shared<box>(point3(0, 0, 0), point3(size[0], size[1], size[2])));
        } else if(type == "xy_rect") {
            auto size = object["size"].as<std::vector<float>>();
            objects.add(std::make_shared<xy_rect>(size[0], size[1], size[2], size[3], size[4]));
        } else if(type == "xz_rect") {
            auto size = object["size"].as<std::vector<float>>();
            objects.add(std::make_shared<xz_rect>(size[0], size[1], size[2], size[3], size[4]));
        } else if(type == "yz_rect") {
            auto size = object["size"].as<std::vector<float>>();
            objects.add(std::make_shared<yz_rect>(size[0], size[1], size[2], size[3], size[4]));
        } else {
            throw std::runtime_error("Unknown object type");
        }
    }

    return objects;
}


class RayTracer {
public:
    RayTracer(int width, float aspect_ratio,int samples_per_pixel)
        : width(width),samples_per_pixel(samples_per_pixel){
        height = static_cast<int>((float)width / aspect_ratio);
    }

    void render(
            const hittable_list& world,
            std::string fileName,
            std::chrono::steady_clock::time_point begin) {
        std::fstream file_out(fileName + ".ppm", std::ios::out);

        camera cam(
                origin,
                look_at,
                glm::vec3(0, 1, 0),
                40,
                (float)width / (float)height,
                2.0,
                glm::length(look_at - origin)
        );

        file_out << "P3\n" << width << ' ' << height << "\n255\n";

        for (int j = height-1; j >= 0; --j) {
            auto current_time = std::chrono::steady_clock::now();
            std::string time = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(current_time - begin).count() / 1000.0f).substr(0, 5);
            auto percentage = std::to_string(100 -(float)j/(float)height *100.0f).substr(0, 4);

            std::cerr << "\rScanlines remaining: " << j << ' ' <<  percentage << "%  Time elapsed: " << time << "s" << std::flush;
            for (int i = 0; i < width; ++i) {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s) {
                    float u = (float)(i + random_double()) / (float)(width-1);
                    float v = (float)(j + random_double()) / (float)(height-1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color(r, world);
                }
                write_color(file_out, pixel_color, samples_per_pixel);
            }
        }

    }

    void calculate_camera_and_viewport(float viewport_width, float viewport_height, float focal_length, point3 org,
                                       point3 look_at_) {
        this->origin = org;
        horizontal = glm::vec3(viewport_width, 0, 0);
        vertical = glm::vec3(0, viewport_height, 0);
        lower_left_corner = org - horizontal / 2.0f - vertical / 2.0f - glm::vec3(0, 0, focal_length);
        this->look_at = look_at_;

    }

    color ray_color(const ray& r, const hittable& world) { // NOLINT(readability-convert-member-functions-to-static)
        hit_record rec = {};


        if (world.hit(r, 0.001f, infinity, rec)) {
//            point3 target = rec.p + random_in_hemisphere(rec.normal);
            return 0.5f * (rec.normal + color(1,1,1));
        }
        glm::vec3 unit_direction = glm::normalize(r.direction());
        auto t = 0.5*(unit_direction.y + 1.0);
        return (float)(1.0-t)*color(1.0, 1.0, 1.0) + (float)t*color(0.5, 0.7, 1.0);
    }

private:
    int width;
    int height;
    int samples_per_pixel;
    //float aspect_ratio;
    point3 origin = point3(0, 0, 0);
    glm::vec3 horizontal = glm::vec3(4, 0, 0);
    glm::vec3 vertical = glm::vec3(0, 2, 0);
    point3 lower_left_corner = point3(-2, -1, -1);
    point3 look_at;
};


int main() {

    //get yaml node
    YAML::Node input = YAML::LoadFile("input.yaml");
    YAML::Node config = YAML::LoadFile("config.yaml");

    const float aspect_ratio = config["ratio"][0].as<float>() / config["ratio"][1].as<float>();
    const int image_width =  config["image_width"].as<int>();
    const int samples_per_pixel = config["samples_per_pixel"].as<int>();

    RayTracer tracer(image_width, aspect_ratio,samples_per_pixel);

    auto fileName = config["scene"].as<std::string>();
    // World
    hittable_list world = loadSceneFromFile(fileName);


    // Camera and viewport
    auto viewport_height = config["camera"]["viewport_height"].as<float>();
    auto origin = point3(
            config["camera"]["origin"][0].as<float>(),
            config["camera"]["origin"][1].as<float>(),
            config["camera"]["origin"][2].as<float>()
    );

    auto look_at = point3(
            config["camera"]["look_at"][0].as<float>(),
            config["camera"]["look_at"][1].as<float>(),
            config["camera"]["look_at"][2].as<float>()
    );

    tracer.calculate_camera_and_viewport(
            aspect_ratio * viewport_height,
            viewport_height,
            config["camera"]["focal_length"].as<float>(),
            origin,
            look_at);

    std::cout << "Rendering..." << std::endl;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // Render
    tracer.render(world, fileName, begin);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::string time = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0f).substr(0, 5);

    std::cout << "\nTime elapsed: " << time << "s" << std::endl;

    std::string newFileName = fileName + "_s" + std::to_string(samples_per_pixel) + ".png";
    std::string newZoomFileName = fileName + "_s" + std::to_string(samples_per_pixel) + "_zoom.png";

    //run command
    std::string command = std::string("convert -pointsize 20 -fill '#000A' -draw 'rectangle 0,0,150,140' -fill yellow -weight 500 -draw '") +
                          "text 20,40 \"" + fileName + "\" " +
                          "text 20,65 \"Samples: " +
                          std::to_string(samples_per_pixel) + "\" " +
                          "text 20,90 \"Size: " +
                            std::to_string(image_width) + "x" +
                            std::to_string((int)(image_width / aspect_ratio)) + "\" " +
                          "text 20,115 \"Time: " +
                          time + "s\" " +
                          "' " + fileName + ".ppm " + newFileName;

    std::string zoomed = std::string("convert ") + newFileName + " -crop 100x100+240+350 -resize 600x600 " + newZoomFileName;

    std::string command_append = std::string("convert ") + newFileName + " " + newZoomFileName + " +append " + newFileName;

    std::string command_del = std::string("rm ") + fileName + ".ppm " + newZoomFileName;





    std::cout << "\nRunning command: " << command << std::endl;



    system(command.c_str());
    system(zoomed.c_str());
    system(command_append.c_str());
    system(command_del.c_str());
}