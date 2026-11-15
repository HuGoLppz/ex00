/*
Aquí está la función read_file, que guarda todo el texto del
fichero numbers.dict en *text y devuelve 1 (o 0 si hay error).
Para ello con file_size se calcula el tamaño del archivo a leer,
con read_into, copias la información.
Lo ejecuta todo read_file, función que se ejecuta en parse_dict.c
*/
#include "rush02.h"

static int	file_size(char *path)
{
	char	buf[1024];
	int		fd;
	int		bytes;
	int		total;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	total = 0;
	bytes = read(fd, buf, 1024);
	while (bytes > 0)
	{
		total = total + bytes;
		bytes = read(fd, buf, 1024);
	}
	close(fd);
	if (bytes < 0)
		return (-1);
	return (total);
}

static int	read_into(char *path, char *text, int size)
{
	int	fd;
	int	bytes;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	bytes = read(fd, text, size);
	close(fd);
	if (bytes != size)
		return (0);
	text[size] = '\0';
	return (1);
}

int	read_file(char *path, char **text)
{
	char	*content;
	int		size;

	size = file_size(path);
	if (size < 0)
		return (0);
	content = malloc(size + 1);
	if (content == NULL)
		return (0);
	if (!read_into(path, content, size))
	{
		free(content);
		return (0);
	}
	*text = content;
	return (1);
}
