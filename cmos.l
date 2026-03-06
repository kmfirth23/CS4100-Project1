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
#define TKVARIABLE 010
#define TKINCLUDES 011
#define TKVOID 012
#define TKIFELSE 013
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

/*function/variable names*/
A [a-zA-Z1-9_]
/*includes*/
P [a-zA-Z_.]

%%
[ \t\n\f]       {Addline(yytext[0]);
                /*Remove tabs/spaces/newlines */}

\/\*            {
                char c;
                while (1) 
                {
                  if ((c = yyinput()) == EOF ){
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

{A}+\(    			{return TKFUNCTION;}
int             	{return TKINT;}
double          	{return TKDOUBLE;}
string          	{return TKSTRING;}
char            	{return TKCHAR;}
bool            	{return TKBOOL;}
void 				{return TKVOID;}
void\)				{return TKVOID;}
(else[ \t]if)       {return TKIFELSE;}
[ \n]if				    {return TKIFELSE;}
else			    {return TKIFELSE;}
"for" 				{return TKLOOP;}
"while" 			{return TKLOOP;}
"#"include<{P}+> 	{return TKINCLUDES;}
{A}+[ \t]?= 			{return TKVARIABLE;}
{A}+;				{return TKVARIABLE;}
{A}+,				{return TKVARIABLE;}
{A}+\)				{return TKVARIABLE;}
.               	{return TKUNMATCHED;}

%%
int yywrap(){
    return true; 
}

int main() {
	int token = 0;
	token = yylex();
	while(token){

		switch (token) {
			case TKFUNCTION : cout << "001";
				break;
			case TKINT : cout << "002";
				break;
			case TKCHAR : cout << "003";
				break;
			case TKDOUBLE : cout << "004";
				break;
			case TKBOOL : cout << "005";
				break;
			case TKSTRING : cout << "006";
				break;
			case TKLOOP : cout << "007";
				break;
			case TKINCLUDES : cout << "011";
				break;
			case TKVOID : cout << "012";
				break;
			case TKIFELSE : cout << "013";
				break;
			case TKVARIABLE : cout << "010";
				break;
		}

		token = yylex();
        
	}
	cout << endl;
}