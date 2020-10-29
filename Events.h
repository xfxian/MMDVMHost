#ifndef EVENTS_H
#define EVENTS_H

#include "Event.h"

#include <string>

class CEvents
{
public:
    CEvents(unsigned int publishToFile, std::string filePath, std::string fileRoot,
            unsigned int publishToRemote, std::string remoteAddress, unsigned int remotePort, unsigned int localPort);
    ~CEvents();

    void publish(CEvent *event);

private:
    unsigned int m_publishToFile;
    std::string m_filePath;
    std::string m_fileRoot;
    unsigned int m_publishToRemote;
    std::string m_remoteAddress;
    unsigned int m_remotePort;
    unsigned int m_localPort;
    FILE *m_fp = NULL;
};

#endif
