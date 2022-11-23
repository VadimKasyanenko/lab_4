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
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
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
    int Dx=x_end-x_beg;
    int Dy=y_end-y_beg;
    int yi=1;
    if (Dy<0)
    {
        yi=-1;
        Dy=-Dy;
    }
    int D=2*Dy-Dx;
    int y=y_beg;
    for(int x=x_beg;x<=x_end;x++)
    {
        ui->label_17->setNum(x);
        ui->label_19->setNum(y);
        ui->widget->graph(1)->addData(x,y);
        ui->widget->replot();
        QThread::sleep(delay);
        if(D>0)
        {
            y+=yi;
            D+=2*(Dy-Dx);
        }
        else
            D+=2*Dy;
    }
    ui->label_17->setText("");
    ui->label_19->setText("");

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
    int dx = x_end - x_beg;
    int dy = y_end - y_beg;
    int step;
    if (abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);
     float x_incr = (float)dx / step;
     float y_incr = (float)dy / step;
     float x = x_beg;
     float y = y_beg;
     for (int i = 0; i <= step; i++) {
         ui->label_17->setNum(x);
         ui->label_19->setNum(y);
         ui->widget->graph(2)->addData(x,y);
     //  ui->widget->graph(2)->addData(round(x),(y)); Points(3,3);(5,20)
         ui->widget->replot();
         QThread::sleep(delay);
         x += x_incr;
         y += y_incr;
     }
     ui->label_17->setText("");
     ui->label_19->setText("");
}

void MainWindow::on_pushButton_4_clicked()
{
    int xm=0,ym=0,r=3,delay;
    QString str;
    str = ui->lineEdit_10->text();
    xm = str.toInt();
    str = ui->lineEdit_12->text();
    ym = str.toInt();
    str = ui->lineEdit_11->text();
    r = str.toInt();
    str = ui->lineEdit->text();
    delay = str.toInt();
    int x = -r, y = 0, err = 2-2*r;
while (x < 0)
{
    r = err;
    if (r <= y)
        err += ++y*2+1;
    if (r > x || err > y)
        err += ++x*2+1;
        ui->label_17->setNum(x);
        ui->label_19->setNum(y);
        ui->widget->graph(3)->addData(xm+x, ym-y);
        ui->widget->replot();
        ui->widget->graph(4)->addData(xm+y, ym-x);
        ui->widget->replot();
        ui->widget->graph(5)->addData(xm+y, ym+x);
        ui->widget->replot();
        ui->widget->graph(6)->addData(xm+x, ym+y);
        ui->widget->replot();
        ui->widget->graph(7)->addData(xm-x, ym-y);
        ui->widget->replot();
        ui->widget->graph(8)->addData(xm-y, ym-x);
        ui->widget->replot();
        ui->widget->graph(9)->addData(xm-y, ym+x);
        ui->widget->replot();
        ui->widget->graph(10)->addData(xm-x, ym+y);
        ui->widget->replot();
        QThread::sleep(delay);
}
        ui->label_17->setText("");
        ui->label_19->setText("");
}


void MainWindow::on_pushButton_5_clicked()
{
    int x_beg,x_end,y_beg,y_end,delay;
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
    delay = str.toInt();

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
    int x_move=0,y_move=0;
    if (x_beg!=0)
    {
        x_move=x_beg;
    }
    if (y_beg!=0)
    {
        y_move=y_beg;
    }
    double x,y;
    x=x_end-y_end-x_move+y_move;
    y=y_end-y_move;
    QString m1="s",m2="d",tmp;
    while(x!=y)
    {
       if(x>y){
           x-=y;
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
    ui->label_17->setNum(x_beg);
    ui->label_19->setNum(y_beg);
    ui->widget->graph(11)->addData(x_beg,y_beg);
    ui->widget->replot();
    QThread::sleep(delay);
    for(int i=0;i<tmp.size();i++)
    {
        if(tmp[i]=='s')
        {
            x_beg ++;
            ui->label_17->setNum(x_beg);
            ui->label_19->setNum(y_beg);
            ui->widget->graph(11)->addData(x_beg,y_beg);
            ui->widget->replot();
            QThread::sleep(delay);
        }
        else
        {
            x_beg ++;
            y_beg ++;
            ui->label_17->setNum(x_beg);
            ui->label_19->setNum(y_beg);
            ui->widget->graph(11)->addData(x_beg,y_beg);
            ui->widget->replot();
            QThread::sleep(delay);
        }
    }
    ui->label_17->setText("");
    ui->label_19->setText("");
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
ui->widget->graph(4)->data().data()->clear();
ui->widget->graph(5)->data().data()->clear();
ui->widget->graph(6)->data().data()->clear();
ui->widget->graph(7)->data().data()->clear();
ui->widget->graph(8)->data().data()->clear();
ui->widget->graph(9)->data().data()->clear();
ui->widget->graph(10)->data().data()->clear();
ui->widget->replot();
}

void MainWindow::on_pushButton_10_clicked()
{
ui->widget->graph(11)->data().data()->clear();
ui->widget->replot();
ui->label_20->setText(" ");
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
      for(int i=3;i<=10;i++)
      ui->widget->graph(i)->setPen(pen);
}

void MainWindow::on_pushButton_15_clicked()
{
      Castle_Pitway = QColorDialog::getColor(Castle_Pitway, this );
      QPen pen;
      pen.setWidth(1);
      pen.setColor(Castle_Pitway);
      ui->widget->graph(11)->setPen(pen);
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

void MainWindow::on_pushButton_17_clicked()
{
    QMessageBox::information(this,"Methods' features","This method is interseting not for it's efficiency, but for it's algorithm, so there are some features \n \n"
                                                      "It doesn't work with negative numbers \n \n"
                                                      "There are only two operations - increase x or increase both x and y, so your function should lay in first quarter and be increasing");
}

void MainWindow::on_pushButton_18_clicked()
{
    QGraphicsView * view = new QGraphicsView();
    QGraphicsScene * scene = new QGraphicsScene();
    QImage image = QImage(800,600,QImage::Format_RGB32);
    QColor color;
    for (int y=0;y<600;y++)
    {
        for (int x=0;x<800;x++)
        {
            color.setRgb(255,255,255);

          image.setPixelColor(x,y,color);
        }
    }
    QPainter painter(&image);
    painter.setRenderHint (QPainter :: Antialiasing, true);
    int pointx = 40, pointy = 580;
    int width = 780-pointx, height = 560;
    painter.drawRect (5,5,800-10,600-10);
    painter.drawLine (pointx, pointy, width + pointx, pointy);
    painter.drawLine (pointx, pointy-height, pointx, pointy);
    QPen penDegree;
    penDegree.setColor(Qt::black);
    penDegree.setWidth(2);
    painter.setPen(penDegree);
    QString str;
    str = ui->lineEdit_2->text();
    int x_axis = str.toInt();
    str = ui->lineEdit_4->text();
    int y_axis = str.toInt();
    double kx = (double) width / x_axis; // коэффициент оси X
    double ky = (double) height / y_axis; // Y масштабный коэффициент
    for (int i = 0; i <=x_axis; i ++)
    {
    painter.drawLine(pointx+(i+1)*kx,pointy,pointx+(i+1)*kx,pointy+4);
    painter.drawText(pointx+(i+1)*kx,
    pointy+10,QString::number(i+1));
    }
    for(int i=0;i<y_axis;i++)
    {
    painter.drawLine(pointx,pointy-(i+1)*ky,
    pointx-4,pointy-(i+1)*ky);
    painter.drawText(pointx-20,pointy-(i+1)*ky,
    QString::number(i+1));
}
     float x1,y1,x2,y2;
     str = ui->lineEdit_8->text();
     x1 = pointx+str.toInt()*kx;
     str = ui->lineEdit_7->text();
     x2 = pointx+str.toInt()*kx;
     str = ui->lineEdit_9->text();
     y1 = pointy-str.toInt()*ky;
     str = ui->lineEdit_6->text();
     y2 = pointy-str.toInt()*ky;
     str = ui->lineEdit->text();
    if (x2 < x1)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    int dx= x2 - x1;
    int dy= y2 - y1;
    float gradient= (float)dy / dx;

    // обработать начальную точку
    int xend= x1;
    int yend= y1 + gradient * (xend - x1);
    float xgapg= 1 -((x1 + 0.5)-(int)(x1+0.5));
    float xpxl1= xend;
    float ypxl1= (int)(yend);
    color.setRgb( (1 - (yend-(int)yend) * xgapg), (1 - (yend-(int)yend) * xgapg),(1 - (yend-(int)yend) * xgapg));
    image.setPixelColor(xpxl1, ypxl1,color);
    color.setRgb( (yend-(int)yend) * xgapg, (yend-(int)yend) * xgapg,(yend-(int)yend) * xgapg);
    image.setPixelColor(xpxl1, ypxl1+1,color);
    float intery= yend + gradient;

    // обработать конечную точку
    xend = (int)x2;
    yend = y2 + gradient * (xend - x2);
    xgapg = ((x2 + 0.5)-(int)(x2+0.5));
    float xpxl2= xend;
    float ypxl2= (int)yend;
    color.setRgb( (1 - (yend-(int)yend) * xgapg), (1 - (yend-(int)yend) * xgapg),(1 - (yend-(int)yend) * xgapg));
    image.setPixelColor(xpxl2, ypxl2,color);
    color.setRgb( (yend-(int)yend) * xgapg, (yend-(int)yend) * xgapg,(yend-(int)yend) * xgapg);
    image.setPixelColor(xpxl2, ypxl2+1,color);


    // основной цикл
    for (int x =xpxl1 + 1 ; x<= xpxl2 - 1 ;x++)
    {
        color.setRgb( (1 - (intery-(int)intery) * xgapg), (1 - (intery-(int)intery) * xgapg),(1 - (intery-(int)intery) * xgapg));
        image.setPixelColor(x, (int)intery,color);
        color.setRgb( (intery-(int)intery) * xgapg, (intery-(int)intery) * xgapg,(intery-(int)intery) * xgapg);
        image.setPixelColor(x, (int)intery+1,color);
        intery = intery + gradient;
    }

    scene->addPixmap(QPixmap::fromImage(image));
    view->setScene(scene);
    view->show();
}
