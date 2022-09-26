#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);
	m_view.setCenter(0, 0);
	m_zoomCount = 0;
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	int x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	int y = -BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(x, y);
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	int x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	int y = -BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(x, y);
}

void ComplexPlane::setCenter(Vector2f coord)
{
	m_view.setCenter(coord);
}

View ComplexPlane::getView()
{
	return m_view;
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
	m_mouseLocation = coord;
}

void ComplexPlane::loadText(Text& text)
{
	stringstream strStream;

	strStream << "Mandelbrot Set" << endl
		<< "Center: (" << m_view.getCenter().x << "," << m_view.getCenter().y << ")" << endl
		<< "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << endl
		<< "Left-click to Zoom in" << endl << "Right-click to Zoom out";

	text.setString(strStream.str());
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
	double re = coord.x;
	double im = coord.y;

	complex<double> c(re, im);
	complex<double> z(0, 0);

	int iterations = 0;
	while (iterations < MAX_ITER && abs(z) < 2.0)
	{
		z = z * z + c;
		iterations++;
	}

	return iterations;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count >= MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else if (count >= (MAX_ITER / 2.0))
	{
		r = 51;
		g = 51;
		b = 51;
	}
	else if (count >= (MAX_ITER / 3.0))
	{
		r = 115;
		g = 115;
		b = 115;
	}
	else if (count >= (MAX_ITER / 4.0))
	{
		r = 179;
		g = 179;
		b = 179;
	}
	else if (count >= (MAX_ITER / 5.0))
	{
		r = 204;
		g = 204;
		b = 204;
	}
	else
	{
		r = 217;
		g = 217;
		b = 217;
	}
}
