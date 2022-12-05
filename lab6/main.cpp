#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>
#include <signal.h>

// 28. Очереди сообщений. Родитель передает потомку три символа, потомок возвращает сумму их ASCII кода
mqd_t mqID;
bool wait = 1;

void signalHandler (int signum) {
    wait = 0;
    struct mq_attr mqAttr;
    mq_getattr(mqID, &mqAttr);
    char buf[mqAttr.mq_msgsize];
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        if (mq_receive(mqID, buf, mqAttr.mq_msgsize, NULL) < 0) {
            printf("[%d] Receive failed.\n", getpid());
            return;
        }
        printf("[%d] Received: %s\n", getpid(), buf);
        sum += buf[0];
    }
    char str[256];
    int strSize = sprintf(str, "%d", sum);
    if (mq_send(mqID, str, strSize, 0) < 0) {
        printf("[%d] Send failed.\n", getpid());
        return ;
    }
    printf("[%d] Sent: %s\n", getpid(), str);
    _exit(0);
}


int main() {
    mqID = mq_open("/queue", O_RDWR | O_CREAT | O_EXCL, 0666, NULL);
    if (mqID < 0) {
        if (errno == EEXIST) {
            mq_unlink("/queue");
            mqID = mq_open("/queue", O_RDWR | O_CREAT, 0666, NULL);
        } else {
            printf("Error.\n");
            return -1;
        }
    }

    pid_t child_pid = fork();
    if (child_pid == 0) {
        (void) signal(SIGUSR1, signalHandler);
        while(wait);
	_exit(0);
    }

    printf("[%d] Input: ", getpid());
    char str[256];
    scanf("%s", str);

    for (int i = 0; i < 3; i++) {
        if (mq_send(mqID, str+i, sizeof(char), 0) < 0) {
            printf("[%d] Send failed.\n", getpid());
            return -1;
        }
        printf("[%d] Sent: %c\n", getpid(), str[i]);
    }
    kill(child_pid, SIGUSR1);
    sleep(5);
    struct mq_attr mqAttr;
    mq_getattr(mqID, &mqAttr);
    char buf[mqAttr.mq_msgsize];
    if (mq_receive(mqID, buf, mqAttr.mq_msgsize, NULL) < 0) {
        printf("[%d] Receive failed.\n", getpid());
        return -1;
    }
    printf("[%d] Received: %s\n", getpid(), buf);
    printf("[%d] Result: %s\n", getpid(), buf);
}
