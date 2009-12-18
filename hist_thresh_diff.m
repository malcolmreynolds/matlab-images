function masks = hist_thresh_diff(h1,h2,factor);
% Create binary mask which can be multiply by other hists similar
% to h1 and h2. The idea is areas will be zeroed out which are of
% similar value in h1 and h2, because they are not hugely useful in
% the computation.

diff = hist_diff(h1,h2);

numlines = length(diff.lines);

for l=1:numlines,
  masks{l} = make_mask(diff.lines{l}.bins,factor);
end

end


function m = make_mask(bins,factor)
% Make the binary mask for a line. We're going to deal with
% everything that is within some factor of the maximum (for
% positive values) or the same factor of the minimum (for
% negative). I don't know if this asymmetry makes a lot of sense
% but hey lets just go with it for now.
the_max = max(bins);
the_min = min(bins);

max_thresh = factor * the_max;
min_thresh = factor * the_min;

m = (bins > max_thresh) | (bins < min_thresh);

end