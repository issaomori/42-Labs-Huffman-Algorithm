#include "encoder.h"

encoder g_data;

void	check_args(int argc, char **argv)
{
	int i = 1, size_file_txt = 0;
	unsigned char *text;

	setlocale(LC_ALL, "C.UTF-8");
	init_global(g_data.frequency_list);
	if(argc <= 1)
	{
		printf("Error: Invalid number of arguments!\n");
		exit(1);
	}
	while(argv[i])
	{
		text = (unsigned char *)strdup("");
		if(access(argv[i], F_OK | R_OK) != -1)
		{
			size_file_txt = count_txt(argv[i]);
			text = calloc(size_file_txt + 1, sizeof(unsigned char));
			read_txt(argv[i], text);
		}
		if(strlen((char*)text) > 0)
			g_data.txt = str_join(g_data.txt, text);
		else
			g_data.txt = str_join(g_data.txt, (unsigned char*)argv[i]);
		if (i < argc - 1)
			g_data.txt = str_join(g_data.txt, " ");
		free(text);
		i++;
	}
}

int main (int argc,char **argv)
{
	check_args(argc, argv);
	g_data.size_char = strlen(g_data.txt);
	init_list();
	make_tree();
	make_dicionary();
	encode();
	compact();
	generate_memory_shared();
	free_all();
	return (0);
}
