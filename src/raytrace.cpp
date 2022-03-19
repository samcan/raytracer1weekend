#include <iostream>
#include "color.h"
#include "vec3.h"

using namespace std;

inline void update_render_status(int scanline);

int main() {
    // we'll start out by creating just a simple PPM test file. We'll output
    // the PPM data to the standard console (cout), which can then be redirected
    // to a file for saving as a PPM

    // image size (in pixels)
    const int IMAGE_WIDTH = 256;
    const int IMAGE_HEIGHT = 256;

    // output test image
    // PPM header
    cout << "P3" << endl << IMAGE_WIDTH << " " << IMAGE_HEIGHT << endl << "255" << endl;
    
    // PPM image data
    // each row is a RGB pixel with space chars in between each part of the color
    //
    // in Peter Shirley's book, for this test image:
    //  - He has red go from 0 (off) on the left and 1 (on) on the right
    //  - Green goes from 0 at the bottom to 1 at the top
    //  - Blue is constant at 0.25
    double red;
    double green;
    double blue = 0.25;
    
    for (int y=IMAGE_HEIGHT-1; y>=0; y--) {
        for (int x=0; x<IMAGE_WIDTH; x++) {
            // add progress indicator to standard error (cerr)
            //  OK that's a pretty cool trick from the book. By putting a \r
            //  in front of the text, it's keeping it all on one line and
            //  constantly updating the progress in the same spot.
            update_render_status(y);

            red = static_cast<double>(x)/IMAGE_WIDTH;
            green = static_cast<double>(y)/IMAGE_HEIGHT;

            color c = color(red, green, blue);
            write_color(cout, c);
        }
    }
}

inline void update_render_status(int scanline) {
    cerr << "\rScanlines remaining: " << scanline << ' ' << std::flush;   
}