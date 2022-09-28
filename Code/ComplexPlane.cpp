#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);
	m_view.setCenter(0, 0);
	m_zoomCount = 0;
	totalMaxIterations = MAX_ITER;
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	double x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	double y = -BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(x, y);
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	double x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	double y = -BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
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
		<< "Max Iterations: " << totalMaxIterations << endl
		<< "Zooming power: " << m_zoomCount << endl
		<< "Left-click to Zoom in" << endl << "Right-click to Zoom out" << endl
		<< "Press Up-Arrow key to increase max iterations" << endl
		<< "Press Down-Arrow key to decrease max iterations" << endl
		<< "Press R to redraw" << endl;

	text.setString(strStream.str());
}

void ComplexPlane::setTotalMaxIterations(int additionalMaxIterations)
{
	totalMaxIterations = MAX_ITER + additionalMaxIterations;
}

size_t ComplexPlane::countIterations(Vector2f coord, int additionalMaxIterations)
{
	double re = coord.x;
	double im = coord.y;

	int totalMaxIter = MAX_ITER + additionalMaxIterations;

	complex<double> c(re, im);
	complex<double> z(0, 0);

	int iterations = 0;
	while (iterations < totalMaxIter && abs(z) < 2.0)
	{
		z = z * z + c;
		iterations++;
	}

	return iterations;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b, int additionalMaxIterations)
{
	Color color0(0, 0, 0);
	Color color1(254, 39, 18);
	Color color2(247, 247, 212);
	Color color3(254, 254, 51);
	Color color4(134, 1, 175);
	Color color5(2, 71, 254);
	Color color6(68, 36, 214);
	Color color7(146, 20, 184);
	Color color8(42, 9, 52);

	int totalMaxIter = MAX_ITER + additionalMaxIterations;

	if (count >= totalMaxIter)
	{
		r = color0.r;
		g = color0.g;
		b = color0.b;
	}
	else if (count >= totalMaxIter / 2.0)
	{
		r = color1.r;
		g = color1.g;
		b = color1.b;
	}
	else if (count >= totalMaxIter / 4.0)
	{
		r = color2.r;
		g = color2.g;
		b = color2.b;
	}
	else if (count >= totalMaxIter / 5.0)
	{
		r = color3.r;
		g = color3.g;
		b = color3.b;
	}
	else if (count >= totalMaxIter / 8.0)
	{
		r = color4.r;
		g = color4.g;
		b = color4.b;
	}
	else if (count >= totalMaxIter / 10.0)
	{
		r = color5.r;
		g = color5.g;
		b = color5.b;
	}
	else if (count >= totalMaxIter / 15.0)
	{
		r = color6.r;
		g = color6.g;
		b = color6.b;
	}
	else if (count >= totalMaxIter / 24.0)
	{
		r = color7.r;
		g = color7.g;
		b = color7.b;
	}
	else
	{
		r = color8.r;
		g = color8.g;
		b = color8.b;
	}
}