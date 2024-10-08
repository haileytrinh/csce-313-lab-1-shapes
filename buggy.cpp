#include <iostream>
using namespace std;

struct Point {
    int x, y;

    Point () : x(0), y(0) {} // proper memory allocation
    Point (int _x, int _y) : x(_x), y(_y) {}
};

class Shape {
private:
    int vertices;
    Point** points;
public:
    Shape (int _vertices) {
        vertices = _vertices;
        points = new Point*[vertices];
        for (int i=0; i<vertices; i++) {
            points[i] = new Point();
        }
    }

    ~Shape () { // completed destructor
        for (int i=0; i<vertices; i++) {
            delete points[i];
        }
        delete [] points;
    }

    void addPoints (Point pts[] /* unsized Point array */) {
        for (int i = 0; i < vertices; i++) { // changed from <= to = for out bound access
            *points[i] = pts[i%vertices]; // avoiding the use of memcpy()
        }
    }

    double area () { // should not return a pointer double so area is returned by value and not reference
        int temp = 0;
        for (int i = 0; i < vertices; i++) { // changed from <= to = for out bound access
            // FIXME: there are two methods to access members of pointers
            //        use one to fix lhs and the other to fix rhs
            int lhs = points[i]->x * points[(i+1)%vertices]->y; // arrow syntax
            int rhs = (*points[(i+1)%vertices]).x * (*points[i]).y; // dot syntax
            temp += (lhs - rhs);
        }
        double area = abs(temp)/2.0;
        return area;
    }
};

/* int main () {
    // FIXME: create the following points using the three different methods
    //        of defining structs:
    //          tri1 = (0, 0)
    //          tri2 = (1, 2)
    //          tri3 = (2, 0)
    // method 1: direct initialization
    Point tri1(0,0);
    // method 2: default constructor + member assignment
    Point tri2;
    tri2.x = 1;
    tri2.y = 2;
    // method 3: initialization using previously defined variables
    int x = 2;
    int y = 0;
    Point tri3(x,y);

    // adding points to tri
    Point triPts[3] = {tri1, tri2, tri3};
    Shape* tri = new Shape(3);
    tri->addPoints(triPts);

    // FIXME: create the following points using your preferred struct
    //        definition:
    //          quad1 = (0, 0)
    //          quad2 = (0, 2)
    //          quad3 = (2, 2)
    //          quad4 = (2, 0)
    Point quad1(0,0);
    Point quad2(0,2);
    Point quad3(2,2);
    Point quad4(2,0);

    // adding points to quad
    Point quadPts[4] = {quad1, quad2, quad3, quad4};
    Shape* quad = new Shape(4);
    quad->addPoints(quadPts);

    // FIXME: print out area of tri and area of quad
    cout << "Area of triangle: " << tri->area() << endl;
    cout << "Area of quadrilateral: " << quad->area() << endl;

    delete tri;
    delete quad;
} */
