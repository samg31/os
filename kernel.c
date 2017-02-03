void main();
void printString(char*);
void readString(char*);
void clearScreen(int bx, int cx);
void writeInt(int);
void readInt(int*);
int pow( int b, int e );

void main()
{
    char line[80];
    int x;
   
    /* makeInterrupt21(); */
    clearScreen(2,12);

    printString("___.   .__                 __       .___           \r\n\0");
    printString("\\_ |__ |  | _____    ____ |  | __ __| _/___  ______\r\n\0");
    printString(" | __ \\|  | \\__  \\ _/ ___\\|  |/ // __ |/ _ \\/  ___/\r\n\0");
    printString(" | \\_\\ \\  |__/ /\\ \\\\  \\___|    </ /_/ ( <_> )___ \\ \r\n\0");
    printString(" |___  /____(____  /\\___  >__|_ \\____ |\\___/____  >\r\n\0");
    printString("     \\/          \\/     \\/     \\/    \\/         \\/ \r\n\0");
    printString(" V. 1.03, C. 2017. Based on a project by M. Black. \r\n\0");
    printString(" Author(s): Sam Goodrick.\r\n\r\n\0");
   
    printString("Hola mondo.\r\n\0");
    printString("Enter a line: \0");
    readString(line);
    printString("\r\nYou typed: \0");
    printString(line);
    printString("\r\n\0");
    printString("\rEnter a number: \0");
    readInt(&x);
    printString("\nYour number is \0");
    writeInt(x);
    printString("\r\n\0");
    while(1);
}

void printString(char* c)
{
    int i = 0;
    char current;

    do
    {
	current = *(c + i);
	/* call interrupt 16 to print current */
	interrupt( 16, 14*256+current, 0, 0, 0 );
	++i;
	}while( current != '\0' );
    return;
}

void readString(char* c)
{
    int i = 0;
    char current;

    do
    {
	current = interrupt( 22, 0, 0, 0, 0 );
	interrupt( 16, 14*256+current, 0, 0, 0 );
	*(c + i) = current;

	/* if BACKSPACE is pressed */
	if( current == 0x8 )
	    if( i > 0 )
	    {
		i -= 2;
	    }

	++i;
    }while( current != 0xD ); /*continue until ENTER is pressed */
    *(c + (i - 1)) = '\0';

    return;
}

void clearScreen(int bx, int cx)
{
    int i;
    for( i = 0; i < 24; ++i )
    {
    	printString( "\r\n\0" );
    }

    interrupt( 16, 512, 0, 0, 0 );

    if( bx > 0 && cx > 0 )
	interrupt( 16, 1536, 4096 * ( bx - 1 ) + 256 * ( cx - 1 ), 0, 6223 );
    return;

}

int mod(int a, int b)
{
    int x = a;
    while (x >= b) x = x - b;
    return x;
}

int div(int a, int b)
{
    int q = 0;
    while (q * b <= a) q++;
    return (q - 1);
}

void writeInt(int x)
{
    char number[6], *d;
    int q = x, r;
    if (x < 1)
    {
	d = number; *d = 0x30; d++; *d = 0x0; d--;
    }
    else
    {
	d = number + 5;
	*d = 0x0; d--;
	while (q > 0)
	{
	    r = mod(q,10); q = div(q,10);
	    *d = r + 48; d--;
	}
	d++;
    }
    printString(d);
}

void readInt(int* number)
{
    char* input, iterator;
    int i, digit, sum, len;

    /* read a string of digits and check it's length */
    readString( input );
    for( len = 0; *(input + len) != '\0'; ++len );

    sum = i = 0;
    
    while( *(input + i) != '\0' )
    {	
	/* subtract 48 to convert from ASCII to decimal */
	digit = *(input + i) - 48;

	/* convert each digit to its appropriate decimal place */
	sum += digit*pow( 10, len-1-i );
	++i;
    }
    *number = sum;
}

int pow( int b, int e )
{
    int result = 1;
    while (e)
    {
        if (e & 1)
            result *= b;
        e >>= 1;
        b *= b;
    }

    return result;
}
