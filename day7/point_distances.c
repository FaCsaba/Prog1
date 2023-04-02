#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

double distance(Point p1, Point p2) {
    sqrt(pow(abs(p1.x-p2.x), 2) + pow(abs(p2.y-p2.y), 2));
}

int main(void) {
    Point p1 = { 1, 2 };
    Point p2 = { 6, 5 };

    printf("%lf", distance(p1, p2));
}