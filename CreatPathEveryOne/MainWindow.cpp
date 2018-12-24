#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QUrl>
#include <QTextCodec>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //pro.setProcessChannelMode(QProcess::SeparateChannels);
    connect(&pro,SIGNAL(finished(int)),this,SLOT(extFinished(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::isDirExist(QString fullPath)
{
    QDir dir(fullPath);
    if(dir.exists())
    {
      return true;
    }
    else
    {
       bool ok = dir.mkpath(fullPath);
       return ok;
    }
}

void MainWindow::on_StartProcess_clicked()
{
    pro.start("cacls.exe", QStringList()<< fullDirPath
              << "/e" << "/g"
              << "EveryOne:F");
    if (!pro.waitForStarted())
         qDebug() << "error start!";
}

void MainWindow::on_OpenDir_clicked()
{
    qDebug()<<fullDirPath;
    QDesktopServices::openUrl(QUrl("file:///"+fullDirPath, QUrl::TolerantMode));
}

void MainWindow::on_toolButton_clicked()
{
    QString tempDir;
    tempDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                      "/home",
                                      QFileDialog::ShowDirsOnly
                                      | QFileDialog::DontResolveSymlinks);
    qDebug()<<tempDir;
    if(tempDir != ""){
        fullDirPath = tempDir;
        ui->StartProcess->setEnabled(true);
    }else{
        ui->StartProcess->setEnabled(false);
    }
}

void MainWindow::on_CreatDir_clicked()
{
    ui->textBrowser->append(QString("*********************************************"));
    if(fullDirPath == ""){
        ui->textBrowser->append(QString("Empty Folder!"));
        return ;
    }else{
        ui->textBrowser->append(QString("Correct Folder:"));
        ui->textBrowser->append("\t"+fullDirPath);
    }
    if(isDirExist(fullDirPath)){
        ui->textBrowser->append(QString("Creat Folder success or Folder already exist!"));
    }else{
        ui->textBrowser->append(QString("Argument Error,Please check Folder format!"));
    }
    ui->textBrowser->append(QString("-----------------------------------------------"));
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void MainWindow::extFinished(int index)
{
    if(0 == index){
        ui->textBrowser->append(QString("Add User:"));
        ui->textBrowser->append(QString("\t Everyone"));
        ui->textBrowser->append(QString("Result:"));
        ui->textBrowser->append(QString("\t Successed"));
        ui->textBrowser->append(QString(""));
        ui->textBrowser->append(QString("Execute Successed!"));
        ui->textBrowser->append(QString("Please Open Folder check the jurisdiction!"));
    }
    //qDebug()<<pro.readAllStandardOutput();
    ui->textBrowser->append(QString("-----------------------------------------------"));
    ui->textBrowser->append(GBK2UTF8(pro.readAll()));
    ui->textBrowser->append(QString("*********************************************"));
    ui->textBrowser->moveCursor(QTextCursor::End);
}


inline QString MainWindow::GBK2UTF8(const QString &inStr)
{
    QTextCodec *gbk = QTextCodec::codecForName("GB18030");
//    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
    QString g2u = gbk->toUnicode(gbk->fromUnicode(inStr));
    return g2u;
}

inline QString MainWindow::GBK2UTF8(const QByteArray &inStr)
{
    QTextCodec *gbk = QTextCodec::codecForName("GB18030");
    QString g2u = gbk->toUnicode(inStr);
    return g2u;
}



void MainWindow::on_Clean_clicked()
{
    ui->textBrowser->clear();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1 != ""){
        fullDirPath = arg1;
        ui->StartProcess->setEnabled(true);
    }else{
        ui->StartProcess->setEnabled(false);
    }
}

void MainWindow::on_Exit_clicked()
{
    qApp->quit();
}
