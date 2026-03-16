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

/*function/variable names alphabet*/
A [a-zA-Z1-9_]
/*alphabet for values inside <> for include statements*/
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

\/\/					{return TKUNMATCHED;} //single line comments
{A}+\(    				{return TKFUNCTION;} //function name found (ex: int func(int v), returns variable token for func)
int             		{return TKINT;}
double          		{return TKDOUBLE;}
string          		{return TKSTRING;}
char            		{return TKCHAR;}
bool            		{return TKBOOL;}
void 					{return TKVOID;}
void\)					{return TKVOID;} 
(else[ \t]if)       	{return TKIFELSE;} //returns ifelse token for else if
[ \n]if				    {return TKIFELSE;} //returns ifelse token for if (includes [ \n] as variable names can include if(like fifty))
else			    	{return TKIFELSE;} // returns if else token for else 
"for" 					{return TKLOOP;}
"while" 				{return TKLOOP;}
"#"include<{P}+> 		{return TKINCLUDES;} //returns includes token for #include <value>
{A}+[ \t]?= 			{return TKVARIABLE;} //ex: int var = returns variable token for var
{A}+;					{return TKVARIABLE;} //ex: int var; returns variable token for var
{A}+,					{return TKVARIABLE;} //ex: void function(int var, int var2); returns variable token for var
{A}+\)					{return TKVARIABLE;} //ex: void function(int var, int var2); returns variabl token for var2
.               		{return TKUNMATCHED;}

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
}