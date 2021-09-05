HEADER_FILE_RELATIVE_PATH = ../../header
HEADER_FILE_RELATIVE_PATH_MULTI = ../../../header
GPP_FLAGS = -std=c++11 \
            -g \
            -pedantic \
            -Wall \
            -Wno-unused-variable \
            -Wno-multichar \
            -I ${HEADER_FILE_RELATIVE_PATH}
GPP_FLAGS_MULTI = -std=c++11 \
                  -g \
                  -pedantic \
                  -Wall \
                  -Wno-unused-variable \
                  -Wno-multichar \
                  -I ${HEADER_FILE_RELATIVE_PATH_MULTI}