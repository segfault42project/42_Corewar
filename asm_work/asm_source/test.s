# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.s                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabougue <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/17 15:56:18 by rabougue          #+#    #+#              #
#    Updated: 2017/02/17 22:23:04 by rabougue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#klkjl
 ;klkjl	
.name ""
.comment ""

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1
		zjmp %:live
