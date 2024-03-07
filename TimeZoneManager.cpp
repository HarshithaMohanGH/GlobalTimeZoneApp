#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <map>
#include <sstream>
#include <time.h>

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

	string convertTime(string& sourceTimeZone, string& targetTimeZone, string& time) {
		int sourceOffset = timeZoneOffsets[sourceTimeZone];
		int targetOffset = timeZoneOffsets[targetTimeZone];

		int year, month, day, hour, minute, second;
		char colon;
		istringstream ss(time);
		ss >> year >> colon >> month >> colon >> day >> hour >> colon >> minute >> colon >> second;

		tm tm = {};
		tm.tm_year = year - 1900; // Years since 1900
		tm.tm_mon = month - 1;     // Month index is 0-based
		tm.tm_mday = day;
		tm.tm_hour = hour;
		tm.tm_min = minute;
		tm.tm_sec = second;

		time_t rawTime = mktime(&tm);
		rawTime += (targetOffset - sourceOffset) * 3600;
		tm = *localtime(&rawTime);

		char buffer[80];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
		return buffer;
	}

};