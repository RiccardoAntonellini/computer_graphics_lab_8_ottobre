// ============================================================================
// ShapeGenerator.h - GUIDA DIDATTICA
// Interfaccia del generatore geometrico: produce MeshData senza creare risorse GPU.
// ============================================================================

#pragma once

#include "MeshData.h"

// ============================================================================
// ShapeGenerator
// Costruisce le forme sulla CPU. Nessuna chiamata OpenGL in questa classe.
//
// In questo template e' presente SOLO createTriangle().
// Le altre forme saranno aggiunte durante l'esercitazione.
// ============================================================================
class ShapeGenerator
{
// PUBLIC: funzioni statiche chiamabili senza creare un oggetto ShapeGenerator.
public:
    // Genera tre posizioni e tre colori sulla CPU e restituisce MeshData.
    // Ogni parametro e' un colore RGBA passato per riferimento costante.
    static MeshData createTriangle(
        const glm::vec4& color1,
        const glm::vec4& color2,
        const glm::vec4& color3
    );

    static MeshData createCircle(
        const float raggioX,
        const int precision
    );

    static MeshData createMoon(
        const int precision,
        const float scaleX,
        const float scaleY,
        const float shiftX,
        const float shiftY
    );

    static MeshData createHeart(
        const int precision,
        const float scaleX,
        const float scaleY,
        const float shiftX,
        const float shiftY
    );

    static MeshData createButterfly(
        const int precision,
        const float scaleX,
        const float scaleY,
        const float shiftX,
        const float shiftY
    );

    static MeshData createSierpinski(
        const glm::vec3& vert1,
        const glm::vec3& vert2,
        const glm::vec3& vert3,
        const int iterations,
        const glm::vec3& initialPos
    );
};
