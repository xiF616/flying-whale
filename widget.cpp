﻿#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QKeyEvent>
#include<QDebug>//timer
#include<QTimerEvent>//timer
#include "dialog.h"
#include "ui_dialog.h"
#include "dialog1.h"
#include "ui_dialog1.h"
#include<QPixmap>//add background
#include<QPalette>
#include<QBitmap>
#include<QIcon>
#include<windows.h>
const int tt=20;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPixmap p(":/new/prefix1/image/iconR.jpg");
    QPixmap pp(":/new/prefix1/image/iconB.png");
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Background,pp);
    this->setPalette(palette);
    this->setWindowIcon(p);
    //QDesktopScreenWidget*pDesktdget=QApplication::desktop();
    //QRect deskRect = QApplication::desktop()->screenGeometty();
    x=200;
    y=200;
    x1=100;
    y1=100;
    t1=this->startTimer(tt);
    k=1500;
    hurt=0;
    MyHurt=0;
    used=0;
    WhaleDie=0;
}

Widget::~Widget()
{
    delete ui;
    killTimer(t1);
}
void Widget::draw1()
{
     if(used<750)
   {
    QPainter painter(this);
    QPen pen(QColor(150,255,255));//white
    QBrush brush(QColor(0,245,252));
    painter.setPen(pen);
    painter.setBrush(brush);
    for(int i=0;i<v.size();++i)
        {
        painter.drawEllipse(v[i].a,v[i].b,20,20);
        }
}
}
void Widget::star()
{
    srand(time(0));

    QPainter painter(this);
    if(vv.size()<30)
    for(int i=0;i<20;++i)
   {
         A temp1;
    temp1.a=rand()%1500;
    temp1.b=80+rand()%600;
    vv.push_back(temp1);
    }
    for(int i=0;i<vv.size();++i)
    { 
        QPen pen(QColor(rand()%255,rand()%255,rand()%255));//white
        QBrush brush(QColor(255,255,255));
        painter.setPen(pen);
        painter.setBrush(brush);
    painter.drawEllipse(vv[i].a,vv[i].b,15,15);
    }
}
void Widget::WhiteWhale()
{

    QPainter painter(this);
    QPen pen(QColor(120,100,222));
    QBrush brush(QColor(150+hurt,200-hurt,255-hurt));
    painter.setPen(pen);
    painter.setBrush(brush);
    QPolygon pts;
    pts.setPoints(12, 0+k,20,10+k,10,30+k,10,40+k,20, 50+k,20,60+k,0,70+k,10,80+k,10,60+k,20,50+k,30, 20+k,40,10+k,30); //第一个参数表示3个点，后面是三个点坐标
    painter.drawConvexPolygon(pts);
}
void Widget::draw()
{
    QPainter painter(this);
    QPen pen(QColor(255,255,255));//white
    QBrush brush(QColor(120,255,222));
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawEllipse(x,y,25,25);
}
void Widget::success()
{
  //  srand(time(0));
     for(int i=0;i<vv.size();++i)
         if(( ((x+12.5)-(vv[i].a+7.5))*((x+12.5)-(vv[i].a+7.5))+((y-vv[i].b+5)*(y-vv[i].b+5)) )<40*40)
            {
                vv.erase(vv.begin()+i);
                if(used>0)used=used-10;
            }
}

void Widget::HurtSuccess()
{
    if(used<750)
    for(int i=0;i<v.size();++i)
    {
        if((v[i].a>k)&&(v[i].a<k+80)&&(v[i].b<40))
            hurt=hurt+2;
    }
    if(hurt>=100)WhaleDie=1;
}
void Widget::WhaleBlood()
{
     QPainter painter(this);
    painter.fillRect(QRect(k,50,100,10), QBrush(Qt::darkRed));
    painter.eraseRect(QRect(k,50,hurt,10));
}
void Widget::KillWhale()
{
    if(WhaleDie==1)
    //if(hurt>5)
    {
        //while(GetAsyncKeyState(VK_SPACE));
        //hurt=0;
        Sleep(1000);
        Dialog *d1=new Dialog(t);
        d1->show();
        killTimer(t1);
        close();
    }
}
void Widget::Idie()
{
    if((MyHurt>750)&&(MyHurt<850))
    {
        Dialog1 *d2=new Dialog1;
        d2->show();
        close();
    }
}

void Widget::Attack()
{
      QPainter painter(this);
    if(( ((hurt>25)&&(hurt<50))||(((hurt>75))&&(hurt<100)) )&&(WhaleDie==0))
       /*{ QRectF rect(40, 50, 80.0, 60.0); //x,y,w,h
        int startAngle = 30 * 16; //值为，实际角度 * 16
        int spanAngle = 120 * 16;
        //三个参数：rect表示弧线所在的矩形，startAngle起始角度，spanAngle跨越角度
        painter.drawArc(rect, startAngle, spanAngle);
    }*/
      {
        int w1=80+1500-k;
        int h1= 80.0+1500-k;
        if((w1>0)&&(h1>0))
      { QRectF rect(k, 30.0,w1,h1);
      painter.setPen(QPen(Qt::blue,4,Qt::SolidLine));
      painter.drawArc(rect,-150*16,120*16);}

        int w2=80+1200-k;
        int h2= 80.0+1200-k;
        if((w2>0)&&(h2>0))
      {QRectF rect1(k, 30.0, w2,h2);
    painter.setPen(QPen(Qt::darkBlue,5,Qt::SolidLine));
    painter.drawArc(rect1,-150*16,120*16);}

        int w3=80+900-k;
        int h3=80.0+900-k;
        if((w3>0)&&(h3>0))
   { QRectF rect2(k, 30.0, w3,h3);
  painter.setPen(QPen(Qt::blue,6,Qt::SolidLine));
  painter.drawArc(rect2,-150*16,120*16);}

        int w4=80+600-k;
        int h4=80.0+600-k;
        if((w4>0)&&(h4>0))
  {QRectF rect3(k, 30.0, w4, h4);
painter.setPen(QPen(Qt::darkBlue,7,Qt::SolidLine));
painter.drawArc(rect3,-150*16,120*16);}

int w5=80+300-k;
int h5= 80.0+300-k;
if((w5>0)&&(h5>0))
{QRectF rect4(k, 30.0,w5,h5);
painter.setPen(QPen(Qt::blue,8,Qt::SolidLine));
painter.drawArc(rect4,-150*16,120*16);}
    }
}
void Widget::FailAvoid()
{
       QPainter painter(this);
       painter.fillRect(QRect(0,800,750,15), QBrush(Qt::darkRed));
       painter.eraseRect(QRect(0,800,MyHurt,14));
       //int dd=((x-k-27.5)*(x-k-27.5)+(y-17.5)*(y-17.5));
       bool A[5]={0};
       int r[5]={0};
       int dd[5]={0};
       int w[5]={0};
       for(int i=0;i<5;++i){
           r[i]=(40+150*(i+1)-0.5*k);
           w[i]=2*r[i];
           dd[i]= (x-0.5*k-27.5-150*(i+1))*(x-0.5*k-27.5-150*(i+1))+(y-82.5-150*(i+1)+0.5*k)*(y-82.5-150*(i+1)+0.5*k) ;
       A[i]=
              ( ( dd[i]<r[i]*r[i] )
            &&(dd[i] >(r[i]-8)*(r[i]-8) )&&((y+12.5)>0.75*w[i]) );
       }
       if( (hurt>25)&&(WhaleDie==0)
               &&
               ((A[1]==1)||(A[2]==1)||(A[3]==1)||(A[4]==1))
          )
       {
           MyHurt=MyHurt+15;
           Idie();
       }
}
void Widget::MyResource()
{    
     QPainter painter(this);
     painter.fillRect(QRect(800,800,750,15), QBrush(Qt::blue));
     painter.eraseRect(QRect(800,800,used,14));
}
void Widget::Night()
{
    QPainter painter(this);
    if((hurt>=25)&&(hurt<=50))
    {QBrush brush(QColor(110-hurt,130+hurt-25,222+hurt-25));
     painter.setBrush(brush);}
    if(hurt>=75)
    {QBrush brush(QColor(110,130+hurt-80,222+hurt-80));
    painter.setBrush(brush);}
    painter.drawRect(0, 0, 1550, 750);
    ui->label_4->setText("Night(The whale is dangerous!Do not try to cross the arc from behind.)");
}
void Widget::Fog()
{
    QPainter painter(this);
    QPen pen(QColor(255,255,255));//white
    QBrush brush(QColor(150+hurt,150+hurt,150+hurt));
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(0, 0, 1550, 750);
    ui->label_4->setText("Fog(Watch out the invisible attacks!)");
}
void Widget:: paintEvent(QPaintEvent* ev)//paint
{
    if(((hurt>=25)&&(hurt<=50))||(hurt>=75))
    Night();
    if((hurt>50)&&(hurt<75))
    Fog();
    star();
    WhiteWhale();
    WhaleBlood();
    draw1();
    draw();
    Attack();
    FailAvoid();
    MyResource();
}
 //void Widget::keyPressEvent(QKeyEvent*ev)//key
void Widget::key()
 {
   /* switch(ev->key())
    {
    case Qt::Key_Up:c=1;break;
    case Qt::Key_Down:c=2;break;
    case Qt::Key_Right:c=3;break;
    case Qt::Key_Left:c=4;break;
    case Qt::Key_Space:
        {
        KillWhale();
            A temp;
            temp.a=x;
            temp.b=y+5;
            v.push_back(temp);
            break;
        }

    }*/
    static bool b=true;
    if(GetAsyncKeyState(VK_UP))
       {
           c=1;
           //keys.push_back(1);
       }
       if(GetAsyncKeyState(VK_DOWN))
       {
           c=2;
           //keys.push_back(2);
       }
       if(GetAsyncKeyState(VK_RIGHT))
       {
           c=3;
           //keys.push_back(3);
       }
       if(GetAsyncKeyState(VK_LEFT))
       {
           c=4;
           //keys.push_back(4);
       }
       if(GetAsyncKeyState(VK_SPACE)&&b)
       {
           b=false;
               A temp;
               temp.a=x;
               temp.b=y+5;
               v.push_back(temp);
       }
       if(!GetAsyncKeyState(VK_SPACE))b=true;
       //keys.push_back(ev->key());
    }


 void Widget:: timerEvent(QTimerEvent *ev)//timer
{
     QString s=(QString)(std::to_string((clock()-t)/1000)+'s').c_str();
     ui->lineEdit->setText(s);
     //ui->lineEdit->setBackgroundRole(
     ui->lineEdit->setEnabled(false);


     if(ev->timerId()==t1)
     {
         //srand(time(0));
         success();
         HurtSuccess();
         for(int i=0;i<v.size();++i)
         {
             v[i].b=v[i].b-20;
             if(v[i].b<0)
             {
                 v.erase(v.begin()+i);
                 if(used<750)used=used+50;
             }
         }

         if(WhaleDie==0)
        {k=k-5;if(k<0)k=1500;}
        /*QKeyEvent*ev;
        keyPressEvent(ev);*/
         key();
         switch(c)
         {
         case 1:y=y-12;if(y<0)y=600;update();break;
         case 2:y=y+12;if(y>750)y=750;update();break;
         case 3:x=x+12;if(x>1550)x=1550;update();break;
         case 4:x=x-12;if(x<0)x=0;update();break;
         }
         c=0;
         KillWhale();
         update();
     }

 }
