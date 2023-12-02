| Supported Targets | ESP32-S3 |
| ----------------- | -------- |
|  ESP-IDF Version  |  v5.1.1  |
| ----------------- | -------- |

# _Handwritten Digit Recognition Project_

this project is to fulfill the assignments for UGM's advanced microcontroller-based systems course. This project is the implementation of digit handwritten recognition training on Tensorflow Python and tests the model/inferencing on ESP32s3 with TensorFlow Lite Micro model programmed with Espressif-IDF. The project only require ESP32s3, LCD ILI9341 + xp2046 touchscreen and a few wire.



## How to build
```
idf.py build                        # build program
idf.py flash -p COM{your_number}    # flash to your microcontroller specify {your_number}   
```

## Folder contents

The project **Handwritten Digit Recognition Project** contains one source file in C++ language [main.cpp](main/main.cpp). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt             
├── main
│   ├── model_data*.h          This is model generated from model_train.ipynb file (Tensorflow v2 + Python)
│   ├── NeuralNetwork.*        This is NN to initiate, input data and request data output from the model that has been trained
│   ├── lcd_touch_init.*       This is lcd ili9341 + xpt2046 structure init (not library)
│   ├── lvgl_component_init.*  This is initialization component with LVGL
│   ├── squareline_ui          This is ui exported from squareline studio 1.3.3
│   ├── CMakeLists.txt         For build with idf.py build which using cmake for compiling all whole code
│   └── main.cpp               This is main program 
└── README.md                  This is the file you are currently reading
```
