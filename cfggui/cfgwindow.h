#ifndef CFGWINDOW_H
#define CFGWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>
#include <QFileDialog>
#include "json.h"
#include "common.h"
#include <QLayout>
#include <QLineEdit>
#include <QDebug>
#include <QMessageBox>
#include "dictdis.h"

namespace Ui {
class MainWindow;
}

extern Json::Value config;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void ui_initial();
	CDictDis *pdict=0;
public slots:
	void on_bt_getfromhttp_clicked(void);
	void on_bt_openfile_clicked(void);
	void on_bt_save_file_clicked();

private slots:
	void on_bt_upload_cfg_clicked();

private:
	Ui::MainWindow *ui;
};

#endif // CFGWINDOW_H

