#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sys/types.h>
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    QString s=ui->sys->currentText();
    int syscall=334+s.toInt();
    if(syscall==334){
          ui->rezultat->setText("Campul syscall no. invalid");
          return ;
    }
    s=ui->pid->toPlainText();
    int pid=s.toInt();
    int ok=0;
    if(syscall==335 || syscall==336)
        ok=1;
    QString sys=QString::number(syscall);
    QString p=QString::number(pid);
    if(ok==1){
        QString comanda=QString("./syscall")+" "+sys+" "+p+" "+ui->file->toPlainText();
        system(comanda.toLocal8Bit().data());
    }
    else{
        QString comanda=QString("./syscall")+" "+sys+" "+ui->file->toPlainText();
        system(comanda.toLocal8Bit().data());
    }


    ui->pid->setPlainText("");
    ui->file->setPlainText("");
    ui->rezultat->setText("Executare reusita");
}

