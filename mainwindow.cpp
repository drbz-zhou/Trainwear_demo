// by default the ports should be Suit 2 - COM7
// Suit 3 - COM8
#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->checkBox_port_1->setChecked(true);
    ui->checkBox_port_2->setChecked(true);
    ui->checkBox_port_3->setChecked(false);
    ui->checkBox_port_4->setChecked(false);
    on_checkBox_port_1_toggled(true);
    on_checkBox_port_2_toggled(true);
    on_checkBox_port_3_toggled(false);
    on_checkBox_port_4_toggled(false);

    on_B_scan_clicked(); // scan ports
    m_listeners_set = false;
    stuff_pointerlists();
    qDebug()<<"enabled units"<<check_enabled_units();
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::processRoutine(){

    int ms_start = m_tictoc.currentTime().msecsSinceStartOfDay();

    ui->textBrowser->setText(QTime::currentTime().toString("hh:mm:ss:zzz"));
    data_temporal min_all;
    data_temporal max_all;
    QVector<bool> enabled_ports=check_enables();
    QVector<bool> enabled_units=check_enabled_units();
    QVector<bool> newPacket;
    QVector<QVector<double> > currentPackets;
    currentPackets.resize(4);
    QString packetString;

    for(int n=0; n<enabled_ports.size(); n++){
        if( enabled_ports.at(n) /*&& m_Listenerlist[n]->ifNew()*/ ){

            //qDebug()<<"checking port::"<<QString::number(n);

            QByteArray byteData = m_Listenerlist[n]->get_Packet();
            //m_Listenerlist[n]->currentPacket.clear();
            currentPackets[n] = m_mathagent.parseBytePacket(byteData);
            packetString.append(m_mathagent.VecDouble2Str(currentPackets[n]));
            newPacket.append(true);
        }else{
            newPacket.append(false);
        }
    }
    //m_webchannelcounter++;
//    /if(m_webchannelcounter>10){
        //qDebug()<<"mainprocess::"<<"packetString"<<packetString.size();
        m_WebChannel.sendData(packetString);
        //m_webchannelcounter = 0;
    //}


    //m_WebChannel.sendData("sending data");
    for(int n=0; n<enabled_units.size(); n++){
        int nodenum=m_specs.unit_to_node(n);
        //qDebug()<<"checking node::"<<QString::number(nodenum)<<enabled_units.at(n) <<newPacket[nodenum];
        if(enabled_units.at(n) && newPacket[nodenum]){
            //qDebug()<<"sensor index and numel::"<<m_sensorlist[n]->m_firstind<<m_sensorlist[n]->m_numel;
            m_sensorlist[n]->updateValsVector(
                    currentPackets[nodenum].mid(m_sensorlist[n]->m_firstind,m_sensorlist[n]->m_numel));
            //qDebug()<<"drawFrame data"<<n<<m_sensorlist[n]->copyData2D().getDataLinear();

            m_QMLAgent.drawFrame(n,m_sensorlist[n]->copyData2D());

            double val = m_sensorlist[n]->filter_apply(m_mathagent.mean(m_sensorlist[n]->getValsVector()));
            m_sensorlist[n]->m_wave.circleAppend(val);
            min_all.append(m_sensorlist[n]->m_wave.min());
            max_all.append(m_sensorlist[n]->m_wave.max());
            QString SensorName = "Sensor";
            SensorName.append(QString::number(n));
            m_QMLAgent.addDataToGraph(SensorName, val);
            //qDebug()<<"finished current sensor node"<<QString::number(n);
        }
    }
    //qDebug()<<min_all.min()<<max_all.max()<<min_all.size()<<max_all.size();
    m_QMLAgent.setYRange(min_all.min(),max_all.max());


    int ms_finish = m_tictoc.currentTime().msecsSinceStartOfDay();
}

void MainWindow::config(){
    QVector<bool> enabled_ports=check_enables();
    for(int n=0; n<enabled_ports.size(); n++){
        if(enabled_ports.at(n)){
            if(!m_Listenerlist[n]->ifConnected()){
                qDebug()<<"not connected";
                return;
            }else{
                qDebug()<<"manualStart";
                m_Listenerlist[n]->manualStart();
            }
            if(!m_cmdSent){
                qDebug()<<"trying to send cmd";
                m_Listenerlist[n]->send_cmd("01",m_specs.generate_mapping(n));
                m_cmdSent = true;
            }else{
                if(m_Listenerlist[n]->ifCMDverified()){
                    m_configured=true;
                    m_config_timer.stop();

                    ui->B_Config->setEnabled(true);
                }
            }
        }
    }
}

QStringList MainWindow::scanPorts(){
    QStringList ports;
    QStringList ports_sorted;
    int i=0;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Name        : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        ports.append(info.portName());
        qDebug()<<ports.at(i)<<ports.at(i).mid(3).toInt();

    }
    while(i<ports.size()){
        int minval = 110;
        int minind = 0;
        for(int n=0; n<ports.size();n++){
            if(ports.at(n).mid(3).toInt() < minval){
                minval = ports.at(n).mid(3).toInt();
                minind = n;
            }
        }
        ports_sorted.append(ports.at(minind));
        ports.removeAt(minind);
    }
    qDebug()<<ports_sorted;
    return ports_sorted;
}

void MainWindow::connect_Listeners(){
    QVector<bool> enablelist = check_enables();
    for(int i=0; i<enablelist.size();i++){
        if(enablelist.at(i)){
            connect(m_Timerlist[i], SIGNAL(timeout()),m_Listenerlist[i], SLOT(run()));
            m_Listenerlist[i]->setPort(m_portSelects[i]->currentText());
            m_Timerlist[i]->setSingleShot(false);
            QString fileName="C";
            fileName.append(QString::number(i)).append("_");
            m_Listenerlist[i]->setFileName(fileName);
        }
    }
}

void MainWindow::start_listenertimers(){
    QVector<bool> enablelist = check_enables();
    for(int i=0; i<enablelist.size();i++){
        if(enablelist.at(i)){
            m_Listenerlist[i]->manualStart();
            m_Timerlist[i]->start(20);
        }
    }
}

void MainWindow::stop_listenertimers(){
    for(int i=0; i<m_Timerlist.size();i++){
        m_Timerlist[i]->stop();
    }
}

QVector<bool> MainWindow::check_enables(){
    QVector<bool> enablelist;
    enablelist.append(false);
    enablelist.append(false);
    enablelist.append(false);
    enablelist.append(false);
    if(ui->comboBox_portSelect_1->isEnabled()){
        enablelist[0]=true;
    }
    if(ui->comboBox_portSelect_2->isEnabled()){
        enablelist[1]=true;
    }
    if(ui->comboBox_portSelect_3->isEnabled()){
        enablelist[2]=true;
    }
    if(ui->comboBox_portSelect_4->isEnabled()){
        enablelist[3]=true;
    }
    return enablelist;
}
QVector<bool> MainWindow::check_enabled_units(){
    QVector<bool> enabled_units;
    QVector<bool> enablelist=check_enables();
    for(int i=0;i<m_specs.spec_sensorunit_num(-1);i++){
        enabled_units.append(false);
    }

    for(int n=0;n<4;n++){
        if(enablelist[n]){
            for(int i=0; i<m_specs.spec_sensorunit_num(n);i++ ){
                enabled_units[i+m_specs.spec_sensorunit_num(10+n)]=true;
            }
        }
    }
    return enabled_units;
}

void MainWindow::stuff_pointerlists(){
    //listener list and timer list
    for(int i=0;i<4;i++){
        m_Listenerlist.append(new COMListener());
        m_Timerlist.append(new QTimer());
    }
    //sensor list
    for(int i=0; i< m_specs.spec_sensorunit_num(-1);i++){
        m_sensorlist.append(new SensorUnit);
        m_Wavelist.append(new data_temporal);
    }
    //UI
    m_portSelects.append(ui->comboBox_portSelect_1);
    m_portSelects.append(ui->comboBox_portSelect_2);
    m_portSelects.append(ui->comboBox_portSelect_3);
    m_portSelects.append(ui->comboBox_portSelect_4);
}

////////// UI related functions
void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "APP_NAME",
                                                                tr("Are you sure to quit demo?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        m_listener1.close();
        m_listener2.close();
        delete ui;
        QApplication::quit();
    }
}


void MainWindow::on_B_Config_clicked()
{
    if(ui->B_Config->text()=="config"){
        ui->B_Config->setText("cancel");
        m_cmdSent = false;
        m_configured=false;
        connect(&m_config_timer, SIGNAL(timeout()),this,SLOT(config()));
        m_config_timer.start(50);
        start_listenertimers();
    }else{

        ui->B_Config->setText("config");
        m_configured=true;
        m_config_timer.stop();
        stop_listenertimers();
    }
}

void MainWindow::on_B_Start_clicked()
{
    if(ui->B_Start->text()=="start"){
        /// set up listeners and sensor dimensions

        for(int i=0;i<m_sensorlist.size();i++){
            m_sensorlist[i]->setDims(m_specs.rows_linear[i],m_specs.cols_linear[i]);
            m_sensorlist[i]->setFirstInd(m_specs.unit_first_ind(i));
            m_sensorlist[i]->m_wave.setLength(TemporalBufferSize);
        }
        connect_Listeners();
        start_listenertimers();
        /*if(!m_listeners_set){
            if(ui->checkBox_port_1->isEnabled()){
                m_sensor1.setDims(A1_x,A1_y);
                m_sensor1.setFirstInd(0);
                m_sensor2.setDims(A2_x,A2_y);
                m_sensor2.setFirstInd(m_sensor1.m_lastind);
                m_sensor3.setDims(A3_x,A3_y);
                m_sensor3.setFirstInd(m_sensor2.m_lastind);

                m_sensor1.m_wave.setLength(TemporalBufferSize);
                m_sensor2.m_wave.setLength(TemporalBufferSize);
                m_sensor3.m_wave.setLength(TemporalBufferSize);

                m_listener1.setPort(ui->comboBox_portSelect_1->currentText());
                m_listener1.setFileName("c1_");
                m_listener1.startlistener();

                connect(&m_listener_timer_1, SIGNAL(timeout()),&m_listener1, SLOT(run()));

                m_listener_timer_1.setSingleShot(false);

            }


            if(ui->checkBox_port_2->isEnabled()){
                m_sensor4.setDims(A4_x,A4_y);
                m_sensor4.setFirstInd(0);
                m_sensor5.setDims(A5_x,A5_y);
                m_sensor5.setFirstInd(m_sensor4.m_lastind);

                m_sensor4.m_wave.setLength(TemporalBufferSize);
                m_sensor5.m_wave.setLength(TemporalBufferSize);

                m_listener2.setPort(ui->comboBox_portSelect_2->currentText());
                m_listener2.setFileName("c2_");
                m_listener2.startlistener();

                connect(&m_listener_timer_2, SIGNAL(timeout()),&m_listener2, SLOT(run()));

                m_listener_timer_2.setSingleShot(false);

            }

            m_listeners_set = true;
        }

        m_listener_timer_1.start(20);
        m_listener_timer_2.start(20);

        m_listener1.disconnect();
        m_listener2.disconnect();

        m_listener1.manualStart();
        m_listener2.manualStart();*/
        m_process_timer.setSingleShot(false);
        connect(&m_process_timer, SIGNAL(timeout()),this,SLOT(processRoutine()));

        started=false;
        m_configured=false;
        m_cmdSent = false;

        m_process_timer.start(100);
        ui->B_Start->setText("stop");

    }else{
        m_process_timer.stop();
        ui->B_Start->setText("start");
        stop_listenertimers();
    }
}


void MainWindow::on_B_scan_clicked()
{
    m_listeners_set = false; // rescanning ports should reset listeners
    QStringList ports = scanPorts();
    ui->comboBox_portSelect_1->clear();
    ui->comboBox_portSelect_2->clear();
    ui->comboBox_portSelect_3->clear();
    ui->comboBox_portSelect_4->clear();
    ui->comboBox_portSelect_1->addItems(ports);
    ui->comboBox_portSelect_2->addItems(ports);
    ui->comboBox_portSelect_3->addItems(ports);
    ui->comboBox_portSelect_4->addItems(ports);
    int indoffset = 1;
    ui->comboBox_portSelect_1->setCurrentIndex(indoffset+0);
    ui->comboBox_portSelect_2->setCurrentIndex(indoffset+2);
    ui->comboBox_portSelect_3->setCurrentIndex(indoffset+4);
    ui->comboBox_portSelect_4->setCurrentIndex(indoffset+6);
}

void MainWindow::on_checkBox_port_1_toggled(bool checked)
{
    ui->comboBox_portSelect_1->setEnabled(checked);
    qDebug()<<"enabled units"<<check_enabled_units();
}

void MainWindow::on_checkBox_port_2_toggled(bool checked)
{
    ui->comboBox_portSelect_2->setEnabled(checked);
    qDebug()<<"enabled units"<<check_enabled_units();
}

void MainWindow::on_checkBox_port_3_toggled(bool checked)
{
    ui->comboBox_portSelect_3->setEnabled(checked);
    qDebug()<<"enabled units"<<check_enabled_units();
}

void MainWindow::on_checkBox_port_4_toggled(bool checked)
{
    ui->comboBox_portSelect_4->setEnabled(checked);
    qDebug()<<"enabled units"<<check_enabled_units();
}

void MainWindow::on_B_connect_clicked()
{
    connect_Listeners();
}

void MainWindow::on_pushButton_clicked()
{
    QString data2send="T";
    m_WebChannel.sendData(data2send.append(QString::number(m_messagecounter)).append(":"));
    m_messagecounter++;
    ui->m_lable_1->setText(QString::number(m_messagecounter));
    /*
    if(m_messagecounter==0){
        m_WebChannel.sendData("T1:I am your personal coach");
        m_WebChannel.sendData("V: Hi, I am your personal coach");
        m_messagecounter++;
    } else if(m_messagecounter==1){
        m_WebChannel.sendData("T2:Lets start our program with Biceps Curls");
        m_WebChannel.sendData("V: Lets start with Biceps Curls");
        m_messagecounter++;
    } else if(m_messagecounter==2){
        m_WebChannel.sendData("I1:img/Smiley-Red-rating.jpg");

        m_WebChannel.sendData("T1:Mind your speed");
        m_WebChannel.sendData("T2:move slower");

        m_WebChannel.sendData("V: slow down");
        m_messagecounter++;
    } else if(m_messagecounter==3){
        m_WebChannel.sendData("I1:img/Smiley-Red-rating.jpg");

        m_WebChannel.sendData("T1:Mind your range of motion");
        m_WebChannel.sendData("T2:go higher");

        m_WebChannel.sendData("V: go higher");
        m_messagecounter++;
    } else if(m_messagecounter==4){
        m_WebChannel.sendData("I1:img/Smiley-Green-rating.jpg");

        m_WebChannel.sendData("T1:That's it!");
        m_WebChannel.sendData("T2:Keep it up!");

        m_WebChannel.sendData("V: that's it, keep it up!");
        m_messagecounter++;
    } else if(m_messagecounter==5){
        m_WebChannel.sendData("I1:img/Smiley-Green-rating.jpg");

        m_WebChannel.sendData("T1:Well done, you've made it");
        m_WebChannel.sendData("T2:Now take a brake for 30 seconds");

        m_WebChannel.sendData("V: Well done, you've made it. Now take a break for 30 seconds. At the beginning you did it too fast, then the range of motion is not full enough. But you've done good quality ones in the end.");
        m_messagecounter++;
    } else if(m_messagecounter==6){
        m_WebChannel.sendData("I1:img/Smiley-Green-rating.jpg");

        m_WebChannel.sendData("T1:Get ready for..");
        m_WebChannel.sendData("T2:Push ups");

        m_WebChannel.sendData("V: your next exercise is push ups. starting in: five.. four.. three.. two.. one.. start!");
        m_messagecounter++;
    }else if(m_messagecounter==7){
        m_WebChannel.sendData("I1:img/Smiley-Green-rating.jpg");

        m_WebChannel.sendData("T1:Push ups");
        m_WebChannel.sendData("T2:let's start!");

        m_messagecounter++;
    }else if(m_messagecounter==8){
        m_WebChannel.sendData("I1:img/Smiley-Red-rating.jpg");

        m_WebChannel.sendData("T1:Mind your speed");
        m_WebChannel.sendData("T2:be slower");

        m_WebChannel.sendData("V: slow down");
        m_messagecounter++;
    }else if(m_messagecounter==9){
        m_WebChannel.sendData("I1:img/Smiley-Red-rating.jpg");

        m_WebChannel.sendData("T1:Mind your range");
        m_WebChannel.sendData("T2:go deeper");

        m_WebChannel.sendData("V: mind your range, go deeper");
        m_messagecounter++;
    }else{
        m_messagecounter = 0;
    }*/

}

void MainWindow::on_pushButton_cali_clicked()
{
    QString data2send="C";
    m_WebChannel.sendData(data2send.append(QString::number(m_calicounter)).append(":"));
    m_calicounter++;
    ui->m_label_2->setText(QString::number(m_calicounter));
}

void MainWindow::on_pushButton_reset_clicked()
{
    m_messagecounter = 0;
    m_calicounter = 0;
    ui->m_lable_1->setText(QString::number(m_messagecounter));
    ui->m_label_2->setText(QString::number(m_calicounter));
}

void MainWindow::on_pushButton_min_action_clicked()
{
    m_messagecounter--;
    ui->m_lable_1->setText(QString::number(m_messagecounter));
}

void MainWindow::on_pushButton_min_cali_clicked()
{
    m_calicounter--;
    ui->m_label_2->setText(QString::number(m_calicounter));
}
