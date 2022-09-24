#include <SFML/Graphics.hpp>
#include <iostream>
#include "ComplexPlane.h"

using namespace std;
using namespace sf;


int main()
{
    int screenWidth = VideoMode::getDesktopMode().width;
    int screenHeight = VideoMode::getDesktopMode().height;
    float aspectRatio = screenHeight / (float)screenWidth;

    int screenRes_X = 1920;
    int screenRes_Y = 1080;

	RenderWindow window(VideoMode(screenRes_X, screenRes_Y), "Mandelbrot Set", Style::Default);

    // Change the displayed cursor.
    Cursor cursor;
    if (cursor.loadFromSystem(Cursor::Arrow))
    {
        window.setMouseCursor(cursor);
    }

    ComplexPlane complexPlane(aspectRatio);

    Font font;
    font.loadFromFile("Fonts/sf-atarian-system.regular.ttf");

    Text text;

    int points_vertexCount = screenWidth * screenHeight;
    VertexArray points(Points);
    points.resize(points_vertexCount);

    enum ProgramState
    {
        CALCULATING,
        DISPLAYING
    };

    ProgramState currentProgramState = ProgramState::CALCULATING;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            // This event is triggered when the user wants to close the window,
            // through any of the possible methods the window manager provides (Alt + F4).
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed)
            {
                Vector2i mousePosition = Vector2i(event.mouseButton.x, event.mouseButton.y);
                Vector2f coord = window.mapPixelToCoords(mousePosition, complexPlane.getView());

                if (event.mouseButton.button == Mouse::Right)
                {
                    complexPlane.zoomOut();
                    complexPlane.setCenter(coord);
                }

                if (event.mouseButton.button == Mouse::Left)
                {
                    complexPlane.zoomIn();
                    complexPlane.setCenter(coord);
                }

                currentProgramState = ProgramState::CALCULATING;
            }

            if (event.type == Event::MouseMoved)
            {
                Vector2i mousePosition = Vector2i(event.mouseMove.x, event.mouseMove.y);
                Vector2f coord = window.mapPixelToCoords(mousePosition, complexPlane.getView());

                complexPlane.setMouseLocation(coord);
            }
        }

        // Close the game window if the user pressed the Escape button.
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if (currentProgramState == ProgramState::CALCULATING)
        {
            for (int j = 0; j < screenWidth; j++)
            {
                for (int i = 0; i < screenHeight; i++)
                {
                    //cout << "(" << j << ", " << i << ")" << endl;
                    points[j + i * screenWidth].position = {(float)j, (float)i};

                    Vector2f coord = window.mapPixelToCoords(Vector2i(j, i), complexPlane.getView());

                    int iterationsCount = complexPlane.countIterations(coord);

                    Uint8 r, g, b;

                    complexPlane.iterationsToRGB(iterationsCount, r, g, b);

                    points[j + i * screenWidth].color = {r, g, b};

                    currentProgramState = ProgramState::DISPLAYING;

                    complexPlane.loadText(text);
                }
            }
        }

        window.clear();
        window.draw(points);
        window.draw(text);
        window.display();
    }

    return 0;
}