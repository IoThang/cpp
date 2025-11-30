#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#include <unistd.h>

using namespace std;

void basic_io(){
    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd == -1){
        perror("open failed");
        return;
    }

    const char* data = "Hello world!\n";
    ssize_t written_bytes = write(fd, data, strlen(data));
    if(written_bytes == -1){
        perror("write failed");
    }

    lseek(fd, 0 , SEEK_SET);

    char buf[100] = {0};
    ssize_t read_bytes = read(fd, buf, sizeof(buf) - 1);
    cout << "Read: " << buf << endl;
}

void metadata(){
    struct stat st;
    if(stat("test.txt", &st) == 0){
        cout << "Size: " << st.st_size << endl;
        cout << "Inode: " << st.st_ino << endl;
        cout << "Permissions: " << oct << (st.st_mode & 0777) << endl;
        cout << "UID: " << st.st_uid << " GID: " << st.st_gid <<endl;
        cout << "Is dir? " << S_ISDIR(st.st_mode) << endl;
        cout << "Is regular file? " << S_ISREG(st.st_mode) << endl;
        cout << "Is symlink? " << S_ISLNK(st.st_mode) << endl;
        cout << "Number of link: " << st.st_nlink << endl;
        cout << "Number of allocated block: " << st.st_blocks << endl;
    }

    symlink("test.txt", "link_test.txt");
    lstat("link_test.txt", &st);
    cout << "lstat on symlink size: " << st.st_size << endl;
    cout << "lstat on Number of link: " << st.st_nlink << endl;
}

void hard_and_soft_link(){
    struct stat st;

    link("test.txt", "hard_link.txt");
    symlink("test.txt", "soft_link.txt");

    if(stat("test.txt", &st) == 0){
        cout << "Number of link: " << st.st_nlink << endl;

        // unlink("soft_link.txt");
        cout << "Number of link: " << st.st_nlink << endl;
    }
}

int main(void){
    cout << "=== POSIX FILESYSTEM MASTER DEMO ===\n";

    basic_io();
    metadata();
    hard_and_soft_link();

    return EXIT_SUCCESS;
}