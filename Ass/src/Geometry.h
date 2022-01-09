#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "Vertex.h"

struct Triangle
{
    // indices of a triangle
    unsigned int vertex[3];
};

namespace cube
{
    const float X = 0.5f;
    const float Y = 0.5f;
    const float Z = 0.5f;
    const float N = 1.0f;

    static const std::vector<Vertex> vertices =
    {
        {glm::vec3(-X, -Y,  Z), glm::vec3(0.0, 0.0,  N)},
        {glm::vec3( X, -Y,  Z), glm::vec3(0.0, 0.0,  N)},
        {glm::vec3( X,  Y,  Z), glm::vec3(0.0, 0.0,  N)},
        {glm::vec3(-X,  Y,  Z), glm::vec3(0.0, 0.0,  N)},

        {glm::vec3(-X, -Y, -Z), glm::vec3(0.0, 0.0, -N)},
        {glm::vec3(-X,  Y, -Z), glm::vec3(0.0, 0.0, -N)},
        {glm::vec3( X,  Y, -Z), glm::vec3(0.0, 0.0, -N)},
        {glm::vec3( X, -Y, -Z), glm::vec3(0.0, 0.0, -N)},

        {glm::vec3(-X,  Y, -Z), glm::vec3(0.0,  N, 0.0)},
        {glm::vec3(-X,  Y,  Z), glm::vec3(0.0,  N, 0.0)},
        {glm::vec3( X,  Y,  Z), glm::vec3(0.0,  N, 0.0)},
        {glm::vec3( X,  Y, -Z), glm::vec3(0.0,  N, 0.0)},

        {glm::vec3(-X, -Y, -Z), glm::vec3(0.0, -N, 0.0)},
        {glm::vec3( X, -Y, -Z), glm::vec3(0.0, -N, 0.0)},
        {glm::vec3( X, -Y,  Z), glm::vec3(0.0, -N, 0.0)},
        {glm::vec3(-X, -Y,  Z), glm::vec3(0.0, -N, 0.0)},

        {glm::vec3( X, -Y, -Z), glm::vec3( N, 0.0, 0.0)},
        {glm::vec3( X,  Y, -Z), glm::vec3( N, 0.0, 0.0)},
        {glm::vec3( X,  Y,  Z), glm::vec3( N, 0.0, 0.0)},
        {glm::vec3( X, -Y,  Z), glm::vec3( N, 0.0, 0.0)},

        {glm::vec3(-X, -Y, -Z), glm::vec3(-N, 0.0, 0.0)},
        {glm::vec3(-X, -Y,  Z), glm::vec3(-N, 0.0, 0.0)},
        {glm::vec3(-X,  Y,  Z), glm::vec3(-N, 0.0, 0.0)},
        {glm::vec3(-X,  Y, -Z), glm::vec3(-N, 0.0, 0.0)}
    };

    //static const std::vector <Triangle> triangles =
    //{
    //    // front
    //    {0,  1,  2},
    //    {0,  2,  3},

    //    // back
    //    {4,  5,  6},
    //    {4,  7,  6},

    //    // top
    //    {8,  9,  10},
    //    {8,  10, 11},

    //    // bottom
    //    {12, 14, 13},
    //    {12, 15, 14},

    //    // right
    //    {16, 17, 18},
    //    {16, 18, 19},

    //    // left
    //    {20, 22, 21},
    //    {20, 23, 22}
    //};

    static const std::vector <unsigned int> triangles =
    {
        // front
        0,  1,  2,
        0,  2,  3,

        // back
        4,  5,  6,
        4,  7,  6,

        // top
        8,  9,  10,
        8,  10, 11,

        // bottom
        12, 14, 13,
        12, 15, 14,

        // right
        16, 17, 18,
        16, 18, 19,

        // left
        20, 22, 21,
        20, 23, 22
    };
}

namespace icosahedron
{
	const float X = 0.525731f;
	const float Z = 0.850651f;
	const float N = 0.0f;

	static const std::vector<Vertex_P> vertices =
	{
        {glm::vec3(-X,  N,  Z)},
        {glm::vec3( X,  N,  Z)},
        {glm::vec3(-X,  N, -Z)},
        {glm::vec3( X,  N, -Z)},

        {glm::vec3( N,  Z,  X)},
        {glm::vec3( N,  Z, -X)},
        {glm::vec3( N, -Z,  X)},
        {glm::vec3( N, -Z, -X)},

        {glm::vec3( Z,  X,  N)},
        {glm::vec3(-Z,  X,  N)},
        {glm::vec3( Z, -X,  N)},
        {glm::vec3(-Z, -X,  N)}
	};

    static const std::vector<unsigned int> triangles =
    {
        0,  4,  1,
        0,  9,  4,
        9,  5,  4,
        4,  5,  8,
        4,  8,  1,

        8,  10, 1,
        8,  3,  10,
        5,  3,  8,
        5,  2,  3,
        2,  7,  3,

        7,  10, 3,
        7,  6,  10,
        7,  11, 6,
        11, 0,  6,
        0,  1,  6,

        6,  1,  10,
        9,  0,  11,
        9,  11, 2,
        9,  2,  5,
        7,  2,  11
    };
}