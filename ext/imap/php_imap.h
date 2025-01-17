/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) The PHP Group                                          |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Rex Logan           <veebert@dimensional.com>               |
   |          Mark Musone         <musone@afterfive.com>                  |
   |          Brian Wang          <brian@vividnet.com>                    |
   |          Kaj-Michael Lang    <milang@tal.org>                        |
   |          Antoni Pamies Olive <toni@readysoft.net>                    |
   |          Rasmus Lerdorf      <rasmus@php.net>                        |
   |          Chuck Hagenbuch     <chuck@horde.org>                       |
   |          Andrew Skalski      <askalski@chekinc.com>                  |
   |          Hartmut Holzgraefe  <hholzgra@php.net>                      |
   |          Jani Taskinen       <sniper@iki.fi>                         |
   |          Daniel R. Kalowsky  <kalowsky@php.net>                      |
   | PHP 4.0 updates:  Zeev Suraski <zeev@php.net>                        |
   +----------------------------------------------------------------------+
 */

#ifndef PHP_IMAP_H
#define PHP_IMAP_H

#if HAVE_IMAP

#if defined(HAVE_IMAP2000) || defined(HAVE_IMAP2001)

 /* For now these appear on Windows, remove this check if it appears outside */
# ifdef PHP_WIN32
 /* Undefine these LOG defines to avoid warnings */
#  undef LOG_EMERG
#  undef LOG_CRIT
#  undef LOG_ERR
#  undef LOG_WARNING
#  undef LOG_NOTICE
#  undef LOG_DEBUG

 /* c-client also redefines its own ftruncate */
#  undef ftruncate
# endif

 /* these are used for quota support */
# include "c-client.h"	/* includes mail.h and rfc822.h */
# include "imap4r1.h"	/* location of c-client quota functions */
#else
# include "mail.h"
# include "rfc822.h"
#endif

extern zend_module_entry imap_module_entry;
#define imap_module_ptr &imap_module_entry

#include "php_version.h"
#define PHP_IMAP_VERSION PHP_VERSION

/* Data types */

#ifdef IMAP41
#define LSIZE text.size
#define LTEXT text.data
#define DTYPE int
#define CONTENT_PART nested.part
#define CONTENT_MSG_BODY nested.msg->body
#define IMAPVER "Imap 4R1"
#else
#define LSIZE size
#define LTEXT text
#define DTYPE char
#define CONTENT_PART contents.part
#define CONTENT_MSG_BODY contents.msg.body
#define IMAPVER "Imap 4"
#endif


/* Determines how mm_list() and mm_lsub() are to return their results. */
typedef enum {
	FLIST_ARRAY,
	FLIST_OBJECT
} folderlist_style_t;

typedef struct php_imap_le_struct {
	MAILSTREAM *imap_stream;
	long flags;
} pils;

typedef struct php_imap_mailbox_struct {
	SIZEDTEXT text;
	DTYPE delimiter;
	long attributes;
	struct php_imap_mailbox_struct *next;
} FOBJECTLIST;

typedef struct php_imap_error_struct {
	SIZEDTEXT text;
	long errflg;
	struct php_imap_error_struct *next;
} ERRORLIST;

typedef struct _php_imap_message_struct {
	unsigned long msgid;
	struct _php_imap_message_struct *next;
} MESSAGELIST;


/* Functions */

PHP_MINIT_FUNCTION(imap);
PHP_RINIT_FUNCTION(imap);
PHP_RSHUTDOWN_FUNCTION(imap);
PHP_MINFO_FUNCTION(imap);

PHP_FUNCTION(imap_open);
PHP_FUNCTION(imap_popen);
PHP_FUNCTION(imap_reopen);
PHP_FUNCTION(imap_num_msg);
PHP_FUNCTION(imap_num_recent);
PHP_FUNCTION(imap_headers);
PHP_FUNCTION(imap_headerinfo);
PHP_FUNCTION(imap_rfc822_parse_headers);
PHP_FUNCTION(imap_body);
PHP_FUNCTION(imap_fetchstructure);
PHP_FUNCTION(imap_fetchbody);
PHP_FUNCTION(imap_fetchmime);
PHP_FUNCTION(imap_savebody);
PHP_FUNCTION(imap_gc);
PHP_FUNCTION(imap_expunge);
PHP_FUNCTION(imap_delete);
PHP_FUNCTION(imap_undelete);
PHP_FUNCTION(imap_check);
PHP_FUNCTION(imap_close);
PHP_FUNCTION(imap_mail_copy);
PHP_FUNCTION(imap_mail_move);
PHP_FUNCTION(imap_createmailbox);
PHP_FUNCTION(imap_renamemailbox);
PHP_FUNCTION(imap_deletemailbox);
PHP_FUNCTION(imap_listmailbox);
PHP_FUNCTION(imap_scanmailbox);
PHP_FUNCTION(imap_subscribe);
PHP_FUNCTION(imap_unsubscribe);
PHP_FUNCTION(imap_append);
PHP_FUNCTION(imap_ping);
PHP_FUNCTION(imap_base64);
PHP_FUNCTION(imap_qprint);
PHP_FUNCTION(imap_8bit);
PHP_FUNCTION(imap_binary);
PHP_FUNCTION(imap_mailboxmsginfo);
PHP_FUNCTION(imap_rfc822_write_address);
PHP_FUNCTION(imap_rfc822_parse_adrlist);
PHP_FUNCTION(imap_setflag_full);
PHP_FUNCTION(imap_clearflag_full);
PHP_FUNCTION(imap_sort);
PHP_FUNCTION(imap_fetchheader);
PHP_FUNCTION(imap_fetchtext);
PHP_FUNCTION(imap_uid);
PHP_FUNCTION(imap_msgno);
PHP_FUNCTION(imap_list);
PHP_FUNCTION(imap_getmailboxes);
PHP_FUNCTION(imap_listscan);
PHP_FUNCTION(imap_lsub);
PHP_FUNCTION(imap_getsubscribed);
PHP_FUNCTION(imap_create);
PHP_FUNCTION(imap_rename);
PHP_FUNCTION(imap_status);
PHP_FUNCTION(imap_bodystruct);
PHP_FUNCTION(imap_fetch_overview);
PHP_FUNCTION(imap_mail_compose);
PHP_FUNCTION(imap_alerts);
PHP_FUNCTION(imap_errors);
PHP_FUNCTION(imap_last_error);
PHP_FUNCTION(imap_mail);
PHP_FUNCTION(imap_search);
PHP_FUNCTION(imap_utf8);
PHP_FUNCTION(imap_utf7_decode);
PHP_FUNCTION(imap_utf7_encode);
#ifdef HAVE_IMAP_MUTF7
PHP_FUNCTION(imap_utf8_to_mutf7);
PHP_FUNCTION(imap_mutf7_to_utf8);
#endif
PHP_FUNCTION(imap_mime_header_decode);
PHP_FUNCTION(imap_thread);
PHP_FUNCTION(imap_timeout);

#if defined(HAVE_IMAP2000) || defined(HAVE_IMAP2001)
PHP_FUNCTION(imap_get_quota);
PHP_FUNCTION(imap_get_quotaroot);
PHP_FUNCTION(imap_set_quota);
PHP_FUNCTION(imap_setacl);
PHP_FUNCTION(imap_getacl);
#endif


ZEND_BEGIN_MODULE_GLOBALS(imap)
	char *imap_user;
	char *imap_password;

	STRINGLIST *imap_alertstack;
	ERRORLIST *imap_errorstack;

	STRINGLIST *imap_folders;
	STRINGLIST *imap_folders_tail;
	STRINGLIST *imap_sfolders;
	STRINGLIST *imap_sfolders_tail;
	MESSAGELIST *imap_messages;
	MESSAGELIST *imap_messages_tail;
	FOBJECTLIST *imap_folder_objects;
	FOBJECTLIST *imap_folder_objects_tail;
	FOBJECTLIST *imap_sfolder_objects;
	FOBJECTLIST *imap_sfolder_objects_tail;

	folderlist_style_t folderlist_style;
	long status_flags;
	unsigned long status_messages;
	unsigned long status_recent;
	unsigned long status_unseen;
	unsigned long status_uidnext;
	unsigned long status_uidvalidity;
#if defined(HAVE_IMAP2000) || defined(HAVE_IMAP2001)
	zval **quota_return;
	zval *imap_acl_list;
#endif
	/* php_stream for php_mail_gets() */
	php_stream *gets_stream;
	zend_bool enable_rsh;
ZEND_END_MODULE_GLOBALS(imap)

#if defined(ZTS) && defined(COMPILE_DL_IMAP)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

ZEND_EXTERN_MODULE_GLOBALS(imap)
#define IMAPG(v) ZEND_MODULE_GLOBALS_ACCESSOR(imap, v)

#else

#define imap_module_ptr NULL

#endif

#define phpext_imap_ptr imap_module_ptr

#endif /* PHP_IMAP_H */
