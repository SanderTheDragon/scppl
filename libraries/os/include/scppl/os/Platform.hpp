// SPDX-FileCopyrightText: 2021-2022 SanderTheDragon <sanderthedragon@zoho.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

/**
 * @file Platform.hpp
 *
 * @brief Platform identification constants, based on the data from
 *        https://sourceforge.net/p/predef/wiki.
 *
 * @warning This file is generated by "generate_platorm.py" and may contain
 *          slightly wrong or outdated data. Any edits to this file could be
 *          overwritten.
 *
 * @note This file was generated on 2022-04-07 11:09:40.353312.
 */

#ifndef SCPPL_OS_PLATFORM_HPP_
#define SCPPL_OS_PLATFORM_HPP_

namespace scppl {

/**
 * @page OS Operating Systems
 *
 * The following operating systems are defined along with their name in
 * `SCPPL_OS_NAME`.
 *
 * - `SCPPL_OS_AIX` for "AIX".
 * - `SCPPL_OS_ANDROID` for "Android".
 * - `SCPPL_OS_AMDAHL_UTS` for "Amdahl UTS".
 * - `SCPPL_OS_AMIGAOS` for "AmigaOS".
 * - `SCPPL_OS_APOLLO_AEGIS` for "Apollo AEGIS".
 * - `SCPPL_OS_APOLLO_DOMAINOS` for "Apollo Domain/OS".
 * - `SCPPL_OS_BEOS` for "BeOS".
 * - `SCPPL_OS_BLUE_GENE` for "Blue Gene".
 * - `SCPPL_OS_BSDOS` for "BSD/OS".
 * - `SCPPL_OS_CONVEXOS` for "ConvexOS".
 * - `SCPPL_OS_CYGWIN` for "Cygwin Environment".
 * - `SCPPL_OS_DGUX` for "DG/UX".
 * - `SCPPL_OS_DRAGONFLY` for "DragonFly".
 * - `SCPPL_OS_DYNIXPTX` for "DYNIX/ptx".
 * - `SCPPL_OS_ECOS` for "eCos".
 * - `SCPPL_OS_EMX_ENVIRONMENT` for "EMX Environment".
 * - `SCPPL_OS_FREEBSD` for "FreeBSD".
 * - `SCPPL_OS_GNUHURD` for "GNU/Hurd".
 * - `SCPPL_OS_GNUKFREEBSD` for "GNU/kFreeBSD".
 * - `SCPPL_OS_GNULINUX` for "GNU/Linux".
 * - `SCPPL_OS_HI_UX_MPP` for "HI-UX MPP".
 * - `SCPPL_OS_HP_UX` for "HP-UX".
 * - `SCPPL_OS_IBM_OS400` for "IBM OS/400".
 * - `SCPPL_OS_INTEGRITY` for "INTEGRITY".
 * - `SCPPL_OS_INTERIX_ENVIRONMENT` for "Interix Environment".
 * - `SCPPL_OS_IRIX` for "IRIX".
 * - `SCPPL_OS_LINUX_KERNEL` for "Linux kernel".
 * - `SCPPL_OS_LYNXOS` for "LynxOS".
 * - `SCPPL_OS_MACOS` for "MacOS".
 * - `SCPPL_OS_MICROWARE_OS_9` for "Microware OS-9".
 * - `SCPPL_OS_MINIX` for "MINIX".
 * - `SCPPL_OS_MORPHOS` for "MorphOS".
 * - `SCPPL_OS_MPEIX` for "MPE/iX".
 * - `SCPPL_OS_MSDOS` for "MSDOS".
 * - `SCPPL_OS_NETBSD` for "NetBSD".
 * - `SCPPL_OS_NONSTOP` for "NonStop".
 * - `SCPPL_OS_NUCLEUS_RTOS` for "Nucleus RTOS".
 * - `SCPPL_OS_OPENBSD` for "OpenBSD".
 * - `SCPPL_OS_OS2` for "OS/2".
 * - `SCPPL_OS_PALM_OS` for "Palm OS".
 * - `SCPPL_OS_PLAN_9` for "Plan 9".
 * - `SCPPL_OS_PYRAMID_DCOSX` for "Pyramid DC/OSx".
 * - `SCPPL_OS_QNX` for "QNX".
 * - `SCPPL_OS_RELIANT_UNIX` for "Reliant UNIX".
 * - `SCPPL_OS_SCO_OPENSERVER` for "SCO OpenServer".
 * - `SCPPL_OS_SOLARIS` for "Solaris".
 * - `SCPPL_OS_STRATUS_VOS` for "Stratus VOS".
 * - `SCPPL_OS_SVR4_ENVIRONMENT` for "SVR4 Environment".
 * - `SCPPL_OS_SYLLABLE` for "Syllable".
 * - `SCPPL_OS_SYMBIAN_OS` for "Symbian OS".
 * - `SCPPL_OS_TRU64_OSF1` for "Tru64 (OSF/1)".
 * - `SCPPL_OS_ULTRIX` for "Ultrix".
 * - `SCPPL_OS_UNICOS` for "UNICOS".
 * - `SCPPL_OS_UNICOSMP` for "UNICOS/mp".
 * - `SCPPL_OS_UNIX_ENVIRONMENT` for "UNIX Environment".
 * - `SCPPL_OS_UNIXWARE` for "UnixWare".
 * - `SCPPL_OS_UWIN_ENVIRONMENT` for "U/Win Environment".
 * - `SCPPL_OS_VMS` for "VMS".
 * - `SCPPL_OS_VXWORKS` for "VxWorks".
 * - `SCPPL_OS_WINDOWS` for "Windows".
 * - `SCPPL_OS_WINDOWS_CE` for "Windows CE".
 * - `SCPPL_OS_WINDU_ENVIRONMENT` for "Wind/U Environment".
 * - `SCPPL_OS_ZOS` for "z/OS".
 *
 * If there is no match, `SCPPL_OS_UNKNOWN` is defined, with the name
 * "Unknown".
 *
 * Operating systems based on another will define a base macro as well, since
 * this is done manually, it may be out of date if the source documentation is
 * updated.
 *
 * The following base macros can be defined:
 *
 * - `SCPPL_OS_UNIX` for UNIX.
 * - `SCPPL_OS_LINUX` for Linux (also defines `SCPPL_OS_UNIX`).
 * - `SCPPL_OS_BSD` for BSD (also defines `SCPPL_OS_UNIX`).
 */

/// @cond

// NOLINTBEGIN(cppcoreguidelines-macro-usage): Allow macro definitions
#if defined(_AIX) || \
    defined(__TOS_AIX__)
#define SCPPL_OS_AIX
#define SCPPL_OS_NAME "AIX"
#elif defined(__ANDROID__)
#define SCPPL_OS_ANDROID
#define SCPPL_OS_UNIX
#define SCPPL_OS_NAME "Android"
#elif defined(UTS)
#define SCPPL_OS_AMDAHL_UTS
#define SCPPL_OS_NAME "Amdahl UTS"
#elif defined(AMIGA) || \
      defined(__amigaos__)
#define SCPPL_OS_AMIGAOS
#define SCPPL_OS_NAME "AmigaOS"
#elif defined(aegis)
#define SCPPL_OS_APOLLO_AEGIS
#define SCPPL_OS_NAME "Apollo AEGIS"
#elif defined(apollo)
#define SCPPL_OS_APOLLO_DOMAINOS
#define SCPPL_OS_NAME "Apollo Domain/OS"
#elif defined(__BEOS__)
#define SCPPL_OS_BEOS
#define SCPPL_OS_NAME "BeOS"
#elif defined(__bg__) || \
      defined(__THW_BLUEGENE__)
#define SCPPL_OS_BLUE_GENE
#define SCPPL_OS_NAME "Blue Gene"
#elif defined(__bsdi__)
#define SCPPL_OS_BSDOS
#define SCPPL_OS_NAME "BSD/OS"
#elif defined(__convex__)
#define SCPPL_OS_CONVEXOS
#define SCPPL_OS_NAME "ConvexOS"
#elif defined(__CYGWIN__)
#define SCPPL_OS_CYGWIN
#define SCPPL_OS_UNIX
#define SCPPL_OS_NAME "Cygwin Environment"
#elif defined(DGUX) || \
      defined(__DGUX__) || \
      defined(__dgux__)
#define SCPPL_OS_DGUX
#define SCPPL_OS_NAME "DG/UX"
#elif defined(__DragonFly__)
#define SCPPL_OS_DRAGONFLY
#define SCPPL_OS_BSD
#define SCPPL_OS_UNIX
#define SCPPL_OS_NAME "DragonFly"
#elif defined(_SEQUENT_) || \
      defined(sequent)
#define SCPPL_OS_DYNIXPTX
#define SCPPL_OS_NAME "DYNIX/ptx"
#elif defined(__ECOS)
#define SCPPL_OS_ECOS
#define SCPPL_OS_NAME "eCos"
#elif defined(__EMX__)
#define SCPPL_OS_EMX_ENVIRONMENT
#define SCPPL_OS_NAME "EMX Environment"
#elif defined(__FreeBSD__) || \
      defined(__FreeBSD_kernel__)
#define SCPPL_OS_FREEBSD
#define SCPPL_OS_BSD
#define SCPPL_OS_UNIX
#define SCPPL_OS_NAME "FreeBSD"
#elif defined(__GNU__) || \
      defined(__gnu_hurd__)
#define SCPPL_OS_GNUHURD
#define SCPPL_OS_UNIX
#define SCPPL_OS_NAME "GNU/Hurd"
#elif (defined(__FreeBSD_kernel__) && defined(__GLIBC__))
#define SCPPL_OS_GNUKFREEBSD
#define SCPPL_OS_BSD
#define SCPPL_OS_UNIX
#define SCPPL_OS_NAME "GNU/kFreeBSD"
#elif defined(__gnu_linux__)
#define SCPPL_OS_GNULINUX
#define SCPPL_OS_LINUX
#define SCPPL_OS_UNIX
#define SCPPL_OS_NAME "GNU/Linux"
#elif defined(__hiuxmpp)
#define SCPPL_OS_HI_UX_MPP
#define SCPPL_OS_NAME "HI-UX MPP"
#elif defined(_hpux) || \
      defined(hpux) || \
      defined(__hpux)
#define SCPPL_OS_HP_UX
#define SCPPL_OS_NAME "HP-UX"
#elif defined(__OS400__)
#define SCPPL_OS_IBM_OS400
#define SCPPL_OS_NAME "IBM OS/400"
#elif defined(__INTEGRITY)
#define SCPPL_OS_INTEGRITY
#define SCPPL_OS_NAME "INTEGRITY"
#elif defined(__INTERIX)
#define SCPPL_OS_INTERIX_ENVIRONMENT
#define SCPPL_OS_NAME "Interix Environment"
#elif defined(sgi) || \
      defined(__sgi)
#define SCPPL_OS_IRIX
#define SCPPL_OS_NAME "IRIX"
#elif defined(__linux__) || \
      defined(linux) || \
      defined(__linux)
#define SCPPL_OS_LINUX_KERNEL
#define SCPPL_OS_LINUX
#define SCPPL_OS_UNIX
#define SCPPL_OS_NAME "Linux kernel"
#elif defined(__Lynx__)
#define SCPPL_OS_LYNXOS
#define SCPPL_OS_NAME "LynxOS"
#elif defined(macintosh) || \
      defined(Macintosh) || \
      (defined(__APPLE__) && defined(__MACH__))
#define SCPPL_OS_MACOS
#define SCPPL_OS_UNIX
#define SCPPL_OS_NAME "MacOS"
#elif defined(__OS9000) || \
      defined(_OSK)
#define SCPPL_OS_MICROWARE_OS_9
#define SCPPL_OS_NAME "Microware OS-9"
#elif defined(__minix)
#define SCPPL_OS_MINIX
#define SCPPL_OS_UNIX
#define SCPPL_OS_NAME "MINIX"
#elif defined(__MORPHOS__)
#define SCPPL_OS_MORPHOS
#define SCPPL_OS_NAME "MorphOS"
#elif defined(mpeix) || \
      defined(__mpexl)
#define SCPPL_OS_MPEIX
#define SCPPL_OS_NAME "MPE/iX"
#elif defined(MSDOS) || \
      defined(__MSDOS__) || \
      defined(_MSDOS) || \
      defined(__DOS__)
#define SCPPL_OS_MSDOS
#define SCPPL_OS_NAME "MSDOS"
#elif defined(__NetBSD__)
#define SCPPL_OS_NETBSD
#define SCPPL_OS_BSD
#define SCPPL_OS_UNIX
#define SCPPL_OS_NAME "NetBSD"
#elif defined(__TANDEM)
#define SCPPL_OS_NONSTOP
#define SCPPL_OS_NAME "NonStop"
#elif defined(__nucleus__)
#define SCPPL_OS_NUCLEUS_RTOS
#define SCPPL_OS_NAME "Nucleus RTOS"
#elif defined(__OpenBSD__)
#define SCPPL_OS_OPENBSD
#define SCPPL_OS_BSD
#define SCPPL_OS_UNIX
#define SCPPL_OS_NAME "OpenBSD"
#elif defined(OS2) || \
      defined(_OS2) || \
      defined(__OS2__) || \
      defined(__TOS_OS2__)
#define SCPPL_OS_OS2
#define SCPPL_OS_NAME "OS/2"
#elif defined(__palmos__)
#define SCPPL_OS_PALM_OS
#define SCPPL_OS_NAME "Palm OS"
#elif defined(EPLAN9)
#define SCPPL_OS_PLAN_9
#define SCPPL_OS_NAME "Plan 9"
#elif defined(pyr)
#define SCPPL_OS_PYRAMID_DCOSX
#define SCPPL_OS_NAME "Pyramid DC/OSx"
#elif defined(__QNX__) || \
      defined(__QNXNTO__)
#define SCPPL_OS_QNX
#define SCPPL_OS_NAME "QNX"
#elif defined(sinux)
#define SCPPL_OS_RELIANT_UNIX
#define SCPPL_OS_NAME "Reliant UNIX"
#elif defined(M_I386) || \
      defined(M_XENIX) || \
      defined(_SCO_DS)
#define SCPPL_OS_SCO_OPENSERVER
#define SCPPL_OS_NAME "SCO OpenServer"
#elif defined(sun) || \
      defined(__sun)
#define SCPPL_OS_SOLARIS
#define SCPPL_OS_NAME "Solaris"
#elif defined(__VOS__)
#define SCPPL_OS_STRATUS_VOS
#define SCPPL_OS_NAME "Stratus VOS"
#elif defined(__sysv__) || \
      defined(__SVR4) || \
      defined(__svr4__) || \
      defined(_SYSTYPE_SVR4)
#define SCPPL_OS_SVR4_ENVIRONMENT
#define SCPPL_OS_NAME "SVR4 Environment"
#elif defined(__SYLLABLE__)
#define SCPPL_OS_SYLLABLE
#define SCPPL_OS_NAME "Syllable"
#elif defined(__SYMBIAN32__)
#define SCPPL_OS_SYMBIAN_OS
#define SCPPL_OS_NAME "Symbian OS"
#elif defined(__osf__) || \
      defined(__osf)
#define SCPPL_OS_TRU64_OSF1
#define SCPPL_OS_NAME "Tru64 (OSF/1)"
#elif defined(ultrix) || \
      defined(__ultrix) || \
      defined(__ultrix__) || \
      defined(unix) || \
      defined(vax)
#define SCPPL_OS_ULTRIX
#define SCPPL_OS_NAME "Ultrix"
#elif defined(_UNICOS)
#define SCPPL_OS_UNICOS
#define SCPPL_OS_NAME "UNICOS"
#elif defined(_CRAY) || \
      defined(__crayx1)
#define SCPPL_OS_UNICOSMP
#define SCPPL_OS_NAME "UNICOS/mp"
#elif defined(__unix__) || \
      defined(__unix)
#define SCPPL_OS_UNIX_ENVIRONMENT
#define SCPPL_OS_UNIX
#define SCPPL_OS_NAME "UNIX Environment"
#elif defined(sco) || \
      defined(_UNIXWARE7)
#define SCPPL_OS_UNIXWARE
#define SCPPL_OS_NAME "UnixWare"
#elif defined(_UWIN)
#define SCPPL_OS_UWIN_ENVIRONMENT
#define SCPPL_OS_NAME "U/Win Environment"
#elif defined(VMS) || \
      defined(__VMS)
#define SCPPL_OS_VMS
#define SCPPL_OS_NAME "VMS"
#elif defined(__VXWORKS__) || \
      defined(__vxworks)
#define SCPPL_OS_VXWORKS
#define SCPPL_OS_NAME "VxWorks"
#elif defined(_WIN16) || \
      defined(_WIN32) || \
      defined(_WIN64) || \
      defined(__WIN32__) || \
      defined(__TOS_WIN__) || \
      defined(__WINDOWS__)
#define SCPPL_OS_WINDOWS
#define SCPPL_OS_NAME "Windows"
#elif defined(_WIN32_WCE)
#define SCPPL_OS_WINDOWS_CE
#define SCPPL_OS_NAME "Windows CE"
#elif defined(_WINDU_SOURCE)
#define SCPPL_OS_WINDU_ENVIRONMENT
#define SCPPL_OS_NAME "Wind/U Environment"
#elif defined(__MVS__) || \
      defined(__HOS_MVS__) || \
      defined(__TOS_MVS__)
#define SCPPL_OS_ZOS
#define SCPPL_OS_NAME "z/OS"
#else
#define SCPPL_OS_UNKNOWN
#define SCPPL_OS_NAME "Unknown"
#endif
// NOLINTEND(cppcoreguidelines-macro-usage)

/// @endcond

/**
 * @page ARCH Architectures
 *
 * The following architectures are defined along with their name in
 * `SCPPL_ARCH_NAME`.
 *
 * - `SCPPL_ARCH_ALPHA` for "Alpha".
 * - `SCPPL_ARCH_AMD64` for "AMD64".
 * - `SCPPL_ARCH_ARM` for "ARM".
 * - `SCPPL_ARCH_ARM64` for "ARM64".
 * - `SCPPL_ARCH_BLACKFIN` for "Blackfin".
 * - `SCPPL_ARCH_CONVEX` for "Convex".
 * - `SCPPL_ARCH_EPIPHANY` for "Epiphany".
 * - `SCPPL_ARCH_HPPA_RISC` for "HP/PA RISC".
 * - `SCPPL_ARCH_INTEL_X86` for "Intel x86".
 * - `SCPPL_ARCH_INTEL_ITANIUM_IA_64` for "Intel Itanium (IA-64)".
 * - `SCPPL_ARCH_MOTOROLA_68K` for "Motorola 68k".
 * - `SCPPL_ARCH_MIPS` for "MIPS".
 * - `SCPPL_ARCH_POWERPC` for "PowerPC".
 * - `SCPPL_ARCH_PYRAMID_9810` for "Pyramid 9810".
 * - `SCPPL_ARCH_RS6000` for "RS/6000".
 * - `SCPPL_ARCH_SUPERH` for "SuperH".
 * - `SCPPL_ARCH_SYSTEMZ` for "SystemZ".
 * - `SCPPL_ARCH_TMS320` for "TMS320".
 * - `SCPPL_ARCH_TMS470` for "TMS470".
 *
 * If there is no match, `SCPPL_ARCH_UNKNOWN` is defined, with the name
 * "Unknown".
 */

/// @cond

// NOLINTBEGIN(cppcoreguidelines-macro-usage): Allow macro definitions
#if defined(__alpha__) || \
    defined(__alpha) || \
    defined(_M_ALPHA)
#define SCPPL_ARCH_ALPHA
#define SCPPL_ARCH_NAME "Alpha"
#elif defined(__amd64__) || \
      defined(__amd64) || \
      defined(__x86_64__) || \
      defined(__x86_64) || \
      defined(_M_AMD64)
#define SCPPL_ARCH_AMD64
#define SCPPL_ARCH_NAME "AMD64"
#elif defined(__arm__) || \
      defined(__thumb__) || \
      defined(__TARGET_ARCH_ARM) || \
      defined(__TARGET_ARCH_THUMB) || \
      defined(_ARM) || \
      defined(_M_ARM) || \
      defined(_M_ARMT) || \
      defined(__arm)
#define SCPPL_ARCH_ARM
#define SCPPL_ARCH_NAME "ARM"
#elif defined(__aarch64__)
#define SCPPL_ARCH_ARM64
#define SCPPL_ARCH_NAME "ARM64"
#elif defined(__bfin) || \
      defined(__BFIN__)
#define SCPPL_ARCH_BLACKFIN
#define SCPPL_ARCH_NAME "Blackfin"
#elif defined(__convex__)
#define SCPPL_ARCH_CONVEX
#define SCPPL_ARCH_NAME "Convex"
#elif defined(__epiphany__)
#define SCPPL_ARCH_EPIPHANY
#define SCPPL_ARCH_NAME "Epiphany"
#elif defined(__hppa__) || \
      defined(__HPPA__) || \
      defined(__hppa)
#define SCPPL_ARCH_HPPA_RISC
#define SCPPL_ARCH_NAME "HP/PA RISC"
#elif defined(i386) || \
      defined(__i386) || \
      defined(__i386__) || \
      defined(__IA32__) || \
      defined(_M_I86) || \
      defined(_M_IX86) || \
      defined(__X86__) || \
      defined(_X86_) || \
      defined(__THW_INTEL__) || \
      defined(__I86__) || \
      defined(__INTEL__) || \
      defined(__386)
#define SCPPL_ARCH_INTEL_X86
#define SCPPL_ARCH_NAME "Intel x86"
#elif defined(__ia64__) || \
      defined(_IA64) || \
      defined(__IA64__) || \
      defined(__ia64) || \
      defined(_M_IA64) || \
      defined(__itanium__)
#define SCPPL_ARCH_INTEL_ITANIUM_IA_64
#define SCPPL_ARCH_NAME "Intel Itanium (IA-64)"
#elif defined(__m68k__) || \
      defined(M68000) || \
      defined(__MC68K__)
#define SCPPL_ARCH_MOTOROLA_68K
#define SCPPL_ARCH_NAME "Motorola 68k"
#elif defined(__mips__) || \
      defined(mips) || \
      defined(__mips) || \
      defined(__MIPS__)
#define SCPPL_ARCH_MIPS
#define SCPPL_ARCH_NAME "MIPS"
#elif defined(__powerpc) || \
      defined(__powerpc__) || \
      defined(__powerpc64__) || \
      defined(__POWERPC__) || \
      defined(__ppc__) || \
      defined(__ppc64__) || \
      defined(__PPC__) || \
      defined(__PPC64__) || \
      defined(_ARCH_PPC) || \
      defined(_ARCH_PPC64) || \
      defined(_M_PPC) || \
      defined(__ppc)
#define SCPPL_ARCH_POWERPC
#define SCPPL_ARCH_NAME "PowerPC"
#elif defined(pyr)
#define SCPPL_ARCH_PYRAMID_9810
#define SCPPL_ARCH_NAME "Pyramid 9810"
#elif defined(__THW_RS6000) || \
      defined(_IBMR2) || \
      defined(_POWER) || \
      defined(_ARCH_PWR) || \
      defined(_ARCH_PWR2) || \
      defined(_ARCH_PWR3) || \
      defined(_ARCH_PWR4)
#define SCPPL_ARCH_RS6000
#define SCPPL_ARCH_NAME "RS/6000"
#elif defined(__sh__)
#define SCPPL_ARCH_SUPERH
#define SCPPL_ARCH_NAME "SuperH"
#elif defined(__370__) || \
      defined(__THW_370__) || \
      defined(__s390__) || \
      defined(__s390x__) || \
      defined(__zarch__) || \
      defined(__SYSC_ZARCH__)
#define SCPPL_ARCH_SYSTEMZ
#define SCPPL_ARCH_NAME "SystemZ"
#elif defined(_TMS320C2XX) || \
      defined(__TMS320C2000__) || \
      defined(_TMS320C5X) || \
      defined(__TMS320C55X__) || \
      defined(_TMS320C6X) || \
      defined(__TMS320C6X__)
#define SCPPL_ARCH_TMS320
#define SCPPL_ARCH_NAME "TMS320"
#elif defined(__TMS470__)
#define SCPPL_ARCH_TMS470
#define SCPPL_ARCH_NAME "TMS470"
#else
#define SCPPL_ARCH_UNKNOWN
#define SCPPL_ARCH_NAME "Unknown"
#endif
// NOLINTEND(cppcoreguidelines-macro-usage)

/// @endcond

}

#endif
