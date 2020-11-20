#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

#define EOL 1 // End of line석
#define ARG 2 // arg 남음.
#define AMPERSAND 3 // &

#define FOREGROUND 0
#define BACKGROUND 1

#define min(a,b) a<b ? a : b
 
typedef struct { //arg 배열중에 < , > , | 등이 어디있는지 알려준다.
    int a;  // 0 == no, else == < index
    int b;  // 0 == no, else == > index
    int pipe;  // 0==no, else == | index
}ReDirectionPipe;

static char input[512];
static char tokens[1024];
char  *ptr, *tok;
char   *cutArr[1024];

void cutArrayCtoZero(char **C){ //C부터 (char*)0까지 잘라서 cutArr에 저장.
    char **k1 = C;
    char **k2 = cutArr;
    
    while( *k1 != (char*)0 )
        *k2++ = *k1++;
    *k2 = (char*)0;
}

ReDirectionPipe *getRDP(char **arg, int narg){
    int ret = 0, i;
    ReDirectionPipe *rd = malloc(sizeof(ReDirectionPipe));
    rd->a = rd->b = rd->pipe = 0;
    // 리디렉션이나 파이프가 어디에 위치한지 구조체에 저장해준다. 
    // 각각 하나씩밖에 저장을 못하므로
    // 같은 리디렉션이나 파이프가 여러개가 오면 곤란하다.
    // 또한 파이프의 왼쪽은 <, 오른쪽은 > 만 올 수 있다.
    for( i=0 ; i<narg ; i++ ){
        if( !strcmp(arg[i],"<") ) rd->a = i;  
        else if( !strcmp(arg[i],">") ) rd->b = i;  
        else if( !strcmp(arg[i],"|") ) rd->pipe = i; 
    }
    return rd;
}

int get_token(char **outptr)
{ 
    int type;

    *outptr = tok;

    while ( (*ptr == ' ') || (*ptr == '\t') ) ptr++;
    
    *tok++ = *ptr;
    
    switch (*ptr++) {
        case '\0' : type = EOL; break;
        case '&': type = AMPERSAND; break;
        default : type = ARG;
            while ( (*ptr != ' ') && (*ptr != '&') &&
                (*ptr != '\t') && (*ptr != '\0') )
                *tok++ = *ptr++;
    }
    *tok++ = '\0';
    return(type);
}

int execute(char **comm, int how)
{
    int pid;

    if ( (pid = fork()) < 0 ) {
        fprintf(stderr, "minish : fork error\n");
        return(-1);
    }
    else if ( pid == 0 ) {
        execvp(*comm, comm);
        fprintf(stderr, "minish : command not found\n");
        exit(127);
    }
    if ( how == BACKGROUND ) { /* Background execution */
        printf("[%d]\n", pid);
        return 0;
    }  
    /* Foreground execution */
    while ( waitpid(pid, NULL, 0) < 0 )
        if ( errno != EINTR ) return -1;
    return 0;
}

int parse_and_execute(char *input)
{
    char   *arg[1024];
    int   type, how;
    int   quit = FALSE;
    int   narg = 0;
    int   finished = FALSE;
    ReDirectionPipe  *rD;
    
    ptr = input;
    tok = tokens;
    while ( !finished ) {
        switch (type = get_token(&arg[narg])) { 
        case ARG :
            narg++;
            break;
        case EOL :
        case AMPERSAND:
            rD = getRDP(arg,narg); // arg 분석
            if ( !strcmp(arg[0], "quit") ) quit = TRUE;
            else if ( !strcmp(arg[0], "exit") ) quit = TRUE;
            else if ( !strcmp(arg[0], "cd") ) {
                /* Do something */   
                if( chdir(arg[1])==0 ){
                    char buf[255];
                    printf("\tSuccess Change Directory : ",narg);
                    getcwd(buf,255);
                    printf("%s\n",buf);
                }
                else printf("\tfail change directory\n"); 
            }
            else if ( !strcmp(arg[0],"type") ) {
                if( narg>1 ){
                    int i, fd;
                    int readcount;
                    char buf[512];
                    fd = open(arg[1],O_RDONLY);
                    if( fd<0 ) printf("open fail\n");
                    else {
                        readcount = read(fd,buf,512);
                        while( readcount>0 ){
                            for( i=0;i<readcount;i++ ) putchar(buf[i]);
                            readcount = read(fd,buf,512);
                        }
                    }
                    close(fd);
                }
            }
            else if ( rD->a || rD->b || rD->pipe ) { //리디렉션이나 파이프 중 하나라도 있으면
                int pid1, fd, pid2, pid3;
                int rda = rD->a, rdb = rD->b, rdp = rD->pipe;
                pid1 = fork();
                if(pid1==0){ //pid1
                    if( rda ) { // stdin 바꿈
                        // 없으면 만들고 있으면 그냥 연다.
                        fd = open(arg[rda+1], O_RDWR | O_CREAT | S_IROTH, 0644);
                        if( fd<0 ){perror("error"); exit(-1);}
                        arg[rda] = arg[rda+1] = (char*)0;
                        dup2(fd,STDIN_FILENO);
                        close(fd);
                    }
                    if( rdb ){ // stdout 바꿈
                        // 있든 없든 새로 만든다.
                        fd = open(arg[rdb+1], O_RDWR | O_CREAT | O_TRUNC | S_IROTH, 0644);
                        if( fd<0 ){perror("error"); exit(-1);}
                        arg[rdb] = arg[rdb+1] = (char*)0;
                        dup2(fd,STDOUT_FILENO);
                        close(fd);
                    }
                    
                    how = (type == AMPERSAND) ? BACKGROUND : FOREGROUND;
                    if( rdp == 0 ) // 파이프가 없는 경우 
                        execute(arg, how);
                    else{  // 파이프가 있는 경우
                        int p[2];
                        int pid2, pid3;
                        arg[rdp] = (char*)0;
                        arg[narg] = (char*)0;
                        cutArrayCtoZero(&arg[rdp+1]);
                        pid2 = fork();
                        if( pid2==0 ){ //pid2
                            pipe(p);
                            pid3 = fork();
                            if( pid3==0 ){ //pid3
                                dup2(p[1],STDOUT_FILENO);
                                close(p[0]);close(p[1]);
                                execute(arg,how);
                                exit(0);
                            }
                            wait(); //wait pid3
                            dup2(p[0],STDIN_FILENO);
                            close(p[0]);close(p[1]);
                            execute(cutArr,how);
                            exit(0);
                        } 
                        wait(); //wait pid2
                    }
                    exit(0); //exit pid1
                }
                wait(); // wait pid1
                
            }
            else {
                how = (type == AMPERSAND) ? BACKGROUND : FOREGROUND;
                arg[narg] = NULL;
                if (narg != 0)
                    execute(arg, how);
            }
            narg = 0;
            free(rD); // rD해제
            if (type == EOL)
                finished = TRUE;
            break; 
        }
    }
    return quit;
}

int main()
{
        char *arg[1024];
    int quit;

    printf("msh #\t& ");
    while (gets(input)) {
        quit = parse_and_execute(input);
        if (quit) break;
        printf("msh #\t& ");
    }
    return 0;
}