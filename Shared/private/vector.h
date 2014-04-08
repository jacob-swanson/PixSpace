#ifndef VECTOR_H
#define VECTOR_H

#include <QJsonObject>
#include <cmath>

#include "shared_global.h"

/**
 * @brief The Vector class Base 2D vector implemented using doubles
 */
class SHAREDSHARED_EXPORT Vector
{
public:
    /**
     * @brief Vector Create null vector, (0.0,0.0)
     */
    Vector();

    /**
     * @brief Vector Create a vector with the given values
     * @param x
     * @param y
     */
    Vector(double x, double y);

    /**
     * @brief normalized Return a normalized copy of the vector
     * @return
     */
    Vector normalized() const;

    /**
     * @brief length Return the magnitude of the vector
     * @return
     */
    double length() const;

    /**
     * @brief getX Get the x value
     * @return
     */
    double getX() const;

    /**
     * @brief getY Get the y value
     * @return
     */
    double getY() const;

    /**
     * @brief setX Set the value of x
     * @param x
     */
    void setX(double x);

    /**
     * @brief setY Set the value of y
     * @param y
     */
    void setY(double y);

    // Arithmetic operators
    Vector operator+(const Vector& right) const;
    Vector operator-(const Vector& right) const;
    Vector operator*(const double& factor) const;
    Vector operator/(const double& factor) const;

    // Compoud assignment operators
    Vector& operator+=(const Vector& right);
    Vector& operator-=(const Vector& right);
    Vector& operator*=(const double& right);
    Vector& operator/=(const double& right);

    // Relational and comparison operators
    bool operator==(const Vector& right) const;
    bool operator!=(const Vector& right) const;

    /**
     * @brief read Read in from the given JSON object
     * @param json
     */
    void read(const QJsonObject &json);

    /**
     * @brief write Write to the given JSON object
     * @param json
     */
    void write(QJsonObject &json) const;

private:
    double x, y;

    // Helper functions
    Vector multiplyByFactor(const double& factor) const;
    Vector divideByFactor(const double& factor) const;
    Vector add(const Vector& right) const;
    Vector sub(const Vector& right) const;
};

#endif // VECTOR_H
