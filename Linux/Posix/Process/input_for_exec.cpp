#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[]){
    cout <<"A new process is called by exec()" << endl;
    cout << "New process pid is " << getpid();
    for(int i = 0; i < argc; i++){
        cout << "argv[" << i << "]: " << argv[i] << endl;
    }
    sleep(10);
    return EXIT_SUCCESS;
}