
#ifndef MEDIAWIKI_EXPORT_H
#define MEDIAWIKI_EXPORT_H

#ifdef MEDIAWIKI_STATIC_DEFINE
#  define MEDIAWIKI_EXPORT
#  define MEDIAWIKI_NO_EXPORT
#else
#  ifndef MEDIAWIKI_EXPORT
#    ifdef KF5MediaWiki_EXPORTS
        /* We are building this library */
#      define MEDIAWIKI_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define MEDIAWIKI_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef MEDIAWIKI_NO_EXPORT
#    define MEDIAWIKI_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef MEDIAWIKI_DEPRECATED
#  define MEDIAWIKI_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef MEDIAWIKI_DEPRECATED_EXPORT
#  define MEDIAWIKI_DEPRECATED_EXPORT MEDIAWIKI_EXPORT MEDIAWIKI_DEPRECATED
#endif

#ifndef MEDIAWIKI_DEPRECATED_NO_EXPORT
#  define MEDIAWIKI_DEPRECATED_NO_EXPORT MEDIAWIKI_NO_EXPORT MEDIAWIKI_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MEDIAWIKI_NO_DEPRECATED
#    define MEDIAWIKI_NO_DEPRECATED
#  endif
#endif

#endif
