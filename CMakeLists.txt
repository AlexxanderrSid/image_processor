add_executable(
        image_processor
        image_processor.cpp
        constant.h reading_and_writing/reader.cpp
        reading_and_writing/reader.h
        image/image.cpp
        image/image.h parser_and_controller/parser.cpp
        parser_and_controller/parser.h
        reading_and_writing/writer.cpp
        reading_and_writing/writer.h
        filters/filters.cpp
        filters/filters.h
        parser_and_controller/filter_controller.cpp
        parser_and_controller/filter_controller.h)

add_catch(image_processor_parser_test
        tests/parser_test.cpp
        parser_and_controller/parser.cpp
        )

add_catch(image_processor_filter_controller_test
        tests/filter_controller_test.cpp
        parser_and_controller/filter_controller.cpp
        image/image.cpp
        filters/filters.cpp
        )

add_catch(image_processor_reading_test
        tests/reading_test.cpp
        reading_and_writing/reader.cpp
        image/image.cpp
        )

add_catch(image_processor_writing_test
        tests/writing_test.cpp
        reading_and_writing/writer.cpp
        image/image.cpp
        )
