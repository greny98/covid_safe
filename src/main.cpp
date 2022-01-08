#include "uvc_com.h"
#include "lite.h"
#include "box_utils.h"


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
    std::vector<BoundingBox> bboxes = lite.get_boxes();
    NonMaxSuppression(bboxes, 0.6);

    size_t n_cols = frame.cols;
    size_t n_rows = frame.rows;
    for (auto bbox: bboxes) {
      auto box = bbox.get_box();
      float x = (float) box.x * (float) n_cols / 160;
      float width = (float) box.width * (float) n_cols / 160;
      float y = (float) box.y * (float) n_rows / 160;
      float height = (float) box.height * (float) n_rows / 160;
      cv::Rect truth_box = cv::Rect((int) x, (int) y, (int) width, (int) height);
      cv::Scalar color(0, 255, 0);
      if (bbox.get_label() != 0)
        color = cv::Scalar(0, 0, 255);
      cv::rectangle(frame, truth_box, color, 2);
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


//int main() {
//  Lite lite{};
//  lite.init();
//  cv::Mat img = cv::imread("image.jpeg");
//  cv::Mat image_tensor;
//  lite.preprocess(img, image_tensor);
//  lite.predict(image_tensor);
//  std::vector<BoundingBox> bboxes = lite.get_boxes();
//  NonMaxSuppression(bboxes, 0.6);
//  for (auto bbox: bboxes) {
//    std::cout << " " << bbox.get_score() << " " << bbox.get_label() << std::endl;
//  }
//
//  return 0;
//}