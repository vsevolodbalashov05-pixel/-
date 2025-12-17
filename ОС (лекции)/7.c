#include <syslog.h>

int main() {
    openlog("MyApp", LOG_PID, LOG_USER);
    syslog(LOG_INFO, "Программа запущена");
    closelog();
    return 0;
}
