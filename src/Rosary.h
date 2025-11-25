#ifndef ROSARY_H
#define ROSARY_H

#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <pplx/pplx.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace web;
using namespace web::http;
using namespace web::http::client;

class Rosary {
private:
    std::string api_base = "https://the-rosary-api.vercel.app";
    http_client_config client_config;
    
    http_request create_request(const std::string& endpoint, const std::string& method, const std::string& data = "") {
        http_request request;
        
        if (method == "GET") {
            request.set_method(methods::GET);
        } else if (method == "POST") {
            request.set_method(methods::POST);
        } else if (method == "PUT") {
            request.set_method(methods::PUT);
        } else if (method == "DEL") {
            request.set_method(methods::DEL);
        }
        
        request.set_request_uri(utility::conversions::to_string_t(endpoint));
        
        // Set headers
        request.headers().add(U("Host"), U("the-rosary-api.vercel.app"));
        request.headers().add(U("Content-Type"), U("application/json"));
        request.headers().add(U("User-Agent"), U("Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/115.0"));
        
        if (!data.empty() && (method == "POST" || method == "PUT")) {
            request.set_body(data);
        }
        
        return request;
    }
    
    std::string build_query_params(const std::map<std::string, std::string>& params) {
        if (params.empty()) return "";
        
        std::string query = "?";
        bool first = true;
        for (const auto& param : params) {
            if (!param.second.empty()) {
                if (!first) query += "&";
                // Кодируем значения параметров
                auto encoded_value = web::uri::encode_data_string(utility::conversions::to_string_t(param.second));
                query += param.first + "=" + utility::conversions::to_utf8string(encoded_value);
                first = false;
            }
        }
        return query;
    }
    
    pplx::task<json::value> make_api_call(const std::string& endpoint, const std::string& method, const std::string& data = "") {
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        auto request = create_request(endpoint, method, data);

        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: ") + utility::conversions::to_string_t(std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: ") + utility::conversions::to_string_t(e.what()));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
public:
    Rosary(){
        client_config.set_validate_certificates(false);
    }

    pplx::task<json::value> get_today() {
        return make_api_call("/v1/today", "GET");
    }

    pplx::task<json::value> get_yesterday() {
        return make_api_call("/v1/yesterday", "GET");
    }

    pplx::task<json::value> get_tomorrow() {
        return make_api_call("/v1/tomorrow", "GET");
    }

    pplx::task<json::value> get_monday() {
        return make_api_call("/v1/monday", "GET");
    }

    pplx::task<json::value> get_tuesday() {
        return make_api_call("/v1/tuesday", "GET");
    }

    pplx::task<json::value> get_wednesday() {
        return make_api_call("/v1/wednesday", "GET");
    }

    pplx::task<json::value> get_thursday() {
        return make_api_call("/v1/thursday", "GET");
    }

    pplx::task<json::value> get_friday() {
        return make_api_call("/v1/friday", "GET");
    }

    pplx::task<json::value> get_saturday() {
        return make_api_call("/v1/saturday", "GET");
    }

    pplx::task<json::value> get_sunday() {
        return make_api_call("/v1/sunday", "GET");
    }

    pplx::task<json::value> get_by_date(int date) {
        return make_api_call("/v1/date/" + std::to_string(date), "GET");
    }

    pplx::task<json::value> get_joyful() {
        return make_api_call("/v1/joyful", "GET");
    }

    pplx::task<json::value> get_glorious() {
        return make_api_call("/v1/glorious", "GET");
    }

    pplx::task<json::value> get_sorrowful() {
        return make_api_call("/v1/sorrowful", "GET");
    }

    pplx::task<json::value> get_luminous() {
        return make_api_call("/v1/luminous", "GET");
    }

    pplx::task<json::value> get_random() {
        return make_api_call("/v1/random", "GET");
    }

    pplx::task<json::value> get_list() {
        return make_api_call("/v1/list", "GET");
    }

    pplx::task<json::value> get_novena() {
        return make_api_call("/v1/novena", "GET");
    }

    pplx::task<json::value> get_novena_by_date(int date) {
        return make_api_call("/v1/novena/" + std::to_string(date), "GET");
    }

    pplx::task<json::value> get_54day_novena() {
        return make_api_call("/v1/54daynovena", "GET");
    }
};

#endif
