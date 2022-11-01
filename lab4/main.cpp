#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
//0 1 1 2 2 5 6
void process1();
void process2();
void process3();
void process4();
void process5();
void process6();

int main() { //process 0
    printf("[Process 0]: process created. PID = %d, PPID = %d\n", getpid(), getppid());
    switch(fork()) {
        case -1:
            printf("[Process 0]: Error while fork();\n");
            break;
        case 0:
            process1();
            break;
        default:
            switch(fork()) {
                case -1:
                    printf("[Process 0]: Error while fork();\n");
                    break;
                case 0:
                    process2();
                    break;
            }
    }
    sleep(5);
    printf("[Process 0]: Exit. PID = %d, PPID = %d\n", getpid(), getppid());
    _exit(0);
    return 0;
}

void process1() {
    printf("[Process 1]: process created. PID = %d, PPID = %d\n", getpid(), getppid());
    switch(fork()) {
        case -1:
            printf("[Process 1]: Error while fork();\n");
            break;
        case 0:
            process3();
            break;
        default:
            switch(fork()) {
                case -1:
                    printf("[Process 1]: Error while fork();\n");
                    break;
                case 0:
                    process4();
                    break;
            }
            break;
    }
    sleep(4);
    printf("[Process 1]: Exit. PID = %d, PPID = %d\n", getpid(), getppid());
    execl("/bin/whoami", "whoami", NULL);
    _exit(0);
}

void process2() {
    printf("[Process 2]: process created. PID = %d, PPID = %d\n", getpid(), getppid());
    sleep(1);
    printf("[Process 2]: Exit. PID = %d, PPID = %d\n", getpid(), getppid());
    _exit(0);

}

void process3() {
    printf("[Process 3]: process created. PID = %d, PPID = %d\n", getpid(), getppid());
    sleep(1);
    printf("[Process 3]: Exit. PID = %d, PPID = %d\n", getpid(), getppid());
    _exit(0);

}

void process4() {
    printf("[Process 4]: process created. PID = %d, PPID = %d\n", getpid(), getppid());
    switch(fork()) {
        case -1:
            printf("[Process 4]: Error while fork();\n");
            break;
        case 0:
            process5();
            break;
    }
    sleep(3);
    printf("[Process 4]: Exit. PID = %d, PPID = %d\n", getpid(), getppid());
    _exit(0);
}

void process5() {
    printf("[Process 5]: process created. PID = %d, PPID = %d\n", getpid(), getppid());
    switch(fork()) {
        case -1:
            printf("[Process 5]: Error while fork();\n");
            break;
        case 0:
            process6();
            break;
    }
    sleep(2);
    printf("[Process 5]: Exit. PID = %d, PPID = %d\n", getpid(), getppid());
    _exit(0);
}

void process6() {
    printf("[Process 6]: process created. PID = %d, PPID = %d\n", getpid(), getppid());
    sleep(1);
    printf("[Process 6]: Exit. PID = %d, PPID = %d\n", getpid(), getppid());
    _exit(0);
}