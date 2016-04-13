#include "MyFilterRunnable.h"

#include "converter.h"

QVideoFrame MyFilterRunnable::run(QVideoFrame *input,
  const QVideoSurfaceFormat &surfaceFormat, RunFlags flags)
{

  QImage q_img;
  if(!convert::frameToImage(input, q_img))
  {

  }
 // cv::Mat mat_img = imageToMat(q_img);


 // cv::Mat mat_img_fliped;

 // cv::flip(mat_img, mat_img_fliped, 1);

 // QImage image_from_mat = matToImage(mat_img_fliped);

  //QImage q_img_out = q_img.mirrored(false, true);

  QVideoFrame output(q_img);
  return output;
}
