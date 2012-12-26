#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "actions.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void logText(QString text);
	void fixIfNeeded();

public slots:
	void startAutofix();
	void stopAutofix();
	void detectValues();
	void moveWindow();

	void timerUpdate();
	
private:
	Ui::MainWindow *ui;

	time_t logTime;
	char logTimeBuf[64];

	bool autofix;
	bool windowKnown;

	QTimer *timer;
};

#endif // MAINWINDOW_H
