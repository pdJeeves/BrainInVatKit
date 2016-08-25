#ifndef COLORVIEW_H
#define COLORVIEW_H
#include <QGLWidget>

class ColorView : public QGLWidget
{
	Q_OBJECT

public:
	explicit ColorView(QWidget *parent = 0);

	~ColorView();

public slots:
	void initializeGL()
	{
		qglClearColor(Qt::black);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glTranslatef(0.0, 0.0, -10.0);
	}
	void paintGL() { }
	void resizeGL() { }
	void draw(QColor color);

};

#endif // COLORVIEW_H
