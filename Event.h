#ifndef EVENT_H
#define EVENT_H

#include <chrono>
#include <string>

class CEvent {
public:
    CEvent();
    ~CEvent();

    std::string toJsonString() const;

private:
    std::string m_source;
    std::chrono::time_point<std::chrono::system_clock> m_timestamp;
};

#endif
