# Implement decision tree on FPGA
This is an example of how to implement a decision tree on an FPGA board. The decision tree was trained using Sklearn. The dataset
can be downloaded from [here](https://www.kaggle.com/datasets/laavanya/human-stress-detection-in-and-through-sleep). For hardware implementation, I have used [Vitis 
hello world example](https://github.com/Xilinx/Vitis_Accel_Examples/tree/master/host_xrt/hello_world_xrt) as a reference to build the hardware for FPGA (alveo u280 data center accelerator card). Here, I have also
demonstrated how to convert the decision tree model to if-else code and also covert the tree into a decision table. Also demonstrated how to use that if-else code and
decision table to make predictions.

## Train the model
Go to the "Tree_to_Table" folder where you will find the notebook which can be used to train the model and convert the tree to if_else code and table. Also, you can
use this notebook file to use if_else code and table to make prediction.


## Hardware build (for alveo u280 data center accelerator card )
Check "src" folder in "Decision_Tree_HW" for source files. The c++ kernel can be fouund in "decision_tree.cpp". I have used Vitis to build the HW.


## Test on FPGA
I have used pynq library to run that binary file on the board. I have taken this [pynq example](https://github.com/Xilinx/Alveo-PYNQ/blob/master/pynq_alveo_examples/notebooks/1_introduction/1-vector-addition.ipynb) 
as a reference.
