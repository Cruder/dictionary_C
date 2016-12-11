#ifndef VERSION_H_INCLUDED
#define VERSION_H_INCLUDED

#include <stdint.h>

/**
 *  \brief Information the version in use.
 *
 *  Represents the library's version as three levels: major revision
 *  (increments with massive changes, additions, and enhancements),
 *  minor revision (increments with backwards-compatible changes to the
 *  major revision), and patchlevel (increments with fixes to the minor
 *  revision).
 */
typedef struct Version {
    uint8_t major, minor, patch;
} Version;

/**
 *  \brief Information the version of AccelLib in use.
 *
 *  Represents the library's version as three levels: major revision
 *  (increments with massive changes, additions, and enhancements),
 *  minor revision (increments with backwards-compatible changes to the
 *  major revision), and patchlevel (increments with fixes to the minor
 *  revision).
 *
 *  \sa ACCELLIB_VERSION
 *  \sa AccelLib_GetVersion
 */
typedef Version AccelLib_version;

/* Printable format: "%d.%d.%d", MAJOR, MINOR, PATCHLEVEL
*/
#define ACCELLIB_MAJOR_VERSION   0
#define ACCELLIB_MINOR_VERSION   0
#define ACCELLIB_PATCHLEVEL      2

#define ACCELLIB_REVISION "git-0022:000029879485EN"
#define ACCELLIB_REVISION_NUMBER 0022


/**
 *  \brief Macro to determine AccelLib version program was compiled against.
 *
 *  This macro fills in a SDL_version structure with the version of the
 *  library you compiled against. This is determined by what header the
 *  compiler uses. Note that if you dynamically linked the library, you might
 *  have a slightly newer or older version at runtime. That version can be
 *  determined with AccelLib_GetVersion(), which, unlike ACCELLIB_VERSION(),
 *  is not a macro.
 *
 *  \param x A pointer to a AccelLib_version struct to initialize.
 *
 *  \sa AccelLib_version
 *  \sa AccelLib_GetVersion
 */
#define ACCELLIB_VERSION(x)              \
{                                        \
    (x)->major = ACCELLIB_MAJOR_VERSION; \
    (x)->minor = ACCELLIB_MINOR_VERSION; \
    (x)->patch = ACCELLIB_PATCHLEVEL;    \
}


/**
 *  \brief Get the version of AccelLib that is linked against your program.
 *
 *  If you are linking to AccelLib dynamically, then it is possible that the
 *  current version will be different than the version you compiled against.
 *  This function returns the current version, while ACCELLIB_VERSION() is a
 *  macro that tells you what version you compiled with.
 *
 *  \code
 *  AccelLib_version compiled;
 *  AccelLib_version linked;
 *
 *  ACCELLIB_VERSION(&compiled);
 *  AccelLib_GetVersion(&linked);
 *  printf("We compiled against AccelLib version %d.%d.%d ...\n",
 *         compiled.major, compiled.minor, compiled.patch);
 *  printf("But we linked against AccelLib version %d.%d.%d.\n",
 *         linked.major, linked.minor, linked.patch);
 *  \endcode
 *
 *  \sa ACCELLIB_VERSION
 */
void AccelLib_GetVersion(AccelLib_version *ver);

/**
 *  \brief Get the code revision of AccelLib that is linked against your program.
 *
 *  Returns an arbitrary string (a hash value) uniquely identifying the
 *  exact revision of the AccelLib library in use, and is only useful in comparing
 *  against other revisions. It is NOT an incrementing number.
 */
const char* AccelLib_GetRevision(/*void*/);

/**
 *  \brief Get the revision number of AccelLib that is linked against your program.
 *
 *  Returns a number uniquely identifying the exact revision of the AccelLib
 *  library in use. It is an incrementing number based on commits to
 *  gtihub.org.
 */
int AccelLib_GetRevisionNumber(/*void*/);


/**
 *  This macro turns the version numbers into a numeric value:
 *  \verbatim
    (1,2,3) -> (1203)
    \endverbatim
 *
 *  This assumes that there will never be more than 100 patchlevels.
 */
#define ACCELLIB_VERSIONNUM(X, Y, Z) ((X)*1000 + (Y)*100 + (Z))

/**
 *  This is the version number macro for the current AccelLib version.
 */
#define ACCELLIB_COMPILEDVERSION ACCELLIB_VERSIONNUM(LIB_MAJOR_VERSION, LIB_MINOR_VERSION, LIB_PATCHLEVEL)

/**
 *  This macro will evaluate to true if compiled with AccelLib at least X.Y.Z.
 */
#define ACCELLIB_VERSION_ATLEAST(X, Y, Z) (ACCELLIB_COMPILEDVERSION >= ACCELLIB_VERSIONNUM(X, Y, Z))


#endif // VERSION_H_INCLUDED
