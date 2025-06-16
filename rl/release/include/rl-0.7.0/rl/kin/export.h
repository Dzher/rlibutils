
#ifndef RL_KIN_EXPORT_H
#define RL_KIN_EXPORT_H

#ifdef RL_KIN_STATIC_DEFINE
#  define RL_KIN_EXPORT
#  define RL_KIN_NO_EXPORT
#else
#  ifndef RL_KIN_EXPORT
#    ifdef kin_EXPORTS
        /* We are building this library */
#      define RL_KIN_EXPORT 
#    else
        /* We are using this library */
#      define RL_KIN_EXPORT 
#    endif
#  endif

#  ifndef RL_KIN_NO_EXPORT
#    define RL_KIN_NO_EXPORT 
#  endif
#endif

#ifndef RL_KIN_DEPRECATED
#  define RL_KIN_DEPRECATED __declspec(deprecated)
#endif

#ifndef RL_KIN_DEPRECATED_EXPORT
#  define RL_KIN_DEPRECATED_EXPORT RL_KIN_EXPORT RL_KIN_DEPRECATED
#endif

#ifndef RL_KIN_DEPRECATED_NO_EXPORT
#  define RL_KIN_DEPRECATED_NO_EXPORT RL_KIN_NO_EXPORT RL_KIN_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef RL_KIN_NO_DEPRECATED
#    define RL_KIN_NO_DEPRECATED
#  endif
#endif

#endif /* RL_KIN_EXPORT_H */
