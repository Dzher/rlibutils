
#ifndef RL_SG_EXPORT_H
#define RL_SG_EXPORT_H

#ifdef RL_SG_STATIC_DEFINE
#  define RL_SG_EXPORT
#  define RL_SG_NO_EXPORT
#else
#  ifndef RL_SG_EXPORT
#    ifdef sg_EXPORTS
        /* We are building this library */
#      define RL_SG_EXPORT 
#    else
        /* We are using this library */
#      define RL_SG_EXPORT 
#    endif
#  endif

#  ifndef RL_SG_NO_EXPORT
#    define RL_SG_NO_EXPORT 
#  endif
#endif

#ifndef RL_SG_DEPRECATED
#  define RL_SG_DEPRECATED __declspec(deprecated)
#endif

#ifndef RL_SG_DEPRECATED_EXPORT
#  define RL_SG_DEPRECATED_EXPORT RL_SG_EXPORT RL_SG_DEPRECATED
#endif

#ifndef RL_SG_DEPRECATED_NO_EXPORT
#  define RL_SG_DEPRECATED_NO_EXPORT RL_SG_NO_EXPORT RL_SG_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef RL_SG_NO_DEPRECATED
#    define RL_SG_NO_DEPRECATED
#  endif
#endif

#endif /* RL_SG_EXPORT_H */
