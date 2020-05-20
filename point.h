#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

class Point
{
public:
    float x, y, z;

    Point(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Point() {}

    Point(const Point &p2)
    {
        x = p2.x;
        y = p2.y;
        z = p2.z;
    }
};


#endif // POINT_H_INCLUDED
