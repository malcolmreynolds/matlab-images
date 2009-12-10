function plottable = cube_to_plottable(bins)
plottable.r = sum(sum(bins,3),2)';
plottable.g = sum(sum(bins,3),1);
plottable.b = squeeze(sum(sum(bins,2),1))';
