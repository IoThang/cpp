#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

using namespace std;

int main(int argc, char *argv[]){
    int status;
    pid_t pid;

    pid = fork();
    if(pid == -1){
        exit(0);
    }
    else if(pid == 0){
        cout << "Before exec() \n";
        execl("./input_for_exec", "arg1", "arg2", "NULL");
        cout << "This line will not be printed :)\n";
    }
    else{
        cout << "Parent executing before wait(), child process created by parent is = " << pid << "\n";
        waitpid(pid, &status, 0);
        cout << "Wait() done, parent id = " << getpid() << endl;
        cout << "child id = " << pid << endl;
        cout << "child status" << status << endl;
    }

    return EXIT_SUCCESS;
}