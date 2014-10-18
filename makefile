prog: pipe_client.o pipe_func.o
    gcc pipe_client.o pipe_func.o -o pipe_client

pipe_client.o: pipe_client.c
    gcc -Wall pipe_client.c -c

pipe_func.o: pipe_func.c
    gcc -Wall pipe_func.c -c

clean: *.o
    rm *.o
