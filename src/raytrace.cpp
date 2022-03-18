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

    for (int x=0; x<IMAGE_WIDTH; x++) {
        for (int y=0; y<IMAGE_HEIGHT; y++) {
            cout << "128 128 128" << endl;
        }
    }
}