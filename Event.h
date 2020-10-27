#ifndef EVENT_H
#define EVENT_H

#include <chrono>
#include <string>

#define E_STRING_NONE ""
#define E_UINT_NONE -1
#define E_UFLOAT_NONE = -1.0F

class CEvent
{
public:
    ~CEvent();

    virtual std::string toJsonString() const = 0;
    void log(unsigned int level = 2U) const;

protected:
    CEvent();

    std::string baseJsonMaps() const;

    std::string m_source;
    std::string m_type;

private:
    std::chrono::time_point<std::chrono::system_clock> m_timestamp;
};

#define E_SYSTEM_STARTUP "startup"
#define E_SYSTEM_SHUTDOWN "shutdown"

class CSystemEvent : public CEvent
{
public:
    CSystemEvent(std::string type,
                 std::string version = E_STRING_NONE,
                 std::string gitVersion = E_STRING_NONE,
                 int exitCode = E_UINT_NONE);

    std::string toJsonString() const;

private:
    std::string m_version;
    std::string m_gitVersion;
    int m_exitCode;
};

#define E_DMR_RF_VOICE_HEADER "rf_voice_header"
#define E_DMR_RF_VOICE_END "rf_voice_end"
#define E_DMR_NET_VOICE_HEADER "net_voice_header"
#define E_DMR_NET_VOICE_END "net_voice_end"

class CDmrEvent : public CEvent
{
public:
    CDmrEvent(std::string type,
              int timeslot,
              int id,
              std::string callsign,
              int target,
              float packetLoss,
              float bitErrorRate,
              float duration);

    std::string toJsonString() const;

private:
    int m_timeslot;
    int m_id;
    std::string m_callsign;
    int m_target;
    float m_duration;
    float m_packetLoss;
    float m_bitErrorRate;
};

#endif
