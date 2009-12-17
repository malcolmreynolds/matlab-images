function ss = hist_ss(h)
% Returns sum of squared values in a histogram - this wil
% correspond to sum of squared errors assuming the histogram has
% been created from two others using hist_diff. Adds together the
% sum of squares from however many lines are represented.

ss = 0;

for l=1:length(h.lines),
  ss = ss + sum(h.lines{l}.bins .^ 2);
end