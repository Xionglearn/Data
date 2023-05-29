#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>    // std::unique_ptr, std::make_unique

using namespace std;

// 定义图形结构体
struct Point {
    int x;
    int y;
};

struct Shape {
    virtual void draw() = 0;
};

class Line : public Shape {
public:
    Line(Point start, Point end) : m_start(start), m_end(end) {}
    void draw() override {
        cout << "Line from (" << m_start.x << "," << m_start.y << ") to ("
            << m_end.x << "," << m_end.y << ")" << endl;
    }
private:
    Point m_start;
    Point m_end;
};

class Circle : public Shape {
public:
    Circle(Point center, int radius) : m_center(center), m_radius(radius) {}
    void draw() override {
        cout << "Circle with center (" << m_center.x << "," << m_center.y
            << ") and radius " << m_radius << endl;
    }
private:
    Point m_center;
    int m_radius;
};

// 抽象工厂类
class StorageFactory {
public:
    virtual unique_ptr<ofstream> createOfstream(const string& fileName) = 0;
    virtual unique_ptr<Shape> createShape(const string& type, const vector<int>& params) = 0;
};

// 文件存储工厂类
class FileStorageFactory : public StorageFactory {
public:
    unique_ptr<ofstream> createOfstream(const string& fileName) override {
        return make_unique<ofstream>(fileName);
    }
    unique_ptr<Shape> createShape(const string& type, const vector<int>& params) override {
        if (type == "Line") {
            Point start = { params[0], params[1] };
            Point end = { params[2], params[3] };
            return make_unique<Line>(start, end);
        }
        else if (type == "Circle") {
            Point center = { params[0], params[1] };
            int radius = params[2];
            return make_unique<Circle>(center, radius);
        }
        else {
            throw invalid_argument("Unsupported shape type");
        }
    }
};

// 数据库存储工厂类
class DatabaseStorageFactory : public StorageFactory {
public:
    unique_ptr<ofstream> createOfstream(const string&) override {
        throw runtime_error("Database storage does not support file output");
    }
    unique_ptr<Shape> createShape(const string& type, const vector<int>& params) override {
        // 从数据库中读取数据并创建图形对象
        // ...
        throw runtime_error("Database storage is not implemented yet");
    }
};

void saveShapes(const vector<unique_ptr<Shape>>& shapes, StorageFactory& factory, const string& fileName) {
    unique_ptr<ofstream> ofs = factory.createOfstream(fileName);
    for (const auto& shape : shapes) {
        shape->draw();
        (*ofs) << "Shape: ";
        shape->draw(); // 写入图形信息
    }
}

