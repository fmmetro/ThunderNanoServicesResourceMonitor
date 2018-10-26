#ifndef RTSPPARSER_H
#define RTSPPARSER_H

#include <plugins/Logging.h>

#include <string>
#include <map>

#include "RtspSessionInfo.h"

typedef std::map<std::string, std::string> NAMED_ARRAY;

class RtspParser
{
    public:
        enum MessageType {
            RTSP_UNKNOWN,
            RTSP_RESPONSE,
            RTSP_ANNOUNCE
        };

        RtspParser();
        std::string buildSetupRequest(const std::string &server, const std::string &assetId);
        std::string buildPlayRequest(float scale = 1.0, int pos = 0);
        std::string buildGetParamRequest(bool bSRM);
        std::string buildTeardownRequest(int reason);
        std::string buildResponse(int seq, bool bSRM);

        int processSetupResponse(const std::string &response);
        int processPlayResponse(const std::string &response);
        int processGetParamResponse(const std::string &response);
        int processTeardownResponse(const std::string &response);
        int processAnnouncement(const std::string &response, bool bSRM);

    private:
        void updateNPT(NAMED_ARRAY &playMap);

        void parse(const std::string &str,  NAMED_ARRAY &contents, const string &sep1, const string &sep2);
        int parseResponse(const std::string str,  std::string &rtspBody, RtspParser::MessageType &msgType);
        int split(const string& str, const string& delim,  std::vector<string>& tokens);
        void hexDump(const char* label, const std::string& msg);

    public:
        RtspSessionInfo sessionInfo;

    private:
        static unsigned int seq;
};


#endif