#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "comlistener.h"
#include "qmlagent.h"
#include "mathagent.h"
#include "sensorunit.h"
#include "sensorspecs.h"
#include "math/lpfilter.h"
#include "math/data_temporal.h"
#include <QVector>
#include "WebChannelWrapper/webchannelwrapper.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent (QCloseEvent *event);

public slots:
    void processRoutine();
    void config();

private slots:

    void on_B_Config_clicked();

    void on_B_Start_clicked();


    void on_B_scan_clicked();

    void on_checkBox_port_1_toggled(bool checked);

    void on_checkBox_port_2_toggled(bool checked);

    void on_checkBox_port_3_toggled(bool checked);

    void on_checkBox_port_4_toggled(bool checked);

    void on_B_connect_clicked();

    void on_pushButton_clicked();

    void on_pushButton_cali_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_min_action_clicked();

    void on_pushButton_min_cali_clicked();

private:

    void connect_Listeners();
    void start_listenertimers();
    void stop_listenertimers();
    QVector<bool> check_enables();
    QVector<bool> check_enabled_units();
    void stuff_pointerlists();
    QStringList scanPorts();

    Ui::MainWindow *ui;
    SensorSpecs m_specs;

    QTimer m_process_timer;
    QTimer m_config_timer;


    COMListener m_listener1;
    COMListener m_listener2;
    COMListener m_listener3;
    COMListener m_listener4;

    QTimer m_listener_timer_1;
    QTimer m_listener_timer_2;
    QTimer m_listener_timer_3;
    QTimer m_listener_timer_4;

    QTime m_tictoc;

    //QThread m_listener_thread_1;
    //QThread m_listener_thread_2;
    QThread m_QML_thread;
    QThread m_math_thread;
    QMLAgent m_QMLAgent;

    mathagent m_mathagent;

    SensorUnit m_sensor1;
    SensorUnit m_sensor2;
    SensorUnit m_sensor3;
    SensorUnit m_sensor4;
    SensorUnit m_sensor5;

    QVector<SensorUnit*> m_sensorlist;

    QVector<COMListener*> m_Listenerlist;

    QVector<QTimer*> m_Timerlist;
    QVector<data_temporal*> m_Wavelist;
    QVector<QComboBox*> m_portSelects;

    lpfilter m_filter1;
    lpfilter m_filter2;
    lpfilter m_filter3;
    lpfilter m_filter4;
    lpfilter m_filter5;

    bool started;
    bool m_configured;
    bool m_cmdSent;
    bool m_listeners_set;

    data_temporal m_wave1;
    data_temporal m_wave2;
    data_temporal m_wave3;
    data_temporal m_wave4;
    data_temporal m_wave5;
    WebChannelWrapper m_WebChannel;
    int m_webchannelcounter=0;
    int m_messagecounter = 0;
    int m_calicounter = 0;
};

#endif // MAINWINDOW_H
