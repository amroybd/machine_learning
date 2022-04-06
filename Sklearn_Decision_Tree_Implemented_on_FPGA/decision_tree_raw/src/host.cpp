/**
* Copyright (C) 2019-2021 Xilinx, Inc
*
* Licensed under the Apache License, Version 2.0 (the "License"). You may
* not use this file except in compliance with the License. A copy of the
* License is located at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
* License for the specific language governing permissions and limitations
* under the License.
*/

#include "cmdlineparser.h"
#include <iostream>
#include <cstring>

// XRT includes
#include "experimental/xrt_bo.h"
#include "experimental/xrt_device.h"
#include "experimental/xrt_kernel.h"

#define DATA_SIZE 4096

int main(int argc, char** argv) {
    // Command Line Parser
    sda::utils::CmdLineParser parser;

    // Switches
    //**************//"<Full Arg>",  "<Short Arg>", "<Description>", "<Default>"
    parser.addSwitch("--xclbin_file", "-x", "input binary file string", "");
    parser.addSwitch("--device_id", "-d", "device index", "0");
    parser.parse(argc, argv);

    // Read settings
    std::string binaryFile = parser.value("xclbin_file");
    int device_index = stoi(parser.value("device_id"));

    if (argc < 3) {
        parser.printHelp();
        return EXIT_FAILURE;
    }

    std::cout << "Open the device" << device_index << std::endl;
    auto device = xrt::device(device_index);
    std::cout << "Load the xclbin " << binaryFile << std::endl;
    auto uuid = device.load_xclbin(binaryFile);

    size_t vector_size_bytes = sizeof(int) * DATA_SIZE;

    auto krnl = xrt::kernel(device, uuid, "decision_tree");

    std::cout << "Allocate Buffer in Global Memory\n";
    auto bo0 = xrt::bo(device, vector_size_bytes, krnl.group_id(0));
    auto bo1 = xrt::bo(device, vector_size_bytes, krnl.group_id(1));
    auto bo2 = xrt::bo(device, vector_size_bytes, krnl.group_id(2));
    auto bo3 = xrt::bo(device, vector_size_bytes, krnl.group_id(3));
    auto bo4 = xrt::bo(device, vector_size_bytes, krnl.group_id(4));
    auto bo5 = xrt::bo(device, vector_size_bytes, krnl.group_id(5));
    auto bo6 = xrt::bo(device, vector_size_bytes, krnl.group_id(6));
    auto bo7 = xrt::bo(device, vector_size_bytes, krnl.group_id(7));
    auto bo_out = xrt::bo(device, vector_size_bytes, krnl.group_id(8));

    // Map the contents of the buffer object into host memory
    auto bo0_map = bo0.map<int*>();
    auto bo1_map = bo1.map<int*>();
    auto bo2_map = bo2.map<int*>();
    auto bo3_map = bo4.map<int*>();
    auto bo4_map = bo4.map<int*>();
    auto bo5_map = bo5.map<int*>();
    auto bo6_map = bo6.map<int*>();
    auto bo7_map = bo7.map<int*>();
    auto bo_out_map = bo_out.map<int*>();
    std::fill(bo0_map, bo0_map + DATA_SIZE, 0);
    std::fill(bo1_map, bo1_map + DATA_SIZE, 0);
    std::fill(bo2_map, bo2_map + DATA_SIZE, 0);
    std::fill(bo3_map, bo3_map + DATA_SIZE, 0);
    std::fill(bo4_map, bo4_map + DATA_SIZE, 0);
    std::fill(bo5_map, bo5_map + DATA_SIZE, 0);
    std::fill(bo6_map, bo6_map + DATA_SIZE, 0);
    std::fill(bo7_map, bo7_map + DATA_SIZE, 0);
    std::fill(bo_out_map, bo_out_map + DATA_SIZE, 0);

    // Create the test data
    int bufReference[DATA_SIZE];
    for (int i = 0; i < DATA_SIZE; ++i) {
        bo0_map[i] = i;
        bo1_map[i] = i;
        bo2_map[i] = i;
        bo3_map[i] = i;
        bo4_map[i] = i;
        bo5_map[i] = i;
        bo6_map[i] = i;
        bo7_map[i] = i;
        
    }

    // Synchronize buffer content with device side
    std::cout << "synchronize input buffer data to device global memory\n";

    bo0.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    bo1.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    bo2.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    bo3.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    bo4.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    bo5.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    bo6.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    bo7.sync(XCL_BO_SYNC_BO_TO_DEVICE);

    std::cout << "Execution of the kernel\n";
    auto run = krnl(bo0, bo1, bo2, bo3, bo4, bo5, bo6, bo7, bo_out, DATA_SIZE);
    run.wait();

    // Get the output;
    std::cout << "Get the output data from the device" << std::endl;
    bo_out.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    for (int i = 0; i < DATA_SIZE; ++i) {
       bufReference[i] = bo_out_map[i];
    }
    // Validate our results
    if (std::memcmp(bo_out_map, bufReference, DATA_SIZE))
        throw std::runtime_error("Value read back does not match reference");

    std::cout << "TEST PASSED\n";
    return 0;
}

