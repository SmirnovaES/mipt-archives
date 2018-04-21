
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

class Point {
public:
    Point (double abscissa, double ordinate) {
        x = abscissa;
        y = ordinate;
    }

    Point (const Point& point) {
        x = point.x;
        y = point.y;
    }

    double get_x() const{
        return x;
    }

    double get_y() const{
        return y;
    }

    void set_x(double new_x) {
        x = new_x;
    }

    void set_y(double new_y) {
        y = new_y;
    }

private:
    double x, y;
};

class Segment {
public:
    Segment (const Point& first_point, const Point& second_point): point1(first_point), point2(second_point) {}

    Segment (const Segment& segment): point1(segment.point1), point2(segment.point2) {}

    Point get_first_point() const{
        return point1;
    }

    Point get_second_point() const{
        return point2;
    }

    double get_length() const{
        return sqrt(pow((point2.get_x() - point1.get_x()), 2) + pow((point2.get_y() - point1.get_y()), 2));
    }

    double length_square () const{
        return pow((point2.get_x() - point1.get_x()), 2) + pow((point2.get_y() - point1.get_y()), 2);
    }

    bool is_point_on_segm(const Point& pt) const{
        Segment segm1(point1, pt);
        Segment segm2(pt, point2);
        if (segm1.get_length() + segm2.get_length() == this->get_length()) return true;
        return false;
    }

private:
    Point point1;
    Point point2;
};

bool are_segms_intersect(const Segment& segm1, const Segment& segm2) {
    if (segm1.is_point_on_segm(segm2.get_first_point()) || segm1.is_point_on_segm(segm2.get_second_point()) || segm2.is_point_on_segm(segm1.get_first_point()) || segm2.is_point_on_segm(segm1.get_second_point())) return true;
    double x11 = segm1.get_first_point().get_x();
    double y11 = segm1.get_first_point().get_y();
    double x12 = segm1.get_second_point().get_x();
    double y12 = segm1.get_second_point().get_y();
    double x21 = segm2.get_first_point().get_x();
    double y21 = segm2.get_first_point().get_y();
    double x22 = segm2.get_second_point().get_x();
    double y22 = segm2.get_second_point().get_y();
    double vect1 = (x21 - x11) * (y12 - y11) - (y21 - y11) * (x12 - x11);
    double vect2 = (x12 - x11) * (y22 - y11) - (y12 - y11) * (x22 - x11);
    double vect3 = (x11 - x21) * (y22 - y21) - (y11 - y21) * (x22 - x21);
    double vect4 = (x22 - x21) * (y12 - y21) - (y22 - y21) * (x12 - x21);
    if (vect1 * vect2 >= 0 && vect3 * vect4 >= 0) return true;
    return false;
}

bool are_verts_polygon(const std::vector <Point>& vertices) {
    if (vertices.size() < 3) return false;
    for (unsigned int i = 0; i < vertices.size() - 1; i++) {
        Segment segm1(vertices[i], vertices[i + 1]);
        Segment segm2(vertices[i + 1], vertices[(i + 2) % vertices.size()]);

        if (segm1.is_point_on_segm(vertices[(i + 2) % vertices.size()]) || segm2.is_point_on_segm(vertices[i])) return false;

        for(unsigned int j = i + 2; j < vertices.size(); j++) {
            Segment segm1(vertices[i], vertices[i + 1]);
            Segment segm2(vertices[j % vertices.size()], vertices[(j + 1) % vertices.size()]);
            if (are_segms_intersect(segm1, segm2) && !(segm1.is_point_on_segm(segm2.get_first_point()) || segm1.is_point_on_segm(segm2.get_second_point()) || segm2.is_point_on_segm(segm1.get_first_point()) || segm2.is_point_on_segm(segm1.get_second_point()))) return false;
        }
    }
    return true;
}

double scalar_op(const Point& pt1, const Point& pt2) {
    return pt1.get_x() * pt2.get_x() + pt1.get_y() * pt2.get_y();
}

class Shape {
public:
    virtual bool is_point_on_boarder(const Point &pt) {};

    virtual bool is_point_in_shape(const Point &pt) {};

    virtual Point get_intersection_point(const Segment &segm) {};

    virtual double get_area() {};

    virtual ~Shape() {};
};

class Polygon: public Shape {
public:
    Polygon(const std::vector <Point>& new_vertices) {
        if (!are_verts_polygon(new_vertices)) {
            std::cout << "Error: can not create polygon.\n";
            return;
        }
        vertices = new_vertices;
        for(unsigned int i = 0; i < vertices.size(); i++) {
            boarder.push_back(Segment(vertices[i], vertices[(i + 1) % vertices.size()]));
        }
    }

    Polygon(const Polygon& pol) {
        vertices = pol.vertices;
        boarder = pol.boarder;
    }

    std::vector<Point> get_vertices() const{
        return vertices;
    }

    bool is_point_on_boarder(const Point &pt) {
        for(unsigned int i = 0; i < vertices.size(); i++) {
            if(boarder[i].is_point_on_segm(pt)) return true;
        }
        return false;
    }

    bool is_polygon_convex() {
        for (unsigned int i = 0; i < vertices.size(); i++) {
            int s = vertices.size();
            double vect1 = (vertices[i].get_x() - vertices[(i + 1) % s].get_x()) * (vertices[(i + 2) % s].get_y() - vertices[(i + 1) % s].get_y()) - (vertices[i].get_y() - vertices[(i + 1) % s].get_y()) * (vertices[(i + 2) % s].get_x() - vertices[(i + 1) % s].get_x());
            double vect2 = (vertices[(i + 1) % s].get_x() - vertices[(i + 2) % s].get_x()) * (vertices[(i + 3) % s].get_y() - vertices[(i + 2) % s].get_y()) - (vertices[(i + 1) % s].get_y() - vertices[(i + 2) % s].get_y()) * (vertices[(i + 3) % s].get_x() - vertices[(i + 2) % s].get_x());
            if (vect1 * vect2 <= 0) return false;
        }
        return true;
    }

    Point get_intersection_point(const Segment& segm) {
        for(unsigned int i = 0; i < vertices.size(); i++) {
            if(are_segms_intersect(segm, boarder[i])) {
            double brd_x = boarder[i].get_second_point().get_x() - boarder[i].get_first_point().get_x();
            double sgm_x = segm.get_second_point().get_x() - segm.get_first_point().get_x();
            double sb_x = segm.get_second_point().get_x() - boarder[i].get_first_point().get_x();
            double brd_y = boarder[i].get_second_point().get_y() - boarder[i].get_first_point().get_y();
            double sgm_y = segm.get_second_point().get_y() - segm.get_first_point().get_y();
            double sb_y = segm.get_second_point().get_y() - boarder[i].get_first_point().get_y();
            double res = (sb_x * sgm_y - sgm_x * sb_y) / (brd_x * sgm_y - sgm_x * brd_y);
            double x = boarder[i].get_first_point().get_x() + brd_x * res;
            double y = boarder[i].get_first_point().get_y() + brd_y * res;
            Point result(x, y);
            return result;
            }
        }
        std::cout << "Error: there is no intersection point.\n";
        return Point(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    }

    bool is_point_in_shape(const Point& pt) {

    }

private:
    std::vector<Point> vertices;
    std::vector<Segment> boarder;
};

class ConvexPolygon: public Polygon {
public:
    ConvexPolygon(const std::vector<Point>& vertices): Polygon(vertices) {
        if(!this->is_polygon_convex()) {
            std::cout << "Error: the polygon is not convex.\n";
        }
    }

    ConvexPolygon(const ConvexPolygon& conv_pol): Polygon(conv_pol) {
        if(!this->is_polygon_convex()) {
            std::cout << "Error: the polygon is not convex.\n";
        }
    }

    bool is_point_in_shape(const Point &pt) {
        std::vector<Point> curr_vert = this->get_vertices();
        double x = 0;
        double y = 0;
        for (unsigned int i = 0; i < curr_vert.size(); i++) {
            x += curr_vert[i].get_x();
            y += curr_vert[i].get_y();
        }
        x /= curr_vert.size();
        y /= curr_vert.size();
        Point pt1(x, y);
        Segment segm(pt, pt1);
        Point pt2 = get_intersection_point(segm);
        if (pt2.get_x() == std::numeric_limits<double>::max()) return true;
        return false;
    }

    double get_area(){
        double ans = 0;
        std::vector<Point> curr_vert = this->get_vertices();
        for (unsigned int i = 1; i < curr_vert.size() - 1; i++) {
            ans += (curr_vert[i].get_x() - curr_vert[0].get_x()) * (curr_vert[i + 1].get_y() - curr_vert[0].get_y()) - (curr_vert[i].get_y() - curr_vert[0].get_y()) * (curr_vert[i + 1].get_x() - curr_vert[0].get_x());
        }
        return ans;
    }
};

class Triangle: public ConvexPolygon {
public:
    //Triangle():ConvexPolygon(){}

    Triangle(const std::vector<Point>& new_vertices): ConvexPolygon(new_vertices) {
        if (new_vertices.size() != 3) {
            std::cout << "Error: number of vertices is not 3.\n";
        }
    }
    Triangle(const Triangle& trig): ConvexPolygon(trig.get_vertices()){}
};

class Rectangle: public ConvexPolygon {
public:
//Rectangle():ConvexPolygon(){}
    Rectangle(const std::vector<Point>& new_vertices): ConvexPolygon(new_vertices) {
        if (new_vertices.size() != 4) {
            std::cout << "Error: number of vertices is not 4.\n";
        }
    }
    Rectangle(const Rectangle& rect): ConvexPolygon(rect.get_vertices()) {}
};

class Square: public Rectangle {
public:
    Square(const std::vector<Point>& new_vertices): Rectangle(new_vertices) {
        std::vector<Point> curr_vert = this->get_vertices();
        Segment segm1(curr_vert[0], curr_vert[1]);
        Segment segm2(curr_vert[1], curr_vert[2]);
        if (segm1.get_length() != segm2.get_length()) {
            std::cout << "Error: this is not a square.\n";
        }
    }
    Square(const Square& sq): Rectangle(sq.get_vertices()) {}
~Square();
};

class Circle: public Shape {
public:
    Circle(const Point& new_center, double new_radius): center(new_center) {
        if (new_radius < 0) {
            std::cout << "Error: radius < 0.\n";
            radius = 0;
        } else {
            radius = new_radius;
        }
    }

    Circle(const Circle& circ): center(circ.center), radius(circ.radius) {}

    Point get_center() {
        return center;
    }

    double get_radius() {
        return radius;
    }

    bool is_point_on_boarder(const Point& pt) {
        Segment segm(center, pt);
        if (segm.get_length() == radius) return true;
        return false;
    }

    bool is_point_in_shape(const Point& pt) {
        Segment segm(center, pt);
        if (segm.get_length() < radius) return true;
        return false;
    }

    double getSquare() {
        return (M_PI * radius * radius / 2);
    }

private:
    Point center;
    double radius;
};

int main() {
    Point pt1(0,0);
    Point pt2(2,2);
    Point pt3(4,0);
    Point pt4(1,1);
    std::vector<Point> vertices;
    vertices.push_back(pt1);
    vertices.push_back(pt2);
    vertices.push_back(pt3);
    int n =3;
    Triangle triangle(vertices);
    std::cout << triangle.is_point_on_boarder(pt4) << "\n";
    return 0;
}
