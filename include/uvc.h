#include <iostream>
#include <opencv2/opencv.hpp>
#include "libuvc/libuvc.h"

uvc_error_t initialize(uvc_context_t* &ctx, uvc_device_t* &dev, uvc_device_handle_t* &devh);
void callback(uvc_frame_t *frame, void *ptr);
void stream(uvc_device_handle_t* &devh, uvc_stream_ctrl_t &ctrl);
