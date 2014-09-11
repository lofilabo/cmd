#include "cmd.h"

void main(int argc, char *argv[])
{
  char command = 'x';
  int valid_com, n1 = 0, n2 = 0;

  *FileToOpen = *++argv;

  getch();	
  /*init_text();*/
  /*read_file();*/

  if( next != 0){
    n2 = next -1;
    printf (0, n2);
    }

int printedOnce = 0;
	
    while (command != 'q'){
      if(printedOnce==0){
	      printf(":--< ");
	      printedOnce=0;
      }
      command = read_command(&n1, &n2, &valid_com);

      process_option(command, &n1, &n2);
    }
}


char read_command(int *pn1, int *pn2, int *valid)
{
  extern int next;
  char c1;

  c1 = getnextchar();
  *valid = TRUE;

  switch(c1)
  {
	case '%':
	    *pn1 = 0;
	    *pn2 = next - 1;
	    c1 = getnextchar();
	    break;

	default :
		*pn1 = *pn2;
		break;
	}
	
	fflush(stdin);

if( next == 0 )	*pn1 = *pn2 = 0;
if( *pn1 <  0 )	*pn1 = 0;	
if( *pn2 <  0 )	*pn2 = 0;
if( *pn1 >next) *pn1 = next - 1;
if( *pn2 >next) *pn2 = next - 1;
if( *pn1 >*pn2) *pn1 = *pn2;

return(c1);

}


char getnextchar(){

  char c;

  while((c = getchar()) == SP);
  return (c);
}


int isadigit(char c)
{
  if (c >= '0' && c<= '9' )
    return(TRUE);
  else
  return(FALSE);
}

int get_int(char c){
  int i = 0;

  while(isadigit(c)){
    i=10*i + (c - '0');
    c = getchar();
    }	
	
  ungetc(c, stdin);
  return (i);
}


int check_command(char cm, int *n1, int *n2){
  int valid = FALSE;

    	if( cm == 'p' || cm == 'q' ){
	  valid = TRUE;
	}
	return(valid);
}


void process_option(char com, int *pn1, int *pn2){
  extern char text [MAXLINES][MAXCOLS];
  extern int  next;

  switch (com){

	case 'q' :
	break;
  }
}

void read_file(void){
	extern char text [MAXLINES][MAXCOLS];
	extern int next;

	FILE *fp;
	char c;
	int col = 0;

		next = 0;

/*	if((fp = fopen("data.txt","r")) == NULL)	*/
	if((fp = fopen(*FileToOpen,"r")) == NULL){
		puts("^AF: ");
		return;
	}else{
		while((c = getc(fp)) != EOF){
			if ( c == NL || col >= MAXCOLS - 1 ){
				text[next++][col] = NL;
				col = 0;

					if( next > MAXLINES ){
						next = MAXLINES;
						puts ("^LE");
						fclose(fp);
						return;
					}

			}else{
				text[next][col++] = c;
			}
		}
	
		if ( col != 0 && c == EOF){
			text[next][col] = NL;
			next++;
		}

	}
	fclose(fp);
}

void init_text(void){
	extern char text [MAXLINES][MAXCOLS];

	int line, col;

	for ( line = 0; line <= MAXLINES; line++ ){
		for (col = 0; col <= MAXCOLS; col++){
			text[line][col] = NULL;
		}
	}
}


int save_text(void){
	extern char text [MAXLINES][MAXCOLS];
	extern int next;

	int line, col;
	FILE *fp;

	if((fp = fopen(*FileToOpen,"w")) == NULL){
		fp = fopen(*FileToOpen,"a");
	}

	for ( line = 0; line < next; line++){
	
		for (col = 0; col < MAXCOLS; col++){
			putc( text[line][col], fp );
			if ( text [line][col] == NL ){
				col = MAXCOLS;
			}
		}
	}

	fclose(fp);
	return(TRUE);
}
