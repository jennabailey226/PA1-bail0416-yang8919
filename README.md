## **Build Instructions**
### **Step 1: Make sure you are at the top of the Repository**
```sh
cd <repository_name>
```
### **Step 2: Compile the Coordinator and ComputeNode**
```sh
mkdir build && cd build
cmake ..
make
```
### **Step 3: Compile the Client**
```sh
cd client
mkdir build && cd build
cmake ..
make
```
## **Execution Instructions**
### **Step 1: Start Compute Nodes**
```sh
./computeNode <port> <load_probability>
```
Example:
```sh
./computeNode 9091 0.8
```
### **Step 2: Start the Coordinator**
```sh
./coordinator <port> <scheduling_policy>
```
Example
```sh
./coordinator 5105 1
```
### **Step 3: Run the Client**
```sh
./client <coordinator_ip> <coordinator_port> <training_data_path> <rounds> <epochs>
```
Example
```sh
./client csel-cuda-02 5105 /home/yang8919/PA1-bail0416-yang8919-yahui 1 75
```
## **File Structure**
.
├── build/                    # Compiled binaries and CMake build files
├── gen-cpp/                  # Thrift-generated C++ files
├── ML/                       # Machine Learning implementation
│   ├── ML.cpp                # MLP model implementation
│   ├── ML.hpp                # MLP model header
├── client/
│   ├── client.cpp            # Client implementation
│   ├── CMakeLists.txt        # Build instructions for client
├── CMakeLists.txt            # Main build configuration
├── compute_nodes.txt         # A file that lists the ip and port of possible compute nodes
├── ComputeNode_server.cpp    # Compute node implementation
├── Coordinator_server.cpp    # Coordinator implementation
├── dir.txt                   # The path that is used for client server
├── distributedML.thrift      # Thrift interface definition
├── README.md                 # This file
