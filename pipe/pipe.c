#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

// Compile with gcc and run
int main(int argc, char *argv[])
{
    int file_descriptor[2];
    // [0] - read end
    // [1] - write end

    // opens pipe
    if (pipe(file_descriptor) == -1)
    {
        printf("An error has occured with opening the pipe");
        return 1;
    }

    // fork over
    int id = fork();
    if (id == 0)
    {
        // since this process is not reading at all
        close(file_descriptor[0]);

        int x;
        printf("Input a number:\n");
        scanf("%d", &x);
        // write to the write end
        // catch error for writing
        if (write(file_descriptor[1], &x, sizeof(int)) == -1)
        {
            printf("An error has occured with writing");
            return 2;
        }

        // close both write and read end
        close(file_descriptor[1]);
    }
    else
    {
        int y;
        // this process does not use write port
        close(file_descriptor[1]);

        // catch error for reading
        if (read(file_descriptor[0], &y, sizeof(int)) == -1)
        {
            printf("An error has occured with reading");
            return 3;
        }

        // close the read process
        close(file_descriptor[0]);
        printf("Got from child process %d\n", y);
    }

    return 0;
}