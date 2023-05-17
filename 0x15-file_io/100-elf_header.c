#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void checkElfFileType(unsigned char *ident);
void printMagicNumbers(unsigned char *ident);
void printClass(unsigned char *ident);
void printData(unsigned char *ident);
void printVersion(unsigned char *ident);
void printAbi(unsigned char *ident);
void printOsAbi(unsigned char *ident);
void printFileType(unsigned int type, unsigned char *ident);
void printEntryPoint(unsigned long int entry, unsigned char *ident);
void closeElfFile(int file);

/**
 * checkElfFileType - Checks file is  ELF file.
 * @ident: A pointer to  array containing the ELF magic numbers.
 *
 * Description: If the file is not  ELF file - exit code 98.
 */
void checkElfFileType(unsigned char *ident)
{
    int index;

    for (index = 0; index < 4; index++)
    {
        if (ident[index] != 127 &&
            ident[index] != 'E' &&
            ident[index] != 'L' &&
            ident[index] != 'F')
        {
            dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
            exit(98);
        }
    }
}

/**
 * printMagicNumbers - Prints  magic numbers of  ELF header.
 * @ident: A pointer to  array containing  ELF magic numbers.
 *
 * Description: Magic numbers are separated by spaces.
 */
void printMagicNumbers(unsigned char *ident)
{
    int index;

    printf("  Magic:   ");

    for (index = 0; index < EI_NIDENT; index++)
    {
        printf("%02x", ident[index]);

        if (index == EI_NIDENT - 1)
            printf("\n");
        else
            printf(" ");
    }
}

/**
 * printClass - Prints  class of an ELF header.
 * @ident: A pointer to n array containing  ELF class.
 */
void printClass(unsigned char *ident)
{
    printf("  Class:                             ");

    switch (ident[EI_CLASS])
    {
        case ELFCLASSNONE:
            printf("none\n");
            break;
        case ELFCLASS32:
            printf("ELF32\n");
            break;
        case ELFCLASS64:
            printf("ELF64\n");
            break;
        default:
            printf("<unknown: %x>\n", ident[EI_CLASS]);
    }
}
/**
 * printData - Prints  data encoding of  ELF heaer.
 * @ident: A pointer to array contain  ELF identification.
 *
 * Description: Prints  data encoding format oe ELF file.
 */
void printData(unsigned char *ident)
{
    printf("  Data:                              ");

    switch (ident[EI_DATA])
    {
        case ELFDATANONE:
            printf("none\n");
            break;
        case ELFDATA2LSB:
            printf("2's complement, little endian\n");
            break;
        case ELFDATA2MSB:
            printf("2's complement, big endian\n");
            break;
        default:
            printf("<unknown: %x>\n", ident[EI_CLASS]);
    }
}

/**
 * printVersion - Prints  version of  ELF header.
 * @ident: A pointer to  array containing the ELF identification.
 *
 * Description: Prints the version of the ELF file.
 */
void printVersion(unsigned char *ident)
{
    printf("  Version:                           %d",
           ident[EI_VERSION]);

    switch (ident[EI_VERSION])
    {
        case EV_CURRENT:
            printf(" (current)\n");
            break;
        default:
            printf("\n");
            break;
    }
}

/**
 * printOsAbi - Prints  OS/ABI of an ELF header.
 * @ident: A pointer to an array containing  ELF identification.
 *
 * Description: Prints  operating system and ABI associated with  ELF file.
 */
void printOsAbi(unsigned char *ident)
{
    printf("  OS/ABI:                            ");

    switch (ident[EI_OSABI])
    {
        case ELFOSABI_NONE:
            printf("UNIX - System V\n");
            break;
        case ELFOSABI_HPUX:
            printf("UNIX - HP-UX\n");
            break;
        case ELFOSABI_NETBSD:
            printf("UNIX - NetBSD\n");
            break;
        case ELFOSABI_LINUX:
            printf("UNIX - Linux\n");
            break;
        case ELFOSABI_SOLARIS:
            printf("UNIX - Solaris\n");
            break;
        case ELFOSABI_IRIX:
            printf("UNIX - IRIX\n");
            break;
        case ELFOSABI_FREEBSD:
            printf("UNIX - FreeBSD\n");
            break;
        case ELFOSABI_TRU64:
            printf("UNIX - TRU64\n");
            break;
        case ELFOSABI_ARM:
            printf("ARM\n");
            break;
        case ELFOSABI_STANDALONE:
            printf("Standalone App\n");
            break;
        default:
            printf("<unknown: %x>\n", ident[EI_OSABI]);
    }
}

/**
 * printAbi - Prints  ABI version of an ELF header.
 * @ident: A pointer to an array containing  ELF identification.
 *
 * Description: Prints  ABI version of  ELF file.
 */
void printAbi(unsigned char *ident)
{
    printf("  ABI Version:                       %d\n",
           ident[EI_ABIVERSION]);
}
/**
 * printType - type of  ELF header.
 * @type: The ELF type.
 * @ident: A pointer to array containing  ELF identification.
 *
 * Description: Prints  type of  ELF file.
 */
void printType(unsigned int type, unsigned char *ident)
{
    if (ident[EI_DATA] == ELFDATA2MSB)
        type >>= 8;

    printf("  Type:                              ");

    switch (type)
    {
        case ET_NONE:
            printf("NONE (None)\n");
            break;
        case ET_REL:
            printf("REL (Relocatable file)\n");
            break;
        case ET_EXEC:
            printf("EXEC (Executable file)\n");
            break;
        case ET_DYN:
            printf("DYN (Shared object file)\n");
            break;
        case ET_CORE:
            printf("CORE (Core file)\n");
            break;
        default:
            printf("<unknown: %x>\n", type);
    }
}

/**
 * printEntry - Prints  entry point of an ELF header.
 * @entry: The address of  ELF entry point.
 * @ident: A pointer to  array containing  ELF identification.
 *
 * Description: Prints  entry point address of  ELF file.
 */
void printEntry(unsigned long int entry, unsigned char *ident)
{
    printf("  Entry point address:               ");

    if (ident[EI_DATA] == ELFDATA2MSB)
    {
        entry = ((entry << 8) & 0xFF00FF00) |
                 ((entry >> 8) & 0xFF00FF);
        entry = (entry << 16) | (entry >> 16);
    }

    if (ident[EI_CLASS] == ELFCLASS32)
        printf("%#x\n", (unsigned int)entry);
    else
        printf("%#lx\n", entry);
}

/**
 * closeElf - Closes  ELF file.
 * @fileDescriptor: The file descriptor of  ELF file.
 *
 * Description: Closes  file associated with  file descriptor.
 * If  file cannot be closed, it exits with code 98.
 */
void closeElf(int fileDescriptor)
{
    if (close(fileDescriptor) == -1)
    {
        dprintf(STDERR_FILENO,
                "Error: Can't close file descriptor %d\n", fileDescriptor);
        exit(98);
    }
}
/**
 * main - Displays the information contained in the
 *        ELF header at the start of an ELF file.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: This program reads an ELF file specified as a command-line argument
 * and displays the information contained in its ELF header. If the file is not an
 * ELF file or if the function fails, it exits with code 98.
 */
int main(int __attribute__((__unused__)) argc, char *argv[])
{
    Elf64_Ehdr *elfHeader;
    int fileDescriptor, readResult;

    fileDescriptor = open(argv[1], O_RDONLY);
    if (fileDescriptor == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
        exit(98);
    }

    elfHeader = malloc(sizeof(Elf64_Ehdr));
    if (elfHeader == NULL)
    {
        closeElf(fileDescriptor);
        dprintf(STDERR_FILENO, "Error: Can't allocate memory for ELF header\n");
        exit(98);
    }

    readResult = read(fileDescriptor, elfHeader, sizeof(Elf64_Ehdr));
    if (readResult == -1)
    {
        free(elfHeader);
        closeElf(fileDescriptor);
        dprintf(STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
        exit(98);
    }

    checkElf(elfHeader->e_ident);
    printf("ELF Header:\n");
    printMagic(elfHeader->e_ident);
    printClass(elfHeader->e_ident);
    printData(elfHeader->e_ident);
    printVersion(elfHeader->e_ident);
    printOsabi(elfHeader->e_ident);
    printAbi(elfHeader->e_ident);
    printType(elfHeader->e_type, elfHeader->e_ident);
    printEntry(elfHeader->e_entry, elfHeader->e_ident);

    free(elfHeader);
    closeElf(fileDescriptor);
    return 0;
}
