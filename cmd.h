#include<stdio.h>
#include<curses.h>

#define MAXLINES	400
#define MAXCOLS		100

#define FALSE		0
#define TRUE		1

#define SP			' '
#define NL			'\n'
#define CR			'\r'
#define	BS			'\b'	/*Back Space*/



char	getnextchar(void),
		read_command(int *pn1, int *pn2, int *valid);
int		check_command(char cm, int *n1, int *n2),
		isadigit(char c),
		get_int(char c),
		save_text(void);
void	process_option(char com, int *pn1, int *pn2),
		helpscreen(void),
		insert(int line),
		deleter (int n1, int *n2),
		print(int start, int end),
		movetext(int line),
		read_file(void),
		init_text(void);

/*externs*/

int next = 0;

char text [MAXLINES][MAXCOLS];

char *FileToOpen[256];