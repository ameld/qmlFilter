
#include "FrameToImage.h"
#include <iostream>

namespace fti{


  //----------------------------------------------------------------------------
  //
  //
  //
  //
  //----------------------------------------------------------------------------
  //
  void YUV411toMat(QVideoFrame *video_frame, cv::Mat &mat_img, int mat_channel = 3)
  {
    uchar *bits = video_frame->bits();

    //std::cout << "Height : " << frame_size.height() <<" Width : " << frame_size.width() << std::endl; // REMOVE_FINISH

    QSize frame_size = video_frame->size();
    int frame_width = frame_size.width();
    int frame_height = frame_size.height();

    cv::Mat mat_image(frame_height, frame_width, CV_8UC(mat_channel));


    int count_pixel;
    for (int y = 0; y < frame_height; y++)
    {
      for (int x = 0; x < frame_width; x += 4)
      {

        uchar u_ = bits[count_pixel];
        uchar y_1 = bits[count_pixel + 1];
        uchar y_2 = bits[count_pixel + 2];
        uchar v_ = bits[count_pixel + 3];
        uchar y_3 = bits[count_pixel + 4];
        uchar y_4 = bits[count_pixel + 5];
        

        uchar b_1, g_1, r_1;
        uchar b_2, g_2, r_2;
        uchar b_3, g_3, r_3;
        uchar b_4, g_4, r_4;

        yuv444toRgb888(y_1, u_, v_, r_1, g_1, b_1);
        yuv444toRgb888(y_2, u_, v_, r_2, g_2, b_2);
        yuv444toRgb888(y_3, u_, v_, r_3, g_3, b_3);
        yuv444toRgb888(y_4, u_, v_, r_4, g_4, b_4);

        switch (mat_channel)
        {
          case 1:
          {
            uchar gray_1 = (r_1 + g_1 + b_1) / 255;
            uchar gray_2 = (r_2 + g_2 + b_2) / 255;
            uchar gray_3 = (r_3 + g_3 + b_3) / 255;
            uchar gray_4 = (r_4 + g_4 + b_4) / 255;

            mat_image.at<uchar>(y, x) = gray_1;
            mat_image.at<uchar>(y, (x + 1)) = gray_2;
            mat_image.at<uchar>(y, (x + 2)) = gray_3;
            mat_image.at<uchar>(y, (x + 3)) = gray_4;
          }
          break;

          case 3:
          {
            cv::Vec3b bgr_1(b_1, g_1, r_1);
            cv::Vec3b bgr_2(b_2, g_2, r_2);
            cv::Vec3b bgr_3(b_3, g_3, r_3);
            cv::Vec3b bgr_4(b_4, g_4, r_4);

            mat_image.at<cv::Vec3b>(y, x) = bgr_1;
            mat_image.at<cv::Vec3b>(y, (x + 1)) = bgr_2;
            mat_image.at<cv::Vec3b>(y, (x + 2)) = bgr_3;
            mat_image.at<cv::Vec3b>(y, (x + 3)) = bgr_4;
          }
          break;

          case 4:
          {
            cv::Vec4b bgra_1(b_1, g_1, r_1, 255);
            cv::Vec4b bgra_2(b_2, g_2, r_2, 255);
            cv::Vec4b bgra_3(b_3, g_3, r_3, 255);
            cv::Vec4b bgra_4(b_4, g_4, r_4, 255);

            mat_image.at<cv::Vec4b>(y, x) = bgra_1;
            mat_image.at<cv::Vec4b>(y, (x + 1)) = bgra_2;
            mat_image.at<cv::Vec4b>(y, (x + 2)) = bgra_3;
            mat_image.at<cv::Vec4b>(y, (x + 3)) = bgra_4;
          }
          break;


        }

        count_pixel += 6;
      }
    }

  mat_img = mat_image;
  //cv::imwrite("cv_MAT.png", mat_image); // REMOVE_FINISH

  }
  
  //----------------------------------------------------------------------------
  //
  //
  //
  //
  //----------------------------------------------------------------------------
  //

  void YUV444toMat(QVideoFrame *video_frame, cv::Mat &mat_img, int mat_channel = 3)
  {
    uchar *bits = video_frame->bits();
    QSize frame_size = video_frame->size();

    int frame_width = frame_size.width();
    int frame_height = frame_size.height();

    cv::Mat mat_image(frame_height, frame_width, CV_8UC(mat_channel));

    int count_pixel = 0;

    for (int y = 0; y < frame_height; y++)
    {
      for (int x = 0; x < frame_width; x++)
      {

        uchar y_ = bits[count_pixel];
        uchar u_ = bits[count_pixel + 1];
        uchar v_ = bits[count_pixel + 2];

        uchar b, g, r;

        yuv444toRgb888(y_, u_, v_, r, g, b);

        switch (mat_channel)
        {
          case 1:
          {
            uchar gray = (r + g + b) / 255;
            mat_image.at<uchar>(y, x) = gray;
          }
          break;

          case 2:
          {
            cv::Vec3b bgr(b, g, r);
            mat_image.at<cv::Vec3b>(y, x) = bgr;
          }
          break;

          case 3:
          {
            cv::Vec4b bgra(b, g, r, 255);
            mat_image.at<cv::Vec4b>(y, x) = bgra;
          }
          break;
        }
        
        count_pixel += 3;
      }
    }

  mat_img = mat_image;
  //cv::imwrite("cv_MAT.png", mat_image); // REMOVE_FINISH

  }

  //----------------------------------------------------------------------------
  //
  //
  //
  //
  //----------------------------------------------------------------------------
  //
  void YUV444toQImage(QVideoFrame *video_frame, QImage &q_img, QImage::Format img_format = QImage::Format_RGB32)
  {
    QSize frame_size = video_frame->size();
    QImage q_image(frame_size, img_format);
    uchar *bits = video_frame->bits();

    int frame_width = frame_size.width();
    int frame_height = frame_size.height();

    int count_pixel = 0;

    for (int y = 0; y < frame_height; y++)
    {
      for (int x = 0; x < frame_width; x++)
      {

        uchar y_ = bits[count_pixel];
        uchar u_ = bits[count_pixel + 1];
        uchar v_ = bits[count_pixel + 2];

        uchar b, g, r;

        yuv444toRgb888(y_, u_, v_, r, g, b);

        QColor color(r, g, b);
        q_image.setPixelColor(x, y, color);

        count_pixel += 3;
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
  //
  void YUV420PtoMat(QVideoFrame *video_frame, cv::Mat &mat_img, int mat_channel = 3)
  {
    uchar *bits = video_frame->bits();

    //std::cout << "Height : " << frame_size.height() <<" Width : " << frame_size.width() << std::endl; // REMOVE_FINISH

    QSize frame_size = video_frame->size();
    int frame_width = frame_size.width();
    int frame_height = frame_size.height();
    int size_total = frame_width * frame_height;

    cv::Mat mat_image(frame_height, frame_width, CV_8UC(mat_channel));


    for (int y = 0; y < frame_height; y++)
    {
      for (int x = 0; x < frame_width; x++)
      {

        uchar y_ = bits[y * frame_width + x];
        uchar u_ = bits[(y / 2) * (frame_size.width() / 2) + (x / 2) + size_total];
        uchar v_ = bits[(y / 2) * (frame_size.width() / 2) + (x / 2) + size_total + (size_total / 4)];

        uchar b, g, r;

        yuv444toRgb888(y_, u_, v_, r, g, b);


        switch (mat_channel)
        {
          case 1:
          {
            uchar gray = (r + g + b) / 255;
            mat_image.at<uchar>(y, x) = gray;
          }
          break;

          case 3:
          {
            cv::Vec3b bgr(b, g, r);
            mat_image.at<cv::Vec3b>(y, x) = bgr;
          }
          break;

          case 4:
          {
            cv::Vec4b bgra(b, g, r, 255);
            mat_image.at<cv::Vec4b>(y, x) = bgra;
          }
          break;

        }

      }
    }

  mat_img = mat_image;
  //cv::imwrite("cv_MAT.png", mat_image); // REMOVE_FINISH

  }

  //----------------------------------------------------------------------------
  //
  //
  //
  //
  //----------------------------------------------------------------------------
  //
  void YUV420PtoQImage(QVideoFrame *video_frame, QImage &q_img, QImage::Format img_format = QImage::Format_RGB32)
  {
    QSize frame_size = video_frame->size();

    QImage q_image(frame_size, img_format);
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

        yuv444toRgb888(y_, u_, v_, r, g, b);

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
  //
  bool frameToQMat(QVideoFrame *video_frame, cv::Mat &mat_image, int mat_channel = CV_8UC3)
  {

     if ( !video_frame->map(QAbstractVideoBuffer::ReadWrite))
     {
       std::cout << "Error with Frame map() !!" << std::endl; // REMOVE_FINISH
       return false;
     }


    QVideoFrame::PixelFormat frame_format = video_frame->pixelFormat();

    cv::Mat mat_img;

    switch (frame_format)
    {
      case int(QVideoFrame::Format_Invalid):
        std::cout << "Pixel Fomat [" << frame_format << "] - Invalid" << std::endl; // REMOVE_FINISH
        
        break;

      case QVideoFrame::Format_BGR24:
        std::cout << "Pixel Fomat [" << frame_format << "] - BGR24" << std::endl; // REMOVE_FINISH
        // CV_8UC3
        break;
      
      case QVideoFrame::Format_BGR32:
        std::cout << "Pixel Fomat [" << frame_format << "] - BGR32" << std::endl; // REMOVE_FINISH
        // CV_8UC4
        break;

      case QVideoFrame::Format_RGB24:

        break;

      case QVideoFrame::Format_RGB32:

        break;
      
      case QVideoFrame::Format_YUV444:
        //YUV444toMat(video_frame, );
        std::cout << "Pixel Fomat [" << frame_format << "] - YUV444" << std::endl; // REMOVE_FINISH
        break;
      
      case QVideoFrame::Format_YUV420P:

        YUV420PtoMat(video_frame, mat_img, CV_8UC3);
        std::cout << "Pixel Fomat [" << frame_format << "] - YUV420P" << std::endl; // REMOVE_FINISH

        break;


    }

    mat_image = mat_img;

    return true;
  }




  //----------------------------------------------------------------------------
  //
  //
  //
  //
  //----------------------------------------------------------------------------
  //
  bool frameToQImage(QVideoFrame *video_frame, QImage &q_image, QImage::Format img_format = QImage::Format_RGB32)
  {

     if ( !video_frame->map(QAbstractVideoBuffer::ReadWrite))
     {
       std::cout << "Error with Frame map() !!" << std::endl; // REMOVE_FINISH
       return false;
     }


    QVideoFrame::PixelFormat frame_format = video_frame->pixelFormat();

    QImage q_img;

    switch (frame_format)
    {
      case QVideoFrame::Format_Invalid:
        std::cout << "Pixel Fomat [" << frame_format << "] - Invalid" << std::endl; // REMOVE_FINISH
        // Invalide Pixel Format
        break;
      case QVideoFrame::Format_BGR24:
        std::cout << "Pixel Fomat [" << frame_format << "] - BGR24" << std::endl; // REMOVE_FINISH
        // CV_8UC3
        break;
      case QVideoFrame::Format_BGR32:
        std::cout << "Pixel Fomat [" << frame_format << "] - BGR32" << std::endl; // REMOVE_FINISH
        // CV_8UC4
        break;

      case QVideoFrame::Format_RGB24:

        break;

      case QVideoFrame::Format_RGB32:
        break;
      case QVideoFrame::Format_YUV444:
        //YUV444toMat(video_frame, );
        std::cout << "Pixel Fomat [" << frame_format << "] - YUV444" << std::endl; // REMOVE_FINISH

        break;
      case (QVideoFrame::Format_YUV420P):


        YUV420PtoQImage(video_frame, q_img, img_format);
        std::cout << "Pixel Fomat [" << frame_format << "] - YUV420P" << std::endl; // REMOVE_FINISH

        break;


    }


    q_image = q_img;
    return true;
  }


  //----------------------------------------------------------------------------
  //
  //
  //
  //
  //----------------------------------------------------------------------------
  //
  uchar clamp( uchar n, uchar lower, uchar upper )
  {
    n = ( n > lower ) * n + !( n > lower ) * lower;
    return ( n < upper ) * n + !( n < upper ) * upper;
  }

  //----------------------------------------------------------------------------
  //
  //
  //
  //
  //----------------------------------------------------------------------------
  //
  void yuv444toRgb888(uchar y_val, uchar u_val, uchar v_val, uchar &r, uchar &g, uchar &b)
  {
    int rTmp = y_val + (1.370705 * (v_val - 128));
    int gTmp = y_val - (0.698001 * (v_val - 128)) - (0.337633 * (u_val - 128));
    int bTmp = y_val + (1.732446 * (u_val - 128));

    r = clamp(rTmp, 0, 255);
    g = clamp(gTmp, 0, 255);
    b = clamp(bTmp, 0, 255);
  }


  void rgb2yuv(uchar r, uchar g, uchar b, uchar &y_val, uchar &u_val, uchar &v_val)
  {



  }

} // Namespace fti

