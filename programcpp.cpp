/*
Test 2 - parse the input file and write each character in tabular from
example:
for file content:

abcd
j jk
h

output should be:
+---+---+---+---+
| a | b | c | d |
+---+---+---+---+
| j |   | j | k |
+---+   +---+---+
| h |   
+---+   


*/
#include <stdio.h>

#include <iostream>
#include <fstream>
using namespace std; 
#define MAXLINE 1024

void createBorderLine(char * data, char * line);
void createDataLine(char * data, char * dataline);
char* mergeBorderLines(char * upper_line, char * lower_line);


int main(int argc, char *  argv[])
{
    if(argc<2)
    {
        cout<<"Please provide the input file as parameter!";
        return 0;
    }
    ifstream  from(argv[1]);
    if(!from)
    {
        cout<<"Problem with reading the file. Is the file provideed correct?";
        return 0;
    }


    char data[MAXLINE];
    char line[MAXLINE*5];
    char upper_line[MAXLINE*4+1];   //for each char in file we need 4 bytes for border display data.
    char lower_line[MAXLINE*4+1];

    line[0] ='\0';                  //init first char to zero, for strlen to work.
    upper_line[0] ='\0';
    lower_line[0] = '\0';   

    while(!from.eof())
    {
       from.getline(data, MAXLINE);
       int len = strlen(data);
       
       if(len<=0)
       {
           continue; //skip empty lines
       }

       createBorderLine(data,upper_line);
       char * merged = upper_line;
       if(strlen(lower_line)>0)
       {
          merged = mergeBorderLines(upper_line,lower_line); //merge previous lower border with current upper.
       }
       cout<<merged;
       cout<<endl;
       
       createDataLine(data,line); //create the line with file content
       cout<<line;
       cout<<endl;

       createBorderLine(data,lower_line);

    }
    cout<<lower_line; //write out the last lower border.
    cout<<endl;

	return 0;
}


/*createBorderLine - creates the border display for the given data
params:
    data - pointer to the chars where content data is stored
    line - pointer to the chars to store border data.
*/
void createBorderLine(char * data, char * line)
{
    int len = strlen(data);
    
    for(int i=0; i < len; i++)
    {
        line[i*4+0]='+';
        bool notempty = (data[i]!=' ');
        line[i*4+1] = notempty ? '-' : ' ';
        line[i*4+2] = notempty ? '-' : ' ';
        line[i*4+3] = notempty ? '-' : ' ';
        if(i==len-1)
        {
            line[i*4+4]=notempty ? '+' : ' ';
        }
    }
    line[len*4+1] = data[len];
    len = strlen(line);
    for(int i=0; i < len-1; i++)
    {
        if(line[i] == '+')
        {
            if(i<3)
            {
                if(line[i+1] == ' ')
                {
                    line[i] = ' ';
                }
            }
            else
            {
                if(line[i-1]==' ' && line[i+1] == ' ')
                {
                     line[i] = ' ';
                }
            }
        }
    }
}

/*mergeBorderLines - merges the upper border with lower producing the only one.
params:
    upper_line - pointer to the chars where upper border data is stored.
    lower_line - pointer to the chars where lower border data is stored.
*/
char* mergeBorderLines(char * upper_line, char * lower_line)
{
    int len_upper = strlen(upper_line);
    int len_lower = strlen(lower_line);
    
    if(len_upper>len_lower)
    {
        for(int i = 0; i<len_lower; i++)
        {
            if(lower_line[i] == '+' || lower_line[i] == '-')
            {
                upper_line[i] = lower_line[i];
            }
        }
        return upper_line;
    }
    else
    {
        for(int i = 0; i<len_upper; i++)
        {
            if(upper_line[i] == '+' || upper_line[i] == '-')
            {
                lower_line[i] = upper_line[i];
            }
        }
        return lower_line;
    }
}

/*createDataLine - creates the data line display for the given data
params:
    data - pointer to the chars where content data is stored
    line - pointer to the chars to store new formated data.
*/
void createDataLine(char * data, char * line)
{
    int len = strlen(data);
    for(int i=0; i < len; i++)
    {
        line[i*4+0]='|';
        bool notempty = (data[i]!=' ');
        line[i*4+1] =  ' ';
        line[i*4+2] = notempty ? data[i] : ' ';
        line[i*4+3] =  ' ';
        if(i==len-1)
        {
            line[i*4+4]= notempty ? '|' : ' ';
        }
    }
    line[len*4+1] = data[len];
    len = strlen(line);
    for(int i=0; i < len-2; i++)
    {
        if(line[i] == '|')
        {
            if(i<3)
            {
                if(line[i+2] == ' ')
                {
                    line[i] = ' ';
                }
            }
            else
            {
                if(line[i-2]==' ' && line[i+2] == ' ')
                {
                     line[i] = ' ';
                }
            }
        }
    }
}
