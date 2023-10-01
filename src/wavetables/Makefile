faust_libs := synthwave.lib

all: $(faust_libs)

%.lib: wav2wavetable
	./wav2wavetable -n $* $*/* -o $@

clean:
	rm *.lib