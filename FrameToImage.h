#ifndef FRAMETOIMAGE_H
#define FRAMETOIMAGE_H


#include <QImage>
#include <QVideoFrame>
#include <opencv/highgui.h>
#include <opencv/cv.hpp>

// fti ( Frame to Image)
namespace fti{

  #define CHANNEL_SIZE 8


  bool frameToQImage(QVideoFrame *video_frame, QImage &q_image, int mat_channel = CV_8UC3);
  bool frameToMatImage(QVideoFrame *video_frame, cv::Mat &mat_image, QImage::Format img_format = QImage::Format_RGB32);


  void YUV444toMat(QVideoFrame *video_frame, cv::Mat &mat_img, int mat_channel);
  void YUV444toQImage(QVideoFrame *video_frame, QImage &q_img, QImage::Format img_format);

  void YUV420PtoMat(QVideoFrame *video_frame, cv::Mat &mat_img, int mat_channel);
  void YUV420PtoQImage(QVideoFrame *video_frame, QImage &q_img, QImage::Format img_format);

  uchar clamp(uchar n, uchar lower, uchar upper);
  void yuv444toRgb888(uchar y_val, uchar u_val, uchar v_val, uchar &r, uchar &g, uchar &b);
  
  void rgb2yuv(uchar r, uchar g, uchar b, uchar &y_val, uchar &u_val, uchar &v_val);


}

#endif 
