/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:31:45 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:31:45 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}
/*#include <stdio.h>
int main()
{
    const char *str = "Hello, World!";
    int ch = 'W';
    char *result;

    // طباعة السلسلة النصية والحرف المراد البحث عنه
    printf("String: \"%s\"\n", str);
    printf("Character to find: '%c'\n", ch);

    // استدعاء ft_strchr للبحث عن الحرف في السلسلة النصية
    result = ft_strchr(str, ch);

    // طباعة النتيجة
    if (result)
        printf("Character found at position: %ld\n", result - str);
    else
        printf("Character not found\n");

    return 0;
}*/