PROCESSOS= commander manager reporter

all: $(PROCESSOS)

commander:
	$(MAKE) -C Commander $(COMANDO)

manager:
	$(MAKE) -C Manager $(COMANDO)

reporter:
	$(MAKE) -C Reporter $(COMANDO)

.PHONY : clean
clean: COMANDO+=clean
clean: all
