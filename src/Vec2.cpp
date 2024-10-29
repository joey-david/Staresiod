#include "Vec2.h"

Vec2::Vec2(float X, float Y) : x(X), y(Y) {}

Vec2::Vec2(const Vec2 &v) {
    x = v.x;
    y = v.y;
}

float Vec2::getX() const {
    return(x);
}

float Vec2::getY() const {
    return(y);
}

void Vec2::setX(const float& X) {
    x = X;
}

void Vec2::setY(const float& Y) {
    y = Y;
}

Vec2 Vec2::operator+(Vec2 v) {
    Vec2 res;
    res.x = x + v.x;
    res.y = y + v.y;
    return res;
}

Vec2 Vec2::operator-(Vec2& v) {
    Vec2 res;
    res.x = x - v.x;
    res.y = y - v.y;
    return res;
}

Vec2 Vec2::operator*(Vec2& v) {
    Vec2 res;
    res.x = x * v.x - y * v.y;
    res.y = x * v.y + y * v.x;
    return res;
}

Vec2 Vec2::operator*(float lambda) {
    Vec2 res;
    res.x = x * lambda;
    res.y = y * lambda;
    return res;
}

bool Vec2::operator==(Vec2 v){
    return(x == v.x && y == v.y);
}

void Vec2::test() {
    Vec2 v1;
    assert(v1.getX() == 0);
    assert(v1.getY() == 0);
    
    Vec2 v2(2,4);
    assert(v2.getX() == 2);
    assert(v2.getY() == 4);

    Vec2 v3(v2);
    assert(v2.getX() == 2);
    assert(v2.getY() == 4);

    assert(v2.getX() == 2);
    assert(v3.getY() == 4);

    v3.setX(3);
    v3.setY(1);
    assert(v3.getX() == 3);
    assert(v3.getY() == 1);

    Vec2 v4;
    v4 = v2 + v3;
    assert(v4.getX() == v2.getX()+v3.getX());
    assert(v4.getY() == v2.getY()+v3.getY());
    v4 = v4 - v3;
    assert(v4.getX() == v2.getX());
    assert(v4.getY() == v2.getY());
    v4 = v2 * v3;
    assert(v4.getX() == v2.getX()*v3.getX()-v2.getY()*v3.getY());
    assert(v4.getY() == v2.getX()*v3.getY()+v3.getX()*v2.getY());

    v3 = v2 * 3;
    assert(v3.getX() == 3*v2.getX());
    assert(v3.getY() == 3*v2.getY());
    std::cout<<"test de regression vec 2 : ok"<<std::endl;
}
