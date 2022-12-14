#include <dirent.h>
#include <iterator>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>
#include <vector>
#include "device.c"

int test_openDevices();
void test_readWriteDigital(int card);
void test_readAnalog(int card);
void test_PWM(int card);

// A wrapper that open devices on creation and closes them on destruction, 
// like when it goes out of scope.
struct DeviceCtx {
    DeviceCtx() : devices(OpenDevices()) {}
    ~DeviceCtx() { CloseDevices(); }

    operator int() const { return devices; }  // implicit conversion to `int`

    int devices;
};

void mychardev() { // 
    syslog(LOG_INFO, "Loop");

    DeviceCtx devices;                 // calls OpenDevices

    if (devices == 0) {
        syslog(LOG_ERR, "Driver error condition, exiting");
        return;                        // CloseDevices() will be called

    } else if (devices == -1) {
        syslog(LOG_ERR, "No devices found on system, exiting\n");
        return;                        // CloseDevices() will be called
    }

    int ver = VersionDLL();
    syslog(LOG_INFO, "DLL Version: %d.%d.%d.%d\n", (ver >> 24),
           (ver >> 16) & 0xFF, (ver >> 8) & 0xFF, ver & 0xFF);

}   // `devices` goes out of scope and calls CloseDevices()

// For security purposes, we don't allow any arguments to be passed into the daemon
int main(void)
{
   // Define variables
   pid_t pid, sid;

   // Fork the current process
   pid = fork();
   // The parent process continues with a process ID greater than 0
   if(pid > 0)
   {
      exit(EXIT_SUCCESS);
   }
   // A process ID lower than 0 indicates a failure in either process
   else if(pid < 0)
   {
      exit(EXIT_FAILURE);
   }
   // The parent process has now terminated, and the forked child process will continue
   // (the pid of the child process was 0)

   // Since the child process is a daemon, the umask needs to be set so files and logs can be written
   umask(0);

   // Open system logs for the child process
   openlog("Daemon-GPIO", LOG_NOWAIT | LOG_PID, LOG_USER);
   syslog(LOG_NOTICE, "Successfully started Daemon-GPIO");

   // Generate a session ID for the child process
   sid = setsid();
   // Ensure a valid SID for the child process
   if(sid < 0)
   {
      // Log failure and exit
      syslog(LOG_ERR, "Could not generate session ID for child process");

      // If a new session ID could not be generated, we must terminate the child process
      // or it will be orphaned
      exit(EXIT_FAILURE);
   }

   // Change the current working directory to a directory guaranteed to exist
   if((chdir("/")) < 0)
   {
      // Log failure and exit
      syslog(LOG_ERR, "Could not change working directory to /");

      // If our guaranteed directory does not exist, terminate the child process to ensure
      // the daemon has not been hijacked
      exit(EXIT_FAILURE);
   }

   // A daemon cannot use the terminal, so close standard file descriptors for security reasons
   close(STDIN_FILENO);
   close(STDOUT_FILENO);
   close(STDERR_FILENO);

   // Daemon-specific intialization should go here
   const int SLEEP_INTERVAL = 5;

   // Enter daemon loop
   while(1)
   {
      syslog(LOG_INFO, "Starting helper loop");
      // Execute daemon heartbeat, where your recurring activity occurs
      mychardev();

      // Sleep for a period of time
      sleep(SLEEP_INTERVAL);
   }

   // Close system logs for the child process
   syslog(LOG_NOTICE, "Stopping Daemon-GPIO");
   closelog();

   // Terminate the child process when the daemon completes
   exit(EXIT_SUCCESS);
}