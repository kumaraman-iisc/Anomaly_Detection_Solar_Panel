Solar Panel Anomaly Detection using Edge Devices (Deployable on Arduino Nicla Vision)
=============================================================================

Overview:
---------
This project focuses on classifying solar panel images into five categories:
1. Clean
2. Cracks
3. Discoloration
4. Dust
5. Organic matter (e.g., bird droppings)

We used several convolutional neural networks including:
- Pretrained MobileNetV2
- Pretrained EfficientNetB0
- Tiny CNN
- Custom ResNet-8 and ResNet-10

Each model is trained, evaluated, quantized, and prepared for deployment on the Arduino Nicla Vision board.

Directory Structure:
--------------------
- TensorFlow_Models/       # Saved Keras and TFLite models
- TensorFlow_Codes/        # Training and evaluation notebooks and python files
- Pytorch_model            # Pytorch models
- Arduino_deployment       # Deployment materials for Arduino IDE
- Impulse_Deployment       # Edge Impulse Deployment
- Readme.md                # Documentation of the project

Impulse_Deployment/
├── ei-solar_pv_anomaly_detection_clean_dust-openmv-v4  
  ├── ei_object_detection.py
  ├── new.py
  ├── labels.txt
  ├── trained.tflite

/Arduino_Deployment/
├── main
  ├── main.ino
  ├── resnet8_int8_model.cc
  ├── image_provider.cpp
  ├── image_provider.h
  ├── detection_responder.cpp
  ├── detection_responder.h
  ├── model_settings.h
├── resnet8_int8_model.cc

Deloyment through Tensorflow_Codes
├── data_preprocessing.py
├── tensorflow_models.py
├── quantization.py


Requirements:
-------------
- Python 3.8+
- TensorFlow 2.x
- NumPy, Matplotlib
- Arduino IDE (for deployment)
- Edge Impulse Studio- for deployment via EI

How to Run:
-----------
1. **Data Preparation**:
   - Organize your dataset with images inside folders named after class labels.
   - Split the dataset using ImageDataGenerator (with augmentation).

2. **Training**:
   - Choose a model architecture (MobileNetV2, Tiny CNN, ResNet-8, ResNet-10).
   - Train with data augmentation, dropout, L2 regularization, early stopping, and learning rate reduction.

3. **Evaluation**:
   - Plot training/validation accuracy and loss.
   - Generate and analyze the confusion matrix.

4. **Quantization**:
   - Convert `.keras` or `.h5` models to TensorFlow Lite format using representative datasets.
   - Apply INT8 quantization for deployment on Nicla Vision.

5. **Deployment**:
   - Upload the `.tflite` model to the Nicla Vision using Arduino tools or Edge Impulse.
   - Deploy with a custom Arduino sketch that loads the model and processes camera input.

Results:
--------
Best model performance:
- Accuracy: TinyCnn - 93% (on validation set)
- Deployment model size: MobileNet V2 0.35 - ~40 KB (via Edge Impulse)
                       : ResNet8 - ~50kB (quantized tflite model) 
- Inference time: ~100 ms on Nicla Vision

Credits:
--------
Developed as part of the EDGE AI course project.

Author- Kumar Aman, M.Tech, DM, IISc
      - Shreya U, M.Tech, CST, IISc
      - Harinath S, M.Tech, CST, IISc
      - Sher Singh Baghel, M.Tech, CST, IISc

Course instructor - Arjunan Pandarswamy

