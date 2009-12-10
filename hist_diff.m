function diff = hist_diff(foo,bar)
%subtracts two colour histograms so the difference can be plotted
%(using draw3hist.m)
diff.r = foo.r - bar.r;
diff.g = foo.g - bar.g;
diff.b = foo.b - bar.b;