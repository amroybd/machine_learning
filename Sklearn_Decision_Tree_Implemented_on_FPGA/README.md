# Implement decision tree on FPGA
This is an example of how to implement a small decision tree ( max depth approx. 10 or less) on an FPGA board. The decision tree was trained using Sklearn. The dataset can be downloaded from [here](https://www.kaggle.com/datasets/laavanya/human-stress-detection-in-and-through-sleep). For hardware implementation, I have used [Vitis hello world example](https://github.com/Xilinx/Vitis_Accel_Examples/tree/master/host_xrt/hello_world_xrt) as a reference to build the hardware for FPGA. Remember this solution will only work for a small decision tree.
## Train the model
Go to the Training folder where you will find the notebook which can be used to train the model. 


## Hardware build
The notebook will generate if-else code using a function called tree_to_code which can be used to build the hardware. You have to edit this if-else code as per your need. I have used c++ to build the hardware so I have edited this generated code for c++. Remember every time you train the model this function will generate new if-else code. I have used Vitis to build the hardware. After the successful build, Vitis will generate a binary file that can be used on an FPGA.


## Test on FPGA
I have used pynq library to run that binary file on the board. I have taken this [pynq example](https://github.com/Xilinx/Alveo-PYNQ/blob/master/pynq_alveo_examples/notebooks/1_introduction/1-vector-addition.ipynb) as a reference.
