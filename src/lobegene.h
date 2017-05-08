#ifndef LOBEGENE_H
#define LOBEGENE_H
#include "colorwidget.h"
#include "mainwindow.h"
#include "lobemodel.h"
#include <QMainWindow>

namespace Ui {
class LobeSettings;
}

class LobeSettings : public QMainWindow
{
typedef QMainWindow super;

	Q_OBJECT
private:
	MainWindow * ownr;
	LobeModel  * original;
	
public:
	explicit LobeSettings(MainWindow * ownr, LobeModel * data);
	~LobeSettings();

public slots:
	void closeEvent(QCloseEvent * event);
	void onClosePushed();
	void onSelectColor();
	void onTextEdited();

	void onRelaxPrev(int i);
	void onRelaxState(int i);

private:
	bool can_close() const;
	Ui::LobeSettings *ui;
};

#endif // LOBEGENE_H
