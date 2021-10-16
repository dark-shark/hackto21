#include <iostream>
using namespace std;


class Point
{
  public:
    int x;
    int y;

};
void checkPos(Point P1,Point P2,Point P)
  {
    // I am using Determinant to find this position.
    /* 1  1   1
       x1 x2  x
       y1 y2  y
       Here x1 y1 are P1.x P1.y , x2 y2 are P2.x P2.y and x y are P.x P.y
       Determinant = 1*(x2*y - y2*x) - 1*(x1*y - y1*x) + 1*(x1*y2 - y1*x2)
       Using Determinant Value > < or = 0 we will comment accordingly.
    */
    int det = 1*(P2.x*P.y - P2.y*P.x) - 1*(P1.x*P.y - P1.y*P.x) + 1*(P1.x*P2.y - P1.y*P2.x);

    if (det < 0)
      cout<<"Point lies on right side of line."<<endl;
    else if (det == 0)
      cout<<"Point P lies on line."<<endl;
    else
      cout<<"Point lies on left side of line."<<endl;
  }
int main()
{
  Point P1 , P2 , P;
  cout<<"Enter co-ordinates of Point P1 for the straight line : ";
  cin>>P1.x >>P1.y;

  cout<<"Enter co-ordinates of Point P2 for the straight line : ";
  cin>>P2.x >>P2.y;

  /*
  Let the given two points be P(x1, y1) and Q(x2, y2). Now, we find the equation of line formed by these points.
  Any line can be represented as,
  ax + by = c where
  a = y2 - y1
  b = x1 - x2
  c = ax1 + by1
  */

  int a = P2.y - P1.y;
  int b = P1.x - P2.x;
  int c = a*P1.x + b*P1.y;

  if (b < 0) {
        cout << "The line passing through points P1 and P2 "
                "is: "
             << a << "x - " << -1*b << "y = " << c << endl;
    }
    else {
        cout << "The line passing through points P1 and P2 "
                "is: "
             << a << "x + " << b << "y = " << c << endl;
        }

        cout<<"Enter co-ordinates of Point P to check its position : ";
        cin>>P.x >>P.y;
        checkPos(P1,P2,P);
return 0;

}
