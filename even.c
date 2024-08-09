#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sighup(int signal) {
    printf("Ouch!\n");
    fflush(stdout);
}

void handle_sigint(int signal) {
    printf("Yeah!\n");
    fflush(stdout);
}

int main(int argk, char *argv[]) {
    if (argk != 2) {
        fprintf(stderr, "Usage: %s <even_num>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    signal(SIGHUP, handle_sighup);
    signal(SIGINT, handle_sigint);

    for (int i = 0; i < n; i++) {
        printf("%d\n", 2 * i);
        sleep(1);  // Sleep for 5 sec
    }

    return 0;
}
