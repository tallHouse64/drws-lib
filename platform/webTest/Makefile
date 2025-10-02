
CC := emcc

FLAGS := -Oz

TEST_FOLDERS := getoutsurftest

getoutsurftest:
	-mkdir getoutsurftest
	-cp page.html getoutsurftest/page.html
	$(CC) getoutsurftest.c -o getoutsurftest/page.js $(FLAGS)


clean:
	-rm -r $(TEST_FOLDERS)
