// Read rectangles and circles from Shapes.txt
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int main()
{
    std::ifstream infile("config.txt");

    // Temporary buffer
    std::string strTemp;

    if (!infile.is_open())
    {
        std::cerr << "Could not open file...\n";
        return -1;
    }

    // Get the input from the input file until EOF
    while (std::getline(infile, strTemp))
    {
        if (strTemp.empty() || strTemp.size() == 1)
        {
            // Empty line, or 1 character. Skip.
            continue;
        }

        if (strTemp[0] == '/' && strTemp[1] == '/')
        {
            // Comment. Skip.
            continue;
        }

        // Transform string to a stream
        std::stringstream lineStream(strTemp);

        std::string strShape, strName;
        int x, y, width, height, radius;

        lineStream >> strShape;

        // Is it a rectangle?
        if (strShape == "Rectangle")
        {
            // Rectangle | Name | x | y | width | height
            lineStream >> strName;
            lineStream >> x;
            lineStream >> y;
            lineStream >> width;
            lineStream >> height;

            std::cout << "Rectangle " << strName
                      << ", x = " << x
                      << ", y = " << y
                      << ", width = " << width
                      << ", height = " << height
                      << "\n";
        }

        // Is it a circle?
        if (strShape == "Circle")
        {
            // Circle | Name | x | y | radius
            lineStream >> strName >> x >> y >> radius;

            std::cout << "Circle " << strName
                      << ", x = " << x
                      << ", y = " << y
                      << ", radius = " << radius
                      << "\n";
        }
    }

    return 0;
}
