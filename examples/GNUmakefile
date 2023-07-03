EXAMPLES := 1.bmp 2.bmp

all: $(EXAMPLES)
.PHONY: all

%.bmp: tmp/%.exe
	./$< $@.tmp
	mv $@.tmp $@

tmp/%.exe: src/%.c tmp/libft_bmp.a
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) -I ../include $(CFLAGS) $(LDFLAGS) src/$*.c -L tmp -l ft_bmp -o $@.tmp
	mv $@.tmp $@

.NOTPARALLEL: tmp/libft_bmp.a
tmp/libft_bmp.a:
	mkdir -p $(@D)
	NAME=examples/tmp/libft_bmp.a $(MAKE) -C ..

.PHONY: clean
clean:
	rm -rf tmp
.PHONY: fclean
fclean: clean
	rm -f $(EXAMPLES)
