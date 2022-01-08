//
// Created by Tuấn Nguyễn on 1/8/22.
//

#include "box_utils.h"

float IoU(cv::Rect &&box1, cv::Rect &&box2) {
  using namespace cv;
  Point tl1 = box1.tl(), br1 = box1.br();
  Point tl2 = box2.tl(), br2 = box2.br();
  Point inner_tl(std::max(tl1.x, tl2.x), std::max(tl1.y, tl2.y));
  Point inner_br(std::min(br1.x, br2.x), std::min(br1.y, br2.y));
  // Compute area
  int inner_area{0};
  if (inner_br.y > inner_tl.y && inner_br.x > inner_tl.x) {
    Rect inner(inner_tl, inner_br);
    inner_area = inner.area();
  }
  float union_area = std::max<float>((float) (box1.area() + box2.area() - inner_area), 0.0000001);
  return (float) inner_area / union_area;
}

bool CompareBox(BoundingBox box1, BoundingBox box2) {
  return (box1.get_score() < box2.get_score());
}

void NonMaxSuppression(std::vector<BoundingBox> &boxes, float threshold_iou) {
  std::sort(boxes.begin(), boxes.end(), CompareBox);
  std::vector<BoundingBox> results;
  while (!boxes.empty()) {
    if (results.empty()) {
      results.push_back(boxes.back());
    }
    BoundingBox &current_box = boxes.back();
    bool valid = true;
    for (auto &box: results) {
      if (IoU(box.get_box(), current_box.get_box()) > threshold_iou &&
          box.get_label() == current_box.get_label()) {
        valid = false;
        break;
      }
    }
    if (valid) {
      results.push_back(boxes.back());
    }
    boxes.pop_back();
  }
  boxes = results;
}