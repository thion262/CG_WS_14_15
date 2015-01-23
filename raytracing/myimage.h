#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <sstream>

inline double clampd(double x) {
    if (x < 0.0) return 0.0;
    else if (x > 1.0) return 1.0;
    else return x;
}

inline int toInt(double x) {
    return int(pow(clampd(x),1.0/2.2)*255.0+0.5);
}

inline void saveAsPPM(int nx, int ny, Vec3* image) {
    // write out result image as ppm
    std::stringstream fileName;
    fileName << "result.ppm";
    FILE* resultFile = fopen(fileName.str().c_str(), "w");
    fprintf(resultFile, "P3\n%d %d\n%d\n", nx, ny, 255);
    for (int i=0; i<nx*ny; i++)
        fprintf(resultFile, "%d %d %d ",
                toInt(image[i].x), toInt(image[i].y), toInt(image[i].z));
}

#endif // MYIMAGE_H