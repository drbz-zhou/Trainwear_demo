#include "cv_spatialmethods.h"

cv_spatialMethods::cv_spatialMethods()
{

}
cv::Mat cv_spatialMethods::DS2Mat(data_spatial ds){
    int rows = ds.numRows();
    int cols = ds.numCols();
    cv::Mat mat = cv::Mat::zeros(rows, cols, CV_32F);
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            mat.at<float>(i,j)=ds.value(i,j);
        }
    }
    return mat;
}
data_spatial cv_spatialMethods::Mat2DS(cv::Mat mat){
    int rows = mat.rows;
    int cols = mat.cols;
    data_spatial ds(rows, cols);
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            double value = mat.at<float>(i,j);
            ds.setValue(i,j,value);
        }
    }
    return ds;
}
