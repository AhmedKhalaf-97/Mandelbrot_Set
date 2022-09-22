#ifndef COMPLEXPLANE
#define COMPLEXPLANE

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
using namespace sf;

class ComplexPlane
{
private:
	Vector2f m_mouseLocation;
	View m_view;
	int m_zoomCount;
	float m_aspectRation;

public:
	ComplexPlane(float aspectRatio);
	void zoomIn();
	void zoomOut();
	void setCenter(Vector2f coord);
	View getView();
	void setMouseLocation(Vector2f coord);
	void loadText(Text& text);
	static size_t countIterations(Vector2f coord);
	static void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
};

#endif // !COMPLEXPLANE