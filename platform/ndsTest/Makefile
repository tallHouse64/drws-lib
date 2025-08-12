
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

delaytest: delaytest.c ../ndsd.h ../../d.h ../../devents.h ../../dplatform.h exampleMakefile
	-mkdir delaytest
	-mkdir delaytest/source
	-mkdir delaytest/source/platform
	cp -f delaytest.c delaytest/source/main.c
	cp -f ../ndsd.h delaytest/source/platform
	cp -f ../../d.h delaytest/source
	cp -f ../../devents.h delaytest/source
	cp -f ../../dplatform.h delaytest/source
	cp -f exampleMakefile delaytest/Makefile
	$(MAKE) -C delaytest

pumpeventstest: pumpeventstest.c ../ndsd.h ../../d.h ../../devents.h ../../dplatform.h exampleMakefile
	-mkdir pumpeventstest
	-mkdir pumpeventstest/source
	-mkdir pumpeventstest/source/platform
	cp -f pumpeventstest.c pumpeventstest/source/main.c
	cp -f ../ndsd.h pumpeventstest/source/platform
	cp -f ../../d.h pumpeventstest/source
	cp -f ../../devents.h pumpeventstest/source
	cp -f ../../dplatform.h pumpeventstest/source
	cp -f exampleMakefile pumpeventstest/Makefile
	$(MAKE) -C pumpeventstest

clean:
	-rm -r getoutsurftest delaytest pumpeventstest
