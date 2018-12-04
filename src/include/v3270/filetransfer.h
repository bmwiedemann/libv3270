/*
 * "Software pw3270, desenvolvido com base nos códigos fontes do WC3270  e X3270
 * (Paul Mattes Paul.Mattes@usa.net), de emulação de terminal 3270 para acesso a
 * aplicativos mainframe. Registro no INPI sob o nome G3270. Registro no INPI sob
 * o nome G3270.
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
 * Este programa está nomeado como v3270ft.h e possui - linhas de código.
 *
 * Contatos:
 *
 * perry.werneck@gmail.com	(Alexandre Perry de Souza Werneck)
 * erico.mendonca@gmail.com	(Erico Mascarenhas Mendonça)
 *
 */

#ifndef V3270FT_H_INCLUDED

	#define V3270FT_H_INCLUDED 1

	#include <glib/gi18n.h>
	#include <gtk/gtk.h>
	#include <lib3270.h>
	#include <lib3270/filetransfer.h>

	G_BEGIN_DECLS

	#define GTK_TYPE_V3270FT			(v3270ft_get_type ())
	#define GTK_V3270FT(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_V3270FT, v3270ft))
	#define GTK_V3270FT_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_V3270FT, v3270ftClass))
	#define GTK_IS_V3270FT(obj)			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_V3270FT))
	#define GTK_IS_V3270FT_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_V3270FT))
	#define GTK_V3270FT_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_V3270FT, v3270ftClass))

	typedef struct _v3270ft			v3270ft;
	typedef struct _v3270ftClass	v3270ftClass;


	LIB3270_EXPORT GtkWidget			* v3270ft_new(void);
	LIB3270_EXPORT GType      			  v3270ft_get_type(void);
	LIB3270_EXPORT void					  v3270ft_set_options(GtkWidget *widget, LIB3270_FT_OPTION opt);
	LIB3270_EXPORT LIB3270_FT_OPTION	  v3270ft_get_options(GtkWidget *widget);
	LIB3270_EXPORT void 				  v3270ft_reset(GtkWidget *widget);
	LIB3270_EXPORT gboolean				  v3270ft_is_valid(GtkWidget *widget);
	LIB3270_EXPORT guint				  v3270ft_get_length(GtkWidget *widget);
	LIB3270_EXPORT void					  v3270ft_select_first(GtkWidget *widget);
	LIB3270_EXPORT void					  v3270ft_select_last(GtkWidget *widget);
	LIB3270_EXPORT void					  v3270ft_select_previous(GtkWidget *widget);
	LIB3270_EXPORT void					  v3270ft_select_next(GtkWidget *widget);
	LIB3270_EXPORT void					  v3270ft_remove_selected(GtkWidget *widget);
	LIB3270_EXPORT void					  v3270ft_remove_all(GtkWidget *widget);
	LIB3270_EXPORT void					  v3270ft_save(GtkWidget *widget,const gchar *filename);
	LIB3270_EXPORT void					  v3270ft_load(GtkWidget *widget,const gchar *filename);

	LIB3270_EXPORT gboolean				  v3270ft_has_selected(GtkWidget *widget);
	LIB3270_EXPORT gboolean				  v3270ft_has_next(GtkWidget *widget);

	LIB3270_EXPORT const gchar 			* v3270ft_get_local_filename(GtkWidget *widget);
	LIB3270_EXPORT const gchar 			* v3270ft_get_remote_filename(GtkWidget *widget);

	LIB3270_EXPORT void					  v3270ft_append_file(GtkWidget *widget, const gchar *filename, gboolean text);
	LIB3270_EXPORT guint				  v3270ft_append_selection(GtkWidget *widget, GtkSelectionData *data);

	LIB3270_EXPORT gchar				* v3270ft_select_file(v3270ft *dialog, const gchar *title, const gchar *button, GtkFileChooserAction action, const gchar *filename, const gchar *filter, ... ) G_GNUC_NULL_TERMINATED;

	LIB3270_EXPORT gint					  v3270ft_transfer(GtkWidget *dialog, H3270 *session);

	G_END_DECLS

#endif // V3270FT_H_INCLUDED