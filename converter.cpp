#include "converter.h"

#include <iostream> // REMOVE_FINISH



namespace convert {


  uchar clamp( uchar n, uchar lower, uchar upper )
  {
    n = ( n > lower ) * n + !( n > lower ) * lower;
    return ( n < upper ) * n + !( n < upper ) * upper;
  }


  void yuv2rgb(uchar y_val, uchar u_val, uchar v_val, uchar &r,
               uchar &g, uchar &b)
  {
      int rTmp = y_val + (1.370705 * (v_val - 128));
      int gTmp = y_val - (0.698001 * (v_val - 128)) - (0.337633 * (u_val - 128));
      int bTmp = y_val + (1.732446 * (u_val - 128));

      r = clamp(rTmp, 0, 255);
      g = clamp(gTmp, 0, 255);
      b = clamp(bTmp, 0, 255);
  }

  //----------------------------------------------------------------------------
  //
  //
  //
  //
  //----------------------------------------------------------------------------
  void YUV420PtoMat(QVideoFrame *video_frame, cv::Mat &mat_img, int mat_channel = CV_8UC3)
  {
    uchar *bits = video_frame->bits();

    //std::cout << "Height : " << frame_size.height() <<" Width : " << frame_size.width() << std::endl; // REMOVE_FINISH

    QSize frame_size = video_frame->size();
    int frame_width = frame_size.width();
    int frame_height = frame_size.height();
    int size_total = frame_width * frame_height;

    cv::Mat mat_image(frame_height, frame_width, mat_channel);


    for (int y = 0; y < frame_height; y++)
    {
      for (int x = 0; x < frame_width; x++)
      {

        uchar y_ = bits[y * frame_width + x];
        uchar u_ = bits[(y / 2) * (frame_size.width() / 2) + (x / 2) + size_total];
        uchar v_ = bits[(y / 2) * (frame_size.width() / 2) + (x / 2) + size_total + (size_total / 4)];

        uchar b, g, r;

        yuv2rgb(y_, u_, v_, r, g, b);
        cv::Vec3b bgr(b, g, r);

        mat_image.at<cv::Vec3b>(y, x) = bgr;

      }
    }

  mat_img = mat_image;
  //cv::imwrite("cv_MAT.png", mat_image); // REMOVE_FINISH

  }




  void YUV420PtoQImage(QVideoFrame *video_frame, QImage &q_img, QImage::Format format = QImage::Format_RGB32)
  {
    QSize frame_size = video_frame->size();

    QImage q_image(frame_size, format);
    //cv::Mat mat_image(frame_size.height(), frame_size.width(), mat_channel);

    uchar *bits = video_frame->bits();

    //std::cout << "Height : " << frame_size.height() <<" Width : " << frame_size.width() << std::endl; // REMOVE_FINISH

    int frame_width = frame_size.width();
    int frame_height = frame_size.height();

    int size_total = frame_width * frame_height;

    for (int y = 0; y < frame_height; y++)
    {
      for (int x = 0; x < frame_width; x++)
      {

        uchar y_ = bits[y * frame_width + x];
        uchar u_ = bits[(y / 2) * (frame_size.width() / 2) + (x / 2) + size_total];
        uchar v_ = bits[(y / 2) * (frame_size.width() / 2) + (x / 2) + size_total + (size_total / 4)];

        uchar b, g, r;

        yuv2rgb(y_, u_, v_, r, g, b);

        QColor color(r, g, b);
        q_image.setPixelColor(x, y, color);


      }
    }

  q_img = q_image;
  q_img.save("Qimg..pn", "PNG");
  //cv::imwrite("cv_MAT.png", mat_image); // REMOVE_FINISH

  }


  //----------------------------------------------------------------------------
  //
  //
  //
  //
  //----------------------------------------------------------------------------
  bool frameToImage(QVideoFrame *video_frame, QImage &q_image)
  {

     if ( !video_frame->map(QAbstractVideoBuffer::ReadWrite))
     {
       std::cout << "Error with map " << std::endl; // REMOVE_FINISH
     }

    //QSize frame_size = video_frame->size();


    QVideoFrame::PixelFormat format = video_frame->pixelFormat();

    cv::Mat mat_img;

   //QImage q_img;

    switch (format)
    {
      case (int(QVideoFrame::Format_Invalid)):
        std::cout << "Pixel Fomat [" << format << "] - Invalid" << std::endl; // REMOVE_FINISH
        // Invalide Pixel Format
        break;
      case (QVideoFrame::Format_BGR24):
        std::cout << "Pixel Fomat [" << format << "] - BGR24" << std::endl; // REMOVE_FINISH
        // CV_8UC3
        break;
      case (QVideoFrame::Format_BGR32):
        std::cout << "Pixel Fomat [" << format << "] - BGR32" << std::endl; // REMOVE_FINISH
        // CV_8UC4
        break;

      case (QVideoFrame::Format_RGB24):

        break;

      case (QVideoFrame::Format_RGB32):
        break;
      case (QVideoFrame::Format_YUV444):
        //YUV444toMat(video_frame, );
        std::cout << "Pixel Fomat [" << format << "] - YUV444" << std::endl; // REMOVE_FINISH

        break;
      case (QVideoFrame::Format_YUV420P):

        YUV420PtoMat(video_frame, mat_img, CV_8UC3);
        //YUV420PtoQImage(video_frame, q_img);
        std::cout << "Pixel Fomat [" << format << "] - YUV420P" << std::endl; // REMOVE_FINISH

        break;



    }

    cv::Mat gray;
    cv::cvtColor(mat_img, gray, CV_BGR2GRAY);
    cv::cvtColor(gray, mat_img, CV_GRAY2BGR);
    cv::imwrite("cv_MAT.png", mat_img); // REMOVE_FINISH
    QImage q_img = matToImage(&mat_img);

   // QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format);
   // QImage q_img(video_frame->bits(), video_frame->width(), video_frame->height(),
   //              video_frame->bytesPerLine(), imageFormat);


    video_frame->unmap();
    q_image = q_img;

  }


  //----------------------------------------------------------------------------
  //
  //
  //
  //
  //----------------------------------------------------------------------------
  QImage matToImage(cv::Mat *mat_img)
  {
    cv::Mat temp(mat_img->cols, mat_img->rows, mat_img->type());

    cv::cvtColor(*mat_img, temp, CV_BGR2RGB);

    QImage q_img = QImage((uchar*)temp.data, temp.cols, temp.rows, temp.step,
                        QImage::Format_RGB32);
    return q_img;


  }

  //----------------------------------------------------------------------------
  //
  //
  //
  //
  //----------------------------------------------------------------------------
  cv::Mat imageToMat(QImage *q_img)
  {
    int channel_num = q_img->depth() / CHANNEL_SIZE;
    cv::Mat mat_img(q_img->width(), q_img->height(), CV_8UC(channel_num),
                    q_img->bits(), q_img->bytesPerLine());

    cv::cvtColor(mat_img, mat_img, CV_BGR2RGB);

    return mat_img;
  }



} // Namespace convert
