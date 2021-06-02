#include "serial.h"
#include "ui_serial.h"

serial::serial(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::serial)
{
    ui->setupUi(this);
    //user code
    system_init();

}

serial::~serial()
{
    delete ui;
}
/* --------------------------------------------------------------------------------
 * function
 *  ------------------------------------------------------------------------------*/
void serial:: system_init()
{
    // port config
    global_port.setParity(QSerialPort::NoParity);//无奇偶校验
    global_port.setDataBits(QSerialPort::Data8);//数据位8位
    global_port.setStopBits(QSerialPort::OneStop);//1位停止位
    //connect
    connect(ui->btn_open,&QPushButton::clicked,this,serial::btn_open_port);
    connect(ui->btn_close,&QPushButton::clicked,this,serial::btn_close_port);
    connect(ui->btn_send,&QPushButton::clicked,this,serial::btn_send_data);
    connect(&global_port,&QSerialPort::readyRead,this, &receive_data);
    connect(ui->btn_search,&QPushButton::clicked,this,serial::btn_search_port);
    connect(ui->btn_clear,&QPushButton::clicked,this,serial::btn_clear_text);
    connect(ui->btn_send_newline,&QPushButton::clicked,this,serial::btn_send_newline);
}

/* ---------------------------------------------------------------------------------
 * slots
 *  ------------------------------------------------------------------------------*/
void serial:: btn_open_port(bool)
{
//    qDebug()<<ui->cmb_port_name->currentIndex();
    /*--------------------port name -------------------------*/
    global_port.setPortName(ui->cmb_port_name->currentText());
    /*--------------------baud rate-------------------------*/
    global_port.setBaudRate(ui->cmb_baud_rate->currentText().toInt());
    //open port
    global_port.open(QIODevice::ReadWrite);//打开串口，读写模式
    //设置控件状态
    ui->lab_status->setText("串口已连接");
    ui->cmb_port_name->setEnabled(false);
    ui->cmb_baud_rate->setEnabled(false);
    ui->btn_open->setEnabled(false);
//    //test
//    global_port.write("hello");
}

/*---------------------send data-------------------------------*/
void serial::btn_send_data(bool)
{
    QString data = ui->lint_send_data->text();//获取文本框内容
    QByteArray array;
    if(send_newline_flag == 1){
        array =  (data.append("\r\n")).toLatin1(); //qstring --> qbytearray
        global_port.write(array);
    }
    else{
        array =  data.toLatin1(); //qstring --> qbytearray
        global_port.write(array);
    }

}
/*--------------------receive data-----------------------------*/
void serial::receive_data()
{
    QByteArray array = global_port.readAll();
    if(ui->checkBox->checkState() == Qt::Checked){  //转16进制
        ui->plainTextEdit->insertPlainText(QString(array.toHex(' ').append("\r\n")));
    }
    else{
        ui->plainTextEdit->insertPlainText(QString(array).append("\r\n"));
    }
}
/*-------------------close port---------------------------------*/
void serial::btn_close_port(bool)
{
    global_port.close();
    //设置控件状态
    ui->lab_status->setText("串口未连接");
    ui->cmb_port_name->setEnabled(true);
    ui->cmb_baud_rate->setEnabled(true);
    ui->btn_open->setEnabled(true);
}
/*------------------search port----------------------------------*/
void serial::btn_search_port(bool)
{
    ui->cmb_port_name->clear();
    //通过QSerialPortInfo查找可用串口
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->cmb_port_name->addItem(info.portName());
        //串口信息打印
//        qDebug() << "Name : " << info.portName();
//        qDebug() << "Description : " << info.description();
//        qDebug() << "Manufacturer: " << info.manufacturer();
//        qDebug() << "Serial Number: " << info.serialNumber();
//        qDebug() << "System Location: " << info.systemLocation();
    }

}
/*---------------clear text--------------------------------------*/
void serial::btn_clear_text(bool)
{
    ui->plainTextEdit->clear();
}
/*---------------send newline mode-------------------------------*/
void serial::btn_send_newline(bool)
{
    send_newline_flag = 1-send_newline_flag;
    if(send_newline_flag == 1){
        ui->lab_mode->setText("换行模式");
    }
    else{
        ui->lab_mode->setText("标准模式");
    }
}
