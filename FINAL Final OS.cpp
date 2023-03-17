#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <string>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>

using namespace std;

//TAIL WORK

int checkIfNumber(char argv[20][200], int j) {
    for (long long unsigned int k=0; k<strlen(argv[j]); k++)
        if (!isdigit(argv[j][k])) {
            cout << "Invalid number. Aborting process..." << endl;
            return 0;
        }
    return 1;
}

int numberOfLines(char filename[]) {
    int lines = 0;
    ifstream file(filename);

    if (file.good()) {
        while(!file.eof()) {
            char line[200];
            file.getline(line, 200);
            lines++;
        }
    }

    return lines;
}

int numberOfChars(char filename[]) {
    int chars = 0;
    ifstream file(filename);

    if (file.good()) {
        while(!file.eof()) {
            char line[200];
            file.getline(line, 200);
            chars += strlen(line);
        }
    }

    return chars;
}

void tailFile(char filename[], int &n, int &i) {
    if (n>numberOfLines(filename)) n=numberOfLines(filename);

    char lines[n][200];
    ifstream file(filename);

    if (file.good()) {
        while(!file.eof()) {
            char line[200];
            file.getline(line, 200);

            if (i<n) strcpy(lines[i], line);
            else {
                for (int j=0; j<n-1; j++)
                    strcpy(lines[j], lines[j+1]);
                strcpy(lines[n-1], line);
            }
            i++;
        }

        for (int j=0; j<n; j++)
            cout << lines[j] << endl;
    } else cout << "Specified file " << filename << " does not exist. Aborting process..." << endl;
}

void tailChars(char filename[], int &howmany) {
    if (numberOfChars(filename)<howmany) howmany = numberOfChars(filename);
    char line[200], ch, l, i=0;
    strcpy(line, "");

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        cout << "Specified file " << filename << " does not exist. Aborting process..." << endl;
        return;
    }

    fseek(file, 0, SEEK_END);
    l = ftell(file);
    fseek(file, (l - howmany), SEEK_SET);

    do {
        ch = fgetc(file);
        line[i] = ch;
        i++;
    } while (i < howmany);

    line[howmany] = '\0';

    cout << line << endl;
}

/**
-c, -n, -q, -v

-c: Number of characters instead of lines to be printed. - OK

-n: Number of lines to be printed, default: 10 - OK

-q: For when more than 1 file is given - OK

-v: Print the file name - OK
*/

void tail(int argc, char argv[20][200])
{
    if (argc==0) {
        cout << "No arguments specified." << endl;
        return;
    }
    int n = 10, i=0, options[3] = {0, 0, 0}, howmany = 0;
    /**
    options[0] - Characters instead of Lines
    options[1] - >1 Files
    options[2] - Print the file name
    */
    char filename[50];
    strcpy(filename, argv[0]);

    if (n>numberOfLines(filename)) n=numberOfLines(filename);

    for (int a=0; a<argc; a++) {
        int b = a;
        if (strcmp(argv[b], "-n")==0) {
            b++;
            if (checkIfNumber(argv, b)==0) return;

            n = atoi(argv[b]);

            b++;
            if (b<argc)
                if (strcmp(argv[b], "-n")!=0 && strcmp(argv[b], "-c")!=0 && strcmp(argv[b], "-q")!=0 && strcmp(argv[b], "-v")!=0) {
                    strcpy(filename, argv[b]);
                    if (numberOfLines(filename)<n) n = numberOfLines(filename);
                }

        }
        else if (strcmp(argv[b], "-v")==0) {
            options[2] = 1;

            b++;
            if (b<argc)
                if (strcmp(argv[b], "-n")!=0 && strcmp(argv[b], "-c")!=0 && strcmp(argv[b], "-q")!=0 && strcmp(argv[b], "-v")!=0)
                    strcpy(filename, argv[b]);
        }
        else if (strcmp(argv[b], "-q")==0) {
            options[1] = 1;
        }
        else if (strcmp(argv[b], "-c")==0) {
            options[0] = 1;

            b++;
            if (checkIfNumber(argv, b)==0) return;

            howmany = atoi(argv[b]);

            b++;
            if (b<argc)
                if (strcmp(argv[b], "-n")!=0 && strcmp(argv[b], "-c")!=0 && strcmp(argv[b], "-q")!=0 && strcmp(argv[b], "-v")!=0) {
                    strcpy(filename, argv[b]);
                    if (numberOfChars(filename)<howmany) howmany = numberOfChars(filename);
                }
        }
    }

    if (options[2] == 1 && options[1] == 0) cout << "~~~~> " << filename << " <~~~~" << endl << endl;

    if (options[0]==0) {
        if (options[1] == 1) {
            for (int a=0; a<argc; a++) {
                int b=a;
                if (strcmp(argv[b], "-q")==0) {
                    b++;
                    while(b<argc && (strcmp(argv[b], "-n")!=0 && strcmp(argv[b], "-c")!=0 && strcmp(argv[b], "-q")!=0 && strcmp(argv[b], "-v")!=0)) {
                        int x = n;

                        strcpy(filename, argv[b]);

                        if (numberOfLines(filename)<x) x = numberOfLines(filename);

                        cout << "____| " << filename << endl;
                        tailFile(filename, x, i);
                        cout << endl;

                        b++;
                    }
                }
            }
        } else  tailFile(filename, n, i);
    } else if (options[0] == 1) {
        if (options[1] == 1) {
            for (int a=0; a<argc; a++) {
                int b=a;
                if (strcmp(argv[b], "-q")==0) {
                    b++;
                    while(b<argc && (strcmp(argv[b], "-n")!=0 && strcmp(argv[b], "-c")!=0 && strcmp(argv[b], "-q")!=0 && strcmp(argv[b], "-v")!=0)) {
                        int x = howmany;

                        strcpy(filename, argv[b]);

                        if (numberOfChars(filename)<howmany) howmany = numberOfChars(filename);

                        cout << "____| " << filename << endl;
                        tailChars(filename, x);
                        cout << endl;

                        b++;
                    }
                }
            }
        } else tailChars(filename, howmany);
    }
}

//UNIQ WORK

int uniqLines(char filename[]) {
    ifstream file(filename);
    int lines = 0;
    while(!file.eof()) {
        char line[200];
        file.getline(line, 200);
        lines++;
    }
    return lines;
}

void uniqFile(char filename[], int option) {
    char line[200], line2[200];
    ifstream file(filename);

    if (file.good()) {
        file.getline(line, 200);
        cout << line << endl;
        while(!file.eof()) {
            file.getline(line2, 200);

            if (line[strlen(line)-1]=='\n') line[strlen(line)-1] = '\0';
            if (line2[strlen(line)-1]=='\n') line2[strlen(line)-1] = '\0';

            if (option == 1) {
                char templine[200], templine2[200];
                strcpy(templine, line);
                strcpy(templine2, line2);

                for (int i=0; i<strlen(templine); i++)
                    templine[i] = tolower(templine[i]);
                for (int i=0; i<strlen(templine2); i++)
                    templine2[i] = tolower(templine2[i]);

                if (strcmp(templine, templine2) != 0) {
                    strcpy(line, line2);
                    cout << line << endl;
                }
            } else {
                if (strcmp(line, line2) != 0) {
                    strcpy(line, line2);
                    cout << line << endl;
                }
            }
        }
    } else cout << "Specified file does not exist. Aborting process..." << endl;
}

void u_uniqFile(char filename[], int option) {
    char lines[200][200], i_lines[200][200];
    int ilines = 0;
    ifstream file(filename);

    if (file.good()) {
        while(!file.eof()) {
            file.getline(lines[ilines], 200);

            if (lines[ilines][strlen(lines[ilines])-1]=='\n') lines[ilines][strlen(lines[ilines])-1] = '\0';

            if (option == 1) {

                char templine[200];
                strcpy(templine, lines[ilines]);

                for (int i=0; i<strlen(templine); i++) {
                    templine[i] = tolower(templine[i]);
                }

                strcpy(i_lines[ilines], templine);
            }

            ilines++;
        }
        if (option == 1) {
            for(int i=0; i<ilines; i++) {
                int check = 1;
                for (int j=i+1; j<ilines; j++) {
                    if (strcmp(i_lines[i], i_lines[j])==0 || strcmp(i_lines[i], i_lines[i-1])==0) {
                        check=0;
                        j = ilines;
                    }
                }
                if (check==1) cout << lines[i] << endl;
            }
        } else {
            for(int i=0; i<ilines; i++) {
                int check = 1;
                for (int j=i+1; j<ilines; j++) {
                    if (strcmp(lines[i], lines[j])==0 || strcmp(lines[i], lines[i-1])==0) {
                        check=0;
                        j = ilines;
                    }
                }
                if (check==1) cout << lines[i] << endl;
            }
        }

    } else cout << "Specified file does not exist. Aborting process..." << endl;
}

void d_uniqFile(char filename[], int option) {
    char lines[200][200], i_lines[200][200], printed[200][200];
    int ilines = 0, iprinted=0;
    ifstream file(filename);

    if (file.good()) {
        while(!file.eof()) {
            file.getline(lines[ilines], 200);

            if (lines[ilines][strlen(lines[ilines])-1]=='\n') lines[ilines][strlen(lines[ilines])-1] = '\0';

            if (option == 1) {

                char templine[200];
                strcpy(templine, lines[ilines]);

                for (int i=0; i<strlen(templine); i++) {
                    templine[i] = tolower(templine[i]);
                }

                strcpy(i_lines[ilines], templine);
            }

            ilines++;
        }
        if (option == 1) {
            for(int i=0; i<ilines; i++) {
                int check = 1;
                for (int j=i+1; j<ilines; j++) {
                    if (strcmp(i_lines[i], i_lines[j])==0 || strcmp(i_lines[i], i_lines[i-1])==0) {
                        check=0;
                        j = ilines;
                    }
                }
                if (check==0) {
                    int checking = 1;
                    for (int j=0; j<iprinted; j++) {
                        if (strcmp(i_lines[i], printed[j])==0) {
                            checking = 0;
                            j = iprinted;
                        }
                    }

                    if (checking == 1) {
                        cout << lines[i] << endl;
                        strcpy(printed[iprinted], i_lines[i]);
                        iprinted++;
                    }
                }
            }
        } else {
            for(int i=0; i<ilines; i++) {
                int check = 1;
                for (int j=i+1; j<ilines; j++) {
                    if (strcmp(lines[i], lines[j])==0 || strcmp(lines[i], lines[i-1])==0) {
                        check=0;
                        j = ilines;
                    }
                }
                if (check==0) {
                    int checking = 1;
                    for (int j=0; j<iprinted; j++) {
                        if (strcmp(lines[i], printed[j])==0) {
                            checking = 0;
                            j = iprinted;
                        }
                    }

                    if (checking == 1) {
                        cout << lines[i] << endl;
                        strcpy(printed[iprinted], lines[i]);
                        iprinted++;
                    }
                }
            }
        }

    } else cout << "Specified file does not exist. Aborting process..." << endl;
}

/**
-i: ignore case, no more case sensitive - OK
-d: It prints all and only duplicate lines once - OK
-u: It allows you to print only unique lines - OK
*/

void uniq(int argc, char argv[20][200])
{
    int options[3] = {0, 0, 0};
    /**
    options[1] -i
    options[2] -d
    options[3] -u
    */
    if (argc==0) {
        cout << "No arguments specified." << endl;
        return;
    }

    char filename[50];
    strcpy(filename, argv[0]);

    for (int a=0; a<argc; a++) {
        int b=a;
        if (strcmp(argv[b], "-i")==0) {
            options[0] = 1;

        b++;
        if (b<argc)
            if (strcmp(argv[b], "-i")!=0 && strcmp(argv[b], "-d")!=0 && strcmp(argv[b], "-u")!=0) {
                strcpy(filename, argv[b]);
            }
        }
        else if (strcmp(argv[b], "-d")==0) {
            if (options[2]==0) options[1] = 1;
            else {
                cout << "Cannot have -d and -u simultaniously." << endl;
                return;
            }



            b++;
            if (b<argc)
                if (strcmp(argv[b], "-i")!=0 && strcmp(argv[b], "-d")!=0 && strcmp(argv[b], "-u")!=0) {
                    strcpy(filename, argv[b]);
                }
        }
        else if (strcmp(argv[b], "-u")==0) {
            if (options[1]==0) options[2] = 1;
            else {
                cout << "Cannot have -u and -d simultaniously." << endl;
                return;
            }



            b++;
            if (b<argc)
                if (strcmp(argv[b], "-i")!=0 && strcmp(argv[b], "-d")!=0 && strcmp(argv[b], "-u")!=0) {
                    strcpy(filename, argv[b]);
                }
        }
    }
    if (options[1]==1) {
        d_uniqFile(filename, options[0]);
    } else if (options[2]==1) {
        u_uniqFile(filename, options[0]);
    } else uniqFile(filename, options[0]);
}

//CD WORK

void cd(int argc, char argv[20][200])
{
    char path[200];
    strcpy(path, "");

    for (int i=0; i<argc; i++) {
        strcat(path, argv[i]);
        if (i<argc-1) strcat(path, " ");
    }

    if (strlen(path)==0) {
        cout << "No directory specified." << endl;
    } else {
        char directory[200];
        int newdir = chdir(path);
        if (newdir<0)
            cout << "Change of directory unsuccessful." << endl;
        else {
            cout << "Directory changed." << endl << "New Directory: " << getcwd(directory, 200) << endl;
        }
    }
}

//MAIN

int main()
{
    char *input, directory[200];
    char dir[10];
    do {
    	strcpy(dir, "$ [");
    	strcat(dir, getcwd(directory, 200));
    	strcat(dir, "] ~> ");
    	
        input = readline(dir);
        
        char options[20][200], wc[10], *token; //wc - wrong command
        int nargs = 0, ctc = 0; // ctc - command to call
        
        add_history(input);
        
        token = strtok(input, " ");
        while(token != NULL) {
            if (nargs == 0) {
                if(!strcmp(token, "tail"))
                    ctc = 1;
                else if(!strcmp(token, "uniq"))
                    ctc = 2;
                else if(!strcmp(token, "cd"))
                    ctc = 3;
                else if(!strcmp(token, "exit"))
                    ctc = 4;
                else
                    strcpy(wc, token);
            } else {
                strcpy(options[nargs-1], token);
            }

            nargs++;
            token = strtok(NULL, " ");
        }
        nargs--;
        switch(ctc)
        {
        case 0:
            system(input);
            break;
        case 1:
            tail(nargs, options);
            cout<<endl;
            break;
        case 2:
            uniq(nargs, options);
            cout<<endl;
            break;
        case 3:
            cd(nargs, options);
            cout<<endl;
            break;
        default:
            //exit
            printf("Exiting..\n");
            return 0;
            break;
        }
    }while (strcmp("exit", input) != 0);
    return 0;
}
