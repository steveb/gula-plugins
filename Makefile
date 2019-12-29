
all: vibey

vibey: vibey.lv2/vibey.so

vibey.lv2/vibey.so: build
	cd build && \
	faust2lv2 -keep \
	          -uri-prefix https://github.com/steveb \
			  vibey.dsp
	cp build/vibey.lv2/vibey.so vibey.lv2/vibey.so

build:
	mkdir build
	cp -r src/* build/

clean:
	rm -f *.lv2/*.so

clean-build:
	rm -rf build

clean-all: clean clean-build