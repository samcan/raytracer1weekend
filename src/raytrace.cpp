#include <iostream>
#include "color.h"
#include "vec3.h"
#include "ray.h"

color ray_color(const ray& r);
inline void update_render_status(int scanline);
double hit_sphere(const point3& center, double radius, const ray& r);

int main() {
    // we'll start out by creating just a simple PPM test file. We'll output
    // the PPM data to the standard console (cout), which can then be redirected
    // to a file for saving as a PPM

    // image size (in pixels)
    const auto ASPECT_RATIO = 16.0 / 9.0;
    const int IMAGE_WIDTH = 400;
    const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);

    // camera settings
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * ASPECT_RATIO;
    // distance between camera origin and viewport
    auto focal_length = 1.0;

    // camera origin location
    auto origin = point3(0, 0, 0);
    auto vp_horizontal = vec3(viewport_width, 0, 0);
    auto vp_vertical = vec3(0, viewport_height, 0);
    auto vp_lower_left_corner = origin - vp_horizontal/2 - vp_vertical/2
                - vec3(0, 0, focal_length);
    // in the previous line of code, we're locating the lower left corner of the
    // viewport relative to the camera origin. We can use vector subtraction to
    // locate the viewpoint's lower left corner:
    //      - start at camera origin
    //      - subtract half of the viewpoint's horizontal size to get the left
    //      - subtract half of the viewpoint's vertical size to get the bottom
    //      - subtract the focal length to get the zed
    // (viewport is -zed relative to camera) 

    // output test image
    // PPM header
    std::cout << "P3" << std::endl;
    std::cout << IMAGE_WIDTH << " " << IMAGE_HEIGHT << std::endl;
    std::cout << "255" << std::endl;
    
    // PPM image data
    // each row of PPM file is a RGB pixel with space chars in between each part
    // of the color  
    for (int y=IMAGE_HEIGHT-1; y>=0; --y) {
        // add progress indicator to standard error (cerr)
        //  OK that's a pretty cool trick from the book. By putting a \r
        //  in front of the text, it's keeping it all on one line and
        //  constantly updating the progress in the same spot.
        update_render_status(y);
        for (int x=0; x<IMAGE_WIDTH; x++) {
            auto u = static_cast<double>(x) / (IMAGE_WIDTH-1);
            auto v = static_cast<double>(y) / (IMAGE_HEIGHT-1);
            // TODO not sure why we need to subtract origin in the next line for
            // the vector?
            ray r(origin, vp_lower_left_corner + u*vp_horizontal + v*vp_vertical - origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
}

inline void update_render_status(int scanline) {
    std::cerr << "\rScanlines remaining: " << scanline << ' ' << std::flush;   
}

color ray_color(const ray& r) {
    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }

    // get unit vector with same direction as ray r
    vec3 unit_direction = unit_vector(r.direction());
    // this constrains the y value into the range 0.0 <= t <= 1.0
    t = 0.5*(unit_direction.y() + 1.0);

    // linear blend of white at t=0.0 and blue at t=1.0
    // formula:
    //      blend_value = (1-t)*startValue + (t)*endValue
    //
    // notes from experimentation:
    //  - I thought that changing the 1 to a diff value would adjust the
    //  horizontal location of the gradient, but it didn't?
    color start_color(1.0, 1.0, 1.0);
    color end_color(0.5, 0.7, 1.0);
    return (1-t)*start_color + t*end_color;
}

double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - pow(radius, 2);
    auto discriminant = pow(b, 2) - 4*a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant)) / (2.0*a);
    }
}