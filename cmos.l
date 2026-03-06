/*Here is a lex program */

%{ //declarations

#include <iostream> 
using namespace std;

#define TKFUNCTION 001
#define TKINT 002
#define TKCHAR 003
#define TKDOUBLE 004
#define TKBOOL 005
#define TKSTRING 006
#define TKLOOP 007
#define TKUNMATCHED 225

extern "C" int yylex();
extern char *yytext;

int linecount =1; 
int indent;
int n;
char *return_string;

/*Count the number of lines. */
void Addline(char c)
{
	if(c=='\n')
	{
		linecount++;
	}
}
/*An accessor function that returns the line number*/
int line_num()
{
    return linecount;
}

%}

A [a-zA-Z_]
C [a-zA-Z_,]

%%
[ \t\n\f]       {Addline(yytext[0]);
                /*Remove tabs/spaces/newlines */}

\/\*            {
                char c;
                while (1) 
                {
                  if ((c = yyinput() == EOF) ){
						//unmatched comment
						cout << "Unterminated comment starting on line" << line_num() << endl;
						return (0);
					}
					Addline(c);
					if (c == '*') {
						char x = yyinput();
						if( x == '/') {
							break;
						}
						else
						{
							unput(x);
						}
					}
				}
				}

{A}+\({C}+\)    {return TKFUNCTION;}
int             {return TKINT;}
double          {return TKDOUBLE;}
string          {return TKSTRING;}
char            {return TKCHAR;}
bool            {return TKBOOL;}
"for" | "while" {return TKLOOP;}
.               {return TKUNMATCHED;}

%%
int yywrap(){
    return true; 
}

int main() {
	int token = 0;
	token = yylex();
	while(token){

		switch (token) {
			case TKFUNCTION : cout << "Function" << endl;
				break;
			case TKINT : cout << "Int" << endl;
				break;
			case TKDOUBLE : cout << "Double" << endl;
				break;
			case TKBOOL : cout << "Bool" << endl;
				break;
			case TKSTRING : cout << "String" << endl;
				break;
			case TKLOOP : cout << "Loop" << endl;
				break;
		}
        
		token = yylex();
        
	}
}