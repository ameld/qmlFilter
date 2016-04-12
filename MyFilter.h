#ifndef MYFILTE_H
#define MYFILTE_H

#include <QAbstractVideoFilter>
#include "MyFilterRunnable.h"

class MyFilte : public QAbstractVideoFilter
{
    Q_OBJECT
  public:
    QVideoFilterRunnable *createFilterRunnable();

    MyFilterRunnable *my_filter_runnable_;
  signals:
    void finished(QObject *result);
};

#endif // MYFILTE_H
