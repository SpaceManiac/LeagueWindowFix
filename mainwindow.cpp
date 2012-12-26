#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qtimer.h>
#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
	timer->start(1000);

	logText("League Window Fix starting");
	detectValues();
	startAutofix();

	windowKnown = checkWindow();
	if (!windowKnown) {
		logText("League of Legends not running, will monitor for it");
	} else {
		logText("League of Legends found");
		fixIfNeeded();
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::startAutofix() {
	autofix = true;
	ui->startAutofix->setEnabled(false);
	ui->stopAutofix->setEnabled(true);
}

void MainWindow::stopAutofix() {
	autofix = false;
	ui->startAutofix->setEnabled(true);
	ui->stopAutofix->setEnabled(false);
}

void MainWindow::detectValues() {
	int w, h;
	detectMonitorSize(&w, &h);

	// This is a kind of a weird way to itoa to me
	ui->windowX->setText("0");
	ui->windowY->setText("0");
	ui->windowW->setText(QString("%1").arg(w));
	ui->windowH->setText(QString("%1").arg(h));
}

void MainWindow::moveWindow() {
	if (!windowKnown) return;

	int x = ui->windowX->text().toInt();
	int y = ui->windowY->text().toInt();
	int w = ui->windowW->text().toInt();
	int h = ui->windowH->text().toInt();

	setPosition(x, y, w, h);
	logText(QString("Manually moved to %1,%2 %3x%4").arg(x).arg(y).arg(w).arg(h));
}

void MainWindow::timerUpdate() {
	bool check = checkWindow();

	if (check && !windowKnown) {
		logText("League of Legends has opened");
	} else if (!check && windowKnown) {
		logText("League of Legends has closed");
	}

	windowKnown = check;

	if (windowKnown && autofix) {
		fixIfNeeded();
	}
}

void MainWindow::fixIfNeeded() {
	int x, y, w, h, dw, dh;
	getPosition(&x, &y, &w, &h);
	detectMonitorSize(&dw, &dh);

	if (x != 0 || y != 0 || w != dw || h != dh) {
		setPosition(0, 0, dw, dh);
		logText(QString("Automatically fullscreened from %1,%2 %3x%4").arg(x).arg(y).arg(w).arg(h));
	}
}

void MainWindow::logText(QString text) {
	time(&logTime);
	strftime(logTimeBuf, 64, "[%H:%M:%S] ", localtime(&logTime));
	ui->logText->append(logTimeBuf + text);
}
