#include "Event.h"

#include <ctime>
#include <iomanip>
#include <sstream>

CEvent::CEvent() {
    m_timestamp = std::chrono::system_clock::now();
}

CEvent::~CEvent() {

}

std::string CEvent::toJsonString() const {
    using namespace std::chrono;

    auto t = system_clock::to_time_t(m_timestamp);

    std::stringstream stream;
    stream << std::put_time(std::localtime(&t), "%FT%T%z");

    auto jsonString = std::string("{\n") +
                      std::string("  \"timestamp\": \"") + stream.str() + std::string("\"\n") +
                      std::string("}");

    return jsonString;
}
