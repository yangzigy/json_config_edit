#include "cfgwindow.h"
#include "ui_cfgwindow.h"
#include <QDebug>
#include <QFont>
#include <QInputDialog>
#include "qthttp.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::ui_initial()
{
	ui->le_url->setText(config.get("dft_url","127.0.0.1:1081").asString().c_str());
	try
	{
		pdict=new CDictDis(config["cfg_array"],ui->scrollAreaWidgetContents);
	}
	catch(...)
	{
		exit(1);
	}
}

void MainWindow::on_bt_getfromhttp_clicked(void) //获取配置
{
	string surl=ui->le_url->text().toStdString();
	HttpFun http;
	QByteArray qbuf=http.httpget(surl.c_str());
	if(qbuf.size()>0)
	{
		Json::Value v;
		Json::Reader reader;
		reader.parse(qbuf.data(),v,false); //可以有注释,false不会复制
		pdict->setData(v);
	}
	else
	{
		QMessageBox::information(0,"error","获取失败");
	}
}
void MainWindow::on_bt_openfile_clicked(void) //从文件获取配置
{
	auto name=QFileDialog::getOpenFileName(0,"","","配置文件(*.txt)");
	if(name!="")
	{
		string s=read_textfile(name.toStdString().c_str());
		if(s!="")
		{
			Json::Value v;
			Json::Reader reader;
			reader.parse(s.c_str(),v,false); //可以有注释,false不会复制
			pdict->setData(v);
		}
	}
}

void MainWindow::on_bt_save_file_clicked()//保存文件配置
{
	//创建路径保存文件
	QDir *Dir = new QDir;
	bool exit = Dir->exists("./");
	if(!exit)
	{
		Dir->mkdir("./");
	}
	bool ok = FALSE;
	QString text = QInputDialog::getText(this,"保存文件","请输入文件名:",QLineEdit::Normal,"",&ok);
	if(ok && !text.isEmpty())
	{
		if(text!="")
		{
			QString ts = "./";
			text = ts+text+".json";
		}
	}
	Json::Value tmp_json;
	pdict->getData(tmp_json);
	Json::StyledWriter writer;
	string s=writer.write(tmp_json);
	CComFile cf;
	string str = text.toStdString();
	cf.open(str.c_str(),"w");
	cf.write((void*)s.c_str(),s.size());
	cf.close();
}

void MainWindow::on_bt_upload_cfg_clicked() //上传配置
{
	Json::Value tmp_json;
	pdict->getData(tmp_json);
	Json::StyledWriter writer;
	string s=writer.write(tmp_json);
	string surl=ui->le_url->text().toStdString();
	HttpFun http;
	http.httppost(surl.c_str(),(u8*)s.c_str(),s.size());
}
