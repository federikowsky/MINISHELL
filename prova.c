#include <stdio.h>
#include <string.h>
#include <dirent.h>

# define Directory  4
# define File       8

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) \
		|| (c == 92) || (c == 95))
		return (1);
	else
		return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!n)
		return (0);
	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int main(int argc, char **argv)
{
    DIR *folder;
    DIR *sub_folder;
    struct dirent *entry;
    struct dirent *sub_entry;
    int i = 1;

    if (argc < 2)
        folder = opendir(".");
	else
    	folder = opendir(argv[1]);
    entry = readdir(folder);
    while(entry)
    {
        if (entry->d_type == File)
            printf("%s\n", entry->d_name);
        entry=readdir(folder);
    }
    closedir(folder);


    folder = opendir(".");
    entry=readdir(folder);
    while(entry)
    {
        if (ft_isalpha(entry->d_name[0]) && entry->d_type == Directory)
        {
            sub_folder = opendir(entry->d_name);
            sub_entry = readdir(sub_folder);
            printf("%s:\n", entry->d_name);
            while (sub_entry)
            {   
                if (ft_isalpha(sub_entry->d_name[0]))
                printf("%s \n", sub_entry->d_name);
                sub_entry = readdir(sub_folder);
            }
            printf("\n");
        }
        entry=readdir(folder);
    }
    closedir(folder);
    return(0);
}