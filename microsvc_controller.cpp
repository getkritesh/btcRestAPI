#include "std_micro_service.hpp"
#include "microsvc_controller.hpp"
#include "block_manager.hpp"

using namespace web;
using namespace http;

void MicroserviceController::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&MicroserviceController::handleGet, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&MicroserviceController::handlePut, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&MicroserviceController::handlePost, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&MicroserviceController::handleDelete, this, std::placeholders::_1));
 }

void MicroserviceController::handleGet(http_request message) {
	auto path = requestPath(message);

	if (!path.empty()) {
		if (*(reinterpret_cast<std::string*>(&path[0]))== "blocks") {
			auto response = json::value::object();

			BlockInformation Inputblock{

			};
			
			BlockManager blockmgr;
			std::string TranString = blockmgr.block(Inputblock);

			// Assign block Information Receive from above method to response
			message.reply(status_codes::OK, response);
		}
	}
	else {
		message.reply(status_codes::NotFound);
	}
}

void MicroserviceController::handlePut(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PUT));
}


void MicroserviceController::handlePost(http_request message) {
	auto path = requestPath(message);
	if (!path.empty() &&
		(*(reinterpret_cast<std::string*>(&path[0])) == "transaction")) 
	{
	message.
		extract_json().
		then([=](json::value request) {
		try {
			web::json::value& temp = request.at(U("inputs"));			
			web::json::value& temp_output = request.at(U("outputs"));
			
			TransactionInfo Transaction{			
			};

			BlockManager blockmgr;
			std::string TranString =blockmgr.transaction(Transaction);
			json::value response;

			// Save Transaction string in response and return back

			message.reply(status_codes::OK, response);
		}
		catch (BlockManagerException & e) {
			message.reply(status_codes::BadRequest, e.what());
		}
		catch (json::json_exception & e) {
			message.reply(status_codes::BadRequest);
		}
	});
   }
 }


void MicroserviceController::handleDelete(http_request message) {    
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::DEL));
}

json::value MicroserviceController::responseNotImpl(const http::method & method) {
    auto response = json::value::object();
    response[U("serviceName")] = json::value::string(U("blockchain Mircroservice "));
    response[U("http_method")] = json::value::string(method);
    return response ;
}