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

 #include <config.h>

 #pragma GCC diagnostic ignored "-Wdeprecated-declarations"

 #define ENABLE_NLS
 #define GETTEXT_PACKAGE PACKAGE_NAME

 #include <gtk/gtk.h>
 #include <libintl.h>
 #include <glib/gi18n.h>

 #include "private.h"

 #if defined(HAVE_LIBSSL)
	#include <openssl/ssl.h>
	#include <openssl/err.h>
 #endif


/*--[ Globals ]--------------------------------------------------------------------------------------*/

#if defined(HAVE_LIBSSL)
 static const struct v3270_ssl_status_msg ssl_status_msg[] =
 {
	// http://www.openssl.org/docs/apps/verify.html
	{
		X509_V_OK,
		GTK_STOCK_DIALOG_AUTHENTICATION,
		N_( "Secure connection was successful." ),
		N_( "The connection is secure and the host identity was confirmed." )
	},

	{
		X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Unable to get issuer certificate" ),
		N_( "The issuer certificate of a looked up certificate could not be found. This normally means the list of trusted certificates is not complete." ),
	},

	{
		X509_V_ERR_UNABLE_TO_GET_CRL,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Unable to get certificate CRL" ),
		N_( "The CRL of a certificate could not be found." ),
	},

	{
		X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Unable to decrypt certificate's signature" ),
		N_( "The certificate signature could not be decrypted. This means that the actual signature value could not be determined rather than it not matching the expected value, this is only meaningful for RSA keys." ),
	},

	{
		X509_V_ERR_UNABLE_TO_DECRYPT_CRL_SIGNATURE,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Unable to decrypt CRL's signature" ),
		N_( "The CRL signature could not be decrypted: this means that the actual signature value could not be determined rather than it not matching the expected value. Unused." ),
	},

	{
		X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Unable to decode issuer public key" ),
		N_( "The public key in the certificate SubjectPublicKeyInfo could not be read." ),
	},

	{
		X509_V_ERR_CERT_SIGNATURE_FAILURE,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Certificate signature failure" ),
		N_( "The signature of the certificate is invalid." ),
	},

	{
		X509_V_ERR_CRL_SIGNATURE_FAILURE,
		GTK_STOCK_DIALOG_ERROR,
		N_( "CRL signature failure" ),
		N_( "The signature of the certificate is invalid." ),
	},

	{
		X509_V_ERR_CERT_NOT_YET_VALID,
		GTK_STOCK_DIALOG_WARNING,
		N_( "Certificate is not yet valid" ),
		N_( "The certificate is not yet valid: the notBefore date is after the current time." ),
	},

	{
		X509_V_ERR_CERT_HAS_EXPIRED,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Certificate has expired" ),
		N_( "The certificate has expired: that is the notAfter date is before the current time." ),
	},

	{
		X509_V_ERR_CRL_NOT_YET_VALID,
		GTK_STOCK_DIALOG_WARNING,
		N_( "CRL is not yet valid" ),
		N_( "The CRL is not yet valid." ),
	},

	{
		X509_V_ERR_CRL_HAS_EXPIRED,
		GTK_STOCK_DIALOG_ERROR,
		N_( "CRL has expired" ),
		N_( "The CRL has expired." ),
	},

	{
		X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Format error in certificate's notBefore field" ),
		N_( "The certificate notBefore field contains an invalid time." ),
	},

	{
		X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Format error in certificate's notAfter field" ),
		N_( "The certificate notAfter field contains an invalid time." ),
	},

	{
		X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Format error in CRL's lastUpdate field" ),
		N_( "The CRL lastUpdate field contains an invalid time." ),
	},

	{
		X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Format error in CRL's nextUpdate field" ),
		N_( "The CRL nextUpdate field contains an invalid time." ),
	},

	{
		X509_V_ERR_OUT_OF_MEM,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Out of memory" ),
		N_( "An error occurred trying to allocate memory. This should never happen." ),
	},

	{
		X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT,
		GTK_STOCK_DIALOG_WARNING,
		N_( "Self signed certificate" ),
		N_( "The passed certificate is self signed and the same certificate cannot be found in the list of trusted certificates." ),
	},

	{
		X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN,
		GTK_STOCK_DIALOG_WARNING,
		N_( "Self signed certificate in certificate chain" ),
		N_( "The certificate chain could be built up using the untrusted certificates but the root could not be found locally." ),
	},

	{
		X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY,
		GTK_STOCK_DIALOG_WARNING,
		N_( "Unable to get local issuer certificate" ),
		N_( "The issuer certificate could not be found: this occurs if the issuer certificate of an untrusted certificate cannot be found." ),
	},

	{
		X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Unable to verify the first certificate" ),
		N_( "No signatures could be verified because the chain contains only one certificate and it is not self signed." ),
	},

	{
		X509_V_ERR_CERT_REVOKED,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Certificate revoked" ),
		N_( "The certificate has been revoked." ),
	},

	{
		X509_V_ERR_INVALID_CA,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Invalid CA certificate" ),
		N_( "A CA certificate is invalid. Either it is not a CA or its extensions are not consistent with the supplied purpose." ),
	},

	{
		X509_V_ERR_PATH_LENGTH_EXCEEDED,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Path length constraint exceeded" ),
		N_( "The basicConstraints pathlength parameter has been exceeded." ),
	},

	{
		X509_V_ERR_INVALID_PURPOSE,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Unsupported certificate purpose" ),
		N_( "The supplied certificate cannot be used for the specified purpose." ),
	},

	{
		X509_V_ERR_CERT_UNTRUSTED,
		GTK_STOCK_DIALOG_WARNING,
		N_( "Certificate not trusted" ),
		N_( "The root CA is not marked as trusted for the specified purpose." ),
	},

	{
		X509_V_ERR_CERT_REJECTED,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Certificate rejected" ),
		N_( "The root CA is marked to reject the specified purpose." ),
	},

	{
		X509_V_ERR_SUBJECT_ISSUER_MISMATCH,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Subject issuer mismatch" ),
		N_( "The current candidate issuer certificate was rejected because its subject name did not match the issuer name of the current certificate. Only displayed when the -issuer_checks option is set." ),
	},

	{
		X509_V_ERR_AKID_SKID_MISMATCH,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Authority and subject key identifier mismatch" ),
		N_( "The current candidate issuer certificate was rejected because its subject key identifier was present and did not match the authority key identifier current certificate. Only displayed when the -issuer_checks option is set." ),
	},

	{
		X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Authority and issuer serial number mismatch" ),
		N_( "The current candidate issuer certificate was rejected because its issuer name and serial number was present and did not match the authority key identifier of the current certificate. Only displayed when the -issuer_checks option is set." ),
	},

	{
		X509_V_ERR_KEYUSAGE_NO_CERTSIGN,
		GTK_STOCK_DIALOG_ERROR,
		N_( "Key usage does not include certificate signing" ),
		N_( "The current candidate issuer certificate was rejected because its keyUsage extension does not permit certificate signing." ),
	},

	{
		0,
		NULL,
		NULL,
		NULL
	}

 };
#endif // HAVE_LIBSSL

/*--[ Implement ]------------------------------------------------------------------------------------*/

 G_GNUC_INTERNAL const struct v3270_ssl_status_msg * v3270_get_ssl_status_msg(G_GNUC_UNUSED GtkWidget *widget)
 {
#ifdef HAVE_LIBSSL
	int 	f;
	long 	id		= lib3270_get_SSL_verify_result(GTK_V3270(widget)->host);

	for(f=0;ssl_status_msg[f].text;f++)
	{
		if(ssl_status_msg[f].id == id)
			return ssl_status_msg+f;
	}
#endif // HAVE_LIBSSL
	return NULL;
 }

 const gchar * v3270_get_ssl_status_icon(GtkWidget *widget)
 {
 	g_return_val_if_fail(GTK_IS_V3270(widget),"");

	if(lib3270_get_secure(GTK_V3270(widget)->host) == LIB3270_SSL_UNSECURE)
		return GTK_STOCK_DIALOG_INFO;


#ifdef HAVE_LIBSSL
	if(lib3270_get_secure(GTK_V3270(widget)->host) != LIB3270_SSL_UNSECURE)
	{
		const struct v3270_ssl_status_msg *info = v3270_get_ssl_status_msg(widget);
		if(info)
			return info->icon;
	}
#endif // HAVE_LIBSSL

	return GTK_STOCK_DIALOG_ERROR;

 }

 const gchar	* v3270_get_ssl_status_text(GtkWidget *widget)
 {
 	g_return_val_if_fail(GTK_IS_V3270(widget),"");

	if(lib3270_get_secure(GTK_V3270(widget)->host) == LIB3270_SSL_UNSECURE)
		return v3270_get_hostname(widget);

#ifdef HAVE_LIBSSL
	if(lib3270_get_secure(GTK_V3270(widget)->host) != LIB3270_SSL_UNSECURE)
	{
		const struct v3270_ssl_status_msg *info = v3270_get_ssl_status_msg(widget);
		if(info)
			return gettext(info->text);
	}
#endif // HAVE_LIBSSL
	return v3270_get_hostname(widget);
 }

 const gchar * v3270_get_ssl_status_message(GtkWidget *widget)
 {
 	g_return_val_if_fail(GTK_IS_V3270(widget),"");

	if(lib3270_get_secure(GTK_V3270(widget)->host) == LIB3270_SSL_UNSECURE)
		return _( "The connection is insecure" );

#ifdef HAVE_LIBSSL
	if(lib3270_get_secure(GTK_V3270(widget)->host) != LIB3270_SSL_UNSECURE)
	{
		const struct v3270_ssl_status_msg *info = v3270_get_ssl_status_msg(widget);
		if(info)
			return gettext(info->message);
	}
#endif // HAVE_LIBSSL

	return _( "Unexpected or unknown security status");
 }

