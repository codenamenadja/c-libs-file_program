``Rules
    1. makesure appropriate permissions on files ans dirs
    1. compile options: -Wall -Wextra -Werror and use gcc

### RESEARCHES

- ``cat``
    - ``struct rlimit``

        ```c
        #include <sys/time.h>
        #inlcude <sys/resource.h>

        struct rlimit {
            rlimt_t rlim_cur; // soft limit
            rlimt_t rlim_max; // hard limit (ceiling for rlim_cur)
        }; 
        ```
        - DESC
            - soft limit is value that kernel enforces for corresponding resource.
            - hard limit acts as a ceiling for the soft limit;
                - an unprivileged process may set only its soft limit  
                to value in ranage 0~hardlimit. and, irreversibly lower its hard limit.
            - priviledged process(with the ``CAP_SYS_RESOURCE`` capability) may  
            make arbitary changed to either limit value.

    - ``int getrlimit(int resource, struct rlimit *rlim);``
        - DESC
            - get resource limits repectively.
            - resouce has an associated soft and hard limit, as defined by ``rlimit`` structure.
        - Arguments
            - resource
                - ``RLIMIT_AS, RLIMIT_CORE, RLIMIT_CPU, RLIMIT_FSIZE, RLIMIT_MEMLOCK...``
        - RETURNS
            - success: these system calls return 0
            - error: -1, with errno set.
           
    - ``int setrlimit(int resource, const struct rlimit *rlim);``

### versions and members

- **v1**
    - ``display_file/Makefile``
        - DESC
            1. open file as O_RDONLY mode.
            2. while-start(if read returned success): read BUFSIZ : BLOCKSIZE, from file and move to callstackbuf.
            3. write ``buf`` to ``STDOUT_FILENO``.
            4. POPUP
        - RETURNS
            - EXIT FAILURE only no parameter input.
            - EXIT 0~ if parameter in.
                - file could be more than 1, so not recongnizes as an error for not opened for any reason.
                - main routine returns count of close(fd).
                    - close occurs when only it opened.(means file could be read if there is no data.)
- **v2**
    - ``cat/Makefile``

    - ``tail/Makefile``
        - DESC
            1. print last 10 lines of input file.(default)
                - reads all file and uses malloc to allocate over BUFSIZ,
                - counts \n characters from last allocateds, write() from that pointer till end.
                - free all of line_buf pointer array at the end.
            2. if option -cxx number adds to arguments regardless of order,  
                will print xx bytes from bottom of the file.
                - read all of files to read from bottom of the file.
                - options is bigger than BUFSIZ? option-=BUFSIZ and entry point backs to last BUFSIZ-read string.
                - free all of line_buf pointer array at the end.

