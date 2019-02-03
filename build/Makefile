CPP         = g++
CFLAGS      = -O2 -std=c++14 -D_RPI
INC         = -I/opt/vc/include
DEPS        = fruitbox.hpp fruitbox_types.hpp pages.hpp status.hpp playqueue.hpp audio.hpp config.hpp config_base.hpp database.hpp display.hpp \
              engine.hpp fruitbox_logo.hpp info_bkgnd.hpp chooser_arrow.hpp info_font.hpp status_events.hpp userguide.hpp bitmap.hpp joystick.hpp \
              display_base.hpp input.hpp gpio.hpp
OBJ         = fruitbox.o playqueue.o audio.o config.o database.o display.o engine.o pages.o status.o userguide.o bitmap.o joystick.o input.o gpio.o
LIBS        = -lmpg123 -lm -ldl -L/opt/vc/lib/
STATIC_LIBS = allegro-static-5 allegro_memfile-static-5 allegro_font-static-5 allegro_ttf-static-5 allegro_primitives-static-5 \
              allegro_image-static-5 allegro_audio-static-5 allegro_acodec-static-5 allegro_video-static-5

%.o: %.cpp $(DEPS)
	$(CPP) -c -o $@ $< $(CFLAGS) $(INC)

# ./fruitbox: $(OBJ)
../fruitbox: $(OBJ)
	$(CPP) -Wall -o $@ $^ $(CFLAGS) $(LIBS) `pkg-config --libs --static $(STATIC_LIBS)`

.PHONY: clean
clean:
	rm -f *.o
	rm -f ../fruitbox
	touch Makefile
	touch *.?pp
