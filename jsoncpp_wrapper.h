#pragma once
#include <string>
#include <fstream>
#include "json/json.h"
namespace DWQ {

class JsonReader
{
public:
	JsonReader() = default;

	~JsonReader() = default;

    const Json::Value& Root() {
        return root_;
    }

	bool ParseFromString(std::string json_content) {
        Json::CharReaderBuilder builder;
        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        const auto length = static_cast<int>(json_content.length());
        JSONCPP_STRING err;
        if (!reader->parse(json_content.c_str(), json_content.c_str() + length, &root_, &err)) {
            return false;
        }
        return true;
	}

    bool ParseFromFile(std::string filename) {
        std::ifstream ifs(filename);
        if (!ifs.is_open()) {
            return false;
        }
        Json::CharReaderBuilder builder;
        builder["collectComments"] = true;
        JSONCPP_STRING errs;
        if (!parseFromStream(builder, ifs, &root_, &errs)) {
            return false;
        }
        return true;
    }

private:
    Json::Value root_;
};

class JsonWriter
{
public:
    JsonWriter() = default;

    ~JsonWriter() = default;

    bool Write(std::string filename, Json::Value& root) {
        std::ofstream ofs(filename);
        if (ofs.is_open()) {
            Json::StreamWriterBuilder builder;
            const std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
            writer->write(root, &ofs);
            return true;
        }
        return false;
    }
};


}