#include<sensorspecs.h>
SensorSpecs::SensorSpecs(){
    nodes = 4;
    cols.append({4, 4}); // left chest
    cols.append({4, 4}); // right chest
    cols.append({4, 16}); // left leg
    cols.append({4, 16, 6}); // right leg

    rows.append({16, 10});
    rows.append({16, 10});
    rows.append({10, 4});
    rows.append({10, 4, 10});

    AnalogPins.append({26,27,24,25, 22,23,
                       17,16,19,18,
                       30,31,28,29});
    AnalogPins.append({23,22,25,24, 27,26,
                       29,28,31,30,
                       17,16,19,18});
    AnalogPins.append({24,25,22,23,
                       4,5,2,3, 0,1,7,6, 9,8,11,10, 13,12,15,14});
    AnalogPins.append({19,18,21,20,
                       4,5,2,3, 0,1,7,6, 9,8,11,10, 13,12,15,14,
                       16,17,30,31, 28,29});

    DigitalPins.append({17,16,19,18, 21,20,23,22, 25,24,
                        27,26,29,28, 31,30,15,14,
                        7,6,9,8, 11,10,13,12});
    DigitalPins.append({17,16,19,18, 21,20,23,22, 25,24,
                        3,2,5,4, 7,6,9,8,
                        27,26,29,28, 31,30,1,0});
    DigitalPins.append({3,2,5,4, 7,6,9,8, 11,10,
                        13,12,15,14});
    DigitalPins.append({28,29,26,27, 24,25,22,23, 20,21,
                        17,16,19,18,
                        14,15,12,13, 10,11,8,9, 6,7});
    for(int i=0;i<cols.size();i++){
        for(int j=0;j<cols[i].size();j++){
            cols_linear.append(cols.at(i).at(j));
        }
    }
    for(int i=0;i<rows.size();i++){
        for(int j=0;j<rows[i].size();j++){
            rows_linear.append(rows.at(i).at(j));
        }
    }

}

QByteArray SensorSpecs::dec2hex_8bit(int num){
    QByteArray numByte=QByteArray::number(num,16);
    while(numByte.size()<2){
        numByte.prepend("0");
    }
    return numByte;
}
int SensorSpecs::spec_sensorunit_num(int listener_num){
    int node_0=2;
    int node_1=2;
    int node_2=2;
    int node_3=3;
    switch (listener_num) {
    case -1:
        return node_0+node_1+node_2+node_3;
        break;
    case 0:
        return node_0;
        break;
    case 1:
        return node_1;
        break;
    case 2:
        return node_2;
        break;
    case 3:
        return node_3;
        break;
    case 10:
        return 0;
        break;
    case 11:
        return node_0;
        break;
    case 12:
        return node_0+node_1;
        break;
    case 13:
        return node_0+node_1+node_2;
        break;
    default:
        return node_0+node_1+node_2+node_3;
        break;
    }
}

QByteArray SensorSpecs::generate_mapping(int node_number){
    QByteArray mapping;
    QVector<int> node_AnalogPins;
    QVector<int> node_DigitalPins;
    QVector<int> node_cols;
    QVector<int> node_rows;
    QVector<int> LUT_AI;
    QVector<int> LUT_DO;

    node_cols=cols[node_number];
    node_rows=rows[node_number];
    node_AnalogPins=AnalogPins[node_number];
    node_DigitalPins=DigitalPins[node_number];


    int offset_c = 0;
    int offset_r = 0;
    for(int i=0; i<node_cols.size(); i++){
        for(int r=0; r<node_rows[i]; r++){
            for(int c=0; c<node_cols[i]; c++){
                LUT_AI.append(node_AnalogPins[c+offset_c]);
                LUT_DO.append(node_DigitalPins[r+offset_r]);
            }
        }
        qDebug()<<offset_c<<offset_r<<node_cols[i]+offset_c<<node_rows[i]+offset_r;
        offset_c += node_cols[i];
        offset_r += node_rows[i];
    }
    QByteArray index_length = QByteArray::number(LUT_AI.size(),16);
    qDebug()<<LUT_AI.size()<<LUT_AI;
    qDebug()<<LUT_DO.size()<<LUT_AI;
    int lessthanfour = 4-index_length.size();
    for(int i=0; i<lessthanfour; i++){
        mapping.append("0");
    }
    mapping.append(index_length);
    for(int i=0; i<LUT_AI.size(); i++){
        mapping.append(dec2hex_8bit(LUT_AI[i]));
    }
    for(int i=0; i<LUT_DO.size(); i++){
        mapping.append(dec2hex_8bit(LUT_DO[i]));
    }
    return mapping;
}
int SensorSpecs::unit_to_node(int unit){
    for(int i=0; i<nodes;i++){
        int a=spec_sensorunit_num(i+10); //absolute index
        int b=spec_sensorunit_num(i);    //relative index
        //qDebug()<<"specs"<<unit<<(a-1)<<(a+b);
        if( unit>(a-1) && unit<(a+b)){
            return i;
        }
    }
    return -1;
}

int SensorSpecs::unit_first_ind(int unit){
    int first_ind = 0;
    int node_num=unit_to_node(unit);
    int first_unit_of_node = spec_sensorunit_num(10+node_num);
    for(int i=first_unit_of_node;i<unit;i++){
        first_ind+=cols_linear[i]*rows_linear[i];
    }
    //qDebug()<<"spec::"<<unit << node_num<<first_unit_of_node<<first_ind;
    return first_ind;
}
