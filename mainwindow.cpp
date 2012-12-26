#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	logText("League Window Fix opened");
	detectValues();
	startAutofix();
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
	int x, y, w, h;

	// TODO
	x = y = 0;
	w = 1920;
	h = 1080;

	// This is a kind of a weird way to itoa to me
	ui->windowX->setText(QString("%1").arg(x));
	ui->windowY->setText(QString("%1").arg(y));
	ui->windowW->setText(QString("%1").arg(w));
	ui->windowH->setText(QString("%1").arg(h));
	logText(QString("Detected screen size %1x%2").arg(w).arg(h));
}

void MainWindow::moveWindow() {

	logText(QString("Moved window"));
}

void MainWindow::logText(QString text) {
	time(&logTime);
	strftime(logTimeBuf, 64, "[%H:%M:%S] ", localtime(&logTime));
	ui->logText->append(logTimeBuf + text);
}
