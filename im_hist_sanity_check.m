function im_hist_sanity_check(Im,amask)
% Uses all 3 methods to make 3 1d image histograms and checks they
% are all the same.

h1d = alpha_hist(Im,amask);
h3dslow = im_hist_cube(Im,amask);
h3dfast = im_hist_cube_mex(Im,amask);

h3dslowplot = make_plottable(h3dslow);
h3dfastplot = make_plottable(h3dfast);

%check they are the same here
if ~(isequal(h1d,h3dslowplot)),
  disp('h1d ~= h3dslow');
  draw3hist(difference(h1d,h3dslowplot),'error between alpha\_hist and im\_hist\_cube');
end
if ~(isequal(h1d,h3dfastplot)),
  disp('h1d ~= h3dfast');
  draw3hist(difference(h1d,h3dfastplot),'error between alpha\_hist and im\_hist\_cube\_fast');
end
if ~(isequal(h3dfastplot,h3dslowplot)),
  disp('h3dfast ~= h3dslow');
  draw3hist(difference(h3dfastplot,h3dslowplot),['error between im\_hist\_cube and ' ...
                      'im\_hist\_cube\_fast']);
end

draw3hist(h1d,'alpha\_hist');
draw3hist(h3dslowplot,'im\_hist\_cube');
draw3hist(h3dfastplot,'im\_hist\_cube\_mex');

end

function plottable = make_plottable(bins)
plottable.r = sum(sum(bins,3),2)';
plottable.g = sum(sum(bins,3),1);
plottable.b = squeeze(sum(sum(bins,2),1))';
end

function histdiff = difference(foo,bar)
histdiff.r = foo.r - bar.r;
histdiff.g = foo.g - bar.g;
histdiff.b = foo.b - bar.b;
end