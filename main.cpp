#include <iostream>
#include <fstream>

int main()
{

    // Image

    const int image_width = 256;
    const int image_height = 256;

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
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            out_file << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::cerr << "\r\n"
              << std::flush;
}