#ifndef DETECTION_RESPONDER_H
#define DETECTION_RESPONDER_H

#include "tensorflow/lite/c/common.h"

void RespondToDetection(const TfLiteTensor* output);

#endif  // DETECTION_RESPONDER_H
