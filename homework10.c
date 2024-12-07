#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>

void my_print(const char *filename) {
    // 首先要确保是合法的ELF文件
    int fd;
    Elf64_Ehdr ehdr; 

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return;
    }

    if (read(fd, &ehdr, sizeof(ehdr)) != sizeof(ehdr)) {
        perror("read");
        close(fd);
        return;
    }

    if (ehdr.e_ident[EI_MAG0] != ELFMAG0 || 
        ehdr.e_ident[EI_MAG1] != ELFMAG1 || 
        ehdr.e_ident[EI_MAG2] != ELFMAG2 || 
        ehdr.e_ident[EI_MAG3] != ELFMAG3) {
        fprintf(stderr, "Not a valid ELF file\n");
        close(fd);
        return;
    }

    // 核心的print部分
    printf("Magic                            : 0x%x 0x%x 0x%x 0x%x\n", ehdr.e_ident[EI_MAG0], ehdr.e_ident[EI_MAG1],
    ehdr.e_ident[EI_MAG2], ehdr.e_ident[EI_MAG3]);
    printf("Class                            : %s\n", ehdr.e_ident[EI_CLASS] == ELFCLASS32 ? "ELF32" : "ELF64");
    printf("Data                             : %s\n", ehdr.e_ident[EI_DATA] == ELFDATA2LSB ? "little-endian" : "big-endian");
    printf("Version                          : %d\n", ehdr.e_ident[EI_VERSION]);
    printf("OS/ABI                           : %d\n", ehdr.e_ident[EI_OSABI]);
    printf("Type                             : %d\n", ehdr.e_type);
    printf("Machine                          : %d\n", ehdr.e_machine);
    printf("Version                          : %u\n", ehdr.e_version);
    printf("Entry point address              : 0x%lx\n", ehdr.e_entry);
    printf("Start of program headers         : %lu (bytes into file)\n", ehdr.e_phoff);
    printf("Start of section headers         : %lu (bytes into file)\n", ehdr.e_shoff);
    printf("Flags                            : %u\n", ehdr.e_flags);
    printf("Size of this header              : %u (bytes)\n", ehdr.e_ehsize);
    printf("Size of program headers          : %u (bytes)\n", ehdr.e_phentsize);
    printf("Number of program headers        : %u\n", ehdr.e_phnum);
    printf("Size of section headers          : %u (bytes)\n", ehdr.e_shentsize);
    printf("Number of section headers        : %u\n", ehdr.e_shnum);
    printf("Section header string table index: %u\n", ehdr.e_shstrndx);

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "A filename should be followed.\n", argv[0]);
        return EXIT_FAILURE;
    }

    stdout = freopen("./result10.log","w", stdout);
    my_print(argv[1]);

    return EXIT_SUCCESS;
}
