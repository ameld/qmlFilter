#ifndef CONVERTER_H
#define CONVERTER_H

#include <QImage>
#include <QVideoFrame>
#include <opencv/highgui.h>
#include <opencv/cv.hpp>

#define CHANNEL_SIZE 8

namespace convert {


  //cv::Vec3b yuv;
  //cv::Vec3b rgb;

  bool frameToImage(QVideoFrame *video_frame, QImage &q_image);
  QImage matToImage(cv::Mat *mat_image);
  cv::Mat imageToMat(QImage *q_image);

}


#endif // CONVERTER_H
