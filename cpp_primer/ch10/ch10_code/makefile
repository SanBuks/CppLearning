include ../../Makefile.inc

SALES_ITEM_SOURCE_FILE = Sales_item_test.cc
SALES_ITEM_HEADER_FILE = Sales_item.h
SALES_ITEM_FILE = $(SALES_ITEM_HEADER_FILE) $(SALES_ITEM_SOURCE_FILE)

GENERATE_RANDOM_INT_SOURCE_FILE = generate_random_int.cc
GENERATE_RANDOM_INT_FILE = $(GENERATE_RANDOM_INT_SOURCE_FILE)

all: sales_item random_int

sales_item: $(SALES_ITEM_FILE)
	g++ $(GPP_FLAGS_MULTI) $(SALES_ITEM_SOURCE_FILE) -o sales_item

random_int: $(GENERATE_RANDOM_INT_FILE)
	g++ $(GPP_FLAGS_MULTI) $(GENERATE_RANDOM_INT_SOURCE_FILE) -o random_int

clean:
	rm -rf *.exe Output*