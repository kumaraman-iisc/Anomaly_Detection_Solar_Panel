#include "image_provider.h"
#include <Arduino_OV767X.h>

OV767X cam;

bool InitCamera() {
  if (!cam.begin(QVGA, GRAYSCALE)) {
    return false;
  }
  cam.setFrameRate(5);
  return true;
}

TfLiteStatus CaptureImage(int8_t* image_data, int image_len) {
  cam.readFrame(image_data, image_len);
  return kTfLiteOk;
}
