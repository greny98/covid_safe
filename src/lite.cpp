//
// Created by Tuấn Nguyễn on 1/5/22.
//

#include "lite.h"

void Lite::init() {
  model = tflite::FlatBufferModel::BuildFromFile("model.tflite");
  if (!model)
    throw std::runtime_error("Load model failed");
  tflite::InterpreterBuilder(*model, resolver)(&interpreter);
  if (!interpreter)
    throw std::runtime_error("Interpreter Builder failed");
  if (interpreter->AllocateTensors() != kTfLiteOk)
    throw std::runtime_error("Allocate failed");
  interpreter->SetNumThreads(2);
}

void Lite::preprocess(cv::Mat &img_inp, cv::Mat &img_out) const {
  cv::Mat img_tensor;
  img_inp.convertTo(img_out, CV_32FC3);
  cv::resize(img_out, img_out, cv::Size(WIDTH, HEIGHT));
  cv::cvtColor(img_out, img_out, cv::COLOR_BGR2RGB);
  img_out = img_out / 127.5 - 1.0;
}

void Lite::predict(cv::Mat &img, float threshold_score) {
  bboxes = std::vector<BoundingBox>{};
  memcpy(
      interpreter->typed_input_tensor<float>(0),
      &img.ptr<float>()[0], WIDTH * HEIGHT * CHANNELS * sizeof(float));
  if (interpreter->Invoke() != kTfLiteOk)
    throw std::runtime_error("Invoke failed");
  // Get outputs
  auto output = interpreter->outputs();
  auto cls_tensor = interpreter->tensor(output[0])->data.f;
  auto boxes_tensor = interpreter->tensor(output[1])->data.f;
  for (size_t box = 0; box < N_BOXES; ++box) {
    size_t label_start = box * LABEL_DIMS;
    float max_score = -1;
    int pred_label = -1;
    for (int label = 0; label < LABEL_DIMS; ++label) {
      if (max_score < cls_tensor[label_start + label]) {
        max_score = cls_tensor[label_start + label];
        pred_label = label;
      }
    }
    if (max_score > threshold_score) {
      size_t box_start = box * BOX_DIMS;
      float xmin = boxes_tensor[box_start];
      float ymin = boxes_tensor[box_start + 1];
      float xmax = boxes_tensor[box_start + 2];
      float ymax = boxes_tensor[box_start + 3];
      cv::Rect _box(
      cv::Point((int) xmin, (int) ymin),
          cv::Point((int) xmax, (int) ymax)
      );

      BoundingBox bbox(
          _box,
          max_score,
          pred_label);
      bboxes.push_back(bbox);
    }
  }
}

std::vector<BoundingBox> Lite::get_boxes() {
  return bboxes;
}





