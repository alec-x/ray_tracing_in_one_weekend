#include <iostream>
#include <fstream>
#include "color.h"
#include "vec3.h"
#include "ray.h"

color ray_colour(const ray &r)
{
    vec3 unit_dir = unit_vector(r.direction());
    auto t = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); // TODO: figure out
}

int main()
{

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horz = vec3(viewport_width, 0, 0);
    auto vert = vec3(0, viewport_height, 0);
    auto bot_left = origin - horz / 2 - vert / 2 - vec3(0, 0, focal_length);

    // Render
    std::string out_path = "./image.ppm";
    std::ofstream out_file;
    out_file.open(out_path);

    out_file << "P3\n"
             << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "Scanlines remaining: " << j << ' ' << "\r" << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray r(origin, bot_left + u * horz + v * vert - origin);
            color pixel_color = ray_colour(r);
            write_color(out_file, pixel_color);
        }
    }
    std::cerr << "\r\n"
              << std::flush;
}