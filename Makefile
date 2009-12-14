
allmex: im_hist_cube_res.mexmaci  \
				cube_diff_sse.mexmaci \
				im_hist_cube_mex.mexmaci \
				cube_sse_unsafe.mexmaci \
				norm_cube.mexmaci \
				thresh_cubes.mexmaci

LIBS = mex_im_utils.o

#for now, assume all the files are dependent on all the libs (only 1 anyway...)
%.mexmaci : %.c $(LIBS)
	mex CFLAGS='$$CFLAGS -Wall -std=c99' -o $@ $< $(LIBS)

%.o : %.c %.h
	mex CFLAGS='$$CFLAGS -Wall -std=c99' -c $<

#mex_im_utils.o: mex_im_utils.c mex_im_utils.h
#	mex CFLAGS='$$CFLAGS -Wall' -c mex_im_utils.c

.PHONY: clean

clean:
	rm -f *.o
	rm -f *.mexmaci
