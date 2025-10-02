
CC := emcc

FLAGS := -Oz

TEST_FOLDERS := getoutsurftest

DEPENDENCIES := ../../d.h ../../devents.h ../../dplatform.h ../webd.h

getoutsurftest: getoutsurftest.c page.html $(DEPENDENCIES)
	-mkdir getoutsurftest
	-cp page.html getoutsurftest/page.html
	$(CC) getoutsurftest.c -o getoutsurftest/page.js $(FLAGS)


clean:
	-rm -r $(TEST_FOLDERS)
