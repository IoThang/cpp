#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

using namespace std;

void create_zombie_process(void){
    pid_t pid = fork();
    if(pid == 0){
        cout << "[Zombie Child]: PID: " << getpid() << " PPID: " << getppid() << endl;
        cout << "Kill here" << endl;
        //  Die but parent hasn't waited => Zombie
        exit(42);
        sleep(5);
    }
    else if(pid > 0){
        cout << "[Zombie Parent]: PID: " << getpid() << " PPID: " << getppid() << endl;
        cout << "[Zombie Parent]: PID " << getpid() 
             << " create zombie child PID " << pid << " - Parent sleeps within 15s and don't wait()\n";
        sleep(5);
        cout << "[Zombie Parent] Parent wakes up, wait() to clean zombie...\n";
        int status;
        waitpid(pid, &status, 0);
        if(WIFEXITED(status)){
            cout << "[Zombie Parent] Clean successful, child exit code = " << WEXITSTATUS(status) << endl;
        }
        sleep(5);     
    }
}

void create_orphan_process() {
    pid_t pid = fork();
    if (pid == 0) {
        // Con
        cout << "[Orphan Child] Child PID " << getpid() << " sleeping 20s...\n";
        sleep(20);
        cout << "[Orphan Child] Child wakes up! Parent died, PPID now is: " 
             << getppid() << endl;
        exit(0);
    } else if (pid > 0) {
        cout << "[Orphan Child] Parent PID " << getpid() 
             << " create Child PID " << pid << " and die!\n";
        sleep(2);
        exit(0);  // cha chết trước → con thành orphan
    }
}

int main(){
    cout << "[Main Parent]: PID: " << getpid() << " PPID: " << getppid() << endl;
    sleep(5);
    if(fork() == 0){
        create_zombie_process();
        _exit(0);
    }

    if(fork() == 0){
        create_orphan_process();
        _exit(0);
    }

    // if()
    
    return EXIT_SUCCESS;
}