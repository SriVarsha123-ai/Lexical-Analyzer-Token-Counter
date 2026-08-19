#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char str[])
{
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue",
        "default", "do", "double", "else", "enum", "extern",
        "float", "for", "goto", "if", "int", "long",
        "register", "return", "short", "signed", "sizeof",
        "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };

    int i;

    for (i = 0; i < 32; i++)
    {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

int main()
{
    FILE *fp;
    char ch, token[100];
    int i, j;

    int keywords = 0;
    int identifiers = 0;
    int operators = 0;
    int constants = 0;
    int strings = 0;
    int separators = 0;
    int comments = 0;

    fp = fopen("sample_input.c", "r");

    if (fp == NULL)
    {
        printf("Error: Cannot open sample_input.c\n");
        return 1;
    }

    printf("TOKEN TYPE\n");
    printf("--------------------------------\n");

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isspace(ch))
            continue;

        /* Identifier or Keyword */
        if (isalpha(ch) || ch == '_')
        {
            j = 0;
            token[j++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isalnum(ch) || ch == '_'))
            {
                token[j++] = ch;
            }

            token[j] = '\0';

            if (isKeyword(token))
            {
                printf("%s : Keyword\n", token);
                keywords++;
            }
            else
            {
                printf("%s : Identifier\n", token);
                identifiers++;
            }

            if (ch != EOF)
                ungetc(ch, fp);
        }

        /* Constant */
        else if (isdigit(ch))
        {
            j = 0;
            token[j++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isdigit(ch) || ch == '.'))
            {
                token[j++] = ch;
            }

            token[j] = '\0';

            printf("%s : Constant\n", token);
            constants++;

            if (ch != EOF)
                ungetc(ch, fp);
        }

        /* String Literal */
        else if (ch == '"')
        {
            j = 0;
            token[j++] = ch;

            while ((ch = fgetc(fp)) != EOF && ch != '"')
            {
                token[j++] = ch;
            }

            if (ch == '"')
                token[j++] = ch;

            token[j] = '\0';

            printf("%s : String Literal\n", token);
            strings++;
        }

        /* Comments or Division Operator */
        else if (ch == '/')
        {
            char next = fgetc(fp);

            if (next == '/')
            {
                printf("// : Comment\n");
                comments++;

                while ((ch = fgetc(fp)) != EOF && ch != '\n');
            }
            else if (next == '*')
            {
                printf("/* */ : Comment\n");
                comments++;

                while ((ch = fgetc(fp)) != EOF)
                {
                    if (ch == '*' && (ch = fgetc(fp)) == '/')
                        break;
                }
            }
            else
            {
                printf("/ : Operator\n");
                operators++;

                if (next != EOF)
                    ungetc(next, fp);
            }
        }

        /* Operators */
        else if (ch == '+' || ch == '-' ||
                 ch == '*' || ch == '=' ||
                 ch == '<' || ch == '>' ||
                 ch == '%')
        {
            printf("%c : Operator\n", ch);
            operators++;
        }

        /* Separators */
        else if (ch == '(' || ch == ')' ||
                 ch == '{' || ch == '}' ||
                 ch == '[' || ch == ']' ||
                 ch == ';' || ch == ',')
        {
            printf("%c : Separator\n", ch);
            separators++;
        }

        /* Other special symbols */
        else
        {
            printf("%c : Special Symbol\n", ch);
        }
    }

    fclose(fp);

    printf("\nTOKEN COUNT\n");
    printf("--------------------------------\n");
    printf("Keywords       : %d\n", keywords);
    printf("Identifiers    : %d\n", identifiers);
    printf("Operators      : %d\n", operators);
    printf("Constants      : %d\n", constants);
    printf("String Literals: %d\n", strings);
    printf("Separators     : %d\n", separators);
    printf("Comments       : %d\n", comments);

    return 0;
}