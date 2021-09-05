include ../../Makefile.inc
SALES_DATA_DIR = sales_data
SALES_DATA_FILE = ${SALES_DATA_DIR}/sales_data_main.cpp \
				  ${SALES_DATA_DIR}/sales_data.cpp \
				  ${SALES_DATA_DIR}/sales_data.h

SCREEN_FILE_DIR = screen
SCREEN_FILE = ${SCREEN_FILE_DIR}/screen.h \
			  ${SCREEN_FILE_DIR}/screen.cpp \
			  ${SCREEN_FILE_DIR}/screen_main.cpp \
			  ${SCREEN_FILE_DIR}/window_mgr.h \
			  ${SCREEN_FILE_DIR}/window_mgr.cpp \

.PHONY: sales_data
sales_data: $(SALES_DATA_FILE)
	g++ $(GPP_FLAGS_MULTI) $(SALES_DATA_FILE) -o sales_data
t_sales_data_ctor :
	./sales_data.exe 1
t_sales_data_comb:
	./sales_data.exe 2 < ./sales_data/data
t_sales_data_comb_r:
	./sales_data.exe 3 < ./sales_data/data


.PHONY: screen
screen: $(SCREEN_FILE)
	g++ $(GPP_FLAGS_MULTI) $(SCREEN_FILE) -o screen
t_screen_w:
	./screen.exe 1
t_screen_t:
	./screen.exe 2

.PHONY: clean
clean:
	rm -rf *.exe
