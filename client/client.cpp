#include <iostream>
#include <string>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "../gen-cpp/Coordinator.h"

using namespace std;
using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using namespace apache::thrift;
using namespace distributedML;

int main(int argc, char** argv) {
    // Read IP and port from command line
    if (argc < 6) {
	    std::cout << "Usage: ./client <coordinator_ip> <coordinator_port> <dir_path> <rounds> <epochs>" << std::endl;
      exit(1);
    }

    std::string ip = argv[1];
    int port = std::stoi(argv[2]);
    std::string dir = argv[3];
    int rounds = std::stoi(argv[4]);
    int epochs = std::stoi(argv[5]);

    try {
        // Create a socket connection
        std::shared_ptr<TTransport> socket(new TSocket(ip, port));
        std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

        // Create client
        CoordinatorClient client(protocol);

        // Connect to the server
        transport->open();

        // Call the server's ping() function

        double res = client.train(dir, rounds, epochs, 20, 26, 0.0001, "compute_node.txt");
	      std::cout << "Connected to server!" << std::endl;

	      std::cout << "Validation error: " << res << std::endl;

        // Close the connection
        transport->close();
	      std::cout << "Connection closed." << std::endl;

    } catch (TException& tx) {
	      std::cout << "Thrift error: " << tx.what() << std::endl;
        exit(1);
    }

    return 0;
}
