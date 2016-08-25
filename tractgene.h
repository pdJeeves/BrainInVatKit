#ifndef TractSettings_H
#define TractSettings_H
#include "brainmodel.h"
#include <QMainWindow>

namespace Ui {
class TractSettings;
}

class TractSettings : public QMainWindow
{
typedef QMainWindow super;
	Q_OBJECT
private:
	LobeModel  * lobe;
	MainWindow * ownr;
	TractModel * original;

	TractData getData();

public:
	explicit TractSettings(MainWindow * parent, TractModel * tract = 0L, LobeModel * lobe = 0L);
	~TractSettings();

	void lobe_list_updated();
	void tract_list_updated();

public slots:
	void onOriginLobeSelected(int i);
	void onDataSourceSelected(int i);
	void closeEvent(QCloseEvent * event);
	void onClosePushed();
	void onTextEdited();

	void MinAddChanged(int);
	void MaxAddChanged(int);
	void MinStrChanged(int);
	void MaxStrChanged(int);
	void MinLtwChanged(int);
	void MaxLtwChanged(int);
	void RelaxLtwChanged(int);
	void RelaxStwChanged(int);
	void FirstSourceChanged(int);
	void LastSourceChanged(int);
	void FirstDestChanged(int);
	void LastDestChanged(int);
	void FlatChecked(bool enabled);
	void RelaxStateChanged(int);
	void RelaxSusceptChanged(int);
	void RelaxStrChanged(int);
	void SynapsesChanged(int);

private:
	void setFiring(LobeModel * it);
	bool can_close() const;
	void reset_data_source(int min, int max, int length);
	void reset_origin_lobe(int min, int max, int length);
	
	Ui::TractSettings *ui;
};

#endif // TractSettings_H
