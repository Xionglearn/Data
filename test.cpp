#include"storage.h"
int main() {
    vector<unique_ptr<Shape>> shapes;
    shapes.emplace_back(make_unique<Line>(Point{ 10, 20 }, Point{ 30, 40 }));
    shapes.emplace_back(make_unique<Circle>(Point{ 50, 60 }, 70));

    FileStorageFactory fileFactory;
    saveShapes(shapes, fileFactory, "D://shapes.txt");

    // DatabaseStorageFactory dbFactory;
    // saveShapes(shapes, dbFactory, "shapes.db");
    return 0;
}