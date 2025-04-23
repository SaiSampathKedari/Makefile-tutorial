MODULE_NAME = mod4
TEST_MODULE = test_mod4

TEST_BIN_DIR = ../../test_build

TARGET_DIR = ../../libs
TARGET_NAME = lib$(MODULE_NAME).a
TARGET = $(TARGET_DIR)/$(TARGET_NAME)

OBJ_DIR = ../../objs
OBJ1 = $(OBJ_DIR)/$(MODULE_NAME).o

INC_PATH = ../../share_headers
WARN_FLAGS = -Wall -Werror
CFLAGS = $(WARN_FLAGS) -I$(INC_PATH)
LIB_PATH = ../../libs
LDFLAGS = -L$(LIB_PATH) -lmod4 -Wl,-rpath=$(LIB_PATH)

$(TARGET): $(OBJ1)
	ar rcs $@ $^

$(OBJ1): $(MODULE_NAME).cpp
	g++ $(CFLAGS) -c $< -o $@

test: $(TEST_MODULE).cpp
	g++ $(CFLAGS) $(TEST_MODULE).cpp -o $(TEST_BIN_DIR)/$(TEST_MODULE) $(LDFLAGS)

install:
	cp *.h ../../share_headers/

clean:
	rm $(TARGET) $(OBJ1) $(TEST_BIN_DIR)/$(TEST_MODULE)