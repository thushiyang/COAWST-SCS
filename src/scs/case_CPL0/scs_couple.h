#define ROMS_MODEL
#undef  NESTING
#undef WRF_MODEL
#define SWAN_MODEL
#undef  WW3_MODEL
#define MCT_LIB
#undef MCT_INTERP_OC2AT
#undef MCT_INTERP_WV2AT
#undef MCT_INTERP_OC2WV /* roms and swan in same grid */


#ifdef ROMS_MODEL
/* Physics + numerics, FOCUS terms*/
# if defined WW3_MODEL || defined SWAN_MODEL
#  define WEC_VF              /*Control test, kvrf+hjvf, vortex force*/
#  undef WEC_MELLOR           /*Control test, incompatible with WEC_VF*/

#  define WAVE_MIXING         /*Control test, CHECK, Wave-enhanced vertical viscosity mixing TKE*/

#  define WDISS_WAVEMOD       /*Control test, Wcap, part of Wave-enhanced vertical mixing TKE, also fwav*/
#  undef WDISS_CHURTHOR       /*Control test, incompatible with WAVEMOD*/

#  define ROLLER_RENIERS       /*Control test, Br, part of Wave-enhanced vertical mixing TKE, also fwav*/
#  undef ROLLER_SVENDSEN       /*Control test, incompatible with RENIERS, roms_in cant output rollA*/

#  define BOTTOM_STREAMING    /*Control test, Sstr, surface stress, also non-conservative fwav*/
#  define SURFACE_STREAMING   /*Control test, Bstr, bottom stress, also non-conservative fwav*/

#  define UV_KIRBY            /*Control test*/
#  undef UV_CONST             /*Control test, incompatible with UV_KIRBY*/

#  undef ZETA_CONST           /*Control test*/
#  undef SST_CONST            /*Control test*/

# endif

/* Momentum terms */
# define UV_ADV               /*Control test, hadv, horizontal advection*/
# define CURVGRID             /*Compute extra non-linear advection terms for curvilinear coordinates*/
# define UV_COR               /*Control test, cor, Coriolis force */
# define UV_VIS2              /*Control test, hvisc, horizontal viscosity */
# define DJ_GRADPS            /*Control test, prsgrd, pressure gradient */
# define TS_DIF2              /*Define just for tracers*/ 

/* Horizontal mixing*/
# define MIX_S_UV             /*Control test, Horizontal mixing of momentum, viscosity along s surfaces*/
# define MIX_GEO_TS           /*Define just for tracers*/     

/* Vertical mixing, Turbulence closure*/
# define GLS_MIXING           /*Control test*/
# undef MY25_MIXING
# define LIMIT_VDIFF
# define LIMIT_VVISC
# if defined GLS_MIXING || defined MY25_MIXING
#  define KANTHA_CLAYSON
#  define N2S2_HORAVG
#  define RI_SPLINES
#  define CRAIG_BANNER       /*Define Craig and Banner wave breaking surface flux*/ 
#  undef CHARNOK            /*Define Charnok surface roughness from wind stress*/

#  define ZOS_HSIG            /*CHECK ADD, surface roughness from wave amplitude, incompatible with CHARNOK*/
#  define TKE_WAVEDISS       /*Control test, CHECK ADD, TKE, wave breaking surface flux from wave amplitude*/
# endif

/* Wave roughness in bulk fluxes, SWAN to ROMS for computing ocean surface stress*/
#if defined WRF_MODEL && (defined SWAN_MODEL || defined WW3_MODEL)
# define DRAGLIM_DAVIS          /*Define Drag limiter option*/
# define COARE_TAYLOR_YELLAND   /*Control test, WRough, Wave-enhanced surface roughness*/
# undef COARE_OOST              /*Control test, incompatible with TAYLOR_YELLAND */
# undef DRENNAN                 /*Control test, incompatible with TAYLOR_YELLAND */
#endif

/* Bottom boundary layer */
# define SSW_BBL               /*Control test, Wave-enhanced bottom stress */
# ifdef SSW_BBL
#  define SSW_CALC_ZNOT
#  define ANA_SEDIMENT
# else
#  define UV_LOGDRAG
# endif

# if !defined SWAN_MODEL && defined SSW_BBL
#  define ANA_WWAVE          /*Define analytical wind induced waves*/
# endif

/* Atmospheric Forcing */
# ifdef WRF_MODEL
#  undef  BULK_FLUXES
#  define ATM2OCN_FLUXES
#  undef  ANA_SSFLUX
#  undef  LONGWAVE_OUT
# else
#  define BULK_FLUXES
# endif
# define ANA_NUDGCOEF
# define ATM_PRESS          /*Define atmospheric pressure onto sea surface, ALSO pressure gradient*/
# define ANA_BTFLUX
# define ANA_BSFLUX
# define ANA_BPFLUX
# define ANA_SPFLUX
# define ANA_SRFLUX
# define EMINUSP
# define SOLAR_SOURCE

/* Tide Forcing */    
# define SSH_TIDES       /*Control test, Define if imposing tidal elevation*/
# define UV_TIDES        /*Control test, Define if imposing tidal currents*/
# define TIDE_GENERATING_FORCES  /*Control test, CHECK ADD*/
# define RAMP_TIDES
# define ADD_FSOBC
# define ADD_M2OBC


/* General Options */
# define SOLVE3D
# define MASKING        
# define RADIATION_2D
# define WET_DRY

/* Tracersr */
# define SALINITY
# define SPLINES_VDIFF
# define SPLINES_VVISC
# define NONLIN_EOS
# undef QCORRECTION
# undef SCORRECTION
# undef TS_FIXED

/* Output */
# define AVERAGES
# define DIAGNOSTICS_UV
# define DIAGNOSTICS_TS
# undef PERFECT_RESTART
# undef RST_SINGLE
# define STATIONS
#endif
