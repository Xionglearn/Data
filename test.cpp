#include"Geo.h"
int main() {
    // Create some shapes
    std::shared_ptr<Shape> line = std::make_shared<Line>(Point{ 0, 0 }, Point{ 100, 100 });
    std::shared_ptr<Shape> circle = std::make_shared<Circle>(Point{ 50, 50 }, 25);
    std::shared_ptr<Shape> rectangle = std::make_shared<Rectangle>(Point{ 0, 0 }, 50, 100);
    std::shared_ptr<Shape> triangle = std::make_shared<Triangle>(Point{ 0, 0 }, Point{ 100, 0 }, Point{ 50, 50 });
    std::shared_ptr<Shape> polyline = std::make_shared<Polyline>(std::vector<Point>{ {0, 0}, { 50, 50 }, { 100, 0 } });
    std::shared_ptr<Shape> sector = std::make_shared<Sector>(Point{ 50, 50 }, 25, 45, 135);

    // Save the shapes to a text file
    TextFileStorage textStorage;
    textStorage.save("D://shapes.txt", std::vector<std::shared_ptr<Shape>>{ line, circle, rectangle, triangle, polyline, sector });

    // Load the shapes from the text file and draw them
    auto loadedShapes = textStorage.load("D://shapes.txt");
    for (const auto& shape : loadedShapes) {
        shape->draw();
    }

    // Save the shapes to a binary file
    BinaryFileStorage binaryStorage;
    binaryStorage.save("D://shapes.bin", std::vector<std::shared_ptr<Shape>>{ line, circle, rectangle, triangle, polyline, sector });

    // Load the shapes from the binary file and draw them
    loadedShapes = binaryStorage.load("D://shapes.bin");
    for (const auto& shape : loadedShapes) {
        shape->draw();
    }

    return 0;
}
