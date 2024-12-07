#include <gp_Pnt.hxx>
#include <iostream>

int main() {
    // Create a 3D point using OCC
    gp_Pnt point(10.0, 20.0, 30.0);

    // Print the coordinates of the point
    std::cout << "Point coordinates: (" 
              << point.X() << ", " 
              << point.Y() << ", " 
              << point.Z() << ")" << std::endl;

    return 0;
}
