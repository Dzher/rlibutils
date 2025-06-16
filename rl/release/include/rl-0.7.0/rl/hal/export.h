
#ifndef RL_HAL_EXPORT_H
#define RL_HAL_EXPORT_H

#ifdef RL_HAL_STATIC_DEFINE
#  define RL_HAL_EXPORT
#  define RL_HAL_NO_EXPORT
#else
#  ifndef RL_HAL_EXPORT
#    ifdef hal_EXPORTS
        /* We are building this library */
#      define RL_HAL_EXPORT 
#    else
        /* We are using this library */
#      define RL_HAL_EXPORT 
#    endif
#  endif

#  ifndef RL_HAL_NO_EXPORT
#    define RL_HAL_NO_EXPORT 
#  endif
#endif

#ifndef RL_HAL_DEPRECATED
#  define RL_HAL_DEPRECATED __declspec(deprecated)
#endif

#ifndef RL_HAL_DEPRECATED_EXPORT
#  define RL_HAL_DEPRECATED_EXPORT RL_HAL_EXPORT RL_HAL_DEPRECATED
#endif

#ifndef RL_HAL_DEPRECATED_NO_EXPORT
#  define RL_HAL_DEPRECATED_NO_EXPORT RL_HAL_NO_EXPORT RL_HAL_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef RL_HAL_NO_DEPRECATED
#    define RL_HAL_NO_DEPRECATED
#  endif
#endif

#endif /* RL_HAL_EXPORT_H */
