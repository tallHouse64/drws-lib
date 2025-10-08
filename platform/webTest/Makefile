
CC := emcc

FLAGS := -sASYNCIFY -Oz

TEST_FOLDERS := getoutsurftest pumpeventstest

DEPENDENCIES := page.html ../../d.h ../../devents.h ../../dplatform.h ../webd.h

getoutsurftest: getoutsurftest.c $(DEPENDENCIES)
	-mkdir getoutsurftest
	-cp page.html getoutsurftest/page.html
	$(CC) getoutsurftest.c -o getoutsurftest/page.js $(FLAGS)

pumpeventstest: pumpeventstest.c $(DEPENDENCIES)
	-mkdir pumpeventstest
	-cp page.html pumpeventstest/page.html
	$(CC) pumpeventstest.c -o pumpeventstest/page.js $(FLAGS)

clean:
	-rm -r $(TEST_FOLDERS)
