#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QDebug>
#include <QProcess>
#include <QDesktopServices>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_StartProcess_clicked();

    void on_OpenDir_clicked();

    void on_toolButton_clicked();

    void on_CreatDir_clicked();

    void extFinished(int);

    void on_Clean_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_Exit_clicked();

private:
    Ui::MainWindow *ui;
    QProcess pro;
    QString fullDirPath;
    bool isDirExist(QString fullPath);
    QString GBK2UTF8(const QString &inStr);
    QString GBK2UTF8(const QByteArray &inStr);
};

#endif // MAINWINDOW_H
