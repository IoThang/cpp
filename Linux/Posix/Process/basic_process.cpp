#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(){
    pid_t pid;
    int status;

    std::cout << "[Parent] PID parent: " << getpid() << " , PPID: " << getppid() << std::endl;
    std::cout << "Forking ...\n";
    pid = fork();

    if(pid < 0){
        //  Fork failed
        perror("Fork failed");
        return EXIT_FAILURE;
    }
    else if(pid == 0){
        std::cout << "[Child] PID child: " << getpid() << " , PID parent: " << getppid() << std::endl;
        sleep(2);
        std::cout << "[Child] execvp(\"ls\", \"-l\")..." << std::endl;
        char* args[] = {(char*)"ls", (char*)"-l", (char*)"/tmp", nullptr};
        execvp("ls", args);

        // only running once exec failed
        perror("execvp failed");
        _exit(127);  // Using _exit() instead of exit() to avoid double flush buffer
    }
    else{
        std::cout << "[Parent] Fork successful, PID child = " << pid << std::endl;
        std::cout << "[Parent] Parent is waiting child's finishing by waitpid..." << std::endl;
        pid_t waited = waitpid(pid, &status, 0);

        if (waited == -1) {
            perror("waitpid error");
        } else {
            std::cout << "[Parent] Child (PID=" << waited << ") finshed." << std::endl;

            if (WIFEXITED(status)) {
                std::cout << "[Parent] Child exits normally: " 
                     << WEXITSTATUS(status) << std::endl;
            }
            if (WIFSIGNALED(status)) {
                std::cout << "[Parent] Child was killed by signal: " 
                     << WTERMSIG(status) << std::endl;
            }
        }
    }

    return EXIT_SUCCESS;
}