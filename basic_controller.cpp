
#include "basic_controller.hpp"
#include "network_utils.hpp"
#include<iostream>
using namespace utility;

namespace cfx {
    BasicController::BasicController() {
    }

    BasicController::~BasicController() {
    }

    void BasicController::setEndpoint(std::string & value) {

		utility::char_t ** temp = reinterpret_cast<utility::char_t **>(&value);
		const utility::char_t ** temp1 = const_cast<const utility::char_t **>(temp); 

		uri endpointURI(*temp1);
        uri_builder endpointBuilder;				

        endpointBuilder.set_scheme(endpointURI.scheme());

		utility::char_t ** temp_i4 = reinterpret_cast<utility::char_t **>(&NetworkUtils::hostIP4());
		const utility::char_t ** temp1_ip4 = const_cast<const utility::char_t **>(temp_i4);
        endpointBuilder.set_host(*temp1_ip4);
                
        endpointBuilder.set_port(endpointURI.port());
        endpointBuilder.set_path(endpointURI.path());
        _listener = http_listener(endpointBuilder.to_uri());
    }

    std::string BasicController::endpoint() {
		utility::string_t temp = _listener.uri().to_string();
		std::string **temp_string = reinterpret_cast<std::string **>(&temp);
		return **temp_string;
    }

    pplx::task<void> BasicController::accept() {
        initRestOpHandlers();
        return _listener.open();
    }

    pplx::task<void> BasicController::shutdown() {
        return _listener.close();
    }

    std::vector<utility::string_t> BasicController::requestPath(const http_request & message) {
        auto relativePath = uri::decode(message.relative_uri().path());
        return uri::split_path(relativePath);        
    }
}