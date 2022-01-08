//
// Created by Tuấn Nguyễn on 1/8/22.
//

#include "bounding_box.h"

BoundingBox::BoundingBox(cv::Rect &_box, float _score, int _label) {
  box = _box;
  score = _score;
  label = _label;
}

cv::Rect BoundingBox::get_box() {
  return box;
}

float BoundingBox::get_score() const {
  return score;
}

int BoundingBox::get_label() const {
  return label;
}

