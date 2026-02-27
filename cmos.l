/*Here is a lex program */

%{
#define TKFUNCTION 001
#define TKINT 002
#define TKCHAR 003
#define TKDOUBLE 004
#define TKBOOL 005
#define TKSTRING 006
#define TKFOR 007
#define TKWHILE 008
#define TKDO 009
#define TKUNMATCHED 225

int linecount =1; 
int indent;
int n;
char *return_string;

/*Count the number of lines. */
void ACC(char c)
{
    if(c == '\n')
    {
        linecount++;
    }
}
/*An accessor function that returns the line number*/
int line_nmb()
{
    return linecount;
}

%}

A [a-zA-Z_]
C [a-zA-Z_,]

%%
[ \t\n\f]       {ACC(yytext[0]);
                /*Remove tabs/spaces/newlines */}

\/\*            {
                char c;
                while (1) 
                {
                    if((c = input()) == EOF)
                    {
                        /*If this is the case, 
                        there is an error, an unterminated comment. */
                        printf("Detected unterminated ");
                        printf("comment starting on line ");
                        printf("%d \n", line_cur);
                        return(0);
                    }
                    ACC(c);
                    if (c == '*') 
                    {
                        break; 
                    }
                    else 
                    { 
                        unput (c);
                    }
                
                }

                }

{A}+\({C}+\)    {return TKFUNCTION;}
int             {return TKINT;}
double          {return TKDOUBLE;}
string          {return TKSTRING;}
char            {return TKCHAR;}
bool            {return TKBOOL;}
for             {return TKFOR;}
while           {return TKWHILE;}
do              {return TKDO;}
.               {return TKUNMATCHED;}

%%
yywrap(){
    return 1; 
}

