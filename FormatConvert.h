#ifndef FORMATCONVERT_H
#define FORMATCONVERT_H

#include <QVideoFrame>
#include <QImage>
#include <opencv/highgui.h>




class FormatConvert
{
   public:

    QImage frameToImage(QVideoFrame &video_frame);

    QImage matToImage(cv::Mat &mat_image);
    cv::Mat imageToMat(QImage &q_image);

    void autoConvert();

};

#endif // FORMATCONVERT_H
