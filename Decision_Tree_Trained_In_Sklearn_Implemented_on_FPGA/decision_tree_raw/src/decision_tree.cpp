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

#define BUFFER_SIZE 1024
#define DATA_SIZE 4096

// TRIPCOUNT identifier
const unsigned int c_len = DATA_SIZE / BUFFER_SIZE;
const unsigned int c_size = BUFFER_SIZE;



extern "C" {
void decision_tree(
		  const unsigned int* in1, // Read-Only Vector 1
          const unsigned int* in2, // Read-Only Vector 2
          const unsigned int* in3, // Read-Only Vector 3
		  const unsigned int* in4, // Read-Only Vector 4
		  const unsigned int* in5, // Read-Only Vector 5
		  const unsigned int* in6, // Read-Only Vector 6
		  const unsigned int* in7, // Read-Only Vector 7
		  const unsigned int* in8, // Read-Only Vector 8
          unsigned int* out_r,     // Output Result
          int size                 // Size in integer
          ) {

    unsigned int v1_buffer[BUFFER_SIZE];   // Local memory to store vector1
    unsigned int v2_buffer[BUFFER_SIZE];   // Local memory to store vector2
    unsigned int v3_buffer[BUFFER_SIZE];   // Local memory to store vector3
    unsigned int v4_buffer[BUFFER_SIZE];   // Local memory to store vector4
    unsigned int v5_buffer[BUFFER_SIZE];   // Local memory to store vector5
    unsigned int v6_buffer[BUFFER_SIZE];   // Local memory to store vector6
    unsigned int v7_buffer[BUFFER_SIZE];   // Local memory to store vector7
    unsigned int v8_buffer[BUFFER_SIZE];   // Local memory to store vector8
    unsigned int vout_buffer[BUFFER_SIZE]; // Local Memory to store result

    // Per iteration of this loop perform BUFFER_SIZE vector addition
    for (int i = 0; i < size; i += BUFFER_SIZE) {
#pragma HLS LOOP_TRIPCOUNT min = c_len max = c_len
        int chunk_size = BUFFER_SIZE;
        // boundary checks
        if ((i + BUFFER_SIZE) > size) chunk_size = size - i;


    read1:
        for (int j = 0; j < chunk_size; j++) {
#pragma HLS LOOP_TRIPCOUNT min = c_size max = c_size
#pragma HLS PIPELINE II = 1
            v1_buffer[j] = in1[i + j];
        }

    read2:
        for (int j = 0; j < chunk_size; j++) {
#pragma HLS LOOP_TRIPCOUNT min = c_size max = c_size
#pragma HLS PIPELINE II = 1
            v2_buffer[j] = in2[i + j];
        }

    read3:
	    for (int j = 0; j< chunk_size; j++){
#pragma HLS LOOP_TRIPCOUNT min = c_size max = c_size
#pragma HLS PIPELINE II = 1
	    	v3_buffer[j] = in3[i + j];
	    }

	read4:
		for (int j = 0; j< chunk_size; j++){
#pragma HLS LOOP_TRIPCOUNT min = c_size max = c_size
#pragma HLS PIPELINE II = 1
		    v4_buffer[j] = in4[i + j];
		}

	read5:
		for (int j = 0; j< chunk_size; j++){
#pragma HLS LOOP_TRIPCOUNT min = c_size max = c_size
#pragma HLS PIPELINE II = 1
			 v5_buffer[j] = in5[i + j];
		}

	read6:
		for (int j = 0; j< chunk_size; j++){
#pragma HLS LOOP_TRIPCOUNT min = c_size max = c_size
#pragma HLS PIPELINE II = 1
		    v6_buffer[j] = in6[i + j];
		}

	read7:
		for (int j = 0; j< chunk_size; j++){
#pragma HLS LOOP_TRIPCOUNT min = c_size max = c_size
#pragma HLS PIPELINE II = 1
		    v7_buffer[j] = in7[i + j];
		}

	read8:
		for (int j = 0; j< chunk_size; j++){
#pragma HLS LOOP_TRIPCOUNT min = c_size max = c_size
#pragma HLS PIPELINE II = 1
		    v8_buffer[j] = in8[i + j];
		}

    // PIPELINE pragma reduces the initiation interval for loop by allowing the
    // concurrent executions of operations
    decision_tree:
        for (int j = 0; j < chunk_size; j++) {
#pragma HLS LOOP_TRIPCOUNT min = c_size max = c_size
#pragma HLS PIPELINE II = 1
            // Below code generated from the function shown in decision tree generation folder. If you train the model the function will
			// generate different code. That generated code will be used here.
            if (v6_buffer[j] <= 84.5){
                if (v6_buffer[j] <= 79.5){
                    vout_buffer[j]= 0;}
                else{
                    vout_buffer[j]= 1;}}
            else{
                if (v1_buffer[j] <= 79.5){
                    vout_buffer[j]= 2;}
                else{
                    if (v8_buffer[j] <= 74.5){
                        vout_buffer[j]= 3;}
                    else{
                        vout_buffer[j]= 4;}}}
        }

    // burst write the result
    write:
        for (int j = 0; j < chunk_size; j++) {
#pragma HLS LOOP_TRIPCOUNT min = c_size max = c_size
#pragma HLS PIPELINE II = 1
            out_r[i + j] = vout_buffer[j];
        }
    }
}
}

