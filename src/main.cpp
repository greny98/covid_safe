#include <unistd.h>
#include "uvc_com.h"

int main(int argc, char const *argv[]) {
  UvcCom uvc_com{};
  uvc_com.init();
  uvc_com.stream();
  sleep(10);
  return 0;
}
