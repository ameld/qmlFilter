#include "MyFilterRunnable.h"

#include <iostream>

cv::Mat imageToMat(QImage &q_img)
{
  int channel_num = q_img.depth() / CHANNEL_SIZE;
  cv::Mat mat_img(q_img.width(), q_img.height(), CV_8UC(channel_num),
                  q_img.bits(), q_img.bytesPerLine());

  cv::cvtColor(mat_img, mat_img, CV_BGR2RGB);

  return mat_img;
}


QImage matToImage(cv::Mat &mat_img)
{
  cv::Mat temp(mat_img.cols, mat_img.rows, mat_img.type());

  cv::cvtColor(mat_img, temp, CV_BGR2RGB);

  QImage q_img = QImage((uchar*) temp.data, temp.cols, temp.rows, temp.step,
                      QImage::Format_RGB888);
  return q_img;
}


uchar clamp( uchar n, uchar lower, uchar upper )
{
    n = ( n > lower ) * n + !( n > lower ) * lower;
    return ( n < upper ) * n + !( n < upper ) * upper;
}


void yuv2rgb(uint8_t yValue, uint8_t uValue, uint8_t vValue, uint8_t &r,
             uint8_t &g, uint8_t &b)
{
    int rTmp = yValue + (1.370705 * (vValue - 128));
    int gTmp = yValue - (0.698001 * (vValue - 128)) - (0.337633 * (uValue - 128));
    int bTmp = yValue + (1.732446 * (uValue - 128));
    r = clamp(rTmp, 0, 255);
    g = clamp(gTmp, 0, 255);
    b = clamp(bTmp, 0, 255);
}

//------------------------------------------------------------------------------
//
//
//------------------------------------------------------------------------------
//
QImage frameToImage(QVideoFrame *video_frame)
{
  video_frame->map(QAbstractVideoBuffer::ReadWrite);

  QSize frame_size = video_frame->size();


  QVideoFrame::PixelFormat format = video_frame->pixelFormat();

  QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format);

  std::cout << "Pixel Format" << int(format) << std::endl;

  std::cout << "Image Format" << int(imageFormat) << std::endl;

  QImage q_img(video_frame->bits(), video_frame->width(), video_frame->height(),
               video_frame->bytesPerLine(), imageFormat);


  video_frame->unmap();
  return q_img;
}

QVideoFrame MyFilterRunnable::run(QVideoFrame *input,
  const QVideoSurfaceFormat &surfaceFormat, RunFlags flags)
{

  QImage q_img = frameToImage(input);

 // cv::Mat mat_img = imageToMat(q_img);


 // cv::Mat mat_img_fliped;

 // cv::flip(mat_img, mat_img_fliped, 1);

 // QImage image_from_mat = matToImage(mat_img_fliped);

  QImage q_img_out = q_img.mirrored(false, true);

  QVideoFrame output(q_img_out);
  return output;
}
