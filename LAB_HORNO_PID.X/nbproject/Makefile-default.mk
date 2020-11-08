#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/LAB_HORNO_PID.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/LAB_HORNO_PID.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c xlcd.c hardware_init.c PID_HORNO.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/xlcd.o ${OBJECTDIR}/hardware_init.o ${OBJECTDIR}/PID_HORNO.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/xlcd.o.d ${OBJECTDIR}/hardware_init.o.d ${OBJECTDIR}/PID_HORNO.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/xlcd.o ${OBJECTDIR}/hardware_init.o ${OBJECTDIR}/PID_HORNO.o

# Source Files
SOURCEFILES=main.c xlcd.c hardware_init.c PID_HORNO.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/LAB_HORNO_PID.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ32MC202
MP_LINKER_FILE_OPTION=,--script=p33FJ32MC202.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  .generated_files/562a7987d48a456a1fb2b88ee2c5c3c2fcb4262d.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/xlcd.o: xlcd.c  .generated_files/653a31a64f8e1885cc5f511be133fffa03057d18.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/xlcd.o.d 
	@${RM} ${OBJECTDIR}/xlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  xlcd.c  -o ${OBJECTDIR}/xlcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/xlcd.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/hardware_init.o: hardware_init.c  .generated_files/2bfa0e07416bcaceb18f12a3302f3cad47d52d86.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hardware_init.o.d 
	@${RM} ${OBJECTDIR}/hardware_init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  hardware_init.c  -o ${OBJECTDIR}/hardware_init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/hardware_init.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/PID_HORNO.o: PID_HORNO.c  .generated_files/50dc7339e339a75ac47b4650b2ca9f0787f799a9.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PID_HORNO.o.d 
	@${RM} ${OBJECTDIR}/PID_HORNO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PID_HORNO.c  -o ${OBJECTDIR}/PID_HORNO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/PID_HORNO.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/main.o: main.c  .generated_files/4264873e853e46638f978a86a8bcecaa6c9d80be.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/xlcd.o: xlcd.c  .generated_files/d719d67112d161d819db0b984c75db839fc9c2aa.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/xlcd.o.d 
	@${RM} ${OBJECTDIR}/xlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  xlcd.c  -o ${OBJECTDIR}/xlcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/xlcd.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/hardware_init.o: hardware_init.c  .generated_files/acb5a3080d4a08bc74c8de6e3f7a69cf0389c94.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hardware_init.o.d 
	@${RM} ${OBJECTDIR}/hardware_init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  hardware_init.c  -o ${OBJECTDIR}/hardware_init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/hardware_init.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/PID_HORNO.o: PID_HORNO.c  .generated_files/e9e4a47e500aaa2c64fcdfe34853c733a8f39b8a.flag .generated_files/6fa25bf04b30d9bb4edd8837a4a601db4f515c90.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PID_HORNO.o.d 
	@${RM} ${OBJECTDIR}/PID_HORNO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PID_HORNO.c  -o ${OBJECTDIR}/PID_HORNO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/PID_HORNO.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/LAB_HORNO_PID.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/LAB_HORNO_PID.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/LAB_HORNO_PID.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/LAB_HORNO_PID.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/LAB_HORNO_PID.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
