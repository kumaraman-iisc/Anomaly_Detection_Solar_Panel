#include "model_resnet8_int8.h"
#include "image_provider.h"
#include "detection_responder.h"

#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"

constexpr int kTensorArenaSize = 135 * 1024;
uint8_t tensor_arena[kTensorArenaSize];

tflite::MicroErrorReporter micro_error_reporter;
tflite::ErrorReporter* error_reporter = &micro_error_reporter;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  model = tflite::GetModel(g_model_resnet8_int8);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter, "Model version mismatch.");
    return;
  }

  static tflite::AllOpsResolver resolver;
  static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
  interpreter = &static_interpreter;

  if (interpreter->AllocateTensors() != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors failed.");
    return;
  }

  input = interpreter->input(0);

  if (!InitCamera()) {
    TF_LITE_REPORT_ERROR(error_reporter, "Camera init failed.");
    return;
  }
}

void loop() {
  if (CaptureImage(input->data.int8, input->bytes) != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "Image capture failed.");
    return;
  }

  if (interpreter->Invoke() != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "Model inference failed.");
    return;
  }

  TfLiteTensor* output = interpreter->output(0);
  RespondToDetection(output);
}
