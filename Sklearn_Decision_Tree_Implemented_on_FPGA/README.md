# Implement decision tree on FPGA
This is an example of how to implement a small decision tree ( max depth approx. 10 or less) on an FPGA board. The decision tree was trained using Sklearn. The dataset can be download from [here](https://www.kaggle.com/datasets/laavanya/human-stress-detection-in-and-through-sleep). For hardware implementation I have used [Vitis hello world example](https://github.com/Xilinx/Vitis_Accel_Examples/tree/master/host_xrt/hello_world_xrt) as reference to build the hardware for FPGA. Remember this solution will only work for small decision tree.
## Train the model
Go to folder Training there you will find the notobook which can be used to traiin the model.


## Hardware build
The notebook will generate if-else code using a function called tree_to_code which can be used to build the hardware. You have to edit this if-else code as per your need. I have used c++ to build the hardware so I have edited this generated code for c++. Remember every time you train the model this function will generate new if-else code. I have used vitis to build the hardware. After the successful build vitis will generate a binary file which can be used on an FPGA.


## Test on FPGA
I have used pynq library to run that binary file on the board. I have taken this [pynq example](https://github.com/Xilinx/Alveo-PYNQ/blob/master/pynq_alveo_examples/notebooks/1_introduction/1-vector-addition.ipynb) as reference.
