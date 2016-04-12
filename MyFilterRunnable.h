#ifndef MYFILTERRUNNABLE_H
#define MYFILTERRUNNABLE_H

#include <QVideoFilterRunnable>
#include <QVideoFrame>
#include <opencv/highgui.h>
#include <opencv/cv.hpp>

//#include <QObject>

#define CHANNEL_SIZE 8

class MyFilterRunnable : public QVideoFilterRunnable
{
  public:
    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags);
};

#endif // MYFILTERRUNNABLE_H
