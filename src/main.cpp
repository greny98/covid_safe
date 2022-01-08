#include "uvc_com.h"
#include "lite.h"

int main(int argc, char const *argv[]) {
  // Model
  Lite lite{};
  lite.init();

  UvcCom uvc_com{};
  uvc_com.init();
  uvc_com.stream();
  cv::VideoCapture cap(0);
  while (cap.isOpened()) {
    cv::Mat frame;
    cap >> frame;
    if (frame.empty())
      break;

    cv::Mat image_tensor;
    lite.preprocess(frame, image_tensor);
    lite.predict(image_tensor);
    auto boxes = lite.get_boxes();
    auto cls = lite.get_cls();

    for (auto box: boxes) {
      cv::rectangle(frame, box, cv::Scalar(0, 0, 255), 2);
    }

    UvcCom::thermal_frame.copyTo(
        frame(cv::Rect(0, 0,
                       UvcCom::thermal_frame.cols,
                       UvcCom::thermal_frame.rows)));
    cv::imshow("frame", frame);
    char c = (char) cv::waitKey(3);
    if (c == 27)
      break;
  }
  cap.release();
  cv::destroyAllWindows();
  return 0;
}
