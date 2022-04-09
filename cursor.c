/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:19:07 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/09 18:19:08 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>
#include <stdlib.h>

int main(void)
{
	
	Display *display;
	int active_screen;
	Window active_root;

	display = XOpenDisplay(NULL);
	active_screen = DefaultScreen(display);
	active_root = RootWindow(display, active_screen);
	XFixesHideCursor(display, active_root);
	XFlush(display);

	while (1) {
		sleep(0.01);
	}

	return 0;
}
