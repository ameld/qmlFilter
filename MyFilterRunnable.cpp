#include "MyFilterRunnable.h"

#include "converter.h"

QVideoFrame MyFilterRunnable::run(QVideoFrame *input,
  const QVideoSurfaceFormat &surfaceFormat, RunFlags flags)
{

  QImage q_img;
  if(!convert::frameToImage(input, q_img))
  {

  }



  QVideoFrame output(q_img);
  return output;
}
