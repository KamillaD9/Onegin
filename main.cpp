#include <cstdio>
#include <cstdlib>
#include <cstring>

const int FILENAME_LENGHT = 100;

char** Read_Lines( char **buf, int *linesCount, FILE* inf);
int Print_Lines ( FILE* outf, char** lines, int linesCount);
long File_Size ( FILE* file);
int Replace ( char** buf, char oldc, char newc, int sizeBuf);
int Lines_Compare( const void* first, const void* second );

int main()
{
    printf( "Write the InPut File's name: " );
    char inFile[FILENAME_LENGHT];
    scanf( "%s", inFile );

    FILE* inf = fopen( inFile, "r" );
    char *buf = nullptr;
    int linesCount = 0;
    char** lines = Read_Lines( &buf, &linesCount, inf );
    fclose(inf);

    qsort( lines, linesCount, sizeof( char* ), Lines_Compare );

    printf( "Write the OutPut File's name: " );
    char outFile[FILENAME_LENGHT];
    scanf( "%s", outFile );
    FILE* outf = fopen( outFile, "w" );
    Print_Lines( outf, lines, linesCount );
    return 0;
}


char** Read_Lines( char **buf, int *linesCount, FILE* inf)
{
    long sizeBuf = File_Size( inf );
    *buf = (char*)calloc(sizeof(char), sizeBuf);

    fread( *buf, sizeof( char ), sizeBuf, inf );
    int numberOfLines = Replace( buf, '\n', '\0', sizeBuf );

    char **lines = (char**)calloc(sizeof(char*), numberOfLines);
    *linesCount = numberOfLines;

    for(int i = 0; i <= sizeBuf ; ++i )
    {
        lines[i] = *buf+i;
        i += strlen(*buf+i);
    }

    return lines;
}


int Print_Lines ( FILE* outf, char** lines, int linesCount)
{
    for ( int i = 0; i < linesCount; ++i)
    {
        fprintf( outf, "%s\n", lines[i]);
    }

}


long File_Size ( FILE* file)
{
    fseek( file, 0, SEEK_END );
    long fileSize = ftell(file);
    fseek ( file, 0, SEEK_SET );
    return fileSize;
}


int Replace ( char** buf, char oldc, char newc, int sizeBuf)
{
    int result = 0;
    for ( char* ptr = *buf; ptr < *buf+sizeBuf; ++ptr )
    {
        if ( *ptr == oldc)
        {
            *ptr = newc;
            result++;
        }
    }
    return result;
}


int Lines_Compare( const void* first, const void* second )
{
    return strcmp( (char*)first, (char*)second );
}

