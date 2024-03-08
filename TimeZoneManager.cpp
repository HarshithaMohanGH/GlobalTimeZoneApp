#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <ctime>

using namespace std;

class TimeZoneConverter {
public:
    map<string, int> timeZoneOffsets;

public:
    TimeZoneConverter() {
        timeZoneOffsets["UTC"] = 0;
        timeZoneOffsets["PST"] = -8; // Pacific Standard Time
        timeZoneOffsets["EST"] = -5; // Eastern Standard Time
        timeZoneOffsets["CST"] = -6; // Central Standard Time
        timeZoneOffsets["HST"] = -10; // Hawaii-Aleutian Standard Time
        timeZoneOffsets["AKST"] = -9; // Alaska Standard Time
        timeZoneOffsets["AEST"] = 10; // Australian Eastern Standard Time
        timeZoneOffsets["JST"] = 9; // Japan Standard Time
        timeZoneOffsets["IST"] = 5.5; // Indian Standard Time
        timeZoneOffsets["BST"] = 1; // British Summer Time
        timeZoneOffsets["CET"] = 1; // Central European Time
    }

    int getTimeZoneOffset(const string& timeZone) {
        auto it = timeZoneOffsets.find(timeZone);
        if (it != timeZoneOffsets.end()) {
            return it->second;
        }
        else {
            return 0; // Return a default offset if timezone is not found
        }
    }

    string getCurrentTime(const string& timeZone) {
        time_t now = time(0);
        tm localtime;
        gmtime_s(&localtime, &now);
        localtime.tm_hour += timeZoneOffsets[timeZone];
        mktime(&localtime);

        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d  %H:%M:%S", &localtime);
        return buffer;
    }

    string convertTime(string& sourceTimeZone, string& targetTimeZone, string& sourceTime) {
        int sourceOffset = getTimeZoneOffset(sourceTimeZone);
        int targetOffset = getTimeZoneOffset(targetTimeZone);

        // Parse the source time
        int year, month, day, hour, minute, second;
        char dash, colon;
        istringstream ss(sourceTime);
        ss >> year >> dash >> month >> dash >> day >> hour >> colon >> minute >> colon >> second;

        // Calculate the time difference
        int timeDifference = targetOffset - sourceOffset;

        // Adjust the time
        hour += timeDifference;

        // Handle overflow/underflow of hours
        if (hour >= 24) {
            hour -= 24;
            day++;
        }
        else if (hour < 0) {
            hour += 24;
            day--;
        }

        // Format the output
        ostringstream oss;
        oss << year << "-" << month << "-" << day << " " << hour << ":" << minute << ":" << second;
        return oss.str();
    }
};
