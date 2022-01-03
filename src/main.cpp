#include "uvc_com.h"

int main(int argc, char const *argv[]) {
  UvcCom uvc_com{};
  uvc_com.init();
  uvc_com.stream();

  cv::VideoCapture cap(0);
  while (cap.isOpened()) {
    cv::Mat frame;
    cap >> frame;
    if (frame.empty())
      break;
    UvcCom::thermal_frame.copyTo(
        frame(cv::Rect(0, 0,
                       UvcCom::thermal_frame.cols,
                       UvcCom::thermal_frame.rows)));
    cv::imshow("frame", frame);
    char c = (char) cv::waitKey(0);
    if (c == 27)
      break;
  }
  cap.release();
  cv::destroyAllWindows();
  return 0;
}
