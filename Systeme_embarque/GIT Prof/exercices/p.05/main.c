/**
 * EIA-FR - Microprocessor : solution de l'exercice no 2.
 */

int main()
{
    asm(".long  0xe1a00000\t\n"
        ".long  0xe3a0000a\t\n"
        ".long  0xe59f1018\t\n"
        ".long  0xe1d110b0\t\n"
        ".long  0xe59f3014\t\n"
        ".long  0xe5932000\t\n"
        ".long  0xe0822001\t\n"
        ".long  0xe2500001\t\n"
        ".long  0x1afffffc\t\n"
        ".long  0xe12fff1e\t\n"
        ".long  0xa0000068\t\n"
        ".long  0xa0000064\t\n");

    return 0;
}
