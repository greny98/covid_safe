//
// Created by Tuấn Nguyễn on 1/3/22.
//

#ifndef COVID_SAFE_UVC_COM_H
#define COVID_SAFE_UVC_COM_H



#include <iostream>
#include <libuvc.h>
#include <opencv2/opencv.hpp>

class UvcCom {
private:
  // Properties
  uvc_context_t *ctx;
  uvc_device_t *dev;
  uvc_device_handle_t *devh;
  uvc_stream_ctrl_t ctrl;

  // Private method
  static void callback(uvc_frame_t *frame, void *ptr);

public:
  ~UvcCom();

  uvc_error_t init();

  void stream();
};


#endif //COVID_SAFE_UVC_COM_H
