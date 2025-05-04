#ifndef IMAGE_PROVIDER_H
#define IMAGE_PROVIDER_H

#include "tensorflow/lite/c/common.h"

bool InitCamera();
TfLiteStatus CaptureImage(int8_t* image_data, int image_len);

#endif  // IMAGE_PROVIDER_H
