
# --------------------------------------------------------------------------------------------------------------------------------
# CONFIGURATION
CC_EXTRA_FLAGS := -Wsuggest-override

TARGET_FILENAME := patogaem

THIRDPARTY_REMOTE_LIBS := GL sfml-system sfml-graphics sfml-window pthread sfml-audio
# --------------------------------------------------------------------------------------------------------------------------------
# STATIC

.SECONDEXPANSION:

CC := g++
CC_FLAGS := -std=c++17 -O2 -Wall

BIN_DIR := bin
INCLUDE_DIR := include
SRC_DIR := src
LIB_DIR := lib
BUILD_DIR := build

TARGET := $(BIN_DIR)/$(TARGET_FILENAME)
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

LOCAL_LIBS := $(patsubst $(SRC_DIR)/%/,%,$(wildcard $(SRC_DIR)/*/))
LOCAL_LIBS_FILES := $(patsubst %,$(LIB_DIR)/lib%.a,$(LOCAL_LIBS))

THIRDPARTY_LOCAL_LIBS := $(filter-out $(LOCAL_LIBS),$(patsubst $(LIB_DIR)/lib%.a,%,$(wildcard $(LIB_DIR)/lib*.a)))

THIRDPARTY_REMOTE_LIBS_READY := $(addprefix -l,$(THIRDPARTY_REMOTE_LIBS))
THIRDPARTY_LOCAL_LIBS_READY := $(addprefix -l,$(THIRDPARTY_LOCAL_LIBS))
LOCAL_LIBS_READY := $(addprefix -l,$(patsubst $(SRC_DIR)/%/,%,$(LOCAL_LIBS)))

$(TARGET): $(OBJ_FILES) $(LOCAL_LIBS_FILES)
	$(CC) $(BUILD_DIR)/*.o -o $@ -L$(LIB_DIR) $(LOCAL_LIBS_READY) $(THIRDPARTY_LOCAL_LIBS_READY) $(THIRDPARTY_REMOTE_LIBS_READY)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp _mkdir_$(BUILD_DIR)-$(subst /,-,$$(dir %))
	$(CC) $(CC_FLAGS) $(CC_EXTRA_FLAGS) -I$(INCLUDE_DIR) -I$(SRC_DIR)/$(dir $*) -c -o $@ $<

PERCENT := %
$(LIB_DIR)/lib%.a: $$(patsubst $(SRC_DIR)/$$(PERCENT).cpp, $(BUILD_DIR)/$$(PERCENT).o, $$(wildcard $(SRC_DIR)/%/*.cpp)) _mkdir_$(BUILD_DIR)-%
	ar rcs $@ $(BUILD_DIR)/$*/*.o

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)

clean_all:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)
	rm -f $(LOCAL_LIBS_FILES)

.PHONY: clean clean_all

_mkdir_%:
	mkdir -p $(subst -,/,$*)

# --------------------------------------------------------------------------------------------------------------------------------