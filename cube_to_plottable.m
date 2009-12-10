function plottable = cube_to_plottable(bins)
%converts a 3d histogram of voxels into a struct containing a 1d
%array for each colour channel. Looses information, but crucially
%much easier to plot.
plottable.r = sum(sum(bins,3),2)';
plottable.g = sum(sum(bins,3),1);
plottable.b = squeeze(sum(sum(bins,2),1))';
