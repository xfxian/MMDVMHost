#include "Event.h"

#include "Log.h"

#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

const string JSON_OBJECT_START = "{\n";
const string JSON_OBJECT_END = "}";
const string JSON_NAME_START = "  \"";
const string JSON_NAME_TO_VALUE = "\": ";
const string JSON_VALUE_END = "\n";
const string JSON_VALUE_END_MORE = ",\n";

#define jObject(...) JSON_OBJECT_START + __VA_ARGS__ + JSON_OBJECT_END
#define jMap(name, value) JSON_NAME_START + name + JSON_NAME_TO_VALUE + value + JSON_VALUE_END_MORE
#define jMapEnd(name, value) JSON_NAME_START + name + JSON_NAME_TO_VALUE + value + JSON_VALUE_END
#define jString(s) "\"" + s + "\""
#define jInt(i) std::to_string(i)
#define jStringOptional(opt) (opt == "" ? "null" : jString(opt))
#define jUIntOptional(opt) (opt < 0 ? "null" : jInt(opt))

CEvent::CEvent()
{
    m_timestamp = chrono::system_clock::now();
}

CEvent::~CEvent()
{
}

string CEvent::baseJsonMaps() const
{
    using namespace chrono;

    auto t = system_clock::to_time_t(m_timestamp);

    stringstream stream;
    stream << put_time(localtime(&t), "%FT%T%z");

    return jMap("source", jString(m_source)) +
           jMap("type", jString(m_type)) +
           jMap("timestamp", jString(stream.str()));
}

void CEvent::log(unsigned int level) const
{
    Log(level, this->toJsonString().c_str());
}

CSystemEvent::CSystemEvent(string type, string version, string gitVersion, int exitCode) : CEvent()
{
    m_source = "system";
    m_type = type;
    m_version = version;
    m_gitVersion = gitVersion;
    m_exitCode = exitCode;
}

string CSystemEvent::toJsonString() const
{
    return jObject(
        this->baseJsonMaps() +
        jMap("version", jStringOptional(m_version)) +
        jMap("git_version", jStringOptional(m_gitVersion)) +
        jMapEnd("exit_code", jUIntOptional(m_exitCode)));
}

CDmrEvent::CDmrEvent(string type, int timeslot, int id, string callsign, int target, float packetLoss, float bitErrorRate, float duration)
{
    m_source = "dmr";
    m_type = type;
    m_timeslot = timeslot;
    m_id = id;
    m_callsign = callsign;
    m_target = target;
    m_packetLoss = packetLoss;
    m_bitErrorRate = bitErrorRate;
    m_duration = duration;
}

string CDmrEvent::toJsonString() const
{
    return jObject(
        this->baseJsonMaps() +
        jMap("timeslot", jInt(m_timeslot)) +
        jMap("id", jInt(m_id)) +
        jMap("callsign", jString(m_callsign)) +
        jMapEnd("target", jInt(m_target)));
}
