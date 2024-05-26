/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 21:56:15 by evella            #+#    #+#             */
/*   Updated: 2023/10/04 19:06:36 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_freecontent(void *tempcontent)
{
	free(tempcontent);
	return (NULL);
}

t_list	*ft_lstmap(t_list	*lst, void	*(*f)(void *), void	(*del)(void *))
{
	t_list	*map;
	t_list	*temp;
	void	*tempcontent;

	if (!f || !del || !lst)
		return (NULL);
	tempcontent = f(lst->content);
	map = ft_lstnew(tempcontent);
	if (!map)
		return (ft_freecontent(tempcontent));
	while (lst->next)
	{
		lst = lst->next;
		tempcontent = f(lst->content);
		temp = ft_lstnew(tempcontent);
		if (!temp)
		{
			free(tempcontent);
			ft_lstclear(&map, del);
			return (NULL);
		}
		ft_lstadd_back(&map, temp);
	}
	return (map);
}
