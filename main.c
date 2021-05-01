#include <stdio.h>
#include <stdlib.h>

const char FILE_NOT_SPECIFIED[] = "File not specified.\n";
const char FILE_NOT_AVAILABLE[] = "File not available.\n";
const char HELP[] = 
"uint8 v1.0\n"
"\n"
"USAGE : uint8 [FILENAME] <OPTIONS>\n"
"\n"
"OPTIONS :\n"
"        -v             - Show version.\n"
"        -h             - Show such a helpful text :)\n"
"        -c             - Make the output colorful.\n"
"        -o [FILENAME]  - Print the output into his file.\n";
const char VERSION[] = "uint8 v1.0\n";

#ifdef _WIN32
    #include <Windows.h>
    static HANDLE h;
    static DWORD r;
    int colored = 0;
    void setup(int argc, char **argv, FILE **src) {
        for(int i=1; i<argc; i++) {
            if(strcmp(argv[i], "-v") == 0) {
                fprintf(stdout, VERSION);
                exit(0);
            } else if(strcmp(argv[i], "-h") == 0) {
                fprintf(stdout, HELP);
                exit(0);
            } else if(strcmp(argv[i], "-c") == 0) {
                colored = 1;
                h = GetStdHandle(STD_OUTPUT_HANDLE);
                CONSOLE_SCREEN_BUFFER_INFO info;
                GetConsoleScreenBufferInfo(h, &info);
                r = info.wAttributes;
            } else if(strcmp(argv[i], "-o") == 0) {
                if(i+1 >= argc) {
                    fprintf(stderr, FILE_NOT_SPECIFIED);
                    exit(0);
                }
                FILE *out = freopen(argv[++i], "w", stdout);
                if(out == NULL) {
                    fprintf(stderr, FILE_NOT_AVAILABLE);
                    exit(0);
                }
            } else {
                *src = fopen(argv[i], "r");
                if(*src == NULL) {
                    fprintf(stderr, FILE_NOT_AVAILABLE);
                    exit(0);
                }
            }
        }
        if(*src == NULL) {
            fprintf(stderr, FILE_NOT_SPECIFIED);
            exit(0);
        }
    }
    #define RED   SetConsoleTextAttribute(h, BACKGROUND_RED   \
                                           | FOREGROUND_RED    \
                                           | FOREGROUND_GREEN   \
                                           | FOREGROUND_BLUE     \
                                           | FOREGROUND_INTENSITY);
    #define GRN   SetConsoleTextAttribute(h, BACKGROUND_GREEN \
                                           | FOREGROUND_RED    \
                                           | FOREGROUND_GREEN   \
                                           | FOREGROUND_BLUE     \
                                           | FOREGROUND_INTENSITY);
    #define BLU   SetConsoleTextAttribute(h, BACKGROUND_BLUE  \
                                           | FOREGROUND_RED    \
                                           | FOREGROUND_GREEN   \
                                           | FOREGROUND_BLUE     \
                                           | FOREGROUND_INTENSITY);
    #define RST   SetConsoleTextAttribute(h, r);
    void print_on() {
        if(colored) GRN fprintf(stdout, "1");
    }
    void print_off() {
        if(colored) RED fprintf(stdout, "0");
    }
    void print_number(unsigned char number) {
        if(colored) BLU fprintf(stdout, "%03u", number);
    }
    void print_ascii(unsigned char number) {
        if(colored) BLU fprintf(stdout, "%c", number);
    }
    void print_next() {
        if(colored) RST fprintf(stdout, "\n");
    }
#else
    #include <unistd.h>
    int colored = 0;
    void setup(int argc, char **argv, FILE **src) {
        int c;
        FILE *out;
        while((c = getopt(argc, argv, "vhco:")) != -1) {
            switch(c) {
            case 'v':
                fprintf(stdout, VERSION);
                exit(0);
                break;
            case 'h':
                fprintf(stdout, HELP);
                exit(0);
                break;
            case 'c':
                colored = 1;
                break;
            case 'o':
                out = freopen(optarg, "w", stdout);
                if(out == NULL) {
                    fprintf(stderr, FILE_NOT_AVAILABLE);
                    exit(0);
                }
            case '?':
                if(optopt == 'o') {
                    fprintf(stderr, FILE_NOT_SPECIFIED);
                    exit(0);
                }
                break;
            }
        }
        argc -= optind;
        argv += optind;
        if(argc == 0) {
            fprintf(stderr, FILE_NOT_SPECIFIED);
            exit(0);
        }
        *src = fopen(argv[0], "r");
        if(*src == NULL) {
            fprintf(stderr, FILE_NOT_AVAILABLE);
            exit(0);
        }
    }
    #define RED   "\033[41m"
    #define GRN   "\033[42m"
    #define BLU   "\033[44m"
    #define RST   "\033[0m"
    void print_on() {
        if(colored)
            fprintf(stdout, GRN "1");
        else
            fprintf(stdout, "1");
    }
    void print_off() {
        if(colored)
            fprintf(stdout, RED "0");
        else
            fprintf(stdout, "0");
    }
    void print_number(unsigned char number) {
        if(colored)
            fprintf(stdout, BLU "%03u", number);
        else
            fprintf(stdout, "%03u", number);
    }
    void print_ascii(unsigned char number) {
        if(colored)
            fprintf(stdout, BLU "%c", number);
        else
            fprintf(stdout, "%c", number);
    }
    void print_next() {
        if(colored)
            fprintf(stdout, RST "\n");
        else
            fprintf(stdout, "\n");
    }
#endif

int main(int argc, char **argv) {
    FILE *src = NULL;
    setup(argc, argv, &src);
    fseek(src, 0L, SEEK_END);
    long _l = ftell(src);
    char *s = malloc(sizeof(char) * (_l+1));
    fseek(src, 0L, SEEK_SET);
    size_t l = fread(s, sizeof(char), _l, src);
    fclose(src);

    unsigned char v = 0, m = 1;
    size_t stk = 0;
    for(size_t i=0; i<l; ++i) {
        switch(s[i]) {
        case 'r':
			if(m != 1)
				m = m >> 1;
            break;
        case 'l':
			if(m != 128)
				m = m << 1;
            break;
        case 'i':
            v = v ^ m;
            break;
        case 'a':
            v = v & ~m;
            break;
        case 'o':
            v = v | m;
            break;
        case 'b':
            if(v >> __builtin_ctz(m) & 1)
                print_on();
            else
                print_off();
            break;
        case 's':
            for(int j=7; j>=0; --j) {
                if(v >> j & 1)
                    print_on();
                else
                    print_off();
            }
            break;
        case 'n':
            print_number(v);
            break;
        case 'c':
            print_ascii(v);
            break;
        case 'e':
            print_next();
            break;
        case 'w':
            if(!(v & m)) {
                for(int j=i; j<l; ++j) {
                    if(s[j]=='w')
                        ++stk;
                    if(s[j]=='q')
                        --stk;
                    if(stk == 0) {
                        i = j;
                        break;
                    }
                }
            }
            break;
        case 'q':
            for(int j=i; j>=0; --j) {
                if(s[j]=='q')
                    ++stk;
                if(s[j]=='w')
                    --stk;
                if(stk == 0) {
                    i = j-1;
                    break;
                }
            }
            break;
        }
    }
    print_next();

    free(s);
    return 0;
}