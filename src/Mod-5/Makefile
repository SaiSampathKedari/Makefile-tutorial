MODULE_NAME = mod5
TEST_MODULE = test_mod5

TEST_BIN_DIR = ../../test_build

TARGET_DIR = ../../bins
TARGET_NAME = $(MODULE_NAME)_bin
TARGET = $(TARGET_DIR)/$(TARGET_NAME)

OBJ_DIR = ../../objs
OBJ1 = $(OBJ_DIR)/$(MODULE_NAME).o

INC_PATH = ../../share_headers
WARN_FLAGS = -Wall -Werror
CFLAGS = $(WARN_FLAGS) -I$(INC_PATH)
LIB_PATH = ../../libs
LDFLAGS = -L$(LIB_PATH) -lmod4 -lmod2 -Wl,-rpath=$(LIB_PATH)

$(TARGET): $(OBJ1)
	g++ $< -o $@ $(LDFLAGS)

$(OBJ1): $(MODULE_NAME).cpp
	g++ $(CFLAGS) -c $< -o $@

clean:
	rm $(TARGET) $(OBJ1)