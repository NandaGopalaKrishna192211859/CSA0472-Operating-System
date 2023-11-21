#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long mtype;
    char mtext[100]; 
};

int main() {
    key_t key;
    int msgid;

    key = ftok(".", 'a');

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    pid_t childPid = fork();

    if (childPid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (childPid == 0) {

        struct message receivedMessage;

        msgrcv(msgid, &receivedMessage, sizeof(struct message), 1, 0);

        printf("Received message in child process: %s\n", receivedMessage.mtext);
    } else {

        struct message sendMessage;

        sendMessage.mtype = 1;

        printf("Enter a message to send: ");
        fgets(sendMessage.mtext, sizeof(sendMessage.mtext), stdin);

        msgsnd(msgid, &sendMessage, sizeof(struct message), 0);

        wait(NULL);
    }

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
