#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    pid_t processid;
    processid = fork();
    if(processid<0){
        perror("Fork failed");
        return 1;
    }
    else if(processid==0){
        printf("Child process: PID = %d, Parent PID: %d \n",getpid(),getppid());
    }
    else{
        printf("Parent process: PID = %d, Child PID: %d \n",getpid(),processid);
    }
    return 0;
}
