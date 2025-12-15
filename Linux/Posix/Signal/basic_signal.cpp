#include <iostream>
#include <signal.h>
#include <sys/signalfd.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

volatile sig_atomic_t dump_stats = 0;
volatile sig_atomic_t running = 1;

void graceful_shutdown(int sig){
    cout << "\n[Received signal " << sig << " - " << strsignal(sig) << "] Graceful shutdown...\n";
    running = 0;
}

void sigusr1_handler(int sig){
    dump_stats = 1;
    cout << "[SIGUSR1] Request dump stats!\n";    
}

void sigchld_handler(int sig){
    int status;
    while(waitpid(-1, &status, 0) > 0){
        cout << "[SIGCHLD] Clear zombie sucessful\n";
    }
}

void print_all_signals() {
    cout << "Signals often use:\n";
    for (int sig = 1; sig < 32; ++sig) {
        cout << sig << ": " << strsignal(sig) << "\n";
        if (sig % 4 == 0) cout << endl;
    }
    cout << endl;
}

int main(){
    cout << "=== SIGNAL MASTER DEMO === PID: " << getpid() << endl;
    // print_all_signals();
    struct sigaction sa;

    //  Catch SIGINT, SIGTERM → graceful shutdown
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = graceful_shutdown;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, nullptr);
    sigaction(SIGTERM, &sa, nullptr);

    //  Catch SIGUSR1 to dump stats
    sa.sa_handler = sigusr1_handler;
    sigaction(SIGUSR1, &sa, nullptr);

    //  Catch SIGCHLD to clean zombie
    sa.sa_handler = sigchld_handler;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, nullptr);

    //  Ignored SIGPIPE (avoid crash when writing pipe is closing)
    signal(SIGPIPE, SIG_IGN);

    // Tạo 1 con để demo zombie/orphan
    if (fork() == 0) {
        sleep(3);
        exit(42);
    }

    alarm(5);
    sa.sa_handler = [](int signal) {cout << "[ALARM] 5s troi qua!\n";};
    sigaction(SIGALRM, &sa, nullptr);

    cout << "Program is running ... Try:\n";
    cout << "  kill -TERM " << getpid() << "   → graceful shutdown\n";
    cout << "  kill -USR1 " << getpid() << "   → dump stats\n";
    cout << "  Ctrl+C                          → SIGINT\n";
    cout << "  kill -9 " << getpid() << "      → không bắt được\n";

    int counter = 0;
    while (running) {
        sleep(1);
        counter++;
        if (dump_stats) {
            cout << "[STATS] Đã chạy " << counter << " giây\n";
            dump_stats = 0;
        }
    }

    return EXIT_SUCCESS;
}