# Edge Impulse - OpenMV Image Classification Example (Top-1 Prediction)
#
# This work is licensed under the MIT license.
# Copyright (c) 2013-2024 OpenMV LLC. All rights reserved.
# https://github.com/openmv/openmv/blob/master/LICENSE

import sensor, time, ml, uos, gc

# Initialize the camera sensor
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_windowing((240, 240))
sensor.skip_frames(time=2000)

# Load the model
net = None
labels = None

try:
    model_path = "trained.tflite"
    net = ml.Model(model_path, load_to_fb=uos.stat(model_path)[6] > (gc.mem_free() - (64 * 1024)))
except Exception as e:
    raise Exception('Failed to load "{}". Did you copy the .tflite and labels.txt to the device? ({})'.format(model_path, e))

# Load labels
try:
    with open("labels.txt") as f:
        labels = [line.strip() for line in f]
except Exception as e:
    raise Exception('Failed to load "labels.txt". Did you copy it to the device? ({})'.format(e))

# Run inference loop
clock = time.clock()
while True:
    clock.tick()
    img = sensor.snapshot()

    # Get predictions
    prediction_scores = net.predict([img])[0].flatten().tolist()
    max_idx = prediction_scores.index(max(prediction_scores))

    # Print the top prediction
    print("Prediction: {} ({:.2f})".format(labels[max_idx], prediction_scores[max_idx]))
    print("FPS:", clock.fps())
