#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p_to[2], p_from[2];
    char ball_byte = 'X';
    char buf;

    pipe(p_to);
    pipe(p_from);
    if(fork() == 0) {
        read(p_to[0], &buf, 1);
        printf("%d: received ping\n", getpid());
        write(p_from[1], &buf, 1);
    } else {
        write(p_to[1], &ball_byte, 1);
        read(p_from[0], &buf, 1);
        printf("%d: received pong\n", getpid());
    }
    exit(0);
}