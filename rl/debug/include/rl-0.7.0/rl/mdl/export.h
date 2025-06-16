
#ifndef RL_MDL_EXPORT_H
#define RL_MDL_EXPORT_H

#ifdef RL_MDL_STATIC_DEFINE
#  define RL_MDL_EXPORT
#  define RL_MDL_NO_EXPORT
#else
#  ifndef RL_MDL_EXPORT
#    ifdef mdl_EXPORTS
        /* We are building this library */
#      define RL_MDL_EXPORT 
#    else
        /* We are using this library */
#      define RL_MDL_EXPORT 
#    endif
#  endif

#  ifndef RL_MDL_NO_EXPORT
#    define RL_MDL_NO_EXPORT 
#  endif
#endif

#ifndef RL_MDL_DEPRECATED
#  define RL_MDL_DEPRECATED __declspec(deprecated)
#endif

#ifndef RL_MDL_DEPRECATED_EXPORT
#  define RL_MDL_DEPRECATED_EXPORT RL_MDL_EXPORT RL_MDL_DEPRECATED
#endif

#ifndef RL_MDL_DEPRECATED_NO_EXPORT
#  define RL_MDL_DEPRECATED_NO_EXPORT RL_MDL_NO_EXPORT RL_MDL_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef RL_MDL_NO_DEPRECATED
#    define RL_MDL_NO_DEPRECATED
#  endif
#endif

#endif /* RL_MDL_EXPORT_H */
