#define USE_MATH_DEFINES
#include <iostream>
#include <cmath>

enum Color { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE,INVALID};

class Shape
{
public:
    
    Shape(Color c) : hue(c) {};
    virtual ~ Shape () {};
    
    Color color () const{ return hue; }
    virtual void color(Color c) { hue = c; }
    
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void render(std :: ostream & os) const = 0;
    virtual bool inside(double tx, double ty) const = 0;
    double thickness() {return area()/perimeter();}
    static Color colorAtPoint(Shape** ape,int length,int point1, int point2);
    
private:
    Color hue;
};

class Group : public Shape
{
public:
    Group (Color c, int length, Shape **PointerS): Shape(c){size = length; Pointer = PointerS; color(c);}
    ~ Group ()
    {
        for(int g = 0; g < size; g++)
        {
             delete Pointer[g];
        }
    }
    
    void color(Color c)
    {
        Shape::color(c);
        for(int sc = 0; sc < size; sc++)
        {
            Pointer[sc]->color(c);
        }
    }
    Shape* shape(int A);
    int shapes()const {return size;}
    
    void shapes(int length,Shape **PointerS);
    double area() const;
    double perimeter() const;
    void move(double dx, double dy);
    void render(std :: ostream & os) const;
    bool inside(double tx, double ty) const;
    
private:
    int size;
    Shape ** Pointer;
    Group (const Group& b);
    Group& operator=(const Group& b);
};

//Box Class
class Box : public Shape
{
public:
    Box(Color c, double _left, double  _top, double _right, double _bottom) :
    Shape(c) {l = _left;r = _right; t = _top; b = _bottom;}
    
    //getter
    double left() const {return l;}
    double top() const {return t;}
    double right() const {return r;}
    double bottom() const {return b;}
    //setter
    void left( double _left ) { l = _left; }
    void top( double _top ) { t = _top; }
    void right( double _right ) { r = _right; }
    void bottom( double _bottom ) { b = _bottom; }
    
    virtual double area() const;
    virtual double perimeter() const;
    void move(double dx, double dy);
    virtual void render(std :: ostream & os) const;
    virtual bool inside (double tx, double ty) const;
    
private:
    
    double l, t ,r, b;
    Box (const Box& b);
    Box& operator=(const Box& b);
    
};

//Circle
class Circle : public Shape
{
public:
    Circle(Color c, double x_axis, double  y_axis, double rad) :
    Shape(c) { x = x_axis; y = y_axis ; r = rad;}
    
    //getters
    double centerX() const {return x;}
    double centerY() const {return y;}
    double radius() const {return r;}
    
    //setters
    void centerX( double coordinate ) { x = coordinate; }
    void centerY( double coordinate ) { y = coordinate; }
    void radius( double coordinate ) { r = coordinate; }
    
    double area() const;
    double perimeter()const;
    void move(double dx, double dy);
    void render(std :: ostream & os) const;
    bool inside (double tx, double ty)const;
    
private:
    
    double x, y, r;
    Circle(const Circle& c);
    Circle& operator=(const Circle& c);
    
};

//Triangle
class Triangle : public Shape
{
public:
    Triangle(Color c, double XC1,double YC1, double  XC2, double YC2, double XC3,  double YC3) :
    Shape(c) {xc1 = XC1;yc1 = YC1; xc2 = XC2; yc2 = YC2; xc3 = XC3 ; yc3 = YC3;}
    
    //getter
    double cornerX1() const {return xc1;}
    double cornerX2() const {return xc2;}
    double cornerX3() const {return xc3;}
    double cornerY1() const {return yc1;}
    double cornerY2() const {return yc2;}
    double cornerY3() const {return yc3;}
    
    //setter
    void  cornerX1( double coordinate ) { xc1 = coordinate; }
    void  cornerX2( double coordinate ) { xc2 = coordinate; }
    void  cornerX3( double coordinate ) { xc3 = coordinate; }
    void  cornerY1( double coordinate ) { yc1 = coordinate; }
    void  cornerY2( double coordinate ) { yc2 = coordinate; }
    void  cornerY3( double coordinate ) { yc3 = coordinate; }
    
    double area() const;
    double perimeter()const;
    void move(double dx, double dy);
    void render(std :: ostream & os) const;
    bool inside (double tx, double ty)const;

private:
    
    double xc1, xc2 ,xc3, yc1, yc2, yc3;
    Triangle(const Triangle& tri);
    Triangle& operator=(const Triangle& tri);
};


//Polygon
class Polygon : public Shape
{
public:
    Polygon(Color c,double* point, int max ) : Shape(c), size(max)
    {
        cornersX = new double[max];
        cornersY = new double[max];
        for (int j = 0; j < size; j++)
        {
            cornersX[j] = point[j*2];
            cornersY[j] = point[(j*2)+1];
        }
    }
    
    //deconstructor
    ~Polygon() {delete [] cornersX; delete [] cornersY;}
    
    //getter
    double vertexX(int index) const {return cornersX[index];}
    double vertexY(int index) const {return cornersY[index];}
    
    //setter
    void vertexX( int index, double coordinate ) {  cornersX[index] = coordinate; }
    void vertexY( int index, double coordinate ) { cornersY[index] = coordinate; }
    
    double points() const;
    double area() const;
    double perimeter()const;
    void move(double dx, double dy);
    void render(std :: ostream & os) const;
    bool inside (double tx, double ty)const;
    
private:
    
    double* cornersX;
    double* cornersY;
    int size;
    Polygon(const Polygon& poly);
    Polygon& operator=(const Polygon& poly);
    
};

//line Class
class Line : public Shape
{
public:
    Line(Color c, double endx1, double  endy1, double endx2, double endy2) :
    Shape(c) {EX1 = endx1;EX2 = endx2; EY1 = endy1; EY2 = endy2;}
    
    //getter
    double end1X() const {return EX1;}
    double end2X() const {return EX2;}
    double end1Y() const {return EY1;}
    double end2Y() const {return EY2;}
    //setter
    void end1X(double coordinate) {EX1 = coordinate;}
    void end2X(double coordinate) {EX2 = coordinate;}
    void end1Y(double coordinate) {EY1 = coordinate;}
    void end2Y(double coordinate) {EY2 = coordinate;}

    double area() const{return 0;};
    double perimeter() const {return sqrt(pow(EX1-EX2,2) + pow(EY1-EY2,2));};
    void move(double dx, double dy){EX1 += dx; EX2 += dx; EY1 += dy; EY2 += dy;};
    void render(std :: ostream & os) const;
    bool inside (double tx, double ty) const {double x = tx;double y = ty; return false;};

private:

    double EX1, EX2 ,EY1, EY2;
    Line (const Line& ln);
    Line& operator=(const Line& ln);
    
};

//rounded rectangle Class
class RoundBox : public Box
{
public:
    RoundBox(Color c, double _left, double  _top, double _right, double _bottom, double _radius) :
    Box (c,_left,_top,_right,_bottom){ra = _radius;}
    
    //setter
    void radius(double coordinate){ra = coordinate;}
    //getter
    double radius() const {return ra;}
    double area() const;
    double perimeter() const;
    void render(std :: ostream & os) const;
    bool inside (double tx, double ty)const;
        
private:
        
    double ra;
    RoundBox (const RoundBox& rad);
    RoundBox& operator=(const RoundBox& rad);
        
};
