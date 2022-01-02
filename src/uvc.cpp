#include "uvc.h"

uvc_error_t initialize(uvc_context_t* &ctx, uvc_device_t* &dev, uvc_device_handle_t* &devh)
{
  using namespace std;
  uvc_error_t res;
  // Init uvc
  res = uvc_init(&ctx, NULL);
  if (res < 0)
  {
    uvc_perror(res, "uvc_init failed!");
    return res;
  }
  cout << "UVC initialized" << endl;

  // Find device
  res = uvc_find_device(ctx, &dev, 0, 0, NULL);
  if (res < 0)
  {
    uvc_perror(res, "uvc_find_device failed!");
    return res;
  }
  cout << "Found Device" << endl;

  // Open device
  res = uvc_open(dev, &devh);
  if (res < 0)
  {
    uvc_perror(res, "uvc_open failed!");
    return res;
  }
  cout << "Opened!\n";
  uvc_print_diag(devh, stderr);

  return res;
}

void stream(uvc_device_handle_t* &devh, uvc_stream_ctrl_t &ctrl) {
  uvc_error_t res;
  // Stream from uvc
  res = uvc_get_stream_ctrl_format_size(devh, &ctrl, UVC_COLOR_FORMAT_GRAY16, 160, 120, 9);
  uvc_print_stream_ctrl(&ctrl, stderr);
	if (res < 0) {
		uvc_perror(res, "stream error");
    return;
	}
	res = uvc_start_streaming(devh, &ctrl, callback, NULL, 0);
}


void callback(uvc_frame_t *frame, void *ptr)
{
  using namespace std;
  using namespace cv;

  Mat gray16(120, 160, CV_16UC1, (uint16_t *)frame->data);
  Mat gray8(120, 160, CV_8UC1);
  Mat heatmap(120,160,CV_8UC3);
  normalize(gray16, gray8, 0, 256, NORM_MINMAX, CV_8U);
  applyColorMap(gray8, heatmap, COLORMAP_HOT);
  imshow("heatmap", heatmap);
  waitKey(3);
}

