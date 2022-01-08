//
// Created by Tuấn Nguyễn on 1/5/22.
//

#ifndef COVID_SAFE_LITE_H
#define COVID_SAFE_LITE_H

#include <vector>
#include <opencv2/opencv.hpp>
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "bounding_box.h"

class Lite {
private:
  // Image size
  const int WIDTH = 160;
  const int HEIGHT = 160;
  const int CHANNELS = 3;
  const int N_BOXES = 4842;
  const int LABEL_DIMS = 4;
  const int BOX_DIMS = 4;
  std::vector<BoundingBox> bboxes;
  // Lite config
  std::unique_ptr<tflite::FlatBufferModel> model;
  std::unique_ptr<tflite::Interpreter> interpreter;
  tflite::ops::builtin::BuiltinOpResolver resolver;
public:
  void init();

  void preprocess(cv::Mat &img_inp, cv::Mat &img_out) const;

  void predict(cv::Mat &img, float threshold_score = 0.5);

  std::vector<BoundingBox> get_boxes();

};


#endif //COVID_SAFE_LITE_H
