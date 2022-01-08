//
// Created by Tuấn Nguyễn on 1/8/22.
//

#ifndef COVID_SAFE_BOX_UTILS_H
#define COVID_SAFE_BOX_UTILS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include "bounding_box.h"

float IoU(cv::Rect &&box1, cv::Rect &&box2);

bool CompareBox(BoundingBox box1, BoundingBox box2);

void NonMaxSuppression(std::vector<BoundingBox> &boxes, float threshold_iou = 0.6);

#endif //COVID_SAFE_BOX_UTILS_H
