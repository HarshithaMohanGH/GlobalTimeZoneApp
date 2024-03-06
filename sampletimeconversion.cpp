#include <iostream>
#include <string>



// Time zone information structure
struct TimeZoneInfo {
    std::string name;
    int offset;  // Offset from UTC in hours
    bool has_dst; // Indicates whether daylight saving time is in effect
};

// Function to perform time conversion between two time zones
std::string convertTime(const std::string& sourceTime, const TimeZoneInfo& sourceTimeZone,
    const TimeZoneInfo& targetTimeZone) {
    // Extract hours, minutes, and seconds from the source time
    int sourceHours, sourceMinutes, sourceSeconds;
    sscanf(sourceTime.c_str(), "%d:%d:%d", &sourceHours, &sourceMinutes, &sourceSeconds);

    // Calculate the target time
    int targetHours = sourceHours + (targetTimeZone.offset - sourceTimeZone.offset);
    // Adjust for daylight saving time if applicable
    if (sourceTimeZone.has_dst && targetTimeZone.has_dst) {
        targetHours += 1; // Assuming one-hour DST adjustment
    }

    // Handle overflow/underflow of hours
    if (targetHours >= 24) {
        targetHours -= 24;
    }
    else if (targetHours < 0) {
        targetHours += 24;
    }

    // Construct the target time string
    char targetTime[9]; // Format: HH:MM:SS
    sprintf(targetTime, "%02d:%02d:%02d", targetHours, sourceMinutes, sourceSeconds);

    return std::string(targetTime);
}

int main() {
    // Example time zone information
    TimeZoneInfo sourceTimeZone = { "EST", -5, true }; // Example source time zone (EST with DST)
    TimeZoneInfo targetTimeZone = { "PST", -8, true }; // Example target time zone (PST with DST)

    // Example source time
    std::string sourceTime = "10:30:00"; // Example source time (HH:MM:SS)

    // Perform time conversion
    std::string convertedTime = convertTime(sourceTime, sourceTimeZone, targetTimeZone);

    // Output the converted time
    std::cout << "Source Time (" << sourceTimeZone.name << "): " << sourceTime << std::endl;
    std::cout << "Converted Time (" << targetTimeZone.name << "): " << convertedTime << std::endl;

    return 0;
}
