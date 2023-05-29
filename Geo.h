//#pragma once
//#include<iostream>
//#include<sstream>
//#include<string>
//#include<cmath>
//#include<cassert>
//#include<fstream>
//#include<vector>
//
//using namespace std;
//
////���������Ͷ���
//const double pi = 2 * std::asin(1);
//
//struct Point {
//    int x, y;
//};
//
////ͼ���������
//class shape {
//public:
//    virtual ~shape() = 0;
//    virtual void setBcolor(string color) { Bcolor = color; }//���ñ߿���ɫ
//    virtual void setBstyle(string style) { Bstyle = style; }//���ñ߿���ʽ
//    virtual void setTcolor(string color) { Tcolor = color; }//���������ɫ 
//    virtual void setTstyle(string style) { Tstyle = style; }//���������ʽ
//    virtual string getBcolor() const { return Bcolor; }//��ȡ�߿���ɫ
//    virtual string getBstyle() const { return Bstyle; }//��ȡ�߿���ʽ
//    virtual string getTcolor() const { return Tcolor; }//��ȡ�����ɫ 
//    virtual string getTstyle() const { return Tstyle; }//��ȡ�����ʽ
//private:
//    string Bcolor;
//    string Tcolor;
//    string Bstyle;
//    string Tstyle;
//};
//
//inline shape::~shape() {}
//
//class Line : public shape {
//public:
//    Line(Point s, Point e);
//    Line(const Line& other);
//private:
//    Point start;
//    Point end;
//};
//
//class Points : public shape {
//public:
//    Points(vector<Point> p);
//    Points(const Points& other);
//private:
//    vector<Point> points;
//};
//
//class Circle : public shape {
//public:
//    Circle(Point c, double r);
//    Circle(const Circle& other);
//private:
//    Point center;
//    double radius;
//};
//
//class Rectangle : public shape {
//public:
//    Rectangle(Point tl, int w, int h);
//    Rectangle(const Rectangle& other);
//private:
//    Point topLeft;
//    int width;
//    int height;
//};
//
//class Triangle : public shape {
//public:
//    Triangle(Point p1, Point p2, Point p3);
//    Triangle(const Triangle& other);
//private:
//    Point point1;
//    Point point2;
//    Point point3;
//};
//
//class Polyline : public shape {
//public:
//    Polyline(vector<Point> ps);
//    Polyline(const Polyline& other);
//private:
//    vector<Point> points;
//};
//
//class Sector : public shape {
//public:
//    Sector(Point c, double r, double s, double e);
//    Sector(const Sector& other);
//private:
//    Point center;
//    double radius;
//    double startAngle;
//    double endAngle;
//};
