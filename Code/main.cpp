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

    VertexArray points(Points);
    int points_vertexCount = screenWidth * screenHeight;
    points.resize(points_vertexCount);

    enum ProgramState
    {
        CALCULATING,
        DISPLAYING
    };

    ProgramState currentProgramState = ProgramState::CALCULATING;

    while (window.isOpen())
    {
        // Close the game window if the user pressed the Escape button.
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        window.clear();
        //window.draw();
        window.display();
    }

    return 0;
}