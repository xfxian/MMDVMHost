#include "Events.h"

#include "Log.h"

#include <cstdio>

using namespace std;

CEvents::CEvents(unsigned int publishToFile, string filePath, string fileRoot,
                 unsigned int publishToRemote, string remoteAddress, unsigned int remotePort, unsigned int localPort)
{
    m_publishToFile = publishToFile;
    m_filePath = filePath;
    m_fileRoot = fileRoot;
    m_publishToRemote = publishToRemote;
    m_remoteAddress = remoteAddress;
    m_remotePort = remotePort;
    m_localPort = localPort;

    m_fp = ::fopen("MMDVM-events.jsonl", "a+t");
}

CEvents::~CEvents()
{

}

void CEvents::publish(CEvent *event)
{
    ::fprintf(m_fp, "%s\n", event->toJsonString().c_str());
    ::fflush(m_fp);

    delete event;
}
