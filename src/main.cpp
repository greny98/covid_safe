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

    size_t n_cols = frame.cols;
    size_t n_rows = frame.rows;
    for (auto box: boxes) {
      float x = (float) box.x * (float) n_cols / 160;
      float width = (float) box.width * (float) n_cols / 160;
      float y = (float) box.y * (float) n_rows / 160;
      float height = (float) box.height * (float) n_cols / 160;
      cv::Rect truth_box = cv::Rect((int) x, (int) y, (int) width, (int) height);
      cv::rectangle(frame, truth_box, cv::Scalar(0, 0, 255), 2);
    }

    UvcCom::thermal_frame.copyTo(
        frame(cv::Rect(0, 0,
                       UvcCom::thermal_frame.cols,
                       UvcCom::thermal_frame.rows)));
    cv::imshow("frame", frame);
    char c = (char) cv::waitKey(2);
    if (c == 27)
      break;
  }
  cap.release();
  cv::destroyAllWindows();
  return 0;
}
