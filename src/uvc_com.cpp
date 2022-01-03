//
// Created by Tuấn Nguyễn on 1/3/22.
//

#include "uvc_com.h"


UvcCom::~UvcCom() {
  using namespace std;
  if (devh != nullptr) {
    uvc_stop_streaming(devh);
    cout << "Stop stream." << endl;
    uvc_close(devh);
    cout << "Close Device." << endl;
  }
  if (dev != nullptr)
    uvc_unref_device(dev);
  if (ctx != nullptr) {
    uvc_exit(ctx);
    cout << "Exited." << endl;
  }
}

uvc_error_t UvcCom::init() {
  using namespace std;
  uvc_error_t res;
  // Init uvc
  res = uvc_init(&ctx, nullptr);
  if (res < 0) {
    uvc_perror(res, "uvc_init failed!");
    return res;
  }
  cout << "UVC initialized" << endl;

  // Find device
  res = uvc_find_device(ctx, &dev, 0, 0, nullptr);
  if (res < 0) {
    uvc_perror(res, "uvc_find_device failed!");
    return res;
  }
  cout << "Found Device" << endl;

  // Open device
  res = uvc_open(dev, &devh);
  if (res < 0) {
    uvc_perror(res, "uvc_open failed!");
    return res;
  }
  cout << "Opened!\n";
  uvc_print_diag(devh, stderr);

  return res;
}

void UvcCom::stream() {
  uvc_error_t res;
  // Stream from uvc
  res = uvc_get_stream_ctrl_format_size(devh, &ctrl, UVC_COLOR_FORMAT_GRAY16, 160, 120, 9);
  uvc_print_stream_ctrl(&ctrl, stderr);
  if (res < 0) {
    uvc_perror(res, "stream error");
    return;
  }
  res = uvc_start_streaming(devh, &ctrl, callback, nullptr, 0);
  if (res < 0) {
    uvc_perror(res, "start_streaming"); /* unable to start stream */
    uvc_close(devh);
    puts("Device closed");
  }
}

void UvcCom::callback(uvc_frame_t *frame, void *ptr) {
  using namespace std;
  using namespace cv;

  Mat gray16(120, 160, CV_16UC1, (uint16_t *) frame->data);
  Mat gray8(120, 160, CV_8UC1);
  Mat heatmap(120, 160, CV_8UC3);
  normalize(gray16, gray8, 0, 256, NORM_MINMAX, CV_8U);
  applyColorMap(gray8, heatmap, COLORMAP_HOT);
  imshow("heatmap", heatmap);
  waitKey(3);
}
