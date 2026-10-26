// ============================================================================
// ShapeGenerator.cpp - GUIDA DIDATTICA
// Costruzione del triangolo sulla CPU: associa una posizione e un colore a ogni vertice.
// ============================================================================

#include "ShapeGenerator.h"
#include <cmath>
#include <ctime>

const float PI = 3.1415926535;

// La funzione restituisce per valore un MeshData. I tre vertici sono in coordinate locali e hanno colori corrispondenti.
MeshData ShapeGenerator::createTriangle(
    const glm::vec4& color1,
    const glm::vec4& color2,
    const glm::vec4& color3)
{
    MeshData data;

    // Inseriamo i vertici uno alla volta: push_back aggiunge un elemento
    // alla fine del vector delle posizioni.
    // P0: vertice inferiore sinistro.
    data.positions.push_back(glm::vec3(-0.6f, -0.5f, 0.0f));

    // P1: vertice inferiore destro.
    data.positions.push_back(glm::vec3( 0.6f, -0.5f, 0.0f));

    // P2: vertice superiore.
    data.positions.push_back(glm::vec3( 0.0f,  0.6f, 0.0f));

    // Ogni colore ha lo stesso indice del vertice corrispondente.
    data.colors.push_back(color1);  // Colore del vertice P0.
    data.colors.push_back(color2);  // Colore del vertice P1.
    data.colors.push_back(color3);  // Colore del vertice P2.

    data.primitiveType = GL_TRIANGLES;

    return data;
}

MeshData ShapeGenerator::createCircle(
    const float raggioX,
    const int precision
) {

    MeshData data;
    data.primitiveType = GL_TRIANGLE_FAN;

    float x, y;

    data.positions.reserve(precision);
    data.colors.reserve(precision);

    float stepA = (2 * PI) / precision;
    for (int i = 0; i < precision; ++i)
    {
        double t = (double)i * stepA;
        x = cos(t) * raggioX;
        y = sin(t) * raggioX;

        glm::vec3 pos = glm::vec3(x, y, 0.0f);
        data.positions.push_back(pos);
        data.colors.push_back(glm::vec4(0.55f, 0.12f, 0.83f, 0.1f));
    }

    return data;
}

MeshData ShapeGenerator::createMoon(
    const int precision,
    const float scaleX,
    const float scaleY,
    const float shiftX,
    const float shiftY
) {

    MeshData data;
    data.primitiveType = GL_TRIANGLE_FAN;

    float x, y;
    int nPoints;

    if (precision <= 0) {
        nPoints = 10;
    }
    else {
        nPoints = precision;
    }

    data.positions.reserve(nPoints);
    data.colors.reserve(nPoints);

    float stepA = (2 * PI) / nPoints;
    for (int i = 0; i < nPoints; ++i)
    {
        double t = (double)i * stepA;
        x = scaleX * 3.0 * sin(t);
        y = scaleY * (0.5 - cos(2.0 * t) - cos(t));

        //posizionamento nella scena
        x += shiftX;
        y += shiftY;

        glm::vec3 pos = glm::vec3(x, y, 0.0f);
        data.positions.push_back(pos);
        data.colors.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    }

    return data;
}

MeshData ShapeGenerator::createHeart(
    const int precision,
    const float scaleX,
    const float scaleY,
    const float shiftX,
    const float shiftY
) {

    MeshData data;
    data.primitiveType = GL_TRIANGLE_FAN;

    float x, y;
    int nPoints;

    if (precision <= 0) {
        nPoints = 10;
    }
    else {
        nPoints = precision;
    }

    data.positions.reserve(nPoints);
    data.colors.reserve(nPoints);

    float stepA = (2 * PI) / nPoints;
    for (int i = 0; i < nPoints; ++i)
    {
        double t = (double)i * stepA;
        x = scaleX * (16.0 * pow(sin(t), 3));
        y = scaleY * (13.0 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t));

        //posizionamento nella scena
        x += shiftX;
        y += shiftY;

        glm::vec3 pos = glm::vec3(x, y, 0.0f);
        data.positions.push_back(pos);
        data.colors.push_back(glm::vec4(0.0f, 0.7f, 0.3f, 0.3f));
    }

    return data;
}

MeshData ShapeGenerator::createButterfly(
    const int precision,
    const float scaleX,
    const float scaleY,
    const float shiftX,
    const float shiftY
) {

    MeshData data;
    data.primitiveType = GL_TRIANGLE_FAN;

    float x, y;
    int nPoints;

    if (precision <= 0) {
        nPoints = 10;
    }
    else {
        nPoints = precision;
    }

    data.positions.reserve(nPoints);
    data.colors.reserve(nPoints);

    float stepA = (2 * PI) / nPoints;
    for (int i = 0; i < nPoints; ++i)
    {
        double t = (double)i * stepA;
        x = scaleX * sin(t) * (exp(cos(t)) - 2 * cos(4 * t) - pow(sin(t / 12.0f), 5));

        y = scaleY * cos(t) * (exp(cos(t)) - 2 * cos(4 * t) - pow(sin(t / 12.0f), 5));

        //posizionamento nella scena
        x += shiftX;
        y += shiftY;

        glm::vec3 pos = glm::vec3(x, y, 0.0f);
        data.positions.push_back(pos);
        data.colors.push_back(glm::vec4(0.1f, 0.55f, 0.5f, 1.0f));
    }

    return data;
}

MeshData ShapeGenerator::createSierpinski(
    const glm::vec3& vert1,
    const glm::vec3& vert2,
    const glm::vec3& vert3,
    const int iterations,
    const glm::vec3& initialPos // viene passato sempre e solo vert1
) {
    glm::vec3 baseVertices[] = { vert1, vert2, vert3 };

    MeshData data;
    data.primitiveType = GL_POINTS;
    data.positions.reserve(iterations + 3);

    data.positions.push_back(vert1);
    data.positions.push_back(vert2);
    data.positions.push_back(vert3);
    data.colors.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    data.colors.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    data.colors.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    glm::vec3 actualPos = initialPos;

    for (int i = 0; i < iterations; i++) {

        int whichVec = rand() % (3);

        glm::vec3 vert = baseVertices[whichVec];

        glm::vec3 pos1 = glm::vec3(0.5f * (actualPos + vert));

        data.positions.push_back(pos1);
        data.colors.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        actualPos = pos1;
    }

    return data;
}