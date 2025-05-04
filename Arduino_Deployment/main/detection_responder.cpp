#include "detection_responder.h"
#include <Arduino.h>

void RespondToDetection(const TfLiteTensor* output) {
  Serial.println("Predictions:");
  for (int i = 0; i < output->dims->data[1]; ++i) {
    Serial.print("Class ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(output->data.int8[i]);
  }
}
