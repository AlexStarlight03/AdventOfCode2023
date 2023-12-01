
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct s_index
{
	int	i;
	int	j;
}	t_index;



void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	if (!s)
		return ;
	str = (unsigned char *)s;
	while (n-- > 0)
		*(str++) = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	else
		ft_bzero(ptr, size * count);
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*string_search(const char *s, char c)
{
	int	i;

	i = ft_strlen(s);
	if (!s)
		return (0);
	while (i >= 0)
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}

char	*str_join(char const *s1, char const *s2)
{
	size_t	i;
	size_t	y;
	char	*str;

	i = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[y] != '\0')
	{
		str[i + y] = s2[y];
		y++;
	}
	str[i + y] = '\0';
	return ((char *)str);
}

char	*next_call_prep(char *s)
{
	t_index	index;
	char	*new_line;

	index.i = 0;
	index.j = 0;
	while (s[index.i] && s[index.i] != '\n')
		index.i++;
	if (!s[index.i])
	{
		free(s);
		return (NULL);
	}
	new_line = ft_calloc((ft_strlen(s) - index.i + 1), sizeof(char));
	if (!new_line)
		return (NULL);
	index.i++;
	while (s[index.i])
		new_line[index.j++] = s[index.i++];
	if (*new_line == 0)
	{
		free (new_line);
		new_line = NULL;
	}
	free (s);
	return (new_line);
}

char	*define_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n' && str[i])
		line[i++] = '\n';
	return (line);
}

char	*join_free(char *result, char *buffer)
{
	char	*joined;

	joined = str_join(result, buffer);
	free(result);
	if (!joined)
	{
		free(result);
		free(joined);
		return (NULL);
	}
	if (*joined == 0)
	{
		free(joined);
		joined = NULL;
	}
	return (joined);
}

char	*read_file(int fd, char *result)
{
	char	*buffer;
	int		count_read;

	if (!result)
		result = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	count_read = 1;
	while (count_read != 0 && !string_search(buffer, '\n'))
	{
		count_read = read(fd, buffer, BUFFER_SIZE);
		if (count_read == -1)
		{
			free(buffer);
			free(result);
			return (NULL);
		}
		buffer[count_read] = 0;
		result = join_free(result, buffer);
	}
	free(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char		*buffer[OPEN_MAX];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	line = define_line(buffer[fd]);
	buffer[fd] = next_call_prep(buffer[fd]);
	return (line);
}

long long int add_all(long long int *numbers)
{
	long long int	i;
	long long int result;

	i = 0;
	result = 0;
	printf("RESULT %s\n", "HELLO");
	while (i < 200)
	{
		result += numbers[i];
		i++;
	}
	return (result);
}

int	ft_strncmp(char *s1, char *s2, size_t n, int y)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[y] != '\0' && s2[i] != '\0' && s1[y] == s2[i])
	{
			i++;
			y++;
	}
	return ((unsigned char)s1[y] - (unsigned char)s2[i]);
}

char	*change_names(char *str)
{
	int		i;
	int		j;
	char	*newstr;


	i = 0;
	j = 0;
	newstr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i] != '\0')
	{
		if(ft_strncmp(str, "one", 3, i) == 0)
			newstr[j] = 49;
		else if(ft_strncmp(str, "two", 3, i) == 0)
			newstr[j] = 50;
		else if(ft_strncmp(str, "three", 5, i) == 0)
			newstr[j] = 51;
		else if(ft_strncmp(str, "four", 4, i) == 0)
			newstr[j] = 52;

		else if(ft_strncmp(str, "five", 4, i) == 0)

			newstr[j] = 53;

		else if(ft_strncmp(str, "six", 3, i) == 0)

			newstr[j] = 54;

		else if(ft_strncmp(str, "seven", 5, i) == 0)

			newstr[j] = 55;

		else if(ft_strncmp(str, "eight", 5, i) == 0)

			newstr[j] = 56;

		else if(ft_strncmp(str, "nine", 4, i) == 0)

			newstr[j] = 57;

		else
			newstr[j] = str[i];
		j++;
		i++;
	}
	newstr[j] = '\0';
	printf("RESULT STRING %s\n", newstr);
	return (newstr);
}

int	get_number(char *file)
{
	int	fd;
	int	count;
	long long int	*tab;
	char *str;
	char *check;
	char *nb;
	int	first;
	int	last;
	long long int	trans_num;
	long long int	result;

	fd = open(file, O_RDONLY, 0);
	count = -1;
	check = get_next_line(fd);
	while (check != NULL)
	{
		nb = malloc(sizeof(char ) * 3);
		count++;
		first = 0;
		str = change_names(check);
		while (str[first] < '0' || str[first] > '9')
			first = first + 1;
		nb[0] = str[first];
		last = ft_strlen(str) - 1;
		while (str[last] < '0' || str[last] > '9')
			last = last - 1;
		nb[1] = str[last];
		nb[2] = '\0';
		free(str);
		free(check);
		trans_num = atoi(nb);
		tab[count] = trans_num;
		printf("IN THE TAB: %lld\n", tab[count]);
		check = get_next_line(fd);
	}
	printf("RESULT %s\n", "HELLO");
	result = add_all(tab);
	printf("RESULT %lld\n", result);
	return (0);
}

int	main(int argc, char **argv)
{
	get_number(argv[1]);
	return (0);
}
