# General Makefile for linux
# Created by: Jean-Christophe Dubois

PROC=linux
TYPE=native

###############################################################################
##  Standard commands
###############################################################################

CC=@gcc
AS=@as
AR=@ar
LD=@ld
NM=@nm
OBJDUMP=@objdump
OBJCOPY=@objcopy
ECHO=@echo
MKDIR=@mkdir -p
RMDIR=@rmdir --ignore-fail-on-non-empty
DEL=@/bin/rm -f
CP=@cp


###############################################################################
##  Source paths
###############################################################################

PROJ_ROOT =.
APP_ROOT  =$(PROJ_ROOT)/App
BSP_ROOT  =$(PROJ_ROOT)/../BSP
CPU_ROOT  =$(PROJ_ROOT)/../../../../../uC-CPU
CPUP_ROOT =$(CPU_ROOT)/Posix/GNU
OS_ROOT   =$(PROJ_ROOT)/../../../../../uCOS-II/Source
OSP_ROOT  =$(OS_ROOT)/../Ports/Posix/GNU
TCP_ROOT  =$(PROJ_ROOT)/../../../../../uC-TCPIP/Source
TCPP_ROOT =$(TCP_ROOT)/../Ports/Posix/GNU
TCPD_ROOT =$(TCP_ROOT)/../Dev/Ether/Posix
TCPP_ROOT =$(TCP_ROOT)/../Dev/Ether/PHY/Generic
TCPI_ROOT =$(TCP_ROOT)/../IF
IPV4_ROOT =$(TCP_ROOT)/../IP/IPv4
LIB_ROOT  =$(PROJ_ROOT)/../../../../../uC-LIB
LIBP_ROOT  =$(LIB_ROOT)/Ports
KAL_ROOT  =$(PROJ_ROOT)/../../../../../uC-Common/KAL/uCOS-II
KAL_HEADER  =$(KAL_ROOT)/../..
OUTPUT    =$(PROJ_ROOT)/output


###############################################################################
##  Commands Parameters
###############################################################################

PROJ_NAME =OS

CFLAGS    =-g -Wall -Werror -m32
#CFLAGS    =-Os -Wall -Werror -m32
CINCLUDES =-I$(APP_ROOT) -I$(BSP_ROOT) -I$(CPU_ROOT) -I$(CPUP_ROOT) -I$(OS_ROOT) -I$(OSP_ROOT) -I$(TCP_ROOT) -I$(LIB_ROOT) -I$(KAL_HEADER) -I$(TCPI_ROOT) -I$(TCPD_ROOT) -I$(TCPP_ROOT)
AINCLUDES =-I$(APP_ROOT),-I$(BSP_ROOT),-I$(CPU_ROOT),-I$(CPUP_ROOT),-I$(OS_ROOT),-I$(OSP_ROOT),-I$(TCP_ROOT),-I$(LIB_ROOT),-I$(KAL_HEADER),-I$(TCPI_ROOT),-I$(TCPD_ROOT),-I$(TCPP_ROOT)
ASFLAGS   =-g
LDFLAGS   =-pthread -m32

OS_SRC      :=ucos_ii.c
OSP_SRC     :=os_cpu_c.c
CPU_SRC     :=
CPUP_SRC    :=
APP_SRC     :=app.c
BSP_SRC     :=
TCP_SRC     :=
TCPI_SRC    :=
TCPD_SRC    :=
TCPP_SRC    :=
IPV4_SRC    :=
KAL_SRC     :=
LIB_SRC     :=

OBJS_C      :=$(addprefix $(OS_ROOT)/,  $(patsubst %.c,%.o,$(filter %.c,$(OS_SRC))))   \
              $(addprefix $(OSP_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(OSP_SRC))))  \
              $(addprefix $(CPU_ROOT)/,$(patsubst %.c,%.o,$(filter %.c,$(CPU_SRC)))) \
              $(addprefix $(CPUP_ROOT)/,$(patsubst %.c,%.o,$(filter %.c,$(CPUP_SRC)))) \
              $(addprefix $(APP_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(APP_SRC))))  \
              $(addprefix $(BSP_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(BSP_SRC))))  \
              $(addprefix $(KAL_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(KAL_SRC))))  \
              $(addprefix $(LIB_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(LIB_SRC))))  \
              $(addprefix $(IPV4_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(IPV4_SRC))))  \
              $(addprefix $(TCPI_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(TCPI_SRC))))  \
              $(addprefix $(TCPP_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(TCPP_SRC))))  \
              $(addprefix $(TCPD_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(TCPD_SRC))))  \
              $(addprefix $(TCP_ROOT)/, $(patsubst %.c,%.o,$(filter %.c,$(TCP_SRC))))  
OBJS_ASM    :=$(addprefix $(OS_ROOT)/,  $(patsubst %.asm,%.o,$(filter %.asm,$(OS_SRC))))   \
              $(addprefix $(OSP_ROOT)/, $(patsubst %.asm,%.o,$(filter %.asm,$(OSP_SRC))))  \
              $(addprefix $(CPUP_ROOT)/,$(patsubst %.asm,%.o,$(filter %.asm,$(CPUP_SRC)))) \
              $(addprefix $(APP_ROOT)/, $(patsubst %.asm,%.o,$(filter %.asm,$(APP_SRC))))  \
              $(addprefix $(BSP_ROOT)/, $(patsubst %.asm,%.o,$(filter %.asm,$(BSP_SRC))))  \
              $(addprefix $(TCP_ROOT)/, $(patsubst %.asm,%.o,$(filter %.asm,$(TCP_SRC))))
OBJS_S      :=$(addprefix $(OS_ROOT)/,  $(patsubst %.s,%.o,$(filter %.s,$(OS_SRC))))   \
              $(addprefix $(OSP_ROOT)/, $(patsubst %.s,%.o,$(filter %.s,$(OSP_SRC))))  \
              $(addprefix $(CPUP_ROOT)/,$(patsubst %.s,%.o,$(filter %.s,$(CPUP_SRC)))) \
              $(addprefix $(APP_ROOT)/, $(patsubst %.s,%.o,$(filter %.s,$(APP_SRC))))  \
              $(addprefix $(BSP_ROOT)/, $(patsubst %.s,%.o,$(filter %.s,$(BSP_SRC))))
              $(addprefix $(TCP_ROOT)/, $(patsubst %.s,%.o,$(filter %.s,$(TCP_SRC))))
OBJS_ALL    :=$(addprefix $(OUTPUT)/obj/,$(notdir $(OBJS_C)) $(notdir $(OBJS_ASM)) $(notdir $(OBJS_S)))


###############################################################################
##  Pattern Rules
###############################################################################

%.o: %.c
	$(ECHO) '$(PROC)/GNU C Compiler building $(notdir $<)'
	$(MKDIR) $(OUTPUT)
	$(MKDIR) $(OUTPUT)/obj
	$(MKDIR) $(OUTPUT)/lst	
	$(CC) -c $(CFLAGS) $(CINCLUDES) -Wa,-alh="$(OUTPUT)/lst/$(notdir $(patsubst %.c,%.lst,$<))",$(AINCLUDES) -o "$(OUTPUT)/obj/$(notdir $@)" "$<"

%.o: %.asm
	$(ECHO) '$(PROC)/GNU ASM Compiler building $(notdir $<)'
	$(MKDIR) $(OUTPUT)
	$(MKDIR) $(OUTPUT)/obj
	$(AS) $(ASFLAGS) $(AINCLUDES) -o "$(OUTPUT)/obj/$(notdir $@)" "$<"

%.o: %.s
	$(ECHO) '$(PROC)/GNU C (ASM Pre-processing) Compiler building $(notdir $<)'
	$(MKDIR) $(OUTPUT)
	$(MKDIR) $(OUTPUT)/obj
	$(MKDIR) $(OUTPUT)/lst
	$(CC) -c $(CFLAGS) $(CINCLUDES) -Wa,-alh="$(OUTPUT)/lst/$(notdir $(patsubst %.s,%.lst,$<))",-L,$(AINCLUDES) -o "$(OUTPUT)/obj/$(notdir $@)" "$<"


###############################################################################
##  Build Rules
###############################################################################

all: build

build: $(OBJS_C) $(OBJS_ASM) $(OBJS_S)
	$(ECHO) '$(PROC)/GNU C Linker building target $(PROJ_NAME)'
	$(MKDIR) $(OUTPUT)
	$(CC) $(LDFLAGS) -o "$(OUTPUT)/$(PROJ_NAME).elf" $(OBJS_ALL)
	$(CP) "$(OUTPUT)/$(PROJ_NAME).elf" "$(PROJ_ROOT)/$(PROJ_NAME).elf"
	$(ECHO) 'Target $(PROJ_NAME) completed.'


clean:
	-$(DEL) $(OUTPUT)/obj/*.o $(OUTPUT)/lst/*.lst
	-$(DEL) "$(OUTPUT)/$(PROJ_NAME).elf"
	-$(DEL) "$(PROJ_ROOT)/$(PROJ_NAME).elf"
	-$(RMDIR) $(OUTPUT)/obj
	-$(RMDIR) $(OUTPUT)/lst
	-$(RMDIR) $(OUTPUT)
	$(ECHO) 'Target $(PROJ_NAME) clean.'
	
