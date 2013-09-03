//
//  Vector.hpp
//  OpenGL_ES_Test
//
//  Created by 王 瀚宇 on 13/9/3.
//  Copyright (c) 2013年 王 瀚宇. All rights reserved.
//

#ifndef OpenGL_ES_Test_Vector_hpp
#define OpenGL_ES_Test_Vector_hpp


#pragma once
#include <cmath>

template <typename T>
struct Vector2 {
    Vector2() {}
    Vector2(T x, T y) : x(x), y(y) {}
    T x;
    T y;
};

template <typename T>
struct Vector3 {
    Vector3() {}
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
    void Normalize()
    {
        float length = std::sqrt(x * x + y * y + z * z);
        x /= length;
        y /= length;
        z /= length;
    }
    Vector3 Normalized() const
    {
        Vector3 v = *this;
        v.Normalize();
        return v;
    }
    Vector3 Cross(const Vector3& v) const
    {
        return Vector3(y * v.z - z * v.y,
                       z * v.x - x * v.z,
                       x * v.y - y * v.x);
    }
    T Dot(const Vector3& v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }
    Vector3 operator-() const
    {
        return Vector3(-x, -y, -z);
    }
    bool operator==(const Vector3& v) const
    {
        return x == v.x && y == v.y && z == v.z;
    }
    T x;
    T y;
    T z;
};



typedef Vector2<int> ivec2;
typedef Vector3<int> ivec3;

typedef Vector2<float> vec2;
typedef Vector3<float> vec3;
#endif
