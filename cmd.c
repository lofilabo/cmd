#include "cmd.h"



void main(int argc, char *argv[])
{
  char command = 'x';
  int valid_com, n1 = 0, n2 = 0;

  *FileToOpen = *++argv;

  getch();	
  init_text();
  read_file();

  if( next != 0)
    {
    n2 = next -1;
    print (0, n2);
    }
	
    while (command != 'q')
    {
      printf(":> ");
      command = read_command(&n1, &n2, &valid_com);

      if(!valid_com)
      {
      puts("Invalid Command");
      puts("a:append,d:delete,h:help,i:insert,p:display,q:quit,r:read,s:save");
      }
      else process_option(command, &n1, &n2);
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
  case '$':
    *pn1 = *pn2 = next - 1 ;
    c1 = getnextchar();
    break;
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    *pn1 = get_int(c1) - 1;
    c1 = getnextchar();
    if ( c1 == ',')
      {
      c1 = getnextchar();
	if (c1 == '$')
	  {
	  *pn2 = next -1;
	  c1 = getnextchar();
	  }
        else
	  if(isadigit(c1))
	    {
	    *pn2 = get_int(c1) - 1;
	    c1 = getnextchar();
	    }
	break;
          }
	else
	*pn2 = *pn1;
        break;

	case ',':
	  c1 = getnextchar();
	  if (c1 == '$')
	    {
	    *pn1 = *pn2 = next -1;
	    c1 = getnextchar();
	    }
	  else
	  if(isadigit(c1))
	    {
	    *pn1 = *pn2;
	    *pn2 = get_int(c1) - 1;
	    c1 = getnextchar();
	    }
	  else
	  *valid = FALSE;
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


char getnextchar()
{
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

int get_int(char c)
{
  int i = 0;

  while(isadigit(c))
    {
    i=10*i + (c - '0');
    c = getchar();
    }	
	
  ungetc(c, stdin);
  return (i);
}


int check_command(char cm, int *n1, int *n2)
{
  int valid = FALSE;

  if (cm == 'i' && n2 == n1)
    valid = TRUE;
  else
    if(cm =='a' || cm == 'd' || cm == 'h' || cm == 'p' || cm == 'q' || cm == 'r' || cm == 's')
  valid = TRUE;
  return(valid);
}


void process_option(char com, int *pn1, int *pn2)
{
  extern char text [MAXLINES][MAXCOLS];
  extern int  next;

  switch (com)
  {
  case 'a' :
      *pn2 = next;
      insert(*pn2);
      break;

  case 'd' :
      deleter(*pn1, pn2);
      break;
	
  case 'h' :
      helpscreen();
      break;

  case 'i' :
      insert(*pn1);
      break;

  case 'p' :
      if (next > -1)
      print(*pn1, *pn2);
      else
      puts("\n ^EE");
      break;

  case 'q' :
      break;
	
  case 'r' :
      *pn1 = *pn2 = next = 0;
      init_text();
      read_file();

      if( next != 0 )
      {
	*pn2 = next - 1;
	print (0, *pn2);
      }
      break;

  case 's' :
      if(!save_text())
        puts("\n ^SAVE ERROR");
      else
        puts("\n ~FILE SAVED");
      break;
  }
}


void deleter(int n1, int *pn2)
{
  int line , col, diff;
  extern int next;
  extern char text [MAXLINES][MAXCOLS];

  diff = *pn2 - n1 + 1;

  for(line = n1, col = 0; line < next; ++col)
    {
    text[line][col] = text[line + diff][col];
    if (text[line + diff][col] == NL)
      {
      col = -1;
      ++line;
      }
    }

  if ( next != 0 )
  next = next - diff;
  *pn2 = n1;
}


void helpscreen()
{/* TO DO */}

void print (int n1, int n2)
{
  int line, col;
  extern char text [MAXLINES][MAXCOLS];
  extern int next;

  if (next == 0)
    {
    puts("^EE");
    return;
    }
	
  line = n1;
  printf("%2d: " , line + 1);

  for (col = 0; line <= n2; col++)
  {
  putchar (text[line][col]);

  if(text[line][col]==NL)
    {
    line++;
    col = -1;
    if (line <= n2 ) printf("%2d: " , line + 1);
    }
  }
}

void insert(int ln)
{
#define STOP '|'

  extern char text [MAXLINES][MAXCOLS];
  extern int next;
  int col = 0, line;
  char ch;

  line = ln;

  if(next >= MAXLINES)
    {
    puts ("^EF");
    next = MAXLINES;
    return;
    }

  printf("%2d : ", line + 1);
  ch = getch();
  putchar(ch);

  if ( ch == STOP )
  return;
  col = 0;

  while ( ch != STOP )
  {
  if(next >= 0 && line < next)
  movetext(line);
  ++next;

  text[line][col++] = ch;
  text[line][MAXCOLS - 1] = NL;

  while(!( ch == CR || col == MAXCOLS - 1))
    {
    ch = getch();
    while (ch == BS )
      {
      putchar(ch);
      putchar(SP);
      putchar(BS);
      col--;
      text[line][col] = SP;

        while(( ch = getch()) == BS && col == 0);
      }
				
    if ( ch == CR)
    text[line][col++] = NL;
    else
    {
	putchar(ch);
	text[line][col++] = ch;
    }

  }
		
  col = 0;

  if( next >= MAXLINES)
    {
	next = MAXLINES;
	puts("^BF");
	ch = STOP;
    }
  else
   {
        line++;
	printf("\n%2d : ", line + 1);
	ch = getch();
	putchar(ch);
   }

  }

fflush(stdin);
}


void movetext(int ln)
{
	extern int next;
	extern char text [MAXLINES][MAXCOLS];
	int line, col;

	for( line = next, col = 0; line >= ln; col++)
	{
		text[line + 1][col] = text [line][col];

		if( text[line][col] == NL || col == MAXCOLS -1 )
		{
			col = -1;
			line--;
		}
	}

}


void read_file(void)

{
	extern char text [MAXLINES][MAXCOLS];
	extern int next;

	FILE *fp;
	char c;
	int col = 0;

		next = 0;

/*	if((fp = fopen("data.txt","r")) == NULL)	*/
	if((fp = fopen(*FileToOpen,"r")) == NULL)
	{
		puts("^AF: ");
		return;
	}
	else
	{
		while((c = getc(fp)) != EOF)
		{
			if ( c == NL || col >= MAXCOLS - 1 )
			{
				text[next++][col] = NL;
				col = 0;

					if( next > MAXLINES )
					{
						next = MAXLINES;
						puts ("^LE");
						fclose(fp);
						return;
					}

			}
			else
			{
				text[next][col++] = c;
			}
		}
	
		if ( col != 0 && c == EOF)
		{
			text[next][col] = NL;
			next++;
		}

	}
	fclose(fp);
}

void init_text(void)
{
	extern char text [MAXLINES][MAXCOLS];

	int line, col;

	for ( line = 0; line <= MAXLINES; line++ )
		for (col = 0; col <= MAXCOLS; col++)
			text[line][col] = NULL;
}


int save_text(void)
{
	extern char text [MAXLINES][MAXCOLS];
	extern int next;

	int line, col;
	FILE *fp;

/*	if((fp = fopen("data.txt","w")) == NULL)	*/
	if((fp = fopen(*FileToOpen,"w")) == NULL)
	{
		fp = fopen(*FileToOpen,"a");
		/*
		puts("\n ^OE");
		return FALSE;
		*/
	}

	for ( line = 0; line < next; line++)
	{
	
		for (col = 0; col < MAXCOLS; col++)
		{
			putc( text[line][col], fp );
			if ( text [line][col] == NL )
			col = MAXCOLS;
		}
	}

	fclose(fp);
	return(TRUE);
}