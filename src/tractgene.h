#ifndef TractSettings_H
#define TractSettings_H
#include "brainmodel.h"
#include <QMainWindow>

namespace Ui {
class TractSettings;
}

class QSlider;
class QLabel;

class TractSettings : public QMainWindow
{
typedef QMainWindow super;
	Q_OBJECT
private:
	LobeModel  * lobe;
	MainWindow * ownr;
	TractModel * original;

	static void rangeChanged(QSlider * a, QSlider * b, int width);

	TractData getData();

public:
	explicit TractSettings(MainWindow * parent, TractModel * tract = 0L, LobeModel * lobe = 0L);
	~TractSettings();

	void lobe_list_updated();
	void tract_list_updated();

	void updateSliders(int i);
	void setLabelWidths();

public slots:
	void onOriginLobeSelected(int i);
	void onDataSourceSelected(int i);
	void FlatChecked(bool enabled);
	void closeEvent(QCloseEvent * event);
	void onClosePushed();
	void onTextEdited();

private:
	void setFiring(LobeModel * it);
	bool can_close() const;
	void reset_data_source(int min, int max, int length);
	void reset_origin_lobe(int min, int max, int length);
	
	Ui::TractSettings *ui;
};

#endif // TractSettings_H
