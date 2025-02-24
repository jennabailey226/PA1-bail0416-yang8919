namespace cpp distributedML

struct Weights {
    1: list<list<double>> W,
    2: list<list<double>> V
}

struct Gradient {
    1: list<list<double>> dW, // Gradient of W
    2: list<list<double>> dV  // Gradient of V
}

// Structure for compute node information (IP and port)
struct ComputeNodeInfo {
    1: string ip,  // IP address of compute node
    2: i32 port    // Port number of compute node
}

service Coordinator {
    list<ComputeNodeInfo> load_compute_nodes(1: string filename)

    double train(
        1: string dir,                // Path to training data
        2: i32 rounds,                // Number of training rounds
        3: i32 epochs,                // Training epochs per round
        4: i32 h,                     // Number of hidden units
        5: i32 k,                     // Number of output units
        6: double eta                 // Learning rate
        7: string compute_nodes_file  // Compute Nodes File
    )
}

service ComputeNode {
    Gradient trainModel(
        1: Weights weights,   // Model weights (W, V)
        2: string trainFile,  // Training file path
        3: double eta,        // Learning rate
        4: i32 epochs         // Number of training epochs
    )
}
