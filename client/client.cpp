#include <iostream>
#include <string>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "./gen-cpp/Coordinator.h"
#include "./gen-cpp/distributedML.h"

using namespace std;
using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using namespace apache::thrift;
using namespace distributedML;

int main(int argc, char** argv) {
    // Read IP and port from command line
    if (argc < 6) {
      cout << "Usage: ./client <coordinator_ip> <coordinator_port> <dir_path> <rounds> <epochs>" << endl;
      return 1;
    }

    string ip = argv[1];
    int port = stoi(argv[2]);
    string dir = argv[3]
    int rounds = stoi(argv[4]);
    int epochs = stoi(argv[5]);

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
        string dir = "./ML/ML/letters";
        double res = client.train(dir, rounds, epochs, 20, 26, 0.0001, "compute_node.txt");
        cout << "Connected to server!" << endl;

        cout << "Validation error: " << res << endl;

        // Close the connection
        transport->close();
        cout << "Connection closed." << endl;

    } catch (TException& tx) {
        cerr << "Thrift error: " << tx.what() << endl;
        return 1;
    }

    return 0;
}
