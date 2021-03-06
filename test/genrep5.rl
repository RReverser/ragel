/*
 * @LANG: c
 */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

const char s[4096];

struct nfa_stack
{
	void *data;
	unsigned long sz;
};

struct nfa_bp_rec
{
	long state;
	const char *p;
	long popTrans;
	long q_2;
};

%%{
	machine genrep;
	alphtype unsigned char;

	action psh
	{
		nfa_bp[nfa_len].q_2 = q_2;
	}

	action pop
	{ ({
		q_2 = nfa_bp[nfa_len].q_2;
		1;
	}) }

	action ini_2 	{
		({  q_2 = 0; 1; })
	}

	action stay_2 	{
		({ 1; })
	}

	action repeat_2 	{
		({ ++q_2 < 2; })
	}

	action exit_2 	{
		({ ++q_2 >= 2; })
	}

	action leaving
	{
		printf( "  -> leaving\n" );
	}

	main :=
		(
			'hello' %leaving
				(:nfa( 2, ( ' ' ), psh, pop, ini_2, stay_2, repeat_2, exit_2):)
			'there'
		)
		:>
		any @{
			printf( "------ MATCH\n" );
		};

	write data;
}%%

int test( const char *p )
{
	int len = strlen( p ) + 1;
	const char *pe = p + len;
	int cs;

	struct nfa_bp_rec *nfa_bp = (struct nfa_bp_rec*) s;
	long nfa_len = 0;
	long nfa_count = 0;

	long q_2 = 0;

	printf( "testing: %s\n", p );

	%%{
		machine genrep;
		write init;
		write exec;
	}%%

	return 0;
}

int main()
{
	test( "hellothere" );
	test( "hello there" );
	test( "hello  there" );
	test( "hello   there" );
	test( "hello    there" );
	return 0;
}

########## OUTPUT ##########
testing: hellothere
  -> leaving
testing: hello there
  -> leaving
testing: hello  there
  -> leaving
------ MATCH
testing: hello   there
  -> leaving
testing: hello    there
  -> leaving
