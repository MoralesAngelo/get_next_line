/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:42:03 by mac               #+#    #+#             */
/*   Updated: 2024/11/26 17:18:10 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h> // - para usar el open 
#include <stdio.h>

int	main(void)
{
	char	*line;

	int fd = open("texto.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error abriendo archivo");
		return (1);
	}
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}

/*cc -Wall -Werror -Wextra -D BUFFER_SIZE=2 get_next_line.c get_next_line_utils.c
main.c -o gnl_test
./gnl_test*/
