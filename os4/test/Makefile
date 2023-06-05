CC := gcc
CFLAGS := -Wall -Wextra
# LDFLAGS := -lreadline

TARGET := test
SRCS := test.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)
