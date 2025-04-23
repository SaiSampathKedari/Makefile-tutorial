MODULE_NAME = mod2
TEST_MODULE = test_mod2

TEST_BIN_DIR = ../../test_build

TARGET_DIR = ../../libs
TARGET_NAME = lib$(MODULE_NAME).so
TARGET = $(TARGET_DIR)/$(TARGET_NAME)

OBJ_DIR = ../../objs
OBJ1 = $(OBJ_DIR)/$(MODULE_NAME).o

CFLAGS = -fPIC -Wall -Werror
LDFLAGS = -L$(TARGET_DIR) -l$(MODULE_NAME) -Wl,-rpath=$(TARGET_DIR)


$(TARGET): $(OBJ1)
	g++ -shared $< -o $@ $(LDFLAGS)

$(OBJ1): $(MODULE_NAME).cpp
	g++ $(CFLAGS) -c $< -o $@

test: $(TEST_MODULE).cpp
	g++ $(CFLAGS) $(TEST_MODULE).cpp -o $(TEST_BIN_DIR)/$(TEST_MODULE) $(LDFLAGS)

install:
	cp *.h ../../share_headers/

clean:
	rm -rf $(TARGET) $(OBJ1) $(TEST_BIN_DIR)/$(TEST_MODULE)