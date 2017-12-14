.PHONY: all asan build test do_test clean
.DEFAULT_GOAL := all

ASAN=false
MSAN=false
TSAN=false

BUILD_DIR=./build/
# BINDINGS_DIR=./bindings/
TEST_DIR=${BUILD_DIR}tests/

OPT_COMPILER=-DCMAKE_CXX_COMPILER=clang++
OPT_ASAN=-DASAN=ON
OPT_TSAN=-DTSAN=ON
OPT_MSAN=-DMSAN=ON
OPT_GTEST=-DGTEST=ON
OPT_DEBUG=-DDEBUG_MODE=ON

.mkdir:
	@mkdir -p ${BUILD_DIR}

.run_test:
	@echo -e '\n-------- TESTING --------\n'
	@if [ ${ASAN} = true ]; \
	then \
		(cd ${TEST_DIR} && ASAN_SYMBOLIZER_PATH=$(shell which llvm-symbolizer) ./tests); \
	elif [ ${TSAN} = true ]; \
	then \
		(cd ${TEST_DIR} && TSAN_SYMBOLIZER_PATH=$(shell which llvm-symbolizer) ./tests); \
	elif [ ${MSAN} = true ]; \
	then \
		(cd ${TEST_DIR} && MSAN_SYMBOLIZER_PATH=$(shell which llvm-symbolizer) ./tests); \
	else \
		(cd ${TEST_DIR} && ctest); \
	fi

all: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} .. && $(MAKE) VERBOSE=1)

asan: .mkdir
	$(eval ASAN=true)
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_ASAN} .. && $(MAKE) VERBOSE=1)

debug: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_DEBUG} .. && $(MAKE) VERBOSE=1)

test: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_GTEST} .. && $(MAKE) VERBOSE=1)

asan_test: .mkdir
	$(eval ASAN=true)
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_ASAN} ${OPT_GTEST} .. && $(MAKE) VERBOSE=1)

tsan_test: .mkdir
	$(eval TSAN=true)
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_TSAN} ${OPT_GTEST} .. && $(MAKE) VERBOSE=1)

msan_test: .mkdir
	$(eval MSAN=true)
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_MSAN} ${OPT_GTEST} .. && $(MAKE) VERBOSE=1)

debug_test: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_DEBUG} ${OPT_GTEST} .. && $(MAKE) VERBOSE=1)

full_test: .mkdir
	$(eval ASAN=true)
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_ASAN} ${OPT_GTEST} ${OPT_DEBUG} .. && $(MAKE) VERBOSE=1)

do_test: test .run_test

do_asan_test: asan_test .run_test

do_tsan_test: tsan_test .run_test

do_msan_test: msan_test .run_test

do_debug_test: debug_test .run_test

do_full_test: full_test .run_test

clean:
	@$(RM) -rf ${BUILD_DIR}
	@$(RM) ${DEFAULT_COVERAGE_DATA} ${DEFAULT_COVERAGE_RAW}
