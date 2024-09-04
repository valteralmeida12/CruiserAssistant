#include "TimeUtils.h"

std::string get_current_time() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "Current time is %I:%M %p and the date is %B %d, %Y", ltm);
    return std::string(buffer);
}
 