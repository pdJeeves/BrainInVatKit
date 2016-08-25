#include "colorview.h"


ColorView::ColorView(QWidget * parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
}

ColorView::~ColorView()
{

}

void ColorView::draw(QColor color)
{
	qglClearColor(color);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
