#define BUFFER_SIZE 1024
#define DATA_SIZE 4096


const unsigned int c_len = DATA_SIZE / BUFFER_SIZE;
const unsigned int c_size = BUFFER_SIZE;
const float tree_data[9][7] = {{0.0, 7.0, 59.5, 1.0, 4.0, 0.0, -1.0},
                      {1.0, 5.0, 79.5, 2.0, 3.0, 0.0, -1.0},
                      {2.0, -1.0, -1.0, -1.0, -1.0, 1.0, 0.0},
                      {3.0, -1.0, -1.0, -1.0, -1.0, 1.0, 1.0},
                      {4.0, 5.0, 94.5, 5.0, 6.0, 0.0, -1.0},
                      {5.0, -1.0, -1.0, -1.0, -1.0, 1.0, 2.0},
                      {6.0, 7.0, 74.5, 7.0, 8.0, 0.0, -1.0},
                      {7.0, -1.0, -1.0, -1.0, -1.0, 1.0, 3.0},
                      {8.0, -1.0, -1.0, -1.0, -1.0, 1.0, 4.0}};


extern "C" {
void decision_tree(
		  const float* in1, // Read-Only Vector 1
          float* out_r,     // Output Result
          int size                 // Size in integer
          ) {

    float vout_buffer[BUFFER_SIZE]; // Local Memory to store result
    float v1_buffer[BUFFER_SIZE];

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

    // PIPELINE pragma reduces the initiation interval for loop by allowing the
    // concurrent executions of operations
    decision_tree:
        for (int j = 0; j < chunk_size; j++) {
#pragma HLS LOOP_TRIPCOUNT min = c_size max = c_size
#pragma HLS PIPELINE II = 1
            // perform vector addition
            int node = 0;
            int x = node;
            int next_node = 0;
            float input_var = 0.0;
            int variable_index_int = 0;
            float final_output_from_tree = 0;
            float variable_index = tree_data[x][1];
            float compare_value = tree_data[x][2];
            if (variable_index == -1){
                final_output_from_tree = tree_data[x][6];
            }
            else{
                variable_index_int = (int)variable_index;
                input_var = v1_buffer[variable_index_int];
                if (compare_value == -1){
                    final_output_from_tree = tree_data[x][6];}
                else{
                    while(compare_value != -1){
                        if (input_var < compare_value){
                            next_node = tree_data[x][3];
                            next_node = (int)next_node;}
                        else{
                            next_node = tree_data[x][4];
                            next_node = (int)next_node;}

                        x = next_node;
                        variable_index = tree_data[x][1];
                        variable_index_int = (int)variable_index;
                        input_var = v1_buffer[variable_index_int];
                        compare_value = tree_data[x][2];
                        if(compare_value == -1){
                            final_output_from_tree = tree_data[x][6];

                        }
                    }
                }
            }
            vout_buffer[j] = final_output_from_tree;
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




