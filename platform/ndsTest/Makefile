
getoutsurftest: getoutsurftest.c ../ndsd.h ../../d.h ../../devents.h ../../dplatform.h exampleMakefile
	-mkdir getoutsurftest
	-mkdir getoutsurftest/source
	-mkdir getoutsurftest/source/platform
	cp -f getoutsurftest.c getoutsurftest/source/main.c
	cp -f ../ndsd.h getoutsurftest/source/platform
	cp -f ../../d.h getoutsurftest/source
	cp -f ../../devents.h getoutsurftest/source
	cp -f ../../dplatform.h getoutsurftest/source
	cp -f exampleMakefile getoutsurftest/Makefile
	$(MAKE) -C getoutsurftest

clean:
	-rm -r getoutsurftest
