/*
 * "Software pw3270, desenvolvido com base nos códigos fontes do WC3270  e X3270
 * (Paul Mattes Paul.Mattes@usa.net), de emulação de terminal 3270 para acesso a
 * aplicativos mainframe. Registro no INPI sob o nome G3270.
 *
 * Copyright (C) <2008> <Banco do Brasil S.A.>
 *
 * Este programa é software livre. Você pode redistribuí-lo e/ou modificá-lo sob
 * os termos da GPL v.2 - Licença Pública Geral  GNU,  conforme  publicado  pela
 * Free Software Foundation.
 *
 * Este programa é distribuído na expectativa de  ser  útil,  mas  SEM  QUALQUER
 * GARANTIA; sem mesmo a garantia implícita de COMERCIALIZAÇÃO ou  de  ADEQUAÇÃO
 * A QUALQUER PROPÓSITO EM PARTICULAR. Consulte a Licença Pública Geral GNU para
 * obter mais detalhes.
 *
 * Você deve ter recebido uma cópia da Licença Pública Geral GNU junto com este
 * programa; se não, escreva para a Free Software Foundation, Inc., 51 Franklin
 * St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Este programa está nomeado como - e possui - linhas de código.
 *
 * Contatos:
 *
 * perry.werneck@gmail.com	(Alexandre Perry de Souza Werneck)
 * erico.mendonca@gmail.com	(Erico Mascarenhas Mendonça)
 *
 */

 #include <internals.h>

/*--[ Implement ]------------------------------------------------------------------------------------*/

 GtkWidget * v3270_dialog_create_grid(GtkAlign align)
 {
 	GtkWidget * grid = gtk_grid_new();

 	gtk_grid_set_row_spacing(GTK_GRID(grid),6);
 	gtk_grid_set_column_spacing(GTK_GRID(grid),12);

	g_object_set(G_OBJECT(grid),"margin-top",6,NULL);
	gtk_widget_set_halign(GTK_WIDGET(grid),align);

	return grid;
 }

 GtkWidget * v3270_dialog_create_frame(GtkWidget * child, const gchar *title)
 {
	GtkFrame			* frame		= GTK_FRAME(gtk_frame_new(""));
	g_autofree gchar	* markup	= g_strdup_printf("<b>%s</b>",title);
	GtkWidget			* label		= gtk_label_new(NULL);

	gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_NONE);
	gtk_label_set_markup(GTK_LABEL(label),markup);
	gtk_frame_set_label_widget(GTK_FRAME(frame),label);

	gtk_container_add(GTK_CONTAINER(frame),GTK_WIDGET(child));

	g_object_set(G_OBJECT(frame),"margin-top",6,NULL);

	return GTK_WIDGET(frame);
 }

 GtkWidget * v3270_box_pack_frame(GtkWidget *box, GtkWidget *child, const gchar *title, GtkAlign align, gboolean expand, gboolean fill, guint padding)
 {
	GtkWidget * frame = v3270_dialog_create_frame(child,title);
	gtk_widget_set_halign(GTK_WIDGET(frame),align);
	gtk_box_pack_start(GTK_BOX(box),frame,expand,fill,padding);
	return child;
 }


