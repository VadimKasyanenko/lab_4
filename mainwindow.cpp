#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include "qcustomplot.h"
#include <QDebug>
#include <algorithm>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int x,x2;
    QString str;
    str = ui->lineEdit_2->text();
    x = str.toInt();
    str = ui->lineEdit_3->text();
    x2 = str.toInt();
    ui->widget->xAxis->setRange(x,x2);
    str = ui->lineEdit_4->text();
    x = str.toInt();
    str = ui->lineEdit_5->text();
    x2 = str.toInt();
    ui->widget->yAxis->setRange(x,x2);
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    ui->widget->setInteraction(QCP::iRangeDrag,true);
    ui->widget->setInteraction(QCP::iRangeZoom,true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int x_beg,x_end,y_beg,y_end;
    double delay;
    QString str;
    str = ui->lineEdit_8->text();
    x_beg = str.toInt();
    str = ui->lineEdit_7->text();
    x_end = str.toInt();
    str = ui->lineEdit_9->text();
    y_beg = str.toInt();
    str = ui->lineEdit_6->text();
    y_end = str.toInt();
    str = ui->lineEdit->text();
    delay = str.toDouble();
    double k,b;
    if (x_beg > x_end)
    {
        std::swap(x_beg,x_end);
        std::swap(y_beg,y_end);
    }
    if(x_end-x_beg == 0)
    {
        ui->label_17->setNum(x_beg);
        ui->label_19->setNum(y_beg);
        ui->widget->graph(0)->addData(x_beg,y_beg);
        ui->widget->replot();
        ui->widget->graph(0)->addData(x_end,y_end);
        ui->widget->replot();
    }
    else
    {
    k=1.0*(y_end-y_beg)/(x_end-x_beg);
    b=y_end-k*x_end;
    ui->label_17->setNum(x_beg);
    ui->label_19->setNum(y_beg);
    ui->widget->graph(0)->addData(x_beg,y_beg);
    ui->widget->replot();
    QThread::sleep(delay);
    double v;
    while(x_beg<x_end)
    {
         x_beg++;
         y_beg=round(k*x_beg+b);
         ui->label_17->setNum(x_beg);
         ui->label_19->setNum(y_beg);
         ui->widget->graph(0)->addData(x_beg,y_beg);
         ui->widget->replot();
         QThread::sleep(delay);
    }
    }
    ui->widget->replot();
    ui->label_17->setText("");
    ui->label_19->setText("");
}

void MainWindow::on_pushButton_2_clicked()
{
    int x_beg,x_end,y_beg,y_end;
    double delay;
    QString str;
    str = ui->lineEdit_8->text();
    x_beg = str.toInt();
    str = ui->lineEdit_7->text();
    x_end = str.toInt();
    str = ui->lineEdit_9->text();
    y_beg = str.toInt();
    str = ui->lineEdit_6->text();
    y_end = str.toInt();
    str = ui->lineEdit->text();
    delay = str.toDouble();

    if(abs(y_end-y_beg) > abs(x_end-x_beg))
    {
       std::swap(x_beg,y_beg);
       std::swap(x_end,y_end);
    }
    if (x_beg > x_end)
    {
        std::swap(x_beg,x_end);
        std::swap(y_beg,y_end);
    }
    int x,y,Dx,Dy,e,j;
    Dx = x_end - x_beg;
    Dy = abs(y_end- y_beg);
    e = Dx/2;
    j = (y_beg < y_end) ? 1 : -1;
    x = x_beg;
    y = y_beg;
    for(x = x_beg;x<=x_end;x++)
    {
        if(abs(y_end-y_beg) > abs(x_end-x_beg))
        {
        ui->label_17->setNum(y);
        ui->label_19->setNum(x);
        }
        else
        {
        ui->label_17->setNum(x);
        ui->label_19->setNum(y);
        }
        ui->widget->graph(3)->addData(x,y);
        ui->widget->replot();
        QThread::sleep(delay);
        e -= Dy;
       if(e<0){
           y+= j;
           e+=Dx;
       }
    }
    ui->label_17->setText("");
    ui->label_19->setText("");

    /*int x_beg,x_end,y_beg,y_end;
    double delay;
    QString str;
    str = ui->lineEdit_8->text();
    x_beg = str.toInt();
    str = ui->lineEdit_7->text();
    x_end = str.toInt();
    str = ui->lineEdit_9->text();
    y_beg = str.toInt();
    str = ui->lineEdit_6->text();
    y_end = str.toInt();
    str = ui->lineEdit->text();
    delay = str.toDouble();
    int x,y,Ds,Dd,e;
    if (x_beg > x_end)
    {
        std::swap(x_beg,x_end);
        std::swap(y_beg,y_end);
    }
    x=x_beg;
    y=y_beg;
    e=2*y_end-x_end;
    Ds = 2*y_end;
    Dd = 2*y_end-2*x_end;
    ui->label_17->setNum(x_beg);
    ui->label_19->setNum(y_beg);
    ui->widget->graph(1)->addData(x,y);
    ui->widget->replot();
    QThread::sleep(delay);
    while(x<x_end)
    {
       if(e>0){
           x++;
           y++;
           e+=Dd;
       }
       else{
           x++;
           e+=Ds;
       }
       ui->label_17->setNum(x_beg);
       ui->label_19->setNum(y_beg);
       ui->widget->graph(1)->addData(x,y);
       ui->widget->replot();
       QThread::sleep(delay);
    }
    ui->label_17->setText("");
    ui->label_19->setText("");*/

}

void MainWindow::on_pushButton_3_clicked()
{
    int x_beg,x_end,y_beg,y_end;
    double delay;
    QString str;
    str = ui->lineEdit_8->text();
    x_beg = str.toInt();
    str = ui->lineEdit_7->text();
    x_end = str.toInt();
    str = ui->lineEdit_9->text();
    y_beg = str.toInt();
    str = ui->lineEdit_6->text();
    y_end = str.toInt();
    str = ui->lineEdit->text();
    delay = str.toDouble();
    double x,y,Ds,e;
    QVector<double> X,Y;
    x=x_beg;
    y=y_beg;
    e=1.0*y_end/x_end;
    Ds= 1.0*y_end/x_end;
    ui->widget->graph(2)->addData(x,y);
    ui->widget->replot();
    QThread::sleep(delay);
    while(x<x_end)
    {
       if(e>0.5){
           x++;
           y++;
           e+=Ds - 1;
       }
       else{
           x++;
           e+=Ds;
       }
       ui->widget->graph(2)->addData(x,y);
       ui->widget->replot();
       QThread::sleep(delay);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    int x,rad;
    double delay;
    QString str;
    str = ui->lineEdit_10->text();
    x = str.toInt();
    str = ui->lineEdit_11->text();
    rad = str.toInt();
    str = ui->lineEdit->text();
    delay = str.toDouble();
    QVector<double> q,w;
    double X=0,Y=rad,e=3-2*rad;
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->graph(1)->addData(Y,-X);
    ui->widget->replot();
    ui->widget->graph(5)->addData(X,-Y);
    ui->widget->replot();
    ui->widget->graph(6)->addData(-Y,-X);
    ui->widget->replot();
    ui->widget->graph(7)->addData(-X,-Y);
    ui->widget->replot();
    ui->widget->graph(8)->addData(-Y,X);
    ui->widget->replot();
    ui->widget->graph(9)->addData(-X,Y);
    ui->widget->replot();
    ui->widget->graph(10)->addData(X,Y);
    ui->widget->replot();
    ui->widget->graph(11)->addData(Y,X);
    ui->widget->replot();//3
    //1 x=0 y=5 e=-7  x=1 y=5 e=-1
    //2 x=1 y=5 e=-1  x=2 y=5 e=5
    //3 x=2 y=5 e=5   x=3 y=4 e=3

    QThread::sleep(delay);
    while(X<Y)
    {
       if(e>=0){
          e+= 4*(X-Y)+10;
          X++;
          Y--;
       }
       else{
         e+=4*X+6;
         X++;
       }
       ui->widget->graph(1)->addData(Y,-X);

       ui->widget->graph(5)->addData(X,-Y);

       ui->widget->graph(6)->addData(-Y,-X);

       ui->widget->graph(7)->addData(-X,-Y);

       ui->widget->graph(8)->addData(-Y,X);

       ui->widget->graph(9)->addData(-X,Y);

       ui->widget->graph(10)->addData(X,Y);

       ui->widget->graph(11)->addData(Y,X);
       ui->widget->replot();
       QThread::sleep(delay);
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    int x_beg,x_end,y_beg,y_end;
    QString str;
    str = ui->lineEdit_8->text();
    x_beg = str.toInt();
    str = ui->lineEdit_7->text();
    x_end = str.toInt();
    str = ui->lineEdit_9->text();
    y_beg = str.toInt();
    str = ui->lineEdit_6->text();
    y_end = str.toInt();
    double x,y;
    x=x_end-y_end;
    y=y_end;
    QString m1="s",m2="d",tmp;
    while(x!=y)
    {
       if(x>y){
           x+=y;
           tmp = m2;
           std::reverse(tmp.begin(), tmp.end());
           m2 = m1 + tmp;
       }
       else{
           y-=x;
           tmp = m1;
           std::reverse(tmp.begin(), tmp.end());
           m1 = m2 + tmp;
       }
    }
    std::reverse(m1.begin(), m1.end());
    tmp = m2 +m1;
    ui->label_20->setText(tmp);
}

void MainWindow::on_pushButton_6_clicked()
{
ui->widget->graph(0)->data().data()->clear();
ui->widget->replot();
}

void MainWindow::on_pushButton_12_clicked()
{
ui->widget->graph(1)->data().data()->clear();
ui->widget->replot();
}

void MainWindow::on_pushButton_8_clicked()
{
ui->widget->graph(2)->data().data()->clear();
ui->widget->replot();
}

void MainWindow::on_pushButton_9_clicked()
{
ui->widget->graph(3)->data().data()->clear();
ui->widget->replot();
}

void MainWindow::on_pushButton_10_clicked()
{
ui->widget->graph(4)->data().data()->clear();
ui->widget->replot();
}

void MainWindow::on_pushButton_11_clicked()
{
      Sequential = QColorDialog::getColor(Sequential, this );
      QPen pen;
      pen.setWidth(1);
      pen.setColor(Sequential);
      ui->widget->graph(0)->setPen(pen);
}

void MainWindow::on_pushButton_7_clicked()
{
      Bresenham = QColorDialog::getColor(Bresenham, this );
      QPen pen;
      pen.setWidth(1);
      pen.setColor(Bresenham);
      ui->widget->graph(1)->setPen(pen);
}

void MainWindow::on_pushButton_13_clicked()
{
      DDA = QColorDialog::getColor(DDA, this );
      QPen pen;
      pen.setWidth(1);
      pen.setColor(DDA);
      ui->widget->graph(2)->setPen(pen);
}

void MainWindow::on_pushButton_14_clicked()
{
      Bresenham_Circle = QColorDialog::getColor(Bresenham_Circle, this );
      QPen pen;
      pen.setWidth(1);
      pen.setColor(Bresenham_Circle);
      ui->widget->graph(3)->setPen(pen);
}

void MainWindow::on_pushButton_15_clicked()
{
      Castle_Pitway = QColorDialog::getColor(Castle_Pitway, this );
      QPen pen;
      pen.setWidth(1);
      pen.setColor(Castle_Pitway);
      ui->widget->graph(4)->setPen(pen);
}

void MainWindow::on_pushButton_16_clicked()
{
    int x,x2;
    QString str;
    str = ui->lineEdit_2->text();
    x = str.toInt();
    str = ui->lineEdit_3->text();
    x2 = str.toInt();
    ui->widget->xAxis->setRange(x,x2);
    str = ui->lineEdit_4->text();
    x = str.toInt();
    str = ui->lineEdit_5->text();
    x2 = str.toInt();
    ui->widget->yAxis->setRange(x,x2);
    ui->widget->replot();
}
