LIB_NAME := hw2

ifndef OPTLEVEL
OPTLEVEL := 0
endif

ifndef CUDA_ENABLE
CUDA_ENABLE := 0
endif

CURRENT_BASEIDIR   = $(shell pwd)
CURRENT_SRC_DIR   := ${CURRENT_BASEIDIR}/src
CURRENT_LIB_DIR   := ${CURRENT_BASEIDIR}/lib
CURRENT_OBJ_DIR   := ${CURRENT_BASEIDIR}/obj
CURRENT_HDR_DIR   := ${CURRENT_BASEIDIR}/include
CURRENT_DOC_DIR   := ${CURRENT_BASEIDIR}/docs
CURRENT_TST_DIR   := ${CURRENT_BASEIDIR}/tests

CURRENT_IFLAGS := -I${CURRENT_HDR_DIR}

SRC_FILES_HOST  := $(shell find ${CURRENT_SRC_DIR} -name *.cpp)

HEADER_FILES    := $(shell find ${CURRENT_SRC_DIR} -name *.h)

ifndef TESTS
TESTS := $(wildcard ${CURRENT_TST_DIR}/*)
else
TESTS := $(addprefix ${CURRENT_TST_DIR}/, ${TESTS})
endif

TARGET := ${CURRENT_LIB_DIR}/lib${LIB_NAME}.a

PY_EXE := $(shell which python3)
CC_HOST := $(shell which mpicxx)
CC_DEVICE :=  $(shell which nvcc) -ccbin=${CC_HOST}

CU_O_TARGET_NAME := ${CURRENT_OBJ_DIR}/CU_dlink.o
ifeq (${CUDA_ENABLE}, 1)
LINK_STEP := link_step
CU_O_TARGET := ${CU_O_TARGET_NAME}
ICUDA := -I/usr/local/cuda/include
LCUDA := -L/usr/local/cuda/lib64 -lcudadevrt -lcudart
else
LINK_STEP :=
OBJ_FILES_HYBRID_DEVICE :=
CUDA_ENABLE := 0
OBJ_FILES_CUDA :=
CU_O_TARGET :=
ICUDA :=
LCUDA :=
endif

ifeq (${MEMCHECK}, 1)
VALG := $(shell which valgrind) --error-exitcode=188 --leak-check=full
else
VALG :=
endif
export VALG

COMPILE_TIME_OPT :=
COMPILE_TIME_OPT += -DCUDA_ENABLE=${CUDA_ENABLE}

DEVICE_FLAGS := -O${OPTLEVEL} -x cu -rdc=true -Xcompiler -fPIC ${COMPILE_TIME_OPT} -dc
DEVICE_DLINK_FLAGS := -Xcompiler -fPIC -rdc=true -dlink
HOST_FLAGS := -O${OPTLEVEL} -x c++ -g -Wno-unknown-pragmas -fPIC -fpermissive -std=c++11 -Werror -c ${LCUDA} ${GPROF_FLAG}
export CUDA_ENABLE

ifeq (0, ${CUDA_ENABLE})
SRC_FILES_HYBRID_D :=
endif

CURRENT_IFLAGS += ${ICUDA}

TARGETNAME_HOST     := $(addprefix ${CURRENT_OBJ_DIR}/,$(addsuffix .o,$(notdir ${SRC_FILES_HOST})))
TARGETNAME_CUDA     := $(addprefix ${CURRENT_OBJ_DIR}/,$(addsuffix .o,$(notdir ${SRC_FILES_CUDA})))

SRC_FILES_HOST_DIR := $(dir ${SRC_FILES_HOST})
MP:=%

ifeq (,${TARGETNAME_HYBRID_D})
ifeq (,${TARGETNAME_CUDA})
LINK_STEP :=
endif
endif

export CURRENT_ICONFIG=-I${CURRENT_HDR_DIR} ${ICUDA}
export CURRENT_LCONFIG= ${LCUDA} -L${CURRENT_LIB_DIR} -l${LIB_NAME}
export CC_HOST
export CURRENT_BASEIDIR

.PHONY: final

final: setup ${TARGETNAME_CUDA} ${TARGETNAME_HYBRID_D} ${LINK_STEP} ${TARGETNAME_HYBRID_H} ${TARGETNAME_HOST}
	${CC_HOST} -fPIC -shared ${GPROF_FLAG} ${CURRENT_OBJ_DIR}/*.o ${CURRENT_IFLAGS} ${IFLAGS_DEPENDENCIES} ${COMPILE_TIME_OPT} ${LZLIB} ${LCUDA} ${LFLAGS_DEPENDENCIES} -o ${TARGET}

.SECONDEXPANSION:
${TARGETNAME_HYBRID_D}: ${CURRENT_OBJ_DIR}/%.o : $$(filter $$(MP)/$$*,$$(SRC_FILES_HYBRID_D))
	${CC_DEVICE} ${DEVICE_FLAGS} ${COMPILE_TIME_OPT} ${CURRENT_IFLAGS} ${IFLAGS_DEPENDENCIES} $< -o $@

.SECONDEXPANSION:
${TARGETNAME_HYBRID_H}: ${CURRENT_OBJ_DIR}/%.o : $$(filter $$(MP)/$$*,$$(SRC_FILES_HYBRID_H))
	${CC_HOST} ${HOST_FLAGS} ${COMPILE_TIME_OPT} ${CURRENT_IFLAGS} ${IFLAGS_DEPENDENCIES} $< -o $@

.SECONDEXPANSION:
${TARGETNAME_HOST}: ${CURRENT_OBJ_DIR}/%.o : $$(filter $$(MP)/$$*,$$(SRC_FILES_HOST))
	${CC_HOST} ${HOST_FLAGS} ${COMPILE_TIME_OPT} ${CURRENT_IFLAGS} ${IFLAGS_DEPENDENCIES} $< -o $@

.SECONDEXPANSION:
${TARGETNAME_CUDA}: ${CURRENT_OBJ_DIR}/%.o : $$(filter $$(MP)/$$*,$$(SRC_FILES_CUDA))
	${CC_DEVICE} ${DEVICE_FLAGS} ${COMPILE_TIME_OPT} ${CURRENT_IFLAGS} ${IFLAGS_DEPENDENCIES} $< -o $@

${LINK_STEP}:
	${CC_DEVICE} ${DEVICE_DLINK_FLAGS} ${COMPILE_TIME_OPT} ${OBJ_FILES_HYBRID_DEVICE} ${OBJ_FILES_CUDA} -o ${CU_O_TARGET} -lcudadevrt

setup:
	-rm -r ${CURRENT_HDR_DIR}
	mkdir -p ${CURRENT_LIB_DIR}
	mkdir -p ${CURRENT_OBJ_DIR}
	mkdir -p ${CURRENT_HDR_DIR}
	@for hdr in ${HEADER_FILES} ; do\
		echo "Linking $${hdr}:";\
		ln -s $${hdr} -t ${CURRENT_HDR_DIR};\
	done

clean:
	-rm -r ${CURRENT_LIB_DIR}
	-rm -r ${CURRENT_OBJ_DIR}
	-rm -r ${CURRENT_HDR_DIR}
	@for tdir in ${TESTS} ; do\
		${MAKE} -C $${tdir} -f makefile clean;\
	done

test: ${DOCLEAN} final
	@for tdir in ${TESTS} ; do\
		${MAKE} -C $${tdir} -f makefile test || exit 4;\
	done
	@echo "ALL TESTS SUCCESSFUL"
