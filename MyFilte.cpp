#include "MyFilter.h"

QVideoFilterRunnable *MyFilte::createFilterRunnable()
{
  my_filter_runnable_ = new MyFilterRunnable;

  return my_filter_runnable_;
}
