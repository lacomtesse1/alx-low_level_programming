#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf(unsigned char *elf_ident);
void print_magic(unsigned char *elf_ident);
void print_class(unsigned char *elf_ident);
void print_data(unsigned char *elf_ident);
void print_version(unsigned char *elf_ident);
void print_abi(unsigned char *elf_ident);
void print_osabi(unsigned char *elf_ident);
void print_type(unsigned int elf_type, unsigned char *elf_ident);
void print_entry(unsigned long int entry_point, unsigned char *elf_ident);
void close_elf(int file_descriptor);

/**
 * check_elf - Checks file is an ELF file.
 * @elf_ident: A pointer to  array contain ELF magic numbers.
 *
 * Description: If the file not ELF file, it exits with code 98.
 */
void check_elf(unsigned char *elf_ident)
{
    int index;

    for (index = 0; index < 4; index++)
    {
        if (elf_ident[index] != 127 &&
            elf_ident[index] != 'E' &&
            elf_ident[index] != 'L' &&
            elf_ident[index] != 'F')
        {
            dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
            exit(98);
        }
    }
}

/**
 * print_magic - Print magic numbers of ELF header.
 * @elf_ident: A pointer to array containing ELF magic numbers.
 *
 * Description: Magic numbers are separated by spaces.
 */
void print_magic(unsigned char *elf_ident)
{
    int index;

    printf(" Magic: ");

    for (index = 0; index < EI_NIDENT; index++)
    {
        printf("%02x", elf_ident[index]);

        if (index == EI_NIDENT - 1)
            printf("\n");
        else
            printf(" ");
    }
}

/**
 * print_class - Print class of ELF header.
 * @elf_ident: A pointer to  array containing the ELF class.
 */
void print_class(unsigned char *elf_ident)
{
    printf(" Class: ");

    switch (elf_ident[EI_CLASS])
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
        printf("<unknown: %x>\n", elf_ident[EI_CLASS]);
    }
}

/**
 * print_data - Prints the data of ELF header.
 * @elf_ident: A pointer to  array containing ELF class.
 */
void print_data(unsigned char *elf_ident)
{
    printf(" Data: ");

    switch (elf_ident[EI_DATA])
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
        printf("<unknown: %x>\n", elf_ident[EI_CLASS]);
    }
}
/**
 * print_version - Print version of  ELF header.
 * @elf_ident: A pointer to  array containing the ELF version.
 */
void print_version(unsigned char *elf_ident)
{
    printf(" Version: %d", elf_ident[EI_VERSION]);

    switch (elf_ident[EI_VERSION])
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
 * print_osabi - Print OS/ABI of an ELF header.
 * @elf_ident: A pointer to  array containing  ELF version.
 */
void print_osabi(unsigned char *elf_ident)
{
    printf(" OS/ABI: ");

    switch (elf_ident[EI_OSABI])
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
        printf("<unknown: %x>\n", elf_ident[EI_OSABI]);
    }
}

/**
 * print_abi - Prints the ABI version of ELF header.
 * @elf_ident: A pointer to  array containing the ELF ABI version.
 */
void print_abi(unsigned char *elf_ident)
{
    printf(" ABI Version: %d\n", elf_ident[EI_ABIVERSION]);
}
/**
 * print_type - Print type of  ELF header.
 * @elf_type: ELF type.
 * @elf_ident: A pointer to  array containing the ELF class.
 */
void print_type(unsigned int elf_type, unsigned char *elf_ident)
{
    if (elf_ident[EI_DATA] == ELFDATA2MSB)
        elf_type >>= 8;

    printf(" Type: ");

    switch (elf_type)
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
        printf("<unknown: %x>\n", elf_type);
    }
}

/**
 * print_entry - Prints  entry point of  ELF header.
 * @elf_entry:  address of  ELF entry point.
 * @elf_ident: A pointer to  array containing the ELF class.
 */
void print_entry(unsigned long int elf_entry, unsigned char *elf_ident)
{
    printf(" Entry point address: ");

    if (elf_ident[EI_DATA] == ELFDATA2MSB)
    {
        elf_entry = ((elf_entry << 8) & 0xFF00FF00) |
                    ((elf_entry >> 8) & 0xFF00FF);
        elf_entry = (elf_entry << 16) | (elf_entry >> 16);
    }

    if (elf_ident[EI_CLASS] == ELFCLASS32)
        printf("%#x\n", (unsigned int)elf_entry);
    else
        printf("%#lx\n", elf_entry);
}

/**
 * close_elf - Close ELF file.
 * @file_descriptor: The file descriptor of the ELF file.
 *
 * Description: If the file cannot be closed - exit code 98.
 */
void close_elf(int file_descriptor)
{
    if (close(file_descriptor) == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", file_descriptor);
        exit(98);
    }
}

/**
 * main - Displays information contained in the
 * ELF header at the start of an ELF file.
 * @argument_count: The number of arguments supplied to program.
 * @arguments: An array of pointers to  arguments.
 *
 * Return: 0 on success.
 *
 * Description: If  file  not  ELF File or
 * the function fails - exit code 98.
 */
int main(int __attribute__((__unused__)) argument_count, char *arguments[])
{
    Elf64_Ehdr *elf_header;
    int file_descriptor, read_status;

    file_descriptor = open(arguments[1], O_RDONLY);
    if (file_descriptor == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't read file %s\n", arguments[1]);
        exit(98);
    }

    elf_header = malloc(sizeof(Elf64_Ehdr));
    if (elf_header == NULL)
    {
        close_elf(file_descriptor);
        dprintf(STDERR_FILENO, "Error: Can't read file %s\n", arguments[1]);
        exit(98);
    }

    read_status = read(file_descriptor, elf_header, sizeof(Elf64_Ehdr));
    if (read_status == -1)
    {
        free(elf_header);
        close_elf(file_descriptor);
        dprintf(STDERR_FILENO, "Error: %s: No such file\n", arguments[1]);
		exit(98);
	}

	check_elf(elf_header->e_ident);
	printf("ELF Header:\n");
	print_magic(elf_header->e_ident);
	print_class(elf_header->e_ident);
	print_data(elf_header->e_ident);
	print_version(elf_header->e_ident);
	print_osabi(elf_header->e_ident);
	print_abi(elf_header->e_ident);
	print_type(elf_header->e_type, elf_header->e_ident);
	print_entry(elf_header->e_entry, elf_header->e_ident);

	free(elf_header);
	close_elf(file_descriptor);
	return (0);
}

