#define USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <cmath>
#include "Shapes.h"
using  namespace std;

string olor[9] = { "BLACK", "RED", "GREEN", "YELLOW", "BLUE", "MAGENTA", "CYAN", "WHITE","INVALID" };

//Box
//Box area
double Box::area() const
{
    return (r-l)*(t-b);
}

//box Perimeter
double Box::perimeter() const
{
    return ((r-l)+(t-b))*2;
}

//moving Box
void Box::move(double X, double Y)
{
    l += X;
    t += Y;
    r += X;
    b += Y;
}
//print
void Box::render(ostream &os) const
{
    os << "Box(" << olor[color()] << "," << l << "," << t << ","
    << r << "," << b << ")";
}
//inside
bool Box::inside (double tx, double ty) const
{
    return(ty < top() && tx < right() && ty > bottom() && tx > left());
}
//Circle
//Circle Area
double Circle::area() const
{
    return r*r*M_PI;
}
//circle perimeter
double Circle::perimeter() const
{
    return (r*2)*M_PI;
}
//moving the circle
void Circle::move(double X, double Y)
{
    x += X;
    y += Y;
}
//print
void Circle::render(ostream &os) const
{
    os << "Circle(" << olor[color()] << "," << x << "," << y << ","
    << r << ")";
}
bool Circle::inside (double tx, double ty) const
{
    if( radius() > sqrt(pow((centerX()-tx),2)+pow((centerY()-ty),2)))
    {
        return true;
    }
    else
    {
        return false;
    }
}
//Triangle
//Triangle area
double Triangle::area() const
{
    double uno = sqrt(pow((xc1-xc2),2)+pow((yc1-yc2),2));
    double dos = sqrt(pow((xc2-xc3),2)+pow((yc2-yc3),2));
    double tres = sqrt(pow((xc3-xc1),2)+pow((yc3-yc1),2));
    double peri = perimeter()/2;
    return sqrt(peri*(peri-uno)*(peri-dos)*(peri-tres));
}
// triangle perimeter
double Triangle::perimeter() const
{
    double uno = sqrt(pow((xc1-xc2),2)+pow((yc1-yc2),2));
    double dos = sqrt(pow((xc2-xc3),2)+pow((yc2-yc3),2));
    double tres = sqrt(pow((xc3-xc1),2)+pow((yc3-yc1),2));
    
    return uno+dos+tres;
}
//moving triangle
void Triangle::move(double X, double Y)
{
    xc1 += X;
    xc2 += X;
    xc3 += X;
    yc1 += Y;
    yc2 += Y;
    yc3 += Y;
}
//print
void Triangle::render(ostream &os) const
{
    os << "Triangle(" << olor[color()] << "," << xc1 << "," << yc1 << ","
    << xc2 << "," << yc2 << "," << xc3 << "," << yc3 << ")";
}
//triangle inside
bool Triangle::inside (double tx, double ty) const
{
    Triangle illuminati1(RED, tx, ty, xc1, yc1, xc2, yc2);
    Triangle illuminati2(RED, tx, ty, xc2, yc2, xc3, yc3);
    Triangle illuminati3(RED, tx, ty, xc3, yc3, xc1, yc1);
    
    return ((illuminati1.area()+illuminati2.area()+illuminati3.area()) == area());
}
//Polygon
double Polygon::points() const
{
    return size;
}
//Polygon area
double Polygon::area() const
{
    double aera = 0;
    for (int k=0; k<size; k++)
    {
        aera += ((vertexX(k)*vertexY((k+1)%size))-(vertexX((k+1)%size)*vertexY(k)));
    }
    return aera/2;
}
// polygon perimeter
double Polygon::perimeter() const
{
    double peri = 0;
    for (int i=0; i<size; i++)
    {
        peri += sqrt(pow((vertexX(i)-vertexX((i+1)%size)),2)+pow((vertexY(i)-vertexY((i+1)%size)),2));
    }
    return peri;
}
//move the polygon
void Polygon::move(double X, double Y)
{
    for (int j=0; j<size; j++)
    {
        cornersX[j] += X;
        cornersY[j] += Y;
    }
}
//print
void Polygon::render(ostream &os) const
{
    os << "Polygon(" << olor[color()] << "," << size;
    for (int k=0; k<size; k++)
    {
        os << "," << cornersX[k];
        os << "," << cornersY[k];
    }
    os << ")";
}

bool Polygon::inside (double tx, double ty) const
{
    int j = size -1;
    bool c = false;
    for (int i = 0; i < size; i++) {
        if ( ((cornersY[i]>ty) != (cornersY[j]>ty)) && (tx < (cornersX[j]-cornersX[i]) * (ty-cornersY[i]) / (cornersY[j]-cornersY[i]) + cornersX[i]) )
        {
            c = !c;
        }
        j = i;
    }
    return c;
}

// line
void Line::render(std::ostream &os) const
{
    os << "Line(" << olor[color()] << "," << EX1 << "," << EY1 << "," << EX2 << "," << EY2 << ")";
}

//rounded box area
double RoundBox::area()const
{
    double p = Box::area()-(ra*ra*4);
    return p + (ra*ra*M_PI);
}
//RoundBox Perimeter
double RoundBox::perimeter()const
{
    double a = Box::perimeter()-((ra+ra)*4);
    return a + ((ra*2)*M_PI);
}
// Round Box render
void RoundBox::render(std :: ostream & os) const
{
    os << "RoundBox(" << olor[color()] << "," << left() << "," << top() << "," << right() << "," << bottom() << "," << ra << ")";
}
// Rounded Box inside
bool RoundBox::inside (double tx, double ty) const
{
    Circle I (BLACK,left()-ra,top()-ra,ra); //🐞
    Circle Hate (RED,right()- ra, top()-ra,ra);
    Circle Programming (RED,right()-ra,bottom()-ra,ra);
    Circle Forever (RED,left()-ra,bottom()-ra,ra);
    
    Box stupid (RED,left(),top()-ra,right(),bottom()-ra);
    Box rectangle (RED,left()-ra,top(),right()-ra,bottom());
    
    return (I.inside(tx,ty) || Hate.inside(tx,ty) || Programming.inside(tx,ty) || Forever.inside(tx,ty) || stupid.inside(tx,ty) || rectangle.inside(tx,ty));
}
//color at point
Color Shape::colorAtPoint(Shape** ape,int length,int point1, int point2)
{
    for (int j = 0; j<length;j++)
    {
        if(ape[j]-> inside(point1,point2))
        {
            return ape[j]->color();
        }
    }
    return INVALID;
}
// group
//Group Shape
Shape* Group::shape(int A)
{
    return Pointer[A];
}
// Group area
double Group::area() const
{
    double totalarea = 0;
    for(int b = 0; b < size; b++)
    {
        totalarea += Pointer[b]->area();
    }
    
    return totalarea;
}
// Group perimeter
double Group::perimeter() const
{
    double totalperimeter = 0;
    for(int i = 0; i < size; i++)
    {
        totalperimeter += Pointer[i]->perimeter();
    }
    return totalperimeter;
}
// Group move
void Group::move(double dx, double dy)
{
    for(int g = 0;g < size;g++)
    {
        Pointer[g]->move(dx,dy);
    }
}
// Group render
void Group::render(std :: ostream & os) const
{
    os << "Group(" << olor[Shape::color()] << "," << size;
    for (int a = 0; a<size; a++)
    {
        os << ",";
        Pointer[a]->render(os);
    }
    os << ")";
}
// Gourp inside
bool Group::inside(double tx, double ty) const
{
    for (int i = 0; i < size; i++)
    {
        if(Pointer[i]->inside(tx,ty))
        {
            return true;
        }
    }
    return false;
}
//Group Shape
void Group::shapes(int length,Shape **PointerS)
{
    for(int l = 0;l < size; l++)
    {
        delete Pointer[l];
    }
    
    Pointer = PointerS;
    size = length;
}

//int main()
//{
//    Shape * list[2];
//    list[0] = new Box(GREEN, 0, 1, 1, 0);
//    list[1] = new Circle(YELLOW, 2, 2, 2);
//    Group g(BLUE, 2, list);
//    
//    cout << "Group area: " << g.area() << "\n";
//    cout << "Group perimeter: " << g.perimeter() << "\n";
//    
//    g.move(1,1);
//    g.render(cout); cout << "\n";
//    g.color(RED);
//    g.render(cout); cout << "\n";
//    
//    cout << "Count: " << g.shapes() << "\n";
//    g.shape(1)->render(cout); cout << "\n";
//    
//    Shape * list2[3];
//    list2[0] = new Circle(WHITE,5,5,1);
//    list2[1] = new Box(GREEN,7,1,9,-10);
//    list2[2] = new RoundBox(BLACK,5,5,8.5,4.5,0.1);
//    g.shapes(3,list2);
//    g.render(cout); cout << "\n";
//}
