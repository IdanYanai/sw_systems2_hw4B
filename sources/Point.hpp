#include <iostream>
#include <cmath>

using namespace std;

namespace ariel {
    class Point {
        private:
            double x, y;

        public:
            Point(double inputX, double inputY) : x(inputX), y(inputY) {}
            
            double distance(Point other) {
                return sqrt(pow(this->x - other.getX(), 2) + pow(this->y - other.getY(), 2));
            }

            static Point moveTowards(Point src, Point dst, int speed) {
                double distance = src.distance(dst);
                if(speed >= distance) {
                    return dst;
                }
                else {
                    double ratio = speed / distance;
                    double newX = src.getX() + ratio * (dst.getX() - src.getX());
                    double newY = src.getY() + ratio * (dst.getY() - src.getY());
                    return Point(newX, newY);
                }
            }

            friend ostream& operator<< (ostream& output, const Point& pointo) {
                return (output << "(" << pointo.getX() << "," << pointo.getY() << ")");
            }

            double getX() const { return this->x;}
            double getY() const { return this->y;}
    };
}