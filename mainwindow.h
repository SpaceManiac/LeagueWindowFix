#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void startAutofix();
	void stopAutofix();
	void detectValues();
	void moveWindow();

	void logText(QString text);
	
private:
	Ui::MainWindow *ui;

	time_t logTime;
	char logTimeBuf[64];

	bool autofix;
};

#endif // MAINWINDOW_H
