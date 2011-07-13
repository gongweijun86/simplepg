CC = gcc
CPPFLAGS = -c -g

CUR_DIR = $(shell pwd)
OBJDIR_O = $(CUR_DIR)/objdir_o
OBJDIR_D = $(CUR_DIR)/objdir_d

SOURCES = $(wildcard ./src/*.c)
OBJS = $(foreach obj,$(SOURCES:.c=.o),$(OBJDIR_O)/$(notdir $(obj)))

define MKDIR
@echo 'making directory $(OBJDIR_D)...'
if [ ! -d $(OBJDIR_D) ];then mkdir $(OBJDIR_D);fi
@echo 'making directory $(OBJDIR_O)...'
if [ ! -d $(OBJDIR_O) ];then mkdir $(OBJDIR_O);fi
@echo ''
endef

main:$(OBJ)
	@echo "building target $(@)..."
	$(CC) -o main $(OBJS)
	@echo "finished building target $(@)."
	@echo ''
out:
	$(MKDIR)

include $(SOURCES:.c=.d)

%.d: %.c out
	@echo 'building $(<)'
	$(CC) -MMD -MF $(OBJDIR_D)/$(notdir $(*)).d $(CPPFLAGS) $(<) -o $(OBJDIR_O)/$(notdir $(*)).o
	@echo 'finished building $(<).'
	@echo ''
.PHONY: clean
clean:
	@echo "clean the project..."
	-rm -rf $(OBJDIR_O) $(OBJDIR_D) main
