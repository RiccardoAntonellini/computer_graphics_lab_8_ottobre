// ============================================================================
// main.cpp - GUIDA DIDATTICA
// Punto di ingresso: inizializza GLFW e GLAD, crea shader e scena, avvia il ciclo di rendering e rilascia le risorse.
// ============================================================================

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

#include "Shader.h"
#include "ShapeGenerator.h"
#include "Scene.h"
#include "Renderer.h"
#include "Gui.h"
#include "Input.h"

// Avvio del programma. Le risorse OpenGL vanno create solo dopo che esiste un contesto corrente.
int main()
{
    srand(time(NULL));

    // ========================================================================
    // 1. GLFW
    // ========================================================================

    if (!/* Inizializza GLFW prima di creare la finestra. */
    glfwInit())
    {
        std::cout << "Errore inizializzazione GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // ========================================================================
    // 2. FINESTRA
    // ========================================================================

    GLFWwindow* window = glfwCreateWindow(
        800,
        800,
        "OpenGL - Template classi",
        nullptr,
        nullptr
    );

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    // ========================================================================
    // 3. GLAD
    // ========================================================================

    if (!/* Carica le funzioni OpenGL dopo avere reso corrente il contesto. */
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Errore caricamento GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 800);


    // ========================================================================
    // 4. CALLBACK
    // ========================================================================

    glfwSetKeyCallback(window, Input::keyCallback);
    glfwSetCursorPosCallback(window, Input::cursorPositionCallback);
    glfwSetFramebufferSizeCallback(window, Input::framebufferSizeCallback);


    // ========================================================================
    // 5. SHADER
    // ========================================================================

    Shader shader;

    if (!shader.load(
        "shader/vertexshaderC.glsl",
        "shader/fragmentshaderC.glsl"))
    {
        std::cout << "Errore caricamento shader" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    shader.use();


    // ========================================================================
    // 6. SCENA, RENDERER E GUI
    // ========================================================================

    Scene scene;
    Renderer renderer;
    Gui gui;

    gui.initialize(window);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

    // ========================================================================
    // 7. TRIANGOLO
    // ========================================================================

    MeshData triangle = ShapeGenerator::createTriangle(
        glm::vec4(1.0f, 0.2f, 0.2f, 1.0f),
        glm::vec4(0.2f, 1.0f, 0.2f, 1.0f),
        glm::vec4(0.2f, 0.4f, 1.0f, 1.0f)
    );

    /* Inserisce una Geometry nella Scene e carica i dati sulla GPU. */
    scene.add(
        triangle,
        false
    );

    MeshData circle = ShapeGenerator::createCircle(
        0.15,
        3
    );

    std::size_t circleIdx = scene.add(
        circle,
        true
    );

    int preSegments = 3;

    MeshData moon = ShapeGenerator::createMoon(
        20,
        0.25,
        0.15,
        0.4,
        0.4
    );

    scene.add(
        moon,
        false
    );

    MeshData heart = ShapeGenerator::createHeart(
        14,
        0.0125,
        0.0125,
        -0.4,
        -0.4
    );

    std::size_t heartIdx = scene.add(
        heart,
        true
    );

    MeshData butterfly = ShapeGenerator::createButterfly(
        14,
        0.0625,
        0.0625,
        0.1,
        -0.3
    );

    scene.add(
        butterfly,
        false
    );

    MeshData sierpinsky = ShapeGenerator::createSierpinski(
        glm::vec3(-0.6f, -0.2f, 0.3f),
        glm::vec3(0.6f, -0.5f, 0.0f),
        glm::vec3(-0.1f, 0.9f, 0.2f),
        2000,
        glm::vec3(-0.6f, -0.2f, 0.3f)
    );

    scene.add(
        sierpinsky,
        false
    );

    // ========================================================================
    // 8. RENDER LOOP
    // ========================================================================

    // Ciclo dei frame: aggiorna i controlli, pulisce lo schermo, disegna la scena e presenta il risultato.
    while (!glfwWindowShouldClose(window))
    {
        double nowTime = glfwGetTime();

        float sinScaleX, sinScaleY;

        sinScaleX = sinScaleY = 0.0625f + 0.125f * sin(nowTime * 2.0f);

        MeshData updatedHeart = ShapeGenerator::createHeart(
            14,
            0.125f * sinScaleX,
            0.125f * sinScaleY,
            -0.4f,
            -0.4f
        );

        scene[heartIdx].updatePositions(updatedHeart.positions);

        int segments = gui.segment();

        if (segments != preSegments) {
            MeshData updatedCircle = ShapeGenerator::createCircle(
                0.15f,
                segments
            );

            scene[circleIdx].setData(updatedCircle.positions, updatedCircle.colors, GL_TRIANGLE_FAN);
            scene[circleIdx].upload(true);
            preSegments = segments;
        }
        

        /* Inizia il frame dell interfaccia prima di costruire i widget. */
        gui.beginFrame();
        gui.draw();

        renderer.beginFrame(gui.clearColor());
        renderer.setWireframe(gui.wireframe());

        shader.use();

        glPointSize(5.0);
        glLineWidth(10.0f);

        /* Il Renderer visita tutte le Geometry e ne richiama draw(). */
        renderer.drawScene(scene);

        // ImGui va disegnata in modalita' fill.
        renderer.setWireframe(false);

        /* Disegna la GUI sopra la scena OpenGL. */
        gui.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // ========================================================================
    // 9. CLEANUP
    // ========================================================================

    gui.shutdown();
    scene.clear();
    shader.destroy();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
