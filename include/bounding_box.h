//
// Created by Tuấn Nguyễn on 1/8/22.
//

#ifndef COVID_SAFE_BOUNDING_BOX_H
#define COVID_SAFE_BOUNDING_BOX_H

#include <opencv2/opencv.hpp>

class BoundingBox {
private:
  cv::Rect box;
  float score;
  int label;

public:
  BoundingBox(cv::Rect &_box, float _score, int _label);

  cv::Rect get_box();

  float get_score() const;

  int get_label() const;
};


#endif //COVID_SAFE_BOUNDING_BOX_H
