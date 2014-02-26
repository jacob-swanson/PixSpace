#include <cmath>
#include "vector.h"

Vector::Vector()
{
    // Initialize null vector
    this->x = 0.0;
    this->y = 0.0;
}

Vector::Vector(double x, double y)
{
    // Initialize a vector with given values
    this->x = x;
    this->y = y;
}

Vector Vector::normalized() const
{
    // Return a normalized copy of this vector
    // A normal vector will have a magnitude of 1

    double length = this->length();

    // Handle special case
    if (length == 0) {
        return Vector(0,0);
    }

    double x = this->x / length;
    double y = this->y / length;

    Vector result(x,y);
    return result;
}

double Vector::length() const
{
    // Compute the magnitude, sqrt(x^2 + y^2)
    double x = this->x * this->x;
    double y = this->y * this->y;

    double length = sqrt(x + y);
    return length;
}

double Vector::getX() const
{
    // Return x components
    return this->x;
}

double Vector::getY() const
{
    // Return y component
    return this->y;
}

void Vector::setX(double x)
{
    // Set the x component
    this->x = x;
}

void Vector::setY(double y)
{
    // Set the y component
    this->y = y;
}

Vector Vector::operator+(const Vector& right) const
{
    // Addition
    return this->add(right);
}

Vector Vector::operator-(const Vector& right) const
{
    // Subtraction
    return this->sub(right);
}

Vector Vector::operator*(const double& factor) const
{
    // Multiply by number
    return this->multiplyByFactor(factor);
}

Vector Vector::operator/(const double& factor) const
{
    // Divide by number
    return this->divideByFactor(factor);
}

Vector& Vector::operator+=(const Vector& right)
{
    // Add assignment
    this->x += right.getX();
    this->y += right.getY();

    return *this;
}

Vector& Vector::operator-=(const Vector& right)
{
    // Subtract assignment
    this->x -= right.getX();
    this->y -= right.getY();

    return *this;
}

Vector& Vector::operator*=(const double& right)
{
    // Multiplication assignment
    this->x *= right;
    this->y *= right;

    return *this;
}

Vector& Vector::operator/=(const double& right)
{
    // Divide assignment
    this->x /= right;
    this->y /= right;

    return *this;
}

bool Vector::operator==(const Vector& right) const
{
    // Equals comparison, all elements equal
    if (this->x == right.getX() && this->y == right.getY())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Vector::operator!=(const Vector& right) const
{
    // Not equals comparison, one element different
    if (this->x != right.getX() || this->y != right.getY())
    {
        return true;
    }
    else
    {
        return false;
    }
}

Vector Vector::multiplyByFactor(const double& factor) const
{
    // Multiply by a scalar and return new Vector
    double x = this->x * factor;
    double y = this->y * factor;

    Vector result(x, y);
    return result;
}

Vector Vector::divideByFactor(const double& factor) const
{
    // Divide by a scalar and return new Vector
    double x = this->x / factor;
    double y = this->y / factor;

    Vector result(x, y);
    return result;
}

Vector Vector::add(const Vector& right) const
{
    // Add and return new Vector
    double x = this->x + right.getX();
    double y = this->y + right.getY();

    Vector result(x, y);
    return result;
}

Vector Vector::sub(const Vector& right) const
{
    // Subtract and return new vector
    double x = this->x - right.getX();
    double y = this->y - right.getY();

    Vector result(x, y);
    return result;
}

void Vector::read(const QJsonObject &json)
{
    this->setX(json["x"].toDouble());
    this->setY(json["y"].toDouble());
}

void Vector::write(QJsonObject &json) const
{
    json["x"] = this->x;
    json["y"] = this->y;
}

