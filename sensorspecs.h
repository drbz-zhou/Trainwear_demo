#ifndef SENSORSPECS
#define SENSORSPECS

#define A1_x    10
#define A1_y    6

#define A2_x    8
#define A2_y    4

#define A3_x    8
#define A3_y    4

#define A4_x    4
#define A4_y    10

#define A5_x    16
#define A5_y    4

#define TemporalBufferSize 200

#include <QByteArray>
#include <QVector>
#include <QDebug>
class SensorSpecs{
public:
    SensorSpecs();
    int nodes;
    QVector<QVector<int> > cols;
    QVector<QVector<int> > rows;
    QVector<QVector<int> > AnalogPins;
    QVector<QVector<int> > DigitalPins;

    QVector<int> cols_linear;
    QVector<int> rows_linear;

    int unit_to_node(int unit);
    int unit_first_ind(int unit);

    QByteArray dec2hex_8bit(int num);
    int spec_sensorunit_num(int listener_num);
    QByteArray generate_mapping(int node_number);
};



#endif // SENSORSPECS

