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
    std::cout << frame.size << std::endl;
    cv::imshow("frame", frame);
    char c = (char) cv::waitKey(0);
    if (c == 27)
      break;
  }
  cap.release();
  cv::destroyAllWindows();
  return 0;
}
