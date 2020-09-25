.name "stayin' alive"
.comment "Ha, Ha, Ha, stayiiiiin' aliiiiiiiiiive"
	
mov:
	live	%99
	sti		r6, :up, r4
	add		r4, r8, r4
	sti		r6, :up, r4
	add		r4, r8, r4
	fork	%:mov
	zjmp	%:mov

torpille_front:
	live	%4242
	add		r4, r8, r4
	sti		r6, r4, %:up
	add		r4, r8, r4
	sti		r6, r4, %:up
	zjmp	%:torpille_front

up:

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instruments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <dpenney@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 06:21:48 by dpenney           #+#    #+#             */
/*   Updated: 2020/09/15 06:44:55 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */