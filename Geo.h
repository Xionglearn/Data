#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
using namespace std::filesystem;
using namespace std;

struct Point {
    int x, y;
};

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;

protected:
    std::string borderColor;
    std::string borderStyle;
    std::string fillColor;
    std::string fillStyle;
};

class Line : public Shape {
public:
    Line(Point s, Point e) : start(s), end(e) {}
    void draw() const override {
        std::cout << "Line from (" << start.x << "," << start.y << ") to ("
            << end.x << "," << end.y << ")" << std::endl;
    }
private:
    Point start;
    Point end;
};

class Circle : public Shape {
public:
    Circle(Point c, double r) : center(c), radius(r) {}
    void draw() const override {
        std::cout << "Circle with center (" << center.x << "," << center.y
            << ") and radius " << radius << std::endl;
    }
private:
    Point center;
    double radius;
};

class Rectangle : public Shape {
public:
    Rectangle(Point tl, int w, int h)
        : topLeft(tl), width(w), height(h) {}
    void draw() const override {
        std::cout << "Rectangle with width " << width << ", and height" << height
            << " and the topleft point lies in (" << topLeft.x << ","
            << topLeft.y << ")" << std::endl;
    }
private:
    Point topLeft;
    int width;
    int height;
};

class Triangle : public Shape {
public:
    Triangle(Point p1, Point p2, Point p3)
        : point1(p1), point2(p2), point3(p3) {}
    void draw() const override {
        std::cout << "Triangle with 3 points (" << point1.x << ","
            << point1.y << "), (" << point2.x << ", " << point2.y
            << "), and (" << point3.x << ", " << point3.y << ")" << std::endl;
    }
private:
    Point point1;
    Point point2;
    Point point3;
};

class Polyline : public Shape {
public:
    Polyline(std::vector<Point> ps) : points(ps) {}
    void draw() const override {
        std::cout << "Polyline with points: ";
        for (const auto& p : points) {
            std::cout << "(" << p.x << "," << p.y << ") ";
        }
        std::cout << std::endl;
    }
private:
    std::vector<Point> points;
};

class Sector : public Shape {
public:
    Sector(Point c, double r, double s, double e)
        : center(c), radius(r), startAngle(s), endAngle(e) {}
    void draw() const override {
        std::cout << "Sector with center (" << center.x << "," << center.y
            << "), radius " << radius << ", start angle " << startAngle
            << ", and end angle " << endAngle << std::endl;
    }
private:
    Point center;
    double radius;
    double startAngle;
    double endAngle;
};

class Storage {
public:
    virtual void save(const std::string& fileName,
        const std::vector<std::shared_ptr<Shape>>& shapes) = 0;
    virtual std::vector<std::shared_ptr<Shape>> load(
        const std::string& fileName) = 0;
    virtual ~Storage() = default;
};

class TextFileStorage : public Storage {
public:
    void save(const std::string& fileName,
        const std::vector<std::shared_ptr<Shape>>& shapes) override {  // Create or open the text file
        std::ofstream outFile(fileName);

        // Check if the file was opened successfully
        if (!outFile.is_open()) {
            throw std::runtime_error("Failed to open file: " + fileName);
        }

        // Write each shape to the file
        for (const auto& shape : shapes) {
            outFile << typeid(*shape).name() << " ";
            shape->draw();
        }
    }

    std::vector<std::shared_ptr<Shape>> load(
        const std::string& fileName) override {
        // Check if the file exists
        if (!std::filesystem::exists(fileName)) {
            throw std::runtime_error("File not found: " + fileName);
        }

        // Open the text file
        std::ifstream inFile(fileName);

        // Check if the file was opened successfully
        if (!inFile.is_open()) {
            throw std::runtime_error("Failed to open file: " + fileName);
        }

        // Read each line from the file and create a shape object based on the type name
        std::vector<std::shared_ptr<Shape>> shapes;
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string typeName;
            iss >> typeName;

            if (typeName == typeid(Line).name()) {
                Point start, end;
                iss >> start.x >> start.y >> end.x >> end.y;
                shapes.push_back(std::make_shared<Line>(start, end));
            }
            else if (typeName == typeid(Circle).name()) {
                Point center;
                double radius;
                iss >> center.x >> center.y >> radius;
                shapes.push_back(std::make_shared<Circle>(center, radius));
            }
            else if (typeName == typeid(Rectangle).name()) {
                Point topLeft;
                int width, height;
                iss >> topLeft.x >> topLeft.y >> width >> height;
                shapes.push_back(std::make_shared<Rectangle>(topLeft, width, height));
            }
            else if (typeName == typeid(Triangle).name()) {
                Point point1, point2, point3;
                iss >> point1.x >> point1.y >> point2.x >> point2.y >> point3.x >> point3.y;
                shapes.push_back(std::make_shared<Triangle>(point1, point2, point3));
            }
            else if (typeName == typeid(Polyline).name()) {
                std::vector<Point> points;
                int x, y;
                while (iss >> x >> y) {
                    points.push_back(Point{ x, y });
                }
                shapes.push_back(std::make_shared<Polyline>(points));
            }
            else if (typeName == typeid(Sector).name()) {
                Point center;
                double radius, startAngle, endAngle;
                iss >> center.x >> center.y >> radius >> startAngle >> endAngle;
                shapes.push_back(std::make_shared<Sector>(center, radius, startAngle, endAngle));
            }
        }

        return shapes;
    }
};

class BinaryFileStorage : public Storage {
public:
    void save(const std::string& fileName,
        const std::vector<std::shared_ptr<Shape>>& shapes) override {
        // Create or open the binary file
        std::ofstream outFile(fileName, std::ios::binary);

        // Check if the file was opened successfully
        if (!outFile.is_open()) {
            throw std::runtime_error("Failed to open file: " + fileName);
        }

        // Write each shape to the file
        for (const auto& shape : shapes) {
            // Get the size of the shape object
            size_t size = sizeof(*shape);

            // Write the size and the shape object to the file
            outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
            outFile.write(reinterpret_cast<const char*>(shape.get()), size);
        }
    }

    std::vector<std::shared_ptr<Shape>> load(
        const std::string& fileName) override {
        // Check if the file exists
        if (!std::filesystem::exists(fileName)) {
            throw std::runtime_error("File not found: " + fileName);
        }

        // Open the binary file
        std::ifstream inFile(fileName, std::ios::binary);

        // Check if the file was opened successfully
        if (!inFile.is_open()) {
            throw std::runtime_error("Failed to open file: " + fileName);
        }

        // Read each shape from the file
        std::vector<std::shared_ptr<Shape>> shapes;
        while (inFile.peek() != EOF) {
            // Read the size of the shape object
            size_t size;
            inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
            // Allocate memory for the shape object and read it from the file
            std::unique_ptr<char[]> buffer(new char[size]);
            inFile.read(buffer.get(), size);

            // Create a shared pointer to the shape object and add it to the vector
            if (typeid(*reinterpret_cast<Shape*>(buffer.get())) == typeid(Line)) {
                shapes.push_back(std::make_shared<Line>(*reinterpret_cast<Line*>(buffer.get())));
            }
            else if (typeid(*reinterpret_cast<Shape*>(buffer.get())) == typeid(Circle)) {
                shapes.push_back(std::make_shared<Circle>(*reinterpret_cast<Circle*>(buffer.get())));
            }
            else if (typeid(*reinterpret_cast<Shape*>(buffer.get())) == typeid(Rectangle)) {
                shapes.push_back(std::make_shared<Rectangle>(*reinterpret_cast<Rectangle*>(buffer.get())));
            }
            else if (typeid(*reinterpret_cast<Shape*>(buffer.get())) == typeid(Triangle)) {
                shapes.push_back(std::make_shared<Triangle>(*reinterpret_cast<Triangle*>(buffer.get())));
            }
            else if (typeid(*reinterpret_cast<Shape*>(buffer.get())) == typeid(Polyline)) {
                shapes.push_back(std::make_shared<Polyline>(*reinterpret_cast<Polyline*>(buffer.get())));
            }
            else if (typeid(*reinterpret_cast<Shape*>(buffer.get())) == typeid(Sector)) {
                shapes.push_back(std::make_shared<Sector>(*reinterpret_cast<Sector*>(buffer.get())));
            }
        }

        return shapes;
    }
};
