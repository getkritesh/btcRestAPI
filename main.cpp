#include <iostream>
#include "block_interrupt_handler.hpp"
#include "microsvc_controller.hpp"

using namespace web;
using namespace cfx;

int main(int argc, const char * argv[]) {
	InterruptHandler::hookSIGINT();

	MicroserviceController server;
	std::string endpoint_temp = "http://127.0.0.1:2826/v1/api";
	server.setEndpoint(endpoint_temp);

	try {
		// wait for server initialization...
		server.accept().wait();
		std::cout << "Microservice now listening for requests at: " << server.endpoint() << '\n';

		InterruptHandler::waitForBlockInterrupt();

		server.shutdown().wait();
	}
	catch (std::exception & e) {
		std::cerr << "somehitng wrong happen! :(" << '\n';
	}
	catch (...) {
		std::cerr << "uncaught Exception ! :(" << '\n';
	}
	return 0;
}