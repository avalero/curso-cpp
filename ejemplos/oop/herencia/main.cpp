#include "regularpolygon.h"
#include "Cuadrado.h"
#include <iostream>
using namespace std;

int main()
{
  RegularPolygon triangulo(3, 4);
  cout << "Perimeter: " << triangulo.getPerimeter() << endl;

  RegularPolygon cuadrado(4, 5);
  cout << "Perimeter: " << cuadrado.getPerimeter() << endl;
  cout << "Area: " << cuadrado.getArea() << endl;

  Cuadrado cuadrado2(6);
  cout << "Perimeter: " << cuadrado2.getPerimeter() << endl;
  cout << "Area: " << cuadrado2.getArea() << endl;

  return 0;
}