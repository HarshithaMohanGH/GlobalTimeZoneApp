#include <iostream>
#include <string>
#include <ctime>
#include <map>
#include <sstream>
#include <time.h>


using namespace std;
class TimeZoneConverter {
private:
	map<string, int> timeZoneOffsets;
public:
	TimeZoneConverter() {
		timeZoneOffsets["UTC"] = 0;
		timeZoneOffsets["PST"] = -8;
		timeZoneOffsets["EST"] = -5;

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
class Globaltimezone {
private:
	TimeZoneConverter converter;

	map<int, string> favoriteTimeZones;
public:
	void displayMenu() {
		cout << "Welcome to the Global Time Zone Application \n\n"
			<< " 1. View current time in different time zones \n "
			<< " 2. Convert time between different time zones \n"
			<< " 3. Toggle daylight savings time on or off. \n"
			<< " 4. Manage fav time zones \n"
			<< " 5. Help and info \n"
			<< " 6. Exit .\n\n"
			<< "Enter your choice";
	}
	void executeChoice(int choice) {
		switch (choice) {
		case 1:
			viewCurrentTime(); break;
		case 2:
			convertTime(); break;
		case 3:
			toggleDayLight();
		case 4:
			manageFavoriteTimeZones();
			break;
		case 5:
			displayHelp();
			break;
		default:
			cout << "invalid choice\n";
		}
	}

	void viewCurrentTime() {
		string timezone;
		cout << "Enter the name of the timezone\n";
		cin >> timezone;
		cout << "Current time in " << timezone << ":" << converter.getCurrentTime(timezone) << "\n\n";
	}

	void convertTime() {
		string sourceTimeZone, targetTimeZone, time;
		cout << "Enter the source time\n";
		cin >> sourceTimeZone;
		cout << "Enter the target time zone\n";
		cin >> targetTimeZone;
		cout << "Enter the time (YYYY-MM-DD HH:MM:SS): ";
		cin.ignore();
		getline(cin, time);
		cout << "Converted time in " << targetTimeZone << ": " << converter.convertTime(sourceTimeZone, targetTimeZone, time) << "\n\n";



	}

	void toggleDayLight() {
		string choice;
		cout << "Enable or diable DST?(on/off) ";
		cin >> choice;
		cout << "DST " << choice << " for the time zone\n\n ";

	}

	void manageFavoriteTimeZones() {
		int choice;
		cout << "1. Add fav time zone. \n"
			<< "2. Remove fav time zone. \n"
			<< "3. View fav time zone \n"
			<< "4. to main menu. \n"
			<< "5. Enter choice \n";
		cin >> choice;
		cout << "\n";

		switch (choice) {
		case 1:
			addFavTimeZ(); break;
		case 2:
			removeFavTimeZone(); break;
		case 3:
			viewFavTimeZone(); break;
		case 4:
			break;

		}

	}

	void addFavTimeZ() {
		string timezone;
		cout << " Enter the name of the timezone\n";
		cin >> timezone;
		favoriteTimeZones.insert(pair<int, string>(favoriteTimeZones.size() + 1, timezone));
		cout << "Time zone added to favorites.\n\n";

	}

	void removeFavTimeZone() {
		int index;
		cout << "Enter the index of the time zone to be removed:\n";
		cin >> index;

		if (index > 0 && index <= favoriteTimeZones.size()) {
			auto it = favoriteTimeZones.begin();
			std::advance(it, index - 1); 

			cout << "Removed " << it->second << " successfully.\n";
			favoriteTimeZones.erase(it); // Remove the element
		}
		else {
			cout << "Invalid index.\n\n";
		}
	}


	void viewFavTimeZone() {
		cout << "Favourite timezones are: ";
		for (const auto& pair : favoriteTimeZones) {
			cout << pair.first << "." << pair.second << "\n";
		}
		cout << "\n";
	}
	void displayHelp() {
		cout << "Help & Information:\n"
			<< "- This application allows you to view current time in different time zones, convert time between time zones, toggle daylight savings time adjustments, and manage favorite time zones.\n"
			<< "- When converting time between time zones, please enter the time in the format: YYYY-MM-DD HH:MM:SS\n"
			<< "- You can add or remove time zones from your favorites for quick access.\n\n";
	}
};
int main() {
	Globaltimezone app;
	int choice;
	while (true) {
		app.displayMenu();
		cin >> choice;
		cout << "\n";
		app.executeChoice(choice);
	}

}