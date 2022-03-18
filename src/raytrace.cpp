#include <iostream>

using namespace std;

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
    float red;
    float green;
    float blue = 0.25;

    int red_int;
    int green_int;
    int blue_int = blue * 256;
    
    for (int y=IMAGE_HEIGHT-1; y>=0; y--) {
        for (int x=0; x<IMAGE_WIDTH; x++) {
            red = static_cast<float>(x)/IMAGE_WIDTH * 256;
            green = static_cast<float>(y)/IMAGE_HEIGHT * 256;
            
            red_int = static_cast<int>(red);
            green_int = static_cast<int>(green);

            cout << red_int << " ";
            cout << green_int << " ";
            cout << blue_int << endl;
        }
    }
}